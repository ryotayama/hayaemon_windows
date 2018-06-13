//----------------------------------------------------------------------------
// RMenu_Taskbar.h : タスクバー用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_TaskbarH
#define RMenu_TaskbarH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// タスクバー用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_Taskbar : public CMenu
{
public: // 関数

	CRMenu_Taskbar(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_Taskbar() { }

	virtual BOOL Create();
	virtual UINT GetItemFlags(UINT_PTR uID);

private: // メンバ変数

	CMainWnd & m_rParent;
	CMenu m_returnMenu;
	CMenu m_forwardMenu;
	CMenu m_speedMenu;
	CMenu m_freqMenu;
	CMenu m_pitchMenu;
	CMenu m_systemMenu;
	CMenu m_effectMenu;
	CMenu m_reverbMenu;
	CMenu m_delayMenu;
	CMenu m_chorusMenu;
	CMenu m_compressorMenu;
	CMenu m_flangerMenu;
	CMenu m_gargleMenu;
	CMenu m_distortionMenu;
	CMenu m_eqPresetMenu;
	CMenu m_recoveryMenu;
	CMenu m_recoverVisibleMenu;
	CMenu m_recoverPlayModeMenu;

public: // 定数

};
//----------------------------------------------------------------------------

#endif