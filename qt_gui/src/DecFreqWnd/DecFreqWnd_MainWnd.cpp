//----------------------------------------------------------------------------
// DecFreqWnd_MainWnd.cpp : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "DecFreqWnd_MainWnd.h"
#include "../MainWnd/MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDecFreqWnd_MainWnd::CDecFreqWnd_MainWnd(CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(mainWnd)
{
	setWindowTitle(tr("Decrease frequency"));

	m_label->setText(tr("Turn down frequency", "for seconds"));
	m_label3->setText(tr("seconds"));
	m_label4->setText(tr("Turn down frequency", "for looping"));
	m_label5->setText(tr("% every looping"));
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CDecFreqWnd_MainWnd::OnOkButtonClicked()
{
	if(m_secondRadioButton->isChecked()) {
		double nSecond = m_edit->value();
		double nDecFreq = m_edit2->value();
		m_rMainWnd.SetDecFreq(nSecond, nDecFreq);
	}
	else {
		double nDecFreq = m_edit3->value();
		m_rMainWnd.SetDecFreq(nDecFreq);
	}
	accepted();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CDecFreqWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetDecFreq(FALSE, 0);
	rejected();
}
//----------------------------------------------------------------------------
