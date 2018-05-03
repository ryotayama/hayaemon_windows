//----------------------------------------------------------------------------
// MetronomeWnd_MainWnd.cpp : メトロノーム用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "MetronomeWnd_MainWnd.h"
#include "../MainWnd/MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CMetronomeWnd_MainWnd::CMetronomeWnd_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::MetronomeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	int nBpm = m_rMainWnd.GetBpm();
	m_bpmEdit->setValue(nBpm);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { OnOkButtonClicked(); });
	connect(this->buttonBox, &QDialogButtonBox::rejected,
					[&] { OnCancelButtonClicked(); });
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnOkButtonClicked()
{
	int nBpm = m_bpmEdit->value();
	m_rMainWnd.SetMetronome(nBpm);
	accepted();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.StopMetronome();
	rejected();
}
//----------------------------------------------------------------------------
