//----------------------------------------------------------------------------
// CompressorCustomizeWnd.h : コンプレッサのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef CompressorCustomizeWndH
#define CompressorCustomizeWndH

#include <QDialog>
#include "ui_CompressorCustomizeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// コンプレッサーのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CCompressorCustomizeWnd : public QDialog,
                                public Ui::CompressorCustomizeWnd
{
public: // 関数

	explicit CCompressorCustomizeWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif // CompressorCustomizeWndH
