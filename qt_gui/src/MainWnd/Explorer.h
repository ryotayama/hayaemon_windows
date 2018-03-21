//----------------------------------------------------------------------------
// Explorer.h : エクスプローラの管理を行う
//----------------------------------------------------------------------------
#ifndef ExplorerH
#define ExplorerH

#include <tuple>
#include <vector>
#include "../Common/Define.h"
#include "../Common/ListView.h"
class CMainWnd;
//----------------------------------------------------------------------------
// エクスプローラの管理を行うクラス
//----------------------------------------------------------------------------
class CExplorer : public CListView
{
	Q_OBJECT

public: // 関数

	explicit CExplorer(QWidget * parent);

	virtual BOOL Create(CMainWnd & mainWnd);
	virtual BOOL OpenDirectory();
	virtual void OpenFiles(BOOL bClear);
	virtual void OpenFolder();
	virtual BOOL ShowFiles();

	virtual void OnContextMenu(const QPoint & pos);
	virtual void OnLButtonDoubleClick(int row, int column);

protected:

	QIcon GetItemIcon(int idx) const override {
		if (idx == -1) { return QIcon(); }
		if (idx == kFolderIconIndex) { return m_folderIcon; }
		return std::get<1>(m_extIconList[idx]);
	}

private: // メンバ変数

	static const int kFolderIconIndex = -2;

	CMainWnd * m_rMainWnd;
	std::vector<QString> filePaths;

	std::vector<std::tuple<QString, QIcon>> m_extIconList;
	QIcon m_folderIcon;

public: // メンバ変数の取得・設定

	CMainWnd & GetMainWnd() { return *m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif
