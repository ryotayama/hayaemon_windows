//----------------------------------------------------------------------------
// Menu_MainWnd.cpp : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#include "Menu_MainWnd.h"
#include <cassert>
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CMenu_MainWnd::Create()
{
	CreateConnections();
	CreateActionMap();
	return TRUE;
}
//----------------------------------------------------------------------------
// 表示 → 音量メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVolumeMenuSelected(bool checked)
{
	m_rMainWnd.SetVolumeVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → パンメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPanMenuSelected(bool checked)
{
	m_rMainWnd.SetPanVisible(checked);
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
// メニューの項目のチェック状態を設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::CheckItem(UINT uIDCheckItem, UINT uCheck)
{
	auto it = m_actionMap.find(uIDCheckItem);
	assert(it != m_actionMap.end());
	if(it == m_actionMap.end()) {
		return;
	}
	it->second->setChecked(uCheck == MF_CHECKED);
}
//----------------------------------------------------------------------------
// メニューの項目のチェック状態を取得
//----------------------------------------------------------------------------
BOOL CMenu_MainWnd::IsItemChecked(UINT uID)
{
	auto it = m_actionMap.find(uID);
	assert(it != m_actionMap.end());
	if(it == m_actionMap.end()) {
		return FALSE;
	}
	return it->second->isChecked() ? TRUE : FALSE;
}
//----------------------------------------------------------------------------
// メニューの項目IDとQActionの対応付け
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateActionMap()
{
	m_actionMap = std::unordered_map<UINT, QAction*>{
		{ID_VOLUME, m_rMainWnd.actionVolumeVisible},
		{ID_PAN, m_rMainWnd.actionPanVisible},
	};
}
//----------------------------------------------------------------------------
// シグナル&スロットの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateConnections()
{
	// View
	connect(m_rMainWnd.actionVolumeVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnVolumeMenuSelected);
	connect(m_rMainWnd.actionPanVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnPanMenuSelected);
	// Play
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
