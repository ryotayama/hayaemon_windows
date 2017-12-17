//----------------------------------------------------------------------------
// FreqLabel_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "FreqLabel_MainWnd.h"
#include <cmath>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CFreqLabel_MainWnd::Create()
{
	auto spinbox = m_rMainWnd.freqSpinBox;
	spinbox->setDecimals(1);
	spinbox->setSingleStep(0.1);

	spinbox->setRange(10.0, 1200.0);
	SetFreq(100.0);

	connect(spinbox, static_cast<void (QDoubleSpinBox::*)(double)>(
						&QDoubleSpinBox::valueChanged),
					[&] (double d) {
						int digit = m_rMainWnd.GetFreqSlider().GetDecimalDigit();
						int n = (int)(d * pow(10.0, digit) + 0.9 / pow(10.0, digit));
						m_rMainWnd.GetFreqSlider().SetThumbPos(n);
					});

	return TRUE;
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	m_nDecimalDigit = nDecimalDigit;
	auto spinbox = m_rMainWnd.freqSpinBox;
	spinbox->setDecimals(nDecimalDigit);
	spinbox->setSingleStep(1.0 / pow(10, nDecimalDigit));
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(nDecimalDigit);
}
//----------------------------------------------------------------------------
// 表示する周波数を表示
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::SetFreq(double dFreq)
{
	m_rMainWnd.freqSpinBox->setValue(dFreq);
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::SetLimit(double dMinFreq,
									   double dMaxFreq)
{
	m_rMainWnd.freqSpinBox->setRange(dMinFreq, dMaxFreq);
}
//----------------------------------------------------------------------------
// コントロールの表示状態を設定
//----------------------------------------------------------------------------
void CFreqLabel_MainWnd::Show(int nCmdShow)
{
	bool visible = nCmdShow != SW_HIDE;
	m_rMainWnd.freqLabel->setVisible(visible);
	m_rMainWnd.freqLabel2->setVisible(visible);
	m_rMainWnd.freqSpinBox->setVisible(visible);
}
//----------------------------------------------------------------------------
