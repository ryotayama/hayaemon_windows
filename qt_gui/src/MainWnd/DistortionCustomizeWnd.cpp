//----------------------------------------------------------------------------
// DistortionCustomizeWnd.cpp : ディストーションカスタマイズ用ウィンドウの管理
//----------------------------------------------------------------------------
#include "DistortionCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDistortionCustomizeWnd::CDistortionCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::DistortionCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_DISTORTION bdd;
	BOOL bDistortion = m_rMainWnd.GetSound().GetDistortion(&bdd);
	float fGain = bDistortion ? bdd.fGain : -18.0f;
	float fEdge = bDistortion ? bdd.fEdge : 15.0f;
	float fPostEQCenterFrequency =
		bDistortion ? bdd.fPostEQCenterFrequency : 2400.0f;
	float fPostEQBandwidth = bDistortion ? bdd.fPostEQBandwidth : 2400.0f;
	float fPreLowpassCutoff = bDistortion ? bdd.fPreLowpassCutoff : 8000.0f;

	m_gain->setValue(fGain);
	m_edge->setValue(fEdge);
	m_postEQCenterFrequency->setValue(fPostEQCenterFrequency);
	m_postEQBandwidth->setValue(fPostEQBandwidth);
	m_preLowpassCutoff->setValue(fPreLowpassCutoff);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnOkButtonClicked()
{
	float fGain = (float)m_gain->value();
	float fEdge = (float)m_edge->value();
	float fPostEQCenterFrequency = (float)m_postEQCenterFrequency->value();
	float fPostEQBandwidth = (float)m_postEQBandwidth->value();
	float fPreLowpassCutoff = (float)m_preLowpassCutoff->value();

	m_rMainWnd.GetMenu().SetDistortion(fGain, fEdge, fPostEQCenterFrequency,
		fPostEQBandwidth, fPreLowpassCutoff, ID_DISTORTION_CUSTOMIZE);
	accepted();
}
//----------------------------------------------------------------------------
