//----------------------------------------------------------------------------
// ProgressCtrl.h : スライダコントロールの管理を行う
//----------------------------------------------------------------------------
#ifndef ProgressCtrlH
#define ProgressCtrlH

#include <commctrl.h>
#include "Wnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// スライダコントロールの管理を行うクラス
//----------------------------------------------------------------------------
class CProgressCtrl : public CWnd
{
public: // 関数

	CProgressCtrl() { }
	virtual ~CProgressCtrl() { }

	virtual BOOL Create(HWND hParentWnd) {
		Destroy();
	
		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_PROGRESS_CLASS;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateWindow(PROGRESS_CLASS, _T(""), PBS_SMOOTH | WS_CHILD, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								hParentWnd, 0, GetModuleHandle(NULL), NULL);
		if(!m_hWnd) return FALSE;
		SetProc();
		return TRUE;
	}
	virtual void SetProgressPos(int nPos) {
		SendMessage(m_hWnd, PBM_SETPOS, (WPARAM)nPos, 0L);
	}
	virtual void SetProgressRange(int nLower, int nUpper) {
		SendMessage(m_hWnd, PBM_SETRANGE32, (WPARAM)nLower, (LPARAM)nUpper);
	}
};
//----------------------------------------------------------------------------

#endif