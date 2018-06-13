//----------------------------------------------------------------------------
// PlayRangeWnd.h : 再生範囲設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef PlayRangeWndH
#define PlayRangeWndH

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
// 再生範囲設定用エディットボックスの管理を行うクラス
//----------------------------------------------------------------------------
class CEdit_PlayRange : public CEdit
{
public: // 関数

	CEdit_PlayRange(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_PlayRange() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// 再生範囲設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CPlayRangeWnd : public CFrameWnd
{
public: // 関数

	CPlayRangeWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_editStart(app, mainWnd),
		  m_editEnd(app, mainWnd) { }
	virtual ~CPlayRangeWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void SetNextFocus();
	virtual void SetRange();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_OkButton;
	CFont m_font;
	CEdit_PlayRange m_editStart;
	CEdit_PlayRange m_editEnd;
	CStatic m_label; // 「～」表示用ラベル

public: // 定数
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif