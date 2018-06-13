//----------------------------------------------------------------------------
// PresetNameInputWnd.cpp : プリセット名入力ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "PresetNameInputWnd.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEdit_PresetNameInput::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) m_rMainWnd.GetPresetNameInputWnd().SetPreset();
	else if(vk == VK_ESCAPE) m_rMainWnd.GetPresetNameInputWnd().Close();
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPresetNameInputWnd::Create()
{
	Destroy();

	RegisterClass(_T("PresetNameInputWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("PresetNameInputWndCls"),
#if JP
							_T("プリセット名の入力"),
#else // JP
							_T("Input preset name"),
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
void CPresetNameInputWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		SetPreset();
		break;
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CPresetNameInputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(320, 240, FALSE);

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
	m_label.SetPos(10, 20);
#if JP
	m_label.SetText(_T("プリセット名 : "));
#else // JP
	m_label.SetText(_T("Preset Name : "));
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
	SendMessage(m_edit, EM_SETLIMITTEXT, 100, 0);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(10 + m_label.GetWidth() + 10, 20);
	m_edit.SetText(_T("１２３４５６７８９０１２３４５６７８９０１２３４５６"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T(""));
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
	m_OkButton.SetPos(GetClientWidth() - 10 - m_OkButton.GetWidth(), pt.y + 30);

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	SetFocus(m_edit);

	Show(SW_SHOW);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow(m_hWnd);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CPresetNameInputWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// プリセット名の設定
//----------------------------------------------------------------------------
void CPresetNameInputWnd::SetPreset()
{
	tstring strTime = m_edit.GetText();
	m_rMainWnd.AddPreset(strTime);
	Close();
}
//----------------------------------------------------------------------------
