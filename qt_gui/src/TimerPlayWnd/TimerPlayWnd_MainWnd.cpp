//----------------------------------------------------------------------------
// TimerPlayWnd_MainWnd.cpp : タイマー再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "TimerPlayWnd_MainWnd.h"
#include <ctime>
#include "../MainWnd/MainWnd.h"
#include "Utility.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CTimerPlayWnd_MainWnd::CTimerPlayWnd_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::TimerPlayWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	m_playRadioButton->setChecked(true);

	time_t now = std::time(nullptr);
	auto localNow = std::localtime(&now);
	m_edit->setValue(localNow->tm_hour);
	m_edit->setRange(0, 23);
	m_edit2->setValue(localNow->tm_min);
	m_edit2->setRange(0, 59);
	m_edit3->setValue(localNow->tm_hour);
	m_edit3->setRange(0, 23);
	m_edit4->setValue(localNow->tm_min);
	m_edit4->setRange(0, 59);

	if (QLocale::system().name() == "ja_JP") {
		m_label3->setText(m_label->text());
		m_label->setText(QString());
		m_label6->setText(m_label4->text());
		m_label4->setText(QString());
	}

	EnableControl(true, false);

	connect(m_playRadioButton, &QRadioButton::clicked,
					[&] (bool checked) { if (checked) { EnableControl(true, false); }});
	connect(m_stopRadioButton, &QRadioButton::clicked,
					[&] (bool checked) { if (checked) { EnableControl(false, true); }});
	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
	connect(this->buttonBox, &QDialogButtonBox::rejected,
					[&] { OnCancelButtonClicked(); });
}
//----------------------------------------------------------------------------
// コントロールの有効・無効の設定
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::EnableControl(bool bPlayEnable, bool bStopEnable)
{
	m_label->setEnabled(bPlayEnable);
	m_label2->setEnabled(bPlayEnable);
	m_label3->setEnabled(bPlayEnable);
	m_edit->setEnabled(bPlayEnable);
	m_edit2->setEnabled(bPlayEnable);

	m_label4->setEnabled(bStopEnable);
	m_label5->setEnabled(bStopEnable);
	m_label6->setEnabled(bStopEnable);
	m_edit3->setEnabled(bStopEnable);
	m_edit4->setEnabled(bStopEnable);
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnOkButtonClicked()
{
	if(m_playRadioButton->isChecked()) {
		int nHour = m_edit->value();
		int nMinute = m_edit2->value();
		m_rMainWnd.SetTimerPlay(nHour, nMinute);
	}
	else {
		int nHour = m_edit3->value();
		int nMinute = m_edit4->value();
		m_rMainWnd.SetTimerStop(nHour, nMinute);
	}
	accepted();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CTimerPlayWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetTimerPlay(FALSE);
	rejected();
}
//----------------------------------------------------------------------------
