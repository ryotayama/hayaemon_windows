//----------------------------------------------------------------------------
// DecSpeedWnd_MainWnd.cpp : だんだん遅くするウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "DecSpeedWnd_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDecSpeedWnd_MainWnd::CDecSpeedWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(app, mainWnd)
{
#if JP
	strLabel2 = _T("下げる");
#else // JP
	strLabel = _T("Turn down speed");
#endif // JP
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CDecSpeedWnd_MainWnd::~CDecSpeedWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CDecSpeedWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("DecSpeedWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("DecSpeedWndCls"),
#if JP
							_T("だんだん遅くする"),
#else // JP
							_T("Decrease speed"),
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
void CDecSpeedWnd_MainWnd::OnOkButtonClicked()
{
	if(SendMessage(m_secondRadioButton, BM_GETCHECK, 0, 0)) {
		double nSecond = _ttof(m_edit.GetText().c_str());
		double nDecSpeed = _ttof(m_edit2.GetText().c_str());
		m_rMainWnd.SetDecSpeed(nSecond, nDecSpeed);
	}
	else {
		double nDecSpeed = _ttof(m_edit3.GetText().c_str());
		m_rMainWnd.SetDecSpeed(nDecSpeed);
	}
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetDecSpeed(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetDecSpeed(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
