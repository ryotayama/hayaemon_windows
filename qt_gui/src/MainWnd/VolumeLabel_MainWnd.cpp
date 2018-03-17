//----------------------------------------------------------------------------
// VolumeLabel_MainWnd.cpp : ボリューム表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "VolumeLabel_MainWnd.h"
#include "MainWnd.h"
#include "VolumeSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CVolumeLabel_MainWnd::Create()
{
	auto spinbox = m_rMainWnd.volumeSpinBox;
	spinbox->setRange(0.0, 100.0);
	spinbox->setDecimals(1);
	spinbox->setSingleStep(0.1);

	SetVolume(100.0);

	connect(spinbox, static_cast<void (QDoubleSpinBox::*)(double)>(
						&QDoubleSpinBox::valueChanged),
					[&] (double n) {
						m_rMainWnd.GetVolumeSlider().SetThumbPos((LONG)(n * 10.0), TRUE);
					});

	return TRUE;
}
//----------------------------------------------------------------------------
// 表示する周波数を表示
//----------------------------------------------------------------------------
void CVolumeLabel_MainWnd::SetVolume(double nVolume)
{
	m_rMainWnd.volumeSpinBox->setValue(nVolume);
}
//----------------------------------------------------------------------------
// コントロールの表示状態を設定
//----------------------------------------------------------------------------
void CVolumeLabel_MainWnd::Show(int nCmdShow)
{
	bool visible = nCmdShow != SW_HIDE;
	m_rMainWnd.volumeLabel->setVisible(visible);
	m_rMainWnd.volumeLabel2->setVisible(visible);
	m_rMainWnd.volumeSpinBox->setVisible(visible);
}
//----------------------------------------------------------------------------
