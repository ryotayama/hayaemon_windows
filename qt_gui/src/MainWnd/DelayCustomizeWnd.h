//----------------------------------------------------------------------------
// DelayCustomizeWnd.h : ディレイのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef DelayCustomizeWndH
#define DelayCustomizeWndH

#include <QDialog>
#include "ui_DelayCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// ディレイのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CDelayCustomizeWnd : public QDialog, public Ui::DelayCustomizeWnd
{
public: // 関数

	explicit CDelayCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // DelayCustomizeWndH
