//----------------------------------------------------------------------------
// Tab.h : タブコントロールの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef TabH
#define TabH

#include <QTabWidget>
#include "Define.h"
//----------------------------------------------------------------------------
// タブコントロールの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CTab : public QTabWidget
{
public: // 関数

	explicit CTab(QWidget * parent = nullptr) : QTabWidget(parent) { }
	virtual ~CTab() { }

	virtual BOOL DeleteItem(int iItem) {
		removeTab(iItem);
		return TRUE;
	}
	virtual int GetCurrentFocus() {
		return currentIndex();
	}
	virtual int GetItemCount() {
		return count();
	}
	virtual void SetCurrentFocus(int iItem) {
		setCurrentIndex(iItem);
	}
	virtual void Show(int nCmdShow) {
		setVisible(nCmdShow != SW_HIDE);
	}
	virtual void SetItem(LPTSTR lpText, int iItem) {
#ifdef UNICODE
		setTabText(iItem, QString::fromStdWString(lpText));
#else
		setTabText(iItem, QString::fromStdString(lpText));
#endif
	}
	virtual QString GetItemText(int iItem) {
		return tabText(iItem);
	}
};
//----------------------------------------------------------------------------

#endif
