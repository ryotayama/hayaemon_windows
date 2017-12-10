//----------------------------------------------------------------------------
// Menu_MainWnd.cpp : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#include "Menu_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CMenu_MainWnd::Create()
{
	CreateConnections();
	return TRUE;
}
//----------------------------------------------------------------------------
// 再生 → 一時停止メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseMenuSelected()
{
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 再生 → 停止メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnStopMenuSelected()
{
	m_rMainWnd.Stop(FALSE);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → デフォルトに戻すメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetVolumeMenuSelected()
{
	m_rMainWnd.ResetVolume();
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 0%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume0MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(0.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 10%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume10MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(10.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 20%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume20MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(20.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 30%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume30MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(30.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 40%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume40MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(40.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 50%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume50MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(50.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 60%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume60MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(60.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 70%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume70MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(70.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 80%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume80MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(80.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 90%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume90MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(90.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 100%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume100MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(100.0);
}
//----------------------------------------------------------------------------
// シグナル&スロットの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateConnections()
{
	connect(m_rMainWnd.actionPlayPlayPause, &QAction::triggered,
					this, &CMenu_MainWnd::OnPauseMenuSelected);
	connect(m_rMainWnd.actionPlayStop, &QAction::triggered,
					this, &CMenu_MainWnd::OnStopMenuSelected);
	// Effect
	connect(m_rMainWnd.actionResetVolume, &QAction::triggered,
					this, &CMenu_MainWnd::OnResetVolumeMenuSelected);
	connect(m_rMainWnd.actionSetVolume0, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume0MenuSelected);
	connect(m_rMainWnd.actionSetVolume10, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume10MenuSelected);
	connect(m_rMainWnd.actionSetVolume20, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume20MenuSelected);
	connect(m_rMainWnd.actionSetVolume30, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume30MenuSelected);
	connect(m_rMainWnd.actionSetVolume40, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume40MenuSelected);
	connect(m_rMainWnd.actionSetVolume50, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume50MenuSelected);
	connect(m_rMainWnd.actionSetVolume60, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume60MenuSelected);
	connect(m_rMainWnd.actionSetVolume70, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume70MenuSelected);
	connect(m_rMainWnd.actionSetVolume80, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume80MenuSelected);
	connect(m_rMainWnd.actionSetVolume90, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume90MenuSelected);
	connect(m_rMainWnd.actionSetVolume100, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetVolume100MenuSelected);
}
//----------------------------------------------------------------------------
