//----------------------------------------------------------------------------
// ExplorerBar.cpp : エクスプローラ用ツールバーの管理を行う
//----------------------------------------------------------------------------
#include "ExplorerBar.h"
#include <QDir>
#include <QLineEdit>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CExplorerBar::CExplorerBar(QWidget * parent)
	: m_rMainWnd(nullptr), m_edit(*this)
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CExplorerBar::Create(CMainWnd * mainWnd)
{
	m_rMainWnd = mainWnd;
	connect(&m_edit, &QLineEdit::returnPressed,
					this, &CExplorerBar::OnReturnKeyPressed);
	return TRUE;
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CExplorerBar::OnReturnKeyPressed()
{
	QString chPath = QDir::current().absolutePath();

	if(m_edit.text() != chPath) {
		QDir::setCurrent(m_edit.text());
		if(!m_rMainWnd->GetExplorer().ShowFiles()) {
			QDir::setCurrent(chPath);
			m_rMainWnd->GetExplorer().ShowFiles();
		}
	}
}
//----------------------------------------------------------------------------
