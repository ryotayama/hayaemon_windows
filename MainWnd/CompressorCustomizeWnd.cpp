//----------------------------------------------------------------------------
// CompressorCustomizeWnd.cpp : コンプレッサカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "CompressorCustomizeWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CCompressorCustomizeWnd::CCompressorCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_gainEdit(*this),
	  m_attackEdit(*this), m_releaseEdit(*this), m_thresholdEdit(*this),
	  m_ratioEdit(*this), m_predelayEdit(*this), m_OkButton(*this),
	  m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CCompressorCustomizeWnd::~CCompressorCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CCompressorCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("CompressorCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("CompressorCustomizeWndCls"),
#if JP
							_T("コンプレッサーのカスタマイズ"),
#else // JP
							_T("Customize Compressor"),
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
void CCompressorCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_attackEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_releaseEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_thresholdEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_ratioEdit);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_predelayEdit);
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
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// 前のコントロールにフォーカス
//----------------------------------------------------------------------------
void CCompressorCustomizeWnd::SetPreviousFocus()
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
			SetFocus((HWND)m_gainEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_attackEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_releaseEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_thresholdEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_ratioEdit);
			m_nFocus = 5;
			break;
		case 7:
			SetFocus((HWND)m_predelayEdit);
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
void CCompressorCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if( hwndCtl == m_gainEdit || hwndCtl == m_attackEdit ||
		hwndCtl == m_releaseEdit || hwndCtl == m_thresholdEdit ||
		hwndCtl == m_ratioEdit || hwndCtl == m_predelayEdit)
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
			dMax = 60.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_attackEdit) {
			rEdit = &m_attackEdit;
			rUd = &m_attackUd;
			dMin = 0.01;
			dMax = 500.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_releaseEdit) {
			rEdit = &m_releaseEdit;
			rUd = &m_releaseUd;
			dMin = 50.0;
			dMax = 3000.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_thresholdEdit) {
			rEdit = &m_thresholdEdit;
			rUd = &m_thresholdUd;
			dMin = -60.0;
			dMax = 0.0;
			nNewFocus = 4;
		}
		else if(hwndCtl == m_ratioEdit) {
			rEdit = &m_ratioEdit;
			rUd = &m_ratioUd;
			dMin = 1.0;
			dMax = 100.0;
			nNewFocus = 5;
		}
		else if(hwndCtl == m_predelayEdit) {
			rEdit = &m_predelayEdit;
			rUd = &m_predelayUd;
			dMin = 0.0;
			dMax = 4.0;
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
void CCompressorCustomizeWnd::OnOkButtonClicked()
{
	float fGain = (float)_tstof(m_gainEdit.GetText().c_str());
	float fAttack = (float)_tstof(m_attackEdit.GetText().c_str());
	float fRelease = (float)_tstof(m_releaseEdit.GetText().c_str());
	float fThreshold = (float)_tstof(m_thresholdEdit.GetText().c_str());
	float fRatio = (float)_tstof(m_ratioEdit.GetText().c_str());
	float fPredelay = (float)_tstof(m_predelayEdit.GetText().c_str());

	m_rMainWnd.GetMenu().SetCompressor(fGain, fAttack, fRelease, fThreshold,
		fRatio, fPredelay, ID_COMPRESSOR_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// キャンセルボタンが押された
//----------------------------------------------------------------------------
void CCompressorCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// エンターキーが押された
//----------------------------------------------------------------------------
void CCompressorCustomizeWnd::OnReturnKeyPressed()
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
void CCompressorCustomizeWnd::OnSpaceKeyPressed()
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
void CCompressorCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CCompressorCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_COMPRESSOR bdcmp;
	BOOL bCompressor = m_rMainWnd.GetSound().GetCompressor(&bdcmp);
	float fGain = bCompressor ? bdcmp.fGain : 0.0f;
	float fAttack = bCompressor ? bdcmp.fAttack : 10.0f;
	float fRelease = bCompressor ? bdcmp.fRelease : 200.0f;
	float fThreshold = bCompressor ? bdcmp.fThreshold : -20.0f;
	float fRatio = bCompressor ? bdcmp.fRatio : 3.0f;
	float fPredelay = bCompressor ? bdcmp.fPredelay : 4.0f;

	TCHAR chGain[255], chAttack[255], chRelease[255], chThreshold[255],
		  chRatio[255], chPredelay[255];
	_stprintf_s(chGain, _T("%4.3f"), fGain);
	_stprintf_s(chAttack, _T("%4.3f"), fAttack);
	_stprintf_s(chRelease, _T("%4.3f"), fRelease);
	_stprintf_s(chThreshold, _T("%4.3f"), fThreshold);
	_stprintf_s(chRatio, _T("%4.3f"), fRatio);
	_stprintf_s(chPredelay, _T("%4.3f"), fPredelay);

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
	SendMessage(m_gainUd, UDM_SETRANGE32, -60000, 60000);
	SendMessage(m_gainUd, UDM_SETPOS32, 0, (LONG)(fGain * 1000));
	m_gainUd.Show(SW_SHOW);
	m_gainEdit.SetSize(m_gainEdit.GetWidth()
		+ m_gainUd.GetWidth(), m_gainEdit.GetHeight());

	if(!m_attackLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_attackLabel.SetParent(m_hWnd);
	m_attackLabel.SetFont(m_font, TRUE);
	m_attackLabel.SetText(_T("ATTACK: "));
	m_attackLabel.SetSizeToTextSize();
	m_attackLabel.Show(SW_SHOW);

	if(!m_attackEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_attackEdit, EM_SETLIMITTEXT, 7, 0);
	m_attackEdit.SetStyle(m_attackEdit.GetStyle() | ES_RIGHT);
	m_attackEdit.SetFont(m_font, TRUE);
	m_attackEdit.SetText(_T("2000.000"));
	m_attackEdit.SetSizeToTextSize();
	m_attackEdit.SetText(chAttack);
	m_attackEdit.Show(SW_SHOW);

	if(!m_attackUd.Create(m_hWnd, m_attackEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_attackUd, UDM_SETRANGE32, 10, 500000);
	SendMessage(m_attackUd, UDM_SETPOS32, 0, (LONG)(fAttack * 1000));
	m_attackUd.Show(SW_SHOW);
	m_attackEdit.SetSize(m_attackEdit.GetWidth()
		+ m_attackUd.GetWidth(), m_attackEdit.GetHeight());

	if(!m_releaseLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_releaseLabel.SetParent(m_hWnd);
	m_releaseLabel.SetFont(m_font, TRUE);
	m_releaseLabel.SetText(_T("RELEASE: "));
	m_releaseLabel.SetSizeToTextSize();
	m_releaseLabel.Show(SW_SHOW);

	if(!m_releaseEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_releaseEdit, EM_SETLIMITTEXT, 8, 0);
	m_releaseEdit.SetStyle(m_releaseEdit.GetStyle() | ES_RIGHT);
	m_releaseEdit.SetFont(m_font, TRUE);
	m_releaseEdit.SetText(_T("2000.000"));
	m_releaseEdit.SetSizeToTextSize();
	m_releaseEdit.SetText(chRelease);
	m_releaseEdit.Show(SW_SHOW);

	if(!m_releaseUd.Create(m_hWnd, m_releaseEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_releaseUd, UDM_SETRANGE32, 50000, 3000000);
	SendMessage(m_releaseUd, UDM_SETPOS32, 0, (LONG)(fRelease * 1000));
	m_releaseUd.Show(SW_SHOW);
	m_releaseEdit.SetSize(m_releaseEdit.GetWidth()
		+ m_releaseUd.GetWidth(), m_releaseEdit.GetHeight());

	if(!m_thresholdLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_thresholdLabel.SetParent(m_hWnd);
	m_thresholdLabel.SetFont(m_font, TRUE);
	m_thresholdLabel.SetText(_T("THRESHOLD: "));
	m_thresholdLabel.SetSizeToTextSize();
	m_thresholdLabel.Show(SW_SHOW);

	if(!m_thresholdEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_thresholdEdit, EM_SETLIMITTEXT, 7, 0);
	m_thresholdEdit.SetStyle(m_thresholdEdit.GetStyle() | ES_RIGHT);
	m_thresholdEdit.SetFont(m_font, TRUE);
	m_thresholdEdit.SetText(_T("2000.000"));
	m_thresholdEdit.SetSizeToTextSize();
	m_thresholdEdit.SetText(chThreshold);
	m_thresholdEdit.Show(SW_SHOW);

	if(!m_thresholdUd.Create(m_hWnd, m_thresholdEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_thresholdUd, UDM_SETRANGE32, -60000, 0);
	SendMessage(m_thresholdUd, UDM_SETPOS32, 0, (LONG)(fThreshold * 1000));
	m_thresholdUd.Show(SW_SHOW);
	m_thresholdEdit.SetSize(m_thresholdEdit.GetWidth()
		+ m_thresholdUd.GetWidth(), m_thresholdEdit.GetHeight());

	if(!m_ratioLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_ratioLabel.SetParent(m_hWnd);
	m_ratioLabel.SetFont(m_font, TRUE);
	m_ratioLabel.SetText(_T("RATIO: "));
	m_ratioLabel.SetSizeToTextSize();
	m_ratioLabel.Show(SW_SHOW);

	if(!m_ratioEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ratioEdit, EM_SETLIMITTEXT, 7, 0);
	m_ratioEdit.SetStyle(m_ratioEdit.GetStyle() | ES_RIGHT);
	m_ratioEdit.SetFont(m_font, TRUE);
	m_ratioEdit.SetText(_T("2000.000"));
	m_ratioEdit.SetSizeToTextSize();
	m_ratioEdit.SetText(chRatio);
	m_ratioEdit.Show(SW_SHOW);

	if(!m_ratioUd.Create(m_hWnd, m_ratioEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_ratioUd, UDM_SETRANGE32, 1000, 100000);
	SendMessage(m_ratioUd, UDM_SETPOS32, 0, (LONG)(fRatio * 1000));
	m_ratioUd.Show(SW_SHOW);
	m_ratioEdit.SetSize(m_ratioEdit.GetWidth()
		+ m_ratioUd.GetWidth(), m_ratioEdit.GetHeight());

	if(!m_predelayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_predelayLabel.SetParent(m_hWnd);
	m_predelayLabel.SetFont(m_font, TRUE);
	m_predelayLabel.SetText(_T("PREDELAY: "));
	m_predelayLabel.SetSizeToTextSize();
	m_predelayLabel.Show(SW_SHOW);

	if(!m_predelayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_predelayEdit, EM_SETLIMITTEXT, 5, 0);
	m_predelayEdit.SetStyle(m_predelayEdit.GetStyle() | ES_RIGHT);
	m_predelayEdit.SetFont(m_font, TRUE);
	m_predelayEdit.SetText(_T("2000.000"));
	m_predelayEdit.SetSizeToTextSize();
	m_predelayEdit.SetText(chPredelay);
	m_predelayEdit.Show(SW_SHOW);

	if(!m_predelayUd.Create(m_hWnd, m_predelayEdit)) {
#if JP
		m_rApp.ShowError(_T("アップダウンコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_predelayUd, UDM_SETRANGE32, 0, 4000);
	SendMessage(m_predelayUd, UDM_SETPOS32, 0, (LONG)(fPredelay * 1000));
	m_predelayUd.Show(SW_SHOW);
	m_predelayEdit.SetSize(m_predelayEdit.GetWidth()
		+ m_predelayUd.GetWidth(), m_predelayEdit.GetHeight());

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
	nLeft += m_thresholdLabel.GetWidth();
	m_gainEdit.SetPos(nLeft, nTop);
	nLeft += m_gainEdit.GetWidth();
	m_gainUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_gainEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_attackLabel.SetPos(nLeft, nTop);
	nLeft += m_thresholdLabel.GetWidth();
	m_attackEdit.SetPos(nLeft, nTop);
	nLeft += m_attackEdit.GetWidth();
	m_attackUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_attackEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_releaseLabel.SetPos(nLeft, nTop);
	nLeft += m_thresholdLabel.GetWidth();
	m_releaseEdit.SetPos(nLeft, nTop);
	nLeft += m_releaseEdit.GetWidth();
	m_releaseUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_releaseEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_thresholdLabel.SetPos(nLeft, nTop);
	nLeft += m_thresholdLabel.GetWidth();
	m_thresholdEdit.SetPos(nLeft, nTop);
	nLeft += m_thresholdEdit.GetWidth();
	m_thresholdUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_thresholdEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_ratioLabel.SetPos(nLeft, nTop);
	nLeft += m_thresholdLabel.GetWidth();
	m_ratioEdit.SetPos(nLeft, nTop);
	nLeft += m_ratioEdit.GetWidth();
	m_ratioUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_ratioEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_predelayLabel.SetPos(nLeft, nTop);
	nLeft += m_thresholdLabel.GetWidth();
	m_predelayEdit.SetPos(nLeft, nTop);
	nLeft += m_predelayEdit.GetWidth();
	m_predelayUd.SetPos(nLeft, nTop);

	// 「OK」「キャンセル」ボタンの位置設定
	int nCancelButtonLeft = nLeft;
	int nCancelButtonTop = nTop + m_predelayEdit.GetHeight()
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
void CCompressorCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CCompressorCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
LRESULT CCompressorCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if( pnmhdr->hwndFrom == m_gainUd ||
			pnmhdr->hwndFrom == m_attackUd ||
			pnmhdr->hwndFrom == m_releaseUd ||
			pnmhdr->hwndFrom == m_thresholdUd ||
			pnmhdr->hwndFrom == m_ratioUd ||
			pnmhdr->hwndFrom == m_predelayUd)
		{
			CEditExt * rEdit;
			CUpDownCtrl * rUd;
			double dMin;
			double dMax;
			if(pnmhdr->hwndFrom == m_gainUd) {
				rEdit = &m_gainEdit;
				rUd = &m_gainUd;
				dMin = -60.0;
				dMax = 60.0;
			}
			else if(pnmhdr->hwndFrom == m_attackUd) {
				rEdit = &m_attackEdit;
				rUd = &m_attackUd;
				dMin = 0.01;
				dMax = 500.0;
			}
			else if(pnmhdr->hwndFrom == m_releaseUd) {
				rEdit = &m_releaseEdit;
				rUd = &m_releaseUd;
				dMin = 50.0;
				dMax = 3000.0;
			}
			else if(pnmhdr->hwndFrom == m_thresholdUd) {
				rEdit = &m_thresholdEdit;
				rUd = &m_thresholdUd;
				dMin = -60.0;
				dMax = 0.0;
			}
			else if(pnmhdr->hwndFrom == m_ratioUd) {
				rEdit = &m_ratioEdit;
				rUd = &m_ratioUd;
				dMin = 1.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_predelayUd) {
				rEdit = &m_predelayEdit;
				rUd = &m_predelayUd;
				dMin = 0.0;
				dMax = 4.0;
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
