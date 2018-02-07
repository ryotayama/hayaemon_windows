//----------------------------------------------------------------------------
// TimerPlayWnd_MainWnd.h : タイマー再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef TimerPlayWnd_MainWndH
#define TimerPlayWnd_MainWndH

#include <QDialog>
#include "ui_TimerPlayWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// タイマー再生用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CTimerPlayWnd_MainWnd : public QDialog, Ui::TimerPlayWnd
{
public: // 関数

	explicit CTimerPlayWnd_MainWnd(CMainWnd & mainWnd);

	virtual void EnableControl(bool bPlayEnable, bool bStopEnable);
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
