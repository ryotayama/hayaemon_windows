//----------------------------------------------------------------------------
// Tab_MainWnd.h : タブの管理を行う
//----------------------------------------------------------------------------
#ifndef Tab_MainWndH
#define Tab_MainWndH

class CApp;
class CMainWnd;
#include "RMenu_Tab.h"
#include "../Common/Tab.h"
#include "../Common/EditExt.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// タブの管理を行うクラス
//----------------------------------------------------------------------------
class CTab_MainWnd : public CTab
{
public: // 関数

	CTab_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(*this), m_edit(*this)
	{ }
	virtual ~CTab_MainWnd() { }

	virtual void AddNewTab(BOOL bChangeFocus = TRUE);
	virtual void CloseTab();
	virtual BOOL Create();
	virtual int GetItemHeight() {
		RECT rc;
		TabCtrl_GetItemRect(m_hWnd, 1, &rc);
		return rc.bottom - rc.top;
	}
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void ResetWidth();
	virtual void ShowEdit();
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual void OnMouseMove(int x, int y, UINT keyFlags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);
	virtual void OnReturnKeyPressed();

	CRMenu_Tab m_rClickMenu; // 右クリックメニュー
	int m_nTab;
	CFont m_font;
	CEditExt m_edit;
	RECT rcLast;

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

public: // メンバ変数の取得・設定

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif