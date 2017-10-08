//----------------------------------------------------------------------------
// DelayCustomizeWnd.h : ディレイのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef DelayCustomizeWndH
#define DelayCustomizeWndH

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
// ディレイのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CDelayCustomizeWnd : public CFrameWnd
{
public: // 関数

	CDelayCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CDelayCustomizeWnd();

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
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;

	CStatic m_wetDryMixLabel; // 「WET DRY MIX:」表示用ラベル
	CEditExt m_wetDryMixEdit;
	CUpDownCtrl m_wetDryMixUd;

	CStatic m_feedbackLabel; // 「FEEDBACK:」表示用ラベル
	CEditExt m_feedbackEdit;
	CUpDownCtrl m_feedbackUd;

	CStatic m_leftDelayLabel; // 「LEFT DELAY:」表示用ラベル
	CEditExt m_leftDelayEdit;
	CUpDownCtrl m_leftDelayUd;

	CStatic m_rightDelayLabel; // 「RIGHT DELAY:」表示用ラベル
	CEditExt m_rightDelayEdit;
	CUpDownCtrl m_rightDelayUd;

	CStatic m_panDelayLabel; // 「PAN DELAY:」表示用ラベル
	CEditExt m_panDelayEdit;
	CUpDownCtrl m_panDelayUd;

	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;

	int m_nFocus;

public: // 定数
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif // DelayCustomizeWndH