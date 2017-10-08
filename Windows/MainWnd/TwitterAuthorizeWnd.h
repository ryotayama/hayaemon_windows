//----------------------------------------------------------------------------
// TwitterAuthorizeWnd.h : ツイッター認証用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef TwitterAuthorizeWndH
#define TwitterAuthorizeWndH

class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/Button.h"
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ツイッター認証用ウィンドウ内エディットボックスの管理を行うクラス
//----------------------------------------------------------------------------
class CEdit_TwitterAuthorize : public CEdit
{
public: // 関数

	CEdit_TwitterAuthorize(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_TwitterAuthorize() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// ツイッター認証用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CTwitterAuthorizeWnd : public CFrameWnd
{
public: // 関数

	CTwitterAuthorizeWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd) { }
	virtual ~CTwitterAuthorizeWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual bool ParseReply(const char *reply, std::string *token,
							std::string *secret);
	virtual void SetPin();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_okButton;
	CFont m_font;
	CEdit_TwitterAuthorize m_edit;
	CStatic m_label; // ブラウザ上で「許可する」をクリックしていただき、
					 // 表示された８桁のPINコードを入力してください。
	CStatic m_label2; // ブラウザ上で「許可する」をクリックしていただき、
					 // 表示された８桁のPINコードを入力してください。
	CStatic m_label3; // PINコード
	std::string t_key;
	std::string postarg;

public: // 定数
	enum {
		ID_OK = 100,
	};
};
//----------------------------------------------------------------------------

#endif