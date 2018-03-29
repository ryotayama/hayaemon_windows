//----------------------------------------------------------------------------
// Menu_MainWnd.h : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef Menu_MainWndH
#define Menu_MainWndH

#include <unordered_map>
#include <QObject>
#include "../Common/Define.h"
#include "PresetMenu.h"
class CApp;
class CMainWnd;
class QAction;
//----------------------------------------------------------------------------
// メインウィンドウ用メニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMenu_MainWnd : public QObject
{
	Q_OBJECT

public: // 関数

	CMenu_MainWnd(CApp & app, CMainWnd & mainWnd);

	virtual BOOL Create();
	void SetABLoopState(BOOL bALoop, BOOL bBLoop);
	void SetFileLoadState(BOOL bLoad);
	void SetDelay(float fWetDryMix, float fFeedback, float fLeftDelay,
		float fRightDelay, BOOL lPanDelay, UINT uID);
	void SetChorus(float fWetDryMix, float fDepth, float fFeedback,
				   float fFreq, DWORD lWaveform, float fDelay, DWORD lPhase,
				   UINT uID);
	void SetCompressor(float fGain, float fAttack, float fRelease,
					   float fThreshold, float fRatio, float fPredelay,
					   UINT uID);
	void SetFlanger(float fWetDryMix, float fDepth, float fFeedback,
					float fFreq, DWORD lWaveform, float fDelay,
					DWORD lPhase, UINT uID);
	void SetGargle(DWORD dwRateHz, DWORD dwWaveShape, UINT uID);
	void SetDistortion(float fGain, float fEdge, float fPostEQCenterFreq,
					   float fPostEQBandwidth, float fPreLowpassCutoff,
					   UINT uID);
	void SetReverb(float fInGain, float fReverbMix, float fReverbTime,
		float fHighFreqRTRatio, UINT uID);
	void Set3DReverb(int lRoom, int lRoomHF, float flRoomRolloffFactor,
		float flDecayTime, float flDecayHFRatio, int lReflections,
		float flReflectionsDelay, int lReverb, float flReverbDelay,
		float flDiffusion, float flDensity, float flHFReference, UINT uID);
	void SetSingleLoopState(BOOL bSLoop);
	void SwitchEQVisible(UINT uID);
	void SwitchItemChecked(UINT uID);
	void UncheckChorusMenu();
	void UncheckCompressorMenu();
	void UncheckDelayMenu();
	void UncheckDistortionMenu();
	void UncheckFlangerMenu();
	void UncheckGargleMenu();
	void UncheckPresetMenu();
	void UncheckReverbMenu();
	void Uncheck3DReverbMenu();
	void UncheckSoundEffectMenu();
	void OnOpenFileMenuSelected();
	void OnAddFileMenuSelected();
	void OnOpenFolderMenuSelected();
	void OnAddFolderMenuSelected();
	void OnOpenURLMenuSelected();
	void OnAddURLMenuSelected();
	void OnSaveFileMenuSelected();
	void OnSaveAllFileMenuSelected();
	void OnExitMenuSelected();
	void OnDeleteMenuSelected();
	void OnSelectAllMenuSelected();
	void OnTimeSliderMenuSelected(bool checked);
	void OnExplorerMenuSelected(bool checked);
	void OnSpeedMenuSelected(bool checked);
	void OnFreqMenuSelected(bool checked);
	void OnPitchMenuSelected(bool checked);
	void OnVolumeMenuSelected(bool checked);
	void OnPanMenuSelected(bool checked);
	void OnEQMenuSelected(bool checked);
	void OnTabMenuSelected(bool checked);
	void OnPlayListMenuSelected(bool checked);
	void OnCloseAllMenuSelected();
	void OnHeadMenuSelected();
	void OnPauseMenuSelected();
	void OnPreviousMenuSelected();
	void OnNextMenuSelected();
	void OnStopMenuSelected();
	void OnRewindMenuSelected(bool checked);
	void OnForwardMenuSelected(bool checked);
	void OnReturn1SecMenuSelected();
	void OnReturn2SecMenuSelected();
	void OnReturn3SecMenuSelected();
	void OnReturn5SecMenuSelected();
	void OnReturn10SecMenuSelected();
	void OnForward1SecMenuSelected();
	void OnForward2SecMenuSelected();
	void OnForward3SecMenuSelected();
	void OnForward5SecMenuSelected();
	void OnForward10SecMenuSelected();
	void OnAddPresetMenuSelected();
	void OnDeletePresetMenuSelected();
	void OnPresetMenuSelected(int id);
	void OnResetSpeedMenuSelected();
	void OnSetSpeed50MenuSelected();
	void OnSetSpeed60MenuSelected();
	void OnSetSpeed70MenuSelected();
	void OnSetSpeed80MenuSelected();
	void OnSetSpeed90MenuSelected();
	void OnSetSpeed100MenuSelected();
	void OnSetSpeed110MenuSelected();
	void OnSetSpeed120MenuSelected();
	void OnSetSpeed130MenuSelected();
	void OnSetSpeed140MenuSelected();
	void OnSetSpeed150MenuSelected();
	void OnSetSpeed160MenuSelected();
	void OnSetSpeed170MenuSelected();
	void OnSetSpeed180MenuSelected();
	void OnSetSpeed190MenuSelected();
	void OnSetSpeed200MenuSelected();
	void OnSetSpeed250MenuSelected();
	void OnSetSpeed300MenuSelected();
	void OnSetSpeed350MenuSelected();
	void OnSetSpeed400MenuSelected();
	void OnDown0_1SpeedMenuSelected();
	void OnDown1SpeedMenuSelected();
	void OnDown2SpeedMenuSelected();
	void OnDown3SpeedMenuSelected();
	void OnDown5SpeedMenuSelected();
	void OnDown10SpeedMenuSelected();
	void OnUp0_1SpeedMenuSelected();
	void OnUp1SpeedMenuSelected();
	void OnUp2SpeedMenuSelected();
	void OnUp3SpeedMenuSelected();
	void OnUp5SpeedMenuSelected();
	void OnUp10SpeedMenuSelected();
	void OnSetSpeedDecimal0MenuSelected();
	void OnSetSpeedDecimal1MenuSelected();
	void OnSetSpeedDecimal2MenuSelected();
	void OnResetFreqMenuSelected();
	void OnSetFreq50MenuSelected();
	void OnSetFreq60MenuSelected();
	void OnSetFreq70MenuSelected();
	void OnSetFreq80MenuSelected();
	void OnSetFreq90MenuSelected();
	void OnSetFreq100MenuSelected();
	void OnSetFreq110MenuSelected();
	void OnSetFreq120MenuSelected();
	void OnSetFreq130MenuSelected();
	void OnSetFreq140MenuSelected();
	void OnSetFreq150MenuSelected();
	void OnSetFreq160MenuSelected();
	void OnSetFreq170MenuSelected();
	void OnSetFreq180MenuSelected();
	void OnSetFreq190MenuSelected();
	void OnSetFreq200MenuSelected();
	void OnSetFreq250MenuSelected();
	void OnSetFreq300MenuSelected();
	void OnSetFreq350MenuSelected();
	void OnSetFreq400MenuSelected();
	void OnDown0_1FreqMenuSelected();
	void OnDown1FreqMenuSelected();
	void OnDown2FreqMenuSelected();
	void OnDown3FreqMenuSelected();
	void OnDown5FreqMenuSelected();
	void OnDown10FreqMenuSelected();
	void OnUp0_1FreqMenuSelected();
	void OnUp1FreqMenuSelected();
	void OnUp2FreqMenuSelected();
	void OnUp3FreqMenuSelected();
	void OnUp5FreqMenuSelected();
	void OnUp10FreqMenuSelected();
	void OnSetFreqDecimal0MenuSelected();
	void OnSetFreqDecimal1MenuSelected();
	void OnSetFreqDecimal2MenuSelected();
	void OnResetPitchMenuSelected();
	void OnSetPitchFlat12MenuSelected();
	void OnSetPitchFlat11MenuSelected();
	void OnSetPitchFlat10MenuSelected();
	void OnSetPitchFlat9MenuSelected();
	void OnSetPitchFlat8MenuSelected();
	void OnSetPitchFlat7MenuSelected();
	void OnSetPitchFlat6MenuSelected();
	void OnSetPitchFlat5MenuSelected();
	void OnSetPitchFlat4MenuSelected();
	void OnSetPitchFlat3MenuSelected();
	void OnSetPitchFlat2MenuSelected();
	void OnSetPitchFlat1MenuSelected();
	void OnSetPitchNaturalMenuSelected();
	void OnSetPitchSharp1MenuSelected();
	void OnSetPitchSharp2MenuSelected();
	void OnSetPitchSharp3MenuSelected();
	void OnSetPitchSharp4MenuSelected();
	void OnSetPitchSharp5MenuSelected();
	void OnSetPitchSharp6MenuSelected();
	void OnSetPitchSharp7MenuSelected();
	void OnSetPitchSharp8MenuSelected();
	void OnSetPitchSharp9MenuSelected();
	void OnSetPitchSharp10MenuSelected();
	void OnSetPitchSharp11MenuSelected();
	void OnSetPitchSharp12MenuSelected();
	void OnDown1PitchMenuSelected();
	void OnDown2PitchMenuSelected();
	void OnDown1OctavePitchMenuSelected();
	void OnUp1PitchMenuSelected();
	void OnUp2PitchMenuSelected();
	void OnUp1OctavePitchMenuSelected();
	void OnSetPitchDecimal0MenuSelected();
	void OnSetPitchDecimal1MenuSelected();
	void OnSetPitchDecimal2MenuSelected();
	void OnResetVolumeMenuSelected();
	void OnSetVolume0MenuSelected();
	void OnSetVolume10MenuSelected();
	void OnSetVolume20MenuSelected();
	void OnSetVolume30MenuSelected();
	void OnSetVolume40MenuSelected();
	void OnSetVolume50MenuSelected();
	void OnSetVolume60MenuSelected();
	void OnSetVolume70MenuSelected();
	void OnSetVolume80MenuSelected();
	void OnSetVolume90MenuSelected();
	void OnSetVolume100MenuSelected();
	void OnSingleLoopMenuSelected();
	void OnAllLoopMenuSelected(bool checked);
	void OnRandomMenuSelected(bool checked);
	void OnContinueMenuSelected(bool checked);
	void OnABLoopAMenuSelected();
	void OnABLoopASettingMenuSelected();
	void OnABLoopBMenuSelected();
	void OnABLoopBSettingMenuSelected();
	void OnMarkerPlayMenuSelected();
	void OnAddMarkerMenuSelected();
	void OnDeleteMarkerMenuSelected();
	void OnCountLoopMenuSelected();
	void OnInstantLoopMenuSelected();
	void OnSetPositionAutoMenuSelected();
	void OnRecordNoiseMenuSelected();
	void OnWaveMenuSelected();
	void OnNormalizeMenuSelected(bool checked);
	void OnVocalCancelMenuSelected(bool checked);
	void OnReverseMenuSelected(bool checked);
	void OnRecordMenuSelected(bool checked);
	void OnLowBatteryMenuSelected(bool checked);
	void OnNoSenseMenuSelected(bool checked);
	void OnBassCopyMenuSelected();
	void OnBassCopyMenuSelected(bool bChecked);
	void OnDrumsCopyMenuSelected();
	void OnDrumsCopyMenuSelected(bool bChecked);
	void OnEarTrainingMenuSelected(bool checked);
	void OnMonoralMenuSelected(bool checked);
	void OnOnlyLeftMenuSelected(bool checked);
	void OnOnlyRightMenuSelected(bool checked);
	void OnChangeLRMenuSelected(bool checked);
	void OnLimitMenuSelected();
	void OnTimerPlayMenuSelected();
	void OnPlayRangeMenuSelected();
	void OnPlayPositionMenuSelected();
	void OnIncSpeedMenuSelected();
	void OnIncFreqMenuSelected();
	void OnDecSpeedMenuSelected();
	void OnDecFreqMenuSelected();
	void OnFadeout1SecMenuSelected();
	void OnFadeout2SecMenuSelected();
	void OnFadeout3SecMenuSelected();
	void OnFadeout4SecMenuSelected();
	void OnFadeout5SecMenuSelected();
	void OnFadeout6SecMenuSelected();
	void OnFadeout7SecMenuSelected();
	void OnFadeout8SecMenuSelected();
	void OnFadeout9SecMenuSelected();
	void OnFadeout10SecMenuSelected();
	void OnFadeoutNext1SecMenuSelected();
	void OnFadeoutNext2SecMenuSelected();
	void OnFadeoutNext3SecMenuSelected();
	void OnFadeoutNext4SecMenuSelected();
	void OnFadeoutNext5SecMenuSelected();
	void OnFadeoutNext6SecMenuSelected();
	void OnFadeoutNext7SecMenuSelected();
	void OnFadeoutNext8SecMenuSelected();
	void OnFadeoutNext9SecMenuSelected();
	void OnFadeoutNext10SecMenuSelected();
	void OnMetronomeMenuSelected();
	void OnReverbDefaultMenuSelected(bool checked = true);
	void OnReverbCustomizeMenuSelected(bool checked);
	void On3DReverbDefaultMenuSelected(bool checked = true);
	void On3DReverbPaddedCellMenuSelected(bool checked = true);
	void On3DReverbRoomMenuSelected(bool checked = true);
	void On3DReverbBathroomMenuSelected(bool checked = true);
	void On3DReverbLivingRoomMenuSelected(bool checked = true);
	void On3DReverbStoneRoomMenuSelected(bool checked = true);
	void On3DReverbAuditoriumMenuSelected(bool checked = true);
	void On3DReverbConcertHallMenuSelected(bool checked = true);
	void On3DReverbCaveMenuSelected(bool checked = true);
	void On3DReverbArenaMenuSelected(bool checked = true);
	void On3DReverbHangarMenuSelected(bool checked = true);
	void On3DReverbCarpetedHallwayMenuSelected(bool checked = true);
	void On3DReverbHallwayMenuSelected(bool checked = true);
	void On3DReverbStoneCorridorMenuSelected(bool checked = true);
	void On3DReverbAlleyMenuSelected(bool checked = true);
	void On3DReverbForestMenuSelected(bool checked = true);
	void On3DReverbCityMenuSelected(bool checked = true);
	void On3DReverbMountainsMenuSelected(bool checked = true);
	void On3DReverbQuarryMenuSelected(bool checked = true);
	void On3DReverbPlainMenuSelected(bool checked = true);
	void On3DReverbParkingLotMenuSelected(bool checked = true);
	void On3DReverbSewerPipeMenuSelected(bool checked = true);
	void On3DReverbUnderwaterMenuSelected(bool checked = true);
	void On3DReverbSmallRoomMenuSelected(bool checked = true);
	void On3DReverbMediumRoomMenuSelected(bool checked = true);
	void On3DReverbLargeRoomMenuSelected(bool checked = true);
	void On3DReverbMediumHallMenuSelected(bool checked = true);
	void On3DReverbLargeHallMenuSelected(bool checked = true);
	void On3DReverbPlateMenuSelected(bool checked = true);
	void On3DReverbCustomizeMenuSelected(bool checked);
	void OnDelayDefaultMenuSelected(bool checked = true);
	void OnDelayShortMenuSelected(bool checked = true);
	void OnDelayMediumMenuSelected(bool checked = true);
	void OnDelayLongMenuSelected(bool checked = true);
	void OnDelayStereoShortMenuSelected(bool checked = true);
	void OnDelayStereoMediumMenuSelected(bool checked = true);
	void OnDelayStereoLongMenuSelected(bool checked = true);
	void OnDelayMountainMenuSelected(bool checked = true);
	void OnDelayBigMenuSelected(bool checked = true);
	void OnDelayStereoBigMenuSelected(bool checked = true);
	void OnDelayDoublingMenuSelected(bool checked = true);
	void OnDelayDoubleKickMenuSelected(bool checked = true);
	void OnDelayCustomizeMenuSelected(bool checked);
	void OnChorusDefaultMenuSelected(bool checked = true);
	void OnChorusCustomizeMenuSelected(bool checked);
	void OnCompressorDefaultMenuSelected(bool checked = true);
	void OnCompressorCustomizeMenuSelected(bool checked);
	void OnFlangerDefaultMenuSelected(bool checked = true);
	void OnFlangerCustomizeMenuSelected(bool checked);
	void OnGargleDefaultMenuSelected(bool checked = true);
	void OnGargleCustomizeMenuSelected(bool checked);
	void OnDistortionDefaultMenuSelected(bool checked = true);
	void OnDistortionCustomizeMenuSelected(bool checked);
	void OnEQFlatMenuSelected();
	void OnEQLowSuperMenuSelected();
	void OnEQLowHighestMenuSelected();
	void OnEQLowHighMenuSelected();
	void OnEQLowMiddleMenuSelected();
	void OnEQLowLowMenuSelected();
	void OnEQLowLowestMenuSelected();
	void OnEQMiddleSuperMenuSelected();
	void OnEQMiddleHighestMenuSelected();
	void OnEQMiddleHighMenuSelected();
	void OnEQMiddleMiddleMenuSelected();
	void OnEQMiddleLowMenuSelected();
	void OnEQMiddleLowestMenuSelected();
	void OnEQHighSuperMenuSelected();
	void OnEQHighHighestMenuSelected();
	void OnEQHighHighMenuSelected();
	void OnEQHighMiddleMenuSelected();
	void OnEQHighLowMenuSelected();
	void OnEQHighLowestMenuSelected();
	void OnEQLowCutSuperMenuSelected();
	void OnEQLowCutHighestMenuSelected();
	void OnEQLowCutHighMenuSelected();
	void OnEQLowCutMiddleMenuSelected();
	void OnEQLowCutLowMenuSelected();
	void OnEQLowCutLowestMenuSelected();
	void OnEQMiddleCutSuperMenuSelected();
	void OnEQMiddleCutHighestMenuSelected();
	void OnEQMiddleCutHighMenuSelected();
	void OnEQMiddleCutMiddleMenuSelected();
	void OnEQMiddleCutLowMenuSelected();
	void OnEQMiddleCutLowestMenuSelected();
	void OnEQHighCutSuperMenuSelected();
	void OnEQHighCutHighestMenuSelected();
	void OnEQHighCutHighMenuSelected();
	void OnEQHighCutMiddleMenuSelected();
	void OnEQHighCutLowMenuSelected();
	void OnEQHighCutLowestMenuSelected();
	void OnResetAllMenuSelected();
	void OnTopMostMenuSelected();
	void OnCopyTimeMenuSelected();
	void OnManualMenuSelected();
	void OnUpdateCheckMenuSelected();
	void OnVersionInfoMenuSelected();

	CPresetMenu & GetPresetMenu() {
		return m_presetMenu;
	}

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CPresetMenu m_presetMenu;
	std::unordered_map<UINT, QAction*> m_actionMap;

	friend class CMainWnd;
	friend class CPresetMenu;

public:
	// Qtのラッパー
	void CheckItem(UINT uIDCheckItem, UINT uCheck);
	BOOL IsItemChecked(UINT uID);
	void EnableItem(UINT uIDEnableItem, UINT uEnable);

private:
	// Qtのラッパー
	void CreateActionMap();
	void CreateActionGroups();
	void CreateConnections();
};
//----------------------------------------------------------------------------

#endif
