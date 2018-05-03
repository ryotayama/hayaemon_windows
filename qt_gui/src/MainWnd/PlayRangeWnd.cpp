//----------------------------------------------------------------------------
// PlayRangeWnd.cpp : 再生範囲設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "PlayRangeWnd.h"
#include "MainWnd.h"
#include "Utility.h"
#include "Platform.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CPlayRangeWnd::CPlayRangeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::PlayRangeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { SetRange(); });
}
//----------------------------------------------------------------------------
// 再生範囲の設定
//----------------------------------------------------------------------------
void CPlayRangeWnd::SetRange()
{
	tstring strTime = ToTstring(m_editStart->text());
	size_t n = 0;
	while((n = strTime.find(_T(":"), 0)) != tstring::npos)
		strTime.replace(n, 1, _T(""));
	int nHour = 0, nMinute = 0, nSecond = 0;
	if(strTime.length() == 6) {
		nHour = _ttoi(strTime.substr(0, 2).c_str());
		nMinute = _ttoi(strTime.substr(2, 2).c_str());
		nSecond = _ttoi(strTime.substr(4, 2).c_str());
	}
	else if(strTime.length() == 5) {
		nHour = _ttoi(strTime.substr(0, 1).c_str());
		nMinute = _ttoi(strTime.substr(1, 2).c_str());
		nSecond = _ttoi(strTime.substr(3, 2).c_str());
	}
	else if(strTime.length() == 4) {
		nMinute = _ttoi(strTime.substr(0, 2).c_str());
		nSecond = _ttoi(strTime.substr(2, 2).c_str());
	}
	else if(strTime.length() == 3) {
		nMinute = _ttoi(strTime.substr(0, 1).c_str());
		nSecond = _ttoi(strTime.substr(1, 2).c_str());
	}
	else if(strTime.length() == 2) {
		nSecond = _ttoi(strTime.substr(0, 2).c_str());
	}
	else if(strTime.length() == 1) {
		nSecond = _ttoi(strTime.substr(0, 1).c_str());
	}
	int nStartSeconds = nHour * 3600 + nMinute * 60 + nSecond;

	strTime = ToTstring(m_editEnd->text());
	n = 0;
	while((n = strTime.find(_T(":"), 0)) != tstring::npos)
		strTime.replace(n, 1, _T(""));
	nHour = 0, nMinute = 0, nSecond = 0;
	if(strTime.length() == 6) {
		nHour = _ttoi(strTime.substr(0, 2).c_str());
		nMinute = _ttoi(strTime.substr(2, 2).c_str());
		nSecond = _ttoi(strTime.substr(4, 2).c_str());
	}
	else if(strTime.length() == 5) {
		nHour = _ttoi(strTime.substr(0, 1).c_str());
		nMinute = _ttoi(strTime.substr(1, 2).c_str());
		nSecond = _ttoi(strTime.substr(3, 2).c_str());
	}
	else if(strTime.length() == 4) {
		nMinute = _ttoi(strTime.substr(0, 2).c_str());
		nSecond = _ttoi(strTime.substr(2, 2).c_str());
	}
	else if(strTime.length() == 3) {
		nMinute = _ttoi(strTime.substr(0, 1).c_str());
		nSecond = _ttoi(strTime.substr(1, 2).c_str());
	}
	else if(strTime.length() == 2) {
		nSecond = _ttoi(strTime.substr(0, 2).c_str());
	}
	else if(strTime.length() == 1) {
		nSecond = _ttoi(strTime.substr(0, 1).c_str());
	}
	int nEndSeconds = nHour * 3600 + nMinute * 60 + nSecond;

	if(nStartSeconds == nEndSeconds) return;
	else if(nEndSeconds > nStartSeconds)
		m_rMainWnd.SetPlayRange(nStartSeconds, nEndSeconds);
	else
		m_rMainWnd.SetPlayRange(nEndSeconds, nStartSeconds);

	accepted();
}
//----------------------------------------------------------------------------
