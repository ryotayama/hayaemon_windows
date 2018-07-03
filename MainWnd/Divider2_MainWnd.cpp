//----------------------------------------------------------------------------
// Divider2_MainWnd.cpp : ‹æØ‚èü‚»‚Ì‚Q‚ÌŠÇ—‚ğs‚¤
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "Divider2_MainWnd.h"
#include "TimeSlider_MainWnd.h"
//----------------------------------------------------------------------------
// ì¬
//----------------------------------------------------------------------------
BOOL CDivider2_MainWnd::Create()
{
	CStatic::Create(SS_SUNKEN);
	if(!m_hWnd) return FALSE;
	SetParent(m_rMainWnd);
	ResetPos();
	ResetSize();

	return TRUE;
}
//----------------------------------------------------------------------------
// ‚‚³‚ğ“¾‚é
//----------------------------------------------------------------------------
int CDivider2_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_FREQ) ||
		m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CStatic::GetHeight() + m_rMainWnd.GetControlOffset();
	else return m_rMainWnd.GetTimeSlider().GetHeight();
}
//----------------------------------------------------------------------------
// cˆÊ’u‚ğ“¾‚é
//----------------------------------------------------------------------------
int CDivider2_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_FREQ) ||
		m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CStatic::GetTop();
	else return m_rMainWnd.GetTimeSlider().GetTop();
}
//----------------------------------------------------------------------------
// ˆÊ’u‚ğÄİ’è
//----------------------------------------------------------------------------
void CDivider2_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetTimeSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(0, pt.y + m_rMainWnd.GetTimeSlider().GetHeight()
			+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
