//----------------------------------------------------------------------------
// RMenu_MainWnd.cpp : 再生時間設定用スライダ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "TimeSlider_MainWnd.h"
#include "RMenu_TimeSlider.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_TimeSlider::Create(BOOL bOnMarker)
{
	CMenu::CreatePopup();
	if(bOnMarker) {
#if JP
		Append(MFS_ENABLED, ID_DELETE, _T("削除(&D)"));
#else // JP
		Append(MFS_ENABLED, ID_DELETE, _T("Delete(&D)"));
#endif // JP
		AppendSeparator();
	}
#if JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("再生位置スライダの表示(&V)"));
#else // JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show Position Slider(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_TimeSlider::OnCommand(int id, HWND/* hwndCtl*/,
								  UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_DELETE:
		OnDeleteMenuSelected();
		break;
	case ID_VISIBLE:
		OnVisibleMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// 削除メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_TimeSlider::OnDeleteMenuSelected()
{
	m_rParent.DeleteMarker();
}
//----------------------------------------------------------------------------
// 再生位置スライダの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_TimeSlider::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnTimeSliderMenuSelected();
}
//----------------------------------------------------------------------------
