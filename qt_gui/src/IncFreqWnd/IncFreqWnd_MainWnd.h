//----------------------------------------------------------------------------
// IncFreqWnd_MainWnd.h : だんだん速くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef IncFreqWnd_MainWndH
#define IncFreqWnd_MainWndH

#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// だんだん速くするウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CIncFreqWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // 関数

	explicit CIncFreqWnd_MainWnd(CMainWnd & mainWnd);

	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
};
//----------------------------------------------------------------------------

#endif
