//----------------------------------------------------------------------------
// ReverbCustomizeWnd.h : リバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef ReverbCustomizeWndH
#define ReverbCustomizeWndH

#include <QDialog>
#include "ui_ReverbCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// リバーブのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CReverbCustomizeWnd : public QDialog, public Ui::ReverbCustomizeWnd
{
public: // 関数

	explicit CReverbCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // ReverbCustomizeWndH
