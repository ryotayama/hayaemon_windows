//----------------------------------------------------------------------------
// Tab_MainWnd.h : タブの管理を行う
//----------------------------------------------------------------------------
#ifndef Tab_MainWndH
#define Tab_MainWndH

#include "../Common/Define.h"
#include "../Common/Tab.h"
class CMainWnd;
class QAction;
class QWidget;
//----------------------------------------------------------------------------
// タブの管理を行うクラス
//----------------------------------------------------------------------------
class CTab_MainWnd : public CTab
{
	Q_OBJECT

public: // 関数

	explicit CTab_MainWnd(QWidget * parent = nullptr);

	virtual void AddNewTab(QWidget * page, BOOL bChangeFocus = TRUE);
	virtual void CloseTab();
	virtual void ShowEdit();
	virtual BOOL Create(CMainWnd * mainWnd);
	void OnContextMenu(const QPoint & pos);

	int HitTest(const QPoint & pos) const;

private: // メンバ変数

	CMainWnd * m_rMainWnd;
	QAction * m_closeAct;
	QAction * m_renameAct;
	QAction * m_newTabAct;
	QAction * m_showTabAct;
	int m_nTab;
};
//----------------------------------------------------------------------------

#endif
