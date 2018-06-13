//----------------------------------------------------------------------------
// Divider_MainWnd.h : 区切り線その１の管理を行う
//----------------------------------------------------------------------------
#ifndef Divider_MainWndH
#define Divider_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 区切り線その１の管理を行うクラス
//----------------------------------------------------------------------------
class CDivider_MainWnd : public CStatic
{
public: // 関数

	CDivider_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CDivider_MainWnd() { }

	virtual BOOL Create();
	virtual void ResetSize();

protected: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

};
//----------------------------------------------------------------------------

#endif