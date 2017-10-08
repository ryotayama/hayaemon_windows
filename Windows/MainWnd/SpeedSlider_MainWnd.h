//----------------------------------------------------------------------------
// SpeedSlider_MainWnd.h : 再生速度設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef SpeedSlider_MainWndH
#define SpeedSlider_MainWndH

class CApp;
class CMainWnd;
#include "../Common/SliderCtrl.h"
#include "RMenu_SpeedCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 再生速度設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CSpeedSlider_MainWnd : public CSliderCtrl
{
public: // 関数

	CSpeedSlider_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  dwThumbClickTime(0), m_nDecimalDigit(1) { }
	virtual ~CSpeedSlider_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetLimit(double dMinSpeed, double dMaxSpeed);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnRButtonUp(int x, int y, UINT keyFlags);
	virtual BOOL OnMouseWheel(UINT nFlags, int zDelta, POINTS pt);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	DWORD dwThumbClickTime;
	int m_nDecimalDigit; // 小数点桁数
	CRMenu_SpeedCtrl m_rClickMenu; // 右クリックメニュー

public: // メンバ変数の取得・設定

	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif