//----------------------------------------------------------------------------
// VolumeSlider_MainWnd.cpp : 音量設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include "VolumeSlider_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CVolumeSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.volumeSlider);

	SetRangeMin(0);
	SetRangeMax(1000);
	SetLineSize(10);
	SetPageSize(50);
	SetThumbPos(1000);

	connect(m_rMainWnd.volumeSlider, &QSlider::valueChanged,
					this, &CVolumeSlider_MainWnd::OnHScroll);

	return TRUE;
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CVolumeSlider_MainWnd::OnHScroll(int pos)
{
	double n = (double)(GetThumbPos() / 10.0);
	LONG trackpos = GetThumbPos();
	m_rMainWnd.SetVolume(n);
	m_rMainWnd.GetVolumeLabel().SetVolume(n);
}
//----------------------------------------------------------------------------
