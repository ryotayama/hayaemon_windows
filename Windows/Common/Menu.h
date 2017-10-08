//----------------------------------------------------------------------------
// Menu.h : メニューの作成・管理・破棄を行う
//----------------------------------------------------------------------------
#ifndef MenuH
#define MenuH
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// メニューの作成・管理・破棄を行うクラス
//----------------------------------------------------------------------------
class CMenu
{
public: // 関数

	CMenu(): m_hMenu(0) { }
	virtual ~CMenu() { Destroy(); }

	// メニューの末尾に新しい項目を追加
	virtual BOOL Append(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR lpNewItem);

	// メニューの末尾に区切り線を追加
	virtual BOOL AppendSeparator();

	virtual BOOL Create();
	virtual void CheckItem(UINT uIDCheckItem, UINT uCheck) {
		CheckMenuItem(m_hMenu, uIDCheckItem, uCheck);
	}
	virtual BOOL CreatePopup();
	virtual void Destroy();
	virtual void EnableItem(UINT uIDEnableItem, UINT uEnable) {
		EnableMenuItem(m_hMenu, uIDEnableItem, uEnable);
	}
	virtual UINT GetState(UINT uID) {
		return GetMenuState(m_hMenu, uID, MF_BYCOMMAND);
	}
	virtual BOOL Insert(UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem,
						LPCTSTR lpNewItem);
	virtual BOOL IsItemChecked(UINT uID) {
		UINT uRet = GetMenuState(m_hMenu, uID, MF_BYCOMMAND);
		return (BOOL)(uRet & MF_CHECKED);
	}

protected: // メンバ変数

	HMENU m_hMenu;

public: // メンバ変数の取得・設定

	operator HMENU() const { return m_hMenu; }
};
//----------------------------------------------------------------------------

#endif