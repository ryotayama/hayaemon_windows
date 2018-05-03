//----------------------------------------------------------------------------
// PitchLabel_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PitchLabel_MainWnd.h"
#include <cmath>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPitchLabel_MainWnd::Create()
{
	auto spinbox = m_rMainWnd.pitchSpinBox;
	spinbox->setDecimals(m_nDecimalDigit);
	spinbox->setSingleStep(0.1);

	spinbox->setRange(-24.0, 24.0);

	SetPitch(0.0);

	connect(spinbox, static_cast<void (QDoubleSpinBox::*)(double)>(
						&QDoubleSpinBox::valueChanged),
					[&] (double d) {
						int digit = m_rMainWnd.GetPitchSlider().GetDecimalDigit();
						int n;
						if(d >= 0.0)
							n = (int)(d * pow(10.0, digit) + 0.9 / pow(10.0, digit));
						else n = (int)(d * pow(10.0, digit) - 0.9 / pow(10.0, digit));
						m_rMainWnd.GetPitchSlider().SetThumbPos(n);
					});

	return TRUE;
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	m_nDecimalDigit = nDecimalDigit;
	auto spinbox = m_rMainWnd.pitchSpinBox;
	spinbox->setDecimals(nDecimalDigit);
	spinbox->setSingleStep(1.0 / pow(10, nDecimalDigit));
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(nDecimalDigit);
}
//----------------------------------------------------------------------------
// 表示する音程を設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::SetPitch(double dPitch)
{
	m_rMainWnd.pitchSpinBox->setValue(dPitch);
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::SetLimit(double dMinPitch, double dMaxPitch)
{
	m_rMainWnd.pitchSpinBox->setRange(dMinPitch, dMaxPitch);
}
//----------------------------------------------------------------------------
// コントロールの表示状態を設定
//----------------------------------------------------------------------------
void CPitchLabel_MainWnd::Show(int nCmdShow)
{
	bool visible = nCmdShow != SW_HIDE;
	m_rMainWnd.pitchLabel->setVisible(visible);
	m_rMainWnd.pitchSpinBox->setVisible(visible);
}
//----------------------------------------------------------------------------
