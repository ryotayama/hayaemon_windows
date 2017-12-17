//----------------------------------------------------------------------------
// PitchSlider_MainWnd.cpp : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PitchSlider_MainWnd.h"
#include <cmath>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPitchSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.pitchSlider);

	SetRangeMin(-240);
	SetRangeMax(240);
	SetLineSize(10);
	SetPageSize(10);
	SetThumbPos(0);

	connect(m_rMainWnd.pitchSlider, &QSlider::valueChanged,
					this, &CPitchSlider_MainWnd::OnHScroll);

	return TRUE;
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	auto pos = GetThumbPos();
	SetRangeMax((LONG)((GetRangeMax() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetRangeMin((LONG)((GetRangeMin() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetLineSize((LONG)(1 * pow(10.0, nDecimalDigit)));
	SetPageSize((LONG)(1 * pow(10.0, nDecimalDigit)));
	int old = m_nDecimalDigit;
	m_nDecimalDigit = nDecimalDigit;
	SetThumbPos((LONG)((pos / pow(10.0, old)) * pow(10.0, nDecimalDigit)));
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::SetLimit(double dMinPitch, double dMaxPitch)
{
	int nMinPitch = (int)(dMinPitch * pow(10.0, m_nDecimalDigit));
	int nMaxPitch = (int)(dMaxPitch * pow(10.0, m_nDecimalDigit));
	int nCurrentPitch = (int)GetThumbPos();
	SetRangeMin(nMinPitch);
	SetRangeMax(nMaxPitch, TRUE);
	if(nCurrentPitch < nMinPitch) nCurrentPitch = nMinPitch;
	else if(nMaxPitch < nCurrentPitch) nCurrentPitch = nMaxPitch;
	SetThumbPos(nCurrentPitch);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CPitchSlider_MainWnd::OnHScroll(int pos)
{
	double n = (double)(GetThumbPos() / pow(10.0, m_nDecimalDigit));
	m_rMainWnd.SetPitch(n);
	m_rMainWnd.GetPitchLabel().SetPitch(n);
}
//----------------------------------------------------------------------------
