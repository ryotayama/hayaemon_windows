//----------------------------------------------------------------------------
// GargleCustomizeWnd.cpp : ガーグルカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "GargleCustomizeWnd.h"
#include "Sound.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CGargleCustomizeWnd::CGargleCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_rateHzEdit(*this),
	  m_waveShapeEdit(*this), m_OkButton(*this), m_CancelButton(*this),
	  m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CGargleCustomizeWnd::~CGargleCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CGargleCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("GargleCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("GargleCustomizeWndCls"),
#if JP
							_T("ガーグルのカスタマイズ"),
#else // JP
							_T("Customize Gargle"),
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
void CGargleCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_rateHzEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_waveShapeEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_rateHzEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 4;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 4;
			break;
		case 2:
			SetFocus((HWND)m_rateHzEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_waveShapeEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 3;
			break;
	}
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_rateHzEdit || hwndCtl == m_waveShapeEdit)
	{
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double dMin;
		double dMax;
		int nNewFocus;
		if(hwndCtl == m_rateHzEdit) {
			rEdit = &m_rateHzEdit;
			rUd = &m_rateHzUd;
			dMin = 1.0;
			dMax = 1000.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_waveShapeEdit) {
			rEdit = &m_waveShapeEdit;
			rUd = &m_waveShapeUd;
			dMin = 0.0;
			dMax = 1.0;
			nNewFocus = 2;
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
				SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			TCHAR buf[255];
			if(n < dMin) n = dMin;
			else if(n > dMax) n = dMax;
			_stprintf_s(buf, _T("%d"), (int)n);
			rEdit->SetText(buf);
			SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
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
void CGargleCustomizeWnd::OnOkButtonClicked()
{
	int nRateHz = _tstoi(m_rateHzEdit.GetText().c_str());
	int nWaveShape = _tstoi(m_waveShapeEdit.GetText().c_str());

	m_rMainWnd.GetMenu().SetGargle((DWORD)nRateHz, (DWORD)nWaveShape,
		ID_GARGLE_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnReturnKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			OnOkButtonClicked();
			break;
		case 4:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// スペースキーが押された
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnSpaceKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
		case 3:
			OnOkButtonClicked();
			break;
		case 4:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// エスケープキーが押された
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CGargleCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_GARGLE bdg;
	BOOL bGargle = m_rMainWnd.GetSound().GetGargle(&bdg);
	int nRateHz = bGargle ? bdg.dwRateHz : 20;
	int nWaveShape = bGargle ? bdg.dwWaveShape : 0;

	TCHAR chRateHz[255], chWaveShape[255];
	_stprintf_s(chRateHz, _T("%d"), nRateHz);
	_stprintf_s(chWaveShape, _T("%d"), nWaveShape);

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

	if(!m_rateHzLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_rateHzLabel.SetParent(m_hWnd);
	m_rateHzLabel.SetFont(m_font, TRUE);
	m_rateHzLabel.SetText(_T("RATE HZ: "));
	m_rateHzLabel.SetSizeToTextSize();
	m_rateHzLabel.Show(SW_SHOW);

	if(!m_rateHzEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_rateHzEdit, EM_SETLIMITTEXT, 4, 0);
	m_rateHzEdit.SetStyle(m_rateHzEdit.GetStyle() | ES_RIGHT);
	m_rateHzEdit.SetFont(m_font, TRUE);
	m_rateHzEdit.SetText(_T("2000"));
	m_rateHzEdit.SetSizeToTextSize();
	m_rateHzEdit.SetText(chRateHz);
	m_rateHzEdit.Show(SW_SHOW);

	if(!m_rateHzUd.Create(m_hWnd, m_rateHzEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_rateHzUd, UDM_SETRANGE32, 1, 1000);
	SendMessage(m_rateHzUd, UDM_SETPOS32, 0, (LONG)nRateHz);
	m_rateHzUd.Show(SW_SHOW);
	m_rateHzEdit.SetSize(m_rateHzEdit.GetWidth()
		+ m_rateHzUd.GetWidth(), m_rateHzEdit.GetHeight());

	if(!m_waveShapeLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_waveShapeLabel.SetParent(m_hWnd);
	m_waveShapeLabel.SetFont(m_font, TRUE);
	m_waveShapeLabel.SetText(_T("WAVE SHAPE: "));
	m_waveShapeLabel.SetSizeToTextSize();
	m_waveShapeLabel.Show(SW_SHOW);

	if(!m_waveShapeEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_waveShapeEdit, EM_SETLIMITTEXT, 1, 0);
	m_waveShapeEdit.SetStyle(m_waveShapeEdit.GetStyle() | ES_RIGHT);
	m_waveShapeEdit.SetFont(m_font, TRUE);
	m_waveShapeEdit.SetText(_T("2000"));
	m_waveShapeEdit.SetSizeToTextSize();
	m_waveShapeEdit.SetText(chWaveShape);
	m_waveShapeEdit.Show(SW_SHOW);

	if(!m_waveShapeUd.Create(m_hWnd, m_waveShapeEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_waveShapeUd, UDM_SETRANGE32, 0, 1);
	SendMessage(m_waveShapeUd, UDM_SETPOS32, 0, (LONG)nWaveShape);
	m_waveShapeUd.Show(SW_SHOW);
	m_waveShapeEdit.SetSize(m_waveShapeEdit.GetWidth()
		+ m_waveShapeUd.GetWidth(), m_waveShapeEdit.GetHeight());

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
	m_rateHzLabel.SetPos(nLeft, nTop);
	nLeft += m_waveShapeLabel.GetWidth();
	m_rateHzEdit.SetPos(nLeft, nTop);
	nLeft += m_rateHzEdit.GetWidth();
	m_rateHzUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_waveShapeEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_waveShapeLabel.SetPos(nLeft, nTop);
	nLeft += m_waveShapeLabel.GetWidth();
	m_waveShapeEdit.SetPos(nLeft, nTop);
	nLeft += m_waveShapeEdit.GetWidth();
	m_waveShapeUd.SetPos(nLeft, nTop);

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nLeft;
	int nCancelButtonTop = nTop + m_waveShapeEdit.GetHeight()
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
void CGargleCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CGargleCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
LRESULT CGargleCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if( pnmhdr->hwndFrom == m_rateHzUd ||
			pnmhdr->hwndFrom == m_waveShapeUd)
		{
			CEditExt * rEdit;
			CUpDownCtrl * rUd;
			double dMin;
			double dMax;
			if(pnmhdr->hwndFrom == m_rateHzUd) {
				rEdit = &m_rateHzEdit;
				rUd = &m_rateHzUd;
				dMin = 1.0;
				dMax = 1000.0;
			}
			else if(pnmhdr->hwndFrom == m_waveShapeUd) {
				rEdit = &m_waveShapeEdit;
				rUd = &m_waveShapeUd;
				dMin = 0.0;
				dMax = 1.0;
			}

			tstring str = rEdit->GetText();
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			double d = _ttof(str.c_str());
			if(lpnmud->iDelta > 0) d += 1.0;
			else d -= 1.0;
			if(dMin <= d && d <= dMax) {
				TCHAR buf[255];
				_stprintf_s(buf, _T("%d"), (int)d);
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
