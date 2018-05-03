//----------------------------------------------------------------------------
// SpeedSlider_MainWnd.cpp : 再生速度設定用スライダの管理を行う
//----------------------------------------------------------------------------
#include "SpeedSlider_MainWnd.h"
#include <cmath>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CSpeedSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.speedSlider);

	SetRangeMin(100);
	SetRangeMax(12000);
	SetLineSize(10);
	SetPageSize(50);
	SetThumbPos(1000);

	connect(m_rMainWnd.speedSlider, &QSlider::valueChanged,
					this, &CSpeedSlider_MainWnd::OnHScroll);

	return TRUE;
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	auto pos = GetThumbPos();
	SetRangeMax((LONG)((GetRangeMax() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetRangeMin((LONG)((GetRangeMin() / pow(10.0, m_nDecimalDigit))
		* pow(10.0, nDecimalDigit)));
	SetLineSize((LONG)(1 * pow(10.0, nDecimalDigit)));
	SetPageSize((LONG)(5 * pow(10.0, nDecimalDigit)));
	int old = m_nDecimalDigit;
	m_nDecimalDigit = nDecimalDigit;
	SetThumbPos((LONG)((pos / pow(10.0, old)) * pow(10.0, nDecimalDigit)));
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::SetLimit(double dMinSpeed, double dMaxSpeed)
{
	int nMinSpeed = (int)(dMinSpeed * pow(10.0, m_nDecimalDigit));
	int nMaxSpeed = (int)(dMaxSpeed * pow(10.0, m_nDecimalDigit));
	int nCurrentSpeed = (int)GetThumbPos();
	SetRangeMin(nMinSpeed);
	SetRangeMax(nMaxSpeed, TRUE);
	if(nCurrentSpeed < nMinSpeed) nCurrentSpeed = nMinSpeed;
	else if(nMaxSpeed < nCurrentSpeed) nCurrentSpeed = nMaxSpeed;
	SetThumbPos(nCurrentSpeed);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CSpeedSlider_MainWnd::OnHScroll(int pos)
{
	double n = (double)(GetThumbPos() / pow(10.0, m_nDecimalDigit));
	m_rMainWnd.SetSpeed(n);
	m_rMainWnd.GetSpeedLabel().SetSpeed(n);
}
//----------------------------------------------------------------------------
