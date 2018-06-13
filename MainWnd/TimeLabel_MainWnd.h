//----------------------------------------------------------------------------
// TimeLabel_MainWnd.h : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef TimeLabel_MainWndH
#define TimeLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 再生時間表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CTimeLabel_MainWnd : public CStatic
{
public: // 関数

	CTimeLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), bRemainMode(FALSE) { }
	virtual ~CTimeLabel_MainWnd() { }

	virtual BOOL Create();
	virtual void ResetPos();
	virtual void SetTime(double time, double totalTime, BOOL bResetPos = TRUE);

	virtual BOOL OnEraseBkgnd(HDC hDc) {
		return TRUE;
	}
	virtual void OnLButtonDown(int x, int y, UINT keyFlags) {
		bRemainMode = !bRemainMode;
		CStatic::OnLButtonDown(x, y, keyFlags);
	}
	virtual void OnPaint();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;
	BOOL bRemainMode;
	HDC hMemDc;
	HBITMAP hMemBmp;
	tstring strLast; // 前回描画した文字列
};
//----------------------------------------------------------------------------

#endif