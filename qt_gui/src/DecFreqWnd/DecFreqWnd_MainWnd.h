//----------------------------------------------------------------------------
// DecFreqWnd_MainWnd.h : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef DecFreqWnd_MainWndH
#define DecFreqWnd_MainWndH

#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// だんだん遅くするウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CDecFreqWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // 関数

	explicit CDecFreqWnd_MainWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
};
//----------------------------------------------------------------------------

#endif
