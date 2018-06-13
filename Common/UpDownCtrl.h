//----------------------------------------------------------------------------
// UpDownCtrl.h : アップダウンコントロールの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef UpDownCtrlH
#define UpDownCtrlH

#include <commctrl.h>
#include "Wnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// アップダウンコントロールの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CUpDownCtrl : public CWnd
{
public: // 関数

	CUpDownCtrl() { }
	virtual ~CUpDownCtrl() { }
	virtual BOOL Create(HWND hParentWnd, HWND hBuddy)
	{
		Destroy();

		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_UPDOWN_CLASS;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateUpDownControl(
			WS_CHILD | WS_BORDER | UDS_ALIGNRIGHT | UDS_ARROWKEYS,
			0, 0, 0, 0,
			hParentWnd,
			0,
			GetModuleHandle(NULL),
			hBuddy,
			2048,
			0,
			0
		);
		if(!m_hWnd) return FALSE;
		SetProc();
		return TRUE;
	}
};
//----------------------------------------------------------------------------

#endif