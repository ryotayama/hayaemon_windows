//----------------------------------------------------------------------------
// ListView.h : リストビューの管理を行う
//----------------------------------------------------------------------------
#ifndef ListViewH
#define ListViewH

#include <commctrl.h>
#include "Wnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// リストビューの管理を行うクラス
//----------------------------------------------------------------------------
class CListView : public CWnd
{
public: // 関数

	CListView() { }
	virtual ~CListView() { }

	virtual BOOL Create(HWND hParentWnd, UINT uStyle = 0) {
		Destroy();

		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
								WC_LISTVIEW, _T(""), WS_CHILD | LVS_REPORT |
								LVS_SHOWSELALWAYS | uStyle, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								hParentWnd, 0, GetModuleHandle(NULL), NULL);
		if(!m_hWnd) return FALSE;

		UINT exStyle = GetExtendedStyle();
		exStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
		SetExtendedStyle(exStyle);
		SetProc();
		return TRUE;
	}
	virtual BOOL DeleteAllItems() {
		return ListView_DeleteAllItems(m_hWnd);
	}
	virtual BOOL DeleteItem(int nItem) {
		return ListView_DeleteItem(m_hWnd, nItem);
	}
	virtual BOOL EnsureVisible(int nItem, BOOL fPartialOK) {
		return ListView_EnsureVisible(m_hWnd, nItem, fPartialOK);
	}
	virtual int GetColumnWidth(int iCol) {
		return ListView_GetColumnWidth(m_hWnd, iCol);
	}
	virtual UINT GetExtendedStyle() const {
		return ListView_GetExtendedListViewStyle(m_hWnd);
	}
	virtual int GetItemCount() const {
		return ListView_GetItemCount(m_hWnd);
	}
	virtual BOOL GetItemRect(int i, PRECT prc, int code) const {
		return ListView_GetItemRect(m_hWnd, i, prc, code);
	}
	virtual DWORD GetItemSpacing(BOOL fSmall) const {
		return ListView_GetItemSpacing(m_hWnd, fSmall);
	}
	virtual void GetItemText(int iItem, int iSubItem, LPTSTR pszText, int cchTextMax) const {
		ListView_GetItemText(m_hWnd, iItem, iSubItem, pszText, cchTextMax);
	}
	virtual int GetNextItem(int iStart, UINT flags) {
		return ListView_GetNextItem(m_hWnd, iStart, flags);
	}
	virtual int HitTest(int x, int y) {
		LVHITTESTINFO lvhti;
		lvhti.pt.x = x;
		lvhti.pt.y = y;
		ListView_HitTest(m_hWnd, &lvhti);
		return lvhti.iItem;
	}
	virtual BOOL Scroll(int dx, int dy) {
		return ListView_Scroll(m_hWnd, dx, dy);
	}
	virtual BOOL SetInsertMark(int i) {
		LVINSERTMARK lvim;
		ZeroMemory(&lvim, sizeof(LVINSERTMARK));
		lvim.cbSize = sizeof(LVINSERTMARK);
		lvim.dwFlags = LVIM_AFTER;
		lvim.iItem = i;
		return ListView_SetInsertMark(m_hWnd, &lvim);
	}
	virtual void SetItem(int i, int iSubItem, LPCTSTR pszText) {
		LVITEM item;
		ZeroMemory(&item, sizeof(LVITEM));
		item.mask = LVIF_TEXT;
		item.iItem = i;
		item.lParam = i;
		item.iSubItem = iSubItem;
		item.pszText = (LPTSTR)pszText;
		ListView_SetItem(m_hWnd, &item);
	}
	virtual void SetItem(int i, int iSubItem, LPCTSTR pszText, int iImage) {
		LVITEM item;
		ZeroMemory(&item, sizeof(LVITEM));
		item.mask = LVIF_TEXT | LVIF_IMAGE;
		item.iItem = i;
		item.lParam = i;
		item.iImage = iImage;
		item.iSubItem = iSubItem;
		item.pszText = (LPTSTR)pszText;
		ListView_SetItem(m_hWnd, &item);
	}
	virtual void SetItemState(int i, UINT state, UINT mask) {
		ListView_SetItemState(m_hWnd, i, state, mask);
	}
	virtual void SetItemText(int i, int iSubItem, LPCTSTR pszText) {
		ListView_SetItemText(m_hWnd, i, iSubItem, (LPTSTR)pszText);
	}
	virtual void SetImageList(HIMAGELIST himl, int iImageList) {
		ListView_SetImageList(m_hWnd, himl, iImageList);
	}
	virtual void SetExtendedStyle(UINT uStyle) {
		ListView_SetExtendedListViewStyle(m_hWnd, uStyle);
	}
	virtual int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
								int nFormat = LVCFMT_LEFT, int nWidth = -1,
								int nSubItem = -1) {
		LVCOLUMN lvc;
		ZeroMemory(&lvc, sizeof(LVCOLUMN));
		lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT | LVCF_SUBITEM;
		lvc.cx = nWidth;
		lvc.pszText = (LPTSTR)lpszColumnHeading;
		lvc.fmt = nFormat;
		lvc.iSubItem = nSubItem;
		return ListView_InsertColumn(m_hWnd, nCol, &lvc);
	}
	virtual int InsertItem(int nItem) {
		LVITEM item;
		ZeroMemory(&item, sizeof(LVITEM));
		item.iItem = nItem;
		item.iSubItem = 0;
		item.lParam = nItem;
		item.mask = LVIF_TEXT | LVIF_PARAM;
		item.pszText = _T("");
		return ListView_InsertItem(m_hWnd, &item);
	}
	virtual int InsertItem(int nItem, const LPLVITEM pitem) {
		pitem->iItem = nItem;
		pitem->lParam = nItem;
		return ListView_InsertItem(m_hWnd, pitem);
	}
	virtual int InsertItem(int i, int iImage, LPTSTR text) {
		LVITEM item;
		ZeroMemory(&item, sizeof(LVITEM));
		item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		item.iItem = i;
		item.iImage = iImage;
		item.pszText = text;
		item.cchTextMax = MAX_PATH + _MAX_FNAME;
		return ListView_InsertItem(m_hWnd, &item);
	}
};
//----------------------------------------------------------------------------

#endif