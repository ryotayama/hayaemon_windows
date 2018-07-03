//----------------------------------------------------------------------------
// Tab.h : タブコントロールの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef TabH
#define TabH

#include <CommCtrl.h>
#include "Wnd.h"
#include "Font.h"
#include "ClientDC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// タブコントロールの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CTab : public CWnd
{
public: // 関数

	CTab() { }
	virtual ~CTab() { }
	virtual BOOL Create(HWND hParentWnd) {
		Destroy();

		m_hWnd = CreateWindow(WC_TABCONTROL, _T(""),
			WS_CHILD | WS_CLIPSIBLINGS | TCS_FLATBUTTONS, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParentWnd, 0,
			GetModuleHandle(NULL), NULL);
		if(!m_hWnd) return FALSE;

		// 画面のプロパティで設定されているメッセージボックスと同じ
		// システムフォントに設定
		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
		ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
		m_font.CreateIndirect(&ncm.lfMessageFont);
		SetFont(m_font, TRUE);

		SetProc();
		return TRUE;
	}
	virtual BOOL DeleteItem(int iItem) {
		return SendMessage(m_hWnd, TCM_DELETEITEM, iItem, 0);
	}

	virtual int GetCurrentFocus() {
		return SendMessage(m_hWnd, TCM_GETCURFOCUS, 0, 0);
	}
	virtual int GetItemCount() {
		return TabCtrl_GetItemCount(m_hWnd);
	}
	virtual RECT GetItemRect(int i) {
		RECT rc;
		TabCtrl_GetItemRect(m_hWnd, i, &rc);
		return rc;
	}
	virtual void InsertItem(LPTSTR lpText, int iItem) {
		TCITEM tc;
		ZeroMemory(&tc, sizeof(TCITEM));
		tc.mask = TCIF_TEXT;
		tc.pszText = lpText;
		SendMessage(m_hWnd, TCM_INSERTITEM, (WPARAM)iItem, (LPARAM)&tc);
	}
	virtual void SetCurrentFocus(int iItem) {
		SendMessage(m_hWnd, TCM_SETCURFOCUS, (WPARAM)iItem, 0);
	}
	virtual void SetItem(LPTSTR lpText, int iItem) {
		TCITEM tc;
		ZeroMemory(&tc, sizeof(TCITEM));
		tc.mask = TCIF_TEXT;
		tc.pszText = lpText;
		SendMessage(m_hWnd, TCM_SETITEM, (WPARAM)iItem, (LPARAM)&tc);
	}
	virtual tstring GetItemText(int iItem) {
		TCHAR text[255];
		TCITEM tc;
		tc.mask = TCIF_TEXT;
		tc.pszText = text;
		tc.cchTextMax = 255;
		SendMessage(m_hWnd, TCM_GETITEM, iItem, (LPARAM)&tc);
		return text;
	}

private: // メンバ変数

	CFont m_font;
};
//----------------------------------------------------------------------------

#endif