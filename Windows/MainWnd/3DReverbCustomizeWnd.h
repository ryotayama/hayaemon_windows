//----------------------------------------------------------------------------
// 3DReverbCustomizeWnd.h : ３Ｄリバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef Reverb3DCustomizeWndH
#define Reverb3DCustomizeWndH

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
// ３Ｄリバーブのカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class C3DReverbCustomizeWnd : public CFrameWnd
{
public: // 関数

	C3DReverbCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~C3DReverbCustomizeWnd();

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

	CStatic m_roomLabel; // 「ROOM:」表示用ラベル
	CEditExt m_roomEdit;
	CUpDownCtrl m_roomUd;

	CStatic m_roomHFLabel; // 「ROOM HF:」表示用ラベル
	CEditExt m_roomHFEdit;
	CUpDownCtrl m_roomHFUd;

	CStatic m_roomRolloffFactorLabel; // 「ROOM ROLLOFF FACTOR:」表示用ラベル
	CEditExt m_roomRolloffFactorEdit;
	CUpDownCtrl m_roomRolloffFactorUd;

	CStatic m_decayTimeLabel; // 「DECAY TIME:」表示用ラベル
	CEditExt m_decayTimeEdit;
	CUpDownCtrl m_decayTimeUd;

	CStatic m_decayHFRatioLabel; // 「DECAY HF RATIO:」表示用ラベル
	CEditExt m_decayHFRatioEdit;
	CUpDownCtrl m_decayHFRatioUd;

	CStatic m_reflectionsLabel; // 「REFLECTIONS:」表示用ラベル
	CEditExt m_reflectionsEdit;
	CUpDownCtrl m_reflectionsUd;

	CStatic m_reflectionsDelayLabel; // 「REFLECTIONS DELAY:」表示用ラベル
	CEditExt m_reflectionsDelayEdit;
	CUpDownCtrl m_reflectionsDelayUd;

	CStatic m_reverbLabel; // 「REVERB:」表示用ラベル
	CEditExt m_reverbEdit;
	CUpDownCtrl m_reverbUd;

	CStatic m_reverbDelayLabel; // 「REVERB DELAY:」表示用ラベル
	CEditExt m_reverbDelayEdit;
	CUpDownCtrl m_reverbDelayUd;

	CStatic m_diffusionLabel; // 「DIFFUSION:」表示用ラベル
	CEditExt m_diffusionEdit;
	CUpDownCtrl m_diffusionUd;

	CStatic m_densityLabel; // 「DENSITY:」表示用ラベル
	CEditExt m_densityEdit;
	CUpDownCtrl m_densityUd;

	CStatic m_hfReferenceLabel; // 「HF REFERENCE:」表示用ラベル
	CEditExt m_hfReferenceEdit;
	CUpDownCtrl m_hfReferenceUd;

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

#endif // Reverb3DCustomizeWndH