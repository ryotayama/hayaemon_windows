//----------------------------------------------------------------------------
// SliderCtrl.h : スライダコントロールの管理を行う
//----------------------------------------------------------------------------
#ifndef SliderCtrlH
#define SliderCtrlH

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
class CSliderCtrl : public CWnd
{
public: // 関数

	CSliderCtrl() { }
	virtual ~CSliderCtrl() { }

	virtual BOOL Create(HWND hParentWnd)
	{
		Destroy();
	
		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_BAR_CLASSES;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateWindow(TRACKBAR_CLASS, _T(""), WS_CHILD, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								hParentWnd, 0, GetModuleHandle(NULL), NULL);
		if(!m_hWnd) return FALSE;
		SetProc();
		return TRUE;
	}
	virtual LONG GetRangeMin() const {
		return (LONG)SendMessage(m_hWnd, TBM_GETRANGEMIN, 0, 0);
	}
	virtual LONG GetRangeMax() const {
		return (LONG)SendMessage(m_hWnd, TBM_GETRANGEMAX, 0, 0);
	}
	virtual void GetSelRect(LPRECT lpRc) const
	{
		RECT rcThumb;
		GetThumbRect(&rcThumb);
		int nThumbWidth = rcThumb.right - rcThumb.left;

		SendMessage(m_hWnd, TBM_GETCHANNELRECT, 0, (LPARAM)lpRc);
		lpRc->left += nThumbWidth / 2;
		lpRc->right -= nThumbWidth / 2;
	}
	virtual LONG GetSelEndLeft() const
	{
		RECT rc;
		GetSelRect(&rc);

		LONG lSelEnd = (LONG)SendMessage(m_hWnd, TBM_GETSELEND, 0, 0);
		LONG lRangeMax = (LONG)SendMessage(m_hWnd, TBM_GETRANGEMAX, 0, 0);
		double dSelEndLeft = (double)lSelEnd / (double)lRangeMax;
		dSelEndLeft *= rc.right - rc.left;
		dSelEndLeft += rc.left;
		return (int)dSelEndLeft;
	}
	virtual LONG GetSelStartLeft() const
	{
		RECT rc;
		GetSelRect(&rc);

		LONG lSelStart = (LONG)SendMessage(m_hWnd, TBM_GETSELSTART, 0, 0);
		LONG lRangeMax = (LONG)SendMessage(m_hWnd, TBM_GETRANGEMAX, 0, 0);
		double dSelStartLeft = (double)lSelStart / (double)lRangeMax;
		dSelStartLeft *= rc.right - rc.left;
		dSelStartLeft += rc.left;
		return (int)dSelStartLeft;
	}
	virtual LONG GetThumbPos() const {
		return (LONG)SendMessage(m_hWnd, TBM_GETPOS, 0, 0);
	}
	virtual void GetThumbRect(LPRECT lpRc) const {
		SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)lpRc);
	}
	virtual LRESULT SetLineSize(LONG lLineSize)
	{
		return SendMessage(m_hWnd, TBM_SETLINESIZE, 0, (LPARAM)lLineSize);
	}
	virtual int SetPageSize(LONG lPageSize)
	{
		return (int)SendMessage(m_hWnd, TBM_SETPAGESIZE, 0, (LPARAM)lPageSize);
	}
	virtual void SetRange(LONG lMin, LONG lMax, BOOL bRedraw = FALSE)
	{
		SendMessage(m_hWnd, TBM_SETRANGE, (WPARAM)bRedraw, MAKELPARAM(lMin, lMax));
	}
	virtual void SetRangeMax(LONG lMax, BOOL bRedraw = FALSE)
	{
		SendMessage(m_hWnd, TBM_SETRANGEMAX, (WPARAM)bRedraw, (LPARAM)lMax);
	}
	virtual void SetRangeMin(LONG lMin, BOOL bRedraw = FALSE)
	{
		SendMessage(m_hWnd, TBM_SETRANGEMIN, (WPARAM)bRedraw, (LPARAM)lMin);
	}
	virtual void SetThumbPos(LONG lPos, BOOL bRedraw = TRUE)
	{
		SendMessage(m_hWnd, TBM_SETPOS, (WPARAM)bRedraw, lPos);
	}
};
//----------------------------------------------------------------------------

#endif