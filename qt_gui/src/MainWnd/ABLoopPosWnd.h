//----------------------------------------------------------------------------
// ABLoopPosWnd.h : ABループ位置設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef ABLoopPosWndH
#define ABLoopPosWndH

#include "../Common/Define.h"
#include <QDialog>
#include "ui_ABLoopPosWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// ABループ位置設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CABLoopPosWnd : public QDialog, public Ui::ABLoopPosWnd
{
	Q_OBJECT

public: // 関数

	CABLoopPosWnd(CMainWnd & mainWnd, BOOL bLoopA);

	virtual void SetPos();

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	BOOL m_bLoopA; // ABループ(A)かどうか（FALSEの場合、B）
};
//----------------------------------------------------------------------------

#endif
