//----------------------------------------------------------------------------
// EditExt.cpp : エディットコントロール（拡張版）の作成・管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "Wnd.h"
#include "EditExt.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEditExt::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0)
			m_rParent.SetPreviousFocus();
		else
			m_rParent.SetNextFocus();
		break;
	case VK_RETURN:
		m_rParent.OnReturnKeyPressed();
		break;
	case VK_ESCAPE:
		m_rParent.OnEscKeyPressed();
		break;
	}
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// キーが離された
//----------------------------------------------------------------------------
void CEditExt::OnKeyUp(UINT vk, UINT lKeyData)
{
	switch(vk)
	{
	case VK_SPACE:
		m_rParent.OnSpaceKeyPressed();
		break;
	}
	CEdit::OnKeyUp(vk, lKeyData);
}
//----------------------------------------------------------------------------
