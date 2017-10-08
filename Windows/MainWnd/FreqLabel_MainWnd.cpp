//----------------------------------------------------------------------------
// FreqLabel_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../Common/Utils.h"
#include "../App.h"
#include "MainWnd.h"
#include "FreqLabel_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CFreqLabel_MainWnd::Create()
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
	pt.y = m_rMainWnd.GetSpeedLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nSpeedLabelBottom = pt.y + m_rMainWnd.GetSpeedLabel().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	pt.y = m_rMainWnd.GetSpeedSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nSpeedSliderBottom = pt.y + m_rMainWnd.GetSpeedSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	int nBigger = nSpeedLabelBottom > nSpeedSliderBottom ?
		nSpeedLabelBottom : nSpeedSliderBottom;
	SetPos(m_rMainWnd.GetControlOffset(), nBigger);
#if JP
	SetText(_T("再生周波数 : "));
#else // JP
	SetText(_T("Frequency : "));
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

	SetSize(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth()
		+ m_percentLabel.GetWidth(), m_edit.GetHeight());
	SetFreq(100.0);

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CFreqLabel_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_FREQ))
		return CStatic::GetHeight();
	else return m_rMainWnd.GetSpeedLabel().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CFreqLabel_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_FREQ))
		return CStatic::GetTop();
	else return m_rMainWnd.GetSpeedLabel().GetTop();
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetSpeedLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nSpeedLabelBottom = pt.y + m_rMainWnd.GetSpeedLabel().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	pt.y = m_rMainWnd.GetSpeedSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nSpeedSliderBottom = pt.y + m_rMainWnd.GetSpeedSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset();
	int nBigger = nSpeedLabelBottom > nSpeedSliderBottom
		? nSpeedLabelBottom : nSpeedSliderBottom;
	int nLeft = m_rMainWnd.GetControlOffset();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, nBigger);
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	m_nDecimalDigit = nDecimalDigit;
	double dCurrentFreq = (double)_tstof(m_edit.GetText().c_str());
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
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(nDecimalDigit);
	SetFreq(dCurrentFreq);
	SetSize(GetWidth() + m_edit.GetWidth() + m_ud.GetWidth() +
			m_percentLabel.GetWidth(), m_edit.GetHeight());
	m_rMainWnd.GetFreqSlider().ResetPos();
	m_edit.SetDecimalDigit(m_nDecimalDigit);
}
//----------------------------------------------------------------------------
// 表示する周波数を表示
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::SetFreq(double dFreq)
{
	double dMinFreq = m_rMainWnd.GetFreqSlider().GetRangeMin()
						/ pow(10.0, m_nDecimalDigit);
	double dMaxFreq = m_rMainWnd.GetFreqSlider().GetRangeMax()
						/ pow(10.0, m_nDecimalDigit);
	if(dFreq < dMinFreq || dMaxFreq < dFreq) return;

	TCHAR text[18];
	if(m_nDecimalDigit == 2)
		_stprintf_s(text, _T("%3.2f"), dFreq);
	else if(m_nDecimalDigit == 1)
		_stprintf_s(text, _T("%3.1f"), dFreq);
	else
		_stprintf_s(text, _T("%d"), (int)dFreq);
	m_edit.SetText(text);
	InvalidateRect(NULL, TRUE);
	SendMessage(m_ud, UDM_SETPOS32, 0, (int)(dFreq * pow(10.0,
		m_nDecimalDigit)));
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::SetLimit(double dMinFreq,
									   double dMaxFreq)
{
	int nMinFreq = (int)(dMinFreq * pow(10.0, m_nDecimalDigit));
	int nMaxFreq = (int)(dMaxFreq * pow(10.0, m_nDecimalDigit));
	int nCurrentFreq = (int)((double)_tstof(m_edit.GetText().c_str())
		* pow(10.0, m_nDecimalDigit) + 0.9 / pow(10.0, m_nDecimalDigit));
	SendMessage(m_ud, UDM_SETRANGE32, nMinFreq, nMaxFreq);
	if(nCurrentFreq < nMinFreq) nCurrentFreq = nMinFreq;
	else if(nMaxFreq < nCurrentFreq) nCurrentFreq = nMaxFreq;
	SetFreq(nCurrentFreq / pow(10.0, m_nDecimalDigit));
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			tstring strFreq = m_edit.GetText();
			double d = _ttof(strFreq.c_str());
			int n = (int)(d * pow(10.0, m_nDecimalDigit)
				+ 0.9 / pow(10.0, m_nDecimalDigit));
			int nMinFreq = m_rMainWnd.GetFreqSlider().GetRangeMin();
			int nMaxFreq = m_rMainWnd.GetFreqSlider().GetRangeMax();
			if(nMinFreq <= n && n <= nMaxFreq) {
				m_rMainWnd.GetFreqSlider().SetThumbPos(n);
				m_rMainWnd.SetFreq(n / pow(10.0, m_nDecimalDigit));
				SendMessage(m_ud, UDM_SETPOS32, 0, n);
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			tstring strFreq = m_edit.GetText();
			double d = _ttof(strFreq.c_str());
			int n = (int)(d * pow(10.0, m_nDecimalDigit)
				+ 0.9 / pow(10.0, m_nDecimalDigit));
			int nMinFreq = m_rMainWnd.GetFreqSlider().GetRangeMin();
			int nMaxFreq = m_rMainWnd.GetFreqSlider().GetRangeMax();
			if(n < nMinFreq) n = nMinFreq;
			else if(n > nMaxFreq) n = nMaxFreq;
			SetFreq(n / pow(10.0, m_nDecimalDigit));
			m_rMainWnd.GetFreqSlider().SetThumbPos(n, TRUE);
			m_rMainWnd.SetFreq(n / pow(10.0, m_nDecimalDigit));
		}
	}
	else m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CFreqLabel_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
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
LRESULT CFreqLabel_MainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->hwndFrom == (HWND)m_ud) {
		if(pnmhdr->code == UDN_DELTAPOS) {
			tstring strFreq = m_edit.GetText();
			double d = _ttof(strFreq.c_str());
			int n = (int)(d * pow(10.0, m_nDecimalDigit)
				+ 0.9 / pow(10.0, m_nDecimalDigit));
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n++;
			else n--;
			SetFreq(n / pow(10.0, m_nDecimalDigit));
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return TRUE;
		}
	}
	return CStatic::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
