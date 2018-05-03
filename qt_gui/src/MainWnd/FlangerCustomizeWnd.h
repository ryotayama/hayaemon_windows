//----------------------------------------------------------------------------
// FlangerCustomizeWnd.h : フランジャーのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef FlangerCustomizeWndH
#define FlangerCustomizeWndH

#include <QDialog>
#include "ui_FlangerCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// フランジャーのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CFlangerCustomizeWnd : public QDialog, public Ui::FlangerCustomizeWnd
{
public: // 関数

	explicit CFlangerCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // FlangerCustomizeWndH
