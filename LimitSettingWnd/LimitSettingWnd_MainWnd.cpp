//----------------------------------------------------------------------------
// LimitSettingWnd_MainWnd.cpp : タイマー再生用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/FreqSlider_MainWnd.h"
#include "../MainWnd/MainWnd.h"
#include "../MainWnd/PanSlider_MainWnd.h"
#include "../MainWnd/PitchSlider_MainWnd.h"
#include "../MainWnd/SpeedSlider_MainWnd.h"
#include "LimitSettingWnd_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CLimitSettingWnd_MainWnd::CLimitSettingWnd_MainWnd(CApp & app,
												   CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_minSpeedEdit(*this),
	  m_maxSpeedEdit(*this), m_minFreqEdit(*this),
	  m_maxFreqEdit(*this),m_minPitchEdit(*this),
	  m_maxPitchEdit(*this),
	  m_OkButton(*this), m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CLimitSettingWnd_MainWnd::~CLimitSettingWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CLimitSettingWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("LimitSettingWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("LimitSettingWndCls"),
#if JP
							_T("最大値／最小値の設定"),
#else // JP
							_T("Max/Min setting"),
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
void CLimitSettingWnd_MainWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_minSpeedEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_maxSpeedEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_minFreqEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_maxFreqEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_minPitchEdit);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_maxPitchEdit);
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
			SetFocus((HWND)m_minSpeedEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CLimitSettingWnd_MainWnd::SetPreviousFocus()
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
			SetFocus((HWND)m_minSpeedEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_maxSpeedEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_minFreqEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_maxFreqEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_minPitchEdit);
			m_nFocus = 5;
			break;
		case 7:
			SetFocus((HWND)m_maxPitchEdit);
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
void CLimitSettingWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_minSpeedEdit || hwndCtl == m_maxSpeedEdit
		|| hwndCtl == m_minFreqEdit || hwndCtl == m_maxFreqEdit
		|| hwndCtl == m_minPitchEdit || hwndCtl == m_maxPitchEdit) {
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double nMin;
		double nMax;
		int nNewFocus;
		if(hwndCtl == m_minSpeedEdit) {
			rEdit = &m_minSpeedEdit;
			rUd = &m_minSpeedUd;
			nMin = 1.0;
			nMax = 100.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_maxSpeedEdit) {
			rEdit = &m_maxSpeedEdit;
			rUd = &m_maxSpeedUd;
			nMin = 100.0;
			nMax = 5000.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_minFreqEdit) {
			rEdit = &m_minFreqEdit;
			rUd = &m_minFreqUd;
			nMin = 1.0;
			nMax = 100.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_maxFreqEdit) {
			rEdit = &m_maxFreqEdit;
			rUd = &m_maxFreqUd;
			nMin = 100.0;
			nMax = 5000.0;
			nNewFocus = 4;
		}
		else if(hwndCtl == m_minPitchEdit) {
			rEdit = &m_minPitchEdit;
			rUd = &m_minPitchUd;
			nMin = -60.0;
			nMax = 0.0;
			nNewFocus = 5;
		}
		else if(hwndCtl == m_maxPitchEdit) {
			rEdit = &m_maxPitchEdit;
			rUd = &m_maxPitchUd;
			nMin = 0.0;
			nMax = 60.0;
			nNewFocus = 6;
		}

		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			m_nFocus = nNewFocus;
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			double n = 0.0;
			if(hwndCtl == m_minPitchEdit || hwndCtl == m_maxPitchEdit) {
				tstring strText = rEdit->GetText();
#ifdef UNICODE
				if(strText.find(_T("♭")) == 0)
					strText.replace(0, 1, _T("-"));
				else if(strText.find(_T("♯")) == 0)
					strText.replace(0, 1, _T(""));
#else // UNICODE
				if(strText.find(_T("♭")) == 0)
					strText.replace(0, 2, _T("-"));
				else if(strText.find(_T("♯")) == 0)
					strText.replace(0, 2, _T(""));
#endif // UNICODE
				n = (double)_tstof(strText.c_str());
			}
			else
				n = (double)_tstof(rEdit->GetText().c_str());
			if(nMin <= n && n <= nMax) {
				if(hwndCtl == m_maxSpeedEdit || hwndCtl == m_maxFreqEdit )
					SendMessage(*rUd, UDM_SETPOS32, 0,
								(LONG)(n * 10.0) - 20000);
				else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 10.0));
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = 0.0;
			TCHAR buf[255];
			if(hwndCtl == m_minPitchEdit || hwndCtl == m_maxPitchEdit) {
				tstring strText = rEdit->GetText();
#ifdef UNICODE
				if(strText.find(_T("♭")) == 0)
					strText.replace(0, 1, _T("-"));
				else if(strText.find(_T("♯")) == 0)
					strText.replace(0, 1, _T(""));
#else // UNICODE
				if(strText.find(_T("♭")) == 0)
					strText.replace(0, 2, _T("-"));
				else if(strText.find(_T("♯")) == 0)
					strText.replace(0, 2, _T(""));
#endif // UNICODE
				n = (double)_tstof(strText.c_str());
				if(n < nMin) n = nMin;
				else if(n > nMax) n = nMax;
				if(n > 0)
					_stprintf_s(buf, _T("♯%2.1f"), n);
				else if(n < 0)
					_stprintf_s(buf, _T("♭%2.1f"), n * -1);
				else
					_stprintf_s(buf, _T("%2.1f"), n);
			}
			else {
				n = (double)_tstof(rEdit->GetText().c_str());
				if(n < nMin) n = nMin;
				else if(n > nMax) n = nMax;
				_stprintf_s(buf, _T("%4.1f"), n);
			}
			rEdit->SetText(buf);
			if(hwndCtl == m_maxSpeedEdit || hwndCtl == m_maxFreqEdit)
				SendMessage(*rUd, UDM_SETPOS32, 0,
							(LONG)(n * 10.0) - 20000);
			else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 10.0));
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
void CLimitSettingWnd_MainWnd::OnOkButtonClicked()
{
	double dMinSpeed = (double)_tstof(m_minSpeedEdit.GetText().c_str());
	double dMaxSpeed = (double)_tstof(m_maxSpeedEdit.GetText().c_str());
	double dMinFreq =
		(double)_tstof(m_minFreqEdit.GetText().c_str());
	double dMaxFreq =
		(double)_tstof(m_maxFreqEdit.GetText().c_str());
	tstring strText = m_minPitchEdit.GetText();
#ifdef UNICODE
	if(strText.find(_T("♭")) == 0)
		strText.replace(0, 1, _T("-"));
	else if(strText.find(_T("♯")) == 0)
		strText.replace(0, 1, _T(""));
#else // UNICODE
	if(strText.find(_T("♭")) == 0)
		strText.replace(0, 2, _T("-"));
	else if(strText.find(_T("♯")) == 0)
		strText.replace(0, 2, _T(""));
#endif // UNICODE
	double dMinPitch = (double)_tstof(strText.c_str());
	strText = m_maxPitchEdit.GetText();
#ifdef UNICODE
	if(strText.find(_T("♭")) == 0)
		strText.replace(0, 1, _T("-"));
	else if(strText.find(_T("♯")) == 0)
		strText.replace(0, 1, _T(""));
#else // UNICODE
	if(strText.find(_T("♭")) == 0)
		strText.replace(0, 2, _T("-"));
	else if(strText.find(_T("♯")) == 0)
		strText.replace(0, 2, _T(""));
#endif // UNICODE
	double dMaxPitch = (double)_tstof(strText.c_str());
	m_rMainWnd.SetLimit(dMinSpeed, dMaxSpeed, dMinFreq, dMaxFreq,
						dMinPitch, dMaxPitch);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CLimitSettingWnd_MainWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CLimitSettingWnd_MainWnd::OnReturnKeyPressed()
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
void CLimitSettingWnd_MainWnd::OnSpaceKeyPressed()
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
void CLimitSettingWnd_MainWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CLimitSettingWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	int nMinSpeed = (int)(m_rMainWnd.GetSpeedSlider().GetRangeMin() * 10.0
		/ pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit()));
	int nMaxSpeed = (int)(m_rMainWnd.GetSpeedSlider().GetRangeMax() * 10.0
		/ pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit()));
	TCHAR chMinSpeed[255];
	_stprintf_s(chMinSpeed, _T("%4.1f"), nMinSpeed / 10.0);
	TCHAR chMaxSpeed[255];
	_stprintf_s(chMaxSpeed, _T("%4.1f"), nMaxSpeed / 10.0);
	int nMinFreq = (int)(m_rMainWnd.GetFreqSlider().GetRangeMin() * 10.0
		/ pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit()));
	int nMaxFreq = (int)(m_rMainWnd.GetFreqSlider().GetRangeMax() * 10.0
		/ pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit()));
	TCHAR chMinFreq[255];
	_stprintf_s(chMinFreq, _T("%4.1f"), nMinFreq / 10.0);
	TCHAR chMaxFreq[255];
	_stprintf_s(chMaxFreq, _T("%4.1f"), nMaxFreq / 10.0);
	int nMinPitch = (int)(m_rMainWnd.GetPitchSlider().GetRangeMin() * 10.0
		/ pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit()));
	int nMaxPitch = (int)(m_rMainWnd.GetPitchSlider().GetRangeMax() * 10.0
		/ pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit()));
	TCHAR chMinPitch[255];
	if(nMinPitch > 0)
		_stprintf_s(chMinPitch, _T("♯%2.1f"), nMinPitch / 10.0);
	else if(nMinPitch < 0)
		_stprintf_s(chMinPitch, _T("♭%2.1f"), nMinPitch * -1 / 10.0);
	else _stprintf_s(chMinPitch, _T("%2.1f"), nMinPitch / 10.0);
	TCHAR chMaxPitch[255];
	if(nMaxPitch > 0)
		_stprintf_s(chMaxPitch, _T("♯%2.1f"), nMaxPitch / 10.0);
	else if(nMaxPitch < 0)
		_stprintf_s(chMaxPitch, _T("♭%2.1f"), nMaxPitch * -1 / 10.0);
	else _stprintf_s(chMaxPitch, _T("%2.1f"), nMaxPitch / 10.0);

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

	// 再生速度ラベルの作成
	if(!m_speedLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_speedLabel.SetParent(m_hWnd);
	m_speedLabel.SetFont(m_font, TRUE);
#if JP
	m_speedLabel.SetText(_T("再生速度 : "));
#else // JP
	m_speedLabel.SetText(_T("Speed : "));
#endif // JP
	m_speedLabel.SetSizeToTextSize();
	m_speedLabel.Show(SW_SHOW);

	// 再生速度の最小値エディットボックスの作成
	if(!m_minSpeedEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_minSpeedEdit, EM_SETLIMITTEXT, 5, 0);
	m_minSpeedEdit.SetStyle(m_minSpeedEdit.GetStyle() | ES_RIGHT);
	m_minSpeedEdit.SetFont(m_font, TRUE);
	m_minSpeedEdit.SetText(_T("9999.9"));
	m_minSpeedEdit.SetSizeToTextSize();
	m_minSpeedEdit.SetText(chMinSpeed);
	m_minSpeedEdit.Show(SW_SHOW);

	// 再生速度の最小値アップダウンコントロールの作成
	if(!m_minSpeedUd.Create(m_hWnd, m_minSpeedEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_minSpeedUd, UDM_SETRANGE32, 10, 1000);
	SendMessage(m_minSpeedUd, UDM_SETPOS32, 0, nMinSpeed);
	m_minSpeedUd.Show(SW_SHOW);
	m_minSpeedEdit.SetSize(m_minSpeedEdit.GetWidth() + m_minSpeedUd.GetWidth(),
						   m_minSpeedEdit.GetHeight());

	// 再生速度の「% ～」ラベルの作成
	if(!m_speedLabel2.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label"));
#endif // JP
		return FALSE;
	}
	m_speedLabel2.SetParent(m_hWnd);
	m_speedLabel2.SetFont(m_font, TRUE);
#if JP
	m_speedLabel2.SetText(_T("%　～　"));
#else // JP
	m_speedLabel2.SetText(_T("% - "));
#endif // JP
	m_speedLabel2.SetSizeToTextSize();
	m_speedLabel2.Show(SW_SHOW);

	// 再生速度の最大値エディットボックスの作成
	if(!m_maxSpeedEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_maxSpeedEdit, EM_SETLIMITTEXT, 6, 0);
	m_maxSpeedEdit.SetStyle(m_maxSpeedEdit.GetStyle() | ES_RIGHT);
	m_maxSpeedEdit.SetFont(m_font, TRUE);
	m_maxSpeedEdit.SetText(_T("9999.9"));
	m_maxSpeedEdit.SetSizeToTextSize();
	m_maxSpeedEdit.SetText(chMaxSpeed);
	m_maxSpeedEdit.Show(SW_SHOW);

	// 再生速度の最大値アップダウンコントロールの作成
	if(!m_maxSpeedUd.Create(m_hWnd, m_maxSpeedEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_maxSpeedUd, UDM_SETRANGE32, -19000, 30000);
	SendMessage(m_maxSpeedUd, UDM_SETPOS32, 0, nMaxSpeed - 20000);
	m_maxSpeedUd.Show(SW_SHOW);
	m_maxSpeedEdit.SetSize(m_maxSpeedEdit.GetWidth() + m_maxSpeedUd.GetWidth(),
						   m_maxSpeedEdit.GetHeight());

	// 再生速度の「%」ラベルの作成
	if(!m_speedLabel3.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_speedLabel3.SetParent(m_hWnd);
	m_speedLabel3.SetFont(m_font, TRUE);
	m_speedLabel3.SetText(_T("%"));
	m_speedLabel3.SetSizeToTextSize();
	m_speedLabel3.Show(SW_SHOW);

	// 再生周波数ラベルの作成
	if(!m_freqLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_freqLabel.SetParent(m_hWnd);
	m_freqLabel.SetFont(m_font, TRUE);
#if JP
	m_freqLabel.SetText(_T("再生周波数 : "));
#else // JP
	m_freqLabel.SetText(_T("Frequency : "));
#endif // JP
	m_freqLabel.SetSizeToTextSize();
	m_freqLabel.Show(SW_SHOW);

	// 再生周波数の最小値エディットボックスの作成
	if(!m_minFreqEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_minFreqEdit, EM_SETLIMITTEXT, 5, 0);
	m_minFreqEdit.SetStyle(m_minFreqEdit.GetStyle() | ES_RIGHT);
	m_minFreqEdit.SetFont(m_font, TRUE);
	m_minFreqEdit.SetText(_T("9999.9"));
	m_minFreqEdit.SetSizeToTextSize();
	m_minFreqEdit.SetText(chMinFreq);
	m_minFreqEdit.Show(SW_SHOW);

	// 再生周波数の最小値アップダウンコントロールの作成
	if(!m_minFreqUd.Create(m_hWnd, m_minFreqEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_minFreqUd, UDM_SETRANGE32, 10, 1000);
	SendMessage(m_minFreqUd, UDM_SETPOS32, 0, nMinFreq);
	m_minFreqUd.Show(SW_SHOW);
	m_minFreqEdit.SetSize(m_minFreqEdit.GetWidth()
							   + m_minFreqUd.GetWidth(),
							   m_minFreqEdit.GetHeight());

	// 再生周波数「% ～」ラベルの作成
	if(!m_freqLabel2.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_freqLabel2.SetParent(m_hWnd);
	m_freqLabel2.SetFont(m_font, TRUE);
#if JP
	m_freqLabel2.SetText(_T("%　～　"));
#else // JP
	m_freqLabel2.SetText(_T("% - "));
#endif // JP
	m_freqLabel2.SetSizeToTextSize();
	m_freqLabel2.Show(SW_SHOW);

	// 再生周波数の最大値エディットボックスの作成
	if(!m_maxFreqEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_maxFreqEdit, EM_SETLIMITTEXT, 6, 0);
	m_maxFreqEdit.SetStyle(m_maxFreqEdit.GetStyle() | ES_RIGHT);
	m_maxFreqEdit.SetFont(m_font, TRUE);
	m_maxFreqEdit.SetText(_T("9999.9"));
	m_maxFreqEdit.SetSizeToTextSize();
	m_maxFreqEdit.SetText(chMaxFreq);
	m_maxFreqEdit.Show(SW_SHOW);

	// 再生周波数の最大値アップダウンコントロールの作成
	if(!m_maxFreqUd.Create(m_hWnd, m_maxFreqEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_maxFreqUd, UDM_SETRANGE32, -19000, 30000);
	SendMessage(m_maxFreqUd, UDM_SETPOS32, 0, nMaxFreq - 20000);
	m_maxFreqUd.Show(SW_SHOW);
	m_maxFreqEdit.SetSize(m_maxFreqEdit.GetWidth()
		+ m_maxFreqUd.GetWidth(), m_maxFreqEdit.GetHeight());

	// 再生周波数「%」ラベルの作成
	if(!m_freqLabel3.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_freqLabel3.SetParent(m_hWnd);
	m_freqLabel3.SetFont(m_font, TRUE);
	m_freqLabel3.SetText(_T("%"));
	m_freqLabel3.SetSizeToTextSize();
	m_freqLabel3.Show(SW_SHOW);

	// 音程ラベルの作成
	if(!m_pitchLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_pitchLabel.SetParent(m_hWnd);
	m_pitchLabel.SetFont(m_font, TRUE);
#if JP
	m_pitchLabel.SetText(_T("音程 : "));
#else // JP
	m_pitchLabel.SetText(_T("Pitch : "));
#endif // JP
	m_pitchLabel.SetSizeToTextSize();
	m_pitchLabel.Show(SW_SHOW);

	// 音程の最小値エディットボックスの作成
	if(!m_minPitchEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_minPitchEdit, EM_SETLIMITTEXT, 5, 0);
	m_minPitchEdit.SetStyle(m_minPitchEdit.GetStyle() | ES_RIGHT);
	m_minPitchEdit.SetFont(m_font, TRUE);
	m_minPitchEdit.SetText(_T("♭88.8"));
	m_minPitchEdit.SetSizeToTextSize();
	m_minPitchEdit.SetText(chMinPitch);
	m_minPitchEdit.Show(SW_SHOW);

	// 音程の最小値アップダウンコントロールの作成
	if(!m_minPitchUd.Create(m_hWnd, m_minPitchEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_minPitchUd, UDM_SETRANGE32, -600, 0);
	SendMessage(m_minPitchUd, UDM_SETPOS32, 0, nMinPitch);
	m_minPitchUd.Show(SW_SHOW);
	m_minPitchEdit.SetSize(m_minPitchEdit.GetWidth()
						   + m_minPitchUd.GetWidth(),
						   m_minPitchEdit.GetHeight());

	// 音程「～」ラベルの作成
	if(!m_pitchLabel2.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_pitchLabel2.SetParent(m_hWnd);
	m_pitchLabel2.SetFont(m_font, TRUE);
#if JP
	m_pitchLabel2.SetText(_T(" 　～　"));
#else // JP
	m_pitchLabel2.SetText(_T("  - "));
#endif // JP

	m_pitchLabel2.SetSizeToTextSize();
	m_pitchLabel2.Show(SW_SHOW);

	// 音程の最大値エディットボックスの作成
	if(!m_maxPitchEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_maxPitchEdit, EM_SETLIMITTEXT, 6, 0);
	m_maxPitchEdit.SetStyle(m_maxPitchEdit.GetStyle() | ES_RIGHT);
	m_maxPitchEdit.SetFont(m_font, TRUE);
	m_maxPitchEdit.SetText(_T("♯88.8"));
	m_maxPitchEdit.SetSizeToTextSize();
	m_maxPitchEdit.SetText(chMaxPitch);
	m_maxPitchEdit.Show(SW_SHOW);

	// 音程の最大値アップダウンコントロールの作成
	if(!m_maxPitchUd.Create(m_hWnd, m_maxPitchEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_maxPitchUd, UDM_SETRANGE32, 0, 600);
	SendMessage(m_maxPitchUd, UDM_SETPOS32, 0, nMaxPitch);
	m_maxPitchUd.Show(SW_SHOW);
	m_maxPitchEdit.SetSize(m_maxPitchEdit.GetWidth()
						   + m_maxPitchUd.GetWidth(),
						   m_maxPitchEdit.GetHeight());

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

	// 再生速度系コントロールの位置設定
	int nSpeedLeft = m_rMainWnd.GetControlOffset() * 2;
	int nSpeedTop = m_rMainWnd.GetControlOffset() * 4;
	m_speedLabel.SetPos(nSpeedLeft, nSpeedTop);
	nSpeedLeft += m_freqLabel.GetWidth();
	m_minSpeedEdit.SetPos(nSpeedLeft, nSpeedTop);
	nSpeedLeft += m_minSpeedEdit.GetWidth();
	m_minSpeedUd.SetPos(nSpeedLeft, nSpeedTop);
	nSpeedLeft += m_minSpeedUd.GetWidth() + m_rMainWnd.GetControlOffset();
	m_speedLabel2.SetPos(nSpeedLeft, nSpeedTop);
	nSpeedLeft += m_speedLabel2.GetWidth();
	m_maxSpeedEdit.SetPos(nSpeedLeft, nSpeedTop);
	nSpeedLeft += m_maxSpeedEdit.GetWidth();
	m_maxSpeedUd.SetPos(nSpeedLeft, nSpeedTop);
	nSpeedLeft += m_maxSpeedUd.GetWidth() + m_rMainWnd.GetControlOffset();
	m_speedLabel3.SetPos(nSpeedLeft, nSpeedTop);

	// 再生周波数系コントロールの位置設定
	int nFreqLeft = m_rMainWnd.GetControlOffset() * 2;
	int nFreqTop = nSpeedTop + m_minSpeedEdit.GetHeight()
						+ m_rMainWnd.GetControlOffset();
	m_freqLabel.SetPos(nFreqLeft, nFreqTop);
	nFreqLeft += m_freqLabel.GetWidth();
	m_minFreqEdit.SetPos(nFreqLeft, nFreqTop);
	nFreqLeft += m_minSpeedEdit.GetWidth();
	m_minFreqUd.SetPos(nFreqLeft, nFreqTop);
	nFreqLeft += m_minSpeedUd.GetWidth() + m_rMainWnd.GetControlOffset();
	m_freqLabel2.SetPos(nFreqLeft, nFreqTop);
	nFreqLeft += m_speedLabel2.GetWidth();
	m_maxFreqEdit.SetPos(nFreqLeft, nFreqTop);
	nFreqLeft += m_maxSpeedEdit.GetWidth();
	m_maxFreqUd.SetPos(nFreqLeft, nFreqTop);
	nFreqLeft += m_maxFreqUd.GetWidth()
					  + m_rMainWnd.GetControlOffset();
	m_freqLabel3.SetPos(nFreqLeft, nFreqTop);

	// 音程系コントロールの位置設定
	int nPitchLeft = m_rMainWnd.GetControlOffset() * 2;
	int nPitchTop = nFreqTop + m_minFreqEdit.GetHeight()
					+ m_rMainWnd.GetControlOffset();
	m_pitchLabel.SetPos(nPitchLeft, nPitchTop);
	nPitchLeft += m_freqLabel.GetWidth();
	m_minPitchEdit.SetPos(nPitchLeft, nPitchTop);
	nPitchLeft += m_minSpeedEdit.GetWidth();
	m_minPitchUd.SetPos(nPitchLeft, nPitchTop);
	nPitchLeft += m_minSpeedUd.GetWidth() + m_rMainWnd.GetControlOffset()
				  + m_speedLabel2.GetWidth() - m_pitchLabel2.GetWidth();
	m_pitchLabel2.SetPos(nPitchLeft, nPitchTop);
	nPitchLeft += m_speedLabel2.GetWidth();
	m_maxPitchEdit.SetPos(nPitchLeft, nPitchTop);
	nPitchLeft += m_maxSpeedEdit.GetWidth();
	m_maxPitchUd.SetPos(nPitchLeft, nPitchTop);

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nFreqLeft + m_freqLabel3.GetWidth()
							- m_CancelButton.GetWidth();
	int nCancelButtonTop = nPitchTop + m_minPitchEdit.GetHeight()
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
void CLimitSettingWnd_MainWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
void CLimitSettingWnd_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	if(hwndCtl == (HWND)m_minSpeedUd) {
		TCHAR text[18];
		_stprintf_s(text, _T("%3.1f"), pos / 10.0);
		m_minSpeedEdit.SetText(text);
		PostMessage(m_minSpeedEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_minSpeedEdit, EM_SETSEL, 0, -1);
	}
	else if(hwndCtl == (HWND)m_maxSpeedUd) {
		TCHAR text[18];
		_stprintf_s(text, _T("%4.1f"), (pos + 20000) / 10.0);
		m_maxSpeedEdit.SetText(text);
		PostMessage(m_maxSpeedEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_maxSpeedEdit, EM_SETSEL, 0, -1);
	}
	else if(hwndCtl == (HWND)m_minFreqUd) {
		TCHAR text[18];
		_stprintf_s(text, _T("%3.1f"), pos / 10.0);
		m_minFreqEdit.SetText(text);
		PostMessage(m_minFreqEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_minFreqEdit, EM_SETSEL, 0, -1);
	}
	else if(hwndCtl == (HWND)m_maxFreqUd) {
		TCHAR text[18];
		_stprintf_s(text, _T("%4.1f"), (pos + 20000) / 10.0);
		m_maxFreqEdit.SetText(text);
		PostMessage(m_maxFreqEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_maxFreqEdit, EM_SETSEL, 0, -1);
	}
	else if(hwndCtl == (HWND)m_minPitchUd) {
		TCHAR text[18];
		if(pos > 0)
			_stprintf_s(text, _T("♯%2.1f"), pos / 10.0);
		else if(pos < 0)
			_stprintf_s(text, _T("♭%2.1f"), pos / 10.0 * -1);
		else
			_stprintf_s(text, _T("%2.1f"), pos / 10.0);
		m_minPitchEdit.SetText(text);
		PostMessage(m_minPitchEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_minPitchEdit, EM_SETSEL, 0, -1);
	}
	else if(hwndCtl == (HWND)m_maxPitchUd) {
		TCHAR text[18];
		if(pos > 0)
			_stprintf_s(text, _T("♯%2.1f"), pos / 10.0);
		else if(pos < 0)
			_stprintf_s(text, _T("♭%2.1f"), pos / 10.0 * -1);
		else
			_stprintf_s(text, _T("%2.1f"), pos / 10.0);
		m_maxPitchEdit.SetText(text);
		PostMessage(m_maxPitchEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_maxPitchEdit, EM_SETSEL, 0, -1);
	}

	CFrameWnd::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CLimitSettingWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
