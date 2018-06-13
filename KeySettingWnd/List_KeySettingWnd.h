//----------------------------------------------------------------------------
// List_KeySettingWnd.h : キーカスタマイズ用ウィンドウ内のリストの管理を行う
//----------------------------------------------------------------------------
#ifndef List_KeySettingWndH
#define List_KeySettingWndH

class CKeySettingWnd_MainWnd;
#include "../Common/ListView.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// キーカスタマイズ用ウィンドウ内のリストの管理を行うクラス
//----------------------------------------------------------------------------
class CList_KeySettingWnd : public CListView
{
public: // 関数

	CList_KeySettingWnd(CKeySettingWnd_MainWnd & parent);
	virtual ~CList_KeySettingWnd();

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CKeySettingWnd_MainWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif