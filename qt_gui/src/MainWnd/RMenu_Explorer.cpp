//----------------------------------------------------------------------------
// RMenu_Explorer.cpp : エクスプローラ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include "RMenu_Explorer.h"
#include <QAction>
#include "MainWnd.h"
#include "Explorer.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CRMenu_Explorer::CRMenu_Explorer(CExplorer & parent, bool bOnItem)
	: m_rParent(parent)
{
	if(bOnItem) {
		auto openAct = new QAction(tr("Open(&O)"), this);
		connect(openAct, &QAction::triggered,
						this, &CRMenu_Explorer::OnOpenFilesMenuSelected);
		addAction(openAct);
		auto addAct = new QAction(tr("Add(&A)"), this);
		connect(addAct, &QAction::triggered,
						this, &CRMenu_Explorer::OnAddFilesMenuSelected);
		addAction(addAct);

		addSeparator();
	}
	auto visibleAct = new QAction(tr("Show Exploler(&S)"), this);
	visibleAct->setCheckable(true);
	visibleAct->setChecked(true);
	connect(visibleAct, &QAction::triggered,
					this, &CRMenu_Explorer::OnVisibleMenuSelected);
	addAction(visibleAct);
}
//----------------------------------------------------------------------------
// 開くメニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnOpenFilesMenuSelected()
{
	m_rParent.OpenFiles(TRUE);
}
//----------------------------------------------------------------------------
// 追加メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnAddFilesMenuSelected()
{
	m_rParent.OpenFiles(FALSE);
}
//----------------------------------------------------------------------------
// エクスプローラの表示メニューが選択された
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnExplorerMenuSelected(false);
}
//----------------------------------------------------------------------------
