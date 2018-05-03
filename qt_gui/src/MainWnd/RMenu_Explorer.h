//----------------------------------------------------------------------------
// RMenu_Explorer.h : エクスプローラ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_ExplorerH
#define RMenu_ExplorerH

#include <QMenu>
class CExplorer;
//----------------------------------------------------------------------------
// エクスプローラ用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_Explorer : public QMenu
{
	Q_OBJECT

public: // 関数

	CRMenu_Explorer(CExplorer & parent, bool bOnItem);

	void OnOpenFilesMenuSelected();
	void OnAddFilesMenuSelected();
	void OnOpenFolderMenuSelected();
	void OnVisibleMenuSelected();

private: // メンバ変数

	CExplorer & m_rParent;
};
//----------------------------------------------------------------------------

#endif
