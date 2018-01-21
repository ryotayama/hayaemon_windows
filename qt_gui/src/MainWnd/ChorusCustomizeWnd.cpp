//----------------------------------------------------------------------------
// ChorusCustomizeWnd.cpp : コーラスのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "ChorusCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CChorusCustomizeWnd::CChorusCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::ChorusCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_CHORUS bdc;
	BOOL bChorus = m_rMainWnd.GetSound().GetChorus(&bdc);
	float fWetDryMix = bChorus ? bdc.fWetDryMix : 50.0f;
	float fDepth = bChorus ? bdc.fDepth : 10.0f;
	float fFeedback = bChorus ? bdc.fFeedback : 25.0f;
	float fFrequency = bChorus ? bdc.fFrequency : 1.1f;
	int lWaveForm = bChorus ? bdc.lWaveform : 1;
	float fDelay = bChorus ? bdc.fDelay : 16.0f;

	m_wetDryMix->setValue(fWetDryMix);
	m_depth->setValue(fDepth);
	m_feedback->setValue(fFeedback);
	m_frequency->setValue(fFrequency);
	m_waveform->setValue(lWaveForm);
	m_delay->setValue(fDelay);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnOkButtonClicked()
{
	float fWetDryMix = (float)m_wetDryMix->value();
	float fDepth = (float)m_depth->value();
	float fFeedback = (float)m_feedback->value();
	float fFrequency = (float)m_frequency->value();
	int lWaveForm = m_waveform->value();
	float fDelay = (float)m_delay->value();

	m_rMainWnd.GetMenu().SetChorus(fWetDryMix, fDepth, fFeedback, fFrequency,
		lWaveForm, fDelay, BASS_DX8_PHASE_90, ID_CHORUS_CUSTOMIZE);
	accepted();
}
//----------------------------------------------------------------------------
