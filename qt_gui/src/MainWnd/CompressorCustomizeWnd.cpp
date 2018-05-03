//----------------------------------------------------------------------------
// CompressorCustomizeWnd.cpp : コンプレッサカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "CompressorCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CCompressorCustomizeWnd::CCompressorCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::CompressorCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_COMPRESSOR bdcmp;
	BOOL bCompressor = m_rMainWnd.GetSound().GetCompressor(&bdcmp);
	float fGain = bCompressor ? bdcmp.fGain : 0.0f;
	float fAttack = bCompressor ? bdcmp.fAttack : 10.0f;
	float fRelease = bCompressor ? bdcmp.fRelease : 200.0f;
	float fThreshold = bCompressor ? bdcmp.fThreshold : -20.0f;
	float fRatio = bCompressor ? bdcmp.fRatio : 3.0f;
	float fPredelay = bCompressor ? bdcmp.fPredelay : 4.0f;

	m_gain->setValue(fGain);
	m_attack->setValue(fAttack);
	m_release->setValue(fRelease);
	m_threshold->setValue(fThreshold);
	m_ratio->setValue(fRatio);
	m_predelay->setValue(fPredelay);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CCompressorCustomizeWnd::OnOkButtonClicked()
{
	float fGain = (float)m_gain->value();
	float fAttack = (float)m_attack->value();
	float fRelease = (float)m_release->value();
	float fThreshold = (float)m_threshold->value();
	float fRatio = (float)m_ratio->value();
	float fPredelay = (float)m_predelay->value();

	m_rMainWnd.GetMenu().SetCompressor(fGain, fAttack, fRelease, fThreshold,
		fRatio, fPredelay, ID_COMPRESSOR_CUSTOMIZE);
	accepted();
}
//----------------------------------------------------------------------------
