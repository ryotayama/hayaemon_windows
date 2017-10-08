//----------------------------------------------------------------------------
// IncFreqWnd_MainWnd.h : だんだん速くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef IncFreqWnd_MainWndH
#define IncFreqWnd_MainWndH

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
// だんだん速くするウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CIncFreqWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // 関数

	CIncFreqWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CIncFreqWnd_MainWnd();

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnEscKeyPressed();
};
//----------------------------------------------------------------------------

#endif