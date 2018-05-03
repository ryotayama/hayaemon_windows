//----------------------------------------------------------------------------
// ReverbCustomizeWnd.cpp : リバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "ReverbCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CReverbCustomizeWnd::CReverbCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::ReverbCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_REVERB bdr;
	BOOL bReverb = m_rMainWnd.GetSound().GetReverb(&bdr);
	int nGain = bReverb ? (int)bdr.fInGain : 0;
	int nRevMix = bReverb ? (int)bdr.fReverbMix : 0;
	double dRevTime = bReverb ? bdr.fReverbTime : 1000.0;
	double dHigh = bReverb ? bdr.fHighFreqRTRatio : 0.001;

	m_gain->setValue(nGain);
	m_revMix->setValue(nRevMix);
	m_revTime->setValue(dRevTime);
	m_high->setValue(dHigh);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] {
						OnOkButtonClicked();
					});
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnOkButtonClicked()
{
	float dGain = (float)m_gain->value();
	float dRevMix = (float)m_revMix->value();
	float dRevTime = (float)m_revTime->value();
	float dHigh = (float)m_high->value();
	m_rMainWnd.GetMenu().SetReverb(dGain, dRevMix, dRevTime, dHigh,
		ID_REVERB_CUSTOMIZE);
	accepted();
}
//----------------------------------------------------------------------------
