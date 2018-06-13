//----------------------------------------------------------------------------
// Edit.h : エディットコントロールの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef EditH
#define EditH

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
class CEdit : public CWnd
{
public: // 関数

	CEdit() { }
	virtual ~CEdit() { }
	virtual BOOL Create(HWND hParentWnd) {
		Destroy();

		m_hWnd = CreateWindow(_T("Edit"), _T(""),
							  WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
							  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							  CW_USEDEFAULT, hParentWnd, 0,
							  GetModuleHandle(NULL), this);
		if(!m_hWnd) return false;
		SetProc();
		return TRUE;
	}
	virtual BOOL Create(HWND hParentWnd, LONG dwStyle) {
		Destroy();

		m_hWnd = CreateWindow(_T("Edit"), _T(""),
							  WS_CHILD | WS_BORDER | dwStyle,
							  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							  CW_USEDEFAULT, hParentWnd, 0,
							  GetModuleHandle(NULL), this);
		if(!m_hWnd) return false;
		SetProc();
		return TRUE;
	}
	virtual tstring GetText() const { return GetCaption(); }
	virtual int GetTextHeight() const {
		if(!m_hWnd) return -1;

		CClientDC dc(m_hWnd);
		HFONT hFont = GetFont();
		HFONT hOrgFont = 0;
		if(hFont)
			hOrgFont = dc.SelectFont(hFont);
		TEXTMETRIC tm;
		GetTextMetrics(dc, &tm);
		int height = tm.tmHeight + tm.tmExternalLeading + 4;
		if(hOrgFont)
			dc.SelectFont(hOrgFont);
		return height;
	}
	virtual int GetTextWidth() const {
		if(!m_hWnd) return -1;

		CClientDC dc(m_hWnd);
		HFONT hFont = GetFont();
		HFONT hOrgFont = 0;
		if(hFont)
			hOrgFont = dc.SelectFont(hFont);
		LRESULT lMargin = SendMessage(m_hWnd, EM_GETMARGINS, 0L, 0L);
		int width = dc.GetTextWidth(GetText()) + LOWORD(lMargin) + HIWORD(lMargin) + 8;
		if(hOrgFont)
			dc.SelectFont(hOrgFont);
		return width;
	}
	virtual void SetSizeToTextSize() {
		SetClientSize(GetTextWidth(), GetTextHeight(), FALSE);
	}
	virtual void SetText(LPCTSTR lpText) { SetCaption(lpText); }
};
//----------------------------------------------------------------------------

#endif