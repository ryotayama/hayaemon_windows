//----------------------------------------------------------------------------
// Menu_MainWnd.cpp : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#include "Menu_MainWnd.h"
#include <cassert>
#include <QActionGroup>
#include <QDesktopServices>
#include <QEventLoop>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include "../App.h"
#include "../Common/CommandList.h"
#include "../Common/Define.h"
#include "MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "Utility.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CMenu_MainWnd::CMenu_MainWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_presetMenu(mainWnd, m_actionMap)
{
}
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
// ＡＢループの状態を設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetABLoopState(BOOL bALoop, BOOL bBLoop)
{
	EnableItem(ID_SLOOP, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_ALOOP, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_RANDOM, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_MARKERPLAY, !(bALoop || bBLoop) ? MFS_ENABLED : 
		MFS_DISABLED);
	EnableItem(ID_ADDMARKER, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_DELETEMARKER, !(bALoop || bBLoop)
		? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_ABLOOP_A_SETTING, bALoop ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_ABLOOP_B_SETTING, bBLoop ? MFS_ENABLED : MFS_DISABLED);
}
//----------------------------------------------------------------------------
// ファイルが読み込まれたかどうかを設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetFileLoadState(BOOL bLoad)
{
	EnableItem(ID_SAVEFILE, bLoad ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_SAVEALLFILE, bLoad ? MFS_ENABLED : MFS_DISABLED);
}
//----------------------------------------------------------------------------
// ディレイの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetDelay(float fWetDryMix, float fFeedback,
		float fLeftDelay, float fRightDelay, BOOL lPanDelay, UINT uID)
{
	BOOL bDelay = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetDelay(fWetDryMix, fFeedback, fLeftDelay,
								  fRightDelay, lPanDelay, bDelay);
	m_rMainWnd.SetDelay(bDelay);
	UncheckDelayMenu();
	CheckItem(uID, bDelay ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// コーラスの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetChorus(float fWetDryMix, float fDepth, float fFeedback,
							  float fFreq, DWORD lWaveform, float fDelay,
							  DWORD lPhase, UINT uID)
{
	BOOL bChorus = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetChorus(fWetDryMix, fDepth, fFeedback, fFreq,
								   lWaveform, fDelay, lPhase, bChorus);
	m_rMainWnd.SetChorus(bChorus);
	UncheckChorusMenu();
	CheckItem(uID, bChorus ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// コンプレッサーの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetCompressor(float fGain, float fAttack, float fRelease,
								  float fThreshold, float fRatio,
								  float fPredelay, UINT uID)
{
	BOOL bCompressor = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetCompressor(fGain, fAttack, fRelease, fThreshold,
									   fRatio, fPredelay, bCompressor);
	m_rMainWnd.SetCompressor(bCompressor);
	UncheckCompressorMenu();
	CheckItem(uID, bCompressor ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// フランジャーの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetFlanger(float fWetDryMix, float fDepth, float fFeedback,
							   float fFreq, DWORD lWaveform, float fDelay,
							   DWORD lPhase, UINT uID)
{
	BOOL bFlanger = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetFlanger(fWetDryMix, fDepth, fFeedback, fFreq,
									lWaveform, fDelay, lPhase, bFlanger);
	m_rMainWnd.SetFlanger(bFlanger);
	UncheckFlangerMenu();
	CheckItem(uID, bFlanger ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ガーグルの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetGargle(DWORD dwRateHz, DWORD dwWaveShape, UINT uID)
{
	BOOL bGargle = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetGargle(dwRateHz, dwWaveShape, bGargle);
	m_rMainWnd.SetGargle(bGargle);
	UncheckGargleMenu();
	CheckItem(uID, bGargle ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ディストーションの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetDistortion(float fGain, float fEdge,
								  float fPostEQCenterFreq,
								  float fPostEQBandwidth,
								  float fPreLowpassCutoff, UINT uID)
{
	BOOL bDistortion = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetDistortion(fGain, fEdge, fPostEQCenterFreq,
									   fPostEQBandwidth, fPreLowpassCutoff,
									   bDistortion);
	m_rMainWnd.SetDistortion(bDistortion);
	UncheckDistortionMenu();
	CheckItem(uID, bDistortion ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// リバーブの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetReverb(float fInGain, float fReverbMix,
	float fReverbTime, float fHighFreqRTRatio, UINT uID)
{
	BOOL bReverb = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetReverb(fInGain, fReverbMix, fReverbTime,
									fHighFreqRTRatio, bReverb);
	m_rMainWnd.SetReverb(bReverb);
	UncheckReverbMenu();
	CheckItem(uID, bReverb ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ３Ｄリバーブの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::Set3DReverb(int lRoom, int lRoomHF,
	float flRoomRolloffFactor, float flDecayTime, float flDecayHFRatio,
	int lReflections, float flReflectionsDelay, int lReverb,
	float flReverbDelay, float flDiffusion, float flDensity,
	float flHFReference, UINT uID)
{
	BOOL bReverb = !IsItemChecked(uID);
	m_rMainWnd.GetSound().Set3DReverb(lRoom, lRoomHF, flRoomRolloffFactor, 
									  flDecayTime, flDecayHFRatio,
									  lReflections, flReflectionsDelay,
									  lReverb, flReverbDelay,  flDiffusion,
									  flDensity, flHFReference, bReverb);
	m_rMainWnd.Set3DReverb(bReverb);
	Uncheck3DReverbMenu();
	CheckItem(uID, bReverb ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// １曲ループの状態を設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetSingleLoopState(BOOL bSLoop)
{
	CheckItem(ID_SLOOP, bSLoop ? MF_CHECKED : MF_UNCHECKED);
	EnableItem(ID_ALOOP, bSLoop ? MFS_DISABLED : MFS_ENABLED);
	EnableItem(ID_RANDOM, bSLoop ? MFS_DISABLED : MFS_ENABLED);
}
//----------------------------------------------------------------------------
// EQ の表示状態を切り替える
//----------------------------------------------------------------------------
void CMenu_MainWnd::SwitchEQVisible(UINT uID)
{
	CheckItem(uID, IsItemChecked(uID) ? MF_UNCHECKED : MF_CHECKED);
}
//----------------------------------------------------------------------------
// メニューのチェック状態を切り替える
//----------------------------------------------------------------------------
void CMenu_MainWnd::SwitchItemChecked(UINT uID)
{
	BOOL bCheck = !IsItemChecked(uID);
	CheckItem(uID, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// コーラスメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckChorusMenu()
{
	CheckItem(ID_CHORUS_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_CHORUS_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// コンプレッサーメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckCompressorMenu()
{
	CheckItem(ID_COMPRESSOR_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_COMPRESSOR_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// エコーメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckDelayMenu()
{
	CheckItem(ID_DELAY_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_DELAY_SHORT, MF_UNCHECKED);
	CheckItem(ID_DELAY_MEDIUM, MF_UNCHECKED);
	CheckItem(ID_DELAY_LONG, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOSHORT, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOMEDIUM, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOLONG, MF_UNCHECKED);
	CheckItem(ID_DELAY_MOUNTAIN, MF_UNCHECKED);
	CheckItem(ID_DELAY_BIG, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOBIG, MF_UNCHECKED);
	CheckItem(ID_DELAY_DOUBLING, MF_UNCHECKED);
	CheckItem(ID_DELAY_DOUBLEKICK, MF_UNCHECKED);
	CheckItem(ID_DELAY_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ディストーションメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckDistortionMenu()
{
	CheckItem(ID_DISTORTION_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_DISTORTION_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// フランジャーメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckFlangerMenu()
{
	CheckItem(ID_FLANGER_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_FLANGER_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ガーグルメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckGargleMenu()
{
	CheckItem(ID_GARGLE_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_GARGLE_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// プリセットメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckPresetMenu()
{
	if(IsItemChecked(ID_RECORD)) return;
	if(IsItemChecked(ID_LOWBATTERY)) return;
	if(IsItemChecked(ID_NOSENSE)) return;
	if(IsItemChecked(ID_EARTRAINING)) return;
	int nCount = GetMenuItemCount(m_presetMenu);
	for(int i = 1; i <= nCount - 3; i++) CheckItem(ID_PRESET + i, MF_UNCHECKED);
	EnableItem(ID_DELETEPRESET, MFS_DISABLED);
}
//----------------------------------------------------------------------------
// リバーブメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckReverbMenu()
{
	CheckItem(ID_REVERB_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_REVERB_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 3Dリバーブメニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::Uncheck3DReverbMenu()
{
	CheckItem(ID_3DREVERB_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PADDEDCELL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_ROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_BATHROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_LIVINGROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_STONEROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_AUDITORIUM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CONCERTHALL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CAVE, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_ARENA, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_HANGAR, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CARPETEDHALLWAY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_HALLWAY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_STONECORRIDOR, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_ALLEY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_FOREST, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CITY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_MOUNTAINS, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_QUARRY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PLAIN, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PARKINGLOT, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_SEWERPIPE, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_UNDERWATER, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_SMALLROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_MEDIUMROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_LARGEROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_MEDIUMHALL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_LARGEHALL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PLATE, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 効果音メニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckSoundEffectMenu()
{
	CheckItem(ID_RECORDNOISE, MF_UNCHECKED);
	CheckItem(ID_WAVE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ファイル → 開くメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOpenFileMenuSelected()
{
	m_rMainWnd.ShowOpenFileDialog(TRUE);
}
//----------------------------------------------------------------------------
// ファイル → 追加メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddFileMenuSelected()
{
	m_rMainWnd.ShowOpenFileDialog(FALSE);
}
//----------------------------------------------------------------------------
// ファイル → フォルダを開くメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOpenFolderMenuSelected()
{
	m_rMainWnd.ShowOpenFolderDialog(TRUE);
}
//----------------------------------------------------------------------------
// ファイル → フォルダを追加メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddFolderMenuSelected()
{
	m_rMainWnd.ShowOpenFolderDialog(FALSE);
}
//----------------------------------------------------------------------------
// ファイル → URLを開くメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOpenURLMenuSelected()
{
	m_rMainWnd.ShowOpenURLWnd();
}
//----------------------------------------------------------------------------
// ファイル → URLを開くメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddURLMenuSelected()
{
	BOOL bAdd = TRUE;
	m_rMainWnd.ShowOpenURLWnd(bAdd);
}
//----------------------------------------------------------------------------
// ファイル → 保存メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSaveFileMenuSelected()
{
	m_rMainWnd.ShowSaveFileDialog();
}
//----------------------------------------------------------------------------
// ファイル → 一括変換メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSaveAllFileMenuSelected()
{
	m_rMainWnd.ShowSaveAllFileDialog();
}
//----------------------------------------------------------------------------
// ファイル → 終了メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnExitMenuSelected()
{
	m_rMainWnd.close();
}
//----------------------------------------------------------------------------
// 削除メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDeleteMenuSelected()
{
	m_rMainWnd.GetPlayList().DeleteSelectedItems();
}
//----------------------------------------------------------------------------
// すべてを選択メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSelectAllMenuSelected()
{
	m_rMainWnd.GetPlayList().SelectAll();
}
//----------------------------------------------------------------------------
// 表示 → 再生位置スライダメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTimeSliderMenuSelected(bool checked)
{
	m_rMainWnd.SetTimeSliderVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → エクスプローラメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnExplorerMenuSelected(bool checked)
{
	m_rMainWnd.SetExplorerVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → 再生速度メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSpeedMenuSelected(bool checked)
{
	m_rMainWnd.SetSpeedVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → 再生周波数メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFreqMenuSelected(bool checked)
{
	m_rMainWnd.SetFreqVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → 音程メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPitchMenuSelected(bool checked)
{
	m_rMainWnd.SetPitchVisible(checked);
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
// 表示 → グラフィックイコライザメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMenuSelected(bool checked)
{
	m_rMainWnd.SetEQVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → タブメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTabMenuSelected(bool checked)
{
	m_rMainWnd.SetTabVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → 再生リストメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayListMenuSelected(bool checked)
{
	m_rMainWnd.SetPlayListVisible(checked);
}
//----------------------------------------------------------------------------
// 表示 → 全てのコントロールを閉じるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCloseAllMenuSelected()
{
	if(IsItemChecked(ID_TIMESLIDER)) OnTimeSliderMenuSelected(false);
	if(IsItemChecked(ID_SPEED)) OnSpeedMenuSelected(false);
	if(IsItemChecked(ID_FREQ)) OnFreqMenuSelected(false);
	if(IsItemChecked(ID_PITCH)) OnPitchMenuSelected(false);
	if(IsItemChecked(ID_VOLUME)) OnVolumeMenuSelected(false);
	if(IsItemChecked(ID_PAN)) OnPanMenuSelected(false);
	if(IsItemChecked(ID_EQ)) OnEQMenuSelected(false);
	if(IsItemChecked(ID_PLAYLIST)) OnPlayListMenuSelected(false);
}
//----------------------------------------------------------------------------
// 再生 → 頭出しメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnHeadMenuSelected()
{
	m_rMainWnd.Head();
}
//----------------------------------------------------------------------------
// 再生 → 前へメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPreviousMenuSelected()
{
	if(!m_rMainWnd.IsMarkerPlay())
		m_rMainWnd.PlayPrevious();
	else
		m_rMainWnd.SetPrevMarker();
}
//----------------------------------------------------------------------------
// 再生 → 次へメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNextMenuSelected()
{
	if(!m_rMainWnd.IsMarkerPlay())
		m_rMainWnd.PlayNext(FALSE, FALSE);
	else
		m_rMainWnd.SetNextMarker();
}
//----------------------------------------------------------------------------
// 再生 → 一時停止メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseMenuSelected()
{
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 再生 → 巻き戻しメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRewindMenuSelected(bool checked)
{
	if(!checked) m_rMainWnd.StopRewind();
	else m_rMainWnd.StartRewind();
}
//----------------------------------------------------------------------------
// 再生 → 早送りメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForwardMenuSelected(bool checked)
{
	if(!checked) m_rMainWnd.StopForward();
	else m_rMainWnd.StartForward();
}
//----------------------------------------------------------------------------
// 再生 → 1秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn1SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(1);
}
//----------------------------------------------------------------------------
// 再生 → 2秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn2SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(2);
}
//----------------------------------------------------------------------------
// 再生 → 3秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn3SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(3);
}
//----------------------------------------------------------------------------
// 再生 → 5秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn5SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(5);
}
//----------------------------------------------------------------------------
// 再生 → 10秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn10SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(10);
}
//----------------------------------------------------------------------------
// 再生 → 1秒進むメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward1SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(1);
}
//----------------------------------------------------------------------------
// 再生 → 2秒進むメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward2SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(2);
}
//----------------------------------------------------------------------------
// 再生 → 3秒進むメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward3SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(3);
}
//----------------------------------------------------------------------------
// 再生 → 5秒進むメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward5SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(5);
}
//----------------------------------------------------------------------------
// 再生 → 10秒進むメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward10SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(10);
}
//----------------------------------------------------------------------------
// エフェクト → プリセット → 現在の設定を追加メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddPresetMenuSelected()
{
	m_rMainWnd.AddPreset();
}
//----------------------------------------------------------------------------
// エフェクト → プリセット → 選択中のプリセットを削除メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDeletePresetMenuSelected()
{
	m_rMainWnd.DeletePreset();
	UncheckPresetMenu();
	OnResetAllMenuSelected();
}
//----------------------------------------------------------------------------
// エフェクト → プリセットメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPresetMenuSelected(int id)
{
	if(!IsItemChecked(id)) {
		OnResetAllMenuSelected();
		UncheckPresetMenu();
	}
	else {
		OnResetAllMenuSelected();
		m_rMainWnd.SetPreset(id - ID_PRESET);
		UncheckPresetMenu();
		CheckItem(id, MF_CHECKED);
		EnableItem(ID_DELETEPRESET, MFS_ENABLED);
	}
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
// 再生 → 再生周波数 → デフォルトに戻すメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetFreqMenuSelected()
{
	m_rMainWnd.ResetFreq();
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 50%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq50MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(50.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 60%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq60MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(60.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 70%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq70MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(70.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 80%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq80MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(80.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 90%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq90MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(90.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 100%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq100MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(100.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 110%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq110MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(110.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 120%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq120MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(120.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 130%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq130MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(130.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 140%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq140MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(140.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 150%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq150MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(150.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 160%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq160MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(160.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 170%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq170MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(170.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 180%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq180MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(180.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 190%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq190MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(190.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 200%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq200MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(200.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 250%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq250MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(250.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 300%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq300MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(300.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 350%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq350MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(350.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 400%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq400MenuSelected()
{
	m_rMainWnd.GetFreqLabel().SetFreq(400.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 0.1%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown0_1FreqMenuSelected()
{
	m_rMainWnd.DownFreq(0.1);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 1%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1FreqMenuSelected()
{
	m_rMainWnd.DownFreq(1);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 2%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown2FreqMenuSelected()
{
	m_rMainWnd.DownFreq(2);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 3%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown3FreqMenuSelected()
{
	m_rMainWnd.DownFreq(3);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 5%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown5FreqMenuSelected()
{
	m_rMainWnd.DownFreq(5);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 10%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown10FreqMenuSelected()
{
	m_rMainWnd.DownFreq(10);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 0.1%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp0_1FreqMenuSelected()
{
	m_rMainWnd.UpFreq(0.1);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 1%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1FreqMenuSelected()
{
	m_rMainWnd.UpFreq(1);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 2%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp2FreqMenuSelected()
{
	m_rMainWnd.UpFreq(2);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 3%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp3FreqMenuSelected()
{
	m_rMainWnd.UpFreq(3);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 5%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp5FreqMenuSelected()
{
	m_rMainWnd.UpFreq(5);
}
//----------------------------------------------------------------------------
// 再生 → 再生周波数 → 10%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp10FreqMenuSelected()
{
	m_rMainWnd.UpFreq(10);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → デフォルトに戻すメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetPitchMenuSelected()
{
	m_rMainWnd.ResetPitch();
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭12メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat12MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-12.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭11メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat11MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-11.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭10メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat10MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-10.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭9メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat9MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-9.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭8メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat8MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-8.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭7メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat7MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-7.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭6メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat6MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-6.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭5メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat5MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-5.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭4メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat4MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-4.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭3メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat3MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-3.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭2メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat2MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-2.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭1メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat1MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(-1.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → 0メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchNaturalMenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(0.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯1メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp1MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(1.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯2メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp2MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(2.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯3メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp3MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(3.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯4メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp4MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(4.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯5メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp5MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(5.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯6メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp6MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(6.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯7メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp7MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(7.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯8メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp8MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(8.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯9メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp9MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(9.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯10メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp10MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(10.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯11メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp11MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(11.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯12メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp12MenuSelected()
{
	m_rMainWnd.GetPitchLabel().SetPitch(12.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 半音下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1PitchMenuSelected()
{
	m_rMainWnd.DownPitch(1);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 全音下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown2PitchMenuSelected()
{
	m_rMainWnd.DownPitch(2);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → １オクターブ下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1OctavePitchMenuSelected()
{
	m_rMainWnd.DownPitch(12);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 半音上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1PitchMenuSelected()
{
	m_rMainWnd.UpPitch(1);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 全音上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp2PitchMenuSelected()
{
	m_rMainWnd.UpPitch(2);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → １オクターブ上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1OctavePitchMenuSelected()
{
	m_rMainWnd.UpPitch(12);
}
//----------------------------------------------------------------------------
// 再生 → 停止メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnStopMenuSelected()
{
	m_rMainWnd.Stop(FALSE);
}
//----------------------------------------------------------------------------
// 再生 → １曲ループメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSingleLoopMenuSelected()
{
	m_rMainWnd.SetSingleLoop();
}
//----------------------------------------------------------------------------
// 再生 → 全曲ループメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAllLoopMenuSelected(bool checked)
{
	m_rMainWnd.SetAllLoop(checked);
}
//----------------------------------------------------------------------------
// 再生 → ランダム再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRandomMenuSelected(bool checked)
{
	m_rMainWnd.SetRandom(checked);
}
//----------------------------------------------------------------------------
// 再生 → 連続再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnContinueMenuSelected(bool checked)
{
	m_rMainWnd.SetContinue(checked);
}
//----------------------------------------------------------------------------
// 再生 → ＡＢループ（Ａ）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopAMenuSelected()
{
	m_rMainWnd.SetABLoopA();
}
//----------------------------------------------------------------------------
// 再生 → ＡＢループ（Ｂ）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopBMenuSelected()
{
	m_rMainWnd.SetABLoopB();
}
//----------------------------------------------------------------------------
// 再生 → ＡＢループ（Ａ）の位置設定メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopASettingMenuSelected()
{
	m_rMainWnd.SetABLoopASetting();
}
//----------------------------------------------------------------------------
// 再生 → ＡＢループ（Ｂ）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopBSettingMenuSelected()
{
	m_rMainWnd.SetABLoopBSetting();
}
//----------------------------------------------------------------------------
// 再生 → マーカー再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMarkerPlayMenuSelected()
{
	m_rMainWnd.SetMarkerPlay();
}
//----------------------------------------------------------------------------
// 再生 → マーカー追加メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddMarkerMenuSelected()
{
	m_rMainWnd.AddMarker();
}
//----------------------------------------------------------------------------
// 再生 → マーカー削除メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDeleteMarkerMenuSelected()
{
	m_rMainWnd.DeleteMarker();
}
//----------------------------------------------------------------------------
// 再生 → 回数ループメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCountLoopMenuSelected()
{
	m_rMainWnd.SetCountLoop();
}
//----------------------------------------------------------------------------
// 再生 → マーカー追加時にループメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnInstantLoopMenuSelected()
{
	m_rMainWnd.SetInstantLoop();
}
//----------------------------------------------------------------------------
// 再生 → マーカー位置変更時に再生位置変更メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPositionAutoMenuSelected()
{
	m_rMainWnd.SetPositionAuto();
}
//----------------------------------------------------------------------------
// 再生 → レコードノイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRecordNoiseMenuSelected()
{
	BOOL bRecordNoise = IsItemChecked(ID_RECORDNOISE);
	m_rMainWnd.SetRecordNoise(bRecordNoise);
}
//----------------------------------------------------------------------------
// 再生 → 波音メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnWaveMenuSelected()
{
	BOOL bWave = IsItemChecked(ID_WAVE);
	m_rMainWnd.SetWave(bWave);
}
//----------------------------------------------------------------------------
// 再生 → ノーマライズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNormalizeMenuSelected(bool checked)
{
	m_rMainWnd.SetNormalize(checked);
}
//----------------------------------------------------------------------------
// 再生 → ボーカルキャンセルメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVocalCancelMenuSelected(bool checked)
{
	m_rMainWnd.SetVocalCancel(checked);
}
//----------------------------------------------------------------------------
// 再生 → 逆回転再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverseMenuSelected(bool checked)
{
	m_rMainWnd.SetReverse(checked);
}
//----------------------------------------------------------------------------
// 再生 → 古びたレコード再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRecordMenuSelected(bool checked)
{
	CheckItem(ID_RECORD, !checked ? MF_CHECKED : MF_UNCHECKED);
	m_rMainWnd.SetRecord();
}
//----------------------------------------------------------------------------
// 再生 → エフェクト → 電池切れメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLowBatteryMenuSelected(bool checked)
{
	m_rMainWnd.SetLowBattery(checked);
}
//----------------------------------------------------------------------------
// 再生 → エフェクト → 歌へたモードメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNoSenseMenuSelected(bool checked)
{
	m_rMainWnd.SetNoSense(checked);
}
//----------------------------------------------------------------------------
// エフェクト → ベースの耳コピメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnBassCopyMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_BASSCOPY);
	OnBassCopyMenuSelected(bChecked);
}
void CMenu_MainWnd::OnBassCopyMenuSelected(bool bChecked)
{
	if(bChecked) {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(12.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos((LONG)(12 * pow(10.0,
			m_rMainWnd.GetPitchSlider().GetDecimalDigit())), TRUE);
		m_rMainWnd.SetPitch(12.0);
		m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30,
						 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
						 -30, -30, -30, -30);
	}
	else {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos(0L, TRUE);
		m_rMainWnd.SetPitch(0.0);
		OnEQFlatMenuSelected();
	}
	CheckItem(ID_BASSCOPY, bChecked ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// エフェクト → ドラム（ハイハット、シンバル）の耳コピメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDrumsCopyMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_CYMBALCOPY);
	OnDrumsCopyMenuSelected(bChecked);
}
void CMenu_MainWnd::OnDrumsCopyMenuSelected(bool bChecked)
{
	if(bChecked) {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos(0L, TRUE);
		m_rMainWnd.SetPitch(0.0);
		m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
						 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
						 -30, -30, 0, 0, 0, 0, 0, 0, 0);
	}
	else {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos(0L, TRUE);
		m_rMainWnd.SetPitch(0.0);
		OnEQFlatMenuSelected();
	}
	CheckItem(ID_CYMBALCOPY, bChecked ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 再生 → エフェクト → 聴覚トレーニングメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEarTrainingMenuSelected(bool checked)
{
	CheckItem(ID_EARTRAINING, !checked ? MF_CHECKED : MF_UNCHECKED);
	m_rMainWnd.SetEarTraining();
}
//----------------------------------------------------------------------------
// 再生 → モノラルメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMonoralMenuSelected(bool checked)
{
	m_rMainWnd.SetMonoral(checked);
}
//----------------------------------------------------------------------------
// 再生 → 左のみ再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOnlyLeftMenuSelected(bool checked)
{
	m_rMainWnd.SetOnlyLeft(checked);
}
//----------------------------------------------------------------------------
// 再生 → 右のみ再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOnlyRightMenuSelected(bool checked)
{
	m_rMainWnd.SetOnlyRight(checked);
}
//----------------------------------------------------------------------------
// 再生 → 左右入れ替えメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChangeLRMenuSelected(bool checked)
{
	m_rMainWnd.SetChangeLR(checked);
}
//----------------------------------------------------------------------------
// エフェクト → 全てデフォルトに戻すメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetAllMenuSelected()
{
	m_rMainWnd.SetRecordNoise(FALSE);
	m_rMainWnd.SetWave(FALSE);
	m_rMainWnd.ResetSpeed();
	m_rMainWnd.ResetFreq();
	m_rMainWnd.ResetPitch();
	OnEQFlatMenuSelected();
	m_rMainWnd.GetPanLabel().SetPan(0);
	m_rMainWnd.GetPanSlider().SetThumbPos(0);
	m_rMainWnd.SetPan(0);
	CheckItem(ID_REVERB_DEFAULT, MF_CHECKED);
	SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_DEFAULT);
	CheckItem(ID_3DREVERB_DEFAULT, MF_CHECKED);
	Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_DEFAULT);
	CheckItem(ID_DELAY_DEFAULT, MF_CHECKED);
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_DEFAULT);
	CheckItem(ID_CHORUS_DEFAULT, MF_CHECKED);
	SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
				ID_CHORUS_DEFAULT);
	CheckItem(ID_COMPRESSOR_DEFAULT, MF_CHECKED);
	SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
					ID_COMPRESSOR_DEFAULT);
	CheckItem(ID_FLANGER_DEFAULT, MF_CHECKED);
	SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
				ID_FLANGER_DEFAULT);
	CheckItem(ID_GARGLE_DEFAULT, MF_CHECKED);
	SetGargle(20, 0, ID_GARGLE_DEFAULT);
	CheckItem(ID_DISTORTION_DEFAULT, MF_CHECKED);
	SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
					ID_DISTORTION_DEFAULT);
	if(IsItemChecked(ID_NORMALIZE)) m_rMainWnd.SetNormalize();
	if(IsItemChecked(ID_VOCALCANCEL)) m_rMainWnd.SetVocalCancel();
	if(IsItemChecked(ID_REVERSE)) m_rMainWnd.SetReverse();
	if(IsItemChecked(ID_RECORD)) m_rMainWnd.SetRecord();
	if(IsItemChecked(ID_LOWBATTERY)) m_rMainWnd.SetLowBattery();
	if(IsItemChecked(ID_NOSENSE)) m_rMainWnd.SetNoSense();
	if(IsItemChecked(ID_EARTRAINING)) m_rMainWnd.SetEarTraining();
	if(IsItemChecked(ID_MONORAL)) m_rMainWnd.SetMonoral();
	if(IsItemChecked(ID_ONLYLEFT)) m_rMainWnd.SetOnlyLeft();
	if(IsItemChecked(ID_ONLYRIGHT)) m_rMainWnd.SetOnlyRight();
	if(IsItemChecked(ID_CHANGELR)) m_rMainWnd.SetChangeLR();
}
//----------------------------------------------------------------------------
// システム → 最大値／最小値設定メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLimitMenuSelected()
{
	m_rMainWnd.SetLimit();
}
//----------------------------------------------------------------------------
// システム → タイマー設定メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTimerPlayMenuSelected()
{
	m_rMainWnd.SetTimerPlay();
}
//----------------------------------------------------------------------------
// システム → 再生範囲メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayRangeMenuSelected()
{
	m_rMainWnd.SetPlayRange();
}
//----------------------------------------------------------------------------
// システム → 再生位置メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayPositionMenuSelected()
{
	m_rMainWnd.SetPlayPosition();
}
//----------------------------------------------------------------------------
// システム → 再生速度をだんだん遅くするメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDecSpeedMenuSelected()
{
	m_rMainWnd.SetDecSpeed();
}
//----------------------------------------------------------------------------
// システム → 再生速度をだんだん速くするメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnIncSpeedMenuSelected()
{
	m_rMainWnd.SetIncSpeed();
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
// システム → 再生周波数をだんだん遅くするメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDecFreqMenuSelected()
{
	m_rMainWnd.SetDecFreq();
}
//----------------------------------------------------------------------------
// システム → 再生周波数をだんだん速くするメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnIncFreqMenuSelected()
{
	m_rMainWnd.SetIncFreq();
}
//----------------------------------------------------------------------------
// システム → 再生周波数 → 小数点桁数 → 0桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreqDecimal0MenuSelected()
{
	CheckItem(ID_FREQDEC_0, MF_CHECKED);
	CheckItem(ID_FREQDEC_1, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetFreqLabel().SetDecimalDigit(0);
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// システム → 再生周波数 → 小数点桁数 → 1桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreqDecimal1MenuSelected()
{
	CheckItem(ID_FREQDEC_0, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_1, MF_CHECKED);
	CheckItem(ID_FREQDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetFreqLabel().SetDecimalDigit(1);
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// システム → 再生周波数 → 小数点桁数 → 2桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreqDecimal2MenuSelected()
{
	CheckItem(ID_FREQDEC_0, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_1, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_2, MF_CHECKED);
	m_rMainWnd.GetFreqLabel().SetDecimalDigit(2);
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(2);
}
//----------------------------------------------------------------------------
// システム → 音程 → 小数点桁数 → 0桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal0MenuSelected()
{
	CheckItem(ID_PITCHDEC_0, MF_CHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// システム → 音程 → 小数点桁数 → 1桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal1MenuSelected()
{
	CheckItem(ID_PITCHDEC_1, MF_CHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// システム → 音程 → 小数点桁数 → 2桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal2MenuSelected()
{
	CheckItem(ID_PITCHDEC_2, MF_CHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(2);
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
// システム → 停止時フェードアウト時間 → 1秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout1SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP1SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 2秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout2SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP2SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 3秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout3SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP3SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 4秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout4SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP4SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 5秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout5SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP5SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 6秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout6SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP6SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 7秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout7SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP7SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 8秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout8SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP8SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 9秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout9SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP9SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 10秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout10SecMenuSelected()
{
	CheckItem(ID_FADEOUTSTOP10SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 1秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext1SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT1SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 2秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext2SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT2SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 3秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext3SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT3SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 4秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext4SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT4SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 5秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext5SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT5SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 6秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext6SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT6SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 7秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext7SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT7SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 8秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext8SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT8SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 9秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext9SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT9SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 10秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext10SecMenuSelected()
{
	CheckItem(ID_FADEOUTNEXT10SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → メトロノームメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMetronomeMenuSelected()
{
	m_rMainWnd.SetMetronome();
}
//----------------------------------------------------------------------------
// システム → エフェクト → リバーブ → デフォルトメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverbDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_REVERB_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → リバーブ → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverbCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_REVERB_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_CUSTOMIZE);
	else m_rMainWnd.ShowReverbCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → デフォルトメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Padded Cellメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPaddedCellMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_PADDEDCELL, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -6000, 0.0f, 0.17f, 0.10f, -1204, 0.001f, 207, 0.002f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_PADDEDCELL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbRoomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_ROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -454, 0.0f, 0.4f, 0.83f, -1646, 0.002f, 53, 0.003f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Bathroomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbBathroomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_BATHROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -1200, 0.0f, 1.49f, 0.54f, -370, 0.007f, 1030, 0.011f,
			  100.0f, 60.0f, 5000.0f, ID_3DREVERB_BATHROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → LivingRoomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLivingRoomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_LIVINGROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -6000, 0.0f, 0.50f, 0.10f, -1376, 0.003f, -1104, 0.004f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LIVINGROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → StoneRoomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbStoneRoomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_STONEROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -300, 0.0f, 2.31f, 0.64f, -711, 0.012f, 83, 0.017f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_STONEROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Auditoriumメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbAuditoriumMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_AUDITORIUM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -476, 0.0f, 4.32f, 0.59f, -789, 0.020f, -289, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_AUDITORIUM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → ConcertHallメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbConcertHallMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_CONCERTHALL, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -500, 0.0f, 3.92f, 0.70f, -1230, 0.020f, -2, 0.029f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CONCERTHALL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Caveメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCaveMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_CAVE, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, 0, 0.0f, 2.91f, 1.30f, -602, 0.015f, -302, 0.022f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CAVE);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Arenaメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbArenaMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_ARENA, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -698, 0.0f, 7.24f, 0.33f, -1166, 0.020f, 16, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ARENA);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Hangarメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbHangarMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_HANGAR, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -1000, 0.0f,10.05f, 0.23f, -602, 0.020f, 198, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_HANGAR);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → CarpetedHallwayメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCarpetedHallwayMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_CARPETEDHALLWAY, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -4000, 0.0f, 0.30f, 0.10f, -1831, 0.002f, -1630, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CARPETEDHALLWAY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Hallwayメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbHallwayMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_HALLWAY, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -300, 0.0f, 1.49f, 0.59f, -1219, 0.007f, 441, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_HALLWAY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → StoneCorridorメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbStoneCorridorMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_STONECORRIDOR, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -237, 0.0f, 2.70f, 0.79f, -1214, 0.013f, 395, 0.020f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_STONECORRIDOR);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Alleyメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbAlleyMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_ALLEY, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -270, 0.0f, 1.49f, 0.86f, -1204, 0.007f, -4, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ALLEY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Forestメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbForestMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_FOREST, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -3300, 0.0f, 1.49f, 0.54f, -2560, 0.162f, -613, 0.088f,
			  79.0f, 100.0f, 5000.0f, ID_3DREVERB_FOREST);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Cityメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCityMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_CITY, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -800, 0.0f, 1.49f, 0.67f, -2273, 0.007f, -2217, 0.011f,
			  50.0f, 100.0f, 5000.0f, ID_3DREVERB_CITY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Mountainsメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMountainsMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_MOUNTAINS, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -2500, 0.0f, 1.49f, 0.21f, -2780, 0.300f, -2014, 0.100f,
			  27.0f, 100.0f, 5000.0f, ID_3DREVERB_MOUNTAINS);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Quarryメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbQuarryMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_QUARRY, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -1000, 0.0f, 1.49f, 0.83f,-10000, 0.061f, 500, 0.025f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_QUARRY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Plainメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPlainMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_PLAIN, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -2000, 0.0f, 1.49f, 0.50f, -2466, 0.179f, -2514, 0.100f,
			  21.0f, 100.0f, 5000.0f, ID_3DREVERB_PLAIN);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → ParkingLotメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbParkingLotMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_PARKINGLOT, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, 0, 0.0f, 1.65f, 1.50f, -1363, 0.008f, -1153, 0.012f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_PARKINGLOT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → SewerPipeメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbSewerPipeMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_SEWERPIPE, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -1000, 0.0f, 2.81f, 0.14f, 429, 0.014f, 648, 0.021f,
			  80.0f, 60.0f, 5000.0f, ID_3DREVERB_SEWERPIPE);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Underwaterメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbUnderwaterMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_UNDERWATER, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -4000, 0.0f, 1.49f, 0.10f, -449, 0.007f, 1700, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_UNDERWATER);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Small Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbSmallRoomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_SMALLROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -600, 0.0f, 1.10f, 0.83f, -400, 0.005f, 500, 0.010f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_SMALLROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Medium Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMediumRoomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_MEDIUMROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -600, 0.0f, 1.30f, 0.83f, -1000, 0.010f, -200, 0.020f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_MEDIUMROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Large Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLargeRoomMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_LARGEROOM, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -600, 0.0f, 1.50f, 0.83f, -1600, 0.020f, -1000, 0.040f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LARGEROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Medium Hallメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMediumHallMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_MEDIUMHALL, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -600, 0.0f, 1.80f, 0.70f, -1300, 0.015f, -800, 0.030f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_MEDIUMHALL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Large Hallメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLargeHallMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_LARGEHALL, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -600, 0.0f, 1.80f, 0.70f, -2000, 0.030f, -1400, 0.060f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LARGEHALL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Plateメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPlateMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_3DREVERB_PLATE, checked ? MF_UNCHECKED : MF_CHECKED);
	Set3DReverb(-1000, -200, 0.0f, 1.30f, 0.90f, 0, 0.002f, 0, 0.010f, 100.0f, 
			  75.0f, 5000.0f, ID_3DREVERB_PLATE);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_3DREVERB_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f,
					100.0f, 100.0f, 5000.0f, ID_3DREVERB_CUSTOMIZE);
	else m_rMainWnd.Show3DReverbCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Short Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayShortMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_SHORT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(15, 50, 150, 150, FALSE, ID_DELAY_SHORT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Medium Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayMediumMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_MEDIUM, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(15, 50, 300, 300, FALSE, ID_DELAY_MEDIUM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Long Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayLongMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_LONG, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(15, 50, 600, 600, FALSE, ID_DELAY_LONG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stereo Short Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoShortMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_STEREOSHORT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(15, 50, 300, 150, TRUE, ID_DELAY_STEREOSHORT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stetreo Medium Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoMediumMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_STEREOMEDIUM, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_STEREOMEDIUM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stereo Long Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoLongMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_STEREOLONG, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(15, 50, 1200, 600, TRUE, ID_DELAY_STEREOLONG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Mountain Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayMountainMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_MOUNTAIN, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(20, 0, 1500, 1500, FALSE, ID_DELAY_MOUNTAIN);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Big Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayBigMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_BIG, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(40, 50, 300, 300, FALSE, ID_DELAY_BIG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stereo Big Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoBigMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_STEREOBIG, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(40, 50, 600, 300, TRUE, ID_DELAY_STEREOBIG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Doublingメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDoublingMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_DOUBLING, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(100, 0, 31, 1, TRUE, ID_DELAY_DOUBLING);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Double Kickメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDoubleKickMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DELAY_DOUBLEKICK, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDelay(50, 0, 100, 100, FALSE, ID_DELAY_DOUBLEKICK);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_DELAY_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_CUSTOMIZE);
	else m_rMainWnd.ShowDelayCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Chorus → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChorusDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_CHORUS_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
			  ID_CHORUS_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Chorus → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChorusCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_CHORUS_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
				  ID_CHORUS_CUSTOMIZE);
	else m_rMainWnd.ShowChorusCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Compressor → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCompressorDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_COMPRESSOR_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
				  ID_COMPRESSOR_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Compressor → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCompressorCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_COMPRESSOR_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
					  ID_COMPRESSOR_CUSTOMIZE);
	else m_rMainWnd.ShowCompressorCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Flanger → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFlangerDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_FLANGER_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
			   ID_FLANGER_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Flanger → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFlangerCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_FLANGER_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
				   ID_FLANGER_CUSTOMIZE);
	else m_rMainWnd.ShowFlangerCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Gargle → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnGargleDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_GARGLE_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetGargle(20, 0, ID_GARGLE_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Gargle → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnGargleCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_GARGLE_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetGargle(20, 0, ID_GARGLE_CUSTOMIZE);
	else m_rMainWnd.ShowGargleCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Distortion → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDistortionDefaultMenuSelected(bool checked /* = true */)
{
	CheckItem(ID_DISTORTION_DEFAULT, checked ? MF_UNCHECKED : MF_CHECKED);
	SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
				  ID_DISTORTION_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Distortion → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDistortionCustomizeMenuSelected(bool checked)
{
	CheckItem(ID_DISTORTION_CUSTOMIZE, checked ? MF_UNCHECKED : MF_CHECKED);
	if(!checked)
		SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
					  ID_DISTORTION_CUSTOMIZE);
	else m_rMainWnd.ShowDistortionCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → EQプリセット → FLATメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQFlatMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音強調（超最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowSuperMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, -30, -30, -30);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音強調（最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowHighestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, -15, -15, -15);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音強調（強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowHighMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, -12, -12, -12);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音強調（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9, -9, -9, -9, -9,
					 -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音強調（弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowLowMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, -6, -6, -6, -6,
					 -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音強調（最弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowLowestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, -3,
					 -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音強調（超最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleSuperMenuSelected()
{
	m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音強調（最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleHighestMenuSelected()
{
	m_rMainWnd.SetEQ(-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音強調（強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleHighMenuSelected()
{
	m_rMainWnd.SetEQ(-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音強調（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音強調（弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleLowMenuSelected()
{
	m_rMainWnd.SetEQ(-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音強調（最弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleLowestMenuSelected()
{
	m_rMainWnd.SetEQ(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音強調（超最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighSuperMenuSelected()
{
	m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音強調（最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighHighestMenuSelected()
{
	m_rMainWnd.SetEQ(-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音強調（強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighHighMenuSelected()
{
	m_rMainWnd.SetEQ(-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音強調（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
					 -9, -9, -9, -9, -9, -9, -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音強調（弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighLowMenuSelected()
{
	m_rMainWnd.SetEQ(-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
					 -6, -6, -6, -6, -6, -6, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音強調（最弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighLowestMenuSelected()
{
	m_rMainWnd.SetEQ(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
					 -3, -3, -3, -3, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音カット（超最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutSuperMenuSelected()
{
	m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音カット（最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutHighestMenuSelected()
{
	m_rMainWnd.SetEQ(-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音カット（強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutHighMenuSelected()
{
	m_rMainWnd.SetEQ(-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音カット（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
					 -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音カット（弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutLowMenuSelected()
{
	m_rMainWnd.SetEQ(-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
					 -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 低音カット（最弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutLowestMenuSelected()
{
	m_rMainWnd.SetEQ(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
					 -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音カット（超最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutSuperMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音カット（最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutHighestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音カット（強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutHighMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音カット（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9, -9, -9, -9, -9,
					 -9, -9, -9, -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音カット（弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutLowMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, -6, -6, -6, -6,
					 -6, -6, -6, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 中音カット（最弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutLowestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, -3,
					 -3, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音カット（超最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutSuperMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音カット（最強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutHighestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音カット（強）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutHighMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音カット（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音カット（弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutLowMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6);
}
//----------------------------------------------------------------------------
// システム → EQプリセット → 高音カット（最弱）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutLowestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3);
}
//----------------------------------------------------------------------------
// システム → 最前面表示メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTopMostMenuSelected()
{
	m_rMainWnd.SetTopMost();
}
//----------------------------------------------------------------------------
// システム → 現在の再生位置をクリップボードにコピーメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCopyTimeMenuSelected()
{
	m_rMainWnd.CopyTime();
}
//----------------------------------------------------------------------------
// ヘルプ → マニュアルメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnManualMenuSelected()
{
	QString lang = QLocale().name();
	lang.truncate(lang.lastIndexOf('_'));
	if (lang == "ja") {
		QDesktopServices::openUrl(
			QUrl("http://soft.edolfzoku.com/hayaemon2/manual.html"));
	} else {
		QString manualPath = m_rApp.GetFilePath() + "manual\\index.html";
		QDesktopServices::openUrl("file:///" + manualPath);
	}
}
//----------------------------------------------------------------------------
// ヘルプ → アップデートの確認メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUpdateCheckMenuSelected()
{
	QNetworkAccessManager manager;
	if (manager.networkAccessible() == QNetworkAccessManager::NotAccessible) {
		QMessageBox::warning(&m_rMainWnd, tr("Offline"),
				tr("Failed to connect to the Internet."));
		return;
	}
	QString strVersion = m_rApp.GetVersionInfo();
	strVersion.replace(".", "");
	int nPos = strVersion.indexOf(u8"β", 0);
	QString strFileName = "Hayaemon";
	if(nPos > 0) {
		int nNextVersion = strVersion.left(nPos).toInt() + 1;
		QString chVersion = QString("%1").arg(nNextVersion);
		strFileName += chVersion + ".zip";
	}
	else {
		int nNextVersion = strVersion.left(nPos).toInt() + 2;
		QString chVersion = QString("%1").arg(nNextVersion);
		strFileName += chVersion + ".zip";
	}
	QUrl url("http://soft.edolfzoku.com/hayaemon2/" + strFileName);
	QEventLoop loop;
	connect(&manager, SIGNAL(finished(QNetworkReply *)), &loop, SLOT(quit()));
	auto header = manager.head(QNetworkRequest(url));
	loop.exec();

	QVariant len = header->header(QNetworkRequest::ContentLengthHeader);
	if(len.toLongLong() > 2000000) {
		int nButton = QMessageBox::question(nullptr, tr("Question"),
			tr("The latest version has been released.\n"
				 "Do you want to access the official site?"));
		if(nButton == QMessageBox::Yes) {
			QString lang = QLocale().name();
			lang.truncate(lang.lastIndexOf('_'));
			QUrl url2;
			if (lang == "ja") {
				url2 = "http://soft.edolfzoku.com/hayaemon2/";
			} else {
				url2 = "http://en.edolfzoku.com/hayaemon2/";
			}
			QDesktopServices::openUrl(url2);
		}
	}
	else {
		QMessageBox::information(nullptr, tr("Information"),
			tr("Your version is latest."));
	}
}
//----------------------------------------------------------------------------
// ヘルプ → バージョン情報メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVersionInfoMenuSelected()
{
	QString str = m_rApp.GetName() + " ";
	QString strVersion = m_rApp.GetVersionInfo();
	int nPos = strVersion.indexOf("β", 0);
	if(nPos > 0) {
		str += "Version " + strVersion.left(nPos);
		str += " β ";
		str += strVersion.mid(nPos + 1);
	}
	else {
		str += "Version " + strVersion +
			   tr(" stable");
	}
	str += "\n\n  " + m_rApp.GetAuthorName()
		+ " <" + m_rApp.GetAuthorEMail() + ">\n  "
		+ m_rApp.GetAuthorWebSiteName() + " : " + m_rApp.GetAuthorURL();

	str += "\n\n"
				 "  This software is built using Qt " QT_VERSION_STR ".\n"
				 "  Qt is licensed under terms of the GNU LGPLv3.";

	QMessageBox msgbox;
	msgbox.setWindowTitle(tr("Version"));
	msgbox.setText(str);
	auto horizontalSpacer = new QSpacerItem(
		600, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	auto layout = (QGridLayout*)msgbox.layout();
	layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
	msgbox.exec();
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
// メニューの項目の有効/無効を設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::EnableItem(UINT uIDEnableItem, UINT uEnable)
{
	auto it = m_actionMap.find(uIDEnableItem);
	assert(it != m_actionMap.end());
	if(it == m_actionMap.end()) {
		return;
	}
	it->second->setEnabled(uEnable == MFS_ENABLED);
}
//----------------------------------------------------------------------------
// メニューの項目IDとQActionの対応付け
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateActionMap()
{
	m_actionMap = std::unordered_map<UINT, QAction*>{
		{ID_SAVEFILE, m_rMainWnd.actionFileSave},
		{ID_SAVEALLFILE, m_rMainWnd.actionFileSaveAll},
		{ID_TIMESLIDER, m_rMainWnd.actionTimeSliderVisible},
		{ID_EXPLORER, m_rMainWnd.actionExplorerVisible},
		{ID_SPEED, m_rMainWnd.actionSpeedVisible},
		{ID_FREQ, m_rMainWnd.actionFreqVisible},
		{ID_PITCH, m_rMainWnd.actionPitchVisible},
		{ID_VOLUME, m_rMainWnd.actionVolumeVisible},
		{ID_PAN, m_rMainWnd.actionPanVisible},
		{ID_EQ, m_rMainWnd.actionEQVisible},
		{ID_TAB, m_rMainWnd.actionTabVisible},
		{ID_PLAYLIST, m_rMainWnd.actionPlaylistVisible},
		{ID_HEAD, m_rMainWnd.actionHead},
		{ID_PREV, m_rMainWnd.actionPrevious},
		{ID_NEXT, m_rMainWnd.actionNext},
		{ID_REWIND, m_rMainWnd.actionRewind},
		{ID_FORWARD, m_rMainWnd.actionForward},
		{ID_SLOOP, m_rMainWnd.actionSingleLoop},
		{ID_ALOOP, m_rMainWnd.actionAllLoop},
		{ID_RANDOM, m_rMainWnd.actionRandomPlay},
		{ID_CONTINUE, m_rMainWnd.actionContinuousPlay},
		{ID_SAMEARTIST, m_rMainWnd.actionSameArtist},
		{ID_ABLOOP_A_SETTING, m_rMainWnd.actionABLoopAPosSetting},
		{ID_ABLOOP_B_SETTING, m_rMainWnd.actionABLoopBPosSetting},
		{ID_MARKERPLAY, m_rMainWnd.actionMarkerPlay},
		{ID_ADDMARKER, m_rMainWnd.actionAddMarker},
		{ID_DELETEMARKER, m_rMainWnd.actionDeleteMarker},
		{ID_COUNTLOOP, m_rMainWnd.actionCountLoop},
		{ID_INSTANTLOOP, m_rMainWnd.actionInstantLoop},
		{ID_SETPOSITIONAUTO, m_rMainWnd.actionSetMarkerPositionAuto},
		{ID_DECSPEED, m_rMainWnd.actionSpeedDecrease},
		{ID_INCSPEED, m_rMainWnd.actionSpeedIncrease},
		{ID_DECFREQ, m_rMainWnd.actionFreqDecrease},
		{ID_INCFREQ, m_rMainWnd.actionFreqIncrease},
		{ID_SPEEDDEC_0, m_rMainWnd.actionSpeedDigit0},
		{ID_SPEEDDEC_1, m_rMainWnd.actionSpeedDigit1},
		{ID_SPEEDDEC_2, m_rMainWnd.actionSpeedDigit2},
		{ID_FREQDEC_0, m_rMainWnd.actionFreqDigit0},
		{ID_FREQDEC_1, m_rMainWnd.actionFreqDigit1},
		{ID_FREQDEC_2, m_rMainWnd.actionFreqDigit2},
		{ID_PITCHDEC_0, m_rMainWnd.actionPitchDigit0},
		{ID_PITCHDEC_1, m_rMainWnd.actionPitchDigit1},
		{ID_PITCHDEC_2, m_rMainWnd.actionPitchDigit2},
		{ID_DELETEPRESET, m_rMainWnd.actionPresetDelete},
		{ID_REVERB_DEFAULT, m_rMainWnd.actionReverbDefault},
		{ID_REVERB_CUSTOMIZE, m_rMainWnd.actionReverbCustomize},
		{ID_3DREVERB_DEFAULT, m_rMainWnd.action3DReverbDefault},
		{ID_3DREVERB_PADDEDCELL, m_rMainWnd.action3DReverbPaddedCell},
		{ID_3DREVERB_ROOM, m_rMainWnd.action3DReverbRoom},
		{ID_3DREVERB_BATHROOM, m_rMainWnd.action3DReverbBathroom},
		{ID_3DREVERB_LIVINGROOM, m_rMainWnd.action3DReverbLivingRoom},
		{ID_3DREVERB_STONEROOM, m_rMainWnd.action3DReverbStoneRoom},
		{ID_3DREVERB_AUDITORIUM, m_rMainWnd.action3DReverbAuditorium},
		{ID_3DREVERB_CONCERTHALL, m_rMainWnd.action3DReverbConcertHall},
		{ID_3DREVERB_CAVE, m_rMainWnd.action3DReverbCave},
		{ID_3DREVERB_ARENA, m_rMainWnd.action3DReverbArena},
		{ID_3DREVERB_HANGAR, m_rMainWnd.action3DReverbHangar},
		{ID_3DREVERB_CARPETEDHALLWAY, m_rMainWnd.action3DReverbCarpetedHallway},
		{ID_3DREVERB_HALLWAY, m_rMainWnd.action3DReverbHallway},
		{ID_3DREVERB_STONECORRIDOR, m_rMainWnd.action3DReverbStoneCorridor},
		{ID_3DREVERB_ALLEY, m_rMainWnd.action3DReverbAlley},
		{ID_3DREVERB_FOREST, m_rMainWnd.action3DReverbForest},
		{ID_3DREVERB_CITY, m_rMainWnd.action3DReverbCity},
		{ID_3DREVERB_MOUNTAINS, m_rMainWnd.action3DReverbMountains},
		{ID_3DREVERB_QUARRY, m_rMainWnd.action3DReverbQuarry},
		{ID_3DREVERB_PLAIN, m_rMainWnd.action3DReverbPlain},
		{ID_3DREVERB_PARKINGLOT, m_rMainWnd.action3DReverbParkingLot},
		{ID_3DREVERB_SEWERPIPE, m_rMainWnd.action3DReverbSewerPipe},
		{ID_3DREVERB_UNDERWATER, m_rMainWnd.action3DReverbUnderwater},
		{ID_3DREVERB_SMALLROOM, m_rMainWnd.action3DReverbSmallRoom},
		{ID_3DREVERB_MEDIUMROOM, m_rMainWnd.action3DReverbMediumRoom},
		{ID_3DREVERB_LARGEROOM, m_rMainWnd.action3DReverbLargeRoom},
		{ID_3DREVERB_MEDIUMHALL, m_rMainWnd.action3DReverbMediumHall},
		{ID_3DREVERB_LARGEHALL, m_rMainWnd.action3DReverbLargeHall},
		{ID_3DREVERB_PLATE, m_rMainWnd.action3DReverbPlate},
		{ID_3DREVERB_CUSTOMIZE, m_rMainWnd.action3DReverbCustomize},
		{ID_DELAY_DEFAULT, m_rMainWnd.actionDelayDefault},
		{ID_DELAY_SHORT, m_rMainWnd.actionDelayShort},
		{ID_DELAY_MEDIUM, m_rMainWnd.actionDelayMedium},
		{ID_DELAY_LONG, m_rMainWnd.actionDelayLong},
		{ID_DELAY_STEREOSHORT, m_rMainWnd.actionDelayStereoShort},
		{ID_DELAY_STEREOMEDIUM, m_rMainWnd.actionDelayStereoMedium},
		{ID_DELAY_STEREOLONG, m_rMainWnd.actionDelayStereoLong},
		{ID_DELAY_MOUNTAIN, m_rMainWnd.actionDelayMountain},
		{ID_DELAY_BIG, m_rMainWnd.actionDelayBig},
		{ID_DELAY_STEREOBIG, m_rMainWnd.actionDelayStereoBig},
		{ID_DELAY_DOUBLING, m_rMainWnd.actionDelayDoubling},
		{ID_DELAY_DOUBLEKICK, m_rMainWnd.actionDelayDoubleKick},
		{ID_DELAY_CUSTOMIZE, m_rMainWnd.actionDelayCustomize},
		{ID_CHORUS_DEFAULT, m_rMainWnd.actionChorusDefault},
		{ID_CHORUS_CUSTOMIZE, m_rMainWnd.actionChorusCustomize},
		{ID_COMPRESSOR_DEFAULT, m_rMainWnd.actionCompressorDefault},
		{ID_COMPRESSOR_CUSTOMIZE, m_rMainWnd.actionCompressorCustomize},
		{ID_FLANGER_DEFAULT, m_rMainWnd.actionFlangerDefault},
		{ID_FLANGER_CUSTOMIZE, m_rMainWnd.actionFlangerCustomize},
		{ID_GARGLE_DEFAULT, m_rMainWnd.actionGargleDefault},
		{ID_GARGLE_CUSTOMIZE, m_rMainWnd.actionGargleCustomize},
		{ID_DISTORTION_DEFAULT, m_rMainWnd.actionDistortionDefault},
		{ID_DISTORTION_CUSTOMIZE, m_rMainWnd.actionDistortionCustomize},
		{ID_RECORDNOISE, m_rMainWnd.actionRecordNoise},
		{ID_WAVE, m_rMainWnd.actionWave},
		{ID_NORMALIZE, m_rMainWnd.actionNormalize},
		{ID_VOCALCANCEL, m_rMainWnd.actionVocalCancel},
		{ID_REVERSE, m_rMainWnd.actionReversePlay},
		{ID_RECORD, m_rMainWnd.actionOldRecordPlay},
		{ID_LOWBATTERY, m_rMainWnd.actionLowBattery},
		{ID_NOSENSE, m_rMainWnd.actionNoSense},
		{ID_BASSCOPY, m_rMainWnd.actionBassCopy},
		{ID_CYMBALCOPY, m_rMainWnd.actionCymbalCopy},
		{ID_EARTRAINING, m_rMainWnd.actionEarTraining},
		{ID_MONORAL, m_rMainWnd.actionMonoral},
		{ID_ONLYLEFT, m_rMainWnd.actionOnlyLeft},
		{ID_ONLYRIGHT, m_rMainWnd.actionOnlyRight},
		{ID_CHANGELR, m_rMainWnd.actionChangeLR},
		{ID_RECOVERTIMESLIDERVISIBLE,
		 m_rMainWnd.actionRecoverTimeSliderVisible},
		{ID_RECOVERSPEEDVISIBLE, m_rMainWnd.actionRecoverSpeedVisible},
		{ID_RECOVERFREQVISIBLE, m_rMainWnd.actionRecoverFreqVisible},
		{ID_RECOVERPITCHVISIBLE, m_rMainWnd.actionRecoverPitchVisible},
		{ID_RECOVERVOLUMEVISIBLE, m_rMainWnd.actionRecoverVolumeVisible},
		{ID_RECOVERPANVISIBLE, m_rMainWnd.actionRecoverPanVisible},
		{ID_RECOVEREQVISIBLE, m_rMainWnd.actionRecoverEQVisible},
		{ID_RECOVERLISTVISIBLE, m_rMainWnd.actionRecoverPlaylistVisible},
		{ID_RECOVERWPOS, m_rMainWnd.actionRecoverWindowPosition},
		{ID_RECOVERWSIZE, m_rMainWnd.actionRecoverWindowSize},
		{ID_RECOVERPLAYPOS, m_rMainWnd.actionRecoverPlayPosition},
		{ID_RECOVERSPEED, m_rMainWnd.actionRecoverSpeed},
		{ID_RECOVERFREQ, m_rMainWnd.actionRecoverFreq},
		{ID_RECOVERPITCH, m_rMainWnd.actionRecoverPitch},
		{ID_RECOVERVOLUME, m_rMainWnd.actionRecoverVolume},
		{ID_RECOVERPAN, m_rMainWnd.actionRecoverPan},
		{ID_RECOVEREQ, m_rMainWnd.actionRecoverEQ},
		{ID_RECOVERLIST, m_rMainWnd.actionRecoverPlaylist},
		{ID_RECOVERSLOOP, m_rMainWnd.actionRecoverPlayModeSingleLoop},
		{ID_RECOVERALOOP, m_rMainWnd.actionRecoverPlayModeAllLoop},
		{ID_RECOVERRANDOM, m_rMainWnd.actionRecoverPlayModeRandom},
		{ID_RECOVERCONTINUE, m_rMainWnd.actionRecoverPlayModeContinuous},
		{ID_RECOVERINSTANTLOOP, m_rMainWnd.actionRecoverPlayModeInstantLoop},
		{ID_RECOVERSETPOSITIONAUTO,
		 m_rMainWnd.actionRecoverPlayModeSetMarkerPositionAuto},
		{ID_RECOVERREVERSE, m_rMainWnd.actionRecoverPlayModeReverse},
		{ID_RECOVERRECORD, m_rMainWnd.actionRecoverPlayModeRecord},
		{ID_LIMIT, m_rMainWnd.actionLimit},
		{ID_TIMERPLAY, m_rMainWnd.actionTimerPlay},
		{ID_PLAYRANGE, m_rMainWnd.actionPlayRange},
		{ID_PLAYPOSITION, m_rMainWnd.actionPlayPosition},
		{ID_FADEOUTSTOP, m_rMainWnd.actionFadeOutStop},
		{ID_FADEOUTSTOP1SEC, m_rMainWnd.actionFadeOutStop1Sec},
		{ID_FADEOUTSTOP2SEC, m_rMainWnd.actionFadeOutStop2Sec},
		{ID_FADEOUTSTOP3SEC, m_rMainWnd.actionFadeOutStop3Sec},
		{ID_FADEOUTSTOP4SEC, m_rMainWnd.actionFadeOutStop4Sec},
		{ID_FADEOUTSTOP5SEC, m_rMainWnd.actionFadeOutStop5Sec},
		{ID_FADEOUTSTOP6SEC, m_rMainWnd.actionFadeOutStop6Sec},
		{ID_FADEOUTSTOP7SEC, m_rMainWnd.actionFadeOutStop7Sec},
		{ID_FADEOUTSTOP8SEC, m_rMainWnd.actionFadeOutStop8Sec},
		{ID_FADEOUTSTOP9SEC, m_rMainWnd.actionFadeOutStop9Sec},
		{ID_FADEOUTSTOP10SEC, m_rMainWnd.actionFadeOutStop10Sec},
		{ID_FADEOUTNEXT, m_rMainWnd.actionFadeOutNext},
		{ID_FADEOUTNEXT1SEC, m_rMainWnd.actionFadeOutNext1Sec},
		{ID_FADEOUTNEXT2SEC, m_rMainWnd.actionFadeOutNext2Sec},
		{ID_FADEOUTNEXT3SEC, m_rMainWnd.actionFadeOutNext3Sec},
		{ID_FADEOUTNEXT4SEC, m_rMainWnd.actionFadeOutNext4Sec},
		{ID_FADEOUTNEXT5SEC, m_rMainWnd.actionFadeOutNext5Sec},
		{ID_FADEOUTNEXT6SEC, m_rMainWnd.actionFadeOutNext6Sec},
		{ID_FADEOUTNEXT7SEC, m_rMainWnd.actionFadeOutNext7Sec},
		{ID_FADEOUTNEXT8SEC, m_rMainWnd.actionFadeOutNext8Sec},
		{ID_FADEOUTNEXT9SEC, m_rMainWnd.actionFadeOutNext9Sec},
		{ID_FADEOUTNEXT10SEC, m_rMainWnd.actionFadeOutNext10Sec},
		{ID_METRONOME, m_rMainWnd.actionMetronome},
		{ID_TOPMOST, m_rMainWnd.actionTopMost},
		{ID_COPYTIME, m_rMainWnd.actionCopyTime},
	};
}
//----------------------------------------------------------------------------
// 排他的にチェックするアイテムのグループ化
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateActionGroups()
{
	// Effect - Speed - Decimal digit
	auto speed_digit_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionSpeedDigit0,
											m_rMainWnd.actionSpeedDigit1,
											m_rMainWnd.actionSpeedDigit2}) {
		speed_digit_group->addAction(action);
	}
	// Effect - Frequency - Decimal digit
	auto freq_digit_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionFreqDigit0,
											m_rMainWnd.actionFreqDigit1,
											m_rMainWnd.actionFreqDigit2}) {
		freq_digit_group->addAction(action);
	}
	// Effect - Pitch - Decimal digit
	auto pitch_digit_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionPitchDigit0,
											m_rMainWnd.actionPitchDigit1,
											m_rMainWnd.actionPitchDigit2}) {
		pitch_digit_group->addAction(action);
	}
	// System - Fade out stop time
	auto fadeout_stop_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionFadeOutStop1Sec,
											m_rMainWnd.actionFadeOutStop2Sec,
											m_rMainWnd.actionFadeOutStop3Sec,
											m_rMainWnd.actionFadeOutStop4Sec,
											m_rMainWnd.actionFadeOutStop5Sec,
											m_rMainWnd.actionFadeOutStop6Sec,
											m_rMainWnd.actionFadeOutStop7Sec,
											m_rMainWnd.actionFadeOutStop8Sec,
											m_rMainWnd.actionFadeOutStop9Sec,
											m_rMainWnd.actionFadeOutStop10Sec}) {
		fadeout_stop_group->addAction(action);
	}
	// System - Fade out next time
	auto fadeout_next_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionFadeOutNext1Sec,
											m_rMainWnd.actionFadeOutNext2Sec,
											m_rMainWnd.actionFadeOutNext3Sec,
											m_rMainWnd.actionFadeOutNext4Sec,
											m_rMainWnd.actionFadeOutNext5Sec,
											m_rMainWnd.actionFadeOutNext6Sec,
											m_rMainWnd.actionFadeOutNext7Sec,
											m_rMainWnd.actionFadeOutNext8Sec,
											m_rMainWnd.actionFadeOutNext9Sec,
											m_rMainWnd.actionFadeOutNext10Sec}) {
		fadeout_next_group->addAction(action);
	}
	// System - Language
	auto lang_group = new QActionGroup(&m_rMainWnd);
	for (auto action : {m_rMainWnd.actionLanguageDefault,
											m_rMainWnd.actionLanguageJapanese,
											m_rMainWnd.actionLanguageEnglish}) {
		lang_group->addAction(action);
	}
}
//----------------------------------------------------------------------------
// シグナル&スロットの設定
//----------------------------------------------------------------------------
void CMenu_MainWnd::CreateConnections()
{
	// File
	connect(m_rMainWnd.actionFileOpen, &QAction::triggered,
					this, &CMenu_MainWnd::OnOpenFileMenuSelected);
	connect(m_rMainWnd.actionFileAdd, &QAction::triggered,
					this, &CMenu_MainWnd::OnAddFileMenuSelected);
	connect(m_rMainWnd.actionFileOpenDirectory, &QAction::triggered,
					this, &CMenu_MainWnd::OnOpenFolderMenuSelected);
	connect(m_rMainWnd.actionFileAddDirectory, &QAction::triggered,
					this, &CMenu_MainWnd::OnAddFolderMenuSelected);
	connect(m_rMainWnd.actionFileOpenUrl, &QAction::triggered,
					this, &CMenu_MainWnd::OnOpenURLMenuSelected);
	connect(m_rMainWnd.actionFileAddUrl, &QAction::triggered,
					this, &CMenu_MainWnd::OnAddURLMenuSelected);
	connect(m_rMainWnd.actionFileSave, &QAction::triggered,
					this, &CMenu_MainWnd::OnSaveFileMenuSelected);
	connect(m_rMainWnd.actionFileSaveAll, &QAction::triggered,
					this, &CMenu_MainWnd::OnSaveAllFileMenuSelected);
	connect(m_rMainWnd.actionFileExit, &QAction::triggered,
					this, &CMenu_MainWnd::OnExitMenuSelected);
	// Edit
	connect(m_rMainWnd.actionEditDelete, &QAction::triggered,
					this, &CMenu_MainWnd::OnDeleteMenuSelected);
	connect(m_rMainWnd.actionEditSelectAll, &QAction::triggered,
					this, &CMenu_MainWnd::OnSelectAllMenuSelected);
	// View
	connect(m_rMainWnd.actionTimeSliderVisible, &QAction::triggered,
					this, &CMenu_MainWnd::OnTimeSliderMenuSelected);
	connect(m_rMainWnd.actionExplorerVisible, &QAction::triggered,
					this, &CMenu_MainWnd::OnExplorerMenuSelected);
	connect(m_rMainWnd.actionSpeedVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnSpeedMenuSelected);
	connect(m_rMainWnd.actionFreqVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnFreqMenuSelected);
	connect(m_rMainWnd.actionPitchVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnPitchMenuSelected);
	connect(m_rMainWnd.actionVolumeVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnVolumeMenuSelected);
	connect(m_rMainWnd.actionPanVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnPanMenuSelected);
	connect(m_rMainWnd.actionEQVisible, &QAction::toggled,
					this, &CMenu_MainWnd::OnEQMenuSelected);
	connect(m_rMainWnd.actionTabVisible, &QAction::triggered,
					this, &CMenu_MainWnd::OnTabMenuSelected);
	connect(m_rMainWnd.actionPlaylistVisible, &QAction::triggered,
					this, &CMenu_MainWnd::OnPlayListMenuSelected);
	connect(m_rMainWnd.actionCloseAll, &QAction::triggered,
					this, &CMenu_MainWnd::OnCloseAllMenuSelected);
	// Play
	connect(m_rMainWnd.actionPlayPlayPause, &QAction::triggered,
					this, &CMenu_MainWnd::OnPauseMenuSelected);
	connect(m_rMainWnd.actionPlayStop, &QAction::triggered,
					this, &CMenu_MainWnd::OnStopMenuSelected);
	connect(m_rMainWnd.actionHead, &QAction::triggered,
					this, &CMenu_MainWnd::OnHeadMenuSelected);
	connect(m_rMainWnd.actionPrevious, &QAction::triggered,
					this, &CMenu_MainWnd::OnPreviousMenuSelected);
	connect(m_rMainWnd.actionNext, &QAction::triggered,
					this, &CMenu_MainWnd::OnNextMenuSelected);
	connect(m_rMainWnd.actionRewind, &QAction::triggered,
					this, &CMenu_MainWnd::OnRewindMenuSelected);
	connect(m_rMainWnd.actionForward, &QAction::triggered,
					this, &CMenu_MainWnd::OnForwardMenuSelected);
	connect(m_rMainWnd.actionRewind1, &QAction::triggered,
					this, &CMenu_MainWnd::OnReturn1SecMenuSelected);
	connect(m_rMainWnd.actionRewind2, &QAction::triggered,
					this, &CMenu_MainWnd::OnReturn2SecMenuSelected);
	connect(m_rMainWnd.actionRewind3, &QAction::triggered,
					this, &CMenu_MainWnd::OnReturn3SecMenuSelected);
	connect(m_rMainWnd.actionRewind5, &QAction::triggered,
					this, &CMenu_MainWnd::OnReturn5SecMenuSelected);
	connect(m_rMainWnd.actionRewind10, &QAction::triggered,
					this, &CMenu_MainWnd::OnReturn10SecMenuSelected);
	connect(m_rMainWnd.actionForward1, &QAction::triggered,
					this, &CMenu_MainWnd::OnForward1SecMenuSelected);
	connect(m_rMainWnd.actionForward2, &QAction::triggered,
					this, &CMenu_MainWnd::OnForward2SecMenuSelected);
	connect(m_rMainWnd.actionForward3, &QAction::triggered,
					this, &CMenu_MainWnd::OnForward3SecMenuSelected);
	connect(m_rMainWnd.actionForward5, &QAction::triggered,
					this, &CMenu_MainWnd::OnForward5SecMenuSelected);
	connect(m_rMainWnd.actionForward10, &QAction::triggered,
					this, &CMenu_MainWnd::OnForward10SecMenuSelected);
	connect(m_rMainWnd.actionSingleLoop, &QAction::triggered,
					this, &CMenu_MainWnd::OnSingleLoopMenuSelected);
	connect(m_rMainWnd.actionAllLoop, &QAction::toggled,
					this, &CMenu_MainWnd::OnAllLoopMenuSelected);
	connect(m_rMainWnd.actionRandomPlay, &QAction::toggled,
					this, &CMenu_MainWnd::OnRandomMenuSelected);
	connect(m_rMainWnd.actionContinuousPlay, &QAction::toggled,
					this, &CMenu_MainWnd::OnContinueMenuSelected);
	connect(m_rMainWnd.actionSetABLoopA, &QAction::triggered,
					this, &CMenu_MainWnd::OnABLoopAMenuSelected);
	connect(m_rMainWnd.actionSetABLoopB, &QAction::triggered,
					this, &CMenu_MainWnd::OnABLoopBMenuSelected);
	connect(m_rMainWnd.actionABLoopAPosSetting, &QAction::triggered,
					this, &CMenu_MainWnd::OnABLoopASettingMenuSelected);
	connect(m_rMainWnd.actionABLoopBPosSetting, &QAction::triggered,
					this, &CMenu_MainWnd::OnABLoopBSettingMenuSelected);
	connect(m_rMainWnd.actionMarkerPlay, &QAction::triggered,
					this, &CMenu_MainWnd::OnMarkerPlayMenuSelected);
	connect(m_rMainWnd.actionAddMarker, &QAction::triggered,
					this, &CMenu_MainWnd::OnAddMarkerMenuSelected);
	connect(m_rMainWnd.actionDeleteMarker, &QAction::triggered,
					this, &CMenu_MainWnd::OnDeleteMarkerMenuSelected);
	connect(m_rMainWnd.actionCountLoop, &QAction::triggered,
					this, &CMenu_MainWnd::OnCountLoopMenuSelected);
	connect(m_rMainWnd.actionInstantLoop, &QAction::triggered,
					this, &CMenu_MainWnd::OnInstantLoopMenuSelected);
	connect(m_rMainWnd.actionSetMarkerPositionAuto, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPositionAutoMenuSelected);
	// Effect - Preset
	connect(m_rMainWnd.actionPresetAddCurrentSettings, &QAction::triggered,
					this, &CMenu_MainWnd::OnAddPresetMenuSelected);
	connect(m_rMainWnd.actionPresetDelete, &QAction::triggered,
					this, &CMenu_MainWnd::OnDeletePresetMenuSelected);
	// Effect - Reverb
	connect(m_rMainWnd.actionReverbDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnReverbDefaultMenuSelected);
	connect(m_rMainWnd.actionReverbCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnReverbCustomizeMenuSelected);
	// Effect - 3D Reverb
	connect(m_rMainWnd.action3DReverbDefault, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbDefaultMenuSelected);
	connect(m_rMainWnd.action3DReverbPaddedCell, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbPaddedCellMenuSelected);
	connect(m_rMainWnd.action3DReverbRoom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbRoomMenuSelected);
	connect(m_rMainWnd.action3DReverbBathroom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbBathroomMenuSelected);
	connect(m_rMainWnd.action3DReverbLivingRoom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbLivingRoomMenuSelected);
	connect(m_rMainWnd.action3DReverbStoneRoom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbStoneRoomMenuSelected);
	connect(m_rMainWnd.action3DReverbAuditorium, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbAuditoriumMenuSelected);
	connect(m_rMainWnd.action3DReverbConcertHall, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbConcertHallMenuSelected);
	connect(m_rMainWnd.action3DReverbCave, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbCaveMenuSelected);
	connect(m_rMainWnd.action3DReverbArena, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbArenaMenuSelected);
	connect(m_rMainWnd.action3DReverbHangar, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbHangarMenuSelected);
	connect(m_rMainWnd.action3DReverbCarpetedHallway, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbCarpetedHallwayMenuSelected);
	connect(m_rMainWnd.action3DReverbHallway, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbHallwayMenuSelected);
	connect(m_rMainWnd.action3DReverbStoneCorridor, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbStoneCorridorMenuSelected);
	connect(m_rMainWnd.action3DReverbAlley, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbAlleyMenuSelected);
	connect(m_rMainWnd.action3DReverbForest, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbForestMenuSelected);
	connect(m_rMainWnd.action3DReverbCity, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbCityMenuSelected);
	connect(m_rMainWnd.action3DReverbMountains, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbMountainsMenuSelected);
	connect(m_rMainWnd.action3DReverbQuarry, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbQuarryMenuSelected);
	connect(m_rMainWnd.action3DReverbPlain, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbPlainMenuSelected);
	connect(m_rMainWnd.action3DReverbParkingLot, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbParkingLotMenuSelected);
	connect(m_rMainWnd.action3DReverbSewerPipe, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbSewerPipeMenuSelected);
	connect(m_rMainWnd.action3DReverbUnderwater, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbUnderwaterMenuSelected);
	connect(m_rMainWnd.action3DReverbSmallRoom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbSmallRoomMenuSelected);
	connect(m_rMainWnd.action3DReverbMediumRoom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbMediumRoomMenuSelected);
	connect(m_rMainWnd.action3DReverbLargeRoom, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbLargeRoomMenuSelected);
	connect(m_rMainWnd.action3DReverbMediumHall, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbMediumHallMenuSelected);
	connect(m_rMainWnd.action3DReverbLargeHall, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbLargeHallMenuSelected);
	connect(m_rMainWnd.action3DReverbPlate, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbPlateMenuSelected);
	connect(m_rMainWnd.action3DReverbCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::On3DReverbCustomizeMenuSelected);
	// Effect - Delay
	connect(m_rMainWnd.actionDelayDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayDefaultMenuSelected);
	connect(m_rMainWnd.actionDelayShort, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayShortMenuSelected);
	connect(m_rMainWnd.actionDelayMedium, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayMediumMenuSelected);
	connect(m_rMainWnd.actionDelayLong, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayLongMenuSelected);
	connect(m_rMainWnd.actionDelayStereoShort, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayStereoShortMenuSelected);
	connect(m_rMainWnd.actionDelayStereoMedium, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayStereoMediumMenuSelected);
	connect(m_rMainWnd.actionDelayStereoLong, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayStereoLongMenuSelected);
	connect(m_rMainWnd.actionDelayMountain, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayMountainMenuSelected);
	connect(m_rMainWnd.actionDelayBig, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayBigMenuSelected);
	connect(m_rMainWnd.actionDelayStereoBig, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayStereoBigMenuSelected);
	connect(m_rMainWnd.actionDelayDoubling, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayDoublingMenuSelected);
	connect(m_rMainWnd.actionDelayDoubleKick, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayDoubleKickMenuSelected);
	connect(m_rMainWnd.actionDelayCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnDelayCustomizeMenuSelected);
	// Effect - Chorus
	connect(m_rMainWnd.actionChorusDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnChorusDefaultMenuSelected);
	connect(m_rMainWnd.actionChorusCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnChorusCustomizeMenuSelected);
	// Effect - Compressor
	connect(m_rMainWnd.actionCompressorDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnCompressorDefaultMenuSelected);
	connect(m_rMainWnd.actionCompressorCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnCompressorCustomizeMenuSelected);
	// Effect - Flanger
	connect(m_rMainWnd.actionFlangerDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnFlangerDefaultMenuSelected);
	connect(m_rMainWnd.actionFlangerCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnFlangerCustomizeMenuSelected);
	// Effect - Gargle
	connect(m_rMainWnd.actionGargleDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnGargleDefaultMenuSelected);
	connect(m_rMainWnd.actionGargleCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnGargleCustomizeMenuSelected);
	// Effect - Distortion
	connect(m_rMainWnd.actionDistortionDefault, &QAction::triggered,
					this, &CMenu_MainWnd::OnDistortionDefaultMenuSelected);
	connect(m_rMainWnd.actionDistortionCustomize, &QAction::triggered,
					this, &CMenu_MainWnd::OnDistortionCustomizeMenuSelected);
	// Effect - Sound Effects
	connect(m_rMainWnd.actionRecordNoise, &QAction::triggered,
					this, &CMenu_MainWnd::OnRecordNoiseMenuSelected);
	connect(m_rMainWnd.actionWave, &QAction::triggered,
					this, &CMenu_MainWnd::OnWaveMenuSelected);
	connect(m_rMainWnd.actionNormalize, &QAction::triggered,
					this, &CMenu_MainWnd::OnNormalizeMenuSelected);
	connect(m_rMainWnd.actionVocalCancel, &QAction::triggered,
					this, &CMenu_MainWnd::OnVocalCancelMenuSelected);
	connect(m_rMainWnd.actionReversePlay, &QAction::triggered,
					this, &CMenu_MainWnd::OnReverseMenuSelected);
	connect(m_rMainWnd.actionOldRecordPlay, &QAction::triggered,
					this, &CMenu_MainWnd::OnRecordMenuSelected);
	connect(m_rMainWnd.actionLowBattery, &QAction::triggered,
					this, &CMenu_MainWnd::OnLowBatteryMenuSelected);
	connect(m_rMainWnd.actionNoSense, &QAction::triggered,
					this, &CMenu_MainWnd::OnNoSenseMenuSelected);
	connect(m_rMainWnd.actionBassCopy, &QAction::triggered,
					this,
					static_cast<void (CMenu_MainWnd::*)(bool)>(
							&CMenu_MainWnd::OnBassCopyMenuSelected));
	connect(m_rMainWnd.actionCymbalCopy, &QAction::triggered,
					this,
					static_cast<void (CMenu_MainWnd::*)(bool)>(
							&CMenu_MainWnd::OnDrumsCopyMenuSelected));
	connect(m_rMainWnd.actionEarTraining, &QAction::triggered,
					this, &CMenu_MainWnd::OnEarTrainingMenuSelected);
	connect(m_rMainWnd.actionMonoral, &QAction::triggered,
					this, &CMenu_MainWnd::OnMonoralMenuSelected);
	connect(m_rMainWnd.actionOnlyLeft, &QAction::triggered,
					this, &CMenu_MainWnd::OnOnlyLeftMenuSelected);
	connect(m_rMainWnd.actionOnlyRight, &QAction::triggered,
					this, &CMenu_MainWnd::OnOnlyRightMenuSelected);
	connect(m_rMainWnd.actionChangeLR, &QAction::triggered,
					this, &CMenu_MainWnd::OnChangeLRMenuSelected);
	connect(m_rMainWnd.actionEffectResetAll, &QAction::triggered,
					this, &CMenu_MainWnd::OnResetAllMenuSelected);
	// Effect - EQ preset
	connect(m_rMainWnd.actionEQPresetFlat, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQFlatMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostLowUltraStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowSuperMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostLowStrongest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowHighestMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostLowStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowHighMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostLowMiddle, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowMiddleMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostLowWeak, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowLowMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostLowWeakest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowLowestMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostMiddleUltraStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleSuperMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostMiddleStrongest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleHighestMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostMiddleStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleHighMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostMiddleMiddle, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleMiddleMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostMiddleWeak, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleLowMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostMiddleWeakest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleLowestMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostHighUltraStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighSuperMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostHighStrongest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighHighestMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostHighStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighHighMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostHighMiddle, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighMiddleMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostHighWeak, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighLowMenuSelected);
	connect(m_rMainWnd.actionEQPresetBoostHighWeakest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighLowestMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutLowUltraStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowCutSuperMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutLowStrongest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowCutHighestMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutLowStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowCutHighMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutLowMiddle, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowCutMiddleMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutLowWeak, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowCutLowMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutLowWeakest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQLowCutLowestMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutMiddleUltraStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleCutSuperMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutMiddleStrongest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleCutHighestMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutMiddleStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleCutHighMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutMiddleMiddle, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleCutMiddleMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutMiddleWeak, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleCutLowMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutMiddleWeakest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQMiddleCutLowestMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutHighUltraStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighCutSuperMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutHighStrongest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighCutHighestMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutHighStrong, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighCutHighMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutHighMiddle, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighCutMiddleMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutHighWeak, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighCutLowMenuSelected);
	connect(m_rMainWnd.actionEQPresetCutHighWeakest, &QAction::triggered,
					this, &CMenu_MainWnd::OnEQHighCutLowestMenuSelected);
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
	connect(m_rMainWnd.actionSpeedDecrease, &QAction::triggered,
					this, &CMenu_MainWnd::OnDecSpeedMenuSelected);
	connect(m_rMainWnd.actionSpeedIncrease, &QAction::triggered,
					this, &CMenu_MainWnd::OnIncSpeedMenuSelected);
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
	// Effect - Frequency
	connect(m_rMainWnd.actionResetFreq, &QAction::triggered,
					this, &CMenu_MainWnd::OnResetFreqMenuSelected);
	connect(m_rMainWnd.actionSetFreq50, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq50MenuSelected);
	connect(m_rMainWnd.actionSetFreq60, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq60MenuSelected);
	connect(m_rMainWnd.actionSetFreq70, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq70MenuSelected);
	connect(m_rMainWnd.actionSetFreq80, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq80MenuSelected);
	connect(m_rMainWnd.actionSetFreq90, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq90MenuSelected);
	connect(m_rMainWnd.actionSetFreq100, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq100MenuSelected);
	connect(m_rMainWnd.actionSetFreq110, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq110MenuSelected);
	connect(m_rMainWnd.actionSetFreq120, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq120MenuSelected);
	connect(m_rMainWnd.actionSetFreq130, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq130MenuSelected);
	connect(m_rMainWnd.actionSetFreq140, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq140MenuSelected);
	connect(m_rMainWnd.actionSetFreq150, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq150MenuSelected);
	connect(m_rMainWnd.actionSetFreq160, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq160MenuSelected);
	connect(m_rMainWnd.actionSetFreq170, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq170MenuSelected);
	connect(m_rMainWnd.actionSetFreq180, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq180MenuSelected);
	connect(m_rMainWnd.actionSetFreq190, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq190MenuSelected);
	connect(m_rMainWnd.actionSetFreq200, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq200MenuSelected);
	connect(m_rMainWnd.actionSetFreq250, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq250MenuSelected);
	connect(m_rMainWnd.actionSetFreq300, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq300MenuSelected);
	connect(m_rMainWnd.actionSetFreq350, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq350MenuSelected);
	connect(m_rMainWnd.actionSetFreq400, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetFreq400MenuSelected);
	connect(m_rMainWnd.actionFreqDown01, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown0_1FreqMenuSelected);
	connect(m_rMainWnd.actionFreqDown1, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown1FreqMenuSelected);
	connect(m_rMainWnd.actionFreqDown2, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown2FreqMenuSelected);
	connect(m_rMainWnd.actionFreqDown3, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown3FreqMenuSelected);
	connect(m_rMainWnd.actionFreqDown5, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown5FreqMenuSelected);
	connect(m_rMainWnd.actionFreqDown10, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown10FreqMenuSelected);
	connect(m_rMainWnd.actionFreqUp01, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp0_1FreqMenuSelected);
	connect(m_rMainWnd.actionFreqUp1, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp1FreqMenuSelected);
	connect(m_rMainWnd.actionFreqUp2, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp2FreqMenuSelected);
	connect(m_rMainWnd.actionFreqUp3, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp3FreqMenuSelected);
	connect(m_rMainWnd.actionFreqUp5, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp5FreqMenuSelected);
	connect(m_rMainWnd.actionFreqUp10, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp10FreqMenuSelected);
	connect(m_rMainWnd.actionFreqDecrease, &QAction::triggered,
					this, &CMenu_MainWnd::OnDecFreqMenuSelected);
	connect(m_rMainWnd.actionFreqIncrease, &QAction::triggered,
					this, &CMenu_MainWnd::OnIncFreqMenuSelected);
	// Effecgt - Frequency - Decimal digit
	connect(m_rMainWnd.actionFreqDigit0, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetFreqDecimal0MenuSelected(); }
					});
	connect(m_rMainWnd.actionFreqDigit1, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetFreqDecimal1MenuSelected(); }
					});
	connect(m_rMainWnd.actionFreqDigit2, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetFreqDecimal2MenuSelected(); }
					});
	// Effect - Pitch
	connect(m_rMainWnd.actionResetPitch, &QAction::triggered,
					this, &CMenu_MainWnd::OnResetPitchMenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat12, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat12MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat11, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat11MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat10, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat10MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat9, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat9MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat8, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat8MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat7, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat7MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat6, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat6MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat5, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat5MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat4, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat4MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat3, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat3MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat2, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat2MenuSelected);
	connect(m_rMainWnd.actionSetPitchFlat1, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchFlat1MenuSelected);
	connect(m_rMainWnd.actionSetPitch0, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchNaturalMenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp1, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp1MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp2, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp2MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp3, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp3MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp4, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp4MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp5, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp5MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp6, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp6MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp7, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp7MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp8, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp8MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp9, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp9MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp10, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp10MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp11, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp11MenuSelected);
	connect(m_rMainWnd.actionSetPitchSharp12, &QAction::triggered,
					this, &CMenu_MainWnd::OnSetPitchSharp12MenuSelected);
	connect(m_rMainWnd.actionPitchFlat, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown1PitchMenuSelected);
	connect(m_rMainWnd.actionPitchDoubleFlat, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown2PitchMenuSelected);
	connect(m_rMainWnd.actionPitchDown1Octave, &QAction::triggered,
					this, &CMenu_MainWnd::OnDown1OctavePitchMenuSelected);
	connect(m_rMainWnd.actionPitchSharp, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp1PitchMenuSelected);
	connect(m_rMainWnd.actionPitchDoubleSharp, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp2PitchMenuSelected);
	connect(m_rMainWnd.actionPitchUp1Octave, &QAction::triggered,
					this, &CMenu_MainWnd::OnUp1OctavePitchMenuSelected);
	// Effecgt - Pitch - Decimal digit
	connect(m_rMainWnd.actionPitchDigit0, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetPitchDecimal0MenuSelected(); }
					});
	connect(m_rMainWnd.actionPitchDigit1, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetPitchDecimal1MenuSelected(); }
					});
	connect(m_rMainWnd.actionPitchDigit2, &QAction::toggled,
					[&] (bool checked) {
						if (checked) { emit OnSetPitchDecimal2MenuSelected(); }
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
	// System
	connect(m_rMainWnd.actionLimit, &QAction::triggered,
					this, &CMenu_MainWnd::OnLimitMenuSelected);
	connect(m_rMainWnd.actionTimerPlay, &QAction::triggered,
					this, &CMenu_MainWnd::OnTimerPlayMenuSelected);
	connect(m_rMainWnd.actionPlayRange, &QAction::triggered,
					this, &CMenu_MainWnd::OnPlayRangeMenuSelected);
	connect(m_rMainWnd.actionPlayPosition, &QAction::triggered,
					this, &CMenu_MainWnd::OnPlayPositionMenuSelected);
	connect(m_rMainWnd.actionMetronome, &QAction::triggered,
					this, &CMenu_MainWnd::OnMetronomeMenuSelected);
	connect(m_rMainWnd.actionTopMost, &QAction::triggered,
					this, &CMenu_MainWnd::OnTopMostMenuSelected);
	connect(m_rMainWnd.actionCopyTime, &QAction::triggered,
					this, &CMenu_MainWnd::OnCopyTimeMenuSelected);
	// Help
	connect(m_rMainWnd.actionManual, &QAction::triggered,
					this, &CMenu_MainWnd::OnManualMenuSelected);
	connect(m_rMainWnd.actionUpdateCheck, &QAction::triggered,
					this, &CMenu_MainWnd::OnUpdateCheckMenuSelected);
	connect(m_rMainWnd.actionVersionInfo, &QAction::triggered,
					this, &CMenu_MainWnd::OnVersionInfoMenuSelected);
}
//----------------------------------------------------------------------------
