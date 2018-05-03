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
		addSeparator();
		auto editTagMenu = new QMenu(tr("Edit the Tag(&T)"));
		auto editTitleAct = new QAction(tr("Title(&T)"), this);
		connect(editTitleAct, &QAction::triggered,
						this, &CRMenu_ListView::OnEditTitleMenuSelected);
		editTagMenu->addAction(editTitleAct);
		auto editArtistAct = new QAction(tr("Artist(&A)"), this);
		connect(editArtistAct, &QAction::triggered,
						this, &CRMenu_ListView::OnEditArtistMenuSelected);
		editTagMenu->addAction(editArtistAct);
		auto editYearAct = new QAction(tr("Year(&Y)"), this);
		connect(editYearAct, &QAction::triggered,
						this, &CRMenu_ListView::OnEditYearMenuSelected);
		editTagMenu->addAction(editYearAct);
		addMenu(editTagMenu);
		auto openFolderAct = new QAction(tr("Open Folder(&O)"), this);
		connect(openFolderAct, &QAction::triggered,
						this, &CRMenu_ListView::OnOpenFolderMenuSelected);
		addAction(openFolderAct);
		addSeparator();
	}
	auto visibleAct = new QAction(tr("Show Play List(&S)"), this);
	visibleAct->setCheckable(true);
	visibleAct->setChecked(true);
	connect(visibleAct, &QAction::triggered,
					this, &CRMenu_ListView::OnVisibleMenuSelected);
	addAction(visibleAct);
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
// タイトルタグの編集メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnEditTitleMenuSelected()
{
	for (auto item : m_rParent.GetMainWnd().GetPlayList().selectedItems()) {
		if (item->column() == 2) {
			m_rParent.GetMainWnd().GetPlayList().editItem(item);
			break;
		}
	}
}
//----------------------------------------------------------------------------
// アーティストタグの編集メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnEditArtistMenuSelected()
{
	for (auto item : m_rParent.GetMainWnd().GetPlayList().selectedItems()) {
		if (item->column() == 3) {
			m_rParent.GetMainWnd().GetPlayList().editItem(item);
			break;
		}
	}
}
//----------------------------------------------------------------------------
// 年タグの編集メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnEditYearMenuSelected()
{
	for (auto item : m_rParent.GetMainWnd().GetPlayList().selectedItems()) {
		if (item->column() == 4) {
			m_rParent.GetMainWnd().GetPlayList().editItem(item);
			break;
		}
	}
}
//----------------------------------------------------------------------------
// フォルダを開くメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnOpenFolderMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().OpenFolder();
}
//----------------------------------------------------------------------------
// 再生リストの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_ListView::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnPlayListMenuSelected(false);
}
//----------------------------------------------------------------------------
