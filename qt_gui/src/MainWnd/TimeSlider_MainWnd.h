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
		: m_rMainWnd(mainWnd), bABLoopADrag(FALSE), bABLoopBDrag(FALSE),
			bDrag(FALSE), nDraggingMarker(0), bControl(FALSE), qwFirstPos(0) { }

	virtual BOOL Create();
	virtual void SetTime(QWORD time, QWORD totalTime);

	virtual void OnHScroll(int pos);
	virtual void OnKeyDown(int vk);
	virtual void OnKeyUp(int vk);
	virtual void OnLButtonDown(int x, int y);
	virtual void OnLButtonUp(int x, int y);
	virtual void OnMouseMove(int x, int y);

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	BOOL bABLoopADrag;
	BOOL bABLoopBDrag;
	BOOL bDrag; // マーカー位置をドラッグ中かどうか
	int nDraggingMarker; // 何番目のマーカーをドラッグ中か
	BOOL bControl; // Ctrl キーによる微調整中かどうか
	QWORD qwFirstPos; // ドラッグ開始時のマーカー位置

public:

	// Qtのラッパー
	void SetSelRangeEnabled(bool enabled);
	void SetSelStart(LONG pos);
	void SetSelEnd(LONG pos);
	void RenderTrackBarBackground(QPaintEvent * e);
};
//----------------------------------------------------------------------------

#endif
