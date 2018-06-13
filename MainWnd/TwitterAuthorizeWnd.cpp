//----------------------------------------------------------------------------
// TwitterAuthorizeWnd.cpp : ツイッター認証用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "TwitterAuthorizeWnd.h"
#include "../Common/oauth.h"
#include "../Common/socket.h"
//----------------------------------------------------------------------------
// キーが押された
//----------------------------------------------------------------------------
void CEdit_TwitterAuthorize::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) m_rMainWnd.GetTwitterAuthorizeWnd().SetPin();
	else if(vk == VK_ESCAPE) m_rMainWnd.GetTwitterAuthorizeWnd().Close();
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTwitterAuthorizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("TwitterAuthorizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("TwitterAuthorizeWndCls"),
#if JP
							_T("ツイッター認証"),
#else // JP
							_T("Twitter Authorize"),
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
void CTwitterAuthorizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		SetPin();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CTwitterAuthorizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(260, 60, FALSE);

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

	if(!m_label.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label.SetParent(m_hWnd);
	m_label.SetFont(m_font, TRUE);
	m_label.SetPos(10, 10);
#if JP
	m_label.SetText(_T("ブラウザ上で「連携アプリを認証」をクリックして"));
#else // JP
	m_label.SetText(_T("Click the \"Authorize app\" button, please enter"));
#endif // JP
	m_label.SetSizeToTextSize();
	m_label.Show(SW_SHOW);

	if(!m_label2.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label2.SetParent(m_hWnd);
	m_label2.SetFont(m_font, TRUE);
	m_label2.SetPos(10, 10 + m_label.GetHeight());
#if JP
	m_label2.SetText(_T("いただき、表示されたPINコードを入力してください。"));
#else // JP
	m_label2.SetText(_T("the PIN in the edit box below."));
#endif // JP
	m_label2.SetSizeToTextSize();
	m_label2.Show(SW_SHOW);

	if(!m_label3.Create()) {
#if JP
		m_rApp.ShowError(_T("ラベルの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_label3.SetParent(m_hWnd);
	m_label3.SetFont(m_font, TRUE);
	m_label3.SetPos(10, 10 + m_label.GetHeight() + m_label2.GetHeight() + 10);
#if JP
	m_label3.SetText(_T("PINコード："));
#else // JP
	m_label3.SetText(_T("PIN Code:"));
#endif // JP
	m_label3.SetSizeToTextSize();
	m_label3.Show(SW_SHOW);

	if(!m_edit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("エディットコントロールの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_edit, EM_SETLIMITTEXT, 8, 0);
	m_edit.SetStyle(m_edit.GetStyle() | ES_RIGHT);
	m_edit.SetFont(m_font, TRUE);
	m_edit.SetPos(10 + m_label3.GetWidth() + 10, 10 + m_label.GetHeight() + m_label.GetHeight() + 10);
	m_edit.SetText(_T("12345678"));
	m_edit.SetSizeToTextSize();
	m_edit.SetText(_T(""));
	m_edit.Show(SW_SHOW);

	// OKボタンの作成
	if(!m_okButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OKボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_okButton.SetSize(90, 20);
	POINT pt;
	pt.y = m_edit.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_okButton.SetPos(GetClientWidth() - 10 - m_okButton.GetWidth(),
		pt.y + 20);

	SetClientSize(GetClientWidth(), m_okButton.GetTop() +
				  m_okButton.GetHeight() + 10, FALSE);

	SetFocus(m_edit);

	Show(SW_SHOW);
	SetForegroundWindow(m_hWnd);

	Socket::initialize();
	char *request_token_uri
		= "http://api.twitter.com/oauth/request_token";
	char *authorize_uri
		= "http://api.twitter.com/oauth/authorize";
	char *access_token_uri
		= "http://api.twitter.com/oauth/access_token";

	std::string c_key = "npkW3TKg8JqvELAlkqCfiA";
	std::string c_secret = "pl502twI6r6tkL7ApH2ElN9Hb1Un4qWvLNpb149IC8";

	std::string t_secret;

	std::string reply;
	std::string req_url = oauth_sign_url2(request_token_uri, &postarg,
		OA_HMAC, 0, c_key.c_str(), c_secret.c_str(), 0, 0);
	reply = oauth_http_post(req_url.c_str(),postarg.c_str(), false);

	ParseReply(reply.c_str(), &t_key, &t_secret);

	req_url = oauth_sign_url2(authorize_uri, 0, OA_HMAC, 0, c_key.c_str(),
		c_secret.c_str(), t_key.c_str(), t_secret.c_str());

	puts(req_url.c_str());

	ShellExecuteA(0, 0, req_url.c_str(), 0, 0, SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 破棄
//----------------------------------------------------------------------------
void CTwitterAuthorizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
bool CTwitterAuthorizeWnd::ParseReply(const char *reply, std::string *token,
	std::string *secret)
{
	std::vector<std::string> arr;

	char const *end = reply + strlen(reply);
	char const *left = reply;
	char const *right = left;
	while (1) {
		int c = 0;
		if (right < end) {
			c = *right;
		}
		if (c == 0 || c == '&') {
			std::string str(left, right);
			arr.push_back(str);
			if (c == 0) {
				break;
			}
			right++;
			left = right;
		}
		right++;
	}

	char const *oauth_token = 0;
	char const *oauth_token_secret = 0;

	for (std::vector<std::string>::const_iterator it = arr.begin(); it != arr.end(); it++) {
		if (strncmp(it->c_str(), "oauth_token=", 12) == 0) {
			oauth_token = it->c_str() + 12;
		} else if (strncmp(it->c_str(), "oauth_token_secret=", 19) == 0) {
			oauth_token_secret = it->c_str() + 19;
		}
	}

	if (oauth_token && oauth_token_secret) {
		if (token) {
			*token = oauth_token;
		}
		if (secret) {
			*secret = oauth_token_secret;
		}
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
// PINコードの設定
//----------------------------------------------------------------------------
void CTwitterAuthorizeWnd::SetPin()
{
	char *access_token_uri
		= "http://api.twitter.com/oauth/access_token";
	std::string c_key = "npkW3TKg8JqvELAlkqCfiA";
	std::string c_secret = "pl502twI6r6tkL7ApH2ElN9Hb1Un4qWvLNpb149IC8";

	std::string t_secret;
	int nCaptionLength = GetWindowTextLength(m_edit) + 1;
	char * pszCaption = new char[nCaptionLength];
	GetWindowTextA(m_edit, pszCaption, nCaptionLength);
	std::string strPin = pszCaption;
	delete [] pszCaption;
	std::string url = access_token_uri;
	url += "?oauth_verifier=";
	url += strPin;

	std::string req_url = oauth_sign_url2(url.c_str(), 0, OA_HMAC, 0,
		c_key.c_str(), 0, t_key.c_str(), 0);
	std::string reply = oauth_http_get(req_url.c_str(), postarg.c_str());

	if(!ParseReply(reply.c_str(), &t_key, &t_secret)) {
		MessageBox(0, _T("PINコードが間違っているようです。"), _T(""), 0);
		return;
	}
	std::string initFilePath = m_rApp.GetFilePathA() + "Setting.ini";
	WritePrivateProfileStringA("Twitter", "Key", t_key.c_str(), 
		initFilePath.c_str());
	WritePrivateProfileStringA("Twitter", "Secret", t_secret.c_str(), 
		initFilePath.c_str());
	Close();
	m_rMainWnd.Tweet();
}
//----------------------------------------------------------------------------
