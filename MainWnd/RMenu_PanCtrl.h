//----------------------------------------------------------------------------
// RMenu_PanCtrl.h : パンコントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_PanCtrlH
#define RMenu_PanCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// パンコントロール用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_PanCtrl : public CMenu
{
public: // 関数

	CRMenu_PanCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_PanCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnVisibleMenuSelected();

private: // メンバ変数

	CMainWnd & m_rParent;

public: // 定数

	// コマンド ID
	enum {
		ID_VISIBLE = 11,
	};
};
//----------------------------------------------------------------------------

#endif