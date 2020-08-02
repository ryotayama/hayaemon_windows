//----------------------------------------------------------------------------
// PlayListView_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include <vector>
#include <shlwapi.h>
#include "../resource.h"
#include "../App.h"
#include "../Common/CommandList.h"
#include "../Common/nsfsdk.h"
#include "EQ20KLabel_MainWnd.h"
#include "EQ20KSlider_MainWnd.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "M3UFile.h"
#include "Sound.h"
#include "Tab_MainWnd.h"

typedef struct _tagSORTDATA{
    HWND hwndList; // リストビューのhwnd
	int isortSubItem; // ソートするサブアイテムインデックス
    int iUPDOWN; // 昇順か降順か
} SORTDATA;
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CTagEdit::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_UP:
		m_rParent.OnUpKeyPressed();
		break;
	case VK_DOWN:
		m_rParent.OnDownKeyPressed();
		break;
	case VK_LEFT:
		m_rParent.OnLeftKeyPressed();
		break;
	case VK_RIGHT:
		m_rParent.OnRightKeyPressed();
		break;
	}
	CEditExt::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CPlayListView_MainWnd::CPlayListView_MainWnd(CApp & app, CMainWnd & mainWnd)
: m_rApp(app), m_rMainWnd(mainWnd), m_nHeaderHeight(0), m_rClickMenu(*this),
  isLastSortUp(FALSE), lastSort(-1), m_edit(*this)
{
	hMp3infpDll = LoadLibrary((app.GetFilePath()
		+ _T("mp3infp.dll")).c_str());
	lpmp3infp_Load
		= (LPMP3INFP_LOAD)GetProcAddress(hMp3infpDll, "mp3infp_LoadW");
	lpmp3infp_SetConf
		= (LPMP3INFP_SETCONF)GetProcAddress(hMp3infpDll, "mp3infp_SetConfW");
	lpmp3infp_GetType
		= (LPMP3INFP_GETTYPE)GetProcAddress(hMp3infpDll, "mp3infp_GetType");
	lpmp3infp_GetValue =
		(LPMP3INFP_GETVALUE)GetProcAddress(hMp3infpDll, "mp3infp_GetValueW");
	lpmp3infp_mp3_GetTagType = (LPMP3INFP_MP3_GETTAGTYPE)
		GetProcAddress(hMp3infpDll, "mp3infp_mp3_GetTagType");
	lpmp3infp_SetValue
		= (LPMP3INFP_SETVALUE)GetProcAddress(hMp3infpDll, "mp3infp_SetValueW");
	lpmp3infp_Save
		= (LPMP3INFP_SAVE)GetProcAddress(hMp3infpDll, "mp3infp_SaveW");
	lpmp3infp_mp3_MakeId3v1 = (LPMP3INFP_MP3_MAKEID3V1)
		GetProcAddress(hMp3infpDll, "mp3infp_mp3_MakeId3v1W");
	lpmp3infp_mp3_MakeId3v2 = (LPMP3INFP_MP3_MAKEID3V2)
		GetProcAddress(hMp3infpDll, "mp3infp_mp3_MakeId3v2W");
	lpmp3infp_mp3_MakeRMP = (LPMP3INFP_MP3_MAKERMP)
		GetProcAddress(hMp3infpDll, "mp3infp_mp3_MakeRMPW");
	lpmp3infp_mp3_MakeApeTag = (LPMP3INFP_MP3_MAKEAPETAG)
		GetProcAddress(hMp3infpDll, "mp3infp_mp3_MakeApeTagW");
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddDirectory(LPCTSTR lpszDirectoryPath)
{
	TCHAR szOriginalDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szOriginalDirectory);

	SetCurrentDirectory(lpszDirectoryPath);

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(_T("*.*"), &wfd);
	if(hFind == INVALID_HANDLE_VALUE) return;

	do {
		if(_tcscmp(wfd.cFileName, _T(".")) == 0 ||
		   _tcscmp(wfd.cFileName, _T("..")) == 0)
			continue;

		TCHAR szFilePath[MAX_PATH];
		lstrcpy(szFilePath, lpszDirectoryPath);
		lstrcat(szFilePath, _T("\\"));
		lstrcat(szFilePath, wfd.cFileName);
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			AddDirectory(szFilePath);
			continue;
		}

		AddFile(szFilePath);
	}
	while(FindNextFile(hFind, &wfd));
	FindClose(hFind);

	SetCurrentDirectory(szOriginalDirectory);
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddFile(LPCTSTR lpszFilePath, int nPos)
{
	if(PathIsURL(lpszFilePath)) {
		AddURL(lpszFilePath);
		return;
	}

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(lpszFilePath, &wfd);
	if(hFind == INVALID_HANDLE_VALUE) return;
	FindClose(hFind);
	if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		AddDirectory(lpszFilePath);
		return;
	}

	TCHAR chExt[_MAX_EXT];
	_tsplitpath_s(lpszFilePath, NULL, 0, NULL, 0, NULL, 0, chExt, _MAX_EXT);

	// 拡張子によっては、プレイリストとして読み込み
	int listType = 0;
	if(_tcsicmp(chExt, _T(".m3u")) == 0) listType = 1;
	else if (_tcsicmp(chExt, _T(".m3u8")) == 0) listType = 2;

	if(listType) {
		CM3UFile file;
		file.Init();
		file.Read(lpszFilePath, listType == 2);
		for(int j = 0; j < file.GetLinesCount(); j++)
			AddFile(file.GetFilePath(j).c_str());
		return;
	}

	// 読み込めない拡張子の場合、何もしない
	if( _tcsicmp(chExt, _T(".wav")) != 0 && _tcsicmp(chExt, _T(".cda")) != 0 &&
		_tcsicmp(chExt, _T(".mp3")) != 0 && _tcsicmp(chExt, _T(".mp2")) != 0 &&
		_tcsicmp(chExt, _T(".mp1")) != 0 && _tcsicmp(chExt, _T(".ogg")) != 0 &&
		_tcsicmp(chExt, _T(".wma")) != 0 && _tcsicmp(chExt, _T(".aiff")) != 0 &&
		_tcsicmp(chExt, _T(".aif")) != 0 && _tcsicmp(chExt, _T(".ape")) != 0 &&
		_tcsicmp(chExt, _T(".flac")) != 0 && _tcsicmp(chExt, _T(".m4a")) != 0 &&
		_tcsicmp(chExt, _T(".m4b")) != 0 &&
		_tcsicmp(chExt, _T(".mp4")) != 0 && _tcsicmp(chExt, _T(".aac")) != 0 &&
		_tcsicmp(chExt, _T(".avi")) != 0 && _tcsicmp(chExt, _T(".wmv")) != 0 &&
		_tcsicmp(chExt, _T(".mkv")) != 0 && _tcsicmp(chExt, _T(".flv")) != 0 &&
		_tcsicmp(chExt, _T(".nsf")) != 0)
		return;

	// No.
	int n = nPos < 0 ? GetItemCount() : nPos;
	InsertItem(n);
	TCHAR text[13];
	_stprintf_s(text, _T("%d"), n + 1);
	SetItem(n, 1, text);

	SetItem(n, 0, _T(""), -1);

	// ファイル名を取得
	TCHAR chFileName[_MAX_FNAME + _MAX_EXT];
	TCHAR chFileExt[_MAX_EXT];
	_tsplitpath_s(lpszFilePath, NULL, 0, NULL, 0, chFileName, _MAX_FNAME,
					chFileExt, _MAX_EXT);

	// タイトル
	SetItem(n, 2, chFileName);

	// ファイルパス
	SetItem(n, 7, lpszFilePath);

	orders.push_back(-1);
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddFile(LPCTSTR lpszFilePath, int nPos,
									LPCTSTR lpszTitle, LPCTSTR lpszArtist,
									LPCTSTR lpszYear, LPCTSTR lpszLength)
{
	// No.
	int n = nPos < 0 ? GetItemCount() : nPos;
	InsertItem(n);
	TCHAR text[13];
	_stprintf_s(text, _T("%d"), n + 1);
	SetItem(n, 1, text);

	SetItem(n, 0, _T(""), -1);

	// ファイル名を取得
	TCHAR chFileName[_MAX_FNAME + _MAX_EXT];
	TCHAR chFileExt[_MAX_EXT];
	_tsplitpath_s(lpszFilePath, NULL, 0, NULL, 0, chFileName, _MAX_FNAME,
					chFileExt, _MAX_EXT);

	// タイトル
	SetItem(n, 2, lpszTitle);

	// アーティスト
	SetItem(n, 3, lpszArtist);

	// 年
	SetItem(n, 4, lpszYear);

	// 長さ
	SetItem(n, 5, lpszLength);

	// ファイル名
	lstrcat(chFileName, chFileExt);
	SetItem(n, 6, chFileName);

	// ファイルパス
	SetItem(n, 7, lpszFilePath);

	orders.push_back(-1);
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddURL(LPCTSTR lpszFilePath, int nPos)
{
	TCHAR chExt[_MAX_EXT];
	_tsplitpath_s(lpszFilePath, NULL, 0, NULL, 0, NULL, 0, chExt, _MAX_EXT);

	// 読み込めない拡張子の場合、何もしない
	if( _tcsicmp(chExt, _T(".wav")) != 0 && _tcsicmp(chExt, _T(".cda")) != 0 &&
		_tcsicmp(chExt, _T(".mp3")) != 0 && _tcsicmp(chExt, _T(".mp2")) != 0 &&
		_tcsicmp(chExt, _T(".mp1")) != 0 && _tcsicmp(chExt, _T(".ogg")) != 0 &&
		_tcsicmp(chExt, _T(".wma")) != 0 && _tcsicmp(chExt, _T(".aiff")) != 0 &&
		_tcsicmp(chExt, _T(".aif")) != 0 && _tcsicmp(chExt, _T(".ape")) != 0 &&
		_tcsicmp(chExt, _T(".flac")) != 0 && _tcsicmp(chExt, _T(".m4a")) != 0 &&
		_tcsicmp(chExt, _T(".m4b")) != 0 &&
		_tcsicmp(chExt, _T(".mp4")) != 0 && _tcsicmp(chExt, _T(".aac")) != 0 &&
		_tcsicmp(chExt, _T(".avi")) != 0 && _tcsicmp(chExt, _T(".wmv")) != 0 &&
		_tcsicmp(chExt, _T(".mkv")) != 0 && _tcsicmp(chExt, _T(".flv")) != 0)
		return;

	// No.
	int n = nPos < 0 ? GetItemCount() : nPos;
	InsertItem(n);
	TCHAR text[13];
	_stprintf_s(text, _T("%d"), n + 1);
	SetItem(n, 1, text);

	SetItem(n, 0, _T(""), -1);

	// ファイル名を取得
	TCHAR chFileName[_MAX_FNAME + _MAX_EXT];
	TCHAR chFileExt[_MAX_EXT];
	_tsplitpath_s(lpszFilePath, NULL, 0, NULL, 0, chFileName, _MAX_FNAME,
					chFileExt, _MAX_EXT);

	// タイトル
	SetItem(n, 2, chFileName);

	// ファイルパス
	SetItem(n, 7, lpszFilePath);

	orders.push_back(-1);
}
//----------------------------------------------------------------------------
// 選択中のファイルをコピー
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::CopySelectedItem(int nDst)
{
	m_rMainWnd.GetTab().SetCurrentFocus(nDst);
	int nItem = -1;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		TCHAR chPath[_MAX_PATH];
		GetItemText(nItem, 7, chPath, _MAX_PATH);
		m_rMainWnd.AddFile(chPath);
	}
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPlayListView_MainWnd::Create()
{
	CListView::Create(m_rMainWnd.GetTab(), LVS_EDITLABELS);
	if(!m_hWnd) return FALSE;
	SetExStyle(GetExStyle() | WS_EX_ACCEPTFILES);

	ResetPos();

	InsertColumn(0, _T(""), LVCFMT_LEFT, 17, 0);
	InsertColumn(1, _T("No."), LVCFMT_RIGHT, 30, 1);
#if JP
	InsertColumn(2, _T("タイトル"), LVCFMT_LEFT, 200, 2);
	InsertColumn(3, _T("アーティスト"), LVCFMT_LEFT, 150, 3);
	InsertColumn(4, _T("年"), LVCFMT_LEFT, 40, 4);
	InsertColumn(5, _T("長さ"), LVCFMT_RIGHT, 50, 5);
	InsertColumn(6, _T("ファイル名"), LVCFMT_LEFT, 150, 6);
	InsertColumn(7, _T("場所"), LVCFMT_LEFT, 200, 7);
#else // JP
	InsertColumn(2, _T("Title"), LVCFMT_LEFT, 200, 2);
	InsertColumn(3, _T("Artist"), LVCFMT_LEFT, 150, 3);
	InsertColumn(4, _T("Year"), LVCFMT_LEFT, 40, 4);
	InsertColumn(5, _T("Length"), LVCFMT_RIGHT, 50, 5);
	InsertColumn(6, _T("File Name"), LVCFMT_LEFT, 150, 6);
	InsertColumn(7, _T("Path"), LVCFMT_LEFT, 200, 7);
#endif // JP

	hSmall = ImageList_Create(16, 16, ILC_COLOR, 2, 0);
	SetImageList(hSmall, LVSIL_SMALL);
	ImageList_AddIcon(hSmall, LoadIcon(GetModuleHandle(NULL),
					  (LPCTSTR)IDI_PLAY));
	ImageList_AddIcon(hSmall, LoadIcon(GetModuleHandle(NULL),
					  (LPCTSTR)IDI_PAUSE));

	InsertItem(0);
	RECT rc;
	GetItemRect(0, &rc, LVIR_BOUNDS);
	m_nHeaderHeight = rc.top;
	DeleteItem(0);

	InitSize();

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);

	m_edit.Create(m_hWnd);
	m_edit.SetStyle(m_edit.GetStyle() | ES_LEFT | ES_AUTOHSCROLL);
	m_edit.SetFont(m_font, TRUE);

	return TRUE;
}
//----------------------------------------------------------------------------
// 新しい再生リストの作成
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::CreateNewList()
{
	m_rMainWnd.CreateNewList();
	int nItem = -1;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		TCHAR chPath[_MAX_PATH];
		GetItemText(nItem, 7, chPath, _MAX_PATH);
		m_rMainWnd.AddFile(chPath);
	}
}
//----------------------------------------------------------------------------
// 選択アイテムを削除
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::DeleteSelectedItems()
{
	BOOL bPlayNext = FALSE;
	BOOL bStop = FALSE;
	BOOL bCurTab = (HWND)m_rMainWnd.GetCurPlayList() == m_hWnd;
	int nItem = -1;
	while((nItem = GetNextItem(-1, LVNI_SELECTED)) >= 0) {
		FixPlayOrder(nItem);
		DeleteItem(nItem);
		if(bCurTab) {
			int nCurItem = m_rMainWnd.GetSound().GetCurFileNum();
			if(nItem < nCurItem - 1)
				// 再生中のアイテムより前のアイテムを削除する場合
				m_rMainWnd.GetSound().SetCurFileNum(nCurItem - 1);
			else if(nItem == nCurItem - 1) {
				// 再生中のアイテムを削除する場合
				if(GetItemCount() > 0) {
					bStop = FALSE;
					bPlayNext = TRUE;
					m_rMainWnd.GetSound().SetCurFileNum(nItem);
				}
				else {
					bPlayNext = FALSE;
					bStop = TRUE;
				}
			}
		}
	}
	if(GetItemCount() <= 0) {
		bPlayNext = FALSE;
		bStop = TRUE;
	}
	ResetNumber();
	if(bCurTab) {
		if(bPlayNext) m_rMainWnd.PlayNext(FALSE, TRUE);
		else if(bStop) {
			m_rMainWnd.GetSound().StreamFree();
			m_rMainWnd.Stop();
		}
	}
}
//----------------------------------------------------------------------------
// アイテムを削除
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::Delete(int nItem)
{
	BOOL bPlayNext = FALSE;
	BOOL bStop = FALSE;
	BOOL bCurTab = (HWND)m_rMainWnd.GetCurPlayList() == m_hWnd;
	FixPlayOrder(nItem);
	DeleteItem(nItem);
	if(bCurTab) {
		int nCurItem = m_rMainWnd.GetSound().GetCurFileNum();
		if(nItem < nCurItem - 1) {
			// 再生中のアイテムより前のアイテムを削除する場合
			m_rMainWnd.GetSound().SetCurFileNum(nCurItem - 1);
		}
		else if(nItem == nCurItem - 1) {
			// 再生中のアイテムを削除する場合
			if(GetItemCount() > 0) {
				bStop = FALSE;
				bPlayNext = TRUE;
				m_rMainWnd.GetSound().SetCurFileNum(nItem);
			}
			else {
				bPlayNext = FALSE;
				bStop = TRUE;
			}
		}
	}
	if(GetItemCount() <= 0) {
		bPlayNext = FALSE;
		bStop = TRUE;
	}
	ResetNumber();
	if(bCurTab) {
		if(bPlayNext) m_rMainWnd.PlayNext(FALSE, TRUE);
		else if(bStop) {
			m_rMainWnd.GetSound().StreamFree();
			m_rMainWnd.Stop();
		}
	}
}
//----------------------------------------------------------------------------
// 全て削除
//----------------------------------------------------------------------------
BOOL CPlayListView_MainWnd::DeleteAllItems()
{
	orders.clear();
	return CListView::DeleteAllItems();
}
//----------------------------------------------------------------------------
// タグの編集終了
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::EndTagEdit()
{
	if(m_pAccel) {
		m_rApp.GetAccelTable().Create(m_pAccel, m_nAccel);
		delete [] m_pAccel; m_pAccel = NULL;
	}
	m_edit.Show(SW_HIDE);
}
//----------------------------------------------------------------------------
// 再生順の最大値を得る
//----------------------------------------------------------------------------
int CPlayListView_MainWnd::GetMaxPlayOrder() const
{
	int nMax = -1;
	for(int i = 0; i < (int)orders.size(); i++)
		if(orders[i] > nMax) nMax = orders[i];
	return nMax;
}
//----------------------------------------------------------------------------
// 選択中のアイテムを再生
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::PlaySelectedItem()
{
	int nItem = GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		m_rMainWnd.ChangeCurPlayTab();
		m_rMainWnd.Play(nItem);
	}
}
//----------------------------------------------------------------------------
// 再生中の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPlaying(int iItem)
{
	for(int i = 0; i < GetItemCount(); i++)
		SetItem(i, 0, _T(""), -1);
	if(m_hWnd == (HWND)m_rMainWnd.GetCurPlayList() && iItem >= 0)
		SetItem(iItem, 0, _T(""), 0);
}
//----------------------------------------------------------------------------
// 一時停止中の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPausing(int iItem)
{
	for(int i = 0; i < GetItemCount(); i++)
		SetItem(i, 0, _T(""), -1);
	if(m_hWnd == (HWND)m_rMainWnd.GetCurPlayList() && iItem >= 0)
		SetItem(iItem, 0, _T(""), 1);
}
//----------------------------------------------------------------------------
// 再生順の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPlayOrder(int iItem)
{
	if(iItem < 0) return;
	orders[iItem] = GetMaxPlayOrder() + 1;
}
//----------------------------------------------------------------------------
// 再生順の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPlayOrder(int iItem, int nOrder)
{
	orders[iItem] = nOrder;
}
//----------------------------------------------------------------------------
// 再生順をクリア
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ClearPlayOrder()
{
	for(int i = 0; i < (int)orders.size(); i++) orders[i] = -1;
}
//----------------------------------------------------------------------------
// 与えられた項目より大きな再生順を持つ項目の再生順をひとつ下げる
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::FixPlayOrder(int iItem)
{
	int nCur = orders[iItem];
	for(int i = 0; i < (int)orders.size(); i++) {
		int n = orders[i];
		if(n > nCur) orders[i] = n - 1;
	}
	orders[iItem] = -1;
}
//----------------------------------------------------------------------------
// 最も近いアイテムを得る
//----------------------------------------------------------------------------
int CPlayListView_MainWnd::GetClosestItem(int x, int y)
{
	int xPos = x, yPos = y - m_nHeaderHeight / 2;
	if(yPos < m_nHeaderHeight) yPos = m_nHeaderHeight;
	return HitTest(xPos, yPos);
}
//----------------------------------------------------------------------------
// 最小サイズを得る
//----------------------------------------------------------------------------
int CPlayListView_MainWnd::GetMinSize()
{
	int nHeight = m_nHeaderHeight + HIWORD(GetItemSpacing(TRUE)) * 3;
		// ３個分のアイテム
	return nHeight;
}
//----------------------------------------------------------------------------
// サイズの初期化
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::InitSize()
{
	int nHeight = m_nHeaderHeight + HIWORD(GetItemSpacing(TRUE)) * 5;
		// ５個分のアイテム
	SetSize(m_rMainWnd.GetClientWidth() - m_rMainWnd.GetControlOffset() * 2,
			nHeight);
}
//----------------------------------------------------------------------------
// フォルダを開く
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OpenFolder()
{
	int nItem = -1;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		TCHAR chPath[_MAX_PATH];
		GetItemText(nItem, 7, chPath, _MAX_PATH);
		PathRemoveFileSpec(chPath);
		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.lpFile = chPath;
		sei.nShow = SW_SHOW;
		sei.fMask = NULL;
		sei.lpVerb = _T("open");
		ShellExecuteEx(&sei);
	}
}
//----------------------------------------------------------------------------
// 「No.」のリセット
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ResetNumber()
{
	TCHAR text[13];
	for(int i = 0; i < GetItemCount(); i++) {
		_stprintf_s(text, _T("%d"), i + 1);
		SetItem(i, 1, text);
	}
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ResetPos()
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_TAB)) {
		int y = m_rMainWnd.GetTab().GetItemHeight()
			+ m_rMainWnd.GetControlOffset() * 2;
		SetPos(m_rMainWnd.GetControlOffset(), y);
	}
	else {
		POINT pt;
		pt.y = m_rMainWnd.GetEQ20KLabel().GetTop();
		ScreenToClient(m_rMainWnd, &pt);
		int nEQ20KLabelBottom = pt.y + m_rMainWnd.GetEQ20KLabel().GetHeight();
		pt.y = m_rMainWnd.GetEQ20KSlider().GetTop();
		ScreenToClient(m_rMainWnd, &pt);
		int nEQ20KSliderBottom = pt.y + m_rMainWnd.GetEQ20KSlider().GetHeight();
		int nBigger = nEQ20KLabelBottom > nEQ20KSliderBottom ? nEQ20KLabelBottom
			: nEQ20KSliderBottom;
		int nLeft = m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER) ?
			m_rMainWnd.GetExplorer().GetWidth() + 2 : 0;
		SetPos(nLeft, nBigger +
			m_rMainWnd.GetControlOffset());
	}
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ResetSize()
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_TAB)) {
		POINT pt;
		pt.y = GetTop();
		ScreenToClient(m_rMainWnd, &pt);
		int nHeight = m_rMainWnd.GetClientHeight() - pt.y
			- m_rMainWnd.GetControlOffset();
		SetSize(m_rMainWnd.GetClientWidth()
			- m_rMainWnd.GetExplorer().GetWidth() - 2
			- m_rMainWnd.GetControlOffset() * 2, nHeight);
	}
	else {
		POINT pt;
		pt.y = GetTop();
		ScreenToClient(m_rMainWnd, &pt);
		int nHeight = m_rMainWnd.GetClientHeight() - pt.y;
		SetSize(m_rMainWnd.GetClientWidth()
			- m_rMainWnd.GetExplorer().GetWidth() - 2, nHeight);
	}
}
//----------------------------------------------------------------------------
// 幅の再設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ResetWidth()
{
	int nWidth;
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_TAB))
		nWidth = m_rMainWnd.GetClientWidth()
			- m_rMainWnd.GetExplorer().GetWidth() - 2
			- m_rMainWnd.GetControlOffset() * 2;
	else
		nWidth = m_rMainWnd.GetClientWidth()
			- m_rMainWnd.GetExplorer().GetWidth();
	int nHeight = GetHeight();
	SetSize(nWidth, nHeight);
}
//----------------------------------------------------------------------------
// タグの設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SaveTag()
{
	TCHAR chValue[255];
	GetItemText(m_nItem, m_nSubItem, chValue, 255);

	TCHAR chPath[_MAX_PATH];
	GetItemText(m_nItem, 7, chPath, _MAX_PATH);

	BOOL bPlaying = FALSE; // 再生中のファイルのタグ更新かどうか
	BOOL bStopped = FALSE, bPausing = FALSE;
	QWORD qwPos;
	if((HWND)m_rMainWnd.GetCurPlayList() == m_hWnd &&
			m_rMainWnd.GetSound().GetCurFileName() == chPath) {
		bPlaying = TRUE;
		qwPos = m_rMainWnd.GetSound().ChannelGetPosition();
		bStopped = m_rMainWnd.GetSound().ChannelIsStopped();
		bPausing = m_rMainWnd.GetSound().ChannelIsPausing();
	}

	if(bPlaying) m_rMainWnd.GetSound().StreamFree();
	if(lpmp3infp_Load(NULL, chPath) == ERROR_SUCCESS) {
		DWORD dwType = lpmp3infp_GetType();
		switch(dwType)
		{
		case MP3INFP_FILE_MP3:
			{
				DWORD dwTagType = lpmp3infp_mp3_GetTagType();
				if(dwTagType & MP3INFP_HAS_MP3_APEV1 ||
						dwTagType & MP3INFP_HAS_MP3_APEV2) {
					if(m_nSubItem == 2)
						lpmp3infp_SetValue(_T("INAM_APE"), chValue);
					else if(m_nSubItem == 3)
						lpmp3infp_SetValue(_T("IART_APE"), chValue);
					else if(m_nSubItem == 4)
						lpmp3infp_SetValue(_T("ICRD_APE"), chValue);
					lpmp3infp_Save(chPath);
				}
				else if(dwTagType & MP3INFP_HAS_MP3_RIFFSIF) {
					if(m_nSubItem == 2)
						lpmp3infp_SetValue(_T("INAM_rmp"), chValue);
					else if(m_nSubItem == 3)
						lpmp3infp_SetValue(_T("IART_rmp"), chValue);
					else if(m_nSubItem == 4)
						lpmp3infp_SetValue(_T("ICRD_rmp"), chValue);
					lpmp3infp_Save(chPath);
				}
				else if(dwTagType & MP3INFP_HAS_MP3_ID3V2 ||
						dwTagType & MP3INFP_HAS_MP3_ID3V2_2 ||
						dwTagType & MP3INFP_HAS_MP3_ID3V2_3 ||
						dwTagType & MP3INFP_HAS_MP3_ID3V2_4) {
					if(m_nSubItem == 2)
						lpmp3infp_SetValue(_T("INAM_v2"), chValue);
					else if(m_nSubItem == 3)
						lpmp3infp_SetValue(_T("IART_v2"), chValue);
					else if(m_nSubItem == 4)
						lpmp3infp_SetValue(_T("ICRD_v2"), chValue);
					lpmp3infp_Save(chPath);
				}
				else if(dwTagType & MP3INFP_HAS_MP3_ID3V1 || 
						dwTagType & MP3INFP_HAS_MP3_ID3V1_0 ||
						dwTagType & MP3INFP_HAS_MP3_ID3V1_1) {
					if(m_nSubItem == 2)
						lpmp3infp_SetValue(_T("INAM_v1"), chValue);
					else if(m_nSubItem == 3)
						lpmp3infp_SetValue(_T("IART_v1"), chValue);
					else if(m_nSubItem == 4)
						lpmp3infp_SetValue(_T("ICRD_v1"), chValue);
					lpmp3infp_Save(chPath);
				}
				else {
					if(m_nSubItem == 2)
						lpmp3infp_SetValue(_T("INAM_v2"), chValue);
					else if(m_nSubItem == 3)
						lpmp3infp_SetValue(_T("IART_v2"), chValue);
					else if(m_nSubItem == 4)
						lpmp3infp_SetValue(_T("ICRD_v2"), chValue);
					lpmp3infp_mp3_MakeId3v2(chPath);
				}
			}
			break;
		case MP3INFP_FILE_WAV:
		case MP3INFP_FILE_AVI:
		case MP3INFP_FILE_VQF:
		case MP3INFP_FILE_WMA:
		case MP3INFP_FILE_OGG:
		case MP3INFP_FILE_APE:
		case MP3INFP_FILE_MP4:
			if(m_nSubItem == 2)
				lpmp3infp_SetValue(_T("INAM"), chValue);
			else if(m_nSubItem == 3)
				lpmp3infp_SetValue(_T("IART"), chValue);
			else if(m_nSubItem == 4)
				lpmp3infp_SetValue(_T("ICRD"), chValue);
			lpmp3infp_Save(chPath);
			break;
		}
	}
	if(bPlaying) {
		m_rMainWnd.GetSound().StreamCreateFile(chPath);
		m_rMainWnd.GetSound().ClearMarker();
		m_rMainWnd.SetAllEffects();
		m_rMainWnd.GetSound().ChannelSetPosition(qwPos);
		if(!bStopped && !bPausing) m_rMainWnd.GetSound().ChannelPlay();
	}
}
//----------------------------------------------------------------------------
// 指定された項目までスクロール
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ScrollToItem(int nItem)
{
	EnsureVisible(nItem, TRUE);
}
//----------------------------------------------------------------------------
// 選択中のアイテムのプロパティを表示
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ShowProperties()
{
	int nItem = -1;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		TCHAR chPath[_MAX_PATH];
		GetItemText(nItem, 7, chPath, _MAX_PATH);
		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.lpFile = chPath;
		sei.nShow = SW_SHOW;
		sei.fMask = SEE_MASK_INVOKEIDLIST;
		sei.lpVerb = _T("properties");
		ShellExecuteEx(&sei);
	}
}
//----------------------------------------------------------------------------
// ソート
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::Sort(NMLISTVIEW* pnmlv)
{
	if(pnmlv->iSubItem == 0 || pnmlv->iSubItem == 1) return;
	SORTDATA sortData;
	sortData.hwndList = m_hWnd;
	sortData.isortSubItem = pnmlv->iSubItem;
	if(lastSort == pnmlv->iSubItem && isLastSortUp) {
		// 降順
		sortData.iUPDOWN = 2;
		isLastSortUp = FALSE;
	}
	else {
		// 昇順
		sortData.iUPDOWN = 1;
		isLastSortUp = TRUE;
	}
	lastSort = pnmlv->iSubItem;
	ListView_SortItemsEx(m_hWnd, CPlayListView_MainWnd::SortProc, &sortData);
	ResetNumber();
}
//----------------------------------------------------------------------------
// タグの編集開始
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::StartTagEdit()
{
	if(m_nItem < 0 || m_nSubItem <= 1 || 5 <= m_nSubItem) return;

	RECT rect;
	ListView_GetSubItemRect(m_hWnd, m_nItem, m_nSubItem, LVIR_LABEL, &rect);

	TCHAR chBuf[_MAX_PATH];
	GetItemText(m_nItem, m_nSubItem, chBuf, _MAX_PATH);
	m_edit.SetText(chBuf);
	m_strTag = chBuf;

	// ショートカットキーを一時停止しておく
	if(m_pAccel) delete [] m_pAccel;
	m_nAccel = m_rApp.GetAccelTable().GetNum();
	m_pAccel = new ACCEL[m_nAccel+1];
	m_rApp.GetAccelTable().Copy(m_pAccel, m_nAccel);
	m_rApp.GetAccelTable().Destroy();

	m_edit.SetPos(rect.left, rect.top);
	m_edit.SetSize(rect.right - rect.left, rect.bottom - rect.top);
	m_edit.Show(SW_SHOW);
	SetFocus(m_edit);
	PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
	PostMessage(m_edit, EM_SETSEL, 0, -1);

	for(int i = 0; i < GetItemCount(); i++)
		SetItemState(i, 0, LVIS_FOCUSED | LVIS_SELECTED);
	SetItemState(m_nItem, LVIS_FOCUSED | LVIS_SELECTED,
		LVIS_FOCUSED | LVIS_SELECTED);
	return;
}
//----------------------------------------------------------------------------
// アイテムの情報をアップデート
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::UpdateItemInfo(int nItem)
{
	// パスを得る
	TCHAR chPath[_MAX_PATH];
	GetItemText(nItem, 7, chPath, _MAX_PATH);

	// ファイル名を取得
	TCHAR chFileName[_MAX_FNAME + _MAX_EXT];
	TCHAR chFileExt[_MAX_EXT];
	_tsplitpath_s(chPath, NULL, 0, NULL, 0, chFileName, _MAX_FNAME, chFileExt,
				  _MAX_EXT);

	// ファイル名
	lstrcat(chFileName, chFileExt);
	SetItem(nItem, 6, chFileName);

	if(PathIsURL(chPath)) return;

	if(_tcsicmp(chFileExt, _T(".nsf")) == 0)
		return;

	if(lpmp3infp_Load(NULL, chPath) != ERROR_SUCCESS) return;
	DWORD dwType = lpmp3infp_GetType();
	TCHAR* pTitle = NULL;
	TCHAR* pArtist = NULL;
	TCHAR* pYear = NULL;
	TCHAR* pTime = NULL;
	switch(dwType)
	{
	case MP3INFP_FILE_MP3:
		{
			DWORD dwTagType = lpmp3infp_mp3_GetTagType();
			TCHAR chTitleKey[255], chArtistKey[255], chYearKey[255];
			if(dwTagType & MP3INFP_HAS_MP3_APEV1 ||
					dwTagType & MP3INFP_HAS_MP3_APEV2) {
				lstrcpy(chTitleKey, _T("INAM_APE"));
				lstrcpy(chArtistKey, _T("IART_APE"));
				lstrcpy(chYearKey, _T("ICRD_APE"));
			}
			else if(dwTagType & MP3INFP_HAS_MP3_RIFFSIF) {
				lstrcpy(chTitleKey, _T("INAM_rmp"));
				lstrcpy(chArtistKey, _T("IART_rmp"));
				lstrcpy(chYearKey, _T("ICRD_rmp"));
			}
			else if(dwTagType & MP3INFP_HAS_MP3_ID3V2 ||
					dwTagType & MP3INFP_HAS_MP3_ID3V2_2 ||
					dwTagType & MP3INFP_HAS_MP3_ID3V2_3 ||
					dwTagType & MP3INFP_HAS_MP3_ID3V2_4) {
				lstrcpy(chTitleKey, _T("INAM_v2"));
				lstrcpy(chArtistKey, _T("IART_v2"));
				lstrcpy(chYearKey, _T("ICRD_v2"));
			}
			else if(dwTagType & MP3INFP_HAS_MP3_ID3V1 || 
					dwTagType & MP3INFP_HAS_MP3_ID3V1_0 ||
					dwTagType & MP3INFP_HAS_MP3_ID3V1_1) {
				lstrcpy(chTitleKey, _T("INAM_v1"));
				lstrcpy(chArtistKey, _T("IART_v1"));
				lstrcpy(chYearKey, _T("ICRD_v1"));
			}
			lpmp3infp_GetValue(chTitleKey, &pTitle);
			SetItem(nItem, 2, lstrcmp(pTitle, _T("")) != 0 ?
				pTitle : chFileName);

			lpmp3infp_GetValue(chArtistKey, &pArtist);
			SetItem(nItem, 3, pArtist);

			lpmp3infp_GetValue(chYearKey, &pYear);
			SetItem(nItem, 4, pYear);

			lpmp3infp_GetValue(_T("TIME"), &pTime);
			SetItem(nItem, 5, pTime);
		break;
		}
	case MP3INFP_FILE_WAV:
	case MP3INFP_FILE_AVI:
	case MP3INFP_FILE_VQF:
	case MP3INFP_FILE_WMA:
	case MP3INFP_FILE_OGG:
	case MP3INFP_FILE_APE:
	case MP3INFP_FILE_MP4:
		lpmp3infp_GetValue(_T("INAM"), &pTitle);
		SetItem(nItem, 2, lstrcmp(pTitle, _T("")) != 0 ?
			pTitle : chFileName);

		lpmp3infp_GetValue(_T("IART"), &pArtist);
		SetItem(nItem, 3, pArtist);

		lpmp3infp_GetValue(_T("ICRD"), &pYear);
		SetItem(nItem, 4, pYear);

		lpmp3infp_GetValue(_T("TIME"), &pTime);
		SetItem(nItem, 5, pTime);
		break;
	default:
		// タイトル
		m_rMainWnd.GetSound().StartReadTag(chPath);
		LPCSTR t = (LPCSTR)m_rMainWnd.GetSound().ReadTitleTag();
		TCHAR chTitle[255];
#ifdef UNICODE
		int cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, NULL, 0);
		wchar_t *wszTmp = new wchar_t[cchWC];
		memset(wszTmp, 0, cchWC * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, wszTmp, cchWC);
		_tcscpy_s(chTitle, cchWC + 1, wszTmp);
		delete[] wszTmp;
#else
		chTitle = t;
#endif
		SetItem(nItem, 2, lstrcmp(chTitle, _T("")) != 0 ? chTitle : chFileName);

		// アーティスト
		t = (LPCSTR)m_rMainWnd.GetSound().ReadArtistTag();
		TCHAR chArtist[255];
#ifdef UNICODE
		cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, NULL, 0);
		wszTmp = new wchar_t[cchWC];
		memset(wszTmp, 0, cchWC * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, wszTmp, cchWC);
		_tcscpy_s(chArtist, cchWC + 1, wszTmp);
		delete[] wszTmp;
#else
		chArtist = t;
#endif
		SetItem(nItem, 3, chArtist);

		// 年
		t = (LPCSTR)m_rMainWnd.GetSound().ReadYearTag();
		TCHAR chYear[255];
#ifdef UNICODE
		cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, NULL, 0);
		wszTmp = new wchar_t[cchWC];
		memset(wszTmp, 0, cchWC * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, wszTmp, cchWC);
		_tcscpy_s(chYear, cchWC + 1, wszTmp);
		delete[] wszTmp;
#else
		chYear = t;
#endif
		SetItem(nItem, 4, chYear);

		// 長さ
		double time = m_rMainWnd.GetSound().ReadTime();

		int hour = (int)(time / 3600) % 60;
		int second = (int)(time / 60) % 60;
		int minute = (int)time % 60;

		TCHAR chTime[255] = _T("");
		if(time >= 0.0) {
			if(hour > 0)
				_stprintf_s(chTime, _T("%02d:%02d:%02d"), hour, second, minute);
			else _stprintf_s(chTime, _T("%02d:%02d"), second, minute);
		}
		m_rMainWnd.GetSound().EndReadTag();

		SetItem(nItem, 5, chTime);
		break;
	}
}
//----------------------------------------------------------------------------
// ソート用コールバック関数
//----------------------------------------------------------------------------
int CALLBACK CPlayListView_MainWnd::SortProc(LPARAM lp1, LPARAM lp2, LPARAM lp3)
{
	TCHAR szItemText1[_MAX_PATH];
	TCHAR szItemText2[_MAX_PATH];

	SORTDATA* sortData = (SORTDATA *)lp3;
	HWND hCtlLView = (HWND)sortData->hwndList;

	ListView_GetItemText(hCtlLView, lp1, sortData->isortSubItem, szItemText1,
		sizeof(szItemText1));
	ListView_GetItemText(hCtlLView, lp2, sortData->isortSubItem, szItemText2, 
		sizeof(szItemText2));

	return lstrcmpi(szItemText1, szItemText2) * (sortData->iUPDOWN == 2 ? -1 : 1);
}
//----------------------------------------------------------------------------
// ドラッグが開始された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnBeginDrag(NM_LISTVIEW *pnmlv)
{
	SetCursor(LoadCursor(GetModuleHandle(NULL), (LPCTSTR)IDC_DRAG_MOVE));
	SetCapture(m_hWnd);
}
//----------------------------------------------------------------------------
// ラベルの編集が開始された
//----------------------------------------------------------------------------
LRESULT CPlayListView_MainWnd::OnBeginLabelEdit(NM_LISTVIEW *pnmlv)
{
	LVHITTESTINFO lvhit;
	GetCursorPos(&lvhit.pt);

	ScreenToClient(m_hWnd, &lvhit.pt);
	ListView_SubItemHitTest(m_hWnd, &lvhit);
	m_nItem = lvhit.iItem;
	m_nSubItem = lvhit.iSubItem;
	StartTagEdit();
	return TRUE;
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == (HWND)m_edit) {
		if(codeNotify == EN_KILLFOCUS) {
			SetItem(m_nItem, m_nSubItem, m_edit.GetText().c_str());
			SaveTag();
			EndTagEdit();
		}
	}
	else if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CListView::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// カスタムドローのタイミングが来た
//----------------------------------------------------------------------------
LRESULT CPlayListView_MainWnd::OnCustomDraw(NMLVCUSTOMDRAW *pnmlvcd)
{
	if(pnmlvcd->nmcd.dwDrawStage == CDDS_PREPAINT) return CDRF_NOTIFYITEMDRAW;
	if(pnmlvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
		if(m_hWnd == (HWND)m_rMainWnd.GetCurPlayList() && 
		   pnmlvcd->nmcd.dwItemSpec == m_rMainWnd.GetSound().GetCurFileNum()-1)
		{
			// ウィンドウの背景色
			DWORD dwWndColor = GetSysColor(COLOR_3DFACE);
			BYTE byWndRed = GetRValue(dwWndColor);
			BYTE byWndGreen = GetGValue(dwWndColor);
			BYTE byWndBlue = GetBValue(dwWndColor);

			if(dwWndColor == 0 || dwWndColor == 0xffffff) {
				// ウィンドウの背景色が黒か白の場合

				int n = 96; // 色の変更量

				// 背景色
				DWORD dwBackColor = GetSysColor(COLOR_HIGHLIGHT);
				BYTE byBackRed = GetRValue(dwBackColor);
				if(byBackRed <= 255 - n) byBackRed += n;
				else byBackRed = 255;
				BYTE byBackGreen = GetGValue(dwBackColor);
				if(byBackGreen <= 255 - n) byBackGreen += n;
				else byBackGreen = 255;
				BYTE byBackBlue = GetBValue(dwBackColor);
				if(byBackBlue <= 255 - n) byBackBlue += n;
				else byBackBlue = 255;
				pnmlvcd->clrTextBk = RGB(byBackRed, byBackGreen, byBackBlue);

				// テキストの色
				DWORD dwTextColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
				BYTE byTextRed = GetRValue(dwTextColor);
				BYTE byTextGreen = GetGValue(dwTextColor);
				BYTE byTextBlue = GetBValue(dwTextColor);
				if((byTextRed + byTextGreen + byTextBlue) / 3 < 128) {
					byTextRed -= byTextRed >= n ? n : byTextRed;
					byTextGreen -= byTextGreen >= n ? n : byTextGreen;
					byTextBlue -= byTextBlue >= n ? n : byTextBlue;
					pnmlvcd->clrText = RGB(byTextRed, byTextGreen, byTextBlue);
				}
				else {
					byTextRed = byTextRed <= 255 - n ? byTextRed + n : 255;
					byTextGreen = byTextGreen <= 255 - n ? byTextGreen + n
								  : 255;
					byTextBlue = byTextBlue <= 255 - n ? byTextBlue + n : 255;
					pnmlvcd->clrText = RGB(byTextRed, byTextGreen, byTextBlue);
				}
			}
			else {
				int n = 64; // 色をいくつ変更するか

				byWndRed -= byWndRed >= n ? n : byWndRed;
				byWndGreen -= byWndGreen >= n ? n : byWndGreen;
				byWndBlue -= byWndBlue >= n ? n : byWndBlue;
				pnmlvcd->clrTextBk = RGB(byWndRed, byWndGreen, byWndBlue);

				DWORD dwTextColor = GetSysColor(COLOR_WINDOWTEXT);
				BYTE byTextRed = GetRValue(dwTextColor);
				BYTE byTextGreen GetGValue(dwTextColor);
				BYTE byTextBlue = GetBValue(dwTextColor);
				if((byWndRed + byWndGreen + byWndBlue) / 3 <= 192 &&
					(byTextRed + byTextGreen + byTextBlue) / 3 <= 192) {
					byTextRed = 255 - byTextRed;
					byTextGreen = 255 - byTextGreen;
					byTextBlue = 255 - byTextBlue;
				}
				else if((byTextRed + byTextGreen + byTextBlue) / 3 > 192) {
					byTextRed = 255 - byTextRed;
					byTextGreen = 255 - byTextGreen;
					byTextBlue = 255 - byTextBlue;
				}
				pnmlvcd->clrText = RGB(byTextRed, byTextGreen, byTextBlue);
			}
			return CDRF_NEWFONT;
		}
		else if(pnmlvcd->nmcd.dwItemSpec % 2 == 1) {
			DWORD dwColor = GetSysColor(COLOR_WINDOW);
			if(dwColor == 0xFFFFFF) {
				int n = 4;
				BYTE byBackRed = GetRValue(dwColor) - n;
				BYTE byBackGreen = GetGValue(dwColor) - n;
				BYTE byBackBlue = GetBValue(dwColor) - n;
				pnmlvcd->clrTextBk = RGB(byBackRed, byBackGreen, byBackBlue);
				return CDRF_NEWFONT;
			}
		}
	}
	return 0;
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CPlayListView_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	POINT pt;
	pt.x = xPos;
	pt.y = yPos;
	LV_HITTESTINFO lvhtst;
	lvhtst.pt = pt;
	ScreenToClient(m_hWnd, &lvhtst.pt);
	ListView_HitTest(m_hWnd, &lvhtst);
	if(lvhtst.flags & LVHT_ONITEM && lvhtst.pt.y > m_nHeaderHeight)
		m_rClickMenu.Create(TRUE);
	else m_rClickMenu.Create(FALSE);
	SetForegroundWindow(m_hWnd);
	TrackPopupMenu((HMENU)m_rClickMenu,
					TPM_LEFTALIGN | TPM_TOPALIGN, xPos, yPos, 0,
					m_hWnd, NULL);
	return CListView::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
// ファイルがドロップされた
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnDropFiles(HDROP hdrop)
{
	m_rMainWnd.AddDropFiles(hdrop, FALSE);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_RETURN && cRepeat == 1) PlaySelectedItem();
	else if(vk == VK_DELETE) DeleteSelectedItems();
	CListView::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// ダブルクリックされた
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnLButtonDoubleClick(int x, int y, UINT keyFlags)
{
	int n = GetNextItem(-1, LVNI_SELECTED);
	if(n >= 0) {
		m_rMainWnd.ChangeCurPlayTab();
		m_rMainWnd.Play(n);
	}
	CListView::OnLButtonDoubleClick(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// マウスが動かされた
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnMouseMove(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		if(y < m_nHeaderHeight * 2) Scroll(0, -m_nHeaderHeight);
		else if(y > GetClientHeight() - m_nHeaderHeight * 2)
			Scroll(0, m_nHeaderHeight);

		int iItem = GetClosestItem(x, y);
		if(iItem == -1) return;
		int width = GetColumnWidth(0) + GetColumnWidth(1) + GetColumnWidth(2) +
					GetColumnWidth(3) + GetColumnWidth(4) + GetColumnWidth(5) +
					GetColumnWidth(6) + GetColumnWidth(7);
		RECT rc;
		if(y < m_nHeaderHeight * 1.5) {
			iItem = -1;
			ListView_GetItemRect(m_hWnd, 0, &rc, LVIR_BOUNDS);
			rc.bottom = rc.top;
		}
		else ListView_GetItemRect(m_hWnd, iItem, &rc, LVIR_BOUNDS);

		if(iItem != m_nLastItem) {
			RECT rc;
			if(m_nLastItem == -1) {
				ListView_GetItemRect(m_hWnd, 0, &rc, LVIR_BOUNDS);
				rc.top -= 2;
				rc.bottom = rc.top + 3;
			}
			else {
				ListView_GetItemRect(m_hWnd, m_nLastItem, &rc, LVIR_BOUNDS);
				rc.top = rc.bottom - 2;
				rc.bottom += 1;
			}
			rc.left = 0;
			rc.right = width + 2;
			InvalidateRect(&rc, TRUE);
		}
		m_nLastItem = iItem;

		CClientDC dc(m_hWnd);
		HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(dc, hPen);
		MoveToEx(dc, 0, rc.bottom - 1, NULL);
		LineTo(dc, width, rc.bottom - 1);
		SelectObject(dc, hOldPen);
		DeleteObject(hPen);
	}
}
//----------------------------------------------------------------------------
// 左クリックが離された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnLButtonUp(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		ReleaseCapture();
		int nDstItem = GetClosestItem(x, y);
		if(y < m_nHeaderHeight * 1.5) nDstItem = 0;
		else if(nDstItem == -1) {
			if(y > m_nHeaderHeight) nDstItem = GetItemCount();
			else {
				InvalidateRect(NULL, TRUE);
				return;
			}
		}
		else nDstItem++;
		int nSrcItem = -1;
		while((nSrcItem = GetNextItem(-1, LVNI_SELECTED)) >= 0) {
			if(nSrcItem == nDstItem) break;
			int nCurItem = m_rMainWnd.GetSound().GetCurFileNum() - 1;
			TCHAR chPath[_MAX_PATH], chTitle[255], chArtist[255], chYear[255],
				  chLength[255];
			GetItemText(nSrcItem, 7, chPath, _MAX_PATH);
			GetItemText(nSrcItem, 2, chTitle, 255);
			GetItemText(nSrcItem, 3, chArtist, 255);
			GetItemText(nSrcItem, 4, chYear, 255);
			GetItemText(nSrcItem, 5, chLength, 255);
			AddFile(chPath, nDstItem, chTitle, chArtist, chYear, chLength);
			if(nSrcItem == nCurItem) {
				nCurItem = nSrcItem < nDstItem ? nDstItem - 1 : nDstItem;
				if(!m_rMainWnd.GetSound().ChannelIsStopped()) {
					if(m_rMainWnd.GetSound().ChannelIsPausing())
						SetItem(nDstItem, 0, _T(""), 1);
					else SetItem(nDstItem, 0, _T(""), 0);
				}
			}
			else if(nSrcItem > nCurItem && nDstItem <= nCurItem)
				nCurItem++;
			else if(nSrcItem < nCurItem && nDstItem > nCurItem)
				nCurItem--;
			DeleteItem(nSrcItem > nDstItem ? nSrcItem + 1 : nSrcItem);
			m_rMainWnd.GetSound().SetCurFileNum(nCurItem + 1);
			if(nSrcItem > nDstItem && nDstItem < GetItemCount())
				nDstItem++;
		}
		ResetNumber();
		InvalidateRect(NULL, TRUE);
	}
}
//----------------------------------------------------------------------------
// コモンコントロールからの通知が来た
//----------------------------------------------------------------------------
LRESULT CPlayListView_MainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	// ヘッダの幅を変更できないようにする
	// UNICODE環境じゃなくてもHDN_*Wが飛んでくる場合があるようなので、
	// HDN_*A, HDN_*W 両方とも禁止
	HD_NOTIFY * phdn = (HD_NOTIFY *)pnmhdr;
	switch(phdn->hdr.code)
	{
	case HDN_BEGINTRACKA:
	case HDN_BEGINTRACKW:
	case HDN_DIVIDERDBLCLICKA:
	case HDN_DIVIDERDBLCLICKW:
		if(phdn->iItem == 0) return TRUE;
		break;
	}
	return CListView::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnEscKeyPressed()
{
	EndTagEdit();
	SetItem(m_nItem, m_nSubItem, m_strTag.c_str());
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnReturnKeyPressed()
{
	SetItem(m_nItem, m_nSubItem, m_edit.GetText().c_str());
	SaveTag();
	if(++m_nItem < GetItemCount()) {
		ScrollToItem(m_nItem);
		StartTagEdit();
	}
	else EndTagEdit();
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnUpKeyPressed()
{
	SetItem(m_nItem, m_nSubItem, m_edit.GetText().c_str());
	SaveTag();
	if(--m_nItem >= 0) {
		ScrollToItem(m_nItem);
		StartTagEdit();
	}
	else EndTagEdit();
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnDownKeyPressed()
{
	OnReturnKeyPressed();
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnLeftKeyPressed()
{
	DWORD dwPos = SendMessage(m_edit, EM_GETSEL, NULL, NULL);
	WORD wStart = LOWORD(dwPos);
	WORD wEnd = HIWORD(dwPos);
	if(wStart != wEnd) return;
	if(wStart != 0) return;
	SetItem(m_nItem, m_nSubItem, m_edit.GetText().c_str());
	EndTagEdit();
	m_nSubItem--;
	StartTagEdit();
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnRightKeyPressed()
{
	DWORD dwPos = SendMessage(m_edit, EM_GETSEL, NULL, NULL);
	WORD wStart = LOWORD(dwPos);
	WORD wEnd = HIWORD(dwPos);
	if(wStart != wEnd) return;
	if(wStart != m_edit.GetText().length()) return;
	SetItem(m_nItem, m_nSubItem, m_edit.GetText().c_str());
	EndTagEdit();
	m_nSubItem++;
	StartTagEdit();
}
//----------------------------------------------------------------------------
// すべての項目を選択
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SelectAll()
{
	if(GetItemCount() == 0) return;

	for(int i = 0; i < GetItemCount(); i++)
		SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
	SetFocus(m_hWnd);
}
//----------------------------------------------------------------------------
