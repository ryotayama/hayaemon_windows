//----------------------------------------------------------------------------
// GargleCustomizeWnd.cpp : ガーグルカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "GargleCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CGargleCustomizeWnd::CGargleCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::GargleCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_GARGLE bdg;
	BOOL bGargle = m_rMainWnd.GetSound().GetGargle(&bdg);
	int nRateHz = bGargle ? bdg.dwRateHz : 20;
	int nWaveShape = bGargle ? bdg.dwWaveShape : 0;

	m_rateHz->setValue(nRateHz);
	m_waveShape->setValue(nWaveShape);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnOkButtonClicked()
{
	int nRateHz = m_rateHz->value();
	int nWaveShape = m_waveShape->value();

	m_rMainWnd.GetMenu().SetGargle((DWORD)nRateHz, (DWORD)nWaveShape,
		ID_GARGLE_CUSTOMIZE);
	accepted();
}
//----------------------------------------------------------------------------
