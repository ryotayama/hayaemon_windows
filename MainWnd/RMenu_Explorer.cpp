//----------------------------------------------------------------------------
// RMenu_Explorer.cpp : エクスプローラ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "Explorer.h"
#include "RMenu_Explorer.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_Explorer::Create(BOOL bOnItem)
{
	CMenu::CreatePopup();

	if(bOnItem) {
#if JP
		Append(MFS_ENABLED, ID_OPEN, _T("開く(&O)"));
		Append(MFS_ENABLED, ID_ADD, _T("追加(&A)"));
#else // JP
		Append(MFS_ENABLED, ID_OPEN, _T("Open(&O)"));
		Append(MFS_ENABLED, ID_ADD, _T("Add(&A)"));
#endif // JP

		AppendSeparator();
#if JP
		Append(MFS_ENABLED, ID_OPENFOLDER, _T("フォルダを開く(&O)"));
		Append(MFS_ENABLED, ID_PROPERTIES, _T("プロパティ(&R)"));
#else // JP
		Append(MFS_ENABLED, ID_OPENFOLDER, _T("Open Folder(&O)"));
		Append(MFS_ENABLED, ID_PROPERTIES, _T("Properties(&R)"));
#endif // JP
		AppendSeparator();
	}
#if JP
	Append(MF_CHECKED, ID_VISIBLE, _T("エクスプローラの表示(&V)"));
#else // JP
	Append(MF_CHECKED, ID_VISIBLE, _T("Show Exploler(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	if(id == ID_OPEN) OnOpenFilesMenuSelected();
	else if(id == ID_ADD) OnAddFilesMenuSelected();
	else if(id == ID_OPENFOLDER) OnOpenFolderMenuSelected();
	else if(id == ID_PROPERTIES) OnPropertiesMenuSelected();
	else if(id == ID_VISIBLE) OnVisibleMenuSelected();
}
//----------------------------------------------------------------------------
// 開くメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnOpenFilesMenuSelected()
{
	m_rParent.OpenFiles(TRUE);
}
//----------------------------------------------------------------------------
// 追加メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnAddFilesMenuSelected()
{
	m_rParent.OpenFiles(FALSE);
}
//----------------------------------------------------------------------------
// フォルダを開くメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnOpenFolderMenuSelected()
{
	m_rParent.OpenFolder();
}
//----------------------------------------------------------------------------
// プロパティメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnPropertiesMenuSelected()
{
	m_rParent.ShowProperties();
}
//----------------------------------------------------------------------------
// エクスプローラの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnExplorerMenuSelected();
}
//----------------------------------------------------------------------------
