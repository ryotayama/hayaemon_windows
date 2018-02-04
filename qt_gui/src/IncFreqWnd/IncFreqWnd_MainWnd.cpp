//----------------------------------------------------------------------------
// IncFreqWnd_MainWnd.cpp : だんだん速くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "IncFreqWnd_MainWnd.h"
#include "../MainWnd/MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CIncFreqWnd_MainWnd::CIncFreqWnd_MainWnd(CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(mainWnd)
{
	setWindowTitle(tr("Increase frequency"));

	m_label->setText(tr("Turn up frequency", "for seconds"));
	m_label3->setText(tr("seconds"));
	m_label4->setText(tr("Turn up frequency", "for looping"));
	m_label5->setText(tr("% every looping"));
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CIncFreqWnd_MainWnd::OnOkButtonClicked()
{
	if(m_secondRadioButton->isChecked()) {
		double nSecond = m_edit->value();
		double nIncFreq = m_edit2->value();
		m_rMainWnd.SetIncFreq(nSecond, nIncFreq);
	}
	else {
		double nIncFreq = m_edit3->value();
		m_rMainWnd.SetIncFreq(nIncFreq);
	}
	accepted();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CIncFreqWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetIncFreq(FALSE, 0);
	rejected();
}
//----------------------------------------------------------------------------
