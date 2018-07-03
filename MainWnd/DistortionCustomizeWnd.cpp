//----------------------------------------------------------------------------
// DistortionCustomizeWnd.cpp : ディストーションカスタマイズ用ウィンドウの管理
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "DistortionCustomizeWnd.h"
#include "Sound.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CDistortionCustomizeWnd::CDistortionCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_gainEdit(*this),
	  m_edgeEdit(*this), m_postEQCenterFrequencyEdit(*this),
	  m_postEQBandwidthEdit(*this), m_preLowpassCutoffEdit(*this),
	  m_OkButton(*this), m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CDistortionCustomizeWnd::~CDistortionCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CDistortionCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("DistortionCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("DistortionCustomizeWndCls"),
#if JP
							_T("ディストーションのカスタマイズ"),
#else // JP
							_T("Customize Distortion"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// 次のコントロールにフォーカス
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_edgeEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_postEQCenterFrequencyEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_postEQBandwidthEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_preLowpassCutoffEdit);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 7;
			break;
		case 7:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 7;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 7;
			break;
		case 2:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_edgeEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_postEQCenterFrequencyEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_postEQBandwidthEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_preLowpassCutoffEdit);
			m_nFocus = 5;
			break;
		case 7:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 6;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if( hwndCtl == m_gainEdit || hwndCtl == m_edgeEdit ||
		hwndCtl == m_postEQCenterFrequencyEdit ||
		hwndCtl == m_postEQBandwidthEdit ||
		hwndCtl == m_preLowpassCutoffEdit)
	{
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double dMin;
		double dMax;
		int nNewFocus;
		if(hwndCtl == m_gainEdit) {
			rEdit = &m_gainEdit;
			rUd = &m_gainUd;
			dMin = -60.0;
			dMax = 0.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_edgeEdit) {
			rEdit = &m_edgeEdit;
			rUd = &m_edgeUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_postEQCenterFrequencyEdit) {
			rEdit = &m_postEQCenterFrequencyEdit;
			rUd = &m_postEQCenterFrequencyUd;
			dMin = 100.0;
			dMax = 8000.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_postEQBandwidthEdit) {
			rEdit = &m_postEQBandwidthEdit;
			rUd = &m_postEQBandwidthUd;
			dMin = 100.0;
			dMax = 8000.0;
			nNewFocus = 4;
		}
		else if(hwndCtl == m_preLowpassCutoffEdit) {
			rEdit = &m_preLowpassCutoffEdit;
			rUd = &m_preLowpassCutoffUd;
			dMin = 100.0;
			dMax = 8000.0;
			nNewFocus = 5;
		}

		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			m_nFocus = nNewFocus;
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			if(dMin <= n && n <= dMax)
				SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			TCHAR buf[255];
			if(n < dMin) n = dMin;
			else if(n > dMax) n = dMax;
			_stprintf_s(buf, _T("%4.3f"), n);
			rEdit->SetText(buf);
			SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
		}
	}

	switch(id)
	{
	case ID_OK:
		OnOkButtonClicked();
		break;
	case ID_CANCEL:
		OnCancelButtonClicked();
		break;
	}
	CFrameWnd::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnOkButtonClicked()
{
	float fGain = (float)_tstof(m_gainEdit.GetText().c_str());
	float fEdge = (float)_tstof(m_edgeEdit.GetText().c_str());
	float fPostEQCenterFrequency =
		(float)_tstof(m_postEQCenterFrequencyEdit.GetText().c_str());
	float fPostEQBandwidth =
		(float)_tstof(m_postEQBandwidthEdit.GetText().c_str());
	float fPreLowpassCutoff =
		(float)_tstof(m_preLowpassCutoffEdit.GetText().c_str());

	m_rMainWnd.GetMenu().SetDistortion(fGain, fEdge, fPostEQCenterFrequency,
		fPostEQBandwidth, fPreLowpassCutoff, ID_DISTORTION_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnReturnKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			OnOkButtonClicked();
			break;
		case 7:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnSpaceKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 6:
			OnOkButtonClicked();
			break;
		case 7:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CDistortionCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_DISTORTION bdd;
	BOOL bDistortion = m_rMainWnd.GetSound().GetDistortion(&bdd);
	float fGain = bDistortion ? bdd.fGain : -18.0f;
	float fEdge = bDistortion ? bdd.fEdge : 15.0f;
	float fPostEQCenterFrequency =
		bDistortion ? bdd.fPostEQCenterFrequency : 2400.0f;
	float fPostEQBandwidth = bDistortion ? bdd.fPostEQBandwidth : 2400.0f;
	float fPreLowpassCutoff = bDistortion ? bdd.fPreLowpassCutoff : 8000.0f;

	TCHAR chGain[255], chEdge[255], chPostEQCenterFrequency[255],
		  chPostEQBandwidth[255], chPreLowpassCutoff[255];
	_stprintf_s(chGain, _T("%4.3f"), fGain);
	_stprintf_s(chEdge, _T("%4.3f"), fEdge);
	_stprintf_s(chPostEQCenterFrequency, _T("%4.3f"), fPostEQCenterFrequency);
	_stprintf_s(chPostEQBandwidth, _T("%4.3f"), fPostEQBandwidth);
	_stprintf_s(chPreLowpassCutoff, _T("%4.3f"), fPreLowpassCutoff);

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

	if(!m_gainLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_gainLabel.SetParent(m_hWnd);
	m_gainLabel.SetFont(m_font, TRUE);
	m_gainLabel.SetText(_T("GAIN: "));
	m_gainLabel.SetSizeToTextSize();
	m_gainLabel.Show(SW_SHOW);

	if(!m_gainEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_gainEdit, EM_SETLIMITTEXT, 7, 0);
	m_gainEdit.SetStyle(m_gainEdit.GetStyle() | ES_RIGHT);
	m_gainEdit.SetFont(m_font, TRUE);
	m_gainEdit.SetText(_T("2000.000"));
	m_gainEdit.SetSizeToTextSize();
	m_gainEdit.SetText(chGain);
	m_gainEdit.Show(SW_SHOW);

	if(!m_gainUd.Create(m_hWnd, m_gainEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_gainUd, UDM_SETRANGE32, -60000, 0);
	SendMessage(m_gainUd, UDM_SETPOS32, 0, (LONG)(fGain * 1000));
	m_gainUd.Show(SW_SHOW);
	m_gainEdit.SetSize(m_gainEdit.GetWidth()
		+ m_gainUd.GetWidth(), m_gainEdit.GetHeight());

	if(!m_edgeLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_edgeLabel.SetParent(m_hWnd);
	m_edgeLabel.SetFont(m_font, TRUE);
	m_edgeLabel.SetText(_T("EDGE: "));
	m_edgeLabel.SetSizeToTextSize();
	m_edgeLabel.Show(SW_SHOW);

	if(!m_edgeEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edgeEdit, EM_SETLIMITTEXT, 7, 0);
	m_edgeEdit.SetStyle(m_edgeEdit.GetStyle() | ES_RIGHT);
	m_edgeEdit.SetFont(m_font, TRUE);
	m_edgeEdit.SetText(_T("2000.000"));
	m_edgeEdit.SetSizeToTextSize();
	m_edgeEdit.SetText(chEdge);
	m_edgeEdit.Show(SW_SHOW);

	if(!m_edgeUd.Create(m_hWnd, m_edgeEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edgeUd, UDM_SETRANGE32, 0, 100000);
	SendMessage(m_edgeUd, UDM_SETPOS32, 0, (LONG)(fEdge * 1000));
	m_edgeUd.Show(SW_SHOW);
	m_edgeEdit.SetSize(m_edgeEdit.GetWidth()
		+ m_edgeUd.GetWidth(), m_edgeEdit.GetHeight());

	if(!m_postEQCenterFrequencyLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_postEQCenterFrequencyLabel.SetParent(m_hWnd);
	m_postEQCenterFrequencyLabel.SetFont(m_font, TRUE);
	m_postEQCenterFrequencyLabel.SetText(_T("POST EQ CENTER FREQUENCY: "));
	m_postEQCenterFrequencyLabel.SetSizeToTextSize();
	m_postEQCenterFrequencyLabel.Show(SW_SHOW);

	if(!m_postEQCenterFrequencyEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_postEQCenterFrequencyEdit, EM_SETLIMITTEXT, 8, 0);
	m_postEQCenterFrequencyEdit.SetStyle(m_postEQCenterFrequencyEdit.GetStyle() | ES_RIGHT);
	m_postEQCenterFrequencyEdit.SetFont(m_font, TRUE);
	m_postEQCenterFrequencyEdit.SetText(_T("2000.000"));
	m_postEQCenterFrequencyEdit.SetSizeToTextSize();
	m_postEQCenterFrequencyEdit.SetText(chPostEQCenterFrequency);
	m_postEQCenterFrequencyEdit.Show(SW_SHOW);

	if(!m_postEQCenterFrequencyUd.Create(m_hWnd, m_postEQCenterFrequencyEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_postEQCenterFrequencyUd, UDM_SETRANGE32, 100000, 8000000);
	SendMessage(m_postEQCenterFrequencyUd, UDM_SETPOS32, 0,
		(LONG)(fPostEQCenterFrequency * 1000));
	m_postEQCenterFrequencyUd.Show(SW_SHOW);
	m_postEQCenterFrequencyEdit.SetSize(m_postEQCenterFrequencyEdit.GetWidth()
		+ m_postEQCenterFrequencyUd.GetWidth(),
		m_postEQCenterFrequencyEdit.GetHeight());

	if(!m_postEQBandwidthLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_postEQBandwidthLabel.SetParent(m_hWnd);
	m_postEQBandwidthLabel.SetFont(m_font, TRUE);
	m_postEQBandwidthLabel.SetText(_T("POST EQ BANDWIDTH: "));
	m_postEQBandwidthLabel.SetSizeToTextSize();
	m_postEQBandwidthLabel.Show(SW_SHOW);

	if(!m_postEQBandwidthEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_postEQBandwidthEdit, EM_SETLIMITTEXT, 8, 0);
	m_postEQBandwidthEdit.SetStyle(m_postEQBandwidthEdit.GetStyle() | ES_RIGHT);
	m_postEQBandwidthEdit.SetFont(m_font, TRUE);
	m_postEQBandwidthEdit.SetText(_T("2000.000"));
	m_postEQBandwidthEdit.SetSizeToTextSize();
	m_postEQBandwidthEdit.SetText(chPostEQBandwidth);
	m_postEQBandwidthEdit.Show(SW_SHOW);

	if(!m_postEQBandwidthUd.Create(m_hWnd, m_postEQBandwidthEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_postEQBandwidthUd, UDM_SETRANGE32, 100000, 8000000);
	SendMessage(m_postEQBandwidthUd, UDM_SETPOS32, 0, (LONG)(fPostEQBandwidth
		* 1000));
	m_postEQBandwidthUd.Show(SW_SHOW);
	m_postEQBandwidthEdit.SetSize(m_postEQBandwidthEdit.GetWidth()
		+ m_postEQBandwidthUd.GetWidth(), m_postEQBandwidthEdit.GetHeight());

	if(!m_preLowpassCutoffLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_preLowpassCutoffLabel.SetParent(m_hWnd);
	m_preLowpassCutoffLabel.SetFont(m_font, TRUE);
	m_preLowpassCutoffLabel.SetText(_T("PRE LOWPASS CUTOFF: "));
	m_preLowpassCutoffLabel.SetSizeToTextSize();
	m_preLowpassCutoffLabel.Show(SW_SHOW);

	if(!m_preLowpassCutoffEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_preLowpassCutoffEdit, EM_SETLIMITTEXT, 8, 0);
	m_preLowpassCutoffEdit.SetStyle(m_preLowpassCutoffEdit.GetStyle() |
		ES_RIGHT);
	m_preLowpassCutoffEdit.SetFont(m_font, TRUE);
	m_preLowpassCutoffEdit.SetText(_T("2000.000"));
	m_preLowpassCutoffEdit.SetSizeToTextSize();
	m_preLowpassCutoffEdit.SetText(chPreLowpassCutoff);
	m_preLowpassCutoffEdit.Show(SW_SHOW);

	if(!m_preLowpassCutoffUd.Create(m_hWnd, m_preLowpassCutoffEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_preLowpassCutoffUd, UDM_SETRANGE32, 100000, 8000000);
	SendMessage(m_preLowpassCutoffUd, UDM_SETPOS32, 0, (LONG)(fPreLowpassCutoff
		* 1000));
	m_preLowpassCutoffUd.Show(SW_SHOW);
	m_preLowpassCutoffEdit.SetSize(m_preLowpassCutoffEdit.GetWidth()
		+ m_preLowpassCutoffUd.GetWidth(), m_preLowpassCutoffEdit.GetHeight());

	// キャンセルボタンの作成
	if(!m_CancelButton.Create(
#if JP
							  _T("キャンセル"),
#else // JP
							  _T("Cancel"),
#endif // JP
							  m_hWnd, ID_CANCEL)) {
#if JP
		m_rApp.ShowError(_T("キャンセルボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create cancel button."));
#endif // JP
		return FALSE;
	}
	m_CancelButton.SetSize(nButtonWidth, nButtonHeight);

	// OKボタンの作成
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(nButtonWidth, nButtonHeight);

	int nLeft = m_rMainWnd.GetControlOffset() * 2;
	int nTop = m_rMainWnd.GetControlOffset() * 4;
	m_gainLabel.SetPos(nLeft, nTop);
	nLeft += m_postEQCenterFrequencyLabel.GetWidth();
	m_gainEdit.SetPos(nLeft, nTop);
	nLeft += m_gainEdit.GetWidth();
	m_gainUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_gainEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_edgeLabel.SetPos(nLeft, nTop);
	nLeft += m_postEQCenterFrequencyLabel.GetWidth();
	m_edgeEdit.SetPos(nLeft, nTop);
	nLeft += m_edgeEdit.GetWidth();
	m_edgeUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_edgeEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_postEQCenterFrequencyLabel.SetPos(nLeft, nTop);
	nLeft += m_postEQCenterFrequencyLabel.GetWidth();
	m_postEQCenterFrequencyEdit.SetPos(nLeft, nTop);
	nLeft += m_postEQCenterFrequencyEdit.GetWidth();
	m_postEQCenterFrequencyUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_postEQCenterFrequencyEdit.GetHeight()
		+ m_rMainWnd.GetControlOffset();
	m_postEQBandwidthLabel.SetPos(nLeft, nTop);
	nLeft += m_postEQCenterFrequencyLabel.GetWidth();
	m_postEQBandwidthEdit.SetPos(nLeft, nTop);
	nLeft += m_postEQBandwidthEdit.GetWidth();
	m_postEQBandwidthUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_postEQBandwidthEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_preLowpassCutoffLabel.SetPos(nLeft, nTop);
	nLeft += m_postEQCenterFrequencyLabel.GetWidth();
	m_preLowpassCutoffEdit.SetPos(nLeft, nTop);
	nLeft += m_preLowpassCutoffEdit.GetWidth();
	m_preLowpassCutoffUd.SetPos(nLeft, nTop);

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nLeft;
	int nCancelButtonTop = nTop + m_preLowpassCutoffEdit.GetHeight()
						   + m_rMainWnd.GetControlOffset() * 4;
	m_CancelButton.SetPos(nCancelButtonLeft, nCancelButtonTop);
	int nOkButtonLeft = nCancelButtonLeft - m_rMainWnd.GetControlOffset()
						- m_OkButton.GetWidth();
	int nOkButtonTop = nCancelButtonTop;
	m_OkButton.SetPos(nOkButtonLeft, nOkButtonTop);

	// ウィンドウサイズの設定
	int nWidth = nCancelButtonLeft + m_CancelButton.GetWidth()
				 + m_rMainWnd.GetControlOffset() * 2;
	int nHeight = nCancelButtonTop + m_CancelButton.GetHeight()
				  + m_rMainWnd.GetControlOffset() * 2;
	SetClientSize(nWidth, nHeight, FALSE);

	m_nFocus = 0;
	SetNextFocus();

	Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CDistortionCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0) SetPreviousFocus();
		else SetNextFocus();
		break;
	case VK_RETURN:
		OnReturnKeyPressed();
		break;
	case VK_SPACE:
		OnSpaceKeyPressed();
		break;
	case VK_ESCAPE:
		OnEscKeyPressed();
		break;
	}
	CFrameWnd::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 通知が来た
//----------------------------------------------------------------------------
LRESULT CDistortionCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if( pnmhdr->hwndFrom == m_gainUd ||
			pnmhdr->hwndFrom == m_edgeUd ||
			pnmhdr->hwndFrom == m_postEQCenterFrequencyUd ||
			pnmhdr->hwndFrom == m_postEQBandwidthUd ||
			pnmhdr->hwndFrom == m_preLowpassCutoffUd)
		{
			CEditExt * rEdit;
			CUpDownCtrl * rUd;
			double dMin;
			double dMax;
			if(pnmhdr->hwndFrom == m_gainUd) {
				rEdit = &m_gainEdit;
				rUd = &m_gainUd;
				dMin = -60.0;
				dMax = 0.0;
			}
			else if(pnmhdr->hwndFrom == m_edgeUd) {
				rEdit = &m_edgeEdit;
				rUd = &m_edgeUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_postEQCenterFrequencyUd) {
				rEdit = &m_postEQCenterFrequencyEdit;
				rUd = &m_postEQCenterFrequencyUd;
				dMin = 100.0;
				dMax = 8000.0;
			}
			else if(pnmhdr->hwndFrom == m_postEQBandwidthUd) {
				rEdit = &m_postEQBandwidthEdit;
				rUd = &m_postEQBandwidthUd;
				dMin = 100.0;
				dMax = 8000.0;
			}
			else if(pnmhdr->hwndFrom == m_preLowpassCutoffUd) {
				rEdit = &m_preLowpassCutoffEdit;
				rUd = &m_preLowpassCutoffUd;
				dMin = 100.0;
				dMax = 8000.0;
			}

			tstring str = rEdit->GetText();
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			double d = _ttof(str.c_str());
			if(lpnmud->iDelta > 0) d += 0.001;
			else d -= 0.001;
			if(dMin <= d && d <= dMax) {
				TCHAR buf[255];
				_stprintf_s(buf, _T("%4.3f"), d);
				rEdit->SetText(buf);
			}
			PostMessage(*rEdit, WM_LBUTTONUP, 0, 0);
			PostMessage(*rEdit, EM_SETSEL, 0, -1);
			return TRUE;
		}
	}

	return CFrameWnd::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
