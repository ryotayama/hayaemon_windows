//----------------------------------------------------------------------------
// EQ250Slider_MainWnd.h : イコライザ ( 250Hz ) 設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef EQ250Slider_MainWndH
#define EQ250Slider_MainWndH

class CApp;
class CMainWnd;
#include "../Common/SliderCtrl.h"
#include "RMenu_EQCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// イコライザ ( 250Hz ) 設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CEQ250Slider_MainWnd : public CSliderCtrl
{
public: // 関数

	CEQ250Slider_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  dwThumbClickTime(0) { }
	virtual ~CEQ250Slider_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnRButtonUp(int x, int y, UINT keyFlags);
	virtual BOOL OnMouseWheel(UINT nFlags, int zDelta, POINTS pt);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	DWORD dwThumbClickTime;
	CRMenu_EQCtrl m_rClickMenu; // 右クリックメニュー
};
//----------------------------------------------------------------------------

#endif