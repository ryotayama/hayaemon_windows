//----------------------------------------------------------------------------
// MainWnd.h : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH

class CApp;
#include <QMainWindow>
#include "../Common/Define.h"
#include "ui_MainWnd.h"
//----------------------------------------------------------------------------
// メインウィンドウの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMainWnd : public QMainWindow, protected Ui::MainWnd
{
public: // 関数

	CMainWnd(CApp & app): m_rApp(app) { }

	virtual BOOL Create() { return OnCreate(); }

	virtual LRESULT OnCreate();

protected: // メンバ変数

	CApp & m_rApp;
};
//----------------------------------------------------------------------------

#endif
