//----------------------------------------------------------------------------
// DecSpeedWnd_MainWnd.cpp : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "DecSpeedWnd_MainWnd.h"
#include "../MainWnd/MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDecSpeedWnd_MainWnd::CDecSpeedWnd_MainWnd(CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(mainWnd)
{
	setWindowTitle(tr("Decrease speed"));

	m_label->setText(tr("Turn down speed", "for seconds"));
	m_label3->setText(tr("seconds"));
	m_label4->setText(tr("Turn down  speed", "for looping"));
	m_label5->setText(tr("% every looping"));
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnOkButtonClicked()
{
	if(m_secondRadioButton->isChecked()) {
		double nSecond = m_edit->value();
		double nDecSpeed = m_edit2->value();
		m_rMainWnd.SetDecSpeed(nSecond, nDecSpeed);
	}
	else {
		double nDecSpeed = m_edit3->value();
		m_rMainWnd.SetDecSpeed(nDecSpeed);
	}
	accepted();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetDecSpeed(FALSE, 0);
	rejected();
}
//----------------------------------------------------------------------------
