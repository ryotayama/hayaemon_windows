//----------------------------------------------------------------------------
// OutKeyInputWnd.h : グローバルホットキー入力用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef OutKeyInputWndH
#define OutKeyInputWndH

class CApp;
class CMainWnd;
class COutKeySettingWnd_MainWnd;
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
// キー入力用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class COutKeyInputWnd : public CFrameWnd
{
public: // 関数

	COutKeyInputWnd(CApp & app, CMainWnd & mainWnd, COutKeySettingWnd_MainWnd & parentWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rParentWnd(parentWnd), bAdd(FALSE) { }
	virtual ~COutKeyInputWnd() { }

	virtual BOOL Create(BOOL bAdd);

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	COutKeySettingWnd_MainWnd & m_rParentWnd;

	CComboBox m_combo;
	CHotKeyCtrl m_hot;
	CButton m_OkButton;
	CButton m_CancelButton;

	BOOL bAdd; // リストに追加するかどうか

public: // メンバ変数の取得・設定

	CHotKeyCtrl & GetHotKeyCtrl() { return m_hot; }
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