//----------------------------------------------------------------------------
// PanSlider_MainWnd.cpp : ボリューム表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PanSlider_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPanSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.panSlider);

	SetRangeMin(-100);
	SetRangeMax(100);
	SetLineSize(1);
	SetPageSize(5);
	SetThumbPos(0);

	connect(m_rMainWnd.panSlider, &QSlider::valueChanged,
					this, &CPanSlider_MainWnd::OnHScroll);

	return TRUE;
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::OnHScroll(int pos)
{
	LONG trackpos = GetThumbPos();
	m_rMainWnd.SetPan((int)trackpos);
	m_rMainWnd.GetPanLabel().SetPan(trackpos);
}
//----------------------------------------------------------------------------
