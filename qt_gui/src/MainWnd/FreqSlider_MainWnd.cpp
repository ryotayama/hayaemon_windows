//----------------------------------------------------------------------------
// FreqSlider_MainWnd.cpp : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "FreqSlider_MainWnd.h"
#include <cmath>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CFreqSlider_MainWnd::Create()
{
	CSliderCtrl::Init(m_rMainWnd.freqSlider);

	SetRangeMin(100);
	SetRangeMax(12000);
	SetLineSize(10);
	SetPageSize(50);
	SetThumbPos(1000);

	connect(m_rMainWnd.freqSlider, &QSlider::valueChanged,
					this, &CFreqSlider_MainWnd::OnHScroll);

	return TRUE;
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CFreqSlider_MainWnd::SetDecimalDigit(int nDecimalDigit)
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
void CFreqSlider_MainWnd::SetLimit(double dMinFreq, double dMaxFreq)
{
	int nMinFreq = (int)(dMinFreq * pow(10.0, m_nDecimalDigit));
	int nMaxFreq = (int)(dMaxFreq * pow(10.0, m_nDecimalDigit));
	int nCurrentFreq = (int)GetThumbPos();
	SetRangeMin(nMinFreq);
	SetRangeMax(nMaxFreq, TRUE);
	if(nCurrentFreq < nMinFreq) nCurrentFreq = nMinFreq;
	else if(nMaxFreq < nCurrentFreq) nCurrentFreq = nMaxFreq;
	SetThumbPos(nCurrentFreq);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CFreqSlider_MainWnd::OnHScroll(int pos)
{
	double n = (double)(GetThumbPos() / pow(10.0, m_nDecimalDigit));
	m_rMainWnd.SetFreq(n);
	m_rMainWnd.GetFreqLabel().SetFreq(n);
}
//----------------------------------------------------------------------------
