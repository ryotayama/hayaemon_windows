//----------------------------------------------------------------------------
// TimeSlider_MainWnd.h : 再生時間設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef TimeSlider_MainWndH
#define TimeSlider_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
class CApp;
class CMainWnd;
#include "../Common/bassinc.h"
#include "../Common/SliderCtrl.h"
#include "RMenu_TimeSlider.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 再生時間設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CTimeSlider_MainWnd : public CSliderCtrl
{
public: // 関数

	CTimeSlider_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), bABLoopADrag(FALSE),
		  bABLoopBDrag(FALSE), m_rClickMenu(*this), bDrag(FALSE),
		  nDraggingMarker(0), bControl(FALSE), qwFirstPos(0), nDeleteMarker(0) 
	{ }
	virtual ~CTimeSlider_MainWnd() { }

	virtual BOOL Create();
	virtual void DeleteMarker();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void SetTime(QWORD time, QWORD totalTime);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnKeyUp(UINT vk, UINT lKeyData);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual void OnRButtonUp(int x, int y, UINT keyFlags);
	virtual void OnMouseMove(int x, int y, UINT keyFlags);
	virtual BOOL OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRMenu_TimeSlider m_rClickMenu; // 右クリックメニュー

	BOOL bABLoopADrag;
	BOOL bABLoopBDrag;
	BOOL bDrag; // マーカー位置をドラッグ中かどうか
	int nDraggingMarker; // 何番目のマーカーをドラッグ中か
	BOOL bControl; // Ctrl キーによる微調整中かどうか
	QWORD qwFirstPos; // ドラッグ開始時のマーカー位置
	int nDeleteMarker; // 何番目のマーカーを削除予定か

public: // メンバ変数の取得・設定

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif