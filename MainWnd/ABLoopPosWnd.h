//----------------------------------------------------------------------------
// ABLoopPosWnd.h : ABループ位置設定用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef ABLoopPosWndH
#define ABLoopPosWndH

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
// ABループ位置設定用エディットボックスの管理を行うクラス
//----------------------------------------------------------------------------
class CEdit_ABLoopPos : public CEdit
{
public: // 関数

	CEdit_ABLoopPos(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_ABLoopPos() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// ABループ位置設定用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CABLoopPosWnd : public CFrameWnd
{
public: // 関数

	CABLoopPosWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd),
		  m_bLoopA(FALSE) { }
	virtual ~CABLoopPosWnd() { }

	virtual BOOL Create(BOOL bLoopA);

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void SetPos();

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_OkButton;
	CFont m_font;
	CEdit_ABLoopPos m_edit;

	BOOL m_bLoopA; // ABループ(A)かどうか（FALSEの場合、B）

public: // 定数
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif