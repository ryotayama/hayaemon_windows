//----------------------------------------------------------------------------
// RMenu_ListView.h : 再生リスト用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_ListViewH
#define RMenu_ListViewH

#include <QMenu>
class CPlayListView_MainWnd;
//----------------------------------------------------------------------------
// 再生リスト用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_ListView : public QMenu
{
	Q_OBJECT

public: // 関数

	CRMenu_ListView(CPlayListView_MainWnd & parent, bool bOnItem);

	void OnDeleteMenuSelected();
	void OnPlayMenuSelected();
	void OnEditTitleMenuSelected();
	void OnEditArtistMenuSelected();
	void OnEditYearMenuSelected();
	void OnOpenFolderMenuSelected();
	void OnVisibleMenuSelected();

private: // メンバ変数

	CPlayListView_MainWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif
