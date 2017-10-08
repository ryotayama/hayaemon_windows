//----------------------------------------------------------------------------
// TimerPlayWnd_MainWnd.cpp : タイマー再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "TimerPlayWnd_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTimerPlayWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("TimerPlayWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("TimerPlayWndCls"),
#if JP
							_T("タイマー設定"),
#else // JP
							_T("Timer setting"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// コントロールの有効・無効の設定
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::EnableControl(BOOL bPlayEnable, BOOL bStopEnable)
{
	EnableWindow(m_label, bPlayEnable);
	EnableWindow(m_label2, bPlayEnable);
	EnableWindow(m_edit, bPlayEnable);
	EnableWindow(m_edit2, bPlayEnable);
	EnableWindow(m_ud, bPlayEnable);
	EnableWindow(m_ud2, bPlayEnable);

	EnableWindow(m_label3, bStopEnable);
	EnableWindow(m_label4, bStopEnable);
	EnableWindow(m_edit3, bStopEnable);
	EnableWindow(m_edit4, bStopEnable);
	EnableWindow(m_ud3, bStopEnable);
	EnableWindow(m_ud4, bStopEnable);
}
//----------------------------------------------------------------------------
// 次のコントロールにフォーカス
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::SetNextFocus()
{
	switch(nFocus)
	{
		case 0:
			SetFocus((HWND)m_edit);
			nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_edit2);
			nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_OkButton);
			nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_CancelButton);
			nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_edit);
			nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::SetPreviousFocus()
{
	switch(nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			nFocus = 4;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			nFocus = 4;
			break;
		case 2:
			SetFocus((HWND)m_edit);
			nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_edit2);
			nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_OkButton);
			nFocus = 3;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit || hwndCtl == m_edit2) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			return;
		}
	}
	else if(hwndCtl == m_playRadioButton) EnableControl(TRUE, FALSE);
	else if(hwndCtl == m_stopRadioButton) EnableControl(FALSE, TRUE);

	switch(id)
	{
	case ID_OK:
		OnOkButtonClicked();
		break;
	case ID_CANCEL:
		OnCancelButtonClicked();
		break;
	}
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnOkButtonClicked()
{
	if(SendMessage(m_playRadioButton, BM_GETCHECK, 0, 0)) {
		int nHour = _ttoi(m_edit.GetText().c_str());
		int nMinute = _ttoi(m_edit2.GetText().c_str());
		m_rMainWnd.SetTimerPlay(nHour, nMinute);
	}
	else {
		int nHour = _ttoi(m_edit3.GetText().c_str());
		int nMinute = _ttoi(m_edit4.GetText().c_str());
		m_rMainWnd.SetTimerStop(nHour, nMinute);
	}
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetTimerPlay(FALSE);
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnReturnKeyPressed()
{
	switch(nFocus)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			OnOkButtonClicked();
			break;
		case 4:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnSpaceKeyPressed()
{
	switch(nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 3:
			OnOkButtonClicked();
			break;
		case 4:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetTimerPlay(FALSE);
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CTimerPlayWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(240, 200, FALSE);

	// 不要なシステムメニューを削除
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // セパレータ

	EnableWindow(m_rMainWnd, FALSE);

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	if(!m_playRadioButton.Create(
#if JP
								 _T("指定時間に再生"),
#else // JP
								 _T("Play at the set time"),
#endif // JP
								 0, 0, 0, 0, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("ラジオボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create radio button."));
#endif // JP
		return FALSE;
	}
	m_playRadioButton.SetFont(m_font, TRUE);
	m_playRadioButton.SetPos(10, 10);
	m_playRadioButton.SetSizeToTextSize();
	SendMessage((HWND)m_playRadioButton, BM_SETCHECK, 1, 0);

#ifndef JP
	if(!m_label2.Create()) {
		m_rApp.ShowError(_T("failed to create label."));
		return FALSE;
	}
	m_label2.SetParent(m_hWnd);
	m_label2.SetFont(m_font, TRUE);
	int nTop = 10 + m_playRadioButton.GetHeight() +
			   m_rMainWnd.GetControlOffset();
	m_label2.SetPos(30, nTop);
	m_label2.SetText(_T("Play at"));
	m_label2.SetSizeToTextSize();
	m_label2.Show(SW_SHOW);
#endif // JP

	if(!m_edit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 2, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
#if JP
	int nTop = 10 + m_playRadioButton.GetHeight() +
			   m_rMainWnd.GetControlOffset();
	m_edit.SetPos(30, nTop);
#else // JP
	m_edit.SetPos(30 + m_label2.GetWidth() + 5, nTop);
#endif // JP
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR szHour[3];
	_stprintf_s(szHour, _T("%02d"), st.wHour);
	m_edit.SetText(szHour);
	m_edit.SetSizeToTextSize();
	m_edit.Show(SW_SHOW);

	if(!m_ud.Create(m_hWnd, m_edit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ud, UDM_SETPOS32, 0, st.wHour);
	SendMessage(m_ud, UDM_SETRANGE32, 0, 23);
	m_ud.Show(SW_SHOW);
	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
#if JP
	m_ud.SetPos(30 + m_edit.GetWidth(), nTop);
#else // JP
	m_ud.SetPos(30 + m_label2.GetWidth() + 5 + m_edit.GetWidth(), nTop);
#endif // JP

	if(!m_label.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label.SetParent(m_hWnd);
	m_label.SetFont(m_font, TRUE);
#if JP
	m_label.SetPos(30 + m_edit.GetWidth() + m_ud.GetWidth() + 5, nTop);
#else // JP
	m_label.SetPos(30 + m_label2.GetWidth() + 5 + m_edit.GetWidth() + 
				   m_ud.GetWidth() + 5, nTop);
#endif // JP
	m_label.SetText(_T("："));
	m_label.SetSizeToTextSize();
	m_label.Show(SW_SHOW);

	if(!m_edit2.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit2, EM_SETLIMITTEXT, 2, 0);
	m_edit2.SetStyle(m_edit2.GetStyle() | ES_RIGHT);
	m_edit2.SetFont(m_font, TRUE);
#if JP
	m_edit2.SetPos(30 + m_edit.GetWidth() + m_ud.GetWidth() + 5 +
				   m_label.GetWidth() + 5, nTop);
#else // JP
	m_edit2.SetPos(30 + m_label2.GetWidth() + 5 + m_edit.GetWidth() +
				   m_ud.GetWidth() + 5 + m_label.GetWidth() + 5, nTop);
#endif // JP
	TCHAR szMinute[3];
	_stprintf_s(szMinute, _T("%02d"), st.wMinute);
	m_edit2.SetText(szMinute);
	m_edit2.SetSizeToTextSize();
	m_edit2.Show(SW_SHOW);

	if(!m_ud2.Create(m_hWnd, m_edit2)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ud2, UDM_SETPOS32, 0, st.wMinute);
	SendMessage(m_ud2, UDM_SETRANGE32, 0, 59);
	m_ud2.Show(SW_SHOW);
	m_edit2.SetSize(m_edit2.GetWidth() + m_ud2.GetWidth(),
					m_edit2.GetHeight());
#if JP
	m_ud2.SetPos(30 + m_edit.GetWidth() + m_ud.GetWidth() + 5 +
				 m_label.GetWidth() + 5 + m_edit2.GetWidth(), nTop);
#else // JP
	m_ud2.SetPos(30 + m_label2.GetWidth() + 5 + m_edit.GetWidth() + 
				 m_ud.GetWidth() + 5 + m_label.GetWidth() + 5 + 
				 m_edit2.GetWidth(), nTop);
#endif // JP

#if JP
	if(!m_label2.Create()) {
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
		return FALSE;
	}
	m_label2.SetParent(m_hWnd);
	m_label2.SetFont(m_font, TRUE);
	m_label2.SetPos(30 + m_edit.GetWidth() + m_ud.GetWidth() + 5 +
					m_label.GetWidth() + 5 + m_edit2.GetWidth() +
					m_ud2.GetWidth() + 10, nTop);
	m_label2.SetText(_T("に再生開始"));
	m_label2.SetSizeToTextSize();
	m_label2.Show(SW_SHOW);
#endif // JP

	if(!m_stopRadioButton.Create(
#if JP
								 _T("指定時間に停止"),
#else // JP
								 _T("Stop at the set time"),
#endif // JP
								 0, 0, 0, 0, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("ラジオボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create radio button."));
#endif // JP
		return FALSE;
	}
	m_stopRadioButton.SetFont(m_font, TRUE);
	POINT pt;
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_stopRadioButton.SetPos(10, pt.y + m_rMainWnd.GetControlOffset());
	m_stopRadioButton.SetSizeToTextSize();

#ifndef JP
	if(!m_label4.Create()) {
		MessageBox(m_hWnd, _T("failed to create label.")
					_T("Application exit."), _T("Error"), MB_ICONERROR);
		m_rMainWnd.Destroy();
		return FALSE;
	}
	m_label4.SetParent(m_hWnd);
	m_label4.SetFont(m_font, TRUE);
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	nTop = pt.y + m_rMainWnd.GetControlOffset() + m_stopRadioButton.GetHeight()
		   + m_rMainWnd.GetControlOffset();
	m_label4.SetPos(30, nTop);
	m_label4.SetText(_T("Stop at"));
	m_label4.SetSizeToTextSize();
	m_label4.Show(SW_SHOW);
#endif // JP

	if(!m_edit3.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit3, EM_SETLIMITTEXT, 2, 0);
	m_edit3.SetStyle(m_edit3.GetStyle() | ES_RIGHT);
	m_edit3.SetFont(m_font, TRUE);
#if JP
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	nTop = pt.y + m_rMainWnd.GetControlOffset() + m_stopRadioButton.GetHeight()
		   + m_rMainWnd.GetControlOffset();
	m_edit3.SetPos(30, nTop);
#else // JP
	m_edit3.SetPos(30 + m_label4.GetWidth() + 5, nTop);
#endif // JP
	m_edit3.SetText(szHour);
	m_edit3.SetSizeToTextSize();
	m_edit3.Show(SW_SHOW);

	if(!m_ud3.Create(m_hWnd, m_edit3)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ud3, UDM_SETPOS32, 0, st.wHour);
	SendMessage(m_ud3, UDM_SETRANGE32, 0, 23);
	m_ud3.Show(SW_SHOW);
	m_edit3.SetSize(m_edit3.GetWidth() + m_ud3.GetWidth(),
					m_edit3.GetHeight());
#if JP
	m_ud3.SetPos(30 + m_edit3.GetWidth(), nTop);
#else // JP
	m_ud3.SetPos(30 + m_label4.GetWidth() + 5 + m_edit3.GetWidth(), nTop);
#endif // JP

	if(!m_label3.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label3.SetParent(m_hWnd);
	m_label3.SetFont(m_font, TRUE);
#if JP
	m_label3.SetPos(30 + m_edit3.GetWidth() + m_ud3.GetWidth() + 5, nTop);
#else // JP
	m_label3.SetPos(30 + m_label4.GetWidth() + 5 + m_edit3.GetWidth() +
					m_ud3.GetWidth() + 5, nTop);
#endif // JP
	m_label3.SetText(_T("："));
	m_label3.SetSizeToTextSize();
	m_label3.Show(SW_SHOW);

	if(!m_edit4.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit4, EM_SETLIMITTEXT, 2, 0);
	m_edit4.SetStyle(m_edit4.GetStyle() | ES_RIGHT);
	m_edit4.SetFont(m_font, TRUE);
#if JP
	m_edit4.SetPos(30 + m_edit3.GetWidth() + m_ud3.GetWidth() + 5 +
				   m_label3.GetWidth() + 5, nTop);
#else // JP
	m_edit4.SetPos(30 + m_label4.GetWidth() + 5 + m_edit3.GetWidth() +
				   m_ud3.GetWidth() + 5 + m_label3.GetWidth() + 5, nTop);
#endif // JP
	m_edit4.SetText(szMinute);
	m_edit4.SetSizeToTextSize();
	m_edit4.Show(SW_SHOW);

	if(!m_ud4.Create(m_hWnd, m_edit4)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ud4, UDM_SETPOS32, 0, st.wMinute);
	SendMessage(m_ud4, UDM_SETRANGE32, 0, 59);
	m_ud4.Show(SW_SHOW);
	m_edit4.SetSize(m_edit4.GetWidth() + m_ud4.GetWidth(),
					m_edit4.GetHeight());
#if JP
	m_ud4.SetPos(30 + m_edit3.GetWidth() + m_ud3.GetWidth() + 5 +
				 m_label3.GetWidth() + 5 + m_edit4.GetWidth(), nTop);
#else // JP
	m_ud4.SetPos(30 + m_label4.GetWidth() + 5 + m_edit3.GetWidth() +
				 m_ud3.GetWidth() + 5 + m_label3.GetWidth() + 5 +
				 m_edit4.GetWidth(), nTop);
#endif // JP

#if JP
	if(!m_label4.Create()) {
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
		return FALSE;
	}
	m_label4.SetParent(m_hWnd);
	m_label4.SetFont(m_font, TRUE);
	m_label4.SetPos(30 + m_edit3.GetWidth() + m_ud3.GetWidth() + 5 +
					m_label3.GetWidth() + 5 + m_edit4.GetWidth() +
					m_ud4.GetWidth() + 10, nTop);
	m_label4.SetText(_T("に停止"));
	m_label4.SetSizeToTextSize();
	m_label4.Show(SW_SHOW);
#endif // JP

	// キャンセルボタンの作成
	if(!m_CancelButton.Create(
#if JP
							  _T("キャンセル"),
#else // JP
							  _T("Cancel"),
#endif // JP
							  m_hWnd, ID_CANCEL)) {
#if JP
		m_rApp.ShowError(_T("キャンセルボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create cancel button."));
#endif // JP
		return FALSE;
	}
	m_CancelButton.SetSize(90, 20);
	pt.y = m_edit3.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_CancelButton.SetPos(GetClientWidth() - 10 - m_CancelButton.GetWidth(), pt.y + 30);

	// OKボタンの作成
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
		return FALSE;
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
	}
	m_OkButton.SetSize(90, 20);
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(),
					  m_CancelButton.GetTop());
	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	SetNextFocus();

	EnableControl(TRUE, FALSE);

	Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	if(hwndCtl == (HWND)m_ud) {
		TCHAR text[3];
		_stprintf_s(text, _T("%02d"), pos);
		m_edit.SetText(text);
		PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit, EM_SETSEL, 0, -1);
	}
	if(hwndCtl == (HWND)m_ud2) {
		TCHAR text[3];
		_stprintf_s(text, _T("%02d"), pos);
		m_edit2.SetText(text);
		PostMessage(m_edit2, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit2, EM_SETSEL, 0, -1);
	}
	if(hwndCtl == (HWND)m_ud3) {
		TCHAR text[3];
		_stprintf_s(text, _T("%02d"), pos);
		m_edit3.SetText(text);
		PostMessage(m_edit3, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit3, EM_SETSEL, 0, -1);
	}
	if(hwndCtl == (HWND)m_ud4) {
		TCHAR text[3];
		_stprintf_s(text, _T("%02d"), pos);
		m_edit4.SetText(text);
		PostMessage(m_edit4, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit4, EM_SETSEL, 0, -1);
	}

	CFrameWnd::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0)
			SetPreviousFocus();
		else
			SetNextFocus();
		break;
	case VK_RETURN:
		OnReturnKeyPressed();
		break;
	case VK_SPACE:
		OnSpaceKeyPressed();
		break;
	case VK_ESCAPE:
		OnEscKeyPressed();
		break;
	}
	CFrameWnd::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
