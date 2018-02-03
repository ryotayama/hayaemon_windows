//----------------------------------------------------------------------------
// Menu_MainWnd.h : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef Menu_MainWndH
#define Menu_MainWndH

#include <unordered_map>
#include <QObject>
#include "../Common/Define.h"
#include "PresetMenu.h"
class CMainWnd;
class QAction;
//----------------------------------------------------------------------------
// メインウィンドウ用メニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMenu_MainWnd : public QObject
{
public: // 関数

	explicit CMenu_MainWnd(CMainWnd & mainWnd);

	virtual BOOL Create();
	void SetABLoopState(BOOL bALoop, BOOL bBLoop);
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
	void OnSaveFileMenuSelected();
	void OnSpeedMenuSelected(bool checked);
	void OnFreqMenuSelected(bool checked);
	void OnPitchMenuSelected(bool checked);
	void OnVolumeMenuSelected(bool checked);
	void OnPanMenuSelected(bool checked);
	void OnEQMenuSelected(bool checked);
	void OnTabMenuSelected(bool checked);
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
	void OnPlayRangeMenuSelected();
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
	void OnReverbDefaultMenuSelected(bool checked);
	void OnReverbCustomizeMenuSelected(bool checked);
	void On3DReverbDefaultMenuSelected(bool checked);
	void On3DReverbPaddedCellMenuSelected(bool checked);
	void On3DReverbRoomMenuSelected(bool checked);
	void On3DReverbBathroomMenuSelected(bool checked);
	void On3DReverbLivingRoomMenuSelected(bool checked);
	void On3DReverbStoneRoomMenuSelected(bool checked);
	void On3DReverbAuditoriumMenuSelected(bool checked);
	void On3DReverbConcertHallMenuSelected(bool checked);
	void On3DReverbCaveMenuSelected(bool checked);
	void On3DReverbArenaMenuSelected(bool checked);
	void On3DReverbHangarMenuSelected(bool checked);
	void On3DReverbCarpetedHallwayMenuSelected(bool checked);
	void On3DReverbHallwayMenuSelected(bool checked);
	void On3DReverbStoneCorridorMenuSelected(bool checked);
	void On3DReverbAlleyMenuSelected(bool checked);
	void On3DReverbForestMenuSelected(bool checked);
	void On3DReverbCityMenuSelected(bool checked);
	void On3DReverbMountainsMenuSelected(bool checked);
	void On3DReverbQuarryMenuSelected(bool checked);
	void On3DReverbPlainMenuSelected(bool checked);
	void On3DReverbParkingLotMenuSelected(bool checked);
	void On3DReverbSewerPipeMenuSelected(bool checked);
	void On3DReverbUnderwaterMenuSelected(bool checked);
	void On3DReverbSmallRoomMenuSelected(bool checked);
	void On3DReverbMediumRoomMenuSelected(bool checked);
	void On3DReverbLargeRoomMenuSelected(bool checked);
	void On3DReverbMediumHallMenuSelected(bool checked);
	void On3DReverbLargeHallMenuSelected(bool checked);
	void On3DReverbPlateMenuSelected(bool checked);
	void On3DReverbCustomizeMenuSelected(bool checked);
	void OnDelayDefaultMenuSelected(bool checked);
	void OnDelayShortMenuSelected(bool checked);
	void OnDelayMediumMenuSelected(bool checked);
	void OnDelayLongMenuSelected(bool checked);
	void OnDelayStereoShortMenuSelected(bool checked);
	void OnDelayStereoMediumMenuSelected(bool checked);
	void OnDelayStereoLongMenuSelected(bool checked);
	void OnDelayMountainMenuSelected(bool checked);
	void OnDelayBigMenuSelected(bool checked);
	void OnDelayStereoBigMenuSelected(bool checked);
	void OnDelayDoublingMenuSelected(bool checked);
	void OnDelayDoubleKickMenuSelected(bool checked);
	void OnDelayCustomizeMenuSelected(bool checked);
	void OnChorusDefaultMenuSelected(bool checked);
	void OnChorusCustomizeMenuSelected(bool checked);
	void OnCompressorDefaultMenuSelected(bool checked);
	void OnCompressorCustomizeMenuSelected(bool checked);
	void OnFlangerDefaultMenuSelected(bool checked);
	void OnFlangerCustomizeMenuSelected(bool checked);
	void OnGargleDefaultMenuSelected(bool checked);
	void OnGargleCustomizeMenuSelected(bool checked);
	void OnDistortionDefaultMenuSelected(bool checked);
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

	CPresetMenu & GetPresetMenu() {
		return m_presetMenu;
	}

private: // メンバ変数

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
