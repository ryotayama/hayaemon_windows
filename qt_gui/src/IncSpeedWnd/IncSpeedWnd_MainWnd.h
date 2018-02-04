//----------------------------------------------------------------------------
// IncSpeedWnd_MainWnd.h : だんだん速くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef IncSpeedWnd_MainWndH
#define IncSpeedWnd_MainWndH

#include <QDialog>
#include "ui_IncSpeedWnd.h"
class CMainWnd;
class QDoubleSpinBox;
//----------------------------------------------------------------------------
// だんだん速くするウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CIncSpeedWnd_MainWnd : public QDialog, public Ui::IncSpeedWnd
{
public: // 関数

	explicit CIncSpeedWnd_MainWnd(CMainWnd & mainWnd);

	virtual void EnableControl(bool bSecondEnable, bool bLoopEnable);
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();

protected: // メンバ変数

	CMainWnd & m_rMainWnd;
	QDoubleSpinBox * m_edit;
	QDoubleSpinBox * m_edit2;
};
//----------------------------------------------------------------------------

#endif
