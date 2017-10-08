//----------------------------------------------------------------------------
// IncSpeedWnd_MainWnd.cpp : だんだん速くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "IncSpeedWnd_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CIncSpeedWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("IncSpeedWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("IncSpeedWndCls"),
#if JP
							_T("だんだん速くする"),
#else // JP
							_T("Increase speed"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	nFocus = 0;

	return TRUE;
}
//----------------------------------------------------------------------------
// コントロールの有効・無効の設定
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::EnableControl(BOOL bSecondEnable, BOOL bLoopEnable)
{
	EnableWindow(m_label, bSecondEnable);
	EnableWindow(m_label2, bSecondEnable);
	EnableWindow(m_label3, bSecondEnable);
	EnableWindow(m_edit, bSecondEnable);
	EnableWindow(m_edit2, bSecondEnable);
	EnableWindow(m_ud, bSecondEnable);
	EnableWindow(m_ud2, bSecondEnable);

	EnableWindow(m_label4, bLoopEnable);
	EnableWindow(m_label5, bLoopEnable);
	EnableWindow(m_label6, bLoopEnable);
	EnableWindow(m_edit3, bLoopEnable);
	EnableWindow(m_ud3, bLoopEnable);
}
//----------------------------------------------------------------------------
// 次のコントロールにフォーカス
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::SetNextFocus()
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
void CIncSpeedWnd_MainWnd::SetPreviousFocus()
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
void CIncSpeedWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit || hwndCtl == m_edit2 || hwndCtl == m_edit3) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			return;
		}
	}
	else if(hwndCtl == m_secondRadioButton)
		EnableControl(TRUE, FALSE);
	else if(hwndCtl == m_loopRadioButton)
		EnableControl(FALSE, TRUE);

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
void CIncSpeedWnd_MainWnd::OnOkButtonClicked()
{
	if(SendMessage(m_secondRadioButton, BM_GETCHECK, 0, 0)) {
		double nSecond = _ttof(m_edit.GetText().c_str());
		double nIncSpeed = _ttof(m_edit2.GetText().c_str());
		m_rMainWnd.SetIncSpeed(nSecond, nIncSpeed);
	}
	else {
		double nIncSpeed = _ttof(m_edit3.GetText().c_str());
		m_rMainWnd.SetIncSpeed(nIncSpeed);
	}
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetIncSpeed(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnReturnKeyPressed()
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
void CIncSpeedWnd_MainWnd::OnSpaceKeyPressed()
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
void CIncSpeedWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetIncSpeed(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CIncSpeedWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(360, 200, FALSE);

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

	if(!m_secondRadioButton.Create(
#if JP
								   _T("秒数ごとに変更"),
#else // JP
								   _T("changes for every number of the ")
								   _T("set-up seconds"),
#endif // JP
								   0, 0, 0, 0, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("ラジオボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create radio button."));
#endif // JP
		return FALSE;
	}
	m_secondRadioButton.SetFont(m_font, TRUE);
	m_secondRadioButton.SetPos(10, 10);
	m_secondRadioButton.SetSizeToTextSize();
	SendMessage((HWND)m_secondRadioButton, BM_SETCHECK, 1, 0);

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
	int nTop = 10 + m_secondRadioButton.GetHeight()
			   + m_rMainWnd.GetControlOffset();
	m_label.SetPos(30, nTop);
	m_label.SetText(strLabel.c_str());
	m_label.SetSizeToTextSize();
	m_label.Show(SW_SHOW);

#if JP
	if(!m_edit.Create(m_hWnd)) {
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 6, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(30 + m_label.GetWidth() + 10, nTop);
	m_edit.SetText(_T("888.88"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T("1.00"));
	m_edit.Show(SW_SHOW);

	if(!m_ud.Create(m_hWnd, m_edit)) {
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
		return FALSE;
	}
	SendMessage(m_ud, UDM_SETPOS32, 0, 100);
	SendMessage(m_ud, UDM_SETRANGE32, 0, 99999);
	m_ud.Show(SW_SHOW);
	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	m_ud.SetPos(30 + m_label.GetWidth() + 10 + m_edit.GetWidth(), nTop);

	if(!m_label2.Create()) {
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
		return FALSE;
	}
	m_label2.SetParent(m_hWnd);
	m_label2.SetFont(m_font, TRUE);
	m_label2.SetPos(30 + m_label.GetWidth() + 10 + m_edit.GetWidth()
					+ m_ud.GetWidth() + 10, nTop);
	m_label2.SetText(_T("秒間に"));
	m_label2.SetSizeToTextSize();
	m_label2.Show(SW_SHOW);

	if(!m_edit2.Create(m_hWnd)) {
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
		return FALSE;
	}
	SendMessage(m_edit2, EM_SETLIMITTEXT, 5, 0);
	m_edit2.SetStyle(m_edit2.GetStyle() | ES_RIGHT);
	m_edit2.SetFont(m_font, TRUE);
	m_edit2.SetPos(30 + m_label.GetWidth() + 10 + m_edit.GetWidth()
				   + m_ud.GetWidth() + 10 + m_label2.GetWidth() + 10, nTop);
	m_edit2.SetText(_T("888.8"));
	m_edit2.SetSizeToTextSize();
	m_edit2.SetText(_T("0.1"));
	m_edit2.Show(SW_SHOW);

	if(!m_ud2.Create(m_hWnd, m_edit2)) {
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
		return FALSE;
	}
	SendMessage(m_ud2, UDM_SETPOS32, 0, 1);
	SendMessage(m_ud2, UDM_SETRANGE32, 0, 9999);
	m_ud2.Show(SW_SHOW);
	m_edit2.SetSize(m_edit2.GetWidth() + m_ud2.GetWidth(), m_edit2.GetHeight());
	m_ud2.SetPos(30 + m_label.GetWidth() + 10 + m_edit.GetWidth()
				 + m_ud.GetWidth() + 10 + m_label2.GetWidth() + 10
				 + m_edit2.GetWidth(), nTop);
#else // JP
	if(!m_edit2.Create(m_hWnd)) {
		m_rApp.ShowError(_T("failed to create edit control."));
		return FALSE;
	}
	SendMessage(m_edit2, EM_SETLIMITTEXT, 5, 0);
	m_edit2.SetStyle(m_edit2.GetStyle() | ES_RIGHT);
	m_edit2.SetFont(m_font, TRUE);
	m_edit2.SetPos(30 + m_label.GetWidth() + 10, nTop);
	m_edit2.SetText(_T("888.8"));
	m_edit2.SetSizeToTextSize();
	m_edit2.SetText(_T("0.1"));
	m_edit2.Show(SW_SHOW);

	if(!m_ud2.Create(m_hWnd, m_edit2)) {
		m_rApp.ShowError(_T("failed to create up down control."));
		return FALSE;
	}
	SendMessage(m_ud2, UDM_SETPOS32, 0, 1);
	SendMessage(m_ud2, UDM_SETRANGE32, 0, 9999);
	m_ud2.Show(SW_SHOW);
	m_edit2.SetSize(m_edit2.GetWidth() + m_ud2.GetWidth(),
					m_edit2.GetHeight());
	m_ud2.SetPos(30 + m_label.GetWidth() + 10 + m_edit2.GetWidth(), nTop);

	if(!m_label2.Create()) {
		m_rApp.ShowError(_T("failed to create label."));
		return FALSE;
	}
	m_label2.SetParent(m_hWnd);
	m_label2.SetFont(m_font, TRUE);
	m_label2.SetPos(30 + m_label.GetWidth() + 10 + m_edit2.GetWidth()
					+ m_ud2.GetWidth() + 10, nTop);
	m_label2.SetText(_T("% in"));
	m_label2.SetSizeToTextSize();
	m_label2.Show(SW_SHOW);

	if(!m_edit.Create(m_hWnd)) {
		m_rApp.ShowError(_T("failed to create edit control."));
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 6, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(30 + m_label.GetWidth() + 10 + m_edit2.GetWidth()
				  + m_ud2.GetWidth() + 10 + m_label2.GetWidth() + 10, nTop);
	m_edit.SetText(_T("888.88"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T("1.00"));
	m_edit.Show(SW_SHOW);

	if(!m_ud.Create(m_hWnd, m_edit)) {
		m_rApp.ShowError(_T("failed to create up down control."));
		return FALSE;
	}
	SendMessage(m_ud, UDM_SETPOS32, 0, 100);
	SendMessage(m_ud, UDM_SETRANGE32, 0, 99999);
	m_ud.Show(SW_SHOW);
	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	m_ud.SetPos(30 + m_label.GetWidth() + 10 + m_edit2.GetWidth() +
				m_ud2.GetWidth() + 10 + m_label2.GetWidth() + 10 +
				m_edit.GetWidth(), nTop);
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
	m_label3.SetPos(30 + m_label.GetWidth() + 10 + m_edit.GetWidth() + 10
					+ m_ud.GetWidth() + 10 + m_label2.GetWidth() + 10
					+ m_edit2.GetWidth() + m_ud2.GetWidth(), nTop);
	m_label3.SetText((_T("% ") + strLabel2).c_str());
#else // JP
	m_label3.SetPos(30 + m_label.GetWidth() + 10 + m_edit2.GetWidth()
					+ m_ud2.GetWidth() + 10 + m_label2.GetWidth() + 10
					+ m_edit2.GetWidth() + m_ud2.GetWidth() + 10, nTop);
	m_label3.SetText(_T("seconds"));
#endif // JP
	m_label3.SetSizeToTextSize();
	m_label3.Show(SW_SHOW);

	if(!m_loopRadioButton.Create(
#if JP
								 _T("ループごとに変更"),
#else // JP
								 _T("changes for every looping"),
#endif // JP
								 0, 0, 0, 0, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("ラジオボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create radio button."));
#endif // JP
		return FALSE;
	}
	m_loopRadioButton.SetFont(m_font, TRUE);
	POINT pt;
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_loopRadioButton.SetPos(10, pt.y + m_rMainWnd.GetControlOffset());
	m_loopRadioButton.SetSizeToTextSize();

	if(!m_label4.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label4.SetParent(m_hWnd);
	m_label4.SetFont(m_font, TRUE);
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	nTop = pt.y + m_rMainWnd.GetControlOffset() + m_loopRadioButton.GetHeight()
		   + m_rMainWnd.GetControlOffset();
	m_label4.SetPos(30, nTop);
#if JP
	m_label4.SetText((_T("ループごとに") + strLabel).c_str());
#else // JP
	m_label4.SetText(strLabel.c_str());
#endif // JP
	m_label4.SetSizeToTextSize();
	m_label4.Show(SW_SHOW);

	if(!m_edit3.Create(m_hWnd))
	{
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control"));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit3, EM_SETLIMITTEXT, 5, 0);
	m_edit3.SetStyle(m_edit3.GetStyle() | ES_RIGHT);
	m_edit3.SetFont(m_font, TRUE);
	m_edit3.SetPos(30 + m_label4.GetWidth() + 10, nTop);
	m_edit3.SetText(_T("888.8"));
	m_edit3.SetSizeToTextSize();
	m_edit3.SetText(_T("0.1"));
	m_edit3.Show(SW_SHOW);

	if(!m_ud3.Create(m_hWnd, m_edit3)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ud3, UDM_SETPOS32, 0, 1);
	SendMessage(m_ud3, UDM_SETRANGE32, 0, 9999);
	m_ud3.Show(SW_SHOW);
	m_edit3.SetSize(m_edit3.GetWidth() + m_ud3.GetWidth(), m_edit3.GetHeight());
	m_ud3.SetPos(30 + m_label4.GetWidth() + 10 + m_edit3.GetWidth(), nTop);

	if(!m_label5.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label5.SetParent(m_hWnd);
	m_label5.SetFont(m_font, TRUE);
	m_label5.SetPos(30 + m_label4.GetWidth() + 10 + m_edit3.GetWidth()
					+ m_ud3.GetWidth() + 10, nTop);
#if JP
	m_label5.SetText((_T("% ") + strLabel2).c_str());
#else // JP
	m_label5.SetText(_T("% every looping"));
#endif // JP
	m_label5.SetSizeToTextSize();
	m_label5.Show(SW_SHOW);

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
	m_CancelButton.SetPos(GetClientWidth() - 10 - m_CancelButton.GetWidth(),
						  pt.y + m_loopRadioButton.GetHeight() + 60);

	// OKボタンの作成
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE))
	{
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(90, 20);
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(),
					  m_CancelButton.GetTop());
	SetClientSize(GetClientWidth(), m_OkButton.GetTop() + m_OkButton.GetHeight()
				  + 10, FALSE);

	SetNextFocus();

	EnableControl(TRUE, FALSE);

	Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	if(hwndCtl == (HWND)m_ud) {
		TCHAR text[18];
		_stprintf_s(text, _T("%3.2f"), pos / 100.0);
		m_edit.SetText(text);
		PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit, EM_SETSEL, 0, -1);
	}
	if(hwndCtl == (HWND)m_ud2) {
		TCHAR text[18];
		_stprintf_s(text, _T("%3.1f"), pos / 10.0);
		m_edit2.SetText(text);
		PostMessage(m_edit2, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit2, EM_SETSEL, 0, -1);
	}
	if(hwndCtl == (HWND)m_ud3) {
		TCHAR text[18];
		_stprintf_s(text, _T("%3.1f"), pos / 10.0);
		m_edit3.SetText(text);
		PostMessage(m_edit3, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit3, EM_SETSEL, 0, -1);
	}
	CFrameWnd::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
