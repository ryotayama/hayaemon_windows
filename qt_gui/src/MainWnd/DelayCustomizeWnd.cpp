//----------------------------------------------------------------------------
// DelayCustomizeWnd.cpp : ディレイのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "DelayCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDelayCustomizeWnd::CDelayCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::DelayCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_ECHO bde;
	BOOL bDelay = m_rMainWnd.GetSound().GetDelay(&bde);
	float fWetDryMix = bDelay ? bde.fWetDryMix : 8.0f;
	float fFeedback = bDelay ? bde.fFeedback : 50.0f;
	float fLeftDelay = bDelay ? bde.fLeftDelay : 600.0f;
	float fRightDelay = bDelay ? bde.fRightDelay : 300.0f;
	int lPanDelay = bDelay ? bde.lPanDelay : 1;

	m_wetDryMix->setValue(fWetDryMix);
	m_feedback->setValue(fFeedback);
	m_leftDelay->setValue(fLeftDelay);
	m_rightDelay->setValue(fRightDelay);
	m_panDelay->setValue(lPanDelay);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnOkButtonClicked()
{
	float flWetDryMix = (float)m_wetDryMix->value();
	float flFeedback = (float)m_feedback->value();
	float flLeftDelay = (float)m_leftDelay->value();
	float flRightDelay = (float)m_rightDelay->value();
	int lPanDelay = m_panDelay->value();

	m_rMainWnd.GetMenu().SetDelay(flWetDryMix, flFeedback, flLeftDelay,
		flRightDelay, (BOOL)lPanDelay, ID_DELAY_CUSTOMIZE);

	accepted();
}
//----------------------------------------------------------------------------
