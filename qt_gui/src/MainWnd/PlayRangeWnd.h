//----------------------------------------------------------------------------
// PlayRangeWnd.h : 再生範囲設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef PlayRangeWndH
#define PlayRangeWndH

#include <QDialog>
#include "ui_PlayRangeWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生範囲設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CPlayRangeWnd : public QDialog, public Ui::PlayRangeWnd
{
public: // 関数

	explicit CPlayRangeWnd(CMainWnd & mainWnd);

	virtual void SetRange();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
