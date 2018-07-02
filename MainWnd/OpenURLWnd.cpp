//----------------------------------------------------------------------------
// OpenURLWnd.cpp : 「URLを開く」用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "OpenURLWnd.h"
#include "PlayListView_MainWnd.h"
#include "Sound.h"
#include "Tab_MainWnd.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEdit_OpenURL::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) m_rMainWnd.GetOpenURLWnd().OpenURL();
	else if(vk == VK_ESCAPE) m_rMainWnd.GetOpenURLWnd().Close();
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL COpenURLWnd::Create(BOOL bAdd)
{
	Destroy();

	RegisterClass(_T("OpenURLWndCls"));

#if JP
	tstring strTitle = bAdd ? _T("URLを追加") : _T("URLを開く");
#else // JP
	tstring strTitle = bAdd ? _T("Add URL") : _T("Open URL");
#endif // JP

	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("OpenURLWndCls"),
							strTitle.c_str(),
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void COpenURLWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		OpenURL();
		break;
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT COpenURLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(320, 60, FALSE);

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

	if(!m_edit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 1024, 0);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(10, 10);
	m_edit.SetText(_T("http://xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T("http://"));
	m_edit.Show(SW_SHOW);

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
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_OkButton.SetPos(GetClientWidth() - 10 - m_OkButton.GetWidth(), pt.y + 20);

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	SetFocus(m_edit);
	PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
	PostMessage(m_edit, EM_SETSEL, 0, -1);

	Show(SW_SHOW);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow(m_hWnd);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void COpenURLWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// URLを開く
//----------------------------------------------------------------------------
void COpenURLWnd::OpenURL()
{
	tstring strTitle = GetCaption();
	tstring strURL = m_edit.GetText();

	int nSelect = m_rMainWnd.GetTab().GetCurrentFocus();
	m_rMainWnd.ChangeCurPlayTab();
#if JP
	if(strTitle == _T("URLを開く"))
		m_rMainWnd.GetPlayList().DeleteAllItems();
#else // JP
	if(strTitle == _T("Open URL"))
		m_rMainWnd.GetPlayList().DeleteAllItems();
#endif // JP
	m_rMainWnd.GetPlayList().AddFile(strURL.c_str());

	if(m_rMainWnd.GetPlayList().GetItemCount() <= 0) {
		m_rMainWnd.GetSound().StreamFree();
		m_rMainWnd.Stop();
	}
	else {
		m_rMainWnd.GetSound().SetCurFileNum(0);
		m_rMainWnd.PlayNext(TRUE, TRUE);
	}

	m_rMainWnd.SetPreviousNextMenuState();
	m_rMainWnd.StartUpdateInfo();

	Close();
}
//----------------------------------------------------------------------------
