//----------------------------------------------------------------------------
// MetronomeWnd_MainWnd.h : メトロノーム用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef MetronomeWnd_MainWndH
#define MetronomeWnd_MainWndH

#include <QDialog>
#include "ui_MetronomeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// メトロノーム用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CMetronomeWnd_MainWnd : public QDialog, public Ui::MetronomeWnd
{
public: // 関数

	explicit CMetronomeWnd_MainWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
