//----------------------------------------------------------------------------
// TweetWnd.h : 再生位置設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef TweetWndH
#define TweetWndH

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
// 再生位置設定用エディットボックスの管理を行うクラス
//----------------------------------------------------------------------------
class CEdit_Tweet : public CEdit
{
public: // 関数

	CEdit_Tweet(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_Tweet() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// 再生位置設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CTweetWnd : public CFrameWnd
{
public: // 関数

	CTweetWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd),
		  m_pAccel(NULL) { }
	virtual ~CTweetWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void Tweet();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_tweetButton;
	CFont m_font;
	CEdit_Tweet m_edit;

	int m_nAccel;
	ACCEL* m_pAccel;

public: // 定数
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif