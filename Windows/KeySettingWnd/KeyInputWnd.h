//----------------------------------------------------------------------------
// KeyInputWnd.h : キー入力用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef KeyInputWndH
#define KeyInputWndH

class CApp;
class CMainWnd;
class CKeySettingWnd_MainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ComboBox.h"
#include "../Common/HotKeyCtrl.h"
#include "../Common/Button.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ホットキーコントロールの管理を行うクラス
//----------------------------------------------------------------------------
class CHotKeyCtrl_KeyInputWnd : public CHotKeyCtrl
{
public: // 関数

	CHotKeyCtrl_KeyInputWnd() { }
	virtual ~CHotKeyCtrl_KeyInputWnd() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
};
//----------------------------------------------------------------------------
// キー入力用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CKeyInputWnd : public CFrameWnd
{
public: // 関数

	CKeyInputWnd(CApp & app, CMainWnd & mainWnd,
				 CKeySettingWnd_MainWnd & parentWnd);
	virtual ~CKeyInputWnd();

	virtual BOOL Create(BOOL bAdd);

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	CKeySettingWnd_MainWnd & m_rParentWnd;

	CComboBox m_combo;
	CHotKeyCtrl_KeyInputWnd m_hot;
	CButton m_OkButton;
	CButton m_CancelButton;

	LPACCEL m_pAccel; // アクセラレータテーブル退避用
	int m_nAccel; // アクセラレータテーブル退避用
	BOOL m_bAdd; // リストに追加するかどうか

public: // メンバ変数の取得・設定

	CHotKeyCtrl_KeyInputWnd & GetHotKeyCtrl() { return m_hot; }
	CComboBox & GetComboBox() { return m_combo; }

public: // 定数
	enum {
		ID_COMBO = 100,
		ID_HOT,
		ID_OK,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif