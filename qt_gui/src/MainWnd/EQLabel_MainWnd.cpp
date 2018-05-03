//----------------------------------------------------------------------------
// EQLabel_MainWnd.cpp : イコライザ表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "EQLabel_MainWnd.h"
#include <functional>
#include <QLabel>
#include <QSpinBox>
#include "EQSlider_MainWnd.h"
//----------------------------------------------------------------------------
// 参照の初期化
//----------------------------------------------------------------------------
void CEQLabel_MainWnd::Init(QLabel * label, QSpinBox * spinBox,
														CEQSlider_MainWnd * slider)
{
	m_label = label; 
	m_spinBox = spinBox;
	m_slider = slider;
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CEQLabel_MainWnd::Create()
{
	m_spinBox->setSingleStep(1);

	m_spinBox->setRange(-30, 30);

	SetEQ(0);

	using namespace std::placeholders;
	connect(m_spinBox, static_cast<void (QSpinBox::*)(int)>(
						&QSpinBox::valueChanged),
					std::bind(&CSliderCtrl::SetThumbPos, m_slider, _1, TRUE));

	return TRUE;
}
//----------------------------------------------------------------------------
// 表示する周波数を表示
//----------------------------------------------------------------------------
void CEQLabel_MainWnd::SetEQ(int nEQ)
{
	m_spinBox->setValue(nEQ);
}
//----------------------------------------------------------------------------
// コントロールの表示状態を設定
//----------------------------------------------------------------------------
void CEQLabel_MainWnd::Show(int nCmdShow)
{
	bool visible = nCmdShow != SW_HIDE;
	m_label->setVisible(visible);
	m_spinBox->setVisible(visible);
}
//----------------------------------------------------------------------------
