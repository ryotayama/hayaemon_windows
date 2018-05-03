//----------------------------------------------------------------------------
// DecSpeedWnd_MainWnd.h : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef DecSpeedWnd_MainWndH
#define DecSpeedWnd_MainWndH

#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
//----------------------------------------------------------------------------
// だんだん遅くするウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CDecSpeedWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
	Q_OBJECT

public: // 関数

	explicit CDecSpeedWnd_MainWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
};
//----------------------------------------------------------------------------

#endif
