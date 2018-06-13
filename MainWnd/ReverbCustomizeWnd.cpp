//----------------------------------------------------------------------------
// ReverbCustomizeWnd.cpp : リバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "ReverbCustomizeWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CReverbCustomizeWnd::CReverbCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_gainEdit(*this),
	  m_revMixEdit(*this), m_revTimeEdit(*this), m_highEdit(*this),
	  m_OkButton(*this), m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CReverbCustomizeWnd::~CReverbCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CReverbCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("ReverbCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("ReverbCustomizeWndCls"),
#if JP
							_T("リバーブのカスタマイズ"),
#else // JP
							_T("Customize Reverb"),
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
void CReverbCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_revMixEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_revTimeEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_highEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
			break;
		case 2:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_revMixEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_revTimeEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_highEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 5;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_gainEdit || hwndCtl == m_revMixEdit
		|| hwndCtl == m_revTimeEdit || hwndCtl == m_highEdit) {
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double dMin;
		double dMax;
		int nNewFocus;
		if(hwndCtl == m_gainEdit) {
			rEdit = &m_gainEdit;
			rUd = &m_gainUd;
			dMin = -96.0;
			dMax = 0.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_revMixEdit) {
			rEdit = &m_revMixEdit;
			rUd = &m_revMixUd;
			dMin = -96.0;
			dMax = 0.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_revTimeEdit) {
			rEdit = &m_revTimeEdit;
			rUd = &m_revTimeUd;
			dMin = 0.001;
			dMax = 3000.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_highEdit) {
			rEdit = &m_highEdit;
			rUd = &m_highUd;
			dMin = 0.001;
			dMax = 0.999;
			nNewFocus = 4;
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
				if(hwndCtl == m_gainEdit || hwndCtl == m_revMixEdit)
					SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
				else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			TCHAR buf[255];
			if(n < dMin) n = dMin;
			else if(n > dMax) n = dMax;
			if(hwndCtl == m_gainEdit || hwndCtl == m_revMixEdit)
				_stprintf_s(buf, _T("%d"), (int)n);
			else _stprintf_s(buf, _T("%4.3f"), n);
			rEdit->SetText(buf);
			if(hwndCtl == m_gainEdit || hwndCtl == m_revMixEdit)
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
void CReverbCustomizeWnd::OnOkButtonClicked()
{
	float dGain = (float)_tstof(m_gainEdit.GetText().c_str());
	float dRevMix = (float)_tstof(m_revMixEdit.GetText().c_str());
	float dRevTime = (float)_tstof(m_revTimeEdit.GetText().c_str());
	float dHigh = (float)_tstof(m_highEdit.GetText().c_str());
	m_rMainWnd.GetMenu().SetReverb(dGain, dRevMix, dRevTime, dHigh,
		ID_REVERB_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnReturnKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			OnOkButtonClicked();
			break;
		case 6:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnSpaceKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 5:
			OnOkButtonClicked();
			break;
		case 6:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CReverbCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_REVERB bdr;
	BOOL bReverb = m_rMainWnd.GetSound().GetReverb(&bdr);
	int nGain = bReverb ? (int)bdr.fInGain : 0;
	TCHAR chGain[255], chRevMix[255], chRevTime[255], chHigh[255];
	_stprintf_s(chGain, _T("%d"), nGain);
	int nRevMix = bReverb ? (int)bdr.fReverbMix : 0;
	_stprintf_s(chRevMix, _T("%d"), nRevMix);
	double dRevTime = bReverb ? bdr.fReverbTime : 1000.0;
	_stprintf_s(chRevTime, _T("%4.3f"), dRevTime);
	double dHigh = bReverb ? bdr.fHighFreqRTRatio : 0.001;
	_stprintf_s(chHigh, _T("%4.3f"), dHigh);

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
	m_gainLabel.SetText(_T("GAIN:"));
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
	SendMessage(m_gainEdit, EM_SETLIMITTEXT, 3, 0);
	m_gainEdit.SetStyle(m_gainEdit.GetStyle() | ES_RIGHT);
	m_gainEdit.SetFont(m_font, TRUE);
	m_gainEdit.SetText(_T("3000.000"));
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
	SendMessage(m_gainUd, UDM_SETRANGE32, -96, 0);
	SendMessage(m_gainUd, UDM_SETPOS32, 0, nGain);
	m_gainUd.Show(SW_SHOW);
	m_gainEdit.SetSize(m_gainEdit.GetWidth() + m_gainUd.GetWidth(),
					   m_gainEdit.GetHeight());

	if(!m_revMixLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_revMixLabel.SetParent(m_hWnd);
	m_revMixLabel.SetFont(m_font, TRUE);
	m_revMixLabel.SetText(_T("REV MIX:"));
	m_revMixLabel.SetSizeToTextSize();
	m_revMixLabel.Show(SW_SHOW);

	if(!m_revMixEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_revMixEdit, EM_SETLIMITTEXT, 3, 0);
	m_revMixEdit.SetStyle(m_revMixEdit.GetStyle() | ES_RIGHT);
	m_revMixEdit.SetFont(m_font, TRUE);
	m_revMixEdit.SetText(_T("3000.000"));
	m_revMixEdit.SetSizeToTextSize();
	m_revMixEdit.SetText(chRevMix);
	m_revMixEdit.Show(SW_SHOW);

	if(!m_revMixUd.Create(m_hWnd, m_revMixEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_revMixUd, UDM_SETRANGE32, -96, 0);
	SendMessage(m_revMixUd, UDM_SETPOS32, 0, nRevMix);
	m_revMixUd.Show(SW_SHOW);
	m_revMixEdit.SetSize(m_revMixEdit.GetWidth() + m_revMixUd.GetWidth(),
						 m_revMixEdit.GetHeight());

	if(!m_revTimeLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_revTimeLabel.SetParent(m_hWnd);
	m_revTimeLabel.SetFont(m_font, TRUE);
	m_revTimeLabel.SetText(_T("REV TIME: "));
	m_revTimeLabel.SetSizeToTextSize();
	m_revTimeLabel.Show(SW_SHOW);

	if(!m_revTimeEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_revTimeEdit, EM_SETLIMITTEXT, 8, 0);
	m_revTimeEdit.SetStyle(m_revTimeEdit.GetStyle() | ES_RIGHT);
	m_revTimeEdit.SetFont(m_font, TRUE);
	m_revTimeEdit.SetText(_T("3000.000"));
	m_revTimeEdit.SetSizeToTextSize();
	m_revTimeEdit.SetText(chRevTime);
	m_revTimeEdit.Show(SW_SHOW);

	if(!m_revTimeUd.Create(m_hWnd, m_revTimeEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_revTimeUd, UDM_SETRANGE32, 1, 3000000);
	SendMessage(m_revTimeUd, UDM_SETPOS32, 0, (LONG)(dRevTime * 1000));
	m_revTimeUd.Show(SW_SHOW);
	m_revTimeEdit.SetSize(m_revTimeEdit.GetWidth() + m_revTimeUd.GetWidth(),
						 m_revTimeEdit.GetHeight());

	if(!m_highLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_highLabel.SetParent(m_hWnd);
	m_highLabel.SetFont(m_font, TRUE);
	m_highLabel.SetText(_T("HIGH:"));
	m_highLabel.SetSizeToTextSize();
	m_highLabel.Show(SW_SHOW);

	if(!m_highEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_highEdit, EM_SETLIMITTEXT, 5, 0);
	m_highEdit.SetStyle(m_highEdit.GetStyle() | ES_RIGHT);
	m_highEdit.SetFont(m_font, TRUE);
	m_highEdit.SetText(_T("3000.000"));
	m_highEdit.SetSizeToTextSize();
	m_highEdit.SetText(chHigh);
	m_highEdit.Show(SW_SHOW);

	if(!m_highUd.Create(m_hWnd, m_highEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_highUd, UDM_SETRANGE32, 1, 999);
	SendMessage(m_highUd, UDM_SETPOS32, 0, (LONG)(dHigh * 1000));
	m_highUd.Show(SW_SHOW);
	m_highEdit.SetSize(m_highEdit.GetWidth() + m_highUd.GetWidth(),
					   m_highEdit.GetHeight());

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

	int nGainLeft = m_rMainWnd.GetControlOffset() * 2;
	int nGainTop = m_rMainWnd.GetControlOffset() * 4;
	m_gainLabel.SetPos(nGainLeft, nGainTop);
	nGainLeft += m_revTimeLabel.GetWidth();
	m_gainEdit.SetPos(nGainLeft, nGainTop);
	nGainLeft += m_gainEdit.GetWidth();
	m_gainUd.SetPos(nGainLeft, nGainTop);
	nGainLeft += m_gainUd.GetWidth() + m_rMainWnd.GetControlOffset();

	int nRevMixLeft = m_rMainWnd.GetControlOffset() * 2;
	int nRevMixTop = nGainTop + m_gainEdit.GetHeight()
						+ m_rMainWnd.GetControlOffset();
	m_revMixLabel.SetPos(nRevMixLeft, nRevMixTop);
	nRevMixLeft += m_revTimeLabel.GetWidth();
	m_revMixEdit.SetPos(nRevMixLeft, nRevMixTop);
	nRevMixLeft += m_revMixEdit.GetWidth();
	m_revMixUd.SetPos(nRevMixLeft, nRevMixTop);
	nRevMixLeft += m_revMixUd.GetWidth() + m_rMainWnd.GetControlOffset();

	int nRevTimeLeft = m_rMainWnd.GetControlOffset() * 2;
	int nRevTimeTop = nRevMixTop + m_revMixEdit.GetHeight()
						+ m_rMainWnd.GetControlOffset();
	m_revTimeLabel.SetPos(nRevTimeLeft, nRevTimeTop);
	nRevTimeLeft += m_revTimeLabel.GetWidth();
	m_revTimeEdit.SetPos(nRevTimeLeft, nRevTimeTop);
	nRevTimeLeft += m_revTimeEdit.GetWidth();
	m_revTimeUd.SetPos(nRevTimeLeft, nRevTimeTop);
	nRevTimeLeft += m_revTimeUd.GetWidth() + m_rMainWnd.GetControlOffset();

	int nHighLeft = m_rMainWnd.GetControlOffset() * 2;
	int nHighTop = nRevTimeTop + m_revTimeEdit.GetHeight()
						+ m_rMainWnd.GetControlOffset();
	m_highLabel.SetPos(nHighLeft, nHighTop);
	nHighLeft += m_revTimeLabel.GetWidth();
	m_highEdit.SetPos(nHighLeft, nHighTop);
	nHighLeft += m_highEdit.GetWidth();
	m_highUd.SetPos(nHighLeft, nHighTop);
	nHighLeft += m_highUd.GetWidth() + m_rMainWnd.GetControlOffset();

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nRevTimeLeft + m_revTimeLabel.GetWidth()
							- m_CancelButton.GetWidth();
	int nCancelButtonTop = nHighTop + m_highEdit.GetHeight()
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
void CReverbCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CReverbCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
LRESULT CReverbCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if(pnmhdr->hwndFrom == (HWND)m_gainUd) {
			tstring strGain = m_gainEdit.GetText();
			int n = _ttoi(strGain.c_str());
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n++;
			else n--;
			if(-96 <= n && n <= 0) {
				TCHAR buf[255];
				_stprintf_s(buf, _T("%d"), (int)n);
				m_gainEdit.SetText(buf);
			}
		}
		else if(pnmhdr->hwndFrom == (HWND)m_revMixUd) {
			tstring str = m_revMixEdit.GetText();
			int n = _ttoi(str.c_str());
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n++;
			else n--;
			if(-96 <= n && n <= 0) {
				TCHAR buf[255];
				_stprintf_s(buf, _T("%d"), (int)n);
				m_revMixEdit.SetText(buf);
			}
		}
		else if(pnmhdr->hwndFrom == (HWND)m_revTimeUd) {
			tstring str = m_revTimeEdit.GetText();
			double n = _ttof(str.c_str());
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n += 0.001;
			else n -= 0.001;
			if(0.001 <= n && n <= 3000.000) {
				TCHAR buf[255];
				_stprintf_s(buf, _T("%4.3f"), n);
				m_revTimeEdit.SetText(buf);
			}
		}
		else if(pnmhdr->hwndFrom == (HWND)m_highUd) {
			tstring str = m_highEdit.GetText();
			double n = _ttof(str.c_str());
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			if(lpnmud->iDelta > 0) n += 0.001;
			else n -= 0.001;
			if(0.001 <= n && n <= 0.999) {
				TCHAR buf[255];
				_stprintf_s(buf, _T("%1.3f"), n);
				m_highEdit.SetText(buf);
			}
		}
		PostMessage(m_gainEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_gainEdit, EM_SETSEL, 0, -1);
		return TRUE;
	}
	return CFrameWnd::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
