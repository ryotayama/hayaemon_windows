//----------------------------------------------------------------------------
// TimeSlider_MainWnd.cpp : 再生時間設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include "TimeSlider_MainWnd.h"
#include <stdint.h>
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
	connect(m_rMainWnd.timeSlider, &CSliderCtrlCore::OnLButtonUp,
					this, &CTimeSlider_MainWnd::OnLButtonUp);
	connect(m_rMainWnd.timeSlider, &CSliderCtrlCore::OnMouseMove,
					this, &CTimeSlider_MainWnd::OnMouseMove);

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
	if(m_rMainWnd.GetSound().IsABLoopA()) {
		// 選択範囲の位置を得る
		QRect rc;
		GetSelRect(&rc);

		LONG nSelStartLeft = GetSelStartLeft();

		// ドラッグの開始
		if(rc.top() <= y && y <= rc.bottom()) {
			QRect rcThumb;
			m_slider->GetThumbRect(&rcThumb);
			int nDrag = rcThumb.width() / 2;
			if(nSelStartLeft - nDrag < x
			   && x < nSelStartLeft + nDrag) {
				bABLoopADrag = TRUE;
				return;
			}
		}
	}

	if(m_rMainWnd.GetSound().IsABLoopB()) {
		// 選択範囲の位置を得る
		QRect rc;
		GetSelRect(&rc);

		LONG nSelEndLeft = GetSelEndLeft();

		// ドラッグの開始
		if(rc.top() <= y && y <= rc.bottom()) {
			QRect rcThumb;
			m_slider->GetThumbRect(&rcThumb);
			int nDrag = rcThumb.width() / 2;
			if(nSelEndLeft - nDrag < x
			   && x < nSelEndLeft + nDrag) {
				bABLoopBDrag = TRUE;
				return;
			}
		}
	}

	// 選択範囲の位置を得る
	QRect rc;
	GetSelRect(&rc);

	double dPos = x;
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
// クリックが離された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnLButtonUp(int x, int y)
{
	bABLoopADrag = bABLoopBDrag = FALSE;
}
//----------------------------------------------------------------------------
// マウスが移動された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnMouseMove(int x, int y)
{
	if(m_rMainWnd.GetSound().IsABLoopA() && bABLoopADrag) {
		// 選択範囲の位置を得る
		QRect rc;
		GetSelRect(&rc);

		// AB ループの A にあたる位置を設定
		double dSelStartLeft = x;
		dSelStartLeft -= rc.left();
		dSelStartLeft /= rc.width();
		int64_t qwRangeMax = GetRangeMax();
		int64_t qwSelStart = (int64_t)(dSelStartLeft * qwRangeMax);
		int64_t qwSelEnd = (int64_t)m_slider->GetSelEnd();
		if(qwSelStart < 0)
			qwSelStart = 0;
		else if(qwSelStart >=
				qwSelEnd - m_rMainWnd.GetSound().ChannelGetFreq()
				/ 100000)
			qwSelStart = qwSelEnd
						- (int64_t)m_rMainWnd.GetSound().ChannelGetFreq()
						/ 100000;

		m_rMainWnd.GetSound().SetLoopPosA(qwSelStart * 100000);

		// 現在の再生位置がループの範囲外にある場合は、修正
		int64_t trackpos = GetThumbPos();
		if(trackpos < qwSelStart)
			m_rMainWnd.SetTime(qwSelStart * 100000);
		else if(trackpos > qwSelEnd)
			m_rMainWnd.SetTime((QWORD)(qwSelEnd * 100000
								 - m_rMainWnd.GetSound().ChannelGetFreq()
								 / 2));

		m_slider->SetSelStart((LPARAM)qwSelStart);
		m_slider->update();
	}

	if(m_rMainWnd.GetSound().IsABLoopB() && bABLoopBDrag) {
		// 選択範囲の位置を得る
		QRect rc;
		GetSelRect(&rc);

		// AB ループの B にあたる位置を設定
		double dSelEndLeft = x;
		dSelEndLeft -= rc.left();
		dSelEndLeft /= rc.width();
		int64_t qwRangeMax = (int64_t)GetRangeMax();
		int64_t qwSelStart = (int64_t)m_slider->GetSelStart();
		int64_t qwSelEnd = (int64_t)(dSelEndLeft * qwRangeMax);
		if(qwSelEnd <= qwSelStart + m_rMainWnd.GetSound().ChannelGetFreq()
						/ 100000)
			qwSelEnd = qwSelStart
						 + (int64_t)m_rMainWnd.GetSound().ChannelGetFreq()
						 / 100000;
		else if(qwSelEnd > qwRangeMax) qwSelEnd = qwRangeMax;

		m_rMainWnd.GetSound().SetLoopPosB(qwSelEnd * 100000);

		// 現在の再生位置がループの範囲外にある場合は、修正
		int64_t trackpos = GetThumbPos();
		if(trackpos < qwSelStart)
			m_rMainWnd.SetTime(qwSelStart * 100000);
		else if(trackpos > qwSelEnd)
			m_rMainWnd.SetTime((QWORD)(qwSelEnd * 100000
								 - m_rMainWnd.GetSound().ChannelGetFreq()));

		m_slider->SetSelEnd((LONG)qwSelEnd);
		m_slider->update();
	}
}
//----------------------------------------------------------------------------
// トラックバーを有効化
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::SetSelRangeEnabled(bool enabled)
{
	m_slider->SetSelRangeEnabled(enabled);
}
//----------------------------------------------------------------------------
// トラックバーの開始位置を設定
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::SetSelStart(LONG pos)
{
	m_slider->SetSelStart(pos);
}
//----------------------------------------------------------------------------
// トラックバーの終了位置を設定
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::SetSelEnd(LONG pos)
{
	m_slider->SetSelEnd(pos);
}
//----------------------------------------------------------------------------
// 再描画
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::Update()
{
	m_slider->update();
}
//----------------------------------------------------------------------------
