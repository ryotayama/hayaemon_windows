//----------------------------------------------------------------------------
// AllSaveWnd_MainWnd.cpp : 一括変換ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "AllSaveWnd_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CAllSaveWnd_MainWnd::CAllSaveWnd_MainWnd(CMainWnd & mainWnd)
{
	Ui::AllSaveWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	tstring strSaveFormat = mainWnd.GetStrSaveFormat();
	int index;
	if(strSaveFormat == _T("MP3"))
		index = 1;
	else if(strSaveFormat == _T("OGG"))
		index = 2;
	else
		index = 0;
	m_Combo->setCurrentIndex(index);
}
//----------------------------------------------------------------------------
