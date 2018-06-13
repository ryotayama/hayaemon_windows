//----------------------------------------------------------------------------
// CountLoopWnd_MainWnd.h : 回数ループウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef CountLoopWnd_MainWndH
#define CountLoopWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ButtonExt.h"
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/EditExt.h"
#include "../Common/UpDownCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 回数ループウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CCountLoopWnd_MainWnd : public CFrameWnd
{
public: // 関数

	CCountLoopWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(*this),
		  m_OkButton(*this), m_CancelButton(*this), nFocus(0) { }
	virtual ~CCountLoopWnd_MainWnd() { }

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnReturnKeyPressed();
	virtual void OnSpaceKeyPressed();
	virtual void OnEscKeyPressed();
	virtual void SetNextFocus();
	virtual void SetPreviousFocus();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void OnVScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;
	CStatic m_label; // 「マーカー間を」表示用ラベル
	CStatic m_label2; // 「回ずつループさせる」表示用ラベル
	CFont m_font;
	CEditExt m_edit;
	CUpDownCtrl m_ud;

	int nFocus;

public: // 定数
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif