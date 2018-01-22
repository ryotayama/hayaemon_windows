//----------------------------------------------------------------------------
// FlangerCustomizeWnd.cpp : フランジャーカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "FlangerCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CFlangerCustomizeWnd::CFlangerCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::FlangerCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_FLANGER bdf;
	BOOL bFlanger = m_rMainWnd.GetSound().GetFlanger(&bdf);
	float fWetDryMix = bFlanger ? bdf.fWetDryMix : 50.0f;
	float fDepth = bFlanger ? bdf.fDepth : 100.0f;
	float fFeedback = bFlanger ? bdf.fFeedback : -50.0f;
	float fFrequency = bFlanger ? bdf.fFrequency : 0.25f;
	int lWaveform = bFlanger ? bdf.lWaveform : 1;
	float fDelay = bFlanger ? bdf.fDelay : 2.0f;

	m_wetDryMix->setValue(fWetDryMix);
	m_depth->setValue(fDepth);
	m_feedback->setValue(fFeedback);
	m_frequency->setValue(fFrequency);
	m_waveform->setValue(lWaveform);
	m_delay->setValue(fDelay);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CFlangerCustomizeWnd::OnOkButtonClicked()
{
	float fWetDryMix = (float)m_wetDryMix->value();
	float fDepth = (float)m_depth->value();
	float fFeedback = (float)m_feedback->value();
	float fFrequency = (float)m_frequency->value();
	int lWaveform = m_waveform->value();
	float fDelay = (float)m_delay->value();

	m_rMainWnd.GetMenu().SetFlanger(fWetDryMix, fDepth, fFeedback, fFrequency,
		(DWORD)lWaveform, fDelay, BASS_DX8_PHASE_ZERO, ID_FLANGER_CUSTOMIZE);
	accepted();
}
//----------------------------------------------------------------------------
