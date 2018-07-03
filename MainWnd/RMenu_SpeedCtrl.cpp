//----------------------------------------------------------------------------
// RMenu_SpeedCtrl.cpp : 再生速度コントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "RMenu_SpeedCtrl.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_SpeedCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_RESETSPEED, _T("デフォルトに戻す(&R)"));
	AppendSeparator();
	m_setSpeedMenu.CreatePopup();
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_50, _T("50%(&A)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_60, _T("60%(&B)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_70, _T("70%(&C)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_80, _T("80%(&D)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_90, _T("90%(&E)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_100, _T("100%(&F)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_110, _T("110%(&G)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_120, _T("120%(&H)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_130, _T("130%(&I)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_140, _T("140%(&J)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_150, _T("150%(&K)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_160, _T("160%(&L)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_170, _T("170%(&M)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_180, _T("180%(&N)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_190, _T("190%(&O)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_200, _T("200%(&P)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_250, _T("250%(&Q)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_300, _T("300%(&R)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_350, _T("350%(&S)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_400, _T("400%(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setSpeedMenu, _T("速度指定(&S)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_DOWN0_1SPEED, _T("0.1%下げる(&0)"));
	Append(MFS_ENABLED, ID_DOWN1SPEED, _T("1%下げる(&1)"));
	Append(MFS_ENABLED, ID_DOWN2SPEED, _T("2%下げる(&2)"));
	Append(MFS_ENABLED, ID_DOWN3SPEED, _T("3%下げる(&3)"));
	Append(MFS_ENABLED, ID_DOWN5SPEED, _T("5%下げる(&5)"));
	Append(MFS_ENABLED, ID_DOWN10SPEED, _T("10%下げる(&T)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_UP0_1SPEED, _T("0.1%上げる(&Z)"));
	Append(MFS_ENABLED, ID_UP1SPEED, _T("1%上げる(&A)"));
	Append(MFS_ENABLED, ID_UP2SPEED, _T("2%上げる(&B)"));
	Append(MFS_ENABLED, ID_UP3SPEED, _T("3%上げる(&C)"));
	Append(MFS_ENABLED, ID_UP5SPEED, _T("5%上げる(&D)"));
	Append(MFS_ENABLED, ID_UP10SPEED, _T("10%上げる(&E)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_DECSPEED) ?
		MF_CHECKED : MF_ENABLED, ID_DECSPEED, _T("だんだん遅くする(&D)..."));
	Append(m_rParent.GetMenu().IsItemChecked(ID_INCSPEED) ?
		MF_CHECKED : MF_ENABLED, ID_INCSPEED, _T("だんだん速くする(&D)..."));
	AppendSeparator();
	m_speedDecimalMenu.CreatePopup();
	m_speedDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_SPEEDDEC_0) ?
		MF_CHECKED : MF_ENABLED, ID_SPEEDDEC_0, _T("0桁(&0)"));
	m_speedDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_SPEEDDEC_1) ?
		MF_CHECKED : MF_ENABLED, ID_SPEEDDEC_1, _T("1桁(&1)"));
	m_speedDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_SPEEDDEC_2) ?
		MF_CHECKED : MF_ENABLED, ID_SPEEDDEC_2, _T("2桁(&2)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedDecimalMenu, _T("小数点桁数"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_SPEED, _T("再生速度コントロールの表示(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_RESETSPEED, _T("Reset(&R)"));
	AppendSeparator();
	m_setSpeedMenu.CreatePopup();
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_50, _T("50%(&A)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_60, _T("60%(&B)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_70, _T("70%(&C)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_80, _T("80%(&D)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_90, _T("90%(&E)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_100, _T("100%(&F)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_110, _T("110%(&G)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_120, _T("120%(&H)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_130, _T("130%(&I)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_140, _T("140%(&J)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_150, _T("150%(&K)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_160, _T("160%(&L)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_170, _T("170%(&M)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_180, _T("180%(&N)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_190, _T("190%(&O)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_200, _T("200%(&P)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_250, _T("250%(&Q)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_300, _T("300%(&R)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_350, _T("350%(&S)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_400, _T("400%(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setSpeedMenu, _T("Set Speed(&S)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_DOWN0_1SPEED, _T("Turn down 0.1%(&0)"));
	Append(MFS_ENABLED, ID_DOWN1SPEED, _T("Turn down 1%(&1)"));
	Append(MFS_ENABLED, ID_DOWN2SPEED, _T("Turn down 2%(&2)"));
	Append(MFS_ENABLED, ID_DOWN3SPEED, _T("Turn down 3%(&3)"));
	Append(MFS_ENABLED, ID_DOWN5SPEED, _T("Turn down 5%(&5)"));
	Append(MFS_ENABLED, ID_DOWN10SPEED, _T("Turn down 10%(&T)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_UP0_1SPEED, _T("Turn up 0.1%(&Z)"));
	Append(MFS_ENABLED, ID_UP1SPEED, _T("Turn up 1%(&A)"));
	Append(MFS_ENABLED, ID_UP2SPEED, _T("Turn up 2%(&B)"));
	Append(MFS_ENABLED, ID_UP3SPEED, _T("Turn up 3%(&C)"));
	Append(MFS_ENABLED, ID_UP5SPEED, _T("Turn up 5%(&D)"));
	Append(MFS_ENABLED, ID_UP10SPEED, _T("Turn up 10%(&E)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_DECSPEED) ?
		MF_CHECKED : MF_ENABLED, ID_DECSPEED, _T("Decrease(&D)..."));
	Append(m_rParent.GetMenu().IsItemChecked(ID_INCSPEED) ?
		MF_CHECKED : MF_ENABLED, ID_INCSPEED, _T("Increase(&D)..."));
	AppendSeparator();
	m_speedDecimalMenu.CreatePopup();
	m_speedDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_SPEEDDEC_0) ?
		MF_CHECKED : MF_ENABLED, ID_SPEEDDEC_0, _T("0 digit(&0)"));
	m_speedDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_SPEEDDEC_1) ?
		MF_CHECKED : MF_ENABLED, ID_SPEEDDEC_1, _T("1 digit(&1)"));
	m_speedDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_SPEEDDEC_2) ?
		MF_CHECKED : MF_ENABLED, ID_SPEEDDEC_2, _T("2 digit(&2)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedDecimalMenu, _T("Decimal digit"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_SPEED, _T("Show Speed Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_SpeedCtrl::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	m_rParent.GetMenu().OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
