//----------------------------------------------------------------------------
// LyricsManager.cpp : bass.dll を使った音の再生管理
//----------------------------------------------------------------------------
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
extern "C"
{
	#define XMD_H
	#include "../Common/jpeglib.h"
	#include "../Common/jerror.h"
}
#include "../App.h"
#include "../Common/bassenc.h"
#include "MainWnd.h"
#include "LyricsManager.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CLyricsManager::CLyricsManager(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), nLine(0), dMaxCharacters(0.0)
{
	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	bmi.bmiHeader.biHeight = -GetSystemMetrics(SM_CYVIRTUALSCREEN);
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	HDC tmpDC = GetDC(GetDesktopWindow());
	hBitmap = CreateDIBSection(tmpDC, &bmi, DIB_RGB_COLORS, (void**)&pImage, 0,
		0);

	hMemDC = CreateCompatibleDC(tmpDC);
	HGDIOBJ hOldHandle = SelectObject(hMemDC, hBitmap);
	ReleaseDC(GetDesktopWindow(), tmpDC);

	SetTextColor(hMemDC, RGB(255,255,255));
	SetBkMode(hMemDC, TRANSPARENT);
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CLyricsManager::~CLyricsManager()
{
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBackBitmap);
	if(hBackDC) DeleteDC(hBackDC);
	DeleteObject(hFont);
}
//----------------------------------------------------------------------------
// 歌詞を追加
//----------------------------------------------------------------------------
void CLyricsManager::AddLyrics(double dStartTime, double dEndTime, tstring str,
							   BOOL bReline)
{
	ST_LYRICS stl = {dStartTime, dEndTime, str, bReline};
	arrayLyrics.push_back(stl);
}
//----------------------------------------------------------------------------
// 画面をクリア
//----------------------------------------------------------------------------
void CLyricsManager::ClearScreen()
{
	BOOL bFullScreen = m_rMainWnd.IsFullScreen();
	CWnd* pWnd;
	if(bFullScreen) pWnd = (CWnd*)&m_rMainWnd.GetVideoScreenWnd();
	else pWnd = (CWnd*)&m_rMainWnd.GetVideoScreen();

	HBRUSH hBackBrush	= (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush	= (HBRUSH)SelectObject(hMemDC, hBackBrush);
	Rectangle(hMemDC, 0, 0, pWnd->GetWidth(), pWnd->GetHeight());

	SelectObject(hMemDC, hOldBrush);
	DeleteObject(hBackBrush);

	pWnd->InvalidateRect(NULL, TRUE);
}
//----------------------------------------------------------------------------
// タイトル画面を描画
//----------------------------------------------------------------------------
void CLyricsManager::DrawTitle(CWnd* pWnd)
{
	if(strTitle == _T("") && strArtist == _T("")) return;

	SIZE sizeTitle;
	if(strTitle != _T("")) {
		GetTextExtentPoint32(hMemDC, strTitle.c_str(),
							 static_cast<int>(strTitle.length()), &sizeTitle);
		int nLeft = (pWnd->GetWidth() - sizeTitle.cx) / 2;
		int nTop = (pWnd->GetHeight() - sizeTitle.cy) / 2;
		if(pWnd->GetHeight() < sizeTitle.cy * 3) nTop = 0;
		BeginPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, strTitle.c_str(),
				lstrlen(strTitle.c_str()));
		EndPath(hMemDC);
		StrokeAndFillPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, strTitle.c_str(),
				lstrlen(strTitle.c_str()));
	}

	if(strArtist != _T("")) {
		tstring str = _T("♪") + strArtist;
		SIZE sizeArtist;
		GetTextExtentPoint32(hMemDC, str.c_str(),
								static_cast<int>(str.length()), &sizeArtist);
		int nLeft = (pWnd->GetWidth() - sizeArtist.cx) / 2;
		int nTop = (pWnd->GetHeight() + sizeArtist.cy) / 2;
		if(pWnd->GetHeight() < sizeArtist.cy * 3) nTop = sizeTitle.cy;
		BeginPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, str.c_str(), lstrlen(str.c_str()));
		EndPath(hMemDC);
		StrokeAndFillPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, str.c_str(), lstrlen(str.c_str()));
	}
}
//----------------------------------------------------------------------------
// １行を描画
//----------------------------------------------------------------------------
void CLyricsManager::DrawLine(tstring str, int nLine, CWnd* pWnd)
{
	if(str == _T("")) return;
	tstring strMargin = _T("　");
	SIZE size;
	GetTextExtentPoint32(hMemDC, strMargin.c_str(),
						 static_cast<int>(strMargin.length()), &size);
	int nMargin = size.cx;

	GetTextExtentPoint32(hMemDC, str.c_str(), static_cast<int>(str.length()),
						 &size);
	if(nLine == 1) {
		int nLeft = nMargin;
		if(nLeft + size.cx < pWnd->GetWidth() / 2 + nMargin)
			nLeft = pWnd->GetWidth() / 2 + nMargin - size.cx;
		int nTop = pWnd->GetHeight() - size.cy * 5;
		if(nTop < 0) nTop = 0;
		BeginPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, str.c_str(), lstrlen(str.c_str()));
		EndPath(hMemDC);
		StrokeAndFillPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, str.c_str(), lstrlen(str.c_str()));
	}
	else {
		int nLeft = pWnd->GetWidth() - size.cx - nMargin;
		if(nLeft > pWnd->GetWidth() / 2 - nMargin)
			nLeft = pWnd->GetWidth() / 2 - nMargin;
		int nTop = pWnd->GetHeight() - size.cy * 3;
		if(nTop < nMargin) nTop = nMargin;
		BeginPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, str.c_str(), lstrlen(str.c_str()));
		EndPath(hMemDC);
		StrokeAndFillPath(hMemDC);
		TextOut(hMemDC, nLeft, nTop, str.c_str(), lstrlen(str.c_str()));
	}
}
//----------------------------------------------------------------------------
// 文字の長さを得る
//----------------------------------------------------------------------------
double CLyricsManager::GetCharacterLength(tstring str)
{
	double dLength = 0.0;
	for(int i = 0; i < (int)str.length(); i++) {
		TCHAR ch = str.at(i);
		if('0' <= ch && ch <= '9') dLength += 0.5;
		else if('a' <= ch && ch <= 'z') dLength += 0.5;
		else if('A' <= ch && ch <= 'Z') dLength += 0.5;
		else if(ch == ' ' || ch == '(' || ch == ')' || ch == ',' ||
				ch == '.' || ch == '\'' || ch == '-')
			dLength += 0.5;
		else dLength += 1.0;
	}
	return dLength;
}
//----------------------------------------------------------------------------
// 拡張タイムタグを得る
//----------------------------------------------------------------------------
double CLyricsManager::GetExtendedTimeTag(LPTSTR p)
{
	tstring strMinutes = (tstring)&p[1] + (tstring)&p[2];
	tstring strSeconds = (tstring)&p[4] + (tstring)&p[5];
	tstring strMilliSeconds = (tstring)&p[7] + (tstring)&p[8];
	double dMinutes = (double)_tstof(strMinutes.c_str());
	double dSeconds = (double)_tstof(strSeconds.c_str());
	double dMilliSeconds = (double)_tstof(strMilliSeconds.c_str());
	return dMinutes * 60.0 + dSeconds + dMilliSeconds / 100.0;
}
//----------------------------------------------------------------------------
// タイムタグを得る
//----------------------------------------------------------------------------
double CLyricsManager::GetTimeTag(LPTSTR p)
{
	tstring strMinutes = (tstring)&p[1] + (tstring)&p[2];
	tstring strSeconds = (tstring)&p[4] + (tstring)&p[5];
	double dMinutes = (double)_tstof(strMinutes.c_str());
	double dSeconds = (double)_tstof(strSeconds.c_str());
	return dMinutes * 60.0 + dSeconds;
}
//----------------------------------------------------------------------------
// タグの値を得る
//----------------------------------------------------------------------------
tstring CLyricsManager::GetTagValue(LPTSTR p)
{
	tstring str;
	while(*p != ']') str += *p++;
	return str;
}
//----------------------------------------------------------------------------
// 拡張タイムタグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsExtendedTimeTag(LPTSTR p)
{
	if((p[0] == '[' || p[0] == '<') && IsNumeric(&p[1]) && IsNumeric(&p[2]) &&
		p[3] == ':' && IsNumeric(&p[4], TRUE) && IsNumeric(&p[5]) &&
	   (p[6] == ':' || p[6] == '.') && IsNumeric(&p[7]) && IsNumeric(&p[8]) &&
	   (p[9] == ']' || p[9] == '>'))
		return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// 数値かどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsNumeric(LPTSTR p, BOOL bBeforeFive)
{
	if(bBeforeFive) // 0～5までかどうかチェック
		return (*p == '0' || *p == '1' || *p == '2' || *p == '3' ||
				*p == '4' || *p == '5');
	else
		return (*p == '0' || *p == '1' || *p == '2' || *p == '3' ||
				*p == '4' || *p == '5' || *p == '6' || *p == '7' ||
				*p == '8' || *p == '9');
}
//----------------------------------------------------------------------------
// タイムタグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsTimeTag(LPTSTR p)
{
	if((p[0] == '[' || p[0] == '<') && IsNumeric(&p[1]) && IsNumeric(&p[2]) &&
		p[3] == ':' && IsNumeric(&p[4], TRUE) && IsNumeric(&p[5]) &&
	   (p[6] == ']' || p[6] == '>'))
		return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// タグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsTag(LPTSTR p)
{
	if(p[0] == '[' && p[3] == ':') return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// アーティストタグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsArtistTag(LPTSTR p)
{
	if(p[0] == '[' && p[1] == 'a' && p[2] == 'r' && p[3] == ':') return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// オフセットタグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsOffsetTag(LPTSTR p)
{
	if(p[0] == '[' && p[1] == 'o' && p[2] == 'f' && p[3] == 'f' &&
	   p[4] == 's'  && p[5] == 'e'  && p[6] == 't' && p[7] == ':')
		return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// タイトルタグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsTitleTag(LPTSTR p)
{
	if(p[0] == '[' && p[1] == 't' && p[2] == 'i' && p[3] == ':') return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// 背景画像フォルダタグかどうか
//----------------------------------------------------------------------------
BOOL CLyricsManager::IsBgFolderTag(LPTSTR p)
{
	if(p[0] == '[' && p[1] == 'b' && p[2] == 'g' && p[3] == 'f' && p[4] == 'o'
		 && p[5] == 'l' && p[6] == 'd' && p[7] == 'e' && p[8] == 'r'
		 && p[9] == ':') return TRUE;
	return FALSE;
}
//----------------------------------------------------------------------------
// 画像の読み込み
//----------------------------------------------------------------------------
void CLyricsManager::LoadBackImage(tstring strPath, double dLevel)
{
	if(strBackPath == strPath) return;
	strBackPath = strPath;
	FILE *fp = NULL;
	_tfopen_s(&fp, strPath.c_str(), _T("rb"));
	if(fp == NULL) return;

	jpeg_decompress_struct cInfo;
	jpeg_error_mgr jErr;

	cInfo.err = jpeg_std_error(&jErr);
	jpeg_create_decompress(&cInfo);
	jpeg_stdio_src(&cInfo, fp);
	jpeg_read_header(&cInfo, TRUE);
	jpeg_start_decompress(&cInfo);

	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(bmih));
	bmih.biSize = sizeof(bmih);
	bmih.biWidth = cInfo.output_width;
	bmih.biHeight = cInfo.output_height;
	bmih.biPlanes = 1;
	bmih.biBitCount = cInfo.out_color_components * 8;
	bmih.biCompression = BI_RGB;

	LPBYTE lpBuf;
	HDC tmpDC = GetDC(GetDesktopWindow());
	hBackBitmap = CreateDIBSection(tmpDC, (BITMAPINFO*)&bmih, DIB_RGB_COLORS,
		(void**)&lpBuf, 0, 0);
	if(hBitmap == NULL) {
		jpeg_destroy_decompress(&cInfo);
		fclose( fp );
		return;
	}
	int nJpegLineBytes = cInfo.output_width * cInfo.output_components;
	long nBmpLineBytes = (cInfo.output_width * 3 + 3) & 0xfffffffcL;

	lpBuf += cInfo.output_height * nBmpLineBytes;
	while(cInfo.output_scanline < cInfo.output_height) {
		lpBuf -= nBmpLineBytes;
		JSAMPROW praw = (JSAMPROW)lpBuf;
		jpeg_read_scanlines(&cInfo, (JSAMPARRAY)&praw, 1);
		for(int i = 0; i < (int)cInfo.output_width; i++) {
			if(cInfo.out_color_components == 3) {
				BYTE R = (BYTE)(*praw + (255 - *praw) * dLevel);
				praw++;
				BYTE G = (BYTE)(*praw + (255 - *praw) * dLevel);
				praw++;
				BYTE B = (BYTE)(*praw + (255 - *praw) * dLevel);
				praw++;
				praw[-3] = B;
				praw[-2] = G;
				praw[-1] = R;
			}
		}
	}

	if(hBackDC) DeleteDC(hBackDC);
	hBackDC = CreateCompatibleDC(tmpDC);
	HGDIOBJ hOldHandle = SelectObject(hBackDC, hBackBitmap);
	ReleaseDC(GetDesktopWindow(), tmpDC);

	jpeg_finish_decompress(&cInfo);
	jpeg_destroy_decompress(&cInfo);

	fclose(fp);

	nBackWidth = cInfo.output_width;
	nBackHeight = cInfo.output_height;
}
//----------------------------------------------------------------------------
// 歌詞の読み込み
//----------------------------------------------------------------------------
BOOL CLyricsManager::Read(tstring strOriginalFilePath)
{
	nLine = 0;
	dMaxCharacters = 0.0;
	arrayLyrics.clear();
	TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_tsplitpath_s(strOriginalFilePath.c_str(), drive, _MAX_DRIVE,
				  dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
	tstring strPath;
	tstring strKraPath = (tstring)drive + (tstring)dir + (tstring)fname +
					  (tstring)_T(".kra");
	tstring strLrcPath = (tstring)drive + (tstring)dir + (tstring)fname +
					  (tstring)_T(".lrc");
	tstring strTxtPath = (tstring)drive + (tstring)dir + (tstring)fname +
					  (tstring)_T(".txt");
	if(PathFileExists(strKraPath.c_str())
	   && !PathIsDirectory(strKraPath.c_str()))
	   strPath = strKraPath;
	else if(PathFileExists(strLrcPath.c_str())
			&& !PathIsDirectory(strLrcPath.c_str()))
	   strPath = strLrcPath;
	else if(PathFileExists(strTxtPath.c_str())
			&& !PathIsDirectory(strTxtPath.c_str()))
	   strPath = strTxtPath;
	else
		return FALSE;

	FILE *fp;
	_tfopen_s(&fp, strPath.c_str(), _T("r"));
	if(!fp) return FALSE;

	HANDLE hFile = CreateFile(strPath.c_str(), GENERIC_READ,
							  FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
							  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
	DWORD fileSize = GetFileSize(hFile, NULL) + 1;
	if((int)fileSize <= 1) return FALSE;

	TCHAR * pBuf = new TCHAR[fileSize];

	strTitle.clear();
	strArtist.clear();
	m_arStrBackPath.clear();
	double dTime = 0.0;
	double dStartTime = 0.0;
	double dEndTime = 0.0;
	double dOffset = 0.0;
	tstring strBuf = _T("");
	tstring strLastBuf = _T("");
	BOOL bReline = FALSE;
	BOOL bTimeTagExist = FALSE; // タイムタグが存在したかどうか
	while(_fgetts(pBuf, fileSize, fp) != NULL) {
		TCHAR * p = pBuf;
		BOOL bTagLine = FALSE;
		BOOL bFirstCharacter = TRUE;
		BOOL bCharacterExist = FALSE;
		while(*p != '\n' && *p != '\r' && *p != NULL) {
			if(bFirstCharacter && *p == '@') {
				bTagLine = TRUE;
				TCHAR * pTag = CharNext(p);
				tstring strTag;
				while(*pTag != '=' && *pTag != '\n' && *pTag != '\r' &&
					  *pTag != NULL) {
					strTag += (TCHAR)_totlower(*pTag);
					pTag = CharNext(pTag);
				}
				tstring strValue;
				TCHAR * pValue = CharNext(pTag);
				while(*pValue != '\n' && *pValue != '\r' && *pValue != NULL) {
					strValue += (TCHAR)_totlower(*pValue);
					pValue = CharNext(pValue);
				}

				if(strTag == _T("offset"))
					dOffset = (double)_tstof(strValue.c_str()) / 1000;
				else if(strTag == _T("title")) strTitle = strValue;
				else if(strTag == _T("artist")) strArtist = strValue;
				break;
			}
			bFirstCharacter = FALSE;
			if(IsExtendedTimeTag(p)) {
				bTimeTagExist = TRUE;
				dTime = GetExtendedTimeTag(p);
				if(bReline) {
					dEndTime = dTime;
					AddLyrics(dStartTime, dEndTime, strLastBuf, bReline);
					double dCharacterLength = GetCharacterLength(strLastBuf);
					if(dCharacterLength > dMaxCharacters)
						dMaxCharacters = dCharacterLength;
					strLastBuf.clear();
					bReline = FALSE;
				}
				if(strBuf != _T("")) {
					dEndTime = dTime;
					AddLyrics(dStartTime, dEndTime, strBuf, FALSE);
					double dCharacterLength = GetCharacterLength(strBuf);
					if(dCharacterLength > dMaxCharacters)
						dMaxCharacters = dCharacterLength;
					strBuf.clear();
				}
				dStartTime = dTime;
				for(int i = 0; i < 10; i++) p = CharNext(p);
				continue;
			}
			else if(IsTimeTag(p)) {
				bTimeTagExist = TRUE;
				dTime = GetTimeTag(p);
				if(bReline) {
					dEndTime = dTime;
					AddLyrics(dStartTime, dEndTime, strLastBuf, bReline);
					double dCharacterLength = GetCharacterLength(strLastBuf);
					if(dCharacterLength > dMaxCharacters)
						dMaxCharacters = dCharacterLength;
					strLastBuf.clear();
					bReline = FALSE;
				}
				if(strBuf != _T("")) {
					dEndTime = dTime;
					AddLyrics(dStartTime, dEndTime, strBuf, FALSE);
					double dCharacterLength = GetCharacterLength(strBuf);
					if(dCharacterLength > dMaxCharacters)
						dMaxCharacters = dCharacterLength;
					strBuf.clear();
				}
				dStartTime = dTime;
				for(int i = 0; i < 7; i++) p = CharNext(p);
				continue;
			}
			else if(IsTitleTag(p)) {
				TCHAR * pValue = p;
				for(int i = 0; i < 4; i++) pValue = CharNext(pValue);
				strTitle = GetTagValue(pValue);
				for(int i = 0; i < (int)strTitle.length() + 5; i++)
					p = CharNext(p);
				bTagLine = TRUE;
				continue;
			}
			else if(IsArtistTag(p)) {
				TCHAR * pValue = p;
				for(int i = 0; i < 4; i++) pValue = CharNext(pValue);
				strArtist = GetTagValue(pValue);
				for(int i = 0; i < (int)strArtist.length() + 5; i++)
					p = CharNext(p);
				bTagLine = TRUE;
				continue;
			}
			else if(IsOffsetTag(p)) {
				TCHAR * pValue = p;
				for(int i = 0; i < 8; i++) pValue = CharNext(pValue);
				tstring strValue = GetTagValue(pValue);
				dOffset = (double)_tstof(strValue.c_str()) / 1000;
				for(int i = 0; i < (int)strValue.length() + 9; i++)
					p = CharNext(p);
				bTagLine = TRUE;
				continue;
			}
			else if(IsBgFolderTag(p)) {
				m_arStrBackPath.clear();
				TCHAR * pValue = p;
				for(int i = 0; i < 10; i++) pValue = CharNext(pValue);
				tstring strPath = GetTagValue(pValue);

				SetCurrentDirectory(strPath.c_str());
				WIN32_FIND_DATA wfd;
				HANDLE hFind = FindFirstFile(TEXT("*.*"), &wfd);
				if(hFind != INVALID_HANDLE_VALUE) {
					do {
						if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
							continue;
						TCHAR szFilePath[MAX_PATH];
						lstrcpy(szFilePath, strPath.c_str());
						lstrcat(szFilePath, _T("\\"));
						lstrcat(szFilePath, wfd.cFileName);
						TCHAR chExt[_MAX_EXT];
						_tsplitpath_s(szFilePath, NULL, 0, NULL, 0, NULL, 0,
							chExt, _MAX_EXT);
						if(_tcsicmp(chExt, _T(".jpg")) == 0 ||
							_tcsicmp(chExt, _T(".jpeg")) == 0)
								m_arStrBackPath.push_back(szFilePath);
					}
					while(FindNextFile(hFind, &wfd));
				}

				for(int i = 0; i < (int)strPath.length() + 11; i++)
					p = CharNext(p);
				bTagLine = TRUE;
				continue;
			}
			else if(IsTag(p)) {
				bTagLine = TRUE;
				break;
			}
			bCharacterExist = TRUE;
			strBuf += *p;
			p = CharNext(p);
		}
		if(!bTagLine) {
			if(bCharacterExist && strBuf == _T(""))
				arrayLyrics[arrayLyrics.size() - 1].bReline = TRUE;
			else {
				strLastBuf = strBuf;
				strBuf.clear();
				bReline = TRUE;
			}
		}
	}
	if(bReline) {
		dEndTime = 5999.99;
		AddLyrics(dStartTime, dEndTime, strLastBuf, bReline);
		double dCharacterLength = GetCharacterLength(strLastBuf);
		if(dCharacterLength > dMaxCharacters)
			dMaxCharacters = dCharacterLength;
	}

	// タイムタグが存在しない場合は終了
	if(!bTimeTagExist) return FALSE;

	// Offsetタグによる補正
	for(int i = 0; i < (int)arrayLyrics.size(); i++) {
		arrayLyrics[i].dStartTime += dOffset;
		if(arrayLyrics[i].dStartTime < 0.0)
			arrayLyrics[i].dStartTime = 0.0;
		arrayLyrics[i].dEndTime += dOffset;
		if(arrayLyrics[i].dEndTime < 0.0)
			arrayLyrics[i].dEndTime = 0.0;
	}

	delete[] pBuf;
	CloseHandle(hFile);
	fclose(fp);
	ZeroMemory(&stlLast, sizeof(stlLast));
	stlLast.strLyrics = _T("");

	return TRUE;
}
//----------------------------------------------------------------------------
// 歌詞の表示
//----------------------------------------------------------------------------
void CLyricsManager::Update(double dCurrentTime)
{
	if(!m_rMainWnd.IsLyricsThreadAlive()) return;
	BOOL bFullScreen = m_rMainWnd.IsFullScreen();
	CWnd* pWnd;
	if(bFullScreen) pWnd = (CWnd*)&m_rMainWnd.GetVideoScreenWnd();
	else pWnd = (CWnd*)&m_rMainWnd.GetVideoScreen();
	HWND hWnd = *pWnd;

	HBRUSH hBackBrush	= (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush	= (HBRUSH)SelectObject(hMemDC, hBackBrush);
	Rectangle(hMemDC, 0, 0, pWnd->GetWidth(), pWnd->GetHeight());
	SelectObject(hMemDC, hOldBrush);
	DeleteObject(hBackBrush);

	if(m_arStrBackPath.size() > 0) {
		int nCurrent = (int)(dCurrentTime / 6) % m_arStrBackPath.size();
		if((int)dCurrentTime % 6 < 1) {
			LoadBackImage(m_arStrBackPath[nCurrent], dCurrentTime - (int)dCurrentTime);
		}
		else
			LoadBackImage(m_arStrBackPath[nCurrent], 1.0);
		SetStretchBltMode(hMemDC, HALFTONE);
		SetBrushOrgEx(hMemDC, 0, 0, NULL);
		int nScreenWidth = pWnd->GetWidth();
		int nScreenHeight = pWnd->GetHeight();
		BOOL bVertical = FALSE;
		if((double)nScreenWidth / (double)nScreenHeight >
				(double)nBackWidth / (double)nBackHeight)
			bVertical = TRUE;
		if(bVertical) {
			int nWidth = pWnd->GetHeight() * nBackWidth / nBackHeight;
			int nLeft = pWnd->GetWidth() / 2 - nWidth / 2;
			StretchBlt(hMemDC, nLeft, 0, nWidth, pWnd->GetHeight(), hBackDC, 0,
				0, nBackWidth, nBackHeight, SRCCOPY);
		}
		else {
			int nHeight = pWnd->GetWidth() * nBackHeight / nBackWidth;
			int nTop = pWnd->GetHeight() / 2 - nHeight / 2;
			StretchBlt(hMemDC, 0, nTop, pWnd->GetWidth(), nHeight, hBackDC, 0,
				0, nBackWidth, nBackHeight, SRCCOPY);
		}
		DeleteObject(hBackBitmap);
	}

	HPEN	hPen	= (HPEN)CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH	hBrush	= (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	HPEN	hOldPen	= (HPEN)SelectObject(hMemDC, hPen);
	hOldBrush		= (HBRUSH)SelectObject(hMemDC, hBrush);
	int nFontSize = (int)(pWnd->GetWidth() / (dMaxCharacters + 2.0));
	if(nFontSize > pWnd->GetHeight() / 2)
		nFontSize = pWnd->GetHeight() / 2;
	HFONT hFont = CreateFont(
		-nFontSize, 0, 0, 0, 0,
		FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH,
		_T("麗流隷書"));
	HFONT hOldFont = (HFONT)SelectObject(hMemDC, hFont);

	tstring str;
	int i = 0;
	BOOL bTitle = FALSE;
	if(dCurrentTime < arrayLyrics[0].dStartTime) {
		bTitle = TRUE;
		nLine = 0;
	}
	else {
		BOOL bExist = FALSE;
		for(; i < (int)arrayLyrics.size(); i++) {
			str += arrayLyrics[i].strLyrics;
			if(arrayLyrics[i].dStartTime <= dCurrentTime &&
			   dCurrentTime < arrayLyrics[i].dEndTime)
			   bExist = TRUE;
			if(arrayLyrics[i].bReline) {
				if(bExist) break;
				else str.clear();
			}
		}
	}
	ST_LYRICS stl;
	stl.strLyrics = str;
	stl.dStartTime = arrayLyrics[i].dStartTime;
	stl.dEndTime = arrayLyrics[i].dEndTime;
	BOOL bFirst = !(stlLast.strLyrics != _T("") || stlLast.dStartTime != 0.0 ||
					stlLast.dEndTime != 0.0);
	if(!bTitle &&
	  (stl.strLyrics	!=	stlLast.strLyrics	||
	   stl.dStartTime	!=	stlLast.dStartTime	||
	   stl.dEndTime		!=	stlLast.dEndTime)) {
		if(nLine == 0 || nLine == 2) nLine = 1;
		else nLine = 2;
		stlLast.strLyrics	= stl.strLyrics;
		stlLast.dStartTime	= stl.dStartTime;
		stlLast.dEndTime	= stl.dEndTime;
	}
	if(bTitle) DrawTitle(pWnd);
	else DrawLine(str, nLine, pWnd);
	if(!bTitle && nLine == 1) {
		tstring strLine2;
		for(i++; i < (int)arrayLyrics.size(); i++) {
			strLine2 += arrayLyrics[i].strLyrics;
			if(arrayLyrics[i].bReline)
				break;
		}
		DrawLine(strLine2, 2, pWnd);
	}

	CClientDC dc(hWnd);
	BitBlt(dc, 0, 0, pWnd->GetWidth(), pWnd->GetHeight(), hMemDC, 0, 0,
		SRCCOPY);

	SelectObject(hMemDC, hOldPen);
	SelectObject(hMemDC, hOldBrush);
	SelectObject(hMemDC, hOldFont);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(hFont);
}
//----------------------------------------------------------------------------
