//----------------------------------------------------------------------------
// ButtonExt.h : ボタン（拡張版）の作成・管理を行う
//----------------------------------------------------------------------------
#ifndef ButtonExtH
#define ButtonExtH

#include "Wnd.h"
#include "Button.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ボタン（拡張版）の作成・管理を行うクラス
//----------------------------------------------------------------------------
class CButtonExt : public CButton
{
public: // 関数

	CButtonExt(CWnd & parent)
		: m_rParent(parent) { }
	virtual ~CButtonExt() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnKeyUp(UINT vk, UINT lKeyData);

private: // メンバ変数

	CWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif