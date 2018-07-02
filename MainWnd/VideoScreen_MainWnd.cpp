//----------------------------------------------------------------------------
// VideoScreen_MainWnd.cpp : ビデオ画面の管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../App.h"
#include "../Common/CommandList.h"
#include "Divider_MainWnd.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "Sound.h"
#include "TimeLabel_MainWnd.h"
#include "ToolBar_MainWnd.h"
#include "VideoScreen_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CVideoScreen_MainWnd::Create()
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

	POINT pt;
	pt.y = m_rMainWnd.GetToolBar().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nToolBarBottom = pt.y + m_rMainWnd.GetToolBar().GetHeight();
	pt.y = m_rMainWnd.GetTimeLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nTimeLabelBottom = pt.y + m_rMainWnd.GetTimeLabel().GetHeight() +
						   m_rMainWnd.GetControlOffset();
	int nBigger = nToolBarBottom > nTimeLabelBottom ? nToolBarBottom :
				  nTimeLabelBottom;
	SetPos(0, nBigger);
	SetSize(m_rMainWnd.GetClientWidth(), 240);

	return TRUE;
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CVideoScreen_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetToolBar().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = 0;
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
		+ m_rMainWnd.GetControlOffset() / 2;
	SetPos(nLeft, pt.y + m_rMainWnd.GetToolBar().GetHeight()
			+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CVideoScreen_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VIDEOSCREEN))
		return CStatic::GetHeight();
	else return m_rMainWnd.GetToolBar().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CVideoScreen_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VIDEOSCREEN))
		return CStatic::GetTop();
	else return m_rMainWnd.GetToolBar().GetTop();
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CVideoScreen_MainWnd::ResetSize()
{
	BOOL bListVisible = m_rMainWnd.GetMenu().IsItemChecked(ID_PLAYLIST);
	int nHeight = IsWindowVisible(m_hWnd) ? GetHeight() : 240;
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	int nWidth = m_rMainWnd.GetClientWidth() - pt.x;
	if(!bListVisible) {
		nHeight = m_rMainWnd.GetClientHeight() -
				  m_rMainWnd.GetDivider1().GetHeight() -
				  m_rMainWnd.GetToolBar().GetHeight() -
				  m_rMainWnd.GetTimeSliderHeight() -  
				  m_rMainWnd.GetControlBarHeight() -
				  m_rMainWnd.GetControlBar2Height() -
				  m_rMainWnd.GetEQHeight() -
				  m_rMainWnd.GetControlOffset();
		SetSize(nWidth, nHeight);
	}
	else SetSize(nWidth, nHeight);
	if(m_rMainWnd.IsVideo())
		m_rMainWnd.GetSound().ResetSize(0, 0, nWidth, nHeight);
}
//----------------------------------------------------------------------------
// 幅の再設定
//----------------------------------------------------------------------------
void CVideoScreen_MainWnd::ResetWidth()
{
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	int nWidth = m_rMainWnd.GetClientWidth() - pt.x;
	int nHeight = GetHeight();
	SetSize(nWidth, nHeight);
	if(m_rMainWnd.IsVideo())
		m_rMainWnd.GetSound().ResetSize(0, 0, nWidth, nHeight);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CVideoScreen_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CVideoScreen_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	m_rClickMenu.Create();
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, xPos,
		yPos, 0, m_hWnd, NULL);
	
	return CStatic::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
// ダブルクリックされた
//----------------------------------------------------------------------------
void CVideoScreen_MainWnd::OnLButtonDoubleClick(int x, int y, UINT keyFlags)
{
	m_rMainWnd.SetFullScreen();
	WindowProc(WM_LBUTTONDBLCLK, (WPARAM)keyFlags, MAKELPARAM(x, y));
}
//----------------------------------------------------------------------------
