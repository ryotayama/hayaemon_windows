//----------------------------------------------------------------------------
// DecFreqWnd_MainWnd.h : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef DecFreqWnd_MainWndH
#define DecFreqWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// だんだん遅くするウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CDecFreqWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // 関数

	CDecFreqWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CDecFreqWnd_MainWnd();

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnEscKeyPressed();
};
//----------------------------------------------------------------------------

#endif