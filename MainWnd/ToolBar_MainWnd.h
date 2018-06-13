//----------------------------------------------------------------------------
// ToolBar_MainWnd.h : メインウィンドウ用ツールバーの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef ToolBar_MainWndH
#define ToolBar_MainWndH

#include <commctrl.h>
class CApp;
class CMainWnd;
#include "../Common/ToolBar.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// メインウィンドウ用ツールバーの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CToolBar_MainWnd : public CToolBar
{
public: // 関数

	CToolBar_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), dwRewindClickTime(0) { }
	virtual ~CToolBar_MainWnd() { }

	virtual BOOL Create();
	virtual void SetABLoopState(BOOL bALoop, BOOL bBLoop);
	virtual void SetMarkerPlayState(BOOL bMarkerPlay);
	virtual void SetPlayingState(BOOL bPlaying);
	virtual void SetPausingState(BOOL bPlaying);
	virtual void SetSingleLoopState(BOOL bSLoop);
	virtual void SetSSize();
	virtual void SetMSize();
	virtual void SetLSize();
	virtual void OnHeadButtonSelected();
	virtual void OnPrevMarkerButtonSelected();
	virtual void OnOpenFileButtonSelected();
	virtual void OnPlayButtonSelected();
	virtual void OnPauseButtonSelected();
	virtual void OnStopButtonSelected();
	virtual void OnNextMarkerButtonSelected();
	virtual void OnNextButtonSelected();
	virtual void OnSingleLoopButtonSelected();
	virtual void OnAllLoopButtonSelected();
	virtual void OnRandomButtonSelected();
	virtual void OnABLoopAButtonSelected();
	virtual void OnABLoopBButtonSelected();
	virtual void OnMarkerPlayButtonSelected();
	virtual void OnAddMarkerButtonSelected();
	virtual void OnDeleteMarkerButtonSelected();
	virtual void OnPlayListButtonSelected();
	virtual void OnExplorerButtonSelected();

	// メッセージ
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);
	virtual void OnNeed_Text(int idFrom, TOOLTIPTEXT* pttt);
	virtual void OnBeginDrag(NMTOOLBAR* pnmtb);
	virtual void OnEndDrag(NMTOOLBAR* pnmtb);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	DWORD dwRewindClickTime;


public: // メンバ変数の取得・設定

	DWORD GetRewindClickTime() const { return dwRewindClickTime; }
};
//----------------------------------------------------------------------------

#endif