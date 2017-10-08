//----------------------------------------------------------------------------
// Divider4_MainWnd.cpp : ‹æØ‚èü‚»‚Ì‚S‚ÌŠÇ—‚ğs‚¤
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "Divider4_MainWnd.h"
//----------------------------------------------------------------------------
// ‚‚³‚ğ“¾‚é
//----------------------------------------------------------------------------
int CDivider4_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EQ))
		return CStatic::GetHeight() + m_rMainWnd.GetControlOffset();
	else return m_rMainWnd.GetPanSlider().GetHeight();
}
//----------------------------------------------------------------------------
// cˆÊ’u‚ğ“¾‚é
//----------------------------------------------------------------------------
int CDivider4_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EQ))
		return CStatic::GetTop();
	else return m_rMainWnd.GetPanSlider().GetTop();
}
//----------------------------------------------------------------------------
// ˆÊ’u‚ğÄİ’è
//----------------------------------------------------------------------------
void CDivider4_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetPanSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetExplorer().GetWidth(),
		pt.y + m_rMainWnd.GetPanSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
