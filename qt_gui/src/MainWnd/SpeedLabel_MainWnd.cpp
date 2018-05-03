//----------------------------------------------------------------------------
// SpeedLabel_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "SpeedLabel_MainWnd.h"
#include <cmath>
#include "MainWnd.h"
#include "SpeedSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CSpeedLabel_MainWnd::Create()
{
	auto spinbox = m_rMainWnd.speedSpinBox;
	spinbox->setDecimals(m_nDecimalDigit);
	spinbox->setSingleStep(0.1);

	spinbox->setRange(10.0, 1200.0);

	SetSpeed(100.0);

	connect(spinbox, static_cast<void (QDoubleSpinBox::*)(double)>(
						&QDoubleSpinBox::valueChanged),
					[&] (double d) {
						int digit = m_rMainWnd.GetSpeedSlider().GetDecimalDigit();
						int n = (int)(d * pow(10.0, digit) + 0.9 / pow(10.0, digit));
						m_rMainWnd.GetSpeedSlider().SetThumbPos(n);
					});

	return TRUE;
}
//----------------------------------------------------------------------------
// 小数点桁数を設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::SetDecimalDigit(int nDecimalDigit)
{
	m_nDecimalDigit = nDecimalDigit;
	auto spinbox = m_rMainWnd.speedSpinBox;
	spinbox->setDecimals(nDecimalDigit);
	spinbox->setSingleStep(1.0 / pow(10, nDecimalDigit));
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(nDecimalDigit);
}
//----------------------------------------------------------------------------
// 表示する速度をパーセントで設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::SetSpeed(double dSpeed)
{
	m_rMainWnd.speedSpinBox->setValue(dSpeed);
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::SetLimit(double dMinSpeed, double dMaxSpeed)
{
	m_rMainWnd.speedSpinBox->setRange(dMinSpeed, dMaxSpeed);
}
//----------------------------------------------------------------------------
// コントロールの表示状態を設定
//----------------------------------------------------------------------------
void CSpeedLabel_MainWnd::Show(int nCmdShow)
{
	bool visible = nCmdShow != SW_HIDE;
	m_rMainWnd.speedLabel->setVisible(visible);
	m_rMainWnd.speedLabel2->setVisible(visible);
	m_rMainWnd.speedSpinBox->setVisible(visible);
}
//----------------------------------------------------------------------------
