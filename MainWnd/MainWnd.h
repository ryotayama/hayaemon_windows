//----------------------------------------------------------------------------
// MainWnd.h : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH

class C3DReverbCustomizeWnd;
class CABLoopPosWnd;
class CApp;
class CChorusCustomizeWnd;
class CCompressorCustomizeWnd;
class CCountLoopWnd_MainWnd;
class CDecFreqWnd_MainWnd;
class CDecSpeedWnd_MainWnd;
class CDelayCustomizeWnd;
class CDistortionCustomizeWnd;
class CDivider2_MainWnd;
class CDivider3_MainWnd;
class CDivider4_MainWnd;
class CDivider5_MainWnd;
class CDivider_MainWnd;
class CEQ100Label_MainWnd;
class CEQ100Slider_MainWnd;
class CEQ10KLabel_MainWnd;
class CEQ10KSlider_MainWnd;
class CEQ125Label_MainWnd;
class CEQ125Slider_MainWnd;
class CEQ12_5KLabel_MainWnd;
class CEQ12_5KSlider_MainWnd;
class CEQ160Label_MainWnd;
class CEQ160Slider_MainWnd;
class CEQ16KLabel_MainWnd;
class CEQ16KSlider_MainWnd;
class CEQ1KLabel_MainWnd;
class CEQ1KSlider_MainWnd;
class CEQ1_25KLabel_MainWnd;
class CEQ1_25KSlider_MainWnd;
class CEQ1_6KLabel_MainWnd;
class CEQ1_6KSlider_MainWnd;
class CEQ200Label_MainWnd;
class CEQ200Slider_MainWnd;
class CEQ20KLabel_MainWnd;
class CEQ20KSlider_MainWnd;
class CEQ20Label_MainWnd;
class CEQ20Slider_MainWnd;
class CEQ250Label_MainWnd;
class CEQ250Slider_MainWnd;
class CEQ25Label_MainWnd;
class CEQ25Slider_MainWnd;
class CEQ2KLabel_MainWnd;
class CEQ2KSlider_MainWnd;
class CEQ2_5KLabel_MainWnd;
class CEQ2_5KSlider_MainWnd;
class CEQ315Label_MainWnd;
class CEQ315Slider_MainWnd;
class CEQ31_5Label_MainWnd;
class CEQ31_5Slider_MainWnd;
class CEQ3_15KLabel_MainWnd;
class CEQ3_15KSlider_MainWnd;
class CEQ400Label_MainWnd;
class CEQ400Slider_MainWnd;
class CEQ40Label_MainWnd;
class CEQ40Slider_MainWnd;
class CEQ4KLabel_MainWnd;
class CEQ4KSlider_MainWnd;
class CEQ500Label_MainWnd;
class CEQ500Slider_MainWnd;
class CEQ50Label_MainWnd;
class CEQ50Slider_MainWnd;
class CEQ5KLabel_MainWnd;
class CEQ5KSlider_MainWnd;
class CEQ630Label_MainWnd;
class CEQ630Slider_MainWnd;
class CEQ63Label_MainWnd;
class CEQ63Slider_MainWnd;
class CEQ6_3KLabel_MainWnd;
class CEQ6_3KSlider_MainWnd;
class CEQ800Label_MainWnd;
class CEQ800Slider_MainWnd;
class CEQ80Label_MainWnd;
class CEQ80Slider_MainWnd;
class CEQ8KLabel_MainWnd;
class CEQ8KSlider_MainWnd;
class CExplorer;
class CExplorerBar;
class CFlangerCustomizeWnd;
class CFreqLabel_MainWnd;
class CFreqSlider_MainWnd;
class CGargleCustomizeWnd;
class CIncFreqWnd_MainWnd;
class CIncSpeedWnd_MainWnd;
class CKeySettingWnd_MainWnd;
class CLAMECommandLineWnd;
class CLimitSettingWnd_MainWnd;
class CLyricsManager;
class CMenu_MainWnd;
class CMetronomeWnd_MainWnd;
class COpenURLWnd;
class COutKeySettingWnd_MainWnd;
class CPanLabel_MainWnd;
class CPanSlider_MainWnd;
class CPitchAnalyser;
class CPitchLabel_MainWnd;
class CPitchSlider_MainWnd;
class CPlayListView_MainWnd;
class CPlayPositionWnd;
class CPlayRangeWnd;
class CPresetNameInputWnd;
class CReverbCustomizeWnd;
class CSound;
class CSpeedLabel_MainWnd;
class CSpeedSlider_MainWnd;
class CTab_MainWnd;
class CTimeLabel_MainWnd;
class CTimeSlider_MainWnd;
class CTimerPlayWnd_MainWnd;
class CToolBar_MainWnd;
class CVideoScreenWnd_MainWnd;
class CVideoScreen_MainWnd;
class CVolumeLabel_MainWnd;
class CVolumeSlider_MainWnd;
#include <cstdlib>
#include <memory>
#include <vector>
#include "../Common/SnapWnd.h"
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// メインウィンドウの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMainWnd : public CSnapWnd
{
public: // 関数

	CMainWnd(CApp & app);
	virtual ~CMainWnd();
	virtual void AddDropFiles(HDROP hdrop, BOOL bClear);
	virtual void AddFile(LPCTSTR lpszFilePath);
	virtual void AddMarker();
	virtual void AddPreset();
	virtual void AddPreset(tstring strPreset);
	virtual void ChangeCurPlayTab();
	virtual BOOL CheckLoop();
	virtual void CopyTime();
	virtual BOOL Create() {
		return CSnapWnd::Create(_T("Hayaemon_MainWndClass"));
	}
	virtual void CreateNewList(BOOL bChangeFocus = TRUE);
	virtual BOOL CreateControls(BOOL bFirst, BOOL bVideoScreenVisible,
		BOOL bTimeSliderVisible, BOOL bExplorerVisible, BOOL bSpeedVisible,
		BOOL bFreqVisible, BOOL bPitchVisible, BOOL bVolumeVisible,
		BOOL bPanVisible, BOOL bEQVisible, BOOL bTabVisible);
	virtual void DeleteArrayList(int nList);
	virtual void DeleteMarker();
	virtual void DeletePreset();
	virtual void DownFreq(double freq);
	virtual void DownPitch(double pitch);
	virtual void DownSpeed(double speed);
	virtual void DownVolume(int volume);
	virtual void Forward();
	virtual void ForwardSeconds(int seconds);
	virtual void Head();
	virtual void LoadSettings(const PCTSTR & pFilePath);
	virtual void MoveList(int nFrom, int nTo);
	virtual BOOL OpenFile(LPCTSTR lpszFilePath, int nCount = 1);
	virtual void OpenInitFile();
	virtual void OpenInitFileAfterShow();
	virtual BOOL OpenNext();
	virtual BOOL OpenPrevious();
	virtual BOOL OpenRandom();
	virtual void Pause();
	virtual BOOL Play();
	virtual void Play(int n);
	virtual void PlayNext(BOOL bPlay, BOOL bFadeoutCancel);
	virtual void PlayPrevious();
	virtual void ResetAllControlPos();
	virtual void ResetCurFileNum();
	virtual void ResetFreq();
	virtual void ResetPitch();
	virtual void ResetSize();
	virtual void ResetSpeed();
	virtual void ResetVolume();
	virtual void Rewind();
	virtual void ReturnSeconds(int seconds);
	virtual void SavePreset(PCTSTR pFilePath);
	virtual void SaveSettings(const PCTSTR & pFilePath);
	virtual void SetABLoopA(QWORD pos);
	virtual void SetABLoopA();
	virtual void SetABLoopA_Sec(double dTime);
	virtual void SetABLoopB();
	virtual void SetABLoopB_Sec(double dTime);
	virtual void SetABLoopASetting();
	virtual void SetABLoopBSetting();
	virtual void SetAllLoop();
	virtual void SetAllEffects();
	virtual void SetContinue();
	virtual void SetVideoScreenVisible();
	virtual void SetTimeSliderVisible();
	virtual void SetExplorerVisible();
	virtual void SetSpeedVisible();
	virtual void SetFreqVisible();
	virtual void SetPitchVisible();
	virtual void SetVolumeVisible();
	virtual void SetPanVisible();
	virtual void SetCountLoop();
	virtual void SetCountLoop(int nCount);
	virtual void SetCountLoop(BOOL nCountLoop, int nCount);
	virtual void SetDoubleRun();
	virtual void SetEQ20(LONG lEQ20);
	virtual void SetEQ25(LONG lEQ25);
	virtual void SetEQ31_5(LONG lEQ31_5);
	virtual void SetEQ40(LONG lEQ40);
	virtual void SetEQ50(LONG lEQ50);
	virtual void SetEQ63(LONG lEQ63);
	virtual void SetEQ80(LONG lEQ80);
	virtual void SetEQ100(LONG lEQ100);
	virtual void SetEQ125(LONG lEQ125);
	virtual void SetEQ160(LONG lEQ160);
	virtual void SetEQ200(LONG lEQ200);
	virtual void SetEQ250(LONG lEQ250);
	virtual void SetEQ315(LONG lEQ315);
	virtual void SetEQ400(LONG lEQ400);
	virtual void SetEQ500(LONG lEQ500);
	virtual void SetEQ630(LONG lEQ630);
	virtual void SetEQ800(LONG lEQ800);
	virtual void SetEQ1K(LONG lEQ1K);
	virtual void SetEQ1_25K(LONG lEQ1_25K);
	virtual void SetEQ1_6K(LONG lEQ1_6K);
	virtual void SetEQ2K(LONG lEQ2K);
	virtual void SetEQ2_5K(LONG lEQ2_5K);
	virtual void SetEQ3_15K(LONG lEQ3_15K);
	virtual void SetEQ4K(LONG lEQ4K);
	virtual void SetEQ5K(LONG lEQ5K);
	virtual void SetEQ6_3K(LONG lEQ6_3K);
	virtual void SetEQ8K(LONG lEQ8K);
	virtual void SetEQ10K(LONG lEQ10K);
	virtual void SetEQ12_5K(LONG lEQ12_5K);
	virtual void SetEQ16K(LONG lEQ16K);
	virtual void SetEQ20K(LONG lEQ20K);
	virtual void SetEQ(LONG lEQ20, LONG lEQ25, LONG lEQ31_5, LONG lEQ40,
					   LONG lEQ50, LONG lEQ63, LONG lEQ80, LONG lEQ100,
					   LONG lEQ125, LONG lEQ160, LONG lEQ200, LONG lEQ250,
					   LONG lEQ315, LONG lEQ400, LONG lEQ500, LONG lEQ630,
					   LONG lEQ800, LONG lEQ1K, LONG lEQ1_25K, LONG lEQ1_6K,
					   LONG lEQ2K, LONG lEQ2_5K, LONG lEQ3_15K, LONG lEQ4K,
					   LONG lEQ5K, LONG lEQ6_3K, LONG lEQ8K, LONG lEQ10K,
					   LONG lEQ12_5K, LONG lEQ16K, LONG lEQ20K);
	virtual void SetEQVisible();
	virtual void SetFullScreen();
	virtual void SetIncFreq();
	virtual void SetIncFreq(double nSecond, double nIncFreq);
	virtual void SetIncFreq(double nIncFreq);
	virtual void SetIncFreq(BOOL bIncFreq, double nSecond);
	virtual void SetIncSpeed();
	virtual void SetIncSpeed(double nSecond, double nIncSpeed);
	virtual void SetIncSpeed(double nIncSpeed);
	virtual void SetIncSpeed(BOOL bIncSpeed, double nSecond);
	virtual void SetDecFreq();
	virtual void SetDecFreq(double nSecond, double nDecFreq);
	virtual void SetDecFreq(double nDecFreq);
	virtual void SetDecFreq(BOOL bDecFreq, double nSecond);
	virtual void SetDecSpeed();
	virtual void SetDecSpeed(double nSecond, double nIncSpeed);
	virtual void SetDecSpeed(double nIncSpeed);
	virtual void SetDecSpeed(BOOL bIncSpeed, double nSecond);
	virtual void SetEarTraining();
	virtual void SetEarTraining(BOOL bEarTraining);
	virtual void SetInstantLoop();
	virtual void SetPositionAuto();
	virtual void SetKeySetting();
	virtual void SetLimit();
	virtual void SetLimit(double dMinSpeed, double dMaxSpeed,
						  double dMinFreq, double dMaxFreq,
						  double dMinPitch, double dMaxPitch);
	virtual void SetMarkerPlay();
	virtual void SetMetronome();
	virtual void SetMetronome(int nBpm);
	virtual void StopMetronome();
	virtual void SetChangeLR();
	virtual void SetChangeLR(BOOL bChangeLR);
	virtual void SetNextMarker();
	virtual void SetFocusNextControl();
	virtual void SetFocusNextTab();
	virtual void SetLAMECommandLine(tstring strCommandLine);
	virtual void SetLowBattery();
	virtual void SetLowBattery(BOOL bLowBattery);
	virtual void SetNormalize();
	virtual void SetNormalize(BOOL bNormalize);
	virtual void SetNoSense();
	virtual void SetNoSense(BOOL bNoSense);
	virtual void SetOnlyLeft();
	virtual void SetOnlyLeft(BOOL bOnlyLeft);
	virtual void SetOnlyRight();
	virtual void SetOnlyRight(BOOL bOnlyRight);
	virtual void SetOutKeySetting();
	virtual void SetPlayListVisible();
	virtual void SetPreset(int n);
	virtual void SetPreviousNextMenuState();
	virtual void SetPrevMarker();
	virtual void SetRandom();
	virtual void SetReverse();
	virtual void SetReverse(BOOL bReverse);
	virtual void SetRecord();
	virtual void SetRecord(BOOL bRecord);
	virtual void SetRecordNoise(BOOL bRecordNoise);
	virtual void SetSeconds(double fSeconds);
	virtual void SetSingleLoop();
	virtual void SetSpeed(double dSpeed);
	virtual void SetTabVisible();
	virtual void SetTime(QWORD qwTime, BOOL bReset = TRUE);
	virtual void SetTimerPlay();
	virtual void SetTimerPlay(int nHour, int nMinute);
	virtual void SetTimerPlay(BOOL bTimerPlay);
	virtual void SetTimerStop(int nHour, int nMinute);
	virtual void SetTimerStop(BOOL bTimerStop);
	virtual void SetTopMost();
	virtual void SetFreq(double dFreq);
	virtual void SetPan(int nPan);
	virtual void SetPitch(double dPitch);
	virtual void SetPlayPosition();
	virtual void SetPlayRange();
	virtual void SetPlayRange(double dStartSeconds, double dEndSeconds);
	virtual void SetReverb(BOOL bReverb);
	virtual void Set3DReverb(BOOL b3DReverb);
	virtual void SetDelay(BOOL bDelay);
	virtual void SetChorus(BOOL bChorus);
	virtual void SetCompressor(BOOL bCompressor);
	virtual void SetFlanger(BOOL bFlanger);
	virtual void SetGargle(BOOL bGargle);
	virtual void SetDistortion(BOOL bDistortion);
	virtual void SetMonoral();
	virtual void SetMonoral(BOOL bMonoral);
	virtual void SetVideo(BOOL bVideo);
	virtual void SetVocalCancel();
	virtual void SetVocalCancel(BOOL bVocalCancel);
	virtual void SetVolume(double nVolume);
	virtual void SetWave(BOOL bWave);
	virtual void Show3DReverbCustomizeWnd();
	virtual void ShowChorusCustomizeWnd();
	virtual void ShowCompressorCustomizeWnd();
	virtual void ShowDelayCustomizeWnd();
	virtual void ShowDistortionCustomizeWnd();
	virtual void ShowFlangerCustomizeWnd();
	virtual void ShowGargleCustomizeWnd();
	virtual void ShowLAMECommandLineWnd();
	virtual void ShowOpenURLWnd(BOOL bAdd = FALSE);
	virtual void ShowOpenFileDialog(BOOL bClear);
	virtual void ShowOpenFolderDialog(BOOL bClear);
	virtual void ShowReverbCustomizeWnd();
	virtual void ShowSaveFileDialog();
	virtual void ShowSaveAllFileDialog();
	virtual void ShowTime(BOOL bReset = TRUE);
	virtual void StartRewind();
	virtual void StartForward();
	virtual void StartLyrics();
	virtual void StartPitchAnalyser();
	virtual void StartUpdateInfo();
	virtual void StopRewind();
	virtual void StopForward();
	virtual void Stop(BOOL bForce = TRUE);
	virtual void Tweet();
	virtual void UpFreq(double freq);
	virtual void UpPitch(double pitch);
	virtual void UpSpeed(double speed);
	virtual void UpVolume(int volume);
	virtual void WriteInitFile();

	// メッセージ
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnClose();
	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual HBRUSH OnCtlColorStatic(HDC hDc, HWND hWnd);
	virtual void OnDestroy();
	virtual void OnDropFiles(HDROP hdrop);
	virtual void OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual void OnMouseMove(int x, int y, UINT keyFlags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);
	virtual void OnSize(UINT state, int cx, int cy);
	virtual void OnSysCommand(UINT cmd, int x, int y);
	virtual void OnTray(UINT uMsg);
	virtual void OnHotKey(int idHotKey, UINT fuModifiers, UINT vk);
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos);
	virtual BOOL OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg);
	virtual void OnTimer(UINT id);

	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static void UpdateThreadProc(void * pParam);
	static void UpdateTimeThreadProc(void * pParam);
	static void UpdateLyricsThreadProc(void * pParam);
	static void UpdatePitchAnalyserThreadProc(void * pParam);

private:
	const TCHAR* EscapeKeystr(const TCHAR* src);
	const tstring UnEscapeKeystr(const tstring src);

protected: // メンバ変数

	CApp & m_rApp;
	std::unique_ptr<CMenu_MainWnd> m_menu;
	std::unique_ptr<CDivider_MainWnd> m_divider1;
	std::unique_ptr<CToolBar_MainWnd> m_toolBar;
	std::unique_ptr<CTimeLabel_MainWnd> m_timeLabel;
	std::unique_ptr<CVideoScreen_MainWnd> m_videoScreen;
	std::unique_ptr<CTimeSlider_MainWnd> m_timeSlider;
	std::unique_ptr<CDivider2_MainWnd> m_divider2;
	std::unique_ptr<CExplorerBar> m_explorerBar;
	std::unique_ptr<CExplorer> m_explorer;
	std::unique_ptr<CSpeedLabel_MainWnd> m_speedLabel;
	std::unique_ptr<CSpeedSlider_MainWnd> m_speedSlider;
	std::unique_ptr<CFreqLabel_MainWnd> m_freqLabel;
	std::unique_ptr<CFreqSlider_MainWnd> m_freqSlider;
	std::unique_ptr<CPitchLabel_MainWnd> m_pitchLabel;
	std::unique_ptr<CPitchSlider_MainWnd> m_pitchSlider;
	std::unique_ptr<CDivider3_MainWnd> m_divider3;
	std::unique_ptr<CVolumeLabel_MainWnd> m_volumeLabel;
	std::unique_ptr<CVolumeSlider_MainWnd> m_volumeSlider;
	std::unique_ptr<CPanLabel_MainWnd> m_panLabel;
	std::unique_ptr<CPanSlider_MainWnd> m_panSlider;
	std::unique_ptr<CDivider4_MainWnd> m_divider4;
	std::unique_ptr<CEQ20Label_MainWnd> m_eq20Label;
	std::unique_ptr<CEQ20Slider_MainWnd> m_eq20Slider;
	std::unique_ptr<CEQ25Label_MainWnd> m_eq25Label;
	std::unique_ptr<CEQ25Slider_MainWnd> m_eq25Slider;
	std::unique_ptr<CEQ31_5Label_MainWnd> m_eq31_5Label;
	std::unique_ptr<CEQ31_5Slider_MainWnd> m_eq31_5Slider;
	std::unique_ptr<CEQ40Label_MainWnd> m_eq40Label;
	std::unique_ptr<CEQ40Slider_MainWnd> m_eq40Slider;
	std::unique_ptr<CEQ50Label_MainWnd> m_eq50Label;
	std::unique_ptr<CEQ50Slider_MainWnd> m_eq50Slider;
	std::unique_ptr<CEQ63Label_MainWnd> m_eq63Label;
	std::unique_ptr<CEQ63Slider_MainWnd> m_eq63Slider;
	std::unique_ptr<CEQ80Label_MainWnd> m_eq80Label;
	std::unique_ptr<CEQ80Slider_MainWnd> m_eq80Slider;
	std::unique_ptr<CEQ100Label_MainWnd> m_eq100Label;
	std::unique_ptr<CEQ100Slider_MainWnd> m_eq100Slider;
	std::unique_ptr<CEQ125Label_MainWnd> m_eq125Label;
	std::unique_ptr<CEQ125Slider_MainWnd> m_eq125Slider;
	std::unique_ptr<CEQ160Label_MainWnd> m_eq160Label;
	std::unique_ptr<CEQ160Slider_MainWnd> m_eq160Slider;
	std::unique_ptr<CEQ200Label_MainWnd> m_eq200Label;
	std::unique_ptr<CEQ200Slider_MainWnd> m_eq200Slider;
	std::unique_ptr<CEQ250Label_MainWnd> m_eq250Label;
	std::unique_ptr<CEQ250Slider_MainWnd> m_eq250Slider;
	std::unique_ptr<CEQ315Label_MainWnd> m_eq315Label;
	std::unique_ptr<CEQ315Slider_MainWnd> m_eq315Slider;
	std::unique_ptr<CEQ400Label_MainWnd> m_eq400Label;
	std::unique_ptr<CEQ400Slider_MainWnd> m_eq400Slider;
	std::unique_ptr<CEQ500Label_MainWnd> m_eq500Label;
	std::unique_ptr<CEQ500Slider_MainWnd> m_eq500Slider;
	std::unique_ptr<CEQ630Label_MainWnd> m_eq630Label;
	std::unique_ptr<CEQ630Slider_MainWnd> m_eq630Slider;
	std::unique_ptr<CEQ800Label_MainWnd> m_eq800Label;
	std::unique_ptr<CEQ800Slider_MainWnd> m_eq800Slider;
	std::unique_ptr<CEQ1KLabel_MainWnd> m_eq1kLabel;
	std::unique_ptr<CEQ1KSlider_MainWnd> m_eq1kSlider;
	std::unique_ptr<CEQ1_25KLabel_MainWnd> m_eq1_25kLabel;
	std::unique_ptr<CEQ1_25KSlider_MainWnd> m_eq1_25kSlider;
	std::unique_ptr<CEQ1_6KLabel_MainWnd> m_eq1_6kLabel;
	std::unique_ptr<CEQ1_6KSlider_MainWnd> m_eq1_6kSlider;
	std::unique_ptr<CEQ2KLabel_MainWnd> m_eq2kLabel;
	std::unique_ptr<CEQ2KSlider_MainWnd> m_eq2kSlider;
	std::unique_ptr<CEQ2_5KLabel_MainWnd> m_eq2_5kLabel;
	std::unique_ptr<CEQ2_5KSlider_MainWnd> m_eq2_5kSlider;
	std::unique_ptr<CEQ3_15KLabel_MainWnd> m_eq3_15kLabel;
	std::unique_ptr<CEQ3_15KSlider_MainWnd> m_eq3_15kSlider;
	std::unique_ptr<CEQ4KLabel_MainWnd> m_eq4kLabel;
	std::unique_ptr<CEQ4KSlider_MainWnd> m_eq4kSlider;
	std::unique_ptr<CEQ5KLabel_MainWnd> m_eq5kLabel;
	std::unique_ptr<CEQ5KSlider_MainWnd> m_eq5kSlider;
	std::unique_ptr<CEQ6_3KLabel_MainWnd> m_eq6_3kLabel;
	std::unique_ptr<CEQ6_3KSlider_MainWnd> m_eq6_3kSlider;
	std::unique_ptr<CEQ8KLabel_MainWnd> m_eq8kLabel;
	std::unique_ptr<CEQ8KSlider_MainWnd> m_eq8kSlider;
	std::unique_ptr<CEQ10KLabel_MainWnd> m_eq10kLabel;
	std::unique_ptr<CEQ10KSlider_MainWnd> m_eq10kSlider;
	std::unique_ptr<CEQ12_5KLabel_MainWnd> m_eq12_5kLabel;
	std::unique_ptr<CEQ12_5KSlider_MainWnd> m_eq12_5kSlider;
	std::unique_ptr<CEQ16KLabel_MainWnd> m_eq16kLabel;
	std::unique_ptr<CEQ16KSlider_MainWnd> m_eq16kSlider;
	std::unique_ptr<CEQ20KLabel_MainWnd> m_eq20kLabel;
	std::unique_ptr<CEQ20KSlider_MainWnd> m_eq20kSlider;
	std::unique_ptr<CDivider5_MainWnd> m_divider5;
	std::unique_ptr<CTab_MainWnd> m_tab;
	std::vector<CPlayListView_MainWnd*> m_arrayList;
	std::unique_ptr<CLimitSettingWnd_MainWnd> limitSettingWnd;
	std::unique_ptr<CKeySettingWnd_MainWnd> keySettingWnd;
	std::unique_ptr<COutKeySettingWnd_MainWnd> outKeySettingWnd;
	std::unique_ptr<CTimerPlayWnd_MainWnd> timerPlayWnd;
	std::unique_ptr<CPlayPositionWnd> playPositionWnd;
	std::unique_ptr<COpenURLWnd> m_openURLWnd;
	std::unique_ptr<CPlayRangeWnd> playRangeWnd;
	std::unique_ptr<CLAMECommandLineWnd> m_lameCommandLineWnd;
	std::unique_ptr<CReverbCustomizeWnd> m_reverbCustomizeWnd;
	std::unique_ptr<C3DReverbCustomizeWnd> m_3dReverbCustomizeWnd;
	std::unique_ptr<CDelayCustomizeWnd> m_delayCustomizeWnd;
	std::unique_ptr<CChorusCustomizeWnd> m_chorusCustomizeWnd;
	std::unique_ptr<CCompressorCustomizeWnd> m_compressorCustomizeWnd;
	std::unique_ptr<CFlangerCustomizeWnd> m_flangerCustomizeWnd;
	std::unique_ptr<CGargleCustomizeWnd> m_gargleCustomizeWnd;
	std::unique_ptr<CDistortionCustomizeWnd> m_distortionCustomizeWnd;
	std::unique_ptr<CPresetNameInputWnd> presetNameInputWnd;
	std::unique_ptr<CABLoopPosWnd> m_abLoopPosWnd;
	std::unique_ptr<CIncSpeedWnd_MainWnd> incSpeedWnd;
	std::unique_ptr<CIncFreqWnd_MainWnd> incFreqWnd;
	std::unique_ptr<CDecSpeedWnd_MainWnd> decSpeedWnd;
	std::unique_ptr<CDecFreqWnd_MainWnd> decFreqWnd;
	std::unique_ptr<CCountLoopWnd_MainWnd> countLoopWnd;
	std::unique_ptr<CVideoScreenWnd_MainWnd> videoScreenWnd;
	std::unique_ptr<CMetronomeWnd_MainWnd> metronomeWnd;
	std::unique_ptr<CLyricsManager> lyricsManager;
	std::unique_ptr<CPitchAnalyser> m_pitchAnalyser;

	std::unique_ptr<CSound> m_sound;
	std::unique_ptr<CSound> m_soundEffect; // 効果音

	const int controlOffset; // コントロール間の間隔
	BOOL isInitFileRead; // INI ファイルがすでに読み込まれたかどうか
	BOOL bTimerPlay; // タイマー再生が予約されているかどうか
	BOOL bTimerPlayNextDay; // タイマー再生を翌日にするかどうか
	BOOL bTimerStop; // タイマー停止が予約されているかどうか
	BOOL bTimerStopNextDay; // タイマー停止を翌日にするかどうか
	BOOL bReverb; // リバーブが有効かどうか
	BOOL b3DReverb; // ３Ｄリバーブが有効かどうか
	BOOL bDelay; // ディレイが有効かどうか
	BOOL bChorus; // コーラスが有効かどうか
	BOOL bCompressor; // コンプレッサーが有効かどうか
	BOOL bFlanger; // フランジャーが有効かどうか
	BOOL bGargle; // ガーグルが有効かどうか
	BOOL bDistortion; // ディストーションが有効かどうか
	BOOL bMarkerPlay; // マーカー再生をするかどうか
	BOOL bCountLoop; // 回数ループをするかどうか
	BOOL bInstantLoop; // マーカー追加時にループするかどうか
	BOOL bSetPositionAuto; // マーカー位置変更時に再生位置を変更するかどうか
	BOOL m_bVideo; // ビデオを再生中かどうか
	BOOL m_bFullScreen; // フルスクリーンかどうか
	BOOL m_bFinish; // 再生が完了したかどうか
	BOOL m_bExplorerResizing; // エクスプローラのリサイズ中かどうか
	BOOL m_bVideoScreenResizing; // ビデオ画面のリサイズ中かどうか
	int nMinWidth; // ウィンドウの最小幅
	int nTimerPlayHour; // タイマー再生の時間
	int nTimerPlayMinute; // タイマー再生の分
	int nTimerStopHour; // タイマー停止の時間
	int nTimerStopMinute; // タイマー停止の分
	double nIncSpeed; // 再生速度をだんだん速くするパーセント
	double nIncFreq; // 再生周波数をだんだん速くするパーセント
	double nDecSpeed; // 再生速度をだんだん遅くするパーセント
	double nDecFreq; // 再生周波数をだんだん遅くするパーセント
	double nFreqVelo; // 周波数の差分（古びたレコード再生用）
	double nFreqAccel; // 周波数の差分の加速度（古びたレコード再生用）
	tstring strSaveFormat; // 前回保存したファイル形式
	int nLoopCount; // 回数ループ時のループ回数
	int nCurrentLoopCount; // 現時点でループした回数
	int nIncSpeedMode; // 再生速度をだんだん速くするモード
					   // 1 : 時間ごと, 2 : ループごと
	int nIncFreqMode; // 再生周波数をだんだん速くするモード
						   // 1 : 時間ごと, 2 : ループごと
	int nDecSpeedMode; // 再生速度をだんだん遅くするモード
					   // 1 : 時間ごと, 2 : ループごと
	int nDecFreqMode; // 再生周波数をだんだん遅くするモード
						   // 1 : 時間ごと, 2 : ループごと
	int nCurPlayTab; // 現在再生中のファイルが存在しているタブ
	DWORD dwLastTime; // 前回の時間（メトロノーム用）
	LPCTSTR lpSound; // 音（メトロノーム用）
	int m_nBpm; // テンポ（メトロノーム用）
	int m_nInterval; // 間隔（メトロノーム用）
	DWORD dwFadeoutStartTime; // フェードアウト開始時間
	int m_nLastDecimalDigit_pitch; // 前回の小数点桁数（音程）
	int m_nLastDecimalDigit_freq; // 前回の小数点桁数（再生周波数）
	int m_nLastDecimalDigit_speed; // 前回の小数点桁数（再生速度）
	double m_dStartSeconds; // 再生範囲の開始位置
	double m_dEndSeconds; // 再生範囲の停止位置
	HBRUSH m_hVideoScreenBrush;
	tstring m_strLAMECommandLine;
	HANDLE m_hUpdateThread;
	BOOL m_bRetryUpdate;
	HANDLE m_hLyricsThread;
	BOOL m_bLyricsThreadAlive;
	HANDLE m_hPitchAnalyserThread;
	BOOL m_bPitchAnalyserThreadAlive;

public: // 定数

	// タイマー ID
	enum {
		IDT_TIME = 11,
		IDT_METRONOME,
		IDT_REWIND,
		IDT_FORWARD,
		IDT_RECORD,
		IDT_LOWBATTERY,
		IDT_NOSENSE,
		IDT_EARTRAINING,
		IDT_TIMERPLAY,
		IDT_TIMERSTOP,
		IDT_INCSPEED,
		IDT_INCFREQ,
		IDT_DECSPEED,
		IDT_DECFREQ,
		IDT_FADEOUT,
		IDT_FADEOUTNEXT,
	};

public: // メンバ変数の取得・設定

	CMenu_MainWnd & GetMenu() { return *m_menu; }
	const CDivider_MainWnd & GetDivider1() const { return *m_divider1; }
	CToolBar_MainWnd & GetToolBar() { return *m_toolBar; }
	const CTimeLabel_MainWnd & GetTimeLabel() const { return *m_timeLabel; }
	const CVideoScreen_MainWnd & GetVideoScreen() const {
		return *m_videoScreen;
	}
	const CTimeSlider_MainWnd & GetTimeSlider() const { return *m_timeSlider; }
	const CDivider2_MainWnd & GetDivider2() const { return *m_divider2; }
	CExplorerBar & GetExplorerBar() { return *m_explorerBar; }
	CExplorer & GetExplorer() { return *m_explorer; }
	CSpeedLabel_MainWnd & GetSpeedLabel() { return *m_speedLabel; }
	CSpeedSlider_MainWnd & GetSpeedSlider() { return *m_speedSlider; }
	CFreqLabel_MainWnd & GetFreqLabel() { return *m_freqLabel; }
	CFreqSlider_MainWnd & GetFreqSlider() { return *m_freqSlider; }
	CPitchLabel_MainWnd & GetPitchLabel() { return *m_pitchLabel; }
	CPitchSlider_MainWnd & GetPitchSlider() { return *m_pitchSlider; }
	const CDivider3_MainWnd & GetDivider3() const { return *m_divider3; }
	CVolumeLabel_MainWnd & GetVolumeLabel() { return *m_volumeLabel; }
	CVolumeSlider_MainWnd & GetVolumeSlider() { return *m_volumeSlider; }
	CPanLabel_MainWnd & GetPanLabel() { return *m_panLabel; }
	CPanSlider_MainWnd & GetPanSlider() { return *m_panSlider; }
	const CDivider4_MainWnd & GetDivider4() const { return *m_divider4; }
	CEQ20Label_MainWnd & GetEQ20Label() { return *m_eq20Label; }
	CEQ20Slider_MainWnd & GetEQ20Slider() { return *m_eq20Slider; }
	CEQ25Label_MainWnd & GetEQ25Label() { return *m_eq25Label; }
	CEQ25Slider_MainWnd & GetEQ25Slider() { return *m_eq25Slider; }
	CEQ31_5Label_MainWnd & GetEQ31_5Label() { return *m_eq31_5Label; }
	CEQ31_5Slider_MainWnd & GetEQ31_5Slider() { return *m_eq31_5Slider; }
	CEQ40Label_MainWnd & GetEQ40Label() { return *m_eq40Label; }
	CEQ40Slider_MainWnd & GetEQ40Slider() { return *m_eq40Slider; }
	CEQ50Label_MainWnd & GetEQ50Label() { return *m_eq50Label; }
	CEQ50Slider_MainWnd & GetEQ50Slider() { return *m_eq50Slider; }
	CEQ63Label_MainWnd & GetEQ63Label() { return *m_eq63Label; }
	CEQ63Slider_MainWnd & GetEQ63Slider() { return *m_eq63Slider; }
	CEQ80Label_MainWnd & GetEQ80Label() { return *m_eq80Label; }
	CEQ80Slider_MainWnd & GetEQ80Slider() { return *m_eq80Slider; }
	CEQ100Label_MainWnd & GetEQ100Label() { return *m_eq100Label; }
	CEQ100Slider_MainWnd & GetEQ100Slider() { return *m_eq100Slider; }
	CEQ125Label_MainWnd & GetEQ125Label() { return *m_eq125Label; }
	CEQ125Slider_MainWnd & GetEQ125Slider() { return *m_eq125Slider; }
	CEQ160Label_MainWnd & GetEQ160Label() { return *m_eq160Label; }
	CEQ160Slider_MainWnd & GetEQ160Slider() { return *m_eq160Slider; }
	CEQ200Label_MainWnd & GetEQ200Label() { return *m_eq200Label; }
	CEQ200Slider_MainWnd & GetEQ200Slider() { return *m_eq200Slider; }
	CEQ250Label_MainWnd & GetEQ250Label() { return *m_eq250Label; }
	CEQ250Slider_MainWnd & GetEQ250Slider() { return *m_eq250Slider; }
	CEQ315Label_MainWnd & GetEQ315Label() { return *m_eq315Label; }
	CEQ315Slider_MainWnd & GetEQ315Slider() { return *m_eq315Slider; }
	CEQ400Label_MainWnd & GetEQ400Label() { return *m_eq400Label; }
	CEQ400Slider_MainWnd & GetEQ400Slider() { return *m_eq400Slider; }
	CEQ500Label_MainWnd & GetEQ500Label() { return *m_eq500Label; }
	CEQ500Slider_MainWnd & GetEQ500Slider() { return *m_eq500Slider; }
	CEQ630Label_MainWnd & GetEQ630Label() { return *m_eq630Label; }
	CEQ630Slider_MainWnd & GetEQ630Slider() { return *m_eq630Slider; }
	CEQ800Label_MainWnd & GetEQ800Label() { return *m_eq800Label; }
	CEQ800Slider_MainWnd & GetEQ800Slider() { return *m_eq800Slider; }
	CEQ1KLabel_MainWnd & GetEQ1KLabel() { return *m_eq1kLabel; }
	CEQ1KSlider_MainWnd & GetEQ1KSlider() { return *m_eq1kSlider; }
	CEQ1_25KLabel_MainWnd & GetEQ1_25KLabel() { return *m_eq1_25kLabel; }
	CEQ1_25KSlider_MainWnd & GetEQ1_25KSlider() { return *m_eq1_25kSlider; }
	CEQ1_6KLabel_MainWnd & GetEQ1_6KLabel() { return *m_eq1_6kLabel; }
	CEQ1_6KSlider_MainWnd & GetEQ1_6KSlider() { return *m_eq1_6kSlider; }
	CEQ2KLabel_MainWnd & GetEQ2KLabel() { return *m_eq2kLabel; }
	CEQ2KSlider_MainWnd & GetEQ2KSlider() { return *m_eq2kSlider; }
	CEQ2_5KLabel_MainWnd & GetEQ2_5KLabel() { return *m_eq2_5kLabel; }
	CEQ2_5KSlider_MainWnd & GetEQ2_5KSlider() { return *m_eq2_5kSlider; }
	CEQ3_15KLabel_MainWnd & GetEQ3_15KLabel() { return *m_eq3_15kLabel; }
	CEQ3_15KSlider_MainWnd & GetEQ3_15KSlider() { return *m_eq3_15kSlider; }
	CEQ4KLabel_MainWnd & GetEQ4KLabel() { return *m_eq4kLabel; }
	CEQ4KSlider_MainWnd & GetEQ4KSlider() { return *m_eq4kSlider; }
	CEQ5KLabel_MainWnd & GetEQ5KLabel() { return *m_eq5kLabel; }
	CEQ5KSlider_MainWnd & GetEQ5KSlider() { return *m_eq5kSlider; }
	CEQ6_3KLabel_MainWnd & GetEQ6_3KLabel() { return *m_eq6_3kLabel; }
	CEQ6_3KSlider_MainWnd & GetEQ6_3KSlider() { return *m_eq6_3kSlider; }
	CEQ8KLabel_MainWnd & GetEQ8KLabel() { return *m_eq8kLabel; }
	CEQ8KSlider_MainWnd & GetEQ8KSlider() { return *m_eq8kSlider; }
	CEQ10KLabel_MainWnd & GetEQ10KLabel() { return *m_eq10kLabel; }
	CEQ10KSlider_MainWnd & GetEQ10KSlider() { return *m_eq10kSlider; }
	CEQ12_5KLabel_MainWnd & GetEQ12_5KLabel() { return *m_eq12_5kLabel; }
	CEQ12_5KSlider_MainWnd & GetEQ12_5KSlider() { return *m_eq12_5kSlider; }
	CEQ16KLabel_MainWnd & GetEQ16KLabel() { return *m_eq16kLabel; }
	CEQ16KSlider_MainWnd & GetEQ16KSlider() { return *m_eq16kSlider; }
	CEQ20KLabel_MainWnd & GetEQ20KLabel() { return *m_eq20kLabel; }
	CEQ20KSlider_MainWnd & GetEQ20KSlider() { return *m_eq20kSlider; }
	const CDivider5_MainWnd & GetDivider5() const { return *m_divider5; }
	CTab_MainWnd & GetTab() { return *m_tab; }
	CPlayListView_MainWnd & GetPlayList();
	CPlayListView_MainWnd & GetCurPlayList() {
		return *m_arrayList[nCurPlayTab];
	}
	CPlayListView_MainWnd & GetPlayList(int n) {
		return *m_arrayList[n];
	}
	std::vector<CPlayListView_MainWnd*> GetArrayList() {
		return m_arrayList;
	}
	CSound & GetSound() { return *m_sound; }
	CPlayPositionWnd & GetPlayPositionWnd() { return *playPositionWnd; }
	COpenURLWnd & GetOpenURLWnd() { return *m_openURLWnd; }
	CPlayRangeWnd & GetPlayRangeWnd() { return *playRangeWnd; }
	CLAMECommandLineWnd & GetLAMECommandLineWnd() {
		return *m_lameCommandLineWnd;
	}
	CReverbCustomizeWnd & GetReverbCustomizeWnd() {
		return *m_reverbCustomizeWnd;
	}
	C3DReverbCustomizeWnd & Get3DReverbCustomizeWnd() {
		return *m_3dReverbCustomizeWnd;
	}
	CDelayCustomizeWnd & GetDelayCustomizeWnd() {
		return *m_delayCustomizeWnd;
	}
	CChorusCustomizeWnd & GetChorusCustomizeWnd() {
		return *m_chorusCustomizeWnd;
	}
	CCompressorCustomizeWnd & GetCompressorCustomizeWnd() {
		return *m_compressorCustomizeWnd;
	}
	CFlangerCustomizeWnd & GetFlangerCustomizeWnd() {
		return *m_flangerCustomizeWnd;
	}
	CGargleCustomizeWnd & GetGargleCustomizeWnd() {
		return *m_gargleCustomizeWnd;
	}
	CPresetNameInputWnd & GetPresetNameInputWnd() {
		return *presetNameInputWnd;
	}
	CABLoopPosWnd & GetABLoopPosWnd() {
		return *m_abLoopPosWnd;
	}
	int GetTimeSliderHeight();
	CVideoScreenWnd_MainWnd & GetVideoScreenWnd() { return *videoScreenWnd; }
	CLyricsManager & GetLyricsManager() { return *lyricsManager; }
	CPitchAnalyser & GetPitchAnalyser() { return *m_pitchAnalyser; }

	int GetControlBarHeight();
	int GetControlBar2Height();
	int GetEQHeight();

	int GetControlOffset() const { return controlOffset; }
	int GetBpm() const { return m_nBpm; }

	BOOL IsReverb() const { return bReverb; }
	BOOL Is3DReverb() const { return b3DReverb; }
	BOOL IsDelay() const { return bDelay; }
	BOOL IsChorus() const { return bChorus; }
	BOOL IsCompressor() const { return bCompressor; }
	BOOL IsFlanger() const { return bFlanger; }
	BOOL IsGargle() const { return bGargle; }
	BOOL IsDistortion() const { return bDistortion; }
	BOOL IsMarkerPlay() const { return bMarkerPlay; }
	BOOL IsSetPositionAuto() const { return bSetPositionAuto; }
	BOOL IsFullScreen() const { return m_bFullScreen; }
	BOOL IsVideo() const { return m_bVideo; }
	BOOL IsLyricsThreadAlive() const { return m_bLyricsThreadAlive; }
	BOOL IsPitchAnalyserThreadAlive() const {
		return m_bPitchAnalyserThreadAlive;
	}
	BOOL IsRetryUpdate() {
		BOOL bRetryUpdate = m_bRetryUpdate;
		m_bRetryUpdate = FALSE;
		return bRetryUpdate;
	}
 	void SetFinish(BOOL bFinish) { m_bFinish = bFinish; }
	void SetMinMax(int n) { nMinWidth = n; }

	tstring GetStrSaveFormat() { return strSaveFormat; }
	tstring GetStrLAMECommandLine() { return m_strLAMECommandLine; }
};
//----------------------------------------------------------------------------

#endif