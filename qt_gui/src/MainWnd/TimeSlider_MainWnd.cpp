//----------------------------------------------------------------------------
// TimeSlider_MainWnd.cpp : 再生時間設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include "TimeSlider_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTimeSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.timeSlider);

	SetLineSize(1);
	SetPageSize(1);

	// シグナルQSlider::valueChanedでは、CMainWnd::SetTimeがSetThumbPosを実行し
	// 正しく動作しない
	connect(m_rMainWnd.timeSlider, &QSlider::sliderMoved,
					this, &CTimeSlider_MainWnd::OnHScroll);
	connect(m_rMainWnd.timeSlider, &CSliderCtrlCore::OnLButtonDown,
					this, &CTimeSlider_MainWnd::OnLButtonDown);

	return TRUE;
}
//----------------------------------------------------------------------------
// スライダをバイト単位で設定
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::SetTime(QWORD bytes, QWORD totalBytes)
{
	SetRangeMin(0);
	SetRangeMax((LONG)(totalBytes / 100000));
	SetThumbPos((LONG)(bytes / 100000));
	SetPageSize((LONG)m_rMainWnd.GetSound().ChannelGetFreq() * 4 / 100000);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnHScroll(int pos)
{
	QWORD trackpos = (QWORD)pos;
	m_rMainWnd.SetTime(trackpos * 100000);
}
//----------------------------------------------------------------------------
// クリックされた
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnLButtonDown(int x, int y)
{
	// 選択範囲の位置を得る
	QRect rc = m_rMainWnd.timeSlider->frameGeometry();
	QRect rc2 = m_rMainWnd.timeSlider->childrenRect();

	double dPos = x;
//	dPos -= rc.x();
	dPos /= rc.width();
	QWORD qwRangeMax = GetRangeMax();
	QWORD qwPos = (QWORD)(dPos * qwRangeMax);
	if(qwPos < 0)
		qwPos = 0;
	else if(qwPos > qwRangeMax - m_rMainWnd.GetSound().ChannelGetFreq()
			/ 100000)
		qwPos = (QWORD)(qwRangeMax - m_rMainWnd.GetSound().ChannelGetFreq()
				/ 100000);

	m_rMainWnd.SetTime(qwPos * 100000);
}
//----------------------------------------------------------------------------
