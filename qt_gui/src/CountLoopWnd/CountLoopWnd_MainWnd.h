//----------------------------------------------------------------------------
// CountLoopWnd_MainWnd.h : 回数ループウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef CountLoopWnd_MainWndH
#define CountLoopWnd_MainWndH

#include <QDialog>
#include "ui_CountLoopWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 回数ループウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CCountLoopWnd_MainWnd : public QDialog, public Ui::CountLoopWnd
{
	Q_OBJECT

public: // 関数

	explicit CCountLoopWnd_MainWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
