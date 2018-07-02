//----------------------------------------------------------------------------
// PitchLabel_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../App.h"
#include "../Common/CommandList.h"
#include "Explorer.h"
#include "FreqLabel_MainWnd.h"
#include "FreqSlider_MainWnd.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "PitchLabel_MainWnd.h"
#include "PitchSlider_MainWnd.h"
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CEdit_PitchLabel::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_HOME) {
		int nDecimalDigit = m_rMainWnd.GetPitchLabel().GetDecimalDigit();
		if(nDecimalDigit == 2) this->SetText(_T("0.00"));
		else if(nDecimalDigit == 1) this->SetText(_T("0.0"));
		else this->SetText(_T("0"));
		PostMessage(m_hWnd, WM_LBUTTONUP, 0, 0);
		PostMessage(m_hWnd, EM_SETSEL, 0, -1);
	}
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPitchLabel_MainWnd::Create()
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
	pt.y = m_rMainWnd.GetFreqLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nFreqLabelBottom = pt.y
		+ m_rMainWnd.GetFreqLabel().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	pt.y = m_rMainWnd.GetFreqSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nFreqSliderBottom = pt.y
		+ m_rMainWnd.GetFreqSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	int nBigger = nFreqLabelBottom > nFreqSliderBottom ?
		nFreqLabelBottom : nFreqSliderBottom;
	SetPos(m_rMainWnd.GetControlOffset(), nBigger);
#if JP
	SetText(_T("音程 : "));
#else // JP
	SetText(_T("Pitch : "));
#endif // JP
	SetSizeToTextSize();

	m_edit.Create(m_hWnd);
	SendMessage(m_edit, EM_SETLIMITTEXT, 6, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(GetWidth(), 0);
	m_edit.SetText(_T("♭88.8"));
	m_edit.SetSizeToTextSize();
	m_edit.Show(SW_SHOW);

	m_ud.Create(m_hWnd, m_edit);
	SendMessage(m_ud, UDM_SETPOS32, 0, 0);
	SendMessage(m_ud, UDM_SETRANGE32, -240, 240);
	m_ud.Show(SW_SHOW);

	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	m_ud.SetPos(GetWidth() + m_edit.GetWidth(), 0);

	SetSize(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth(),
			m_edit.GetHeight());
	SetPitch(0.0);

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CPitchLabel_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CStatic::GetHeight();
	else return m_rMainWnd.GetFreqLabel().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CPitchLabel_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CStatic::GetTop();
	else return m_rMainWnd.GetFreqLabel().GetTop();
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetFreqLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nFreqLabelBottom = pt.y
		+ m_rMainWnd.GetFreqLabel().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	pt.y = m_rMainWnd.GetFreqSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nFreqSliderBottom = pt.y
		+ m_rMainWnd.GetFreqSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	int nBigger = nFreqLabelBottom > nFreqSliderBottom
		? nFreqLabelBottom : nFreqSliderBottom;
	int nLeft = m_rMainWnd.GetControlOffset();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, nBigger);
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	m_nDecimalDigit = nDecimalDigit;
	tstring strText = m_edit.GetText();
#ifdef UNICODE
	if(strText.find(_T("♭")) == 0) strText.replace(0, 1, _T("-"));
	else if(strText.find(_T("♯")) == 0) strText.replace(0, 1, _T(""));
#else // UNICODE
	if(strText.find(_T("♭")) == 0) strText.replace(0, 2, _T("-"));
	else if(strText.find(_T("♯")) == 0) strText.replace(0, 2, _T(""));
#endif // UNICODE
	double dCurrentPitch = (double)_tstof(strText.c_str());
	tstring str = m_edit.GetText();
	tstring strTemp = _T("♭88.");
	for(int i = 0; i < m_nDecimalDigit; i++) strTemp += _T("8");
	SendMessage(m_edit, EM_SETLIMITTEXT, strTemp.length(), 0);
	m_edit.SetText(strTemp.c_str());
	SendMessage(m_ud, UDM_SETPOS32, 0, (LPARAM)0);
	SendMessage(m_ud, UDM_SETRANGE32, (WPARAM)(-24 * (int)pow(10.0,
		m_nDecimalDigit)), (LPARAM)(24 * (int)pow(10.0, m_nDecimalDigit)));
	m_edit.SetSizeToTextSize();
	SetSizeToTextSize();
	m_ud.SetPos(GetWidth() + m_edit.GetWidth(), 0);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(nDecimalDigit);
	SetPitch(dCurrentPitch);
	SetSize(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth(),
		m_edit.GetHeight());
	m_rMainWnd.GetPitchSlider().ResetPos();
}
//----------------------------------------------------------------------------
// 表示する音程を設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::SetPitch(double dPitch)
{
	double dMinPitch = m_rMainWnd.GetPitchSlider().GetRangeMin()
						/ pow(10.0, m_nDecimalDigit);
	double dMaxPitch = m_rMainWnd.GetPitchSlider().GetRangeMax()
						/ pow(10.0, m_nDecimalDigit);
	if(dPitch < dMinPitch || dMaxPitch < dPitch) return;

	TCHAR text[12];
	if(dPitch > 0) {
		if(m_nDecimalDigit == 2) _stprintf_s(text, _T("♯%2.2f"), dPitch);
		else if(m_nDecimalDigit == 1)
			_stprintf_s(text, _T("♯%2.1f"), dPitch);
		else _stprintf_s(text, _T("♯%d"), (int)dPitch);
	}
	else if(dPitch < 0) {
		if(m_nDecimalDigit == 2)
			_stprintf_s(text, _T("♭%2.2f"), dPitch * -1);
		else if(m_nDecimalDigit == 1)
			_stprintf_s(text, _T("♭%2.1f"), dPitch * -1);
		else _stprintf_s(text, _T("♭%d"), (int)dPitch * -1);
	}
	else {
		if(m_nDecimalDigit == 2) _stprintf_s(text, _T("%2.2f"), dPitch);
		else if(m_nDecimalDigit == 1)
			_stprintf_s(text, _T("%2.1f"), dPitch);
		else _stprintf_s(text, _T("%d"), (int)dPitch);
	}
	m_edit.SetText(text);
	InvalidateRect(NULL, TRUE);
	SendMessage(m_ud, UDM_SETPOS32, 0, (int)(dPitch
		* pow(10.0, m_nDecimalDigit)));
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::SetLimit(double dMinPitch, double dMaxPitch)
{
	int nMinPitch = (int)(dMinPitch * pow(10.0, m_nDecimalDigit));
	int nMaxPitch = (int)(dMaxPitch * pow(10.0, m_nDecimalDigit));
	tstring strText = m_edit.GetText();
#ifdef UNICODE
	if(strText.find(_T("♭")) == 0)
		strText.replace(0, 1, _T("-"));
	else if(strText.find(_T("♯")) == 0)
		strText.replace(0, 1, _T(""));
#else // UNICODE
	if(strText.find(_T("♭")) == 0)
		strText.replace(0, 2, _T("-"));
	else if(strText.find(_T("♯")) == 0)
		strText.replace(0, 2, _T(""));
#endif // UNICODE
	double d = _ttof(strText.c_str());
	int n;
	if(d >= 0.0) n = (int)(d * pow(10.0, m_nDecimalDigit) + 0.9
						/ pow(10.0, m_nDecimalDigit));
	else n = (int)(d * pow(10.0, m_nDecimalDigit) - 0.9
				/ pow(10.0, m_nDecimalDigit));
	SendMessage(m_ud, UDM_SETRANGE32, nMinPitch, nMaxPitch);
	if(n < nMinPitch) n = nMinPitch;
	else if(nMaxPitch < n) n = nMaxPitch;
	SetPitch(n / pow(10.0, m_nDecimalDigit));
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			tstring strText = m_edit.GetText();
#ifdef UNICODE
			if(strText.find(_T("♭")) == 0)
				strText.replace(0, 1, _T("-"));
			else if(strText.find(_T("♯")) == 0)
				strText.replace(0, 1, _T(""));
#else // UNICODE
			if(strText.find(_T("♭")) == 0)
				strText.replace(0, 2, _T("-"));
			else if(strText.find(_T("♯")) == 0)
				strText.replace(0, 2, _T(""));
#endif // UNICODE
			double d = _ttof(strText.c_str());
			int n;
			if(d >= 0.0) n = (int)(d * pow(10.0, m_nDecimalDigit) + 0.9
								/ pow(10.0, m_nDecimalDigit));
			else n = (int)(d * pow(10.0, m_nDecimalDigit) - 0.9
						/ pow(10.0, m_nDecimalDigit));
			int nMinPitch = m_rMainWnd.GetPitchSlider().GetRangeMin();
			int nMaxPitch = m_rMainWnd.GetPitchSlider().GetRangeMax();
			if(nMinPitch <= n && n <= nMaxPitch) {
				m_rMainWnd.GetPitchSlider().SetThumbPos(n);
				m_rMainWnd.SetPitch(n / pow(10.0, m_nDecimalDigit));
				SendMessage(m_ud, UDM_SETPOS32, 0, n);
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			tstring strText = m_edit.GetText();
#ifdef UNICODE
			if(strText.find(_T("♭")) == 0)
				strText.replace(0, 1, _T("-"));
			else if(strText.find(_T("♯")) == 0)
				strText.replace(0, 1, _T(""));
#else // UNICODE
			if(strText.find(_T("♭")) == 0)
				strText.replace(0, 2, _T("-"));
			else if(strText.find(_T("♯")) == 0)
				strText.replace(0, 2, _T(""));
#endif // UNICODE
			double d = _ttof(strText.c_str());
			int n;
			if(d >= 0.0) n = (int)(d * pow(10.0, m_nDecimalDigit) + 0.9
								/ pow(10.0, m_nDecimalDigit));
			else n = (int)(d * pow(10.0, m_nDecimalDigit) - 0.9
						/ pow(10.0, m_nDecimalDigit));
			int nMinPitch = m_rMainWnd.GetPitchSlider().GetRangeMin();
			int nMaxPitch = m_rMainWnd.GetPitchSlider().GetRangeMax();
			if(n < nMinPitch) n = nMinPitch;
			else if(n > nMaxPitch) n = nMaxPitch;
			SetPitch(n / pow(10.0, m_nDecimalDigit));
			m_rMainWnd.GetPitchSlider().SetThumbPos(n, TRUE);
			m_rMainWnd.SetPitch(n / pow(10.0, m_nDecimalDigit));
		}
	}
	else m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CPitchLabel_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
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
LRESULT CPitchLabel_MainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->hwndFrom == (HWND)m_ud) {
		if(pnmhdr->code == UDN_DELTAPOS) {
			tstring strText = m_edit.GetText();
#ifdef UNICODE
			if(strText.find(_T("♭")) == 0) strText.replace(0, 1, _T("-"));
			else if(strText.find(_T("♯")) == 0) strText.replace(0, 1, _T(""));
#else // UNICODE
			if(strText.find(_T("♭")) == 0) strText.replace(0, 2, _T("-"));
			else if(strText.find(_T("♯")) == 0) strText.replace(0, 2, _T(""));
#endif // UNICODE
			double d = _ttof(strText.c_str());
			int n;
			if(d >= 0.0) n = (int)(d * pow(10.0, m_nDecimalDigit) + 0.9
								/ pow(10.0, m_nDecimalDigit));
			else n = (int)(d * pow(10.0, m_nDecimalDigit) - 0.9
						/ pow(10.0, m_nDecimalDigit));
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n++;
			else n--;
			SetPitch(n / pow(10.0, m_nDecimalDigit));
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return TRUE;
		}
	}
	return CStatic::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
