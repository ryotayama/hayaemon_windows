//----------------------------------------------------------------------------
// RMenu_PanCtrl.cpp : パンコントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "RMenu_PanCtrl.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_PanCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("パンの表示(&V)"));
#else // JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show Pan Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_PanCtrl::OnCommand(int id, HWND/* hwndCtl*/,
								  UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_VISIBLE:
		OnVisibleMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// パンの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_PanCtrl::OnVisibleMenuSelected()
{
	m_rParent.GetMenu().OnPanMenuSelected();
}
//----------------------------------------------------------------------------
