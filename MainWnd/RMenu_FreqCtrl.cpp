//----------------------------------------------------------------------------
// RMenu_FreqCtrl.cpp : 再生周波数コントロール用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "RMenu_FreqCtrl.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_FreqCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_RESETFREQ, _T("デフォルトに戻す(&R)"));
	AppendSeparator();
	m_setFreqMenu.CreatePopup();
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_50, _T("50%(&A)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_60, _T("60%(&B)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_70, _T("70%(&C)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_80, _T("80%(&D)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_90, _T("90%(&E)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_100, _T("100%(&F)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_110, _T("110%(&G)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_120, _T("120%(&H)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_130, _T("130%(&I)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_140, _T("140%(&J)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_150, _T("150%(&K)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_160, _T("160%(&L)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_170, _T("170%(&M)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_180, _T("180%(&N)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_190, _T("190%(&O)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_200, _T("200%(&P)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_250, _T("250%(&Q)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_300, _T("300%(&R)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_350, _T("350%(&S)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_400, _T("400%(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setFreqMenu, _T("周波数指定(&F)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_DOWN0_1FREQ, _T("0.1%下げる(&0)"));
	Append(MFS_ENABLED, ID_DOWN1FREQ, _T("1%下げる(&1)"));
	Append(MFS_ENABLED, ID_DOWN2FREQ, _T("2%下げる(&2)"));
	Append(MFS_ENABLED, ID_DOWN3FREQ, _T("3%下げる(&3)"));
	Append(MFS_ENABLED, ID_DOWN5FREQ, _T("5%下げる(&5)"));
	Append(MFS_ENABLED, ID_DOWN10FREQ, _T("10%下げる(&T)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_UP0_1FREQ, _T("0.1%上げる(&Z)"));
	Append(MFS_ENABLED, ID_UP1FREQ, _T("1%上げる(&A)"));
	Append(MFS_ENABLED, ID_UP2FREQ, _T("2%上げる(&B)"));
	Append(MFS_ENABLED, ID_UP3FREQ, _T("3%上げる(&C)"));
	Append(MFS_ENABLED, ID_UP5FREQ, _T("5%上げる(&D)"));
	Append(MFS_ENABLED, ID_UP10FREQ, _T("10%上げる(&E)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_DECFREQ) ?
		MF_CHECKED : MF_ENABLED, ID_DECFREQ, _T("だんだん遅くする(&F)..."));
	Append(m_rParent.GetMenu().IsItemChecked(ID_INCFREQ) ?
		MF_CHECKED : MF_ENABLED, ID_INCFREQ, _T("だんだん速くする(&F)..."));
	AppendSeparator();
	m_freqDecimalMenu.CreatePopup();
	m_freqDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_FREQDEC_0) ?
		MF_CHECKED : MF_ENABLED, ID_FREQDEC_0, _T("0桁(&0)"));
	m_freqDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_FREQDEC_1) ?
		MF_CHECKED : MF_ENABLED, ID_FREQDEC_1, _T("1桁(&1)"));
	m_freqDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_FREQDEC_2) ?
		MF_CHECKED : MF_ENABLED, ID_FREQDEC_2, _T("2桁(&2)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqDecimalMenu, _T("小数点桁数"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_FREQ, _T("再生周波数コントロールの表示(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_RESETFREQ, _T("Reset(&R)"));
	AppendSeparator();
	m_setFreqMenu.CreatePopup();
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_50, _T("50%(&A)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_60, _T("60%(&B)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_70, _T("70%(&C)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_80, _T("80%(&D)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_90, _T("90%(&E)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_100, _T("100%(&F)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_110, _T("110%(&G)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_120, _T("120%(&H)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_130, _T("130%(&I)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_140, _T("140%(&J)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_150, _T("150%(&K)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_160, _T("160%(&L)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_170, _T("170%(&M)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_180, _T("180%(&N)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_190, _T("190%(&O)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_200, _T("200%(&P)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_250, _T("250%(&Q)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_300, _T("300%(&R)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_350, _T("350%(&S)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_400, _T("400%(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setFreqMenu, _T("Set Frequency(&F)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_DOWN0_1FREQ, _T("Turn down 0.1%(&0)"));
	Append(MFS_ENABLED, ID_DOWN1FREQ, _T("Turn down 1%(&1)"));
	Append(MFS_ENABLED, ID_DOWN2FREQ, _T("Turn down 2%(&2)"));
	Append(MFS_ENABLED, ID_DOWN3FREQ, _T("Turn down 3%(&3)"));
	Append(MFS_ENABLED, ID_DOWN5FREQ, _T("Turn down 5%(&5)"));
	Append(MFS_ENABLED, ID_DOWN10FREQ, _T("Turn down 10%(&T)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_UP0_1FREQ, _T("Turn up 0.1%(&Z)"));
	Append(MFS_ENABLED, ID_UP1FREQ, _T("Turn up 1%(&A)"));
	Append(MFS_ENABLED, ID_UP2FREQ, _T("Turn up 2%(&B)"));
	Append(MFS_ENABLED, ID_UP3FREQ, _T("Turn up 3%(&C)"));
	Append(MFS_ENABLED, ID_UP5FREQ, _T("Turn up 5%(&D)"));
	Append(MFS_ENABLED, ID_UP10FREQ, _T("Turn up 10%(&E)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_DECFREQ) ?
		MF_CHECKED : MF_ENABLED, ID_DECFREQ, _T("Decrease(&F)..."));
	Append(m_rParent.GetMenu().IsItemChecked(ID_INCFREQ) ?
		MF_CHECKED : MF_ENABLED, ID_INCFREQ, _T("Increase(&F)..."));
	AppendSeparator();
	m_freqDecimalMenu.CreatePopup();
	m_freqDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_FREQDEC_0) ?
		MF_CHECKED : MF_ENABLED, ID_FREQDEC_0, _T("0 digit(&0)"));
	m_freqDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_FREQDEC_1) ?
		MF_CHECKED : MF_ENABLED, ID_FREQDEC_1, _T("1 digit(&1)"));
	m_freqDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_FREQDEC_2) ?
		MF_CHECKED : MF_ENABLED, ID_FREQDEC_2, _T("2 digit(&2)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqDecimalMenu, _T("Decimal digit"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_FREQ, _T("Show Frequency Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_FreqCtrl::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	m_rParent.GetMenu().OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
