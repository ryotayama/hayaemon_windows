//----------------------------------------------------------------------------
// VideoScreenWnd_MainWnd.h : ビデオ全画面再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef VideoScreenWnd_MainWndH
#define VideoScreenWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
class CApp;
class CMainWnd;
#include "RMenu_VideoScreenWnd.h"
#include "../Common/Static.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// タイマー再生用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CVideoScreenWnd_MainWnd : public CStatic
{
public: // 関数

	CVideoScreenWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(*this) { }
	virtual ~CVideoScreenWnd_MainWnd() { }

	virtual BOOL Create();

	virtual void OnClose();
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRMenu_VideoScreenWnd m_rClickMenu; // 右クリックメニュー

public: // メンバ変数の取得・設定

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif