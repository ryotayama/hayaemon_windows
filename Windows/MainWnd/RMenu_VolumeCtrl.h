//----------------------------------------------------------------------------
// RMenu_VolumeCtrl.h : 音量コントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_VolumeCtrlH
#define RMenu_VolumeCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 音量コントロール用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_VolumeCtrl : public CMenu
{
public: // 関数

	CRMenu_VolumeCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_VolumeCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // メンバ変数

	CMainWnd & m_rParent;
	CMenu m_setVolumeMenu;
};
//----------------------------------------------------------------------------

#endif