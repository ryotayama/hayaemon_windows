//----------------------------------------------------------------------------
// PlayRangeWnd.cpp : 再生範囲設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "PlayRangeWnd.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEdit_PlayRange::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) m_rMainWnd.GetPlayRangeWnd().SetRange();
	else if(vk == VK_ESCAPE) m_rMainWnd.GetPlayRangeWnd().Close();
	else if(vk == VK_TAB) m_rMainWnd.GetPlayRangeWnd().SetNextFocus();
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPlayRangeWnd::Create()
{
	Destroy();

	RegisterClass(_T("PlayRangeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("PlayRangeWndCls"),
#if JP
							_T("再生範囲設定"),
#else // JP
							_T("Play position setting"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CPlayRangeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		SetRange();
		break;
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CPlayRangeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(240, 60, FALSE);

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

	if(!m_editStart.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_editStart, EM_SETLIMITTEXT, 8, 0);
	m_editStart.SetStyle(m_editStart.GetStyle() | ES_RIGHT);
	m_editStart.SetFont(m_font, TRUE);
	m_editStart.SetPos(10, 10);
	m_editStart.SetText(_T("88:88:88:88"));
	m_editStart.SetSizeToTextSize();
	m_editStart.SetText(_T(""));
	m_editStart.Show(SW_SHOW);

	// 「～」ラベルの作成
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
	m_label.SetText(_T("～"));
	m_label.SetSizeToTextSize();
	m_label.SetPos(10 + m_editStart.GetWidth() + 10, 10);
	m_label.Show(SW_SHOW);

	if(!m_editEnd.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_editEnd, EM_SETLIMITTEXT, 8, 0);
	m_editEnd.SetStyle(m_editEnd.GetStyle() | ES_RIGHT);
	m_editEnd.SetFont(m_font, TRUE);
	m_editEnd.SetPos(10 + m_editStart.GetWidth() + 10 + m_label.GetWidth() + 10,
		10);
	m_editEnd.SetText(_T("88:88:88:88"));
	m_editEnd.SetSizeToTextSize();
	m_editEnd.SetText(_T(""));
	m_editEnd.Show(SW_SHOW);

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
	POINT pt;
	pt.y = m_editStart.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_OkButton.SetPos(GetClientWidth() - 10 - m_OkButton.GetWidth(), pt.y + 20);

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	SetFocus(m_editStart);

	Show(SW_SHOW);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow(m_hWnd);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CPlayRangeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// フォーカスの変更
//----------------------------------------------------------------------------
void CPlayRangeWnd::SetNextFocus()
{
	HWND hWnd = GetFocus();
	HWND hFocusWnd;
	if(hWnd == m_editStart) hFocusWnd = m_editEnd;
	else hFocusWnd = m_editStart;
	SetFocus(hFocusWnd);
	PostMessage(hFocusWnd, WM_LBUTTONUP, 0, 0);
	PostMessage(hFocusWnd, EM_SETSEL, 0, -1);
}
//----------------------------------------------------------------------------
// 再生範囲の設定
//----------------------------------------------------------------------------
void CPlayRangeWnd::SetRange()
{
	tstring strTime = m_editStart.GetText();
	unsigned int n = 0;
	while((n = strTime.find(_T(":"), 0)) != tstring::npos)
		strTime.replace(n, 1, _T(""));
	int nHour = 0, nMinute = 0, nSecond = 0;
	if(strTime.length() == 6) {
		nHour = _ttoi(strTime.substr(0, 2).c_str());
		nMinute = _ttoi(strTime.substr(2, 2).c_str());
		nSecond = _ttoi(strTime.substr(4, 2).c_str());
	}
	else if(strTime.length() == 5) {
		nHour = _ttoi(strTime.substr(0, 1).c_str());
		nMinute = _ttoi(strTime.substr(1, 2).c_str());
		nSecond = _ttoi(strTime.substr(3, 2).c_str());
	}
	else if(strTime.length() == 4) {
		nMinute = _ttoi(strTime.substr(0, 2).c_str());
		nSecond = _ttoi(strTime.substr(2, 2).c_str());
	}
	else if(strTime.length() == 3) {
		nMinute = _ttoi(strTime.substr(0, 1).c_str());
		nSecond = _ttoi(strTime.substr(1, 2).c_str());
	}
	else if(strTime.length() == 2) {
		nSecond = _ttoi(strTime.substr(0, 2).c_str());
	}
	else if(strTime.length() == 1) {
		nSecond = _ttoi(strTime.substr(0, 1).c_str());
	}
	int nStartSeconds = nHour * 3600 + nMinute * 60 + nSecond;

	strTime = m_editEnd.GetText();
	n = 0;
	while((n = strTime.find(_T(":"), 0)) != tstring::npos)
		strTime.replace(n, 1, _T(""));
	nHour = 0, nMinute = 0, nSecond = 0;
	if(strTime.length() == 6) {
		nHour = _ttoi(strTime.substr(0, 2).c_str());
		nMinute = _ttoi(strTime.substr(2, 2).c_str());
		nSecond = _ttoi(strTime.substr(4, 2).c_str());
	}
	else if(strTime.length() == 5) {
		nHour = _ttoi(strTime.substr(0, 1).c_str());
		nMinute = _ttoi(strTime.substr(1, 2).c_str());
		nSecond = _ttoi(strTime.substr(3, 2).c_str());
	}
	else if(strTime.length() == 4) {
		nMinute = _ttoi(strTime.substr(0, 2).c_str());
		nSecond = _ttoi(strTime.substr(2, 2).c_str());
	}
	else if(strTime.length() == 3) {
		nMinute = _ttoi(strTime.substr(0, 1).c_str());
		nSecond = _ttoi(strTime.substr(1, 2).c_str());
	}
	else if(strTime.length() == 2) {
		nSecond = _ttoi(strTime.substr(0, 2).c_str());
	}
	else if(strTime.length() == 1) {
		nSecond = _ttoi(strTime.substr(0, 1).c_str());
	}
	int nEndSeconds = nHour * 3600 + nMinute * 60 + nSecond;

	if(nStartSeconds == nEndSeconds) return;
	else if(nEndSeconds > nStartSeconds)
		m_rMainWnd.SetPlayRange(nStartSeconds, nEndSeconds);
	else
		m_rMainWnd.SetPlayRange(nEndSeconds, nStartSeconds);

	Close();
}
//----------------------------------------------------------------------------
