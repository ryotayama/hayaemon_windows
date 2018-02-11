//----------------------------------------------------------------------------
// OpenURLWnd.h : 「URLを開く」用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef OpenURLWndH
#define OpenURLWndH

#include <QDialog>
#include "ui_OpenURLWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 「URLを開く」用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class COpenURLWnd : public QDialog, public Ui::OpenURLWnd
{
	Q_OBJECT

public: // 関数

	explicit COpenURLWnd(CMainWnd & mainWnd, bool bAdd = false);

	virtual void OpenURL();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	bool m_bAdd;
};
//----------------------------------------------------------------------------

#endif
