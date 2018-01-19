//----------------------------------------------------------------------------
// 3DReverbCustomizeWnd.h : ３Ｄリバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef Reverb3DCustomizeWndH
#define Reverb3DCustomizeWndH

#include <QDialog>
#include "ui_Reverb3DCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// ３Ｄリバーブのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class C3DReverbCustomizeWnd : public QDialog, public Ui::Reverb3DCustomizeWnd
{
public: // 関数

	explicit C3DReverbCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};

//----------------------------------------------------------------------------

#endif // Reverb3DCustomizeWndH
