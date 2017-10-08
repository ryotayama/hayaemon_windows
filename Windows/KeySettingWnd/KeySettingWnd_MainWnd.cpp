//----------------------------------------------------------------------------
// KeySettingWnd_MainWnd.cpp : キーカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "KeySettingWnd_MainWnd.h"
#include "../Common/AcceleratorTable.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CKeySettingWnd_MainWnd::CKeySettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_keyInputWnd(app, mainWnd, *this),
	  m_AddButton(*this), m_ChangeButton(*this), m_DeleteButton(*this),
	  m_DefaultButton(*this), m_OkButton(*this), m_CancelButton(*this),
	  m_List(*this), m_nFocus(0), m_CmdList()
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CKeySettingWnd_MainWnd::~CKeySettingWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// リストに追加する
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::AddList(UINT bVKHotKey, UINT bfMods, tstring strCommand)
{
	BYTE fVirt = FVIRTKEY;
	if(bfMods & HOTKEYF_CONTROL)
		fVirt |= FCONTROL;
	if(bfMods & HOTKEYF_ALT)
		fVirt |= FALT;
	if(bfMods & HOTKEYF_SHIFT)
		fVirt |= FSHIFT;
	tstring strAddShortCut = m_rApp.GetAccelTable().GetShortCut(fVirt,
																bVKHotKey);
	if(strAddShortCut == _T("")) return;

	for(int i = 0; i < m_List.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		m_List.GetItemText(i, 0, szShortCut, 255);
		tstring strShortCut = szShortCut;
		if(strAddShortCut == szShortCut) {
			tstring strMessage = strAddShortCut +
#if JP
				_T("は既に登録されています。\n\n既存の内容を置き換えますか？");
#else // JP
				_T("already exists.\n\nOverride?");
#endif // JP
			int nRet = MessageBox(m_hWnd, strMessage.c_str(),
#if JP
								  _T("確認"),
#else // JP
								  _T("Question"),
#endif // JP
								  MB_YESNO | MB_ICONQUESTION);
			if(nRet == IDYES) m_List.SetItem(i, 1, strCommand.c_str());
			return;
		}
	}

	int n = m_List.GetItemCount();
	m_List.InsertItem(n);
	m_List.SetItem(n, 0, strAddShortCut.c_str());
	m_List.SetItem(n, 1, strCommand.c_str());
}
//----------------------------------------------------------------------------
// リストを変更する
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::ChangeList(UINT bVKHotKey, UINT bfMods, tstring strCommand)
{
	int nItem = -1;
	int nCount = 0;
	while((nItem = m_List.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
		nCount++;
	if(nCount == 1) {
		int n = m_List.GetNextItem(-1, LVNI_SELECTED);
		BYTE fVirt = FVIRTKEY;
		if(bfMods & HOTKEYF_CONTROL) fVirt |= FCONTROL;
		if(bfMods & HOTKEYF_ALT) fVirt |= FALT;
		if(bfMods & HOTKEYF_SHIFT) fVirt |= FSHIFT;
		tstring strAddShortCut = m_rApp.GetAccelTable().GetShortCut(fVirt,
																	bVKHotKey);
		if(strAddShortCut == _T("")) return;

		for(int i = 0; i < m_List.GetItemCount(); i++) {
			TCHAR szShortCut[255];
			m_List.GetItemText(i, 0, szShortCut, 255);
			tstring strShortCut = szShortCut;
			if(strAddShortCut == szShortCut) {
				if(i == n) continue;
				tstring strMessage = strAddShortCut +
#if JP
				_T("は既に登録されています。\n\n既存の内容を置き換えますか？");
#else // JP
				_T("already exists.\n\nOverride?");
#endif // JP
				int nRet = MessageBox(m_hWnd, strMessage.c_str(),
#if JP
									  _T("確認"),
#else // JP
									  _T("Question"),
#endif // JP
									  MB_YESNO | MB_ICONQUESTION);
				if(nRet == IDNO) return;
				m_List.DeleteItem(i);
			}
		}
		m_List.SetItem(n, 0, strAddShortCut.c_str());
		m_List.SetItem(n, 1, strCommand.c_str());
	}
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CKeySettingWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("KeySettingWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("KeySettingWndCls"),
#if JP
							_T("ショートカットキー設定"),
#else // JP
							_T("Shortcut key setting"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	m_nFocus = 0;

	return TRUE;
}
//----------------------------------------------------------------------------
// 閉じる
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::Close()
{
	Show(SW_HIDE);
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// 閉じられた
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnClose()
{
	Close();
}
//----------------------------------------------------------------------------
// 次のコントロールにフォーカス
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::SetNextFocus()
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
			SetFocus((HWND)m_DefaultButton);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_List);
			m_nFocus = 0;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
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
		case 5:
			SetFocus((HWND)m_DefaultButton);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 5;
			break;
	}
}
//----------------------------------------------------------------------------
// リストビューの表示
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::ShowList()
{
	m_List.DeleteAllItems();
	CAcceleratorTable & accelTable = m_rApp.GetAccelTable();
	int nAccel = accelTable.GetNum();
	ACCEL * pAccel = new ACCEL[nAccel];
	accelTable.Copy(pAccel, nAccel);
	for(int i = 0; i < nAccel; i++) {
		m_List.InsertItem(i);
		m_List.SetItem(i, 0, m_rApp.GetAccelTable().GetShortCut(
			pAccel[i].fVirt, pAccel[i].key).c_str());
		m_List.SetItem(i, 1, m_CmdList.GetCommandName(pAccel[i].cmd).c_str());
	}
	delete [] pAccel;
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
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
	case ID_DEFAULT:
		OnDefaultButtonClicked();
		break;
	case ID_OK:
		OnOkButtonClicked();
		break;
	case ID_CANCEL:
		OnCancelButtonClicked();
		break;
	}
}
//----------------------------------------------------------------------------
// 追加ボタンが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnAddButtonClicked()
{
	if(!m_keyInputWnd.Create(TRUE)) {
#if JP
		m_rApp.ShowError(_T("ショートカットキー入力ダイアログの作成に失敗")
						 _T("しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create shortcut key setting dialog"));
#endif // JP
	}
	m_keyInputWnd.Show(SW_SHOW);
	m_keyInputWnd.Update();
}
//----------------------------------------------------------------------------
// 変更ボタンが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnChangeButtonClicked()
{
	int nItem = -1;
	int nCount = 0;
	while((nItem = m_List.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
		nCount++;
	if(nCount != 1) return;
	if(!m_keyInputWnd.Create(FALSE)) {
#if JP
		m_rApp.ShowError(_T("ショートカットキー入力ダイアログの作成に失敗")
							_T("しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create shortcut key setting dialog"));
#endif // JP
	}

	TCHAR szShortCut[255];
	m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 0, szShortCut,
					   255);
	tstring strShortCut = szShortCut;
	UINT bfMods = 0;
	if(strShortCut.find(_T("Ctrl")) != tstring::npos)
		bfMods |= HOTKEYF_CONTROL;
	if(strShortCut.find(_T("Alt")) != tstring::npos) bfMods |= HOTKEYF_ALT;
	if(strShortCut.find(_T("Shift")) != tstring::npos) bfMods |= HOTKEYF_SHIFT;
	UINT key = 0;
	if(strShortCut.rfind(_T("+"), strShortCut.length() - 2) != tstring::npos)
		key = m_rApp.GetAccelTable().GetKeyFromString(
				strShortCut.substr(strShortCut.rfind(_T("+"),
				strShortCut.length() - 2) + 2));
	else
		key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.c_str());

	if (IS_EXTKEY(key)) bfMods |= HOTKEYF_EXT;

	SendMessage((HWND)m_keyInputWnd.GetHotKeyCtrl(), HKM_SETHOTKEY,
				MAKEWORD(key, bfMods), 0);

	TCHAR szCommand[255];
	m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 1, szCommand,
										  255);
	m_keyInputWnd.GetComboBox().Select(szCommand);

	m_keyInputWnd.Show(SW_SHOW);
	m_keyInputWnd.Update();
}
//----------------------------------------------------------------------------
// 削除ボタンが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnDeleteButtonClicked()
{
	int nItem = -1;
	while((nItem = m_List.GetNextItem(-1, LVNI_SELECTED)) >= 0)
		m_List.DeleteItem(nItem);
}
//----------------------------------------------------------------------------
// デフォルトボタンが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnDefaultButtonClicked()
{
	ST_ACCEL tmp;

	m_List.DeleteAllItems();

	for(int i = 0; (tmp = m_rApp.GetAccelTable().GetDefault(i)).key != NULL;
		i++) {
		m_List.InsertItem(i);
		m_List.SetItem(i, 0, m_rApp.GetAccelTable().GetShortCut(tmp.virt,
					   tmp.key).c_str());
		m_List.SetItem(i, 1, m_CmdList.GetCommandName(tmp.cmd).c_str());
	}
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnOkButtonClicked()
{
	m_rApp.GetAccelTable().Destroy();
	for(int i = 0; i < m_List.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		m_List.GetItemText(i, 0, szShortCut, 255);
		tstring strShortCut = szShortCut;
		BYTE fVirt = FVIRTKEY;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos) fVirt |= FCONTROL;
		if(strShortCut.find(_T("Alt")) != tstring::npos) fVirt |= FALT;
		if(strShortCut.find(_T("Shift")) != tstring::npos) fVirt |= FSHIFT;
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
		m_rApp.GetAccelTable().Add(fVirt, key, cmd);
	}
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// フォーカス中のボタン機能を実行
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::ExecCurrentButtonFunc()
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
			OnDefaultButtonClicked();
			break;
		case 5:
			OnOkButtonClicked();
			break;
		case 6:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnReturnKeyPressed()
{
	ExecCurrentButtonFunc();
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnSpaceKeyPressed()
{
	ExecCurrentButtonFunc();
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CKeySettingWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(350, 200, FALSE);

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
	m_List.InsertColumn(0,
#if JP
						_T("ショートカットキー"),
#else // JP
						_T("Shortcut key"),
#endif // JP
						LVCFMT_LEFT, 125, 0);
	m_List.InsertColumn(1,
#if JP
						_T("アクション"),
#else // JP
						_T("Action"),
#endif // JP
						LVCFMT_LEFT, 150, 0);
	ShowList();
	m_List.Show(SW_SHOW);

	// デフォルトの復元ボタンの作成
	if(!m_DefaultButton.Create(
#if JP
							   _T("デフォルトの復元"),
#else // JP
							   _T("Default"),
#endif // JP
							   m_hWnd, ID_DEFAULT)) {
#if JP
		m_rApp.ShowError(_T("デフォルトの復元ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create recover default button."));
#endif // JP
		return FALSE;
	}
	m_DefaultButton.SetSizeToTextSize();
	POINT pt;
	pt.y = m_List.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_DefaultButton.SetPos(GetClientWidth() - 10 - m_DefaultButton.GetWidth(),
						   pt.y + 10);

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
	m_DeleteButton.SetPos(m_DefaultButton.GetLeft() - 5 - 
						  m_DeleteButton.GetWidth(), m_DefaultButton.GetTop());

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
						  m_ChangeButton.GetWidth(), m_DefaultButton.GetTop());

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
					   m_DefaultButton.GetTop());

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
						  m_AddButton.GetBottom() + 20);

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
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(),
					  m_CancelButton.GetTop());

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0) SetPreviousFocus();
		else SetNextFocus();
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