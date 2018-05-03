//----------------------------------------------------------------------------
// OpenURLWnd.cpp : 「URLを開く」用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "OpenURLWnd.h"
#include "MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "Sound.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
COpenURLWnd::COpenURLWnd(CMainWnd & mainWnd, bool bAdd /* = false */)
	: m_rMainWnd(mainWnd), m_bAdd(bAdd)
{
	Ui::OpenURLWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QString strTitle = bAdd ? tr("Add URL") : tr("Open URL");
	setWindowTitle(strTitle);

	m_edit->setText("http://");

	connect(this->buttonBox, &QDialogButtonBox::accepted, [&] { OpenURL(); });
}
//----------------------------------------------------------------------------
// URLを開く
//----------------------------------------------------------------------------
void COpenURLWnd::OpenURL()
{
	QString strURL = m_edit->text();

	int nSelect = m_rMainWnd.GetTab().GetCurrentFocus();
	m_rMainWnd.ChangeCurPlayTab();
	if(!m_bAdd) {
		m_rMainWnd.GetPlayList().DeleteAllItems();
	}
	m_rMainWnd.GetPlayList().AddFile(strURL);

	if(m_rMainWnd.GetPlayList().GetItemCount() <= 0) {
		m_rMainWnd.GetSound().StreamFree();
		m_rMainWnd.Stop();
	}
	else {
		m_rMainWnd.GetSound().SetCurFileNum(0);
		m_rMainWnd.PlayNext(TRUE, TRUE);
	}

	m_rMainWnd.SetPreviousNextMenuState();
	m_rMainWnd.StartUpdateInfo();

	accepted();
}
//----------------------------------------------------------------------------
