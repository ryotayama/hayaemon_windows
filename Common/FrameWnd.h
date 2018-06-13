//----------------------------------------------------------------------------
// FrameWnd.h : フレームウィンドウクラス
//----------------------------------------------------------------------------
#ifndef FrameWndH
#define FrameWndH

#include "Wnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// フレームウィンドウクラス
//----------------------------------------------------------------------------
class CFrameWnd : public CWnd
{
public: // 関数

	CFrameWnd(): m_bMainWnd(false) { }
	virtual ~CFrameWnd() { }
	virtual BOOL Create(LPCTSTR lpClassName) {
		RegisterClass(lpClassName);
		return CWnd::Create(lpClassName);
	}
	virtual BOOL SetMenu(HMENU hMenu) {
		return ::SetMenu(m_hWnd, hMenu);
	}
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if(uMsg == WM_DESTROY && m_bMainWnd) PostQuitMessage(0);
		return CWnd::WindowProc(uMsg, wParam, lParam);
	}

protected: // メンバ変数

	BOOL m_bMainWnd; // メインウィンドウかどうか

public: // メンバ変数の取得・設定

	void SetMainWnd(bool bMainWnd) { m_bMainWnd = bMainWnd; }
};
//----------------------------------------------------------------------------

#endif