//----------------------------------------------------------------------------
// RMenu_FreqCtrl.h : 再生周波数コントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_FreqCtrlH
#define RMenu_FreqCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 再生周波数コントロール用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_FreqCtrl : public CMenu
{
public: // 関数

	CRMenu_FreqCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_FreqCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // メンバ変数

	CMainWnd & m_rParent;
	CMenu m_setFreqMenu;
	CMenu m_freqDecimalMenu;
};
//----------------------------------------------------------------------------

#endif