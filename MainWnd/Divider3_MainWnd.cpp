//----------------------------------------------------------------------------
// Divider3_MainWnd.cpp : ‹æØ‚èü‚»‚Ì‚R‚ÌŠÇ—‚ğs‚¤
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "Divider3_MainWnd.h"
#include "PitchSlider_MainWnd.h"
//----------------------------------------------------------------------------
// ‚‚³‚ğ“¾‚é
//----------------------------------------------------------------------------
int CDivider3_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VOLUME) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CStatic::GetHeight() + m_rMainWnd.GetControlOffset();
	else return m_rMainWnd.GetPitchSlider().GetHeight();
}
//----------------------------------------------------------------------------
// cˆÊ’u‚ğ“¾‚é
//----------------------------------------------------------------------------
int CDivider3_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VOLUME) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CStatic::GetTop();
	else return m_rMainWnd.GetPitchSlider().GetTop();
}
//----------------------------------------------------------------------------
// ˆÊ’u‚ğÄİ’è
//----------------------------------------------------------------------------
void CDivider3_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetPitchSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetExplorer().GetWidth(),
		pt.y + m_rMainWnd.GetPitchSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
