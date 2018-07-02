//----------------------------------------------------------------------------
// EQ1_25KSlider_MainWnd.cpp : イコライザ ( 1.25KHz ) 設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "EQ1KSlider_MainWnd.h"
#include "EQ1_25KLabel_MainWnd.h"
#include "EQ1_25KSlider_MainWnd.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "PanSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CEQ1_25KSlider_MainWnd::Create()
{
	CSliderCtrl::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;

	SetStyle(GetStyle() | WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ | TBS_NOTICKS);

	SetRangeMin(-30);
	SetRangeMax(30);
	SetLineSize(1);
	SetPageSize(1);
	SetThumbPos(0);

	ResetPos();
	ResetSize();

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CEQ1_25KSlider_MainWnd::GetHeight() const
{
	if(!m_rMainWnd.GetMenu().IsItemChecked(ID_EQ))
		return m_rMainWnd.GetPanSlider().GetHeight();
	else if(m_rMainWnd.GetMenu().IsItemChecked(ID_EQ1_25K))
		return CSliderCtrl::GetHeight();
	else return m_rMainWnd.GetEQ1KSlider().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CEQ1_25KSlider_MainWnd::GetTop() const
{
	if(!m_rMainWnd.GetMenu().IsItemChecked(ID_EQ))
		return m_rMainWnd.GetPanSlider().GetTop();
	else if(m_rMainWnd.GetMenu().IsItemChecked(ID_EQ1_25K))
		return CSliderCtrl::GetTop();
	else return m_rMainWnd.GetEQ1KSlider().GetTop();
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::ResetPos()
{
	POINT pt;
	pt.x = m_rMainWnd.GetEQ1_25KLabel().GetLeft();
	pt.y = m_rMainWnd.GetEQ1_25KLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = pt.x + m_rMainWnd.GetEQ1_25KLabel().GetWidth()
		+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y);
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::ResetSize()
{
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	int nWidth = m_rMainWnd.GetClientWidth() - pt.x;
	SetSize(nWidth, (int)(GetSystemMetrics(SM_CYHSCROLL) * 1.5));
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CSliderCtrl::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::OnHScroll(HWND hwndCtl, UINT code, int pos)
{
	LONG trackpos = GetThumbPos();
	m_rMainWnd.SetEQ1_25K((int)trackpos);
	m_rMainWnd.GetEQ1_25KLabel().SetEQ1_25K(trackpos);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_HOME) {
		SetThumbPos(0);
		m_rMainWnd.SetEQ1_25K(0);
		m_rMainWnd.GetEQ1_25KLabel().SetEQ1_25K(0);
		return;
	}
	else if(vk == VK_UP) vk = VK_DOWN;
	else if(vk == VK_DOWN) vk = VK_UP;
	else if(vk == VK_PRIOR) vk = VK_NEXT;
	else if(vk == VK_NEXT) vk = VK_PRIOR;
	CSliderCtrl::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// クリックされた
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	RECT rc;
	SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&rc);
	if(rc.left < x && x < rc.right &&
		rc.top < y && y < rc.bottom) {
		if(GetTickCount() - dwThumbClickTime <= GetDoubleClickTime()) {
			SetThumbPos(0);
			m_rMainWnd.GetEQ1_25KLabel().SetEQ1_25K(0);
			m_rMainWnd.SetEQ1_25K(0);
			return;
		}
		else dwThumbClickTime = GetTickCount();
	}
	CSliderCtrl::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// マウスホイールがスクロールされた
//----------------------------------------------------------------------------
BOOL CEQ1_25KSlider_MainWnd::OnMouseWheel(UINT nFlags, int zDelta, POINTS pt)
{
	tstring strEQ = m_rMainWnd.GetEQ1_25KLabel().GetEdit().GetText();
	int n = _ttoi(strEQ.c_str());
	if(zDelta >= 0) n++;
	else n--;
	int nMin = GetRangeMin(), nMax = GetRangeMax();
	if(n < nMin) n = nMin;
	if(n > nMax) n = nMax;
	m_rMainWnd.SetEQ1_25K(n);
	m_rMainWnd.GetEQ1_25KLabel().SetEQ1_25K(n);
	return FALSE;
}
//----------------------------------------------------------------------------
// 右クリックが離された
//----------------------------------------------------------------------------
void CEQ1_25KSlider_MainWnd::OnRButtonUp(int x, int y, UINT keyFlags)
{
	m_rClickMenu.Create();
	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(m_hWnd);
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x,
		pt.y, 0, m_hWnd, NULL);

	CSliderCtrl::OnRButtonUp(x, y, keyFlags);
}
//----------------------------------------------------------------------------
