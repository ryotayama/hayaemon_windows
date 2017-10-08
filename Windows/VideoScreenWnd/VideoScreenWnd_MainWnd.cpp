//----------------------------------------------------------------------------
// VideoScreenWnd_MainWnd.cpp : タイマー再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "VideoScreenWnd_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CVideoScreenWnd_MainWnd::Create()
{
	Destroy();

	CStatic::Create(SS_NOTIFY | SS_BLACKRECT);
	if(!m_hWnd) return FALSE;
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	SetPos(GetSystemMetrics(SM_XVIRTUALSCREEN),
		   GetSystemMetrics(SM_YVIRTUALSCREEN));
	SetSize(GetSystemMetrics(SM_CXVIRTUALSCREEN),
			GetSystemMetrics(SM_CYVIRTUALSCREEN));
	Show(SW_SHOW);

	return TRUE;
}
//----------------------------------------------------------------------------
// 閉じられようとしている
//----------------------------------------------------------------------------
void CVideoScreenWnd_MainWnd::OnClose()
{
	if(m_rMainWnd.IsFullScreen()) m_rMainWnd.SetFullScreen();
	CStatic::OnClose();
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CVideoScreenWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CVideoScreenWnd_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	m_rClickMenu.Create();
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, xPos,
		yPos, 0, m_hWnd, NULL);
	
	return CStatic::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
// ダブルクリックされた
//----------------------------------------------------------------------------
void CVideoScreenWnd_MainWnd::OnLButtonDoubleClick(int x, int y, UINT keyFlags)
{
	m_rMainWnd.SetFullScreen();
	CStatic::OnLButtonDoubleClick(x, y, keyFlags);
}
//----------------------------------------------------------------------------
