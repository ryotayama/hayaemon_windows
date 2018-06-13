//----------------------------------------------------------------------------
// RMenu_Tab.cpp : タブ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "Tab_MainWnd.h"
#include "RMenu_Tab.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_Tab::Create()
{
	CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_CLOSE, _T("閉じる(&C)"));
	Append(MFS_ENABLED, ID_RENAME, _T("名前の変更(&R)"));
#else // JP
	Append(MFS_ENABLED, ID_CLOSE, _T("Close(&C)"));
	Append(MFS_ENABLED, ID_RENAME, _T("Rename(&R)"));
#endif // JP
	AppendSeparator();
#if JP
	Append(MFS_ENABLED, ID_NEWTAB, _T("新しいタブ(&N)"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_VISIBLE, _T("タブの表示(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_NEWTAB, _T("New tab(&N)"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show Tab(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	else return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Tab::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_CLOSE:
		OnCloseMenuSelected();
		break;
	case ID_RENAME:
		OnRenameMenuSelected();
		break;
	case ID_NEWTAB:
		OnNewTabMenuSelected();
		break;
	case ID_VISIBLE:
		OnVisibleMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// 閉じるメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Tab::OnCloseMenuSelected()
{
	m_rParent.CloseTab();
}
//----------------------------------------------------------------------------
// 名前の変更メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Tab::OnRenameMenuSelected()
{
	m_rParent.ShowEdit();
}
//----------------------------------------------------------------------------
// 新しいタブメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Tab::OnNewTabMenuSelected()
{
	m_rParent.GetMainWnd().CreateNewList();
}
//----------------------------------------------------------------------------
// タブの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Tab::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnTabMenuSelected();
}
//----------------------------------------------------------------------------
