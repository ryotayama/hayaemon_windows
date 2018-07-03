//----------------------------------------------------------------------------
// TweetWnd.cpp : ツイート用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "Sound.h"
#include "TweetWnd.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEdit_Tweet::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) m_rMainWnd.GetTweetWnd().Tweet();
	else if(vk == VK_ESCAPE) m_rMainWnd.GetTweetWnd().Close();
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTweetWnd::Create()
{
	Destroy();

	RegisterClass(_T("TweetWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("TweetWndCls"),
#if JP
							_T("Twitterでつぶやく"),
#else // JP
							_T("Tweet on Twitter"),
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
void CTweetWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		Tweet();
		break;
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CTweetWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(300, 240, FALSE);

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

	if(!m_edit.Create(m_hWnd, ES_MULTILINE | ES_WANTRETURN)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 140, 0);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(10, 10);
	m_edit.SetSize(280, 90);
	m_edit.Show(SW_SHOW);

	// ツイートボタンの作成
#if JP
	if(!m_tweetButton.Create(_T("ツイート"), m_hWnd, ID_OK, TRUE)) {
		m_rApp.ShowError(_T("ツイートボタンの作成に失敗しました。"));
#else // JP
	if(!m_tweetButton.Create(_T("Tweet"), m_hWnd, ID_OK, TRUE)) {
		m_rApp.ShowError(_T("failed to create Tweet button."));
#endif // JP
		return FALSE;
	}
	m_tweetButton.SetSize(90, 20);
	POINT pt;
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_tweetButton.SetPos(GetClientWidth() - 10 - m_tweetButton.GetWidth(),
		pt.y + 20);

	SetClientSize(GetClientWidth(), m_tweetButton.GetTop() +
				  m_tweetButton.GetHeight() + 10, FALSE);

	SetFocus(m_edit);

	// ファイル名を取得
	TCHAR chFileName[_MAX_FNAME];
	_tsplitpath_s(m_rMainWnd.GetSound().GetCurFileName().c_str(), NULL, 0, NULL,
		0, chFileName, _MAX_FNAME, NULL, 0);

	// タイトル
	m_rMainWnd.GetSound().StartReadTag(
		m_rMainWnd.GetSound().GetCurFileName().c_str());
	LPCSTR t = (LPCSTR)m_rMainWnd.GetSound().ReadTitleTag();
	TCHAR chTitle[255];
#ifdef UNICODE
	int cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, NULL, 0);
	wchar_t *wszTmp = new wchar_t[cchWC];
	memset(wszTmp, 0, cchWC * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, wszTmp, cchWC);
	_tcscpy_s(chTitle, cchWC + 1, wszTmp);
	delete[] wszTmp;
#else
	chTitle = t;
#endif
	if(lstrcmp(chTitle, _T("")) == 0) lstrcpy(chTitle, chFileName);

	// アーティスト
	t = (LPCSTR)m_rMainWnd.GetSound().ReadArtistTag();
	TCHAR chArtist[255];
#ifdef UNICODE
	cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, NULL, 0);
	wszTmp = new wchar_t[cchWC];
	memset(wszTmp, 0, cchWC * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, t, -1, wszTmp, cchWC);
	_tcscpy_s(chArtist, cchWC + 1, wszTmp);
	delete[] wszTmp;
#else
	chArtist = t;
#endif
	m_rMainWnd.GetSound().EndReadTag();

	tstring strTweet = _T("♪");
	strTweet = strTweet + chTitle;
	if(lstrcmp(chArtist, _T("")) != 0)
		strTweet = strTweet + _T(" / ") + chArtist;
	strTweet = strTweet + _T(" #NowPlaying #Hayaemon");
	m_edit.SetText(strTweet.c_str());

	// ショートカットキーを一時停止しておく
	if(m_pAccel) delete [] m_pAccel;
	m_nAccel = m_rApp.GetAccelTable().GetNum();
	m_pAccel = new ACCEL[m_nAccel];
	m_rApp.GetAccelTable().Copy(m_pAccel, m_nAccel);
	m_rApp.GetAccelTable().Destroy();

	Show(SW_SHOW);
	SetForegroundWindow(m_hWnd);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CTweetWnd::OnDestroy()
{
	if(m_pAccel) {
		m_rApp.GetAccelTable().Create(m_pAccel, m_nAccel);
		delete [] m_pAccel; m_pAccel = NULL;
	}
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// 秒数の設定
//----------------------------------------------------------------------------
void CTweetWnd::Tweet()
{
	char chMessage[1000];
	GetWindowTextA(m_edit, chMessage, 1000);
	std::string strMessage = chMessage;
	m_rMainWnd.Tweet(strMessage);
	Close();
}
//----------------------------------------------------------------------------
