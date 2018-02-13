//----------------------------------------------------------------------------
// RMenu_ListView.cpp : 再生リスト用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include "RMenu_ListView.h"
#include "MainWnd.h"
#include "PlayListView_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CRMenu_ListView::CRMenu_ListView(CPlayListView_MainWnd & parent, bool bOnItem)
	: m_rParent(parent)
{
	if(bOnItem) {
		auto copyMenu = new QMenu(tr("Copy Selected Files(&C)"), this);
		auto newlistAct = new QAction(tr("New Playlist(&N)"), this);
		connect(newlistAct, &QAction::triggered,
						&m_rParent, &CPlayListView_MainWnd::CreateNewList);
		copyMenu->addAction(newlistAct);
		int nTabCount = m_rParent.GetMainWnd().GetTab().GetItemCount();
		if(nTabCount >= 2) copyMenu->addSeparator();
		for(int i = 0; i < nTabCount; i++) {
			if(&m_rParent.GetMainWnd().GetPlayList(i) != &m_rParent) {
				auto copyAct =
					new QAction(m_rParent.GetMainWnd().GetTab().GetItemText(i), this);
				connect(copyAct, &QAction::triggered,
								[=] { m_rParent.CopySelectedItem(i); });
				copyMenu->addAction(copyAct);
			}
		}
		auto playAct = new QAction(tr("Play(&P)"), this);
		connect(playAct, &QAction::triggered,
						this, &CRMenu_ListView::OnPlayMenuSelected);
		addAction(playAct);
		auto deleteAct = new QAction(tr("Delete(&D)"), this);
		connect(deleteAct, &QAction::triggered,
						this, &CRMenu_ListView::OnDeleteMenuSelected);
		addAction(deleteAct);
		addSeparator();
		addMenu(copyMenu);
	}
}
//----------------------------------------------------------------------------
// 削除メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnDeleteMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().DeleteSelectedItems();
}
//----------------------------------------------------------------------------
// 再生メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnPlayMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().PlaySelectedItem();
}
//----------------------------------------------------------------------------
