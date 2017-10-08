//----------------------------------------------------------------------------
// SpeedSlider_MainWnd.cpp : 再生速度設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/Utils.h"
#include "MainWnd.h"
#include "SpeedSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CSpeedSlider_MainWnd::Create()
{
	CSliderCtrl::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;

	SetStyle(GetStyle() | WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ | TBS_NOTICKS);
	POINT pt;
	pt.x = m_rMainWnd.GetSpeedLabel().GetLeft();
	pt.y = m_rMainWnd.GetSpeedLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(pt.x + m_rMainWnd.GetSpeedLabel().GetWidth() +
		   m_rMainWnd.GetControlOffset(), pt.y);
	ResetSize();

	SetRangeMin(100);
	SetRangeMax(12000);
	SetLineSize(10);
	SetPageSize(50);
	SetThumbPos(1000);

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CSpeedSlider_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED))
		return CSliderCtrl::GetHeight();
	else return m_rMainWnd.GetDivider2().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CSpeedSlider_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED))
		return CSliderCtrl::GetTop();
	else return m_rMainWnd.GetDivider2().GetTop();
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::ResetPos()
{
	POINT pt;
	pt.x = m_rMainWnd.GetSpeedLabel().GetLeft();
	pt.y = m_rMainWnd.GetSpeedLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = pt.x + m_rMainWnd.GetSpeedLabel().GetWidth()
				+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y);
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::ResetSize()
{
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	SetSize(m_rMainWnd.GetClientWidth() - pt.x,
			(int)(GetSystemMetrics(SM_CYHSCROLL) * 1.5));
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	SetRangeMax((LONG)((GetRangeMax() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetRangeMin((LONG)((GetRangeMin() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetLineSize((LONG)(1 * pow(10.0, nDecimalDigit)));
	SetPageSize((LONG)(5 * pow(10.0, nDecimalDigit)));
	SetThumbPos((LONG)((GetThumbPos() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	m_nDecimalDigit = nDecimalDigit;
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::SetLimit(double dMinSpeed, double dMaxSpeed)
{
	int nMinSpeed = (int)(dMinSpeed * pow(10.0, m_nDecimalDigit));
	int nMaxSpeed = (int)(dMaxSpeed * pow(10.0, m_nDecimalDigit));
	int nCurrentSpeed = (int)GetThumbPos();
	SetRangeMin(nMinSpeed);
	SetRangeMax(nMaxSpeed, TRUE);
	if(nCurrentSpeed < nMinSpeed) nCurrentSpeed = nMinSpeed;
	else if(nMaxSpeed < nCurrentSpeed) nCurrentSpeed = nMaxSpeed;
	SetThumbPos(nCurrentSpeed);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CSliderCtrl::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::OnHScroll(HWND hwndCtl, UINT code, int pos)
{
	double n = (double)(GetThumbPos() / pow(10.0, m_nDecimalDigit));
	m_rMainWnd.SetSpeed(n);
	m_rMainWnd.GetSpeedLabel().SetSpeed(n);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_HOME) {
		SetThumbPos(100 * (int)pow(10.0, m_nDecimalDigit));
		m_rMainWnd.SetSpeed(100.0);
		m_rMainWnd.GetSpeedLabel().SetSpeed(100.0);
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
void CSpeedSlider_MainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	RECT rc;
	SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&rc);
	if(rc.left < x && x < rc.right &&
		rc.top < y && y < rc.bottom) {
		if(GetTickCount() - dwThumbClickTime <= GetDoubleClickTime()) {
			SetThumbPos(100 * (int)pow(10.0, m_nDecimalDigit));
			m_rMainWnd.GetSpeedLabel().SetSpeed(100.0);
			m_rMainWnd.SetSpeed(100.0);
			return;
		}
		else dwThumbClickTime = GetTickCount();
	}
	CSliderCtrl::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// 右クリックが離された
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::OnRButtonUp(int x, int y, UINT keyFlags)
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
// マウスホイールがスクロールされた
//----------------------------------------------------------------------------
BOOL CSpeedSlider_MainWnd::OnMouseWheel(UINT nFlags, int zDelta, POINTS pt)
{
	tstring strSpeed = m_rMainWnd.GetSpeedLabel().GetEdit().GetText();
	int n = _ttoi(CUtils::Replace(strSpeed, _T("."), _T("")).c_str());
	if(zDelta >= 0) n++;
	else n--;
	int nMin = GetRangeMin(), nMax = GetRangeMax();
	if(n < nMin) n = nMin;
	if(n > nMax) n = nMax;
	double dSpeed = n / pow(10.0, m_nDecimalDigit);
	m_rMainWnd.SetSpeed(dSpeed);
	m_rMainWnd.GetSpeedLabel().SetSpeed(dSpeed);
	return FALSE;
}
//----------------------------------------------------------------------------
