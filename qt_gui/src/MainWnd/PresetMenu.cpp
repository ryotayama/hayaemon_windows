//----------------------------------------------------------------------------
// PresetMenu.cpp : プリセット用メニューの管理を行う
//----------------------------------------------------------------------------
#include "PresetMenu.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <QAction>
#include <QMenu>
#include "MainWnd.h"
#include "Utility.h"

//----------------------------------------------------------------------------
// メニューの末尾に新しい項目を追加
//----------------------------------------------------------------------------
BOOL CPresetMenu::Append(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR lpNewItem)
{
	auto action = CreateAction(uIDNewItem, lpNewItem);
	m_rMainWnd.menuPreset->addAction(action);
	m_rActionMap.insert(std::make_pair(static_cast<UINT>(uIDNewItem), action));
	return TRUE;
}
//----------------------------------------------------------------------------
// メニューの末尾に区切り線を追加
//----------------------------------------------------------------------------
BOOL CPresetMenu::AppendSeparator()
{
	m_rMainWnd.menuPreset->addSeparator();
	return TRUE;
}
BOOL CPresetMenu::DeleteMenu(UINT uPosition, UINT uFlags)
{
	auto actions = m_rMainWnd.menuPreset->actions();
	QAction *action = nullptr;
	if (uFlags == MF_BYCOMMAND) {
		auto it = std::find_if(actions.begin(), actions.end(),
			[&] (QAction * act) { return uPosition == act->data().toUInt(); });
		if (it != std::end(actions)) {
			action = *it;
		}
	} else if (uFlags == MF_BYPOSITION) {
		if (static_cast<int>(uPosition) < actions.size()) {
			action = actions[uPosition];
		}
	}

	if (action == nullptr) {
		return FALSE;
	}

	if (!action->isSeparator()) {
		UINT id = action->data().toUInt();
		auto it = m_rActionMap.find(id);
		if (it != std::end(m_rActionMap)) {
			m_rActionMap.erase(it);
		}
	}
	m_rMainWnd.menuPreset->removeAction(action);

	return TRUE;
}
int CPresetMenu::GetMenuItemCount() const
{
	return m_rMainWnd.menuPreset->actions().size();
}
//----------------------------------------------------------------------------
// メニューに新しい項目を挿入
//----------------------------------------------------------------------------
BOOL CPresetMenu::Insert(UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem,
					LPCTSTR lpNewItem)
{
	QAction *before = nullptr;
	if (uFlags == MF_BYCOMMAND) {
		auto it = m_rActionMap.find(uPosition);
		if (it != std::end(m_rActionMap)) {
			before = it->second;
		}
	}

	assert(before != nullptr);
	if (before == nullptr) {
		return FALSE;
	}

	auto action = CreateAction(uIDNewItem, lpNewItem);
	m_rMainWnd.menuPreset->insertAction(before, action);
	m_rActionMap.insert(std::make_pair(static_cast<UINT>(uIDNewItem), action));
	return TRUE;
}
QAction* CPresetMenu::CreateAction(UINT_PTR uIDNewItem, LPCTSTR lpNewItem)
{
	auto action = new QAction(&m_rMainWnd);
	action->setText(ToQString(lpNewItem));
	action->setData(uIDNewItem);
	action->setCheckable(true);
	QObject::connect(
		action, &QAction::triggered,
		[this,uIDNewItem] {
				m_rMainWnd.GetMenu().OnPresetMenuSelected(uIDNewItem); });
	return action;
}
//----------------------------------------------------------------------------
// Win32 APIのラッパー
//----------------------------------------------------------------------------
BOOL DeleteMenu(CPresetMenu & menu, UINT uPosition, UINT uFlags)
{
	return menu.DeleteMenu(uPosition, uFlags);
}
int GetMenuItemCount(const CPresetMenu & menu)
{
	return menu.GetMenuItemCount();
}
//----------------------------------------------------------------------------
