//----------------------------------------------------------------------------
// ABLoopPosWnd.cpp : ABループ位置設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "ABLoopPosWnd.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEdit_ABLoopPos::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) m_rMainWnd.GetABLoopPosWnd().SetPos();
	else if(vk == VK_ESCAPE) m_rMainWnd.GetABLoopPosWnd().Close();
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CABLoopPosWnd::Create(BOOL bLoopA)
{
	m_bLoopA = bLoopA;

	Destroy();

	RegisterClass(_T("ABLoopPosWndCls"));
	if(m_bLoopA)
		m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("ABLoopPosWndCls"),
#if JP
								_T("ABループ(A)位置の設定"),
#else // JP
								_T("AB Loop(A) Pos Setting"),
#endif // JP
								WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
								GetModuleHandle(NULL), this);
	else
		m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("ABLoopPosWndCls"),
#if JP
								_T("ABループ(B)位置の設定"),
#else // JP
								_T("AB Loop(B) Pos Setting"),
#endif // JP
								WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
								GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CABLoopPosWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		SetPos();
		break;
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CABLoopPosWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(160, 60, FALSE);

	// 不要なシステムメニューを削除
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // セパレータ

	EnableWindow(m_rMainWnd, FALSE);

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	if(!m_edit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 12, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(10, 10);
	m_edit.SetText(_T("88:88:88:88.888"));
	m_edit.SetSizeToTextSize();
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
	m_edit.SetText(strTime.c_str());
	m_edit.Show(SW_SHOW);

	// OKボタンの作成
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(90, 20);
	POINT pt;
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_OkButton.SetPos(GetClientWidth() - 10 - m_OkButton.GetWidth(), pt.y + 20);

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	SetFocus(m_edit);
	PostMessage(m_edit, WM_LBUTTONUP, 0, 0);
	PostMessage(m_edit, EM_SETSEL, 0, -1);

	Show(SW_SHOW);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow(m_hWnd);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CABLoopPosWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// 位置の設定
//----------------------------------------------------------------------------
void CABLoopPosWnd::SetPos()
{
	tstring strTime = m_edit.GetText();
	tstring strInt = _T("");
	tstring strDecimals = _T("0");
	int nDecimalPos = 0;
	if((nDecimalPos = strTime.find(_T("."), 0)) != tstring::npos) {
		strInt = strTime.substr(0, nDecimalPos);
		strDecimals += strTime.substr(nDecimalPos,
									 strTime.length() - nDecimalPos);
	}
	else strInt = strTime;

	unsigned int n = 0;
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
	Close();
}
//----------------------------------------------------------------------------
