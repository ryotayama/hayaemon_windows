//----------------------------------------------------------------------------
// PresetMenu.h : プリセット用メニューの管理を行う
//----------------------------------------------------------------------------
#ifndef PresetMenuH
#define PresetMenuH

#include <unordered_map>
#include "../Common/Define.h"
class CMainWnd;
class QAction;
//----------------------------------------------------------------------------
// プリセット用メニューの管理を行うクラス
//----------------------------------------------------------------------------
class CPresetMenu
{
public: // 関数

	explicit CPresetMenu(CMainWnd & mainWnd,
											 std::unordered_map<UINT, QAction*> &actionMap)
		: m_rMainWnd(mainWnd), m_rActionMap(actionMap) { }

	virtual BOOL Append(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR lpNewItem);
	virtual BOOL AppendSeparator();
	BOOL DeleteMenu(UINT uPosition, UINT uFlags);
	int GetMenuItemCount() const;
	BOOL Insert(UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem,
						LPCTSTR lpNewItem);

private:

	QAction* CreateAction(UINT_PTR uIDNewItem, LPCTSTR lpNewItem);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	std::unordered_map<UINT, QAction*> & m_rActionMap;
};
//----------------------------------------------------------------------------
// Win32 APIのラッパー
BOOL DeleteMenu(CPresetMenu & menu, UINT uPosition, UINT uFlags);
int GetMenuItemCount(const CPresetMenu & menu);
//----------------------------------------------------------------------------

#endif
