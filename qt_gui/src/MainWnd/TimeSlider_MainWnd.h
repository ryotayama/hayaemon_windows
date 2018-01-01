//----------------------------------------------------------------------------
// TimeSlider_MainWnd.h : 再生時間設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef TimeSlider_MainWndH
#define TimeSlider_MainWndH

#include <QObject>
#include "../Common/Define.h"
#include "../Common/SliderCtrl.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生時間設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CTimeSlider_MainWnd : public CSliderCtrl, public QObject
{
public: // 関数

	explicit CTimeSlider_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), bABLoopADrag(FALSE), bABLoopBDrag(FALSE)
	{ }

	virtual BOOL Create();
	virtual void SetTime(QWORD time, QWORD totalTime);

	virtual void OnHScroll(int pos);
	virtual void OnLButtonDown(int x, int y);
	virtual void OnLButtonUp(int x, int y);
	virtual void OnMouseMove(int x, int y);

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	BOOL bABLoopADrag;
	BOOL bABLoopBDrag;

public:

	// Qtのラッパー
	void SetSelRangeEnabled(bool enabled);
	void SetSelStart(LONG pos);
	void SetSelEnd(LONG pos);
	void Update();
};
//----------------------------------------------------------------------------

#endif
