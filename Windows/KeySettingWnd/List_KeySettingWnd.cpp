//----------------------------------------------------------------------------
// List_KeySettingWnd.cpp : キーカスタマイズ用ウィンドウ内のリストの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "KeySettingWnd_MainWnd.h"
#include "List_KeySettingWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CList_KeySettingWnd::CList_KeySettingWnd(CKeySettingWnd_MainWnd & parent)
	: m_rParent(parent)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CList_KeySettingWnd::~CList_KeySettingWnd()
{
}
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CList_KeySettingWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
	CListView::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
