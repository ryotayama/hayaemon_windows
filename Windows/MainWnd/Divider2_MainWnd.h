//----------------------------------------------------------------------------
// Divider2_MainWnd.h : 区切り線その２の管理を行う
//----------------------------------------------------------------------------
#ifndef Divider2_MainWndH
#define Divider2_MainWndH

class CApp;
class CMainWnd;
#include "Divider_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 区切り線その２の管理を行うクラス
//----------------------------------------------------------------------------
class CDivider2_MainWnd : public CDivider_MainWnd
{
public: // 関数

	CDivider2_MainWnd(CApp & app, CMainWnd & mainWnd)
		: CDivider_MainWnd(app, mainWnd) { }
	virtual ~CDivider2_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
};
//----------------------------------------------------------------------------

#endif