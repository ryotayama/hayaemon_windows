//----------------------------------------------------------------------------
// ABLoopPosWnd.cpp : ABループ位置設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "ABLoopPosWnd.h"
#include "MainWnd.h"
#include "Platform.h"
#include "Utility.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CABLoopPosWnd::CABLoopPosWnd(CMainWnd & mainWnd, BOOL bLoopA)
	: QDialog(nullptr), m_rMainWnd(mainWnd), m_bLoopA(bLoopA)
{
	Ui::ABLoopPosWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	if (bLoopA) {
		setWindowTitle(tr("AB Loop(A) Pos Setting"));
	} else {
		setWindowTitle(tr("AB Loop(B) Pos Setting"));
	}

	double dTime = m_bLoopA ? m_rMainWnd.GetSound().GetLoopPosA_sec()
							: m_rMainWnd.GetSound().GetLoopPosB_sec();
	tstring strTime;
	TCHAR chBuf[255];
	int hour = (int)(dTime / 3600) % 60;
	int second = (int)(dTime / 60) % 60;
	int minute = (int)dTime %60;
	double dDecimal = dTime - (int)dTime;
	_stprintf_s(chBuf, _T("%02d:%02d:%02d"), hour, second, minute);
	strTime = chBuf;
	_stprintf_s(chBuf, _T("%.3f"), dDecimal);
	tstring strDecimal = chBuf;
	strTime = strTime + _T(".") + strDecimal.substr(2, 3);
	m_edit->setText(ToQString(strTime));

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] {
						SetPos();
						accepted();
					});
}
//----------------------------------------------------------------------------
// 位置の設定
//----------------------------------------------------------------------------
void CABLoopPosWnd::SetPos()
{
	tstring strTime = ToTstring(m_edit->text());
	tstring strInt = _T("");
	tstring strDecimals = _T("0");
	size_t nDecimalPos = 0;
	if((nDecimalPos = strTime.find(_T("."), 0)) != tstring::npos) {
		strInt = strTime.substr(0, nDecimalPos);
		strDecimals += strTime.substr(nDecimalPos,
									 strTime.length() - nDecimalPos);
	}
	else strInt = strTime;

	size_t n = 0;
	while((n = strInt.find(_T(":"), 0)) != tstring::npos)
		strInt.replace(n, 1, _T(""));
	int nHour = 0, nMinute = 0, nSecond = 0;
	if(strInt.length() == 6) {
		nHour = _ttoi(strInt.substr(0, 2).c_str());
		nMinute = _ttoi(strInt.substr(2, 2).c_str());
		nSecond = _ttoi(strInt.substr(4, 2).c_str());
	}
	else if(strInt.length() == 5) {
		nHour = _ttoi(strInt.substr(0, 1).c_str());
		nMinute = _ttoi(strInt.substr(1, 2).c_str());
		nSecond = _ttoi(strInt.substr(3, 2).c_str());
	}
	else if(strInt.length() == 4) {
		nMinute = _ttoi(strInt.substr(0, 2).c_str());
		nSecond = _ttoi(strInt.substr(2, 2).c_str());
	}
	else if(strInt.length() == 3) {
		nMinute = _ttoi(strInt.substr(0, 1).c_str());
		nSecond = _ttoi(strInt.substr(1, 2).c_str());
	}
	else if(strInt.length() == 2) {
		nSecond = _ttoi(strInt.substr(0, 2).c_str());
	}
	else if(strInt.length() == 1) {
		nSecond = _ttoi(strInt.substr(0, 1).c_str());
	}
	double dSeconds = nHour * 3600 + nMinute * 60 + nSecond
						+ _ttof(strDecimals.c_str());
	if(m_bLoopA) m_rMainWnd.SetABLoopA_Sec(dSeconds);
	else m_rMainWnd.SetABLoopB_Sec(dSeconds);
	accept();
}
//----------------------------------------------------------------------------
