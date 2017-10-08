//----------------------------------------------------------------------------
// CompressorCustomizeWnd.h : コンプレッサのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef CompressorCustomizeWndH
#define CompressorCustomizeWndH

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
// コンプレッサーのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CCompressorCustomizeWnd : public CFrameWnd
{
public: // 関数

	CCompressorCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CCompressorCustomizeWnd();

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

	CStatic m_gainLabel; // 「GAIN:」表示用ラベル
	CEditExt m_gainEdit;
	CUpDownCtrl m_gainUd;

	CStatic m_attackLabel; // 「ATTACK:」表示用ラベル
	CEditExt m_attackEdit;
	CUpDownCtrl m_attackUd;

	CStatic m_releaseLabel; // 「RELEASE:」表示用ラベル
	CEditExt m_releaseEdit;
	CUpDownCtrl m_releaseUd;

	CStatic m_thresholdLabel; // 「THRESHOLD:」表示用ラベル
	CEditExt m_thresholdEdit;
	CUpDownCtrl m_thresholdUd;

	CStatic m_ratioLabel; // 「RATIO:」表示用ラベル
	CEditExt m_ratioEdit;
	CUpDownCtrl m_ratioUd;

	CStatic m_predelayLabel; // 「PREDELAY:」表示用ラベル
	CEditExt m_predelayEdit;
	CUpDownCtrl m_predelayUd;

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

#endif // CompressorCustomizeWndH