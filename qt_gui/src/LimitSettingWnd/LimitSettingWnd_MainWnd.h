//----------------------------------------------------------------------------
// LimitSettingWnd_MainWnd.h : 最大値／最小値の設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef LimitSettingWnd_MainWndH
#define LimitSettingWnd_MainWndH

#include <QDialog>
#include "ui_LimitSettingWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 最大値／最小値の設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CLimitSettingWnd_MainWnd : public QDialog, public Ui::LimitSettingWnd
{
public: // 関数

	explicit CLimitSettingWnd_MainWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // LimitSettingWnd_MainWndH
