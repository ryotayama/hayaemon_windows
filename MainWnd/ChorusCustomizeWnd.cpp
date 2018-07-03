//----------------------------------------------------------------------------
// ChorusCustomizeWnd.cpp : コーラスのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "ChorusCustomizeWnd.h"
#include "Sound.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CChorusCustomizeWnd::CChorusCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_wetDryMixEdit(*this),
	  m_depthEdit(*this), m_feedbackEdit(*this), m_frequencyEdit(*this),
	  m_waveformEdit(*this), m_delayEdit(*this), m_OkButton(*this),
	  m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CChorusCustomizeWnd::~CChorusCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CChorusCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("ChorusCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("ChorusCustomizeWndCls"),
#if JP
							_T("コーラスのカスタマイズ"),
#else // JP
							_T("Customize Chorus"),
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
void CChorusCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_wetDryMixEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_depthEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_feedbackEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_frequencyEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_waveformEdit);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_delayEdit);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 7;
			break;
		case 7:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 8;
			break;
		case 8:
			SetFocus((HWND)m_wetDryMixEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 8;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 8;
			break;
		case 2:
			SetFocus((HWND)m_wetDryMixEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_depthEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_feedbackEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_frequencyEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_waveformEdit);
			m_nFocus = 5;
			break;
		case 7:
			SetFocus((HWND)m_delayEdit);
			m_nFocus = 6;
			break;
		case 8:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 7;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if( hwndCtl == m_wetDryMixEdit || hwndCtl == m_depthEdit ||
		hwndCtl == m_feedbackEdit || hwndCtl == m_frequencyEdit ||
		hwndCtl == m_waveformEdit || hwndCtl == m_delayEdit)
	{
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double dMin;
		double dMax;
		int nNewFocus;
		if(hwndCtl == m_wetDryMixEdit) {
			rEdit = &m_wetDryMixEdit;
			rUd = &m_wetDryMixUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_depthEdit) {
			rEdit = &m_depthEdit;
			rUd = &m_depthUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_feedbackEdit) {
			rEdit = &m_feedbackEdit;
			rUd = &m_feedbackUd;
			dMin = -99.0;
			dMax = 99.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_frequencyEdit) {
			rEdit = &m_frequencyEdit;
			rUd = &m_frequencyUd;
			dMin = 0.0;
			dMax = 10.0;
			nNewFocus = 4;
		}
		else if(hwndCtl == m_waveformEdit) {
			rEdit = &m_waveformEdit;
			rUd = &m_waveformUd;
			dMin = 0.0;
			dMax = 1.0;
			nNewFocus = 5;
		}
		else if(hwndCtl == m_delayEdit) {
			rEdit = &m_delayEdit;
			rUd = &m_delayUd;
			dMin = 0.0;
			dMax = 20.0;
			nNewFocus = 6;
		}

		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			m_nFocus = nNewFocus;
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			if(dMin <= n && n <= dMax) {
				if( hwndCtl == m_waveformEdit)
					SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
				else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			TCHAR buf[255];
			if(n < dMin) n = dMin;
			else if(n > dMax) n = dMax;
			if( hwndCtl == m_waveformEdit)
				_stprintf_s(buf, _T("%d"), (int)n);
			else _stprintf_s(buf, _T("%4.3f"), n);
			rEdit->SetText(buf);
			if( hwndCtl == m_waveformEdit)
				SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
			else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
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
void CChorusCustomizeWnd::OnOkButtonClicked()
{
	float fWetDryMix = (float)_tstof(m_wetDryMixEdit.GetText().c_str());
	float fDepth = (float)_tstof(m_depthEdit.GetText().c_str());
	float fFeedback = (float)_tstof(m_feedbackEdit.GetText().c_str());
	float fFrequency = (float)_tstof(m_frequencyEdit.GetText().c_str());
	int lWaveForm = _tstoi(m_waveformEdit.GetText().c_str());
	float fDelay = (float)_tstof(m_delayEdit.GetText().c_str());

	m_rMainWnd.GetMenu().SetChorus(fWetDryMix, fDepth, fFeedback, fFrequency,
		lWaveForm, fDelay, BASS_DX8_PHASE_90, ID_CHORUS_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnReturnKeyPressed()
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
		case 7:
			OnOkButtonClicked();
			break;
		case 8:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnSpaceKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 7:
			OnOkButtonClicked();
			break;
		case 8:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CChorusCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_CHORUS bdc;
	BOOL bChorus = m_rMainWnd.GetSound().GetChorus(&bdc);
	float fWetDryMix = bChorus ? bdc.fWetDryMix : 50.0f;
	float fDepth = bChorus ? bdc.fDepth : 10.0f;
	float fFeedback = bChorus ? bdc.fFeedback : 25.0f;
	float fFrequency = bChorus ? bdc.fFrequency : 1.1f;
	int lWaveForm = bChorus ? bdc.lWaveform : 1;
	float fDelay = bChorus ? bdc.fDelay : 16.0f;

	TCHAR chWetDryMix[255], chDepth[255], chFeedback[255], chFrequency[255],
		  chWaveForm[255], chDelay[255];
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chDepth, _T("%4.3f"), fDepth);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chFrequency, _T("%4.3f"), fFrequency);
	_stprintf_s(chWaveForm, _T("%d"), lWaveForm);
	_stprintf_s(chDelay, _T("%4.3f"), fDelay);

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

	if(!m_wetDryMixLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_wetDryMixLabel.SetParent(m_hWnd);
	m_wetDryMixLabel.SetFont(m_font, TRUE);
	m_wetDryMixLabel.SetText(_T("WET DRY MIX: "));
	m_wetDryMixLabel.SetSizeToTextSize();
	m_wetDryMixLabel.Show(SW_SHOW);

	if(!m_wetDryMixEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_wetDryMixEdit, EM_SETLIMITTEXT, 7, 0);
	m_wetDryMixEdit.SetStyle(m_wetDryMixEdit.GetStyle() | ES_RIGHT);
	m_wetDryMixEdit.SetFont(m_font, TRUE);
	m_wetDryMixEdit.SetText(_T("2000.000"));
	m_wetDryMixEdit.SetSizeToTextSize();
	m_wetDryMixEdit.SetText(chWetDryMix);
	m_wetDryMixEdit.Show(SW_SHOW);

	if(!m_wetDryMixUd.Create(m_hWnd, m_wetDryMixEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_wetDryMixUd, UDM_SETRANGE32, 0, 100000);
	SendMessage(m_wetDryMixUd, UDM_SETPOS32, 0, (LONG)(fWetDryMix * 1000));
	m_wetDryMixUd.Show(SW_SHOW);
	m_wetDryMixEdit.SetSize(m_wetDryMixEdit.GetWidth()
		+ m_wetDryMixUd.GetWidth(), m_wetDryMixEdit.GetHeight());

	if(!m_depthLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_depthLabel.SetParent(m_hWnd);
	m_depthLabel.SetFont(m_font, TRUE);
	m_depthLabel.SetText(_T("DEPTH:"));
	m_depthLabel.SetSizeToTextSize();
	m_depthLabel.Show(SW_SHOW);

	if(!m_depthEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_depthEdit, EM_SETLIMITTEXT, 7, 0);
	m_depthEdit.SetStyle(m_depthEdit.GetStyle() | ES_RIGHT);
	m_depthEdit.SetFont(m_font, TRUE);
	m_depthEdit.SetText(_T("2000.000"));
	m_depthEdit.SetSizeToTextSize();
	m_depthEdit.SetText(chDepth);
	m_depthEdit.Show(SW_SHOW);

	if(!m_depthUd.Create(m_hWnd, m_depthEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_depthUd, UDM_SETRANGE32, 0, 100000);
	SendMessage(m_depthUd, UDM_SETPOS32, 0, (LONG)(fDepth * 1000));
	m_depthUd.Show(SW_SHOW);
	m_depthEdit.SetSize(m_depthEdit.GetWidth()
		+ m_depthUd.GetWidth(), m_depthEdit.GetHeight());

	if(!m_feedbackLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_feedbackLabel.SetParent(m_hWnd);
	m_feedbackLabel.SetFont(m_font, TRUE);
	m_feedbackLabel.SetText(_T("FEEDBACK:"));
	m_feedbackLabel.SetSizeToTextSize();
	m_feedbackLabel.Show(SW_SHOW);

	if(!m_feedbackEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_feedbackEdit, EM_SETLIMITTEXT, 7, 0);
	m_feedbackEdit.SetStyle(m_feedbackEdit.GetStyle() | ES_RIGHT);
	m_feedbackEdit.SetFont(m_font, TRUE);
	m_feedbackEdit.SetText(_T("2000.000"));
	m_feedbackEdit.SetSizeToTextSize();
	m_feedbackEdit.SetText(chFeedback);
	m_feedbackEdit.Show(SW_SHOW);

	if(!m_feedbackUd.Create(m_hWnd, m_feedbackEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_feedbackUd, UDM_SETRANGE32, -99000, 99000);
	SendMessage(m_feedbackUd, UDM_SETPOS32, 0, (LONG)(fFeedback * 1000));
	m_feedbackUd.Show(SW_SHOW);
	m_feedbackEdit.SetSize(m_feedbackEdit.GetWidth()
		+ m_feedbackUd.GetWidth(), m_feedbackEdit.GetHeight());

	if(!m_frequencyLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_frequencyLabel.SetParent(m_hWnd);
	m_frequencyLabel.SetFont(m_font, TRUE);
	m_frequencyLabel.SetText(_T("FREQUENCY:"));
	m_frequencyLabel.SetSizeToTextSize();
	m_frequencyLabel.Show(SW_SHOW);

	if(!m_frequencyEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_frequencyEdit, EM_SETLIMITTEXT, 6, 0);
	m_frequencyEdit.SetStyle(m_frequencyEdit.GetStyle() | ES_RIGHT);
	m_frequencyEdit.SetFont(m_font, TRUE);
	m_frequencyEdit.SetText(_T("2000.000"));
	m_frequencyEdit.SetSizeToTextSize();
	m_frequencyEdit.SetText(chFrequency);
	m_frequencyEdit.Show(SW_SHOW);

	if(!m_frequencyUd.Create(m_hWnd, m_frequencyEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_frequencyUd, UDM_SETRANGE32, 0, 10000);
	SendMessage(m_frequencyUd, UDM_SETPOS32, 0, (LONG)(fFrequency * 1000));
	m_frequencyUd.Show(SW_SHOW);
	m_frequencyEdit.SetSize(m_frequencyEdit.GetWidth()
		+ m_frequencyUd.GetWidth(), m_frequencyEdit.GetHeight());

	if(!m_waveformLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_waveformLabel.SetParent(m_hWnd);
	m_waveformLabel.SetFont(m_font, TRUE);
	m_waveformLabel.SetText(_T("WAVEFORM:"));
	m_waveformLabel.SetSizeToTextSize();
	m_waveformLabel.Show(SW_SHOW);

	if(!m_waveformEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_waveformEdit, EM_SETLIMITTEXT, 1, 0);
	m_waveformEdit.SetStyle(m_waveformEdit.GetStyle() | ES_RIGHT);
	m_waveformEdit.SetFont(m_font, TRUE);
	m_waveformEdit.SetText(_T("2000.000"));
	m_waveformEdit.SetSizeToTextSize();
	m_waveformEdit.SetText(chWaveForm);
	m_waveformEdit.Show(SW_SHOW);

	if(!m_waveformUd.Create(m_hWnd, m_waveformEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_waveformUd, UDM_SETRANGE32, 0, 1);
	SendMessage(m_waveformUd, UDM_SETPOS32, 0, lWaveForm);
	m_waveformUd.Show(SW_SHOW);
	m_waveformEdit.SetSize(m_waveformEdit.GetWidth()
		+ m_waveformUd.GetWidth(), m_waveformEdit.GetHeight());

	if(!m_delayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_delayLabel.SetParent(m_hWnd);
	m_delayLabel.SetFont(m_font, TRUE);
	m_delayLabel.SetText(_T("DELAY:"));
	m_delayLabel.SetSizeToTextSize();
	m_delayLabel.Show(SW_SHOW);

	if(!m_delayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_delayEdit, EM_SETLIMITTEXT, 6, 0);
	m_delayEdit.SetStyle(m_delayEdit.GetStyle() | ES_RIGHT);
	m_delayEdit.SetFont(m_font, TRUE);
	m_delayEdit.SetText(_T("2000.000"));
	m_delayEdit.SetSizeToTextSize();
	m_delayEdit.SetText(chDelay);
	m_delayEdit.Show(SW_SHOW);

	if(!m_delayUd.Create(m_hWnd, m_delayEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_delayUd, UDM_SETRANGE32, 0, 20000);
	SendMessage(m_delayUd, UDM_SETPOS32, 0, (LONG)(fDelay * 1000));
	m_delayUd.Show(SW_SHOW);
	m_delayEdit.SetSize(m_delayEdit.GetWidth()
		+ m_delayUd.GetWidth(), m_delayEdit.GetHeight());

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
	m_wetDryMixLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_wetDryMixEdit.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixEdit.GetWidth();
	m_wetDryMixUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_wetDryMixEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_depthLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_depthEdit.SetPos(nLeft, nTop);
	nLeft += m_depthEdit.GetWidth();
	m_depthUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_depthEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_feedbackLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_feedbackEdit.SetPos(nLeft, nTop);
	nLeft += m_feedbackEdit.GetWidth();
	m_feedbackUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_feedbackEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_frequencyLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_frequencyEdit.SetPos(nLeft, nTop);
	nLeft += m_frequencyEdit.GetWidth();
	m_frequencyUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_frequencyEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_waveformLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_waveformEdit.SetPos(nLeft, nTop);
	nLeft += m_waveformEdit.GetWidth();
	m_waveformUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_waveformEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_delayLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_delayEdit.SetPos(nLeft, nTop);
	nLeft += m_delayEdit.GetWidth();
	m_delayUd.SetPos(nLeft, nTop);

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nLeft;
	int nCancelButtonTop = nTop + m_delayEdit.GetHeight()
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
void CChorusCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CChorusCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0)
			SetPreviousFocus();
		else
			SetNextFocus();
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
LRESULT CChorusCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if( pnmhdr->hwndFrom == m_wetDryMixUd ||
			pnmhdr->hwndFrom == m_depthUd ||
			pnmhdr->hwndFrom == m_feedbackUd ||
			pnmhdr->hwndFrom == m_frequencyUd ||
			pnmhdr->hwndFrom == m_waveformUd ||
			pnmhdr->hwndFrom == m_delayUd)
		{
			CEditExt * rEdit;
			CUpDownCtrl * rUd;
			double dMin;
			double dMax;
			if(pnmhdr->hwndFrom == m_wetDryMixUd) {
				rEdit = &m_wetDryMixEdit;
				rUd = &m_wetDryMixUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_depthUd) {
				rEdit = &m_depthEdit;
				rUd = &m_depthUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_feedbackUd) {
				rEdit = &m_feedbackEdit;
				rUd = &m_feedbackUd;
				dMin = -99.0;
				dMax = 99.0;
			}
			else if(pnmhdr->hwndFrom == m_frequencyUd) {
				rEdit = &m_frequencyEdit;
				rUd = &m_frequencyUd;
				dMin = 0.0;
				dMax = 10.0;
			}
			else if(pnmhdr->hwndFrom == m_waveformUd) {
				rEdit = &m_waveformEdit;
				rUd = &m_waveformUd;
				dMin = 0.0;
				dMax = 1.0;
			}
			else if(pnmhdr->hwndFrom == m_delayUd) {
				rEdit = &m_delayEdit;
				rUd = &m_delayUd;
				dMin = 0.0;
				dMax = 20.0;
			}

			tstring str = rEdit->GetText();
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			double d = _ttof(str.c_str());
			BOOL bInt = FALSE;
			if(pnmhdr->hwndFrom == m_waveformUd)
				bInt = TRUE;
			if(bInt) {
				if(lpnmud->iDelta > 0) d += 1.0;
				else d -= 1.0;
			}
			else {
				if(lpnmud->iDelta > 0) d += 0.001;
				else d -= 0.001;
			}
			if(dMin <= d && d <= dMax) {
				TCHAR buf[255];
				if(bInt) _stprintf_s(buf, _T("%d"), (int)d);
				else _stprintf_s(buf, _T("%4.3f"), d);
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
