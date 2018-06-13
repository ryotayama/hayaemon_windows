//----------------------------------------------------------------------------
// Tab_MainWnd.cpp : タブの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../resource.h"
#include "../App.h"
#include "MainWnd.h"
#include "Tab_MainWnd.h"
//----------------------------------------------------------------------------
// 新しいタブを追加
//----------------------------------------------------------------------------
void CTab_MainWnd::AddNewTab(BOOL bChangeFocus)
{
	int nSelect = !bChangeFocus ? GetItemCount() :
								 GetCurrentFocus() + 1;
#if JP
	InsertItem(_T("無題"), nSelect);
#else // JP
	InsertItem(_T("No Title"), nSelect);
#endif // JP
	if(bChangeFocus) SetCurrentFocus(nSelect);
}
//----------------------------------------------------------------------------
// タブを閉じる
//----------------------------------------------------------------------------
void CTab_MainWnd::CloseTab()
{
	m_rMainWnd.DeleteArrayList(m_nTab);
	if(GetItemCount() > 1) {
		DeleteItem(m_nTab);
		int nFocus = m_nTab > 0 ? m_nTab - 1 : m_nTab;
		SetCurrentFocus(nFocus);
	}
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTab_MainWnd::Create()
{
	CTab::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;
	SetExStyle(GetExStyle() | WS_EX_ACCEPTFILES);

#if JP
	InsertItem(_T("無題"), 0);
#else // JP
	InsertItem(_T("No Title"), 0);
#endif // JP

	ResetPos();

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);

	m_edit.Create(m_hWnd);
	m_edit.SetStyle(m_edit.GetStyle() | ES_LEFT | ES_AUTOHSCROLL);
	m_edit.SetFont(m_font, TRUE);

	return TRUE;
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CTab_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetDivider5().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = 0;
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset() / 2;
	SetPos(nLeft, pt.y + m_rMainWnd.GetDivider5().GetHeight()
		+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CTab_MainWnd::ResetSize()
{
	POINT pt;
	pt.y = GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nHeight = m_rMainWnd.GetClientHeight() - pt.y;
	int nWidth = m_rMainWnd.GetClientWidth();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nWidth -= m_rMainWnd.GetExplorer().GetWidth() + 2;
	SetSize(nWidth, nHeight);
}
//----------------------------------------------------------------------------
// 幅の再設定
//----------------------------------------------------------------------------
void CTab_MainWnd::ResetWidth()
{
	int nHeight = GetHeight();
	int nWidth = m_rMainWnd.GetClientWidth();
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nWidth -= m_rMainWnd.GetExplorer().GetWidth() + 2;
	SetSize(nWidth, nHeight);
}
//----------------------------------------------------------------------------
// エディットコントロールの表示
//----------------------------------------------------------------------------
void CTab_MainWnd::ShowEdit()
{
	RECT rc = GetItemRect(m_nTab);
	m_edit.SetPos(rc.left + 3, rc.top);
	m_edit.SetSize(rc.right - rc.left - 4, rc.bottom - rc.top);
	TCHAR text[255];
	TCITEM tc;
	tc.mask = TCIF_TEXT;
	tc.pszText = text;
	tc.cchTextMax = 255;
	SendMessage(m_hWnd, TCM_GETITEM, m_nTab, (LPARAM)&tc);
	m_edit.SetText(text);
	SendMessage(m_edit, EM_SETLIMITTEXT, 255, 0);
	m_edit.Show(SW_SHOW);
	SetFocus(m_edit);
	PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
	PostMessage(m_edit, EM_SETSEL, 0, -1);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CTab_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == (HWND)m_edit) {
		if(codeNotify == EN_KILLFOCUS) {
			tstring str = m_edit.GetText();
			SetItem((LPTSTR)str.c_str(), m_nTab);
			m_edit.Show(SW_HIDE);
			m_rMainWnd.ResetSize();
		}
	}
	else if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CTab::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
LRESULT CTab_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	m_rClickMenu.Create();
	TC_HITTESTINFO tchtst;
	tchtst.pt.x = xPos;
	tchtst.pt.y = yPos;
	ScreenToClient(m_hWnd, &tchtst.pt);
	m_nTab = TabCtrl_HitTest(m_hWnd, &tchtst);
	if(tchtst.flags & TCHT_ONITEM) {
		SetForegroundWindow(m_hWnd);
		TrackPopupMenu((HMENU)m_rClickMenu,
						TPM_LEFTALIGN | TPM_TOPALIGN, xPos, yPos, 0,
						m_hWnd, NULL);
	}
	
	return CTab::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CTab_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	CTab::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// ダブルクリックされた
//----------------------------------------------------------------------------
void CTab_MainWnd::OnLButtonDoubleClick(int x, int y, UINT keyFlags)
{
	TC_HITTESTINFO tchtst;
	tchtst.pt.x = x;
	tchtst.pt.y = y;
	m_nTab = TabCtrl_HitTest(m_hWnd, &tchtst);
	if(tchtst.flags & TCHT_ONITEM) ShowEdit();
}
//----------------------------------------------------------------------------
// クリックされた
//----------------------------------------------------------------------------
void CTab_MainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	if(IsWindowVisible(m_edit)) {
		tstring str = m_edit.GetText();
		SetItem((LPTSTR)str.c_str(), m_nTab);
		m_edit.Show(SW_HIDE);
		m_rMainWnd.ResetSize();
	}
	TC_HITTESTINFO tchtst;
	tchtst.pt.x = x;
	tchtst.pt.y = y;
	m_nTab = TabCtrl_HitTest(m_hWnd, &tchtst);
	if(tchtst.flags & TCHT_ONITEM)
		SetCapture(m_hWnd);
	CTab::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// クリックが離された
//----------------------------------------------------------------------------
void CTab_MainWnd::OnLButtonUp(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		TC_HITTESTINFO tchtst;
		tchtst.pt.x = x;
		tchtst.pt.y = y;
		int nTab = TabCtrl_HitTest(m_hWnd, &tchtst);
		if(tchtst.flags & TCHT_ONITEM && m_nTab != nTab) {
			tstring str = GetItemText(m_nTab);
			DeleteItem(m_nTab);
			InsertItem((LPTSTR)str.c_str(), nTab);
			m_rMainWnd.MoveList(m_nTab, nTab);
		}
		ReleaseCapture();
		InvalidateRect(NULL, FALSE);
	}
	CTab::OnLButtonUp(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// マウスが動かされた
//----------------------------------------------------------------------------
void CTab_MainWnd::OnMouseMove(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		TC_HITTESTINFO tchtst;
		tchtst.pt.x = x;
		tchtst.pt.y = y;
		MapWindowPoints(m_hWnd, m_rMainWnd, (LPPOINT)&rcLast, (sizeof(RECT)/sizeof(POINT)));
		int nTab = TabCtrl_HitTest(m_hWnd, &tchtst);
		if(tchtst.flags & TCHT_ONITEM && m_nTab != nTab) {
			SetCursor(LoadCursor(GetModuleHandle(NULL),
				(LPCTSTR)IDC_DRAG_MOVE));
			m_rMainWnd.InvalidateRect(&rcLast, FALSE);
			RECT rc = GetItemRect(nTab);
			CClientDC dc(m_hWnd);
			HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
			HPEN hOldPen = (HPEN)SelectObject(dc, hPen);
			if(nTab < m_nTab) {
				MoveToEx(dc, rc.left, rc.top, NULL);
				LineTo(dc, rc.left, rc.bottom - 2);
			}
			else {
				MoveToEx(dc, rc.right, rc.top, NULL);
				LineTo(dc, rc.right, rc.bottom - 2);
			}
			SelectObject(dc, hOldPen);
			DeleteObject(hPen);
			if(nTab > m_nTab) {
				rc.left = rc.right - 4;
				rc.right += 4;
			}
			else {
				rc.right = rc.left + 4;
				rc.left -= 4;
			}
			rcLast = rc;
			rcLast.top -= 1;
			ValidateRect(m_hWnd, &rc);
		}
		else m_rMainWnd.InvalidateRect(&rcLast, FALSE);
	}
}
//----------------------------------------------------------------------------
// コモンコントロールからの通知が来た
//----------------------------------------------------------------------------
LRESULT CTab_MainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->hwndFrom == (HWND)m_rMainWnd.GetPlayList())
		return m_rMainWnd.OnNotify(idFrom, pnmhdr);
	return CTab::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CTab_MainWnd::OnReturnKeyPressed()
{
	tstring str = m_edit.GetText();
	SetItem((LPTSTR)str.c_str(), m_nTab);
	m_edit.Show(SW_HIDE);
	m_rMainWnd.ResetSize();
}
//----------------------------------------------------------------------------
