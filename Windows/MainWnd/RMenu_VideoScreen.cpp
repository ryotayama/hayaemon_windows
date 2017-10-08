//----------------------------------------------------------------------------
// RMenu_VideoScreen.cpp : ビデオ画面用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "VideoScreen_MainWnd.h"
#include "RMenu_VideoScreen.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_VideoScreen::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_FULLSCREEN, _T("全画面表示(&F)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_LYRICS) ?
		MF_CHECKED : MF_ENABLED, ID_LYRICS, _T("歌詞(&L)"));
	Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHANALYSER) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHANALYSER, _T("ピッチアナライザ(&P)"));
	AppendSeparator();
	Append(MF_CHECKED, ID_VIDEOSCREEN, _T("ビデオ画面の表示(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_FULLSCREEN, _T("FullScreen(&F)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_LYRICS) ?
		MF_CHECKED : MF_ENABLED, ID_LYRICS, _T("Lyrics(&L)"));
	Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHANALYSER) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHANALYSER, _T("Pitch Analyser(&P)"));
	AppendSeparator();
	Append(MF_CHECKED, ID_VIDEOSCREEN, _T("Show Video Screen(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_VideoScreen::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_FULLSCREEN:
		OnFullScreenMenuSelected();
		return;
	}
	m_rParent.GetMenu().OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// 全画面表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_VideoScreen::OnFullScreenMenuSelected()
{
	m_rParent.SetFullScreen();
}
//----------------------------------------------------------------------------
