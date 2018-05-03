//----------------------------------------------------------------------------
// PlayPositionWnd.h : 再生位置設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef PlayPositionWndH
#define PlayPositionWndH

#include <QDialog>
#include "ui_PlayPositionWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生位置設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CPlayPositionWnd : public QDialog, public Ui::PlayPositionWnd
{
public: // 関数

	explicit CPlayPositionWnd(CMainWnd & mainWnd);

	virtual void SetSeconds();

private: // メンバ変数

	CMainWnd & m_rMainWnd;

};
//----------------------------------------------------------------------------

#endif
