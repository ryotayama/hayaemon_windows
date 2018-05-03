//----------------------------------------------------------------------------
// CountLoopWnd_MainWnd.cpp : 回数ループウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "CountLoopWnd_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CCountLoopWnd_MainWnd::CCountLoopWnd_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::CountLoopWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	m_edit->setRange(0, 9999);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] {
						OnOkButtonClicked();
						accepted();
					});
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CCountLoopWnd_MainWnd::OnOkButtonClicked()
{
	int nCount = m_edit->value();
	m_rMainWnd.SetCountLoop(nCount);
	accept();
}
//----------------------------------------------------------------------------
