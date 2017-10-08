//----------------------------------------------------------------------------
// DecFreqWnd_MainWnd.cpp : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "DecFreqWnd_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDecFreqWnd_MainWnd::CDecFreqWnd_MainWnd(CApp & app,
												   CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(app, mainWnd)
{
#if JP
	strLabel = _T("再生周波数を");
	strLabel2 = _T("下げる");
#else // JP
	strLabel = _T("Turn down frequency");
#endif // JP
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CDecFreqWnd_MainWnd::~CDecFreqWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CDecFreqWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("DecFreqWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("DecFreqWndCls"),
#if JP
							_T("だんだん遅くする"),
#else // JP
							_T("Decrease frequency"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	nFocus = 0;

	return TRUE;
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CDecFreqWnd_MainWnd::OnOkButtonClicked()
{
	if(SendMessage(m_secondRadioButton, BM_GETCHECK, 0, 0)) {
		double nSecond = _ttof(m_edit.GetText().c_str());
		double nDecFreq = _ttof(m_edit2.GetText().c_str());
		m_rMainWnd.SetDecFreq(nSecond, nDecFreq);
	}
	else {
		double nDecFreq = _ttof(m_edit3.GetText().c_str());
		m_rMainWnd.SetDecFreq(nDecFreq);
	}
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CDecFreqWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetDecFreq(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CDecFreqWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetDecFreq(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
