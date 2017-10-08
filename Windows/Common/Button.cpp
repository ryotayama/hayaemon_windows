//--------------------------------------------------------------------------
// Button.cpp : ボタンの作成・管理を行う
//--------------------------------------------------------------------------
#include <windows.h>
#include "Button.h"
//--------------------------------------------------------------------------
// 作成
//--------------------------------------------------------------------------
BOOL CButton::Create(LPCTSTR lpWindowName, int x, int y, int cx, int cy, HWND hwnd, UINT id, BOOL bDef)
{
	Destroy();
	UINT style = WS_CHILD | WS_VISIBLE;
	if(bDef) style |= BS_DEFPUSHBUTTON;
	m_hWnd = CreateWindow(_T("BUTTON"), lpWindowName, style, x, y, cx, cy, hwnd, (HMENU)id, GetModuleHandle(NULL), NULL);
	if(!m_hWnd) return FALSE;

	// 画面のプロパティで設定されているメッセージボックスと同じシステムフォントに設定
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
// 作成
//--------------------------------------------------------------------------
BOOL CButton::Create(LPCTSTR lpWindowName, HWND hwnd, UINT id, BOOL bDef)
{
	Destroy();
	UINT style = WS_CHILD | WS_VISIBLE;
	if(bDef) style |= BS_DEFPUSHBUTTON;
	m_hWnd = CreateWindow(_T("BUTTON"), lpWindowName, style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)id, GetModuleHandle(NULL), NULL);
	if(!m_hWnd) return FALSE;

	// 画面のプロパティで設定されているメッセージボックスと同じシステムフォントに設定
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
// 左位置を得る
//--------------------------------------------------------------------------
int CButton::GetLeft() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetLeft();
	pt.y = CWnd::GetTop();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.x;
}
//--------------------------------------------------------------------------
// 上位置を得る
//--------------------------------------------------------------------------
int CButton::GetTop() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetLeft();
	pt.y = CWnd::GetTop();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.y;
}
//--------------------------------------------------------------------------
// 右位置を得る
//--------------------------------------------------------------------------
int CButton::GetRight() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetRight();
	pt.y = CWnd::GetBottom();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.x;
}
//--------------------------------------------------------------------------
// 下位置を得る
//--------------------------------------------------------------------------
int CButton::GetBottom() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetRight();
	pt.y = CWnd::GetBottom();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.y;
}
//--------------------------------------------------------------------------
// テキストの高さを得る
//--------------------------------------------------------------------------
int CButton::GetTextHeight() const
{
	if(!m_hWnd) return -1;

	CClientDC dc(m_hWnd);
	HFONT hFont = GetFont();
	HFONT hOrgFont = 0;
	if(hFont)
		hOrgFont = dc.SelectFont(hFont);
	TEXTMETRIC tm;
	GetTextMetrics(dc, &tm);
	int height = tm.tmHeight + tm.tmExternalLeading + 9;
	if(hOrgFont)
		dc.SelectFont(hOrgFont);
	return height;
}
//--------------------------------------------------------------------------
// テキストの幅を得る
//--------------------------------------------------------------------------
int CButton::GetTextWidth() const
{
	if(!m_hWnd) return -1;

	CClientDC dc(m_hWnd);
	HFONT hFont = GetFont();
	HFONT hOrgFont = 0;
	if(hFont)
		hOrgFont = dc.SelectFont(hFont);
	int width = dc.GetTextWidth(GetCaption()) + 16;
	if(hOrgFont)
		dc.SelectFont(hOrgFont);
	return width;
}
//--------------------------------------------------------------------------
// 使用可・不可の設定
//--------------------------------------------------------------------------
void CButton::SetEnable(BOOL bEnable)
{
	UINT style = GetWindowLong(m_hWnd, GWL_STYLE);
	if(bEnable)
		style &= ~WS_DISABLED;
	else
		style |= WS_DISABLED;
	SetWindowLong(m_hWnd, GWL_STYLE, style);
}
//--------------------------------------------------------------------------
// サイズをテキストに合わせる
//--------------------------------------------------------------------------
void CButton::SetSizeToTextSize()
{
	SetClientSize(GetTextWidth(), GetTextHeight(), FALSE);
}
//--------------------------------------------------------------------------
