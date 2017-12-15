//----------------------------------------------------------------------------
// Menu_MainWnd.cpp : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#include "Menu_MainWnd.h"
#include <cassert>
#include <QActionGroup>
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CMenu_MainWnd::Create()
{
	CreateConnections();
	CreateActionMap();
	CreateActionGroups();
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
// 再生 → 再生速度 → デフォルトに戻すメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetSpeedMenuSelected()
{
	m_rMainWnd.ResetSpeed();
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 50%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed50MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(50.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 60%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed60MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(60.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 70%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed70MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(70.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 80%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed80MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(80.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 90%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed90MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(90.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 100%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed100MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(100.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 110%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed110MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(110.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 120%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed120MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(120.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 130%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed130MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(130.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 140%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed140MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(140.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 150%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed150MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(150.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 160%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed160MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(160.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 170%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed170MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(170.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 180%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed180MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(180.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 190%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed190MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(190.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 200%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed200MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(200.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 250%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed250MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(250.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 300%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed300MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(300.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 350%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed350MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(350.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 400%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed400MenuSelected()
{
	m_rMainWnd.GetSpeedLabel().SetSpeed(400.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 0.1%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown0_1SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(0.1);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 1%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(1);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 2%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown2SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(2);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 3%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown3SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(3);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 5%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown5SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(5);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 10%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown10SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(10);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 0.1%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp0_1SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(0.1);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 1%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(1);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 2%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp2SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(2);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 3%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp3SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(3);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 5%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp5SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(5);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 10%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp10SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(10);
}
//----------------------------------------------------------------------------
// システム → 再生速度 → 小数点桁数 → 0桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeedDecimal0MenuSelected()
{
	CheckItem(ID_SPEEDDEC_0, MF_CHECKED);
	CheckItem(ID_SPEEDDEC_1, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetSpeedLabel().SetDecimalDigit(0);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// システム → 再生速度 → 小数点桁数 → 1桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeedDecimal1MenuSelected()
{
	CheckItem(ID_SPEEDDEC_0, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_1, MF_CHECKED);
	CheckItem(ID_SPEEDDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetSpeedLabel().SetDecimalDigit(1);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// システム → 再生速度 → 小数点桁数 → 2桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeedDecimal2MenuSelected()
{
	CheckItem(ID_SPEEDDEC_0, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_1, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_2, MF_CHECKED);
	m_rMainWnd.GetSpeedLabel().SetDecimalDigit(2);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(2);
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
		{ID_SPEEDDEC_0, m_rMainWnd.actionSpeedDigit0},
		{ID_SPEEDDEC_1, m_rMainWnd.actionSpeedDigit1},
		{ID_SPEEDDEC_2, m_rMainWnd.actionSpeedDigit2},
	};
}
//----------------------------------------------------------------------------
// 排他的にチェックするアイテムのグループ化
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateActionGroups()
{
	auto speed_digit_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionSpeedDigit0,
											m_rMainWnd.actionSpeedDigit1,
											m_rMainWnd.actionSpeedDigit2}) {
		speed_digit_group->addAction(action);
	}
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
	// Effect - Speed
	connect(m_rMainWnd.actionResetSpeed, &QAction::triggered,
					this, &CMenu_MainWnd::OnResetSpeedMenuSelected);
	connect(m_rMainWnd.actionSetSpeed50, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed50MenuSelected);
	connect(m_rMainWnd.actionSetSpeed60, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed60MenuSelected);
	connect(m_rMainWnd.actionSetSpeed70, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed70MenuSelected);
	connect(m_rMainWnd.actionSetSpeed80, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed80MenuSelected);
	connect(m_rMainWnd.actionSetSpeed90, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed90MenuSelected);
	connect(m_rMainWnd.actionSetSpeed100, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed100MenuSelected);
	connect(m_rMainWnd.actionSetSpeed110, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed110MenuSelected);
	connect(m_rMainWnd.actionSetSpeed120, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed120MenuSelected);
	connect(m_rMainWnd.actionSetSpeed130, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed130MenuSelected);
	connect(m_rMainWnd.actionSetSpeed140, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed140MenuSelected);
	connect(m_rMainWnd.actionSetSpeed150, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed150MenuSelected);
	connect(m_rMainWnd.actionSetSpeed160, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed160MenuSelected);
	connect(m_rMainWnd.actionSetSpeed170, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed170MenuSelected);
	connect(m_rMainWnd.actionSetSpeed180, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed180MenuSelected);
	connect(m_rMainWnd.actionSetSpeed190, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed190MenuSelected);
	connect(m_rMainWnd.actionSetSpeed200, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed200MenuSelected);
	connect(m_rMainWnd.actionSetSpeed250, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed250MenuSelected);
	connect(m_rMainWnd.actionSetSpeed300, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed300MenuSelected);
	connect(m_rMainWnd.actionSetSpeed350, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed350MenuSelected);
	connect(m_rMainWnd.actionSetSpeed400, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetSpeed400MenuSelected);
	connect(m_rMainWnd.actionSpeedDown01, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown0_1SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedDown1, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown1SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedDown2, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown2SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedDown3, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown3SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedDown5, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown5SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedDown10, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown10SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedUp01, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp0_1SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedUp1, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp1SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedUp2, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp2SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedUp3, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp3SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedUp5, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp5SpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedUp10, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp10SpeedMenuSelected);
	// Effect - Speed - Decimal digit
	connect(m_rMainWnd.actionSpeedDigit0, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetSpeedDecimal0MenuSelected(); }
					});
	connect(m_rMainWnd.actionSpeedDigit1, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetSpeedDecimal1MenuSelected(); }
					});
	connect(m_rMainWnd.actionSpeedDigit2, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetSpeedDecimal2MenuSelected(); }
					});
	// Effect - Volume
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
