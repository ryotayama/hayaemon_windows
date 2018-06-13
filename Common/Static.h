//----------------------------------------------------------------------------
// Static.h : スタティックコントロールの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef StaticH
#define StaticH

#include "Wnd.h"
#include "ClientDC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// スタティックコントロールの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CStatic : public CWnd
{
public: // 関数

	CStatic() { }
	virtual ~CStatic() { }
	virtual BOOL Create() {
		Destroy();

		m_hWnd = CreateWindow(_T("static"), _T(""), WS_POPUP, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
								GetModuleHandle(NULL), this);
		if(!m_hWnd) return FALSE;
		SetProc();
		return TRUE;
	}
	virtual BOOL Create(UINT uStyle) {
		Destroy();
	
		m_hWnd = CreateWindow(_T("static"), _T(""), WS_CHILD | WS_POPUP |
			uStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			0, 0, GetModuleHandle(NULL), this);
		if(!m_hWnd) return false;
		SetProc();
		return TRUE;
	}
	virtual tstring GetText() const { return GetCaption(); }
	virtual int GetTextHeight() const {
		return GetTextHeight(GetText());
	}
	virtual int GetTextHeight(tstring str) const {
		if(!m_hWnd) return -1;

		CClientDC dc(m_hWnd);
		HFONT hFont = GetFont();
		HFONT hOrgFont = 0;
		if(hFont)
			hOrgFont = dc.SelectFont(hFont);
		int width = dc.GetTextHeight(str);
		if(hOrgFont)
			dc.SelectFont(hOrgFont);
		return width;
	}
	virtual int GetTextWidth() const {
		return GetTextWidth(GetText());
	}
	virtual int GetTextWidth(tstring str) const {
		if(!m_hWnd) return -1;

		CClientDC dc(m_hWnd);
		HFONT hFont = GetFont();
		HFONT hOrgFont = 0;
		if(hFont)
			hOrgFont = dc.SelectFont(hFont);
		int width = dc.GetTextWidth(str);
		if(hOrgFont)
			dc.SelectFont(hOrgFont);
		return width;
	}
	virtual void SetSizeToTextSize() {
		SetSize(GetTextWidth(), GetTextHeight());
	}
	virtual void SetText(LPCTSTR lpText) { SetCaption(lpText); }
};
//----------------------------------------------------------------------------

#endif