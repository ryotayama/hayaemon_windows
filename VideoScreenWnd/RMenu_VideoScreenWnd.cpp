//----------------------------------------------------------------------------
// RMenu_VideoScreenWnd.cpp : ビデオ画面用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../MainWnd/MainWnd.h"
#include "VideoScreenWnd_MainWnd.h"
#include "RMenu_VideoScreenWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_VideoScreenWnd::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_CHECKED, ID_FULLSCREEN, _T("全画面表示(&F)"));
#else // JP
	Append(MFS_CHECKED, ID_FULLSCREEN, _T("FullScreen(&F)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_VideoScreenWnd::OnCommand(int id, HWND/* hwndCtl*/,
								  UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_FULLSCREEN:
		OnFullScreenMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// 全画面表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_VideoScreenWnd::OnFullScreenMenuSelected()
{
	m_rParent.GetMainWnd().SetFullScreen();
}
//----------------------------------------------------------------------------
