//----------------------------------------------------------------------------
// OutKeySettingWnd_MainWnd.cpp : グローバルホットキーカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "OutKeySettingWnd_MainWnd.h"
#include "../Common/AcceleratorTable.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL COutKeySettingWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("OutKeySettingWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("OutKeySettingWndCls"),
#if JP
							_T("グローバルホットキー設定"),
#else // JP
							_T("Global hot key setting"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// 次のコントロールにフォーカス
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_AddButton);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_ChangeButton);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_DeleteButton);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_List);
			m_nFocus = 0;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 4;
			break;
		case 1:
			SetFocus((HWND)m_List);
			m_nFocus = 0;
			break;
		case 2:
			SetFocus((HWND)m_AddButton);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_ChangeButton);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_DeleteButton);
			m_nFocus = 3;
			break;
	}
}
//----------------------------------------------------------------------------
// フォーカス中のボタン機能を実行
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::ExecCurrentButtonFunc()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 1:
			OnAddButtonClicked();
			break;
		case 2:
			OnChangeButtonClicked();
			break;
		case 3:
			OnDeleteButtonClicked();
			break;
		case 4:
			OnOkButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_ADD:
		OnAddButtonClicked();
		break;
	case ID_CHANGE:
		OnChangeButtonClicked();
		break;
	case ID_DELETE:
		OnDeleteButtonClicked();
		break;
	case ID_OK:
		OnOkButtonClicked();
		break;
	}
}
//----------------------------------------------------------------------------
// 追加ボタンが押された
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnAddButtonClicked()
{
	if(!m_outKeyInputWnd.Create(TRUE)) {
#if JP
		m_rApp.ShowError(_T("グローバルホットキー入力ダイアログの作成に")
						 _T("失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create global hot key input dialog"));
#endif // JP
	}
	m_outKeyInputWnd.Show(SW_SHOW);
	m_outKeyInputWnd.Update();
}
//----------------------------------------------------------------------------
// 変更ボタンが押された
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnChangeButtonClicked()
{
	int nItem = -1;
	int nCount = 0;
	while((nItem = m_List.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
		nCount++;
	if(nCount == 1) {
		if(!m_outKeyInputWnd.Create(FALSE)) {
#if JP
			m_rApp.ShowError(_T("グローバルホットキー入力ダイアログの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create global hot key input ")
							 _T("dialog."));
#endif // JP
		}

		TCHAR szShortCut[255];
		m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 0,
						   szShortCut, 255);
		tstring strShortCut = szShortCut;
		UINT bfMods = 0;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos)
			bfMods |= HOTKEYF_CONTROL;
		if(strShortCut.find(_T("Alt")) != tstring::npos)
			bfMods |= HOTKEYF_ALT;
		if(strShortCut.find(_T("Shift")) != tstring::npos)
			bfMods |= HOTKEYF_SHIFT;
		UINT key = 0;
		if(strShortCut.rfind(_T("+"), strShortCut.length() - 2)
			!= tstring::npos)
			key = m_rApp.GetAccelTable().GetKeyFromString(
				strShortCut.substr(strShortCut.rfind(_T("+"),
				strShortCut.length() - 2) + 2));
		else
			key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.c_str());

		if (IS_EXTKEY(key))
			bfMods |= HOTKEYF_EXT;

		SendMessage((HWND)m_outKeyInputWnd.GetHotKeyCtrl(), HKM_SETHOTKEY,
					MAKEWORD(key, bfMods), 0);

		TCHAR szCommand[255];
		m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 1, szCommand,
						   255);
		m_outKeyInputWnd.GetComboBox().Select(szCommand);

		m_outKeyInputWnd.Show(SW_SHOW);
		m_outKeyInputWnd.Update();
	}
}
//----------------------------------------------------------------------------
// 削除ボタンが押された
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnDeleteButtonClicked()
{
	int nItem = -1;
	while((nItem = m_List.GetNextItem(-1, LVNI_SELECTED)) >= 0)
		m_List.DeleteItem(nItem);
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnOkButtonClicked()
{
	for (int i = 0; m_CmdList[i].div != DIV_TERMINAL; i++) {
		if (m_CmdList[i].use & CMD_HOTKEY)
			UnregisterHotKey(m_rMainWnd, m_CmdList[i].id);
	}
	for(int i = 0; i < m_List.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		m_List.GetItemText(i, 0, szShortCut, 255);
		tstring strShortCut = szShortCut;
		BYTE fVirt = 0;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos)
			fVirt |= MOD_CONTROL;
		if(strShortCut.find(_T("Alt")) != tstring::npos)
			fVirt |= MOD_ALT;
		if(strShortCut.find(_T("Shift")) != tstring::npos)
			fVirt |= MOD_SHIFT;
		UINT key = 0;
		if(strShortCut.rfind(_T("+"), strShortCut.length() - 2)
		   != tstring::npos)
			key = m_rApp.GetAccelTable().GetKeyFromString(
				strShortCut.substr(strShortCut.rfind(_T("+"),
				strShortCut.length() - 2) + 2));
		else
			key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.c_str());

		TCHAR szCommand[255];
		m_List.GetItemText(i, 1, szCommand, 255);
		WORD cmd = m_CmdList.GetCommandId(szCommand);
		RegisterHotKey(m_rMainWnd, cmd, fVirt, key);
	}
	Close();
}
//----------------------------------------------------------------------------
// 閉じる
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::Close()
{
	Show(SW_HIDE);
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT COutKeySettingWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(320, 200, FALSE);

	// 不要なシステムメニューを削除
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // セパレータ

	EnableWindow(m_rMainWnd, FALSE);

	if(!m_List.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("リストビューの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create list view."));
#endif // JP
		return FALSE;
	}
	m_List.SetPos(10, 10);
	m_List.SetSize(GetClientWidth() - 20, 140);
#if JP
	m_List.InsertColumn(0, _T("ショートカットキー"), LVCFMT_LEFT, 125, 0);
	m_List.InsertColumn(1, _T("アクション"), LVCFMT_LEFT, 150, 0);
#else // JP
	m_List.InsertColumn(0, _T("Shortcut key"), LVCFMT_LEFT, 125, 0);
	m_List.InsertColumn(1, _T("Action"), LVCFMT_LEFT, 150, 0);
#endif // JP
	m_List.Show(SW_SHOW);

	// 削除ボタンの作成
	if(!m_DeleteButton.Create(
#if JP
							  _T("削除"),
#else // JP
							  _T("Delete"),
#endif // JP
							  m_hWnd, ID_DELETE)) {
#if JP
		m_rApp.ShowError(_T("削除ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create delete button."));
#endif // JP
		return FALSE;
	}
	m_DeleteButton.SetSizeToTextSize();
	POINT pt;
	pt.y = m_List.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_DeleteButton.SetPos(GetClientWidth() - 10 - m_DeleteButton.GetWidth(),
						  pt.y + 10);

	// 変更ボタンの作成
	if(!m_ChangeButton.Create(
#if JP
							  _T("変更"),
#else // JP
							  _T("Change"),
#endif // JP
							  m_hWnd, ID_CHANGE)) {
#if JP
		m_rApp.ShowError(_T("変更ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create change button."));
#endif // JP
		return FALSE;
	}
	m_ChangeButton.SetSizeToTextSize();
	m_ChangeButton.SetPos(m_DeleteButton.GetLeft() - 5 -
						  m_ChangeButton.GetWidth(), m_DeleteButton.GetTop());

	// 追加ボタンの作成
	if(!m_AddButton.Create(
#if JP
						   _T("追加"),
#else // JP
						   _T("Add"),
#endif // JP
						   m_hWnd, ID_ADD)) {
#if JP
		m_rApp.ShowError(_T("追加ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create add button."));
#endif // JP
		return FALSE;
	}
	m_AddButton.SetSizeToTextSize();
	m_AddButton.SetPos(m_ChangeButton.GetLeft() - 5 - m_AddButton.GetWidth(),
					   m_DeleteButton.GetTop());

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
	m_OkButton.SetPos(GetClientWidth() - 10 - m_OkButton.GetWidth(),
					  m_AddButton.GetBottom() + 20);

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
