//----------------------------------------------------------------------------
// RMenu_VideoScreen.h : 再生時間設定用スライダ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_VideoScreenH
#define RMenu_VideoScreenH

class CVideoScreen_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// メインウィンドウ用メニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_VideoScreen : public CMenu
{
public: // 関数

	CRMenu_VideoScreen(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_VideoScreen() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnFullScreenMenuSelected();

private: // メンバ変数

	CMainWnd & m_rParent;

public: // 定数

	// コマンド ID
	enum {
		ID_FULLSCREEN = 11,
	};
};
//----------------------------------------------------------------------------

#endif