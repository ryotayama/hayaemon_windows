//----------------------------------------------------------------------------
// TimeSlider_MainWnd.cpp : 再生時間設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include "TimeSlider_MainWnd.h"
#include <stdint.h>
#include <QPainter>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTimeSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.timeSlider);

	SetLineSize(1);
	SetPageSize(1);

	m_slider->SetRenderTrackBarBackground(
			[this] (QPaintEvent * e) { this->RenderTrackBarBackground(e); });
	// シグナルQSlider::valueChanedでは、CMainWnd::SetTimeがSetThumbPosを実行し
	// 正しく動作しない
	connect(m_rMainWnd.timeSlider, &QSlider::sliderMoved,
					this, &CTimeSlider_MainWnd::OnHScroll);
	connect(m_rMainWnd.timeSlider, &CSliderCtrlCore::OnKeyDown,
					this, &CTimeSlider_MainWnd::OnKeyDown);
	connect(m_rMainWnd.timeSlider, &CSliderCtrlCore::OnKeyUp,
					this, &CTimeSlider_MainWnd::OnKeyUp);
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
// キーボードが押された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnKeyDown(int vk)
{
	switch(vk)
	{
	case Qt::Key_Control:
		bControl = TRUE;
		break;
	}
}
//----------------------------------------------------------------------------
// キーボードが離された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnKeyUp(int vk)
{
	switch(vk)
	{
	case Qt::Key_Control:
		bControl = FALSE;
		break;
	}
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

	if(m_rMainWnd.IsMarkerPlay()) {
		// 選択範囲の位置を得る
		QRect rc;
		GetSelRect(&rc);
		int width = rc.width();
		int height = rc.height();

		QWORD length = m_rMainWnd.GetSound().ChannelGetLength();
		std::vector<QWORD> arrayMarker
			= m_rMainWnd.GetSound().GetArrayMarker();
		for(int i = 0; i < (int)arrayMarker.size(); i++) {
			double rate = (double)(int)(arrayMarker[i] / 100000)
							/ (double)(int)(length / 100000);
			int nLeft = LONG(rc.left() + width * rate + 0.5);
			int nTop = rc.top() + 3;
			int nRight = nLeft + 1;
			int nBottom = rc.bottom() - 3;
			QRect rcThumb;
			m_slider->GetThumbRect(&rcThumb);
			int nDrag = rcThumb.width() / 2;
			if(nTop <= y && y <= nBottom
				 && nLeft - nDrag < x && x < nRight + nDrag) {
				bDrag = TRUE;
				nDraggingMarker = i;
				qwFirstPos = arrayMarker[nDraggingMarker];
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
	bABLoopADrag = bABLoopBDrag = bDrag = FALSE;
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

		m_slider->SetSelStart(qwSelStart);
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

	if(m_rMainWnd.IsMarkerPlay() && bDrag) {
		// 変更後の位置を算出

		// スライダの可動領域の位置を得る
		QRect rc;
		GetSelRect(&rc);
		int width = rc.width(); // 可動領域の幅
		int height = rc.height(); // 可動領域の高さ

		QWORD length = m_rMainWnd.GetSound().ChannelGetLength();
		int csrLeft = x - rc.left();
		if(!bControl && csrLeft < 0) csrLeft = 0;
		else if(!bControl && csrLeft > width) csrLeft = width;
		double rate = (double)csrLeft / (double)width;
		QWORD qwDstPos = (QWORD)(length * rate);

		// 変更前の値を保存しておく
		std::vector<QWORD> arrayMarker
			= m_rMainWnd.GetSound().GetArrayMarker();
		QWORD qwSrcPos = arrayMarker[nDraggingMarker];

		if(bControl) {
			QWORD difference = qwDstPos > qwFirstPos ?
								 qwDstPos - qwFirstPos
								 : qwFirstPos - qwDstPos;
			difference /= 10;
			qwDstPos = qwDstPos > qwFirstPos ?
						 qwFirstPos + difference
						 : qwFirstPos - difference;
			if(qwDstPos < 0) qwDstPos = 0;
			else if(qwDstPos > length) qwDstPos = length;
		}

		// 変更
		nDraggingMarker
			= m_rMainWnd.GetSound().ChangeMarkerPos(nDraggingMarker,
													 qwDstPos);

		// 変更後の位置に現在の再生位置を設定
		if(m_rMainWnd.IsSetPositionAuto()) m_rMainWnd.SetTime(qwDstPos);
		else m_rMainWnd.SetTime(m_rMainWnd.GetSound().ChannelGetPosition(),
								FALSE);
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
// 背景を描画
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::RenderTrackBarBackground(QPaintEvent * e)
{
	m_slider->RenderTrackBarBackground(e);

	int min = m_slider->minimum();
	int max = m_slider->maximum();
	if (min >= max) {
		return;
	}

	auto rc = m_slider->GetSpaceAvailabel();
	QPainter p(m_slider);
	QPen pen(QColor(51, 153, 255), 1, Qt::SolidLine);
	p.setPen(pen);
	for (auto marker : m_rMainWnd.GetSound().GetArrayMarker()) {
		double t = (marker / 100000 - min) / static_cast<double>(max - min);
		int pos = rc.width() * t + rc.left();
		p.drawLine(pos, rc.top(), pos, rc.bottom());
	}
}
//----------------------------------------------------------------------------
