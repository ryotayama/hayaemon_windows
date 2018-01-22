//----------------------------------------------------------------------------
// GargleCustomizeWnd.h : ガーグルのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef GargleCustomizeWndH
#define GargleCustomizeWndH

#include <QDialog>
#include "ui_GargleCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// ガーグルのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CGargleCustomizeWnd : public QDialog, public Ui::GargleCustomizeWnd
{
public: // 関数

	explicit CGargleCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // GargleCustomizeWndH
