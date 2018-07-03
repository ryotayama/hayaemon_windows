//----------------------------------------------------------------------------
// PitchAnalyser.cpp : ピッチアナライザ機能の管理
//----------------------------------------------------------------------------
#include <windows.h>
#include <shlwapi.h>
#include "../App.h"
#include "../Common/ClientDC.h"
#include "MainWnd.h"
#include "PitchAnalyser.h"
#include "Sound.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CPitchAnalyser::CPitchAnalyser(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_nLeft(-1)
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
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CPitchAnalyser::~CPitchAnalyser()
{
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hFont);
}
//----------------------------------------------------------------------------
// 画面をクリア
//----------------------------------------------------------------------------
void CPitchAnalyser::ClearScreen()
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
// ピッチアナライザの表示
//----------------------------------------------------------------------------
void CPitchAnalyser::Update(double dCurrentTime)
{
	if(!m_rMainWnd.IsPitchAnalyserThreadAlive()) return;

	BOOL bFullScreen = m_rMainWnd.IsFullScreen();
	CWnd* pWnd;
	if(bFullScreen) pWnd = (CWnd*)&m_rMainWnd.GetVideoScreenWnd();
	else pWnd = (CWnd*)&m_rMainWnd.GetVideoScreen();
	HWND hWnd = *pWnd;

	int nLeft = 41 + (int)(m_rMainWnd.GetSound().ChannelGetSecondsPosition()
		* 100.0) % (pWnd->GetWidth() - 41);
	if(nLeft == m_nLeft) return;
	m_nLeft = nLeft;

	HBRUSH hBackBrush	= (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush	= (HBRUSH)SelectObject(hMemDC, hBackBrush);
	SelectObject(hMemDC, hOldBrush);
	DeleteObject(hBackBrush);

	HPEN	hGreyPen	= (HPEN)CreatePen(PS_SOLID, 1, RGB(80, 80, 80));
	HPEN	hBlackPen	= (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH	hWhiteBrush	= (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH	hGreyBrush	= (HBRUSH)CreateSolidBrush(RGB(80, 80, 80));
	HPEN	hOldPen	= (HPEN)SelectObject(hMemDC, hBlackPen);
	hOldBrush		= (HBRUSH)SelectObject(hMemDC, hWhiteBrush);

	int nWidth = pWnd->GetWidth();
	int nHeight = pWnd->GetHeight();
	double nSpace = (nHeight - 1) / 49.0;
	double nKokkenSpace = nSpace * 2 / 3;
	double nHakkenSpace = nSpace + 2;
	double nLineSpace = (nHeight - 1) / 84.0;
	BOOL arKokken[84] = {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
		0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
		0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
		0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0};
	int j = 0;
	for(int i = 0; i < 84; i++) {
		if(i > 0 && arKokken[i - 1]) {
			SelectObject(hMemDC, hBlackPen);
			SelectObject(hMemDC, hGreyBrush);
			int nTop = (int)((j - 2) * nSpace + (nHakkenSpace * 2 / 3));
			Rectangle(hMemDC, 0, nTop, 20, (int)(nTop + nKokkenSpace));
		}
		else {
			SelectObject(hMemDC, hGreyPen);
			SelectObject(hMemDC, hWhiteBrush);
			int nTop = (int)(j * nSpace + 1);
			Rectangle(hMemDC, 0, nTop, 40, (int)(nTop + nHakkenSpace));
			j++;
		}

		SelectObject(hMemDC, hGreyPen);
		int nTop = (int)(i * nLineSpace + 0.5);
		MoveToEx(hMemDC, 40, nTop, NULL);
		LineTo(hMemDC, pWnd->GetWidth(), nTop);
	}

	float buf[8192];
	m_rMainWnd.GetSound().ChannelGetData(buf, BASS_DATA_FFT16384);
	double dOnkai[84];
	dOnkai[21] = 110.0;
	for(int i = 22; i < 84; i++)
		dOnkai[i] = dOnkai[i-1] * 1.05946309436;
	for(int i = 20; i >= 0; i--)
		dOnkai[i] = dOnkai[i+1] / 1.05946309436;
	int nIndex[84];
	int i = 0;
	for(int j = 0; j < 8192; j++) {
		if((dOnkai[i] >= ((44100.0 / 2.0 / 8192.0) * ((double)j - 0.5))) &&
				dOnkai[i] < (44100.0 / 2.0 / 8192.0) * ((double)(j + 1) - 0.5)) 
		{
			nIndex[i] = j;
			i++; j--;
			if(i >= 84) break;
		}
	}
	j = 0;
	for(int i = 83; i >= 0; i--) {
		int nColor = (int)(buf[nIndex[i]] * 7000);
		HPEN	hPen;
		HBRUSH	hBrush;
		if(nColor > 1275) nColor = 1275;
		if(nColor >= 1020) {
			hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 1275 - nColor, 0));
			hBrush	= (HBRUSH)CreateSolidBrush(RGB(255, 1275 - nColor, 0));
		}
		else if(nColor >= 765) {
			hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(nColor - 510, 255, 0));
			hBrush	= (HBRUSH)CreateSolidBrush(RGB(nColor - 510, 255, 0));
		}
		else if(nColor >= 510) {
			hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 765 - nColor));
			hBrush	= (HBRUSH)CreateSolidBrush(RGB(0, 255, 765 - nColor));
		}
		else if(nColor >= 255) {
			hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, nColor - 255, 255));
			hBrush	= (HBRUSH)CreateSolidBrush(RGB(0, nColor - 255, 255));
		}
		else {
			hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, nColor));
			hBrush	= (HBRUSH)CreateSolidBrush(RGB(0, 0, nColor));
		}
		SelectObject(hMemDC, hPen);
		SelectObject(hMemDC, hBrush);
		int nTop = (int)((83 - i) * nLineSpace + 1.5);
		Rectangle(hMemDC, nLeft, nTop, nLeft + 2, (int)(nTop + nLineSpace));
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}

	CClientDC dc(hWnd);
	BitBlt(dc, 0, 0, pWnd->GetWidth(), pWnd->GetHeight(), hMemDC, 0, 0,
		SRCCOPY);

	for(int i = 0; i < 84; i++) {
		SelectObject(hMemDC, hBlackPen);
		int nTop = (int)(i * nLineSpace + 0.5);
		MoveToEx(hMemDC, 40, nTop, NULL);
		LineTo(hMemDC, pWnd->GetWidth(), nTop);
	}

	SelectObject(hMemDC, hOldPen);
	SelectObject(hMemDC, hOldBrush);
	DeleteObject(hGreyPen);
	DeleteObject(hBlackPen);
	DeleteObject(hGreyBrush);
	DeleteObject(hWhiteBrush);
	DeleteObject(hFont);
}
//----------------------------------------------------------------------------
