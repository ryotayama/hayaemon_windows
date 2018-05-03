//----------------------------------------------------------------------------
// ToolBar_MainWnd.h : メインウィンドウ用ツールバーの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef ToolBar_MainWndH
#define ToolBar_MainWndH

class CMainWnd;
class QToolButton;
#include <unordered_map>
#include <QObject>
#include "../Common/Define.h"
//----------------------------------------------------------------------------
// メインウィンドウ用ツールバーの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CToolBar_MainWnd : public QObject
{
public: // 関数

	explicit CToolBar_MainWnd(CMainWnd & mainWnd);

	virtual BOOL Create();
	virtual void SetABLoopState(BOOL bALoop, BOOL bBLoop);
	virtual void SetMarkerPlayState(BOOL bMarkerPlay);
	virtual void SetPlayingState(BOOL bPlaying);
	virtual void SetPausingState(BOOL bPlaying);
	virtual void SetSingleLoopState(BOOL bSLoop);
	virtual void OnHeadButtonSelected();
	virtual void OnPrevMarkerButtonSelected();
	virtual void OnPlayButtonSelected();
	virtual void OnPauseButtonSelected();
	virtual void OnStopButtonSelected();
	virtual void OnNextMarkerButtonSelected();
	virtual void OnNextButtonSelected();
	virtual void OnSingleLoopButtonSelected();
	virtual void OnAllLoopButtonSelected(bool checked);
	virtual void OnRandomButtonSelected(bool checked);
	virtual void OnABLoopAButtonSelected();
	virtual void OnABLoopBButtonSelected();
	virtual void OnMarkerPlayButtonSelected();
	virtual void OnAddMarkerButtonSelected();
	virtual void OnDeleteMarkerButtonSelected();
	virtual void OnExplorerButtonSelected(bool checked);

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	bool m_bRewinding;

public: // Qtのラッパー

	virtual void CheckButton(int nID, BOOL fCheck);
	virtual void SetState(int nID, UINT nState);

private:

	virtual void EnableButton(int nID, BOOL fEnable);
	virtual void HideButton(int nID, BOOL fHide);
	void CreateConnections();

	const std::unordered_map<int, QToolButton *&> m_buttonMap;
};
//----------------------------------------------------------------------------

#endif
