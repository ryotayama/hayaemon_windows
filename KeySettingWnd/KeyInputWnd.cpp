//----------------------------------------------------------------------------
// KeyInputWnd.cpp : キー入力用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "KeySettingWnd_MainWnd.h"
#include "KeyInputWnd.h"
#include "../Common/AcceleratorTable.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CHotKeyCtrl_KeyInputWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	// 入力制限を無くす
	if(vk == VK_RETURN || vk == VK_TAB || vk == VK_SPACE || vk == VK_DELETE ||
	   vk == VK_ESCAPE || vk == VK_BACK) {
		BYTE bVirt = 0;
		if (GetKeyState(VK_SHIFT) < 0) bVirt |= HOTKEYF_SHIFT;
		if (GetKeyState(VK_CONTROL) < 0) bVirt |= HOTKEYF_CONTROL;
		if (GetKeyState(VK_MENU) < 0) bVirt |= HOTKEYF_ALT;
		if (IS_EXTKEY(vk)) bVirt |= HOTKEYF_EXT;

		SendMessage(m_hWnd, HKM_SETHOTKEY, MAKEWORD(vk, bVirt), 0);
		return;
	}

	CHotKeyCtrl::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CKeyInputWnd::CKeyInputWnd(CApp & app, CMainWnd & mainWnd,
						   CKeySettingWnd_MainWnd & parentWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_rParentWnd(parentWnd),
	  m_pAccel(NULL), m_nAccel(0), m_bAdd(FALSE)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CKeyInputWnd::~CKeyInputWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CKeyInputWnd::Create(BOOL bAdd)
{
	m_bAdd = bAdd;

	Destroy();

	RegisterClass(_T("KeyInputWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("KeyInputWndCls"),
#if JP
							_T("ショートカットキー入力"),
#else // JP
							_T("Shortcut key input"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rParentWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	// アクセラレータテーブルを一旦退避しておき、機能を切る
	CAcceleratorTable accelTable = m_rApp.GetAccelTable();
	m_nAccel = accelTable.GetNum();
	m_pAccel = new ACCEL[m_nAccel];
	accelTable.Copy(m_pAccel, m_nAccel);
	accelTable.Destroy();

	return TRUE;
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CKeyInputWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
	{
		WORD wHotKey = (WORD)SendMessage(m_hot, HKM_GETHOTKEY, 0, 0);
		if(m_bAdd)
			m_rParentWnd.AddList(LOBYTE(wHotKey), HIBYTE(wHotKey),
								 m_combo.GetSelectText());
		else
			m_rParentWnd.ChangeList(LOBYTE(wHotKey), HIBYTE(wHotKey),
									m_combo.GetSelectText());
		Close();
		break;
	}
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CKeyInputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 不要なシステムメニューを削除
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // セパレータ

	EnableWindow(m_rParentWnd, FALSE);

	if(!m_hot.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("ホットキーコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create hot key control."));
#endif // JP
		return FALSE;
	}
	m_hot.SetPos(10, 10);
	m_hot.SetCaption(_T("Ctrl + Alt + Shift + Scroll Lock"));
	m_hot.SetSize(m_hot.GetTextWidth() + 30, m_hot.GetTextHeight() + 5);
	m_hot.Show(SW_SHOW);
	SetFocus(m_hot);

	if(!m_combo.Create(0, 0, 100, 90, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("コンボボックスの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create combobox"));
#endif // JP
		return FALSE;
	}
	POINT pt;
	pt.y = m_hot.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_combo.SetPos(10, pt.y + 10);
	m_combo.SetSize(m_hot.GetWidth(), m_hot.GetHeight() * 10);
	for (int i = 0; m_rParentWnd.m_CmdList[i].div != DIV_TERMINAL; i++)
	{
		if (m_rParentWnd.m_CmdList[i].use & CMD_SHORTCUTKEY)
			m_combo.Add(m_rParentWnd.m_CmdList[i].pszText);
	}
	m_combo.Select(m_rParentWnd.m_CmdList.GetCommandName(ID_OPENFILE).c_str());

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
	pt.y = m_combo.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_CancelButton.SetSize(90, 20);
	m_CancelButton.SetPos(m_hot.GetWidth() + 10 - m_CancelButton.GetWidth(),
						  pt.y + 10);

	// OKボタンの作成
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK)) {
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(90, 20);
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(), m_CancelButton.GetTop());

	SetClientSize(m_hot.GetWidth() + 20, m_OkButton.GetTop() + m_OkButton.GetHeight() + 10, FALSE);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CKeyInputWnd::OnDestroy()
{
	// 退避しておいたアクセラレータテーブルを復活させる
	if(m_pAccel) {
		m_rApp.GetAccelTable().Create(m_pAccel, m_nAccel);
		delete [] m_pAccel;
		m_pAccel = NULL;
		m_nAccel = 0;
	}

	EnableWindow(m_rParentWnd, TRUE);
	SetForegroundWindow(m_rParentWnd);
}
//----------------------------------------------------------------------------
