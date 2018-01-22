//----------------------------------------------------------------------------
// DistortionCustomizeWnd.h : ディストーションのカスタマイズ用ウィンドウの管理
//----------------------------------------------------------------------------
#ifndef DistortionCustomizeWndH
#define DistortionCustomizeWndH

#include <QDialog>
#include "ui_DistortionCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// ディストーションーのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CDistortionCustomizeWnd : public QDialog,
																public Ui::DistortionCustomizeWnd
{
public: // 関数

	explicit CDistortionCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // DistortionCustomizeWndH
