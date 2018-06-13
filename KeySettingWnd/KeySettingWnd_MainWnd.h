//----------------------------------------------------------------------------
// KeySettingWnd_MainWnd.h : キーカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef KeySettingWnd_MainWndH
#define KeySettingWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "./List_KeySettingWnd.h"
#include "../Common/ButtonExt.h"
#include "./KeyInputWnd.h"
#include "../Common/CommandList.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// キーカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CKeySettingWnd_MainWnd : public CFrameWnd
{
public: // 関数

	CKeySettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CKeySettingWnd_MainWnd();

	virtual void AddList(UINT bVKHotKey, UINT bfMods, tstring strCommand);
	virtual void ChangeList(UINT bVKHotKey, UINT bfMods, tstring strCommand);
	virtual BOOL Create();
	virtual void Close();
	virtual void OnClose();
	virtual void OnAddButtonClicked();
	virtual void OnChangeButtonClicked();
	virtual void OnDeleteButtonClicked();
	virtual void OnDefaultButtonClicked();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnReturnKeyPressed();
	virtual void OnSpaceKeyPressed();
	virtual void OnEscKeyPressed();
	virtual void ExecCurrentButtonFunc();
	virtual void SetNextFocus();
	virtual void SetPreviousFocus();
	virtual void ShowList();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

protected: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CList_KeySettingWnd m_List;
	CButtonExt m_AddButton;
	CButtonExt m_ChangeButton;
	CButtonExt m_DeleteButton;
	CButtonExt m_DefaultButton;
	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;

	CKeyInputWnd m_keyInputWnd;

	int m_nFocus;

public: // メンバ変数

	CCommandList m_CmdList;


public: // 定数
	enum {
		ID_ADD = 100,
		ID_CHANGE,
		ID_DELETE,
		ID_DEFAULT,
		ID_OK,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif