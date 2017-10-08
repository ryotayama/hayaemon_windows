//----------------------------------------------------------------------------
// RMenu_PitchCtrl.h : 音程コントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_PitchCtrlH
#define RMenu_PitchCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 音程コントロール用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_PitchCtrl : public CMenu
{
public: // 関数

	CRMenu_PitchCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_PitchCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // メンバ変数

	CMainWnd & m_rParent;
	CMenu m_setPitchMenu;
	CMenu m_pitchDecimalMenu;
};
//----------------------------------------------------------------------------

#endif