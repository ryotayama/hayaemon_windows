//----------------------------------------------------------------------------
// SpeedLabel_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../App.h"
#include "../Common/CommandList.h"
#include "Divider2_MainWnd.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "SpeedLabel_MainWnd.h"
#include "SpeedSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CSpeedLabel_MainWnd::Create()
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
	pt.y = m_rMainWnd.GetDivider2().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetControlOffset(), pt.y +
		   m_rMainWnd.GetDivider2().GetHeight() +
		   m_rMainWnd.GetControlOffset() * 2);
#if JP
	SetText(_T("再生速度 : "));
#else // JP
	SetText(_T("Speed : "));
#endif // JP
	SetSizeToTextSize();

	m_edit.Create(m_hWnd);
	SendMessage(m_edit, EM_SETLIMITTEXT, 6, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(GetWidth(), 0);
	m_edit.SetText(_T("8888.8"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T("100.0"));
	m_edit.Show(SW_SHOW);

	m_ud.Create(m_hWnd, m_edit);
	SendMessage(m_ud, UDM_SETPOS32, 0, 1000);
	SendMessage(m_ud, UDM_SETRANGE32, 100, 12000);
	m_ud.Show(SW_SHOW);

	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	m_ud.SetPos(GetWidth() + m_edit.GetWidth(), 0);

	m_percentLabel.Create();
	m_percentLabel.SetParent(m_hWnd);
	m_percentLabel.SetText(_T(" %"));
	m_percentLabel.SetPos(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth(), 0);
	m_percentLabel.SetFont(m_font, TRUE);
	m_percentLabel.SetSizeToTextSize();
	m_percentLabel.Show(SW_SHOW);

	SetSize(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth() +
			m_percentLabel.GetWidth(), m_edit.GetHeight());
	SetSpeed(100.0);

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CSpeedLabel_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED))
		return CStatic::GetHeight();
	else return m_rMainWnd.GetDivider2().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CSpeedLabel_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED))
		return CStatic::GetTop();
	else return m_rMainWnd.GetDivider2().GetTop();
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetDivider2().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = m_rMainWnd.GetControlOffset();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y + m_rMainWnd.GetDivider2().GetHeight()
		+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	m_nDecimalDigit = nDecimalDigit;
	double dCurrentSpeed = (double)_tstof(m_edit.GetText().c_str());
	tstring str = m_edit.GetText();
	tstring strTemp = _T("8888.");
	for(int i = 0; i < m_nDecimalDigit; i++) strTemp += _T("8");
	SendMessage(m_edit, EM_SETLIMITTEXT, strTemp.length(), 0);
	m_edit.SetText(strTemp.c_str());
	SendMessage(m_ud, UDM_SETPOS32, 0, (LPARAM)(100 * pow(10.0,
		m_nDecimalDigit)));
	SendMessage(m_ud, UDM_SETRANGE32, (WPARAM)(10 * pow(10.0,
		m_nDecimalDigit)), (LPARAM)(1200 * pow(10.0, m_nDecimalDigit)));
	m_edit.SetSizeToTextSize();
	SetSizeToTextSize();
	m_ud.SetPos(GetWidth() + m_edit.GetWidth(), 0);
	m_percentLabel.SetPos(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth(), 0);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(nDecimalDigit);
	SetSpeed(dCurrentSpeed);
	SetSize(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth() +
			m_percentLabel.GetWidth(), m_edit.GetHeight());
	m_rMainWnd.GetSpeedSlider().ResetPos();
	m_edit.SetDecimalDigit(m_nDecimalDigit);
}
//----------------------------------------------------------------------------
// 表示する速度をパーセントで設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::SetSpeed(double dSpeed)
{
	double dMinSpeed = m_rMainWnd.GetSpeedSlider().GetRangeMin()
						/ pow(10.0, m_nDecimalDigit);
	double dMaxSpeed = m_rMainWnd.GetSpeedSlider().GetRangeMax()
						/ pow(10.0, m_nDecimalDigit);
	if(dSpeed < dMinSpeed || dMaxSpeed < dSpeed) return;

	TCHAR text[17];
	if(m_nDecimalDigit == 2)
		_stprintf_s(text, _T("%3.2f"), dSpeed);
	else if(m_nDecimalDigit == 1)
		_stprintf_s(text, _T("%3.1f"), dSpeed);
	else
		_stprintf_s(text, _T("%d"), (int)dSpeed);
	m_edit.SetText(text);
	InvalidateRect(NULL, TRUE);
	SendMessage(m_ud, UDM_SETPOS32, 0, (int)(dSpeed * pow(10.0,
		m_nDecimalDigit)));
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::SetLimit(double dMinSpeed, double dMaxSpeed)
{
	int nMinSpeed = (int)(dMinSpeed * pow(10.0, m_nDecimalDigit));
	int nMaxSpeed = (int)(dMaxSpeed * pow(10.0, m_nDecimalDigit));
	int nCurrentSpeed = (int)((double)_tstof(m_edit.GetText().c_str())
		* pow(10.0, m_nDecimalDigit) + 0.9 / pow(10.0, m_nDecimalDigit));
	SendMessage(m_ud, UDM_SETRANGE32, nMinSpeed, nMaxSpeed);
	if(nCurrentSpeed < nMinSpeed) nCurrentSpeed = nMinSpeed;
	else if(nMaxSpeed < nCurrentSpeed) nCurrentSpeed = nMaxSpeed;
	SetSpeed(nCurrentSpeed / pow(10.0, m_nDecimalDigit));
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			tstring strSpeed = m_edit.GetText();
			double d = _ttof(strSpeed.c_str());
			int n = (int)(d * pow(10.0, m_nDecimalDigit)
				+ 0.9 / pow(10.0, m_nDecimalDigit));
			int nMinSpeed = m_rMainWnd.GetSpeedSlider().GetRangeMin();
			int nMaxSpeed = m_rMainWnd.GetSpeedSlider().GetRangeMax();
			if(nMinSpeed <= n && n <= nMaxSpeed) {
				m_rMainWnd.GetSpeedSlider().SetThumbPos(n);
				m_rMainWnd.SetSpeed(n / pow(10.0, m_nDecimalDigit));
				SendMessage(m_ud, UDM_SETPOS32, 0, n);
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			tstring strSpeed = m_edit.GetText();
			double d = _ttof(strSpeed.c_str());
			int n = (int)(d * pow(10.0, m_nDecimalDigit)
				+ 0.9 / pow(10.0, m_nDecimalDigit));
			int nMinSpeed = m_rMainWnd.GetSpeedSlider().GetRangeMin();
			int nMaxSpeed = m_rMainWnd.GetSpeedSlider().GetRangeMax();
			if(n < nMinSpeed) n = nMinSpeed;
			else if(n > nMaxSpeed) n = nMaxSpeed;
			SetSpeed(n / pow(10.0, m_nDecimalDigit));
			m_rMainWnd.GetSpeedSlider().SetThumbPos(n, TRUE);
			m_rMainWnd.SetSpeed(n / pow(10.0, m_nDecimalDigit));
		}
	}
	else m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CSpeedLabel_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	m_rClickMenu.Create();
	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(m_hWnd);
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x,
		pt.y, 0, m_hWnd, NULL);
	return CStatic::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
LRESULT CSpeedLabel_MainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->hwndFrom == (HWND)m_ud) {
		if(pnmhdr->code == UDN_DELTAPOS) {
			tstring strSpeed = m_edit.GetText();
			double d = _ttof(strSpeed.c_str());
			int n = (int)(d * pow(10.0, m_nDecimalDigit)
				+ 0.9 / pow(10.0, m_nDecimalDigit));
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n++;
			else n--;
			SetSpeed(n / pow(10.0, m_nDecimalDigit));
			m_rMainWnd.GetSpeedSlider().SetThumbPos(n, TRUE);
			m_rMainWnd.SetSpeed(n / pow(10.0, m_nDecimalDigit));
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return TRUE;
		}
	}
	return CStatic::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
