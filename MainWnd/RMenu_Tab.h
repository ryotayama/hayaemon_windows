//----------------------------------------------------------------------------
// RMenu_Tab.h : タブ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_TabH
#define RMenu_TabH

class CTab_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// タブ用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_Tab : public CMenu
{
public: // 関数

	CRMenu_Tab(CTab_MainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_Tab() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnCloseMenuSelected();
	void OnRenameMenuSelected();
	void OnNewTabMenuSelected();
	void OnVisibleMenuSelected();

private: // メンバ変数

	CTab_MainWnd & m_rParent;

public: // 定数

	// コマンド ID
	enum {
		ID_CLOSE = 11,
		ID_RENAME,
		ID_NEWTAB,
		ID_VISIBLE,
	};
};
//----------------------------------------------------------------------------

#endif