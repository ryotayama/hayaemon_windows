//----------------------------------------------------------------------------
// EditExt.h : エディットコントロール（拡張版）の作成・管理を行う
//----------------------------------------------------------------------------
#ifndef EditExtH
#define EditExtH

#include "Wnd.h"
#include "Edit.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// エディットコントロール（拡張版）の作成・管理を行うクラス
//----------------------------------------------------------------------------
class CEditExt : public CEdit
{
public: // 関数

	CEditExt(CWnd & parent)
		: m_rParent(parent) { }
	virtual ~CEditExt() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnKeyUp(UINT vk, UINT lKeyData);

protected: // メンバ変数

	CWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif