//----------------------------------------------------------------------------
// ToolBar_MainWnd.cpp : メインウィンドウ用ツールバーの作成・管理を行う
//----------------------------------------------------------------------------
#include "ToolBar_MainWnd.h"
#include <cassert>
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "PlayListView_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CToolBar_MainWnd::CToolBar_MainWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd), m_bRewinding(false),
		m_buttonMap({{ID_PLAY, m_rMainWnd.playButton},
								 {ID_PAUSE, m_rMainWnd.pauseButton},
								 {ID_STOP, m_rMainWnd.stopButton},
								 {ID_HEAD, m_rMainWnd.prevButton},
								 {ID_PREVMARKER, m_rMainWnd.prevMarkerButton},
								 {ID_NEXTMARKER, m_rMainWnd.nextMarkerButton},
								 {ID_NEXT, m_rMainWnd.nextButton},
								 {ID_SLOOP, m_rMainWnd.singleLoopButton},
								 {ID_ALOOP, m_rMainWnd.allLoopButton},
								 {ID_RANDOM, m_rMainWnd.randomPlayButton},
								 {ID_ABLOOP_A, m_rMainWnd.abLoopAButton},
								 {ID_ABLOOP_B, m_rMainWnd.abLoopBButton},
								 {ID_MARKERPLAY, m_rMainWnd.markerPlayButton},
								 {ID_ADDMARKER, m_rMainWnd.addMarkerButton},
								 {ID_DELETEMARKER, m_rMainWnd.deleteMarkerButton},
								 {ID_EXPLORER, m_rMainWnd.explorerButton},
								 {ID_PLAYLIST, m_rMainWnd.playlistButton}})
{
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CToolBar_MainWnd::Create()
{
	HideButton(ID_PREVMARKER, TRUE);
	HideButton(ID_NEXTMARKER, TRUE);
	HideButton(ID_PAUSE, TRUE);

	CreateConnections();

	return TRUE;
}
//----------------------------------------------------------------------------
// ＡＢループの状態を設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetABLoopState(BOOL bALoop, BOOL bBLoop)
{
	CheckButton(ID_ABLOOP_A, bALoop);
	CheckButton(ID_ABLOOP_B, bBLoop);
}
//----------------------------------------------------------------------------
// マーカー再生の状態を設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetMarkerPlayState(BOOL bMarkerPlay)
{
	CheckButton(ID_MARKERPLAY, bMarkerPlay);
	EnableButton(ID_SLOOP, !bMarkerPlay);
	EnableButton(ID_ALOOP, !bMarkerPlay);
	EnableButton(ID_RANDOM, !bMarkerPlay);
	EnableButton(ID_ABLOOP_A, !bMarkerPlay);
	EnableButton(ID_ABLOOP_B, !bMarkerPlay);

	HideButton(ID_HEAD, bMarkerPlay);
	HideButton(ID_PREVMARKER, !bMarkerPlay);
	HideButton(ID_NEXT, bMarkerPlay);
	HideButton(ID_NEXTMARKER, !bMarkerPlay);
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
// １曲ループの状態を設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetSingleLoopState(BOOL bSLoop)
{
	CheckButton(ID_SLOOP, bSLoop);
	EnableButton(ID_ALOOP, !bSLoop);
	EnableButton(ID_RANDOM, !bSLoop);
}
//----------------------------------------------------------------------------
// 頭出しボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnHeadButtonSelected()
{
	bool pressed = m_rMainWnd.prevButton->isDown();

	if(!pressed && !m_bRewinding) {
		if(m_rMainWnd.GetSound().ChannelGetSecondsPosition() < 1.0f) {
			if(m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM)) {
				if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
				   && m_rMainWnd.GetPlayList().GetMaxPlayOrder() == 1))
					m_rMainWnd.PlayPrevious();
			}
			else {
				if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
				   && m_rMainWnd.GetSound().GetCurFileNum() == 1))
					m_rMainWnd.PlayPrevious();
			}
		}
		else m_rMainWnd.Head();
	}
	else {
		if(!m_bRewinding) {
			m_bRewinding = true;
			m_rMainWnd.StartRewind();
		}
		if(!pressed) {
			m_rMainWnd.StopRewind();
			m_bRewinding = false;
		}
	}
}
//----------------------------------------------------------------------------
// 前のマーカーへボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPrevMarkerButtonSelected()
{
	bool pressed = m_rMainWnd.prevMarkerButton->isDown();

	if(!pressed && !m_bRewinding) {
		if(m_rMainWnd.GetSound().ChannelGetSecondsPosition()
		   < m_rMainWnd.GetSound().GetLoopPosA_sec() + 1.0f) {
			m_rMainWnd.SetPrevMarker();
		}
		else m_rMainWnd.Head();
	}
	else {
		if(!m_bRewinding) {
			m_bRewinding = true;
			m_rMainWnd.StartRewind();
		}
		if(!pressed) {
			m_rMainWnd.StopRewind();
			m_bRewinding = false;
		}
	}
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
// 次のマーカーへボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnNextMarkerButtonSelected()
{
	bool pressed = m_rMainWnd.nextMarkerButton->isDown();

	if(!pressed && !m_bRewinding) {
		m_rMainWnd.SetNextMarker();
	}
	else {
		if(!m_bRewinding) {
			m_bRewinding = true;
			m_rMainWnd.StartForward();
		}
		if(!pressed) {
			m_rMainWnd.StopForward();
			m_bRewinding = false;
		}
	}
}
//----------------------------------------------------------------------------
// 次へボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnNextButtonSelected()
{
	bool pressed = m_rMainWnd.nextButton->isDown();

	if(!pressed && !m_bRewinding) {
		if(m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM)) {
			if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetPlayList().GetMaxPlayOrder()
			   == m_rMainWnd.GetPlayList().GetItemCount()))
				m_rMainWnd.PlayNext(FALSE, FALSE);
		}
		else {
			if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetSound().GetCurFileNum()
			   == m_rMainWnd.GetPlayList().GetItemCount()))
				m_rMainWnd.PlayNext(FALSE, FALSE);
		}
	}
	else {
		if(!m_bRewinding) {
			m_bRewinding = true;
			m_rMainWnd.StartForward();
		}
		if(!pressed) {
			m_rMainWnd.StopForward();
			m_bRewinding = false;
		}
	}
}
//----------------------------------------------------------------------------
// １曲ループボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnSingleLoopButtonSelected()
{
	m_rMainWnd.SetSingleLoop();
}
//----------------------------------------------------------------------------
// 全曲ループボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnAllLoopButtonSelected(bool checked)
{
	m_rMainWnd.SetAllLoop(checked);
}
//----------------------------------------------------------------------------
// ランダム再生ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnRandomButtonSelected(bool checked)
{
	m_rMainWnd.SetRandom(checked);
}
//----------------------------------------------------------------------------
// ＡＢループ（Ａ）ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnABLoopAButtonSelected()
{
	m_rMainWnd.SetABLoopA();
}
//----------------------------------------------------------------------------
// ＡＢループ（Ｂ）ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnABLoopBButtonSelected()
{
	m_rMainWnd.SetABLoopB();
}
//----------------------------------------------------------------------------
// マーカー再生ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnMarkerPlayButtonSelected()
{
	m_rMainWnd.SetMarkerPlay();
}
//----------------------------------------------------------------------------
// マーカー追加ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnAddMarkerButtonSelected()
{
	m_rMainWnd.AddMarker();
}
//----------------------------------------------------------------------------
// マーカー削除ボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnDeleteMarkerButtonSelected()
{
	m_rMainWnd.DeleteMarker();
}
//----------------------------------------------------------------------------
// エクスプローラボタンが選択された
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnExplorerButtonSelected(bool checked)
{
	m_rMainWnd.SetExplorerVisible(checked);
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
// ボタンの状態を設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetState(int nID, UINT nState)
{
	auto it = m_buttonMap.find(nID);
	assert(it != m_buttonMap.end());
	if (it == m_buttonMap.end()) {
		return;
	}
	auto button = it->second;
	button->setDown((nState & TBSTATE_CHECKED) ? true : false);
	button->setEnabled((nState & TBSTATE_ENABLED) ? true : false);
}
//----------------------------------------------------------------------------
// 有効状態の設定
//----------------------------------------------------------------------------
void CToolBar_MainWnd::EnableButton(int nID, BOOL fEnable)
{
	auto it = m_buttonMap.find(nID);
	assert(it != m_buttonMap.end());
	if (it == m_buttonMap.end()) {
		return;
	}
	auto button = it->second;
	button->setEnabled(fEnable ? true : false);
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
	connect(m_rMainWnd.prevMarkerButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnPrevMarkerButtonSelected);
	connect(m_rMainWnd.prevButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnHeadButtonSelected);
	connect(m_rMainWnd.nextMarkerButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnNextMarkerButtonSelected);
	connect(m_rMainWnd.nextButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnNextButtonSelected);
	connect(m_rMainWnd.singleLoopButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnSingleLoopButtonSelected);
	connect(m_rMainWnd.allLoopButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnAllLoopButtonSelected);
	connect(m_rMainWnd.randomPlayButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnRandomButtonSelected);
	connect(m_rMainWnd.abLoopAButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnABLoopAButtonSelected);
	connect(m_rMainWnd.abLoopBButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnABLoopBButtonSelected);
	connect(m_rMainWnd.markerPlayButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnMarkerPlayButtonSelected);
	connect(m_rMainWnd.addMarkerButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnAddMarkerButtonSelected);
	connect(m_rMainWnd.deleteMarkerButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnDeleteMarkerButtonSelected);
	connect(m_rMainWnd.explorerButton, &QToolButton::clicked,
					this, &CToolBar_MainWnd::OnExplorerButtonSelected);
}
//----------------------------------------------------------------------------
