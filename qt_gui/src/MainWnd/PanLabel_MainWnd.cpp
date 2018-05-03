//----------------------------------------------------------------------------
// PanLabel_MainWnd.cpp : パン表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PanLabel_MainWnd.h"
#include "MainWnd.h"
#include "PanSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPanLabel_MainWnd::Create()
{
	auto spinbox = m_rMainWnd.panSpinBox;

	spinbox->setRange(-100, 100);

	SetPan(0);

	connect(spinbox, static_cast<void (QSpinBox::*)(int)>(
						&QSpinBox::valueChanged),
					[&] (int n) {
						m_rMainWnd.GetPanSlider().SetThumbPos(n, TRUE);
					});

	return TRUE;
}
//----------------------------------------------------------------------------
// 表示するパンを表示
//----------------------------------------------------------------------------
void CPanLabel_MainWnd::SetPan(int nPan)
{
	m_rMainWnd.panSpinBox->setValue(nPan);
}
//----------------------------------------------------------------------------
// コントロールの表示状態を設定
//----------------------------------------------------------------------------
void CPanLabel_MainWnd::Show(int nCmdShow)
{
	bool visible = nCmdShow != SW_HIDE;
	m_rMainWnd.panLabel->setVisible(visible);
	m_rMainWnd.panSpinBox->setVisible(visible);
}
//----------------------------------------------------------------------------
