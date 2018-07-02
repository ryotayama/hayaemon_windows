//----------------------------------------------------------------------------
// RMenu_EQCtrl.cpp : EQコントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "RMenu_EQCtrl.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_EQCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("グラフィックイコライザの表示(&V)"));
#else // JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show EQ Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_EQCtrl::OnCommand(int id, HWND/* hwndCtl*/,
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
// EQの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_EQCtrl::OnVisibleMenuSelected()
{
	m_rParent.GetMenu().OnEQMenuSelected();
}
//----------------------------------------------------------------------------
