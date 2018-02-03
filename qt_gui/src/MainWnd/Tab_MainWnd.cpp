//----------------------------------------------------------------------------
// Tab_MainWnd.cpp : タブの管理を行う
//----------------------------------------------------------------------------
#include "Tab_MainWnd.h"
#include <functional>
#include <QAction>
#include <QMenu>
#include <QTabBar>
#include "MainWnd.h"
#include "Menu_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CTab_MainWnd::CTab_MainWnd(QWidget * parent /* = nullptr */)
	: CTab(parent), m_rMainWnd(nullptr), m_closeAct(nullptr),
		m_renameAct(nullptr), m_newTabAct(nullptr), m_showTabAct(nullptr),
		m_nTab(0)
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QWidget::customContextMenuRequested,
					std::bind(&CTab_MainWnd::OnContextMenu, this, 
										std::placeholders::_1));
}
//----------------------------------------------------------------------------
// 新しいタブを追加
//----------------------------------------------------------------------------
void CTab_MainWnd::AddNewTab(QWidget * page, BOOL bChangeFocus)
{
	int nSelect = !bChangeFocus ? GetItemCount() :
								 GetCurrentFocus() + 1;
	insertTab(nSelect, page, tr("No Title"));
	if(bChangeFocus) SetCurrentFocus(nSelect);
}
//----------------------------------------------------------------------------
// タブを閉じる
//----------------------------------------------------------------------------
void CTab_MainWnd::CloseTab()
{
	m_rMainWnd->DeleteArrayList(m_nTab);
	if(GetItemCount() > 1) {
		int nFocus = m_nTab > 0 ? m_nTab - 1 : m_nTab;
		SetCurrentFocus(nFocus);
	}
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTab_MainWnd::Create(CMainWnd * mainWnd)
{
	m_rMainWnd = mainWnd;

	m_closeAct = new QAction(tr("Close(&C)"), this);
	connect(m_closeAct, &QAction::triggered, this, &CTab_MainWnd::CloseTab);

	m_renameAct = new QAction(tr("Rename(&R)"), this);
	connect(m_renameAct, &QAction::triggered, this, &CTab_MainWnd::ShowEdit);

	m_newTabAct = new QAction(tr("New tab(&N)"), this);
	connect(m_newTabAct, &QAction::triggered, mainWnd, &CMainWnd::CreateNewList);

	m_showTabAct = new QAction(tr("Show Tab(&S)"), this);
	connect(m_showTabAct, &QAction::triggered,
					&mainWnd->GetMenu(), &CMenu_MainWnd::OnTabMenuSelected);

	return TRUE;
}
//----------------------------------------------------------------------------
// エディットコントロールの表示
//----------------------------------------------------------------------------
void CTab_MainWnd::ShowEdit()
{
	// TODO Implement
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
void CTab_MainWnd::OnContextMenu(const QPoint & pos)
{
	m_nTab = HitTest(pos);
	if (m_nTab >= 0) {
		QMenu menu;
		menu.addAction(m_closeAct);
		menu.addAction(m_renameAct);
		menu.addSeparator();
		menu.addAction(m_newTabAct);
		menu.addAction(m_showTabAct);
		menu.exec(this->mapToGlobal(pos));
	}
}
//----------------------------------------------------------------------------
// 座標からタブのインデックスを取得する
//----------------------------------------------------------------------------
int CTab_MainWnd::HitTest(const QPoint & pos) const
{
	QTabBar *tabBar = this->tabBar();
	return tabBar->tabAt(pos);
}
//----------------------------------------------------------------------------
