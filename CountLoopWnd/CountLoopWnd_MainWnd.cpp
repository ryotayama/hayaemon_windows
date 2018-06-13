//----------------------------------------------------------------------------
// CountLoopWnd_MainWnd.cpp : 回数ループウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "CountLoopWnd_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CCountLoopWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("CountLoopWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("CountLoopWndCls"),
#if JP
							_T("回数ループ"),
#else // JP
							_T("Count loop"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	nFocus = 0;

	return TRUE;
}
//----------------------------------------------------------------------------
// 次のコントロールにフォーカス
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::SetNextFocus()
{
	switch(nFocus)
	{
		case 0:
			SetFocus((HWND)m_edit);
			nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_OkButton);
			nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_CancelButton);
			nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_edit);
			nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::SetPreviousFocus()
{
	switch(nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			nFocus = 3;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			nFocus = 3;
			break;
		case 2:
			SetFocus((HWND)m_edit);
			nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_OkButton);
			nFocus = 2;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_edit) {
		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			return;
		}
	}

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
void CCountLoopWnd_MainWnd::OnOkButtonClicked()
{
	int nCount = _ttoi(m_edit.GetText().c_str());
	m_rMainWnd.SetCountLoop(nCount);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetCountLoop(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnReturnKeyPressed()
{
	switch(nFocus)
	{
		case 0:
		case 1:
		case 2:
			OnOkButtonClicked();
			break;
		case 3:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnSpaceKeyPressed()
{
	switch(nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 2:
			OnOkButtonClicked();
			break;
		case 3:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetCountLoop(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CCountLoopWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_label.SetPos(10, 10);
#if JP
	m_label.SetText(_T("マーカー間を"));
#else // JP
	m_label.SetText(_T("Play"));
#endif // JP
	m_label.SetSizeToTextSize();
	m_label.Show(SW_SHOW);

	if(!m_edit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 4, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(10 + m_label.GetWidth() + 10, 10);
	m_edit.SetText(_T("8888"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T("2"));
	m_edit.Show(SW_SHOW);

	if(!m_ud.Create(m_hWnd, m_edit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failtd to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ud, UDM_SETPOS32, 0, 1);
	SendMessage(m_ud, UDM_SETRANGE32, 0, 9999);
	m_ud.Show(SW_SHOW);
	m_edit.SetSize(m_edit.GetWidth() + m_ud.GetWidth(), m_edit.GetHeight());
	m_ud.SetPos(10 + m_label.GetWidth() + 10 + m_edit.GetWidth(), 10);

	if(!m_label2.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failtd to create label."));
#endif // JP
		return FALSE;
	}
	m_label2.SetParent(m_hWnd);
	m_label2.SetFont(m_font, TRUE);
	m_label2.SetPos(10 + m_label.GetWidth() + 10 + m_edit.GetWidth() + m_ud.GetWidth() + 10, 10);
#if JP
	m_label2.SetText(_T("回ずつ再生する"));
#else // JP
	m_label2.SetText(_T("count between markers."));
#endif // JP
	m_label2.SetSizeToTextSize();
	m_label2.Show(SW_SHOW);

	// キャンセルボタンの作成
#if JP
	if(!m_CancelButton.Create(_T("キャンセル"), m_hWnd, ID_CANCEL)) {
		m_rApp.ShowError(_T("キャンセルボタンの作成に失敗しました。"));
#else // JP
	if(!m_CancelButton.Create(_T("Cancel"), m_hWnd, ID_CANCEL)) {
		m_rApp.ShowError(_T("failed to create cancel button."));
#endif // JP
		return FALSE;
	}
	m_CancelButton.SetSize(90, 20);
	POINT pt;
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_CancelButton.SetPos(GetClientWidth() - 10 - m_CancelButton.GetWidth(), pt.y + 30);

	// OKボタンの作成
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(90, 20);
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(), m_CancelButton.GetTop());
	SetClientSize(GetClientWidth(), m_OkButton.GetTop() + m_OkButton.GetHeight() + 10, FALSE);

	SetNextFocus();

	Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	if(hwndCtl == (HWND)m_ud) {
		TCHAR text[5];
		_stprintf_s(text, _T("%2d"), pos);
		m_edit.SetText(text);
		PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_edit, EM_SETSEL, 0, -1);
	}
	CFrameWnd::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
