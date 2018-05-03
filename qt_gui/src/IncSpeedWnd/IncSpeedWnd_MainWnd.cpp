//----------------------------------------------------------------------------
// IncSpeedWnd_MainWnd.cpp : だんだん速くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "IncSpeedWnd_MainWnd.h"
#include <QLocale>
#include "../MainWnd/MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CIncSpeedWnd_MainWnd::CIncSpeedWnd_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::IncSpeedWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	m_secondRadioButton->setChecked(true);

	if (QLocale::system().name() == "ja_JP") {
		m_edit = edit;
		m_edit2 = edit2;
	} else {
		m_edit = edit2;
		m_edit2 = edit;
	}

	m_edit->setRange(0.0, 999.99);
	m_edit->setValue(1.00);
	m_edit->setDecimals(2);
	m_edit->setSingleStep(0.01);

	m_edit2->setRange(0, 999.9);
	m_edit2->setValue(0.1);
	m_edit2->setDecimals(1);
	m_edit2->setSingleStep(0.1);

	m_edit3->setRange(0, 999.9);
	m_edit3->setValue(0.1);
	m_edit3->setDecimals(1);
	m_edit3->setSingleStep(0.1);

	EnableControl(true, false);

	connect(m_secondRadioButton, &QRadioButton::clicked,
					[&] (bool checked) { if (checked) { EnableControl(true, false); }});
	connect(m_loopRadioButton, &QRadioButton::clicked,
					[&] (bool checked) { if (checked) { EnableControl(false, true); }});
	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
	connect(this->buttonBox, &QDialogButtonBox::rejected,
					[&] { OnCancelButtonClicked(); });
}
//----------------------------------------------------------------------------
// コントロールの有効・無効の設定
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::EnableControl(bool bSecondEnable, bool bLoopEnable)
{
	m_label->setEnabled(bSecondEnable);
	m_label2->setEnabled(bSecondEnable);
	m_label3->setEnabled(bSecondEnable);
	m_edit->setEnabled(bSecondEnable);
	m_edit2->setEnabled(bSecondEnable);

	m_label4->setEnabled(bLoopEnable);
	m_label5->setEnabled(bLoopEnable);
	m_edit3->setEnabled(bLoopEnable);
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnOkButtonClicked()
{
	if(m_secondRadioButton->isChecked()) {
		double nSecond = m_edit->value();
		double nIncSpeed = m_edit2->value();
		m_rMainWnd.SetIncSpeed(nSecond, nIncSpeed);
	}
	else {
		double nIncSpeed = m_edit3->value();
		m_rMainWnd.SetIncSpeed(nIncSpeed);
	}
	accepted();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CIncSpeedWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetIncSpeed(FALSE, 0);
	rejected();
}
//----------------------------------------------------------------------------
