//----------------------------------------------------------------------------
// LimitSettingWnd_MainWnd.cpp : タイマー再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "LimitSettingWnd_MainWnd.h"
#include <math.h>
#include "../MainWnd/MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CLimitSettingWnd_MainWnd::CLimitSettingWnd_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::LimitSettingWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	int nMinSpeed = (int)(m_rMainWnd.GetSpeedSlider().GetRangeMin() * 10.0
		/ pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit()));
	int nMaxSpeed = (int)(m_rMainWnd.GetSpeedSlider().GetRangeMax() * 10.0
		/ pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit()));
	int nMinFreq = (int)(m_rMainWnd.GetFreqSlider().GetRangeMin() * 10.0
		/ pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit()));
	int nMaxFreq = (int)(m_rMainWnd.GetFreqSlider().GetRangeMax() * 10.0
		/ pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit()));
	int nMinPitch = (int)(m_rMainWnd.GetPitchSlider().GetRangeMin() * 10.0
		/ pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit()));
	int nMaxPitch = (int)(m_rMainWnd.GetPitchSlider().GetRangeMax() * 10.0
		/ pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit()));

	m_minSpeedEdit->setValue(nMinSpeed / 10.0);
	m_minSpeedEdit->setRange(1.0, 100.0);

	m_maxSpeedEdit->setValue(nMaxSpeed / 10.0);
	m_maxSpeedEdit->setRange(100.0, 5000.0);

	m_minFreqEdit->setValue(nMinFreq / 10.0);
	m_minFreqEdit->setRange(1.0, 100.0);

	m_maxFreqEdit->setValue(nMaxFreq / 10.0);
	m_maxFreqEdit->setRange(100.0, 5000.0);

	m_minPitchEdit->setValue(nMinPitch / 10.0);
	m_minPitchEdit->setRange(-60.0, 0.0);

	m_maxPitchEdit->setValue(nMaxPitch / 10.0);
	m_maxPitchEdit->setRange(0.0, 60.0);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CLimitSettingWnd_MainWnd::OnOkButtonClicked()
{
	double dMinSpeed = m_minSpeedEdit->value();
	double dMaxSpeed = m_maxSpeedEdit->value();
	double dMinFreq = m_minFreqEdit->value();
	double dMaxFreq = m_maxFreqEdit->value();
	double dMinPitch = m_minPitchEdit->value();
	double dMaxPitch = m_maxPitchEdit->value();
	m_rMainWnd.SetLimit(dMinSpeed, dMaxSpeed, dMinFreq, dMaxFreq,
						dMinPitch, dMaxPitch);
	accepted();
}
//----------------------------------------------------------------------------
