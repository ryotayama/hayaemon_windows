//----------------------------------------------------------------------------
// ChorusCustomizeWnd.h : コーラスのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef ChorusCustomizeWndH
#define ChorusCustomizeWndH

#include <QDialog>
#include "ui_ChorusCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// コーラスのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CChorusCustomizeWnd : public QDialog, public Ui::ChorusCustomizeWnd
{
public: // 関数

	explicit CChorusCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // ChorusCustomizeWndH
