//----------------------------------------------------------------------------
// ProgressWnd_MainWnd.h : プログレスウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef ProgressWnd_MainWndH
#define ProgressWnd_MainWndH

class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ProgressCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// プログレスウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CProgressWnd_MainWnd : public CFrameWnd
{
public: // 関数

	CProgressWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CProgressWnd_MainWnd() {
		EnableWindow(m_rMainWnd, TRUE);
	}

	virtual BOOL Create();
	virtual void SetProgressPos(int nPos) {
		m_progress.SetProgressPos(nPos);
	}
	virtual void SetProgressRange(int nLower, int nUpper) {
		m_progress.SetProgressRange(nLower, nUpper);
	}

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CProgressCtrl m_progress;
};
//----------------------------------------------------------------------------

#endif