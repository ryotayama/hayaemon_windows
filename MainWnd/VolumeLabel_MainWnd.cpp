//----------------------------------------------------------------------------
// VolumeLabel_MainWnd.cpp : ボリューム表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../App.h"
#include "MainWnd.h"
#include "VolumeLabel_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CVolumeLabel_MainWnd::Create()
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

	ResetPos();
#if JP
	SetText(_T("音量 : "));
#else // JP
	SetText(_T("Volume : "));
#endif // JP
	SetSizeToTextSize();

	m_edit.Create(m_hWnd);
	SendMessage(m_edit, EM_SETLIMITTEXT, 5, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT | ES_NUMBER);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(GetWidth(), 0);
	m_edit.SetText(_T("100.0"));
	m_edit.SetSizeToTextSize();
	m_edit.Show(SW_SHOW);

	m_ud.Create(m_hWnd, m_edit);
	SendMessage(m_ud, UDM_SETPOS32, 0, 1000);
	SendMessage(m_ud, UDM_SETRANGE32, 0, 1000);
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
	SetVolume(100.0);

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CVolumeLabel_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VOLUME))
		return CStatic::GetHeight();
	else return m_rMainWnd.GetDivider3().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CVolumeLabel_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VOLUME))
		return CStatic::GetTop();
	else return m_rMainWnd.GetDivider3().GetTop();
}
//----------------------------------------------------------------------------
// 表示する周波数を表示
//----------------------------------------------------------------------------
void CVolumeLabel_MainWnd::SetVolume(double nVolume)
{
	TCHAR text[17];
	_stprintf_s(text, _T("%3.1f"), nVolume);
	m_edit.SetText(text);
	InvalidateRect(NULL, TRUE);
	SendMessage(m_ud, UDM_SETPOS32, 0, (int)(nVolume * 10.0));
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CVolumeLabel_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetDivider3().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = m_rMainWnd.GetControlOffset();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y + m_rMainWnd.GetDivider3().GetHeight()
		+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CVolumeLabel_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			double n = (double)_tstof(m_edit.GetText().c_str());
			if(0.0 <= n && n <= 100.0) {
				m_rMainWnd.GetVolumeSlider().SetThumbPos((LONG)(n * 10.0),
														 TRUE);
				m_rMainWnd.SetVolume(n);
				SendMessage(m_ud, UDM_SETPOS32, 0, (LONG)(n * 10.0));
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(m_edit.GetText().c_str());
			if(n < 0.0) n = 0.0;
			else if(n > 100.0) n = 100.0;
			SetVolume(n);
			m_rMainWnd.GetVolumeSlider().SetThumbPos((LONG)(n * 10.0), TRUE);
			m_rMainWnd.SetVolume(n);
		}
	}
	else m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CVolumeLabel_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
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
void CVolumeLabel_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	SetVolume((double)(pos / 10.0));
	PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
	PostMessage(m_edit, EM_SETSEL, 0, -1);

	CStatic::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
