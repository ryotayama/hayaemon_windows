//----------------------------------------------------------------------------
// ToolBar.h :ツールバーの作成・管理・破棄を行う
//----------------------------------------------------------------------------
#ifndef ToolBarH
#define ToolBarH

#include "Wnd.h"
#include "Bitmap.h"
#include <vector>
#include <commctrl.h>
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ツールバーの作成・管理・破棄を行うクラス
//----------------------------------------------------------------------------
class CToolBar : public CWnd
{
public: // 関数

	CToolBar() { }
	virtual ~CToolBar() { }

	virtual void CheckButton(int nID, BOOL fCheck);
	virtual BOOL Create(HWND hParentWnd);
	virtual void EnableButton(int nID, BOOL fEnable);
	virtual void HideButton(int nID, BOOL fHide);
	virtual void LoadBitmap(LPCTSTR lpszResourceName);
	virtual void SetButtons(const UINT* lpIDArray, int nIDCount);
	virtual void SetState(int nID, UINT nState);

protected: // メンバ変数

	CBitmap m_bitmap;
	std::vector<TBBUTTON> m_arrayButton;

public: // メンバ変数の取得・設定

	virtual std::vector<TBBUTTON> GetArrayButton() const
	{
		return m_arrayButton;
	}
};
//----------------------------------------------------------------------------

#endif