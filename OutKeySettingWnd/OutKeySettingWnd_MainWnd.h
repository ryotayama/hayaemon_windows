//----------------------------------------------------------------------------
// OutKeySettingWnd_MainWnd.h : グローバルホットキーカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef OutKeySettingWnd_MainWndH
#define OutKeySettingWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "./OutKeyInputWnd.h"
#include "../KeySettingWnd/KeySettingWnd_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// グローバルホットキーカスタマイズ用ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class COutKeySettingWnd_MainWnd : public CKeySettingWnd_MainWnd
{
public: // 関数

	COutKeySettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: CKeySettingWnd_MainWnd(app,mainWnd),
		  m_outKeyInputWnd(app, mainWnd, *this) {}
	virtual ~COutKeySettingWnd_MainWnd() { }

	virtual BOOL Create();
	virtual void Close();
	virtual void OnAddButtonClicked();
	virtual void OnChangeButtonClicked();
	virtual void OnDeleteButtonClicked();
	virtual void OnOkButtonClicked();
	virtual void ExecCurrentButtonFunc();
	virtual void SetNextFocus();
	virtual void SetPreviousFocus();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);


private: // メンバ変数

	COutKeyInputWnd m_outKeyInputWnd;

public: // メンバ変数の取得・設定

	CListView & GetList() { return m_List; }

};
//----------------------------------------------------------------------------

#endif