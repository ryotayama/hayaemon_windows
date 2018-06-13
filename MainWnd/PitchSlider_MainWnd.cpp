//----------------------------------------------------------------------------
// PitchSlider_MainWnd.cpp : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../Common/Utils.h"
#include "../App.h"
#include "MainWnd.h"
#include "PitchSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPitchSlider_MainWnd::Create()
{
	CSliderCtrl::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;

	SetStyle(GetStyle() | WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ | TBS_NOTICKS);

	POINT pt;
	pt.x = m_rMainWnd.GetPitchLabel().GetLeft();
	pt.y = m_rMainWnd.GetPitchLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = pt.x + m_rMainWnd.GetPitchLabel().GetWidth() +
				m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y);
	ResetSize();

	SetRangeMin(-240);
	SetRangeMax(240);
	SetLineSize(10);
	SetPageSize(10);
	SetThumbPos(0);

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CPitchSlider_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CSliderCtrl::GetHeight();
	else return m_rMainWnd.GetFreqSlider().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CPitchSlider_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CSliderCtrl::GetTop();
	else return m_rMainWnd.GetFreqSlider().GetTop();
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::ResetPos()
{
	POINT pt;
	pt.x = m_rMainWnd.GetPitchLabel().GetLeft();
	pt.y = m_rMainWnd.GetPitchLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = pt.x + m_rMainWnd.GetPitchLabel().GetWidth()
				+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y);
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::ResetSize()
{
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	int nWidth = m_rMainWnd.GetClientWidth() - pt.x;
	SetSize(nWidth, (int)(GetSystemMetrics(SM_CYHSCROLL) * 1.5));
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	SetRangeMax((LONG)((GetRangeMax() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetRangeMin((LONG)((GetRangeMin() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetLineSize((LONG)(1 * pow(10.0, nDecimalDigit)));
	SetPageSize((LONG)(1 * pow(10.0, nDecimalDigit)));
	SetThumbPos((LONG)((GetThumbPos() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	m_nDecimalDigit = nDecimalDigit;
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::SetLimit(double dMinPitch, double dMaxPitch)
{
	int nMinPitch = (int)(dMinPitch * pow(10.0, m_nDecimalDigit));
	int nMaxPitch = (int)(dMaxPitch * pow(10.0, m_nDecimalDigit));
	int nCurrentPitch = (int)GetThumbPos();
	SetRangeMin(nMinPitch);
	SetRangeMax(nMaxPitch, TRUE);
	if(nCurrentPitch < nMinPitch) nCurrentPitch = nMinPitch;
	else if(nMaxPitch < nCurrentPitch) nCurrentPitch = nMaxPitch;
	SetThumbPos(nCurrentPitch);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CSliderCtrl::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::OnHScroll(HWND hwndCtl, UINT code, int pos)
{
	double n = (double)(GetThumbPos() / pow(10.0, m_nDecimalDigit));
	m_rMainWnd.SetPitch(n);
	m_rMainWnd.GetPitchLabel().SetPitch(n);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_HOME) {
		SetThumbPos(0);
		m_rMainWnd.SetPitch(0.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
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
void CPitchSlider_MainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	RECT rc;
	SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&rc);
	if(rc.left < x && x < rc.right &&
		rc.top < y && y < rc.bottom) {
		if(GetTickCount() - dwThumbClickTime <= GetDoubleClickTime()) {
			SetThumbPos(0);
			m_rMainWnd.GetPitchLabel().SetPitch(0.0);
			m_rMainWnd.SetPitch(0.0);
			return;
		}
		else dwThumbClickTime = GetTickCount();
	}
	CSliderCtrl::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// マウスホイールがスクロールされた
//----------------------------------------------------------------------------
BOOL CPitchSlider_MainWnd::OnMouseWheel(UINT nFlags, int zDelta, POINTS pt)
{
	tstring strPitch = m_rMainWnd.GetPitchLabel().GetEdit().GetText();
#ifdef UNICODE
	if(strPitch.find(_T("♭")) == 0) strPitch.replace(0, 1, _T("-"));
	else if(strPitch.find(_T("♯")) == 0) strPitch.replace(0, 1, _T(""));
#else // UNICODE
	if(strPitch.find(_T("♭")) == 0) strPitch.replace(0, 2, _T("-"));
	else if(strPitch.find(_T("♯")) == 0) strPitch.replace(0, 2, _T(""));
#endif // UNICODE
	int n = _ttoi(CUtils::Replace(strPitch, _T("."), _T("")).c_str());
	if(zDelta >= 0) n++;
	else n--;
	int nMin = GetRangeMin(), nMax = GetRangeMax();
	if(n < nMin) n = nMin;
	if(n > nMax) n = nMax;
	double dPitch = n / pow(10.0, m_nDecimalDigit);
	m_rMainWnd.SetPitch(dPitch);
	m_rMainWnd.GetPitchLabel().SetPitch(dPitch);
	return FALSE;
}
//----------------------------------------------------------------------------
// 右クリックが離された
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::OnRButtonUp(int x, int y, UINT keyFlags)
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
