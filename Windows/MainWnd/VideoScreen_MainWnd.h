//----------------------------------------------------------------------------
// VideoScreen_MainWnd.h : ビデオ画面の管理を行う
//----------------------------------------------------------------------------
#ifndef VideoScreen_MainWndH
#define VideoScreen_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
class CApp;
class CMainWnd;
#include "RMenu_VideoScreen.h"
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ビデオ画面の管理を行うクラス
//----------------------------------------------------------------------------
class CVideoScreen_MainWnd : public CStatic
{
public: // 関数

	CVideoScreen_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd) { }
	virtual ~CVideoScreen_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void ResetWidth();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRMenu_VideoScreen m_rClickMenu; // 右クリックメニュー
	CFont m_font;

public: // メンバ変数の取得・設定

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif