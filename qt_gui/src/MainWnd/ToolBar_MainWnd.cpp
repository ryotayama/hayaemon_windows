//----------------------------------------------------------------------------
// ToolBar_MainWnd.cpp : メインウィンドウ用ツールバーの作成・管理を行う
//----------------------------------------------------------------------------
#include "ToolBar_MainWnd.h"
#include <cassert>
#include "MainWnd.h"

enum {
	ID_PLAY,
	ID_PAUSE,
	ID_STOP,
};
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CToolBar_MainWnd::CToolBar_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd),
		m_buttonMap({{ID_PLAY, m_rMainWnd.playButton},
								 {ID_PAUSE, m_rMainWnd.pauseButton},
								 {ID_STOP, m_rMainWnd.stopButton}})
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CToolBar_MainWnd::Create()
{
	HideButton(ID_PAUSE, TRUE);

	CreateConnections();

	return TRUE;
}
//----------------------------------------------------------------------------
// 再生状態を設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetPlayingState(BOOL bPlaying)
{
	HideButton(ID_PLAY, bPlaying);
	HideButton(ID_PAUSE, !bPlaying);
	CheckButton(ID_PAUSE, FALSE);
}
//----------------------------------------------------------------------------
// 一時停止状態を設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetPausingState(BOOL bPausing)
{
	CheckButton(ID_PAUSE, bPausing);
}
//----------------------------------------------------------------------------
// 再生ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPlayButtonSelected()
{
	m_rMainWnd.Play();
}
//----------------------------------------------------------------------------
// 一時停止ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPauseButtonSelected()
{
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 停止ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnStopButtonSelected()
{
	m_rMainWnd.Stop(FALSE);
}
//----------------------------------------------------------------------------
// チェック状態の設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::CheckButton(int nID, BOOL fCheck)
{
	auto it = m_buttonMap.find(nID);
	assert(it != m_buttonMap.end());
	if (it == m_buttonMap.end()) {
		return;
	}
	auto button = it->second;
	assert(button->isCheckable());
	button->setChecked(fCheck ? true : false);
}
//----------------------------------------------------------------------------
// 表示状態の設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::HideButton(int nID, BOOL fHide)
{
	auto it = m_buttonMap.find(nID);
	assert(it != m_buttonMap.end());
	if (it == m_buttonMap.end()) {
		return;
	}
	auto button = it->second;
	button->setVisible(fHide ? false : true);
}
//----------------------------------------------------------------------------
// シグナル&スロットの設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::CreateConnections()
{
	connect(m_rMainWnd.playButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnPlayButtonSelected);
	connect(m_rMainWnd.pauseButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnPauseButtonSelected);
	connect(m_rMainWnd.stopButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnStopButtonSelected);
}
//----------------------------------------------------------------------------
