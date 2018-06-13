//----------------------------------------------------------------------------
// 3DReverbCustomizeWnd.cpp : ３Ｄリバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "3DReverbCustomizeWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
C3DReverbCustomizeWnd::C3DReverbCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_roomEdit(*this),
	  m_roomHFEdit(*this), m_roomRolloffFactorEdit(*this),
	  m_decayTimeEdit(*this), m_decayHFRatioEdit(*this),
	  m_reflectionsEdit(*this), m_reflectionsDelayEdit(*this),
	  m_reverbEdit(*this), m_reverbDelayEdit(*this), m_diffusionEdit(*this),
	  m_densityEdit(*this), m_hfReferenceEdit(*this), m_OkButton(*this),
	  m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
C3DReverbCustomizeWnd::~C3DReverbCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL C3DReverbCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("3DReverbCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("3DReverbCustomizeWndCls"),
#if JP
							_T("３Ｄリバーブのカスタマイズ"),
#else // JP
							_T("Customize 3DReverb"),
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
void C3DReverbCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_roomEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_roomHFEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_roomRolloffFactorEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_decayTimeEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_decayHFRatioEdit);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_reflectionsEdit);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_reflectionsDelayEdit);
			m_nFocus = 7;
			break;
		case 7:
			SetFocus((HWND)m_reverbEdit);
			m_nFocus = 8;
			break;
		case 8:
			SetFocus((HWND)m_reverbDelayEdit);
			m_nFocus = 9;
			break;
		case 9:
			SetFocus((HWND)m_diffusionEdit);
			m_nFocus = 10;
			break;
		case 10:
			SetFocus((HWND)m_densityEdit);
			m_nFocus = 11;
			break;
		case 11:
			SetFocus((HWND)m_hfReferenceEdit);
			m_nFocus = 12;
			break;
		case 12:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 13;
			break;
		case 13:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 14;
			break;
		case 14:
			SetFocus((HWND)m_roomEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 14;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 14;
			break;
		case 2:
			SetFocus((HWND)m_roomEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_roomHFEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_roomRolloffFactorEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_decayTimeEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_decayHFRatioEdit);
			m_nFocus = 5;
			break;
		case 7:
			SetFocus((HWND)m_reflectionsEdit);
			m_nFocus = 6;
			break;
		case 8:
			SetFocus((HWND)m_reflectionsDelayEdit);
			m_nFocus = 7;
			break;
		case 9:
			SetFocus((HWND)m_reverbEdit);
			m_nFocus = 8;
			break;
		case 10:
			SetFocus((HWND)m_reverbDelayEdit);
			m_nFocus = 9;
			break;
		case 11:
			SetFocus((HWND)m_diffusionEdit);
			m_nFocus = 10;
			break;
		case 12:
			SetFocus((HWND)m_densityEdit);
			m_nFocus = 11;
			break;
		case 13:
			SetFocus((HWND)m_hfReferenceEdit);
			m_nFocus = 12;
			break;
		case 14:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 13;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if( hwndCtl == m_roomEdit || hwndCtl == m_roomHFEdit ||
		hwndCtl == m_roomRolloffFactorEdit || hwndCtl == m_decayTimeEdit ||
		hwndCtl == m_decayHFRatioEdit || hwndCtl == m_reflectionsEdit ||
		hwndCtl == m_reflectionsDelayEdit || hwndCtl == m_reverbEdit ||
		hwndCtl == m_reverbDelayEdit || hwndCtl == m_diffusionEdit ||
		hwndCtl == m_densityEdit || hwndCtl == m_hfReferenceEdit)
	{
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double dMin;
		double dMax;
		int nNewFocus;
		if(hwndCtl == m_roomEdit) {
			rEdit = &m_roomEdit;
			rUd = &m_roomUd;
			dMin = -10000.0;
			dMax = 0.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_roomHFEdit) {
			rEdit = &m_roomHFEdit;
			rUd = &m_roomHFUd;
			dMin = -10000.0;
			dMax = 0.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_roomRolloffFactorEdit) {
			rEdit = &m_roomRolloffFactorEdit;
			rUd = &m_roomRolloffFactorUd;
			dMin = 0.0;
			dMax = 10.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_decayTimeEdit) {
			rEdit = &m_decayTimeEdit;
			rUd = &m_decayTimeUd;
			dMin = 0.1;
			dMax = 20.0;
			nNewFocus = 4;
		}
		else if(hwndCtl == m_decayHFRatioEdit) {
			rEdit = &m_decayHFRatioEdit;
			rUd = &m_decayHFRatioUd;
			dMin = 0.1;
			dMax = 2.0;
			nNewFocus = 5;
		}
		else if(hwndCtl == m_reflectionsEdit) {
			rEdit = &m_reflectionsEdit;
			rUd = &m_reflectionsUd;
			dMin = -10000.0;
			dMax = 1000.0;
			nNewFocus = 6;
		}
		else if(hwndCtl == m_reflectionsDelayEdit) {
			rEdit = &m_reflectionsDelayEdit;
			rUd = &m_reflectionsDelayUd;
			dMin = 0.0;
			dMax = 0.3;
			nNewFocus = 7;
		}
		else if(hwndCtl == m_reverbEdit) {
			rEdit = &m_reverbEdit;
			rUd = &m_reverbUd;
			dMin = -10000.0;
			dMax = 2000.0;
			nNewFocus = 8;
		}
		else if(hwndCtl == m_reverbDelayEdit) {
			rEdit = &m_reverbDelayEdit;
			rUd = &m_reverbDelayUd;
			dMin = 0.0;
			dMax = 0.1;
			nNewFocus = 9;
		}
		else if(hwndCtl == m_diffusionEdit) {
			rEdit = &m_diffusionEdit;
			rUd = &m_diffusionUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 10;
		}
		else if(hwndCtl == m_densityEdit) {
			rEdit = &m_densityEdit;
			rUd = &m_densityUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 11;
		}
		else if(hwndCtl == m_hfReferenceEdit) {
			rEdit = &m_hfReferenceEdit;
			rUd = &m_hfReferenceUd;
			dMin = 20.0;
			dMax = 20000.0;
			nNewFocus = 12;
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
				if( hwndCtl == m_roomEdit || hwndCtl == m_roomHFEdit ||
					hwndCtl == m_reflectionsEdit || hwndCtl == m_reverbEdit)
					SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
				else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			TCHAR buf[255];
			if(n < dMin) n = dMin;
			else if(n > dMax) n = dMax;
			if( hwndCtl == m_roomEdit || hwndCtl == m_roomHFEdit ||
				hwndCtl == m_reflectionsEdit || hwndCtl == m_reverbEdit)
				_stprintf_s(buf, _T("%d"), (int)n);
			else _stprintf_s(buf, _T("%4.3f"), n);
			rEdit->SetText(buf);
			if( hwndCtl == m_roomEdit || hwndCtl == m_roomHFEdit ||
				hwndCtl == m_reflectionsEdit || hwndCtl == m_reverbEdit)
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
void C3DReverbCustomizeWnd::OnOkButtonClicked()
{
	int lRoom = _tstoi(m_roomEdit.GetText().c_str());
	int lRoomHF = _tstoi(m_roomHFEdit.GetText().c_str());
	float flRoomRolloffFactor
		= (float)_tstof(m_roomRolloffFactorEdit.GetText().c_str());
	float flDecayTime = (float)_tstof(m_decayTimeEdit.GetText().c_str());
	float flDecayHFRatio = (float)_tstof(m_decayHFRatioEdit.GetText().c_str());
	int lReflections = _tstoi(m_reflectionsEdit.GetText().c_str());
	float flReflectionsDelay
		= (float)_tstof(m_reflectionsDelayEdit.GetText().c_str());
	int lReverb = _tstoi(m_reverbEdit.GetText().c_str());
	float flReverbDelay = (float)_tstof(m_reverbDelayEdit.GetText().c_str());
	float flDiffusion = (float)_tstof(m_diffusionEdit.GetText().c_str());
	float flDensity = (float)_tstof(m_densityEdit.GetText().c_str());
	float flHFReference = (float)_tstof(m_hfReferenceEdit.GetText().c_str());

	m_rMainWnd.GetMenu().Set3DReverb(lRoom, lRoomHF, flRoomRolloffFactor,
		flDecayTime, flDecayHFRatio, lReflections, flReflectionsDelay, lReverb,
		flReverbDelay, flDiffusion, flDensity, flHFReference,
		ID_3DREVERB_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnReturnKeyPressed()
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
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
			OnOkButtonClicked();
			break;
		case 14:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnSpaceKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 13:
			OnOkButtonClicked();
			break;
		case 14:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT C3DReverbCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_I3DL2REVERB bdir;
	BOOL b3DReverb = m_rMainWnd.GetSound().Get3DReverb(&bdir);
	int lRoom = b3DReverb ? bdir.lRoom : -1000;
	int lRoomHF = b3DReverb ? bdir.lRoomHF : -100;
	float flRoomRolloffFactor = b3DReverb ? bdir.flRoomRolloffFactor : 0.0f;
	float flDecayTime = b3DReverb ? bdir.flDecayTime : 1.49f;
	float flDecayHFRatio = b3DReverb ? bdir.flDecayHFRatio : 0.83f;
	int lReflections = b3DReverb ? bdir.lReflections : -2602;
	float flReflectionsDelay = b3DReverb ? bdir.flReflectionsDelay : 0.007f;
	int lReverb = b3DReverb ? bdir.lReverb : 200;
	float flReverbDelay = b3DReverb ? bdir.flReverbDelay : 0.011f;
	float flDiffusion = b3DReverb ? bdir.flDiffusion : 100.0f;
	float flDensity = b3DReverb ? bdir.flDensity : 100.0f;
	float flHFReference = b3DReverb ? bdir.flHFReference : 5000.0f;

	TCHAR chRoom[255], chRoomHF[255], chRoomRolloffFactor[255],
		  chDecayTime[255], chDecayHFRatio[255], chReflections[255],
		  chReflectionsDelay[255], chReverb[255], chReverbDelay[255],
		  chDiffusion[255], chDensity[255], chHFReference[255];
	_stprintf_s(chRoom, _T("%d"), lRoom);
	_stprintf_s(chRoomHF, _T("%d"), lRoomHF);
	_stprintf_s(chRoomRolloffFactor, _T("%4.3f"), flRoomRolloffFactor);
	_stprintf_s(chDecayTime, _T("%4.3f"), flDecayTime);
	_stprintf_s(chDecayHFRatio, _T("%4.3f"), flDecayHFRatio);
	_stprintf_s(chReflections, _T("%d"), lReflections);
	_stprintf_s(chReflectionsDelay, _T("%4.3f"), flReflectionsDelay);
	_stprintf_s(chReverb, _T("%d"), lReverb);
	_stprintf_s(chReverbDelay, _T("%4.3f"), flReverbDelay);
	_stprintf_s(chDiffusion, _T("%4.3f"), flDiffusion);
	_stprintf_s(chDensity, _T("%4.3f"), flDensity);
	_stprintf_s(chHFReference, _T("%4.3f"), flHFReference);

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

	if(!m_roomLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_roomLabel.SetParent(m_hWnd);
	m_roomLabel.SetFont(m_font, TRUE);
	m_roomLabel.SetText(_T("ROOM:"));
	m_roomLabel.SetSizeToTextSize();
	m_roomLabel.Show(SW_SHOW);

	if(!m_roomEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_roomEdit, EM_SETLIMITTEXT, 6, 0);
	m_roomEdit.SetStyle(m_roomEdit.GetStyle() | ES_RIGHT);
	m_roomEdit.SetFont(m_font, TRUE);
	m_roomEdit.SetText(_T("20000.000"));
	m_roomEdit.SetSizeToTextSize();
	m_roomEdit.SetText(chRoom);
	m_roomEdit.Show(SW_SHOW);

	if(!m_roomUd.Create(m_hWnd, m_roomEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_roomUd, UDM_SETRANGE32, -10000, 0);
	SendMessage(m_roomUd, UDM_SETPOS32, 0, lRoom);
	m_roomUd.Show(SW_SHOW);
	m_roomEdit.SetSize(m_roomEdit.GetWidth() + m_roomUd.GetWidth(),
					   m_roomEdit.GetHeight());

	if(!m_roomHFLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_roomHFLabel.SetParent(m_hWnd);
	m_roomHFLabel.SetFont(m_font, TRUE);
	m_roomHFLabel.SetText(_T("ROOM HF:"));
	m_roomHFLabel.SetSizeToTextSize();
	m_roomHFLabel.Show(SW_SHOW);

	if(!m_roomHFEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_roomHFEdit, EM_SETLIMITTEXT, 6, 0);
	m_roomHFEdit.SetStyle(m_roomHFEdit.GetStyle() | ES_RIGHT);
	m_roomHFEdit.SetFont(m_font, TRUE);
	m_roomHFEdit.SetText(_T("20000.000"));
	m_roomHFEdit.SetSizeToTextSize();
	m_roomHFEdit.SetText(chRoomHF);
	m_roomHFEdit.Show(SW_SHOW);

	if(!m_roomHFUd.Create(m_hWnd, m_roomHFEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_roomHFUd, UDM_SETRANGE32, -10000, 0);
	SendMessage(m_roomHFUd, UDM_SETPOS32, 0, lRoomHF);
	m_roomHFUd.Show(SW_SHOW);
	m_roomHFEdit.SetSize(m_roomHFEdit.GetWidth() + m_roomHFUd.GetWidth(),
						 m_roomHFEdit.GetHeight());

	if(!m_roomRolloffFactorLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_roomRolloffFactorLabel.SetParent(m_hWnd);
	m_roomRolloffFactorLabel.SetFont(m_font, TRUE);
	m_roomRolloffFactorLabel.SetText(_T("ROOM ROLLOFF FACTOR: "));
	m_roomRolloffFactorLabel.SetSizeToTextSize();
	m_roomRolloffFactorLabel.Show(SW_SHOW);

	if(!m_roomRolloffFactorEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_roomRolloffFactorEdit, EM_SETLIMITTEXT, 6, 0);
	m_roomRolloffFactorEdit.SetStyle(m_roomRolloffFactorEdit.GetStyle()
		| ES_RIGHT);
	m_roomRolloffFactorEdit.SetFont(m_font, TRUE);
	m_roomRolloffFactorEdit.SetText(_T("20000.000"));
	m_roomRolloffFactorEdit.SetSizeToTextSize();
	m_roomRolloffFactorEdit.SetText(chRoomRolloffFactor);
	m_roomRolloffFactorEdit.Show(SW_SHOW);

	if(!m_roomRolloffFactorUd.Create(m_hWnd, m_roomRolloffFactorEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_roomRolloffFactorUd, UDM_SETRANGE32, 0, 10000);
	SendMessage(m_roomRolloffFactorUd, UDM_SETPOS32, 0,
		(LONG)(flRoomRolloffFactor * 1000));
	m_roomRolloffFactorUd.Show(SW_SHOW);
	m_roomRolloffFactorEdit.SetSize(m_roomRolloffFactorEdit.GetWidth()
		+ m_roomRolloffFactorUd.GetWidth(),
		m_roomRolloffFactorEdit.GetHeight());

	if(!m_decayTimeLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_decayTimeLabel.SetParent(m_hWnd);
	m_decayTimeLabel.SetFont(m_font, TRUE);
	m_decayTimeLabel.SetText(_T("DECAY TIME:"));
	m_decayTimeLabel.SetSizeToTextSize();
	m_decayTimeLabel.Show(SW_SHOW);

	if(!m_decayTimeEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_decayTimeEdit, EM_SETLIMITTEXT, 6, 0);
	m_decayTimeEdit.SetStyle(m_decayTimeEdit.GetStyle() | ES_RIGHT);
	m_decayTimeEdit.SetFont(m_font, TRUE);
	m_decayTimeEdit.SetText(_T("20000.000"));
	m_decayTimeEdit.SetSizeToTextSize();
	m_decayTimeEdit.SetText(chDecayTime);
	m_decayTimeEdit.Show(SW_SHOW);

	if(!m_decayTimeUd.Create(m_hWnd, m_decayTimeEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_decayTimeUd, UDM_SETRANGE32, 100, 20000);
	SendMessage(m_decayTimeUd, UDM_SETPOS32, 0, (LONG)(flDecayTime * 1000));
	m_decayTimeUd.Show(SW_SHOW);
	m_decayTimeEdit.SetSize(m_decayTimeEdit.GetWidth()
		+ m_decayTimeUd.GetWidth(), m_decayTimeEdit.GetHeight());

	if(!m_decayHFRatioLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_decayHFRatioLabel.SetParent(m_hWnd);
	m_decayHFRatioLabel.SetFont(m_font, TRUE);
	m_decayHFRatioLabel.SetText(_T("DECAY HF RATIO:"));
	m_decayHFRatioLabel.SetSizeToTextSize();
	m_decayHFRatioLabel.Show(SW_SHOW);

	if(!m_decayHFRatioEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_decayHFRatioEdit, EM_SETLIMITTEXT, 5, 0);
	m_decayHFRatioEdit.SetStyle(m_decayHFRatioEdit.GetStyle() | ES_RIGHT);
	m_decayHFRatioEdit.SetFont(m_font, TRUE);
	m_decayHFRatioEdit.SetText(_T("20000.000"));
	m_decayHFRatioEdit.SetSizeToTextSize();
	m_decayHFRatioEdit.SetText(chDecayHFRatio);
	m_decayHFRatioEdit.Show(SW_SHOW);

	if(!m_decayHFRatioUd.Create(m_hWnd, m_decayHFRatioEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_decayHFRatioUd, UDM_SETRANGE32, 100, 2000);
	SendMessage(m_decayHFRatioUd, UDM_SETPOS32, 0,
		(LONG)(flDecayHFRatio * 1000));
	m_decayHFRatioUd.Show(SW_SHOW);
	m_decayHFRatioEdit.SetSize(m_decayHFRatioEdit.GetWidth()
		+ m_decayHFRatioUd.GetWidth(), m_decayHFRatioEdit.GetHeight());

	if(!m_reflectionsLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_reflectionsLabel.SetParent(m_hWnd);
	m_reflectionsLabel.SetFont(m_font, TRUE);
	m_reflectionsLabel.SetText(_T("REFLECTIONS:"));
	m_reflectionsLabel.SetSizeToTextSize();
	m_reflectionsLabel.Show(SW_SHOW);

	if(!m_reflectionsEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reflectionsEdit, EM_SETLIMITTEXT, 6, 0);
	m_reflectionsEdit.SetStyle(m_reflectionsEdit.GetStyle() | ES_RIGHT);
	m_reflectionsEdit.SetFont(m_font, TRUE);
	m_reflectionsEdit.SetText(_T("20000.000"));
	m_reflectionsEdit.SetSizeToTextSize();
	m_reflectionsEdit.SetText(chReflections);
	m_reflectionsEdit.Show(SW_SHOW);

	if(!m_reflectionsUd.Create(m_hWnd, m_reflectionsEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reflectionsUd, UDM_SETRANGE32, -10000, 1000);
	SendMessage(m_reflectionsUd, UDM_SETPOS32, 0,
		lReflections);
	m_reflectionsUd.Show(SW_SHOW);
	m_reflectionsEdit.SetSize(m_reflectionsEdit.GetWidth()
		+ m_reflectionsUd.GetWidth(), m_reflectionsEdit.GetHeight());

	if(!m_reflectionsDelayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_reflectionsDelayLabel.SetParent(m_hWnd);
	m_reflectionsDelayLabel.SetFont(m_font, TRUE);
	m_reflectionsDelayLabel.SetText(_T("REFLECTIONS DELAY:"));
	m_reflectionsDelayLabel.SetSizeToTextSize();
	m_reflectionsDelayLabel.Show(SW_SHOW);

	if(!m_reflectionsDelayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reflectionsDelayEdit, EM_SETLIMITTEXT, 5, 0);
	m_reflectionsDelayEdit.SetStyle(m_reflectionsDelayEdit.GetStyle()
		| ES_RIGHT);
	m_reflectionsDelayEdit.SetFont(m_font, TRUE);
	m_reflectionsDelayEdit.SetText(_T("20000.000"));
	m_reflectionsDelayEdit.SetSizeToTextSize();
	m_reflectionsDelayEdit.SetText(chReflectionsDelay);
	m_reflectionsDelayEdit.Show(SW_SHOW);

	if(!m_reflectionsDelayUd.Create(m_hWnd, m_reflectionsDelayEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reflectionsDelayUd, UDM_SETRANGE32, 0, 300);
	SendMessage(m_reflectionsDelayUd, UDM_SETPOS32, 0,
		(LONG)(flReflectionsDelay * 1000));
	m_reflectionsDelayUd.Show(SW_SHOW);
	m_reflectionsDelayEdit.SetSize(m_reflectionsDelayEdit.GetWidth()
		+ m_reflectionsDelayUd.GetWidth(), m_reflectionsDelayEdit.GetHeight());

	if(!m_reverbLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_reverbLabel.SetParent(m_hWnd);
	m_reverbLabel.SetFont(m_font, TRUE);
	m_reverbLabel.SetText(_T("REVERB:"));
	m_reverbLabel.SetSizeToTextSize();
	m_reverbLabel.Show(SW_SHOW);

	if(!m_reverbEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reverbEdit, EM_SETLIMITTEXT, 6, 0);
	m_reverbEdit.SetStyle(m_reverbEdit.GetStyle()
		| ES_RIGHT);
	m_reverbEdit.SetFont(m_font, TRUE);
	m_reverbEdit.SetText(_T("20000.000"));
	m_reverbEdit.SetSizeToTextSize();
	m_reverbEdit.SetText(chReverb);
	m_reverbEdit.Show(SW_SHOW);

	if(!m_reverbUd.Create(m_hWnd, m_reverbEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reverbUd, UDM_SETRANGE32, -10000, 2000);
	SendMessage(m_reverbUd, UDM_SETPOS32, 0,
		lReverb);
	m_reverbUd.Show(SW_SHOW);
	m_reverbEdit.SetSize(m_reverbEdit.GetWidth()
		+ m_reverbUd.GetWidth(), m_reverbEdit.GetHeight());

	if(!m_reverbDelayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_reverbDelayLabel.SetParent(m_hWnd);
	m_reverbDelayLabel.SetFont(m_font, TRUE);
	m_reverbDelayLabel.SetText(_T("REVERB DELAY:"));
	m_reverbDelayLabel.SetSizeToTextSize();
	m_reverbDelayLabel.Show(SW_SHOW);

	if(!m_reverbDelayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reverbDelayEdit, EM_SETLIMITTEXT, 5, 0);
	m_reverbDelayEdit.SetStyle(m_reverbDelayEdit.GetStyle()
		| ES_RIGHT);
	m_reverbDelayEdit.SetFont(m_font, TRUE);
	m_reverbDelayEdit.SetText(_T("20000.000"));
	m_reverbDelayEdit.SetSizeToTextSize();
	m_reverbDelayEdit.SetText(chReverbDelay);
	m_reverbDelayEdit.Show(SW_SHOW);

	if(!m_reverbDelayUd.Create(m_hWnd, m_reverbDelayEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_reverbDelayUd, UDM_SETRANGE32, 0, 100);
	SendMessage(m_reverbDelayUd, UDM_SETPOS32, 0,
		(LONG)(flReverbDelay * 1000));
	m_reverbDelayUd.Show(SW_SHOW);
	m_reverbDelayEdit.SetSize(m_reverbDelayEdit.GetWidth()
		+ m_reverbDelayUd.GetWidth(), m_reverbDelayEdit.GetHeight());

	if(!m_diffusionLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_diffusionLabel.SetParent(m_hWnd);
	m_diffusionLabel.SetFont(m_font, TRUE);
	m_diffusionLabel.SetText(_T("DIFFUSION:"));
	m_diffusionLabel.SetSizeToTextSize();
	m_diffusionLabel.Show(SW_SHOW);

	if(!m_diffusionEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_diffusionEdit, EM_SETLIMITTEXT, 7, 0);
	m_diffusionEdit.SetStyle(m_diffusionEdit.GetStyle()
		| ES_RIGHT);
	m_diffusionEdit.SetFont(m_font, TRUE);
	m_diffusionEdit.SetText(_T("20000.000"));
	m_diffusionEdit.SetSizeToTextSize();
	m_diffusionEdit.SetText(chDiffusion);
	m_diffusionEdit.Show(SW_SHOW);

	if(!m_diffusionUd.Create(m_hWnd, m_diffusionEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_diffusionUd, UDM_SETRANGE32, 0, 10000);
	SendMessage(m_diffusionUd, UDM_SETPOS32, 0,
		(LONG)(flDiffusion * 1000));
	m_diffusionUd.Show(SW_SHOW);
	m_diffusionEdit.SetSize(m_diffusionEdit.GetWidth()
		+ m_diffusionUd.GetWidth(), m_diffusionEdit.GetHeight());

	if(!m_densityLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_densityLabel.SetParent(m_hWnd);
	m_densityLabel.SetFont(m_font, TRUE);
	m_densityLabel.SetText(_T("DENSITY:"));
	m_densityLabel.SetSizeToTextSize();
	m_densityLabel.Show(SW_SHOW);

	if(!m_densityEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_densityEdit, EM_SETLIMITTEXT, 7, 0);
	m_densityEdit.SetStyle(m_densityEdit.GetStyle()
		| ES_RIGHT);
	m_densityEdit.SetFont(m_font, TRUE);
	m_densityEdit.SetText(_T("20000.000"));
	m_densityEdit.SetSizeToTextSize();
	m_densityEdit.SetText(chDensity);
	m_densityEdit.Show(SW_SHOW);

	if(!m_densityUd.Create(m_hWnd, m_densityEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_densityUd, UDM_SETRANGE32, 0, 10000);
	SendMessage(m_densityUd, UDM_SETPOS32, 0,
		(LONG)(flDensity * 1000));
	m_densityUd.Show(SW_SHOW);
	m_densityEdit.SetSize(m_densityEdit.GetWidth()
		+ m_densityUd.GetWidth(), m_densityEdit.GetHeight());

	if(!m_hfReferenceLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_hfReferenceLabel.SetParent(m_hWnd);
	m_hfReferenceLabel.SetFont(m_font, TRUE);
	m_hfReferenceLabel.SetText(_T("HF REFERENCE:"));
	m_hfReferenceLabel.SetSizeToTextSize();
	m_hfReferenceLabel.Show(SW_SHOW);

	if(!m_hfReferenceEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_hfReferenceEdit, EM_SETLIMITTEXT, 9, 0);
	m_hfReferenceEdit.SetStyle(m_hfReferenceEdit.GetStyle()
		| ES_RIGHT);
	m_hfReferenceEdit.SetFont(m_font, TRUE);
	m_hfReferenceEdit.SetText(_T("20000.000"));
	m_hfReferenceEdit.SetSizeToTextSize();
	m_hfReferenceEdit.SetText(chHFReference);
	m_hfReferenceEdit.Show(SW_SHOW);

	if(!m_hfReferenceUd.Create(m_hWnd, m_hfReferenceEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_hfReferenceUd, UDM_SETRANGE32, 20000, 20000000);
	SendMessage(m_hfReferenceUd, UDM_SETPOS32, 0,
		(LONG)(flHFReference * 1000));
	m_hfReferenceUd.Show(SW_SHOW);
	m_hfReferenceEdit.SetSize(m_hfReferenceEdit.GetWidth()
		+ m_hfReferenceUd.GetWidth(), m_hfReferenceEdit.GetHeight());

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
	m_roomLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_roomEdit.SetPos(nLeft, nTop);
	nLeft += m_roomEdit.GetWidth();
	m_roomUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_roomEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_roomHFLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_roomHFEdit.SetPos(nLeft, nTop);
	nLeft += m_roomHFEdit.GetWidth();
	m_roomHFUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_roomHFEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_roomRolloffFactorLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_roomRolloffFactorEdit.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorEdit.GetWidth();
	m_roomRolloffFactorUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_roomRolloffFactorEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_decayTimeLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_decayTimeEdit.SetPos(nLeft, nTop);
	nLeft += m_decayTimeEdit.GetWidth();
	m_decayTimeUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_decayTimeEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_decayHFRatioLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_decayHFRatioEdit.SetPos(nLeft, nTop);
	nLeft += m_decayHFRatioEdit.GetWidth();
	m_decayHFRatioUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_decayHFRatioEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_reflectionsLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_reflectionsEdit.SetPos(nLeft, nTop);
	nLeft += m_reflectionsEdit.GetWidth();
	m_reflectionsUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_reflectionsEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_reflectionsDelayLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_reflectionsDelayEdit.SetPos(nLeft, nTop);
	nLeft += m_reflectionsDelayEdit.GetWidth();
	m_reflectionsDelayUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_reflectionsDelayEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_reverbLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_reverbEdit.SetPos(nLeft, nTop);
	nLeft += m_reverbEdit.GetWidth();
	m_reverbUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_reverbEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_reverbDelayLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_reverbDelayEdit.SetPos(nLeft, nTop);
	nLeft += m_reverbDelayEdit.GetWidth();
	m_reverbDelayUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_reverbDelayEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_diffusionLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_diffusionEdit.SetPos(nLeft, nTop);
	nLeft += m_diffusionEdit.GetWidth();
	m_diffusionUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_diffusionEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_densityLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_densityEdit.SetPos(nLeft, nTop);
	nLeft += m_densityEdit.GetWidth();
	m_densityUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_densityEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_hfReferenceLabel.SetPos(nLeft, nTop);
	nLeft += m_roomRolloffFactorLabel.GetWidth();
	m_hfReferenceEdit.SetPos(nLeft, nTop);
	nLeft += m_hfReferenceEdit.GetWidth();
	m_hfReferenceUd.SetPos(nLeft, nTop);

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nLeft;
	int nCancelButtonTop = nTop + m_hfReferenceEdit.GetHeight()
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
void C3DReverbCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
LRESULT C3DReverbCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if( pnmhdr->hwndFrom == m_roomUd ||
			pnmhdr->hwndFrom == m_roomHFUd ||
			pnmhdr->hwndFrom == m_roomRolloffFactorUd ||
			pnmhdr->hwndFrom == m_decayTimeUd ||
			pnmhdr->hwndFrom == m_decayHFRatioUd ||
			pnmhdr->hwndFrom == m_reflectionsUd ||
			pnmhdr->hwndFrom == m_reflectionsDelayUd ||
			pnmhdr->hwndFrom == m_reverbUd ||
			pnmhdr->hwndFrom == m_reverbDelayUd ||
			pnmhdr->hwndFrom == m_diffusionUd ||
			pnmhdr->hwndFrom == m_densityUd ||
			pnmhdr->hwndFrom == m_hfReferenceUd)
		{
			CEditExt * rEdit;
			CUpDownCtrl * rUd;
			double dMin;
			double dMax;
			if(pnmhdr->hwndFrom == m_roomUd) {
				rEdit = &m_roomEdit;
				rUd = &m_roomUd;
				dMin = -10000.0;
				dMax = 0.0;
			}
			else if(pnmhdr->hwndFrom == m_roomHFUd) {
				rEdit = &m_roomHFEdit;
				rUd = &m_roomHFUd;
				dMin = -10000.0;
				dMax = 0.0;
			}
			else if(pnmhdr->hwndFrom == m_roomRolloffFactorUd) {
				rEdit = &m_roomRolloffFactorEdit;
				rUd = &m_roomRolloffFactorUd;
				dMin = 0.0;
				dMax = 10.0;
			}
			else if(pnmhdr->hwndFrom == m_decayTimeUd) {
				rEdit = &m_decayTimeEdit;
				rUd = &m_decayTimeUd;
				dMin = 0.1;
				dMax = 20.0;
			}
			else if(pnmhdr->hwndFrom == m_decayHFRatioUd) {
				rEdit = &m_decayHFRatioEdit;
				rUd = &m_decayHFRatioUd;
				dMin = 0.1;
				dMax = 2.0;
			}
			else if(pnmhdr->hwndFrom == m_reflectionsUd) {
				rEdit = &m_reflectionsEdit;
				rUd = &m_reflectionsUd;
				dMin = -10000.0;
				dMax = 1000.0;
			}
			else if(pnmhdr->hwndFrom == m_reflectionsDelayUd) {
				rEdit = &m_reflectionsDelayEdit;
				rUd = &m_reflectionsDelayUd;
				dMin = 0.0;
				dMax = 0.3;
			}
			else if(pnmhdr->hwndFrom == m_reverbUd) {
				rEdit = &m_reverbEdit;
				rUd = &m_reverbUd;
				dMin = -10000.0;
				dMax = 2000.0;
			}
			else if(pnmhdr->hwndFrom == m_reverbDelayUd) {
				rEdit = &m_reverbDelayEdit;
				rUd = &m_reverbDelayUd;
				dMin = 0.0;
				dMax = 0.1;
			}
			else if(pnmhdr->hwndFrom == m_diffusionUd) {
				rEdit = &m_diffusionEdit;
				rUd = &m_diffusionUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_densityUd) {
				rEdit = &m_densityEdit;
				rUd = &m_densityUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_hfReferenceUd) {
				rEdit = &m_hfReferenceEdit;
				rUd = &m_hfReferenceUd;
				dMin = 20.0;
				dMax = 20000.0;
			}

			tstring str = rEdit->GetText();
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			double d = _ttof(str.c_str());
			BOOL bInt = FALSE;
			if(pnmhdr->hwndFrom == m_roomUd ||
					pnmhdr->hwndFrom == m_roomHFUd ||
					pnmhdr->hwndFrom == m_reflectionsUd ||
					pnmhdr->hwndFrom == m_reverbUd)
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
