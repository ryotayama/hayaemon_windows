//----------------------------------------------------------------------------
// EQSlider_MainWnd.cpp : イコライザ設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include "EQSlider_MainWnd.h"
#include "EQLabel_MainWnd.h"
//----------------------------------------------------------------------------
// 参照の初期化
//----------------------------------------------------------------------------
void CEQSlider_MainWnd::Init(CSliderCtrlCore * slider,
														 CEQLabel_MainWnd * label,
														 std::function<void(LONG)> setEQ)
{
	CSliderCtrl::Init(slider);
	m_label = label;
	m_setEQ = setEQ;
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CEQSlider_MainWnd::Create()
{
	SetRangeMin(-30);
	SetRangeMax(30);
	SetLineSize(1);
	SetPageSize(1);
	SetThumbPos(0);

	connect(m_slider, &QSlider::valueChanged,
					this, &CEQSlider_MainWnd::OnHScroll);

	return TRUE;
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CEQSlider_MainWnd::OnHScroll(int pos)
{
	LONG trackpos = GetThumbPos();
	m_setEQ((int)trackpos);
	m_label->SetEQ(trackpos);
}
//----------------------------------------------------------------------------