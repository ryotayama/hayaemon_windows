//----------------------------------------------------------------------------
// LAMECommandLineWnd.h : LAMEコマンドライン設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef LAMECommandLineWndH
#define LAMECommandLineWndH

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
// LAMEコマンドライン設定用エディットボックスの管理を行うクラス
//----------------------------------------------------------------------------
class CEdit_LAMECommandLine : public CEdit
{
public: // 関数

	CEdit_LAMECommandLine(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_LAMECommandLine() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// LAMEコマンドライン設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CLAMECommandLineWnd : public CFrameWnd
{
public: // 関数

	CLAMECommandLineWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd) { }
	virtual ~CLAMECommandLineWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void SetCommandLine();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_OkButton;
	CFont m_font;
	CEdit_LAMECommandLine m_edit;

public: // 定数
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif