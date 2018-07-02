//----------------------------------------------------------------------------
// ExplorerBar.cpp : エクスプローラ用ツールバーの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "ExplorerBar.h"
#include "ToolBar_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CExplorerBar::Create()
{
	CStatic::Create(SS_NOTIFY);
	if(!m_hWnd) return FALSE;
	SetParent(m_rMainWnd);

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	m_edit.Create(m_hWnd);
	m_edit.SetExStyle(GetExStyle() | WS_EX_STATICEDGE);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(0, 0);
	m_edit.SetText(_T("8888.8"));
	m_edit.SetSizeToTextSize();
	m_edit.SetSize(240, m_edit.GetHeight());
	m_edit.SetText(_T(""));
	EnableWindow(m_edit, FALSE);
	m_edit.Show(SW_SHOW);

	ResetPos();
	SetSize(240, m_edit.GetHeight());

	return TRUE;
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CExplorerBar::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetToolBar().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(0, pt.y + m_rMainWnd.GetToolBar().GetHeight()
			+ m_rMainWnd.GetControlOffset() + 2);
}
//----------------------------------------------------------------------------
// サイズの設定
//----------------------------------------------------------------------------
void CExplorerBar::SetSize(int cx, int cy)
{
	m_edit.SetSize(cx, cy);
	CStatic::SetSize(cx, cy);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CExplorerBar::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == (HWND)m_edit) {
		if(codeNotify == EN_KILLFOCUS) {
			EnableWindow(m_edit, FALSE);
		}
	}
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// 左クリックが押された
//----------------------------------------------------------------------------
void CExplorerBar::OnLButtonDown(int x, int y, UINT keyFlags)
{
	POINT pt;
	pt.x = m_edit.GetLeft();
	pt.y = m_edit.GetTop();
	ScreenToClient(m_hWnd, &pt);
	if(pt.x <= x && x <= pt.x + m_edit.GetWidth()
		&& pt.y <= y && y <= pt.y + m_edit.GetHeight()) {
		EnableWindow(m_edit, TRUE);
		SetFocus(m_edit);
		PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit, EM_SETSEL, 0, -1);
	}

	CStatic::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CExplorerBar::OnReturnKeyPressed()
{
	TCHAR chPath[255];
	GetCurrentDirectory(255, chPath);

	if(lstrcmp(m_edit.GetText().c_str(), chPath) != 0) {
		SetCurrentDirectory(m_edit.GetText().c_str());
		if(!m_rMainWnd.GetExplorer().ShowFiles()) {
			SetCurrentDirectory(chPath);
			m_rMainWnd.GetExplorer().ShowFiles();
		}
	}
	EnableWindow(m_edit, FALSE);
}
//----------------------------------------------------------------------------
