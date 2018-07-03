//----------------------------------------------------------------------------
// PanLabel_MainWnd.cpp : パン表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../App.h"
#include "../Common/CommandList.h"
#include "EQ12_5KLabel_MainWnd.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "PanLabel_MainWnd.h"
#include "PanSlider_MainWnd.h"
#include "VolumeLabel_MainWnd.h"
#include "VolumeSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPanLabel_MainWnd::Create()
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

#if JP
	SetText(_T("パン : "));
#else // JP
	SetText(_T("Pan : "));
#endif // JP
	SetSizeToTextSize();

	m_edit.Create(m_hWnd);
	SendMessage(m_edit, EM_SETLIMITTEXT, 4, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetText(_T("-100"));
	m_edit.SetSizeToTextSize();
	POINT pt;
	pt.x = m_rMainWnd.GetEQ12_5KLabel().GetEdit().GetRight();
	ScreenToClient(m_rMainWnd.GetEQ12_5KLabel(), &pt);
	pt.x -= m_edit.GetWidth();
	m_edit.SetPos(pt.x, 0);
	m_edit.Show(SW_SHOW);

	m_ud.Create(m_hWnd, m_edit);
	SendMessage(m_ud, UDM_SETPOS32, 0, 0);
	SendMessage(m_ud, UDM_SETRANGE32, -100, 100);
	m_ud.Show(SW_SHOW);

	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	m_ud.SetPos(pt.x + m_edit.GetWidth(), 0);

	SetSize(pt.x + m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	SetPan(0);

	ResetPos();

	return TRUE;
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CPanLabel_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CStatic::GetHeight();
	else return m_rMainWnd.GetVolumeLabel().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CPanLabel_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CStatic::GetTop();
	else return m_rMainWnd.GetVolumeLabel().GetTop();
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CPanLabel_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetVolumeLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nVolumeLabelBottom = pt.y + m_rMainWnd.GetVolumeLabel().GetHeight() +
							 m_rMainWnd.GetControlOffset();
	pt.y = m_rMainWnd.GetVolumeSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nVolumeSliderBottom = pt.y + m_rMainWnd.GetVolumeSlider().GetHeight() +
							  m_rMainWnd.GetControlOffset();
	int nBigger = nVolumeLabelBottom > nVolumeSliderBottom ?
				  nVolumeLabelBottom : nVolumeSliderBottom;
	int nLeft = m_rMainWnd.GetControlOffset();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset();
	SetPos(nLeft, nBigger);
}
//----------------------------------------------------------------------------
// 表示するパンを表示
//----------------------------------------------------------------------------
void CPanLabel_MainWnd::SetPan(int nPan)
{
	TCHAR text[13];
	_stprintf_s(text, _T("%d"), nPan);
	m_edit.SetText(text);
	InvalidateRect(NULL, TRUE);
	SendMessage(m_ud, UDM_SETPOS32, 0, nPan);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CPanLabel_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
			PostMessage(m_edit, EM_SETSEL, 0, -1);
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			int n = _ttoi(m_edit.GetText().c_str());
			if(-100 <= n && n <= 100)
			{
				m_rMainWnd.GetPanSlider().SetThumbPos(n, TRUE);
				m_rMainWnd.SetPan(n);
				SendMessage(m_ud, UDM_SETPOS32, 0, n);
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			int n = _ttoi(m_edit.GetText().c_str());
			if(n < -100)
				n = -100;
			else if(n > 100)
				n = 100;
			SetPan(n);
			m_rMainWnd.GetPanSlider().SetThumbPos(n, TRUE);
			m_rMainWnd.SetPan(n);
		}
	}
	else m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CPanLabel_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
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
void CPanLabel_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	SetPan(pos);
	PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
	PostMessage(m_edit, EM_SETSEL, 0, -1);

	CStatic::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
