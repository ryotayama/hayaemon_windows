//----------------------------------------------------------------------------
// MainWnd.h : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH

class CApp;
#include "../Common/SnapWnd.h"
#include "../Common/ToolBar.h"
#include "../Common/Static.h"
#include "Menu_MainWnd.h"
#include "RMenu_Taskbar.h"
#include "Divider_MainWnd.h"
#include "ToolBar_MainWnd.h"
#include "TimeLabel_MainWnd.h"
#include "VideoScreen_MainWnd.h"
#include "TimeSlider_MainWnd.h"
#include "Divider2_MainWnd.h"
#include "ExplorerBar.h"
#include "Explorer.h"
#include "SpeedLabel_MainWnd.h"
#include "SpeedSlider_MainWnd.h"
#include "FreqLabel_MainWnd.h"
#include "FreqSlider_MainWnd.h"
#include "PitchLabel_MainWnd.h"
#include "PitchSlider_MainWnd.h"
#include "Divider3_MainWnd.h"
#include "VolumeLabel_MainWnd.h"
#include "VolumeSlider_MainWnd.h"
#include "PanLabel_MainWnd.h"
#include "PanSlider_MainWnd.h"
#include "Divider4_MainWnd.h"
#include "EQ20Label_MainWnd.h"
#include "EQ20Slider_MainWnd.h"
#include "EQ25Label_MainWnd.h"
#include "EQ25Slider_MainWnd.h"
#include "EQ31_5Label_MainWnd.h"
#include "EQ31_5Slider_MainWnd.h"
#include "EQ40Label_MainWnd.h"
#include "EQ40Slider_MainWnd.h"
#include "EQ50Label_MainWnd.h"
#include "EQ50Slider_MainWnd.h"
#include "EQ63Label_MainWnd.h"
#include "EQ63Slider_MainWnd.h"
#include "EQ80Label_MainWnd.h"
#include "EQ80Slider_MainWnd.h"
#include "EQ100Label_MainWnd.h"
#include "EQ100Slider_MainWnd.h"
#include "EQ125Label_MainWnd.h"
#include "EQ125Slider_MainWnd.h"
#include "EQ160Label_MainWnd.h"
#include "EQ160Slider_MainWnd.h"
#include "EQ200Label_MainWnd.h"
#include "EQ200Slider_MainWnd.h"
#include "EQ250Label_MainWnd.h"
#include "EQ250Slider_MainWnd.h"
#include "EQ315Label_MainWnd.h"
#include "EQ315Slider_MainWnd.h"
#include "EQ400Label_MainWnd.h"
#include "EQ400Slider_MainWnd.h"
#include "EQ500Label_MainWnd.h"
#include "EQ500Slider_MainWnd.h"
#include "EQ630Label_MainWnd.h"
#include "EQ630Slider_MainWnd.h"
#include "EQ800Label_MainWnd.h"
#include "EQ800Slider_MainWnd.h"
#include "EQ1KLabel_MainWnd.h"
#include "EQ1KSlider_MainWnd.h"
#include "EQ1_25KLabel_MainWnd.h"
#include "EQ1_25KSlider_MainWnd.h"
#include "EQ1_6KLabel_MainWnd.h"
#include "EQ1_6KSlider_MainWnd.h"
#include "EQ2KLabel_MainWnd.h"
#include "EQ2KSlider_MainWnd.h"
#include "EQ2_5KLabel_MainWnd.h"
#include "EQ2_5KSlider_MainWnd.h"
#include "EQ3_15KLabel_MainWnd.h"
#include "EQ3_15KSlider_MainWnd.h"
#include "EQ4KLabel_MainWnd.h"
#include "EQ4KSlider_MainWnd.h"
#include "EQ5KLabel_MainWnd.h"
#include "EQ5KSlider_MainWnd.h"
#include "EQ6_3KLabel_MainWnd.h"
#include "EQ6_3KSlider_MainWnd.h"
#include "EQ8KLabel_MainWnd.h"
#include "EQ8KSlider_MainWnd.h"
#include "EQ10KLabel_MainWnd.h"
#include "EQ10KSlider_MainWnd.h"
#include "EQ12_5KLabel_MainWnd.h"
#include "EQ12_5KSlider_MainWnd.h"
#include "EQ16KLabel_MainWnd.h"
#include "EQ16KSlider_MainWnd.h"
#include "EQ20KLabel_MainWnd.h"
#include "EQ20KSlider_MainWnd.h"
#include "Divider5_MainWnd.h"
#include "Tab_MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "Sound.h"
#include "LyricsManager.h"
#include "PitchAnalyser.h"
#include "../LimitSettingWnd/LimitSettingWnd_MainWnd.h"
#include "../KeySettingWnd/KeySettingWnd_MainWnd.h"
#include "../OutKeySettingWnd/OutKeySettingWnd_MainWnd.h"
#include "../TimerPlayWnd/TimerPlayWnd_MainWnd.h"
#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
#include "../IncFreqWnd/IncFreqWnd_MainWnd.h"
#include "../DecSpeedWnd/DecSpeedWnd_MainWnd.h"
#include "../DecFreqWnd/DecFreqWnd_MainWnd.h"
#include "../CountLoopWnd/CountLoopWnd_MainWnd.h"
#include "../VideoScreenWnd/VideoScreenWnd_MainWnd.h"
#include "../MetronomeWnd/MetronomeWnd_MainWnd.h"
#include "PlayRangeWnd.h"
#include "PlayPositionWnd.h"
#include "OpenURLWnd.h"
#include "LAMECommandLineWnd.h"
#include "ReverbCustomizeWnd.h"
#include "3DReverbCustomizeWnd.h"
#include "DelayCustomizeWnd.h"
#include "ChorusCustomizeWnd.h"
#include "CompressorCustomizeWnd.h"
#include "FlangerCustomizeWnd.h"
#include "GargleCustomizeWnd.h"
#include "DistortionCustomizeWnd.h"
#include "PresetNameInputWnd.h"
#include "TwitterAuthorizeWnd.h"
#include "TweetWnd.h"
#include "ABLoopPosWnd.h"
#include <cstdlib>
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

	CMainWnd(CApp & app): controlOffset(5), m_rApp(app), m_menu(app, *this),
		m_divider1(app, *this), limitSettingWnd(m_rApp, *this),
		metronomeWnd(m_rApp, *this), lyricsManager(m_rApp, *this),
		m_pitchAnalyser(m_rApp, *this),
		keySettingWnd(m_rApp, *this), outKeySettingWnd(m_rApp, *this),
		timerPlayWnd(m_rApp, *this), countLoopWnd(m_rApp, *this),
		videoScreenWnd(m_rApp, *this),
		incSpeedWnd(m_rApp, *this), incFreqWnd(m_rApp, *this),
		decSpeedWnd(m_rApp, *this), decFreqWnd(m_rApp, *this),
		playPositionWnd(m_rApp, *this), playRangeWnd(m_rApp, *this),
		m_openURLWnd(m_rApp, *this),
		m_lameCommandLineWnd(m_rApp, *this),
		m_reverbCustomizeWnd(m_rApp, *this),
		m_3dReverbCustomizeWnd(m_rApp, *this),
		m_delayCustomizeWnd(m_rApp, *this),
		m_chorusCustomizeWnd(m_rApp, *this),
		m_compressorCustomizeWnd(m_rApp, *this),
		m_flangerCustomizeWnd(m_rApp, *this),
		m_gargleCustomizeWnd(m_rApp, *this),
		m_distortionCustomizeWnd(m_rApp, *this),
		presetNameInputWnd(m_rApp, *this),
		m_twitterAuthorizeWnd(m_rApp, *this),
		m_tweetWnd(m_rApp, *this), m_abLoopPosWnd(m_rApp, *this),
		m_toolBar(app, *this),
		m_timeLabel(app, *this), m_videoScreen(app, *this),
		m_timeSlider(app, *this),
		m_divider2(app, *this), m_explorerBar(app, *this),
		m_explorer(app, *this),
		m_speedLabel(app, *this),
		m_speedSlider(app, *this), m_freqLabel(app, *this),
		m_freqSlider(app, *this), m_pitchLabel(app, *this),
		m_divider3(app, *this), m_pitchSlider(app, *this),
		m_volumeLabel(app, *this), m_volumeSlider(app, *this),
		m_panLabel(app, *this), m_panSlider(app, *this), m_divider4(app, *this),
		m_eq20Label(app, *this), m_eq20Slider(app, *this),
		m_eq25Label(app, *this), m_eq25Slider(app, *this),
		m_eq31_5Label(app, *this), m_eq31_5Slider(app, *this),
		m_eq40Label(app, *this), m_eq40Slider(app, *this),
		m_eq50Label(app, *this), m_eq50Slider(app, *this),
		m_eq63Label(app, *this), m_eq63Slider(app, *this),
		m_eq80Label(app, *this), m_eq80Slider(app, *this),
		m_eq100Label(app, *this), m_eq100Slider(app, *this),
		m_eq125Label(app, *this), m_eq125Slider(app, *this),
		m_eq160Label(app, *this), m_eq160Slider(app, *this),
		m_eq200Label(app, *this), m_eq200Slider(app, *this),
		m_eq250Label(app, *this), m_eq250Slider(app, *this),
		m_eq315Label(app, *this), m_eq315Slider(app, *this),
		m_eq400Label(app, *this), m_eq400Slider(app, *this),
		m_eq500Label(app, *this), m_eq500Slider(app, *this),
		m_eq630Label(app, *this), m_eq630Slider(app, *this),
		m_eq800Label(app, *this), m_eq800Slider(app, *this),
		m_eq1kLabel(app, *this), m_eq1kSlider(app, *this),
		m_eq1_25kLabel(app, *this), m_eq1_25kSlider(app, *this),
		m_eq1_6kLabel(app, *this), m_eq1_6kSlider(app, *this),
		m_eq2kLabel(app, *this), m_eq2kSlider(app, *this),
		m_eq2_5kLabel(app, *this), m_eq2_5kSlider(app, *this),
		m_eq3_15kLabel(app, *this), m_eq3_15kSlider(app, *this),
		m_eq4kLabel(app, *this), m_eq4kSlider(app, *this),
		m_eq5kLabel(app, *this), m_eq5kSlider(app, *this),
		m_eq6_3kLabel(app, *this), m_eq6_3kSlider(app, *this),
		m_eq8kLabel(app, *this), m_eq8kSlider(app, *this),
		m_eq10kLabel(app, *this), m_eq10kSlider(app, *this),
		m_eq12_5kLabel(app, *this), m_eq12_5kSlider(app, *this),
		m_eq16kLabel(app, *this), m_eq16kSlider(app, *this),
		m_eq20kLabel(app, *this), m_eq20kSlider(app, *this),
		m_divider5(app, *this), m_tab(app, *this), m_sound(app, *this),
		m_soundEffect(app, *this, FALSE),
		bTimerPlay(FALSE), bTimerStop(FALSE),
		bTimerPlayNextDay(FALSE), bTimerStopNextDay(FALSE), bReverb(FALSE),
		b3DReverb(FALSE),
		bDelay(FALSE), bChorus(FALSE), bCompressor(FALSE), bFlanger(FALSE),
		bGargle(FALSE), bDistortion(FALSE),
		bMarkerPlay(FALSE), m_bVideo(FALSE),
		m_bFullScreen(FALSE), m_bFinish(FALSE),
		m_bExplorerResizing(FALSE), m_bVideoScreenResizing(FALSE),
		isInitFileRead(FALSE), m_strLAMECommandLine(_T("--preset cbr 192")),
		nMinWidth(0), nFreqVelo(0.0), nFreqAccel(0.0), nTimerPlayHour(0),
		nTimerPlayMinute(0), nTimerStopHour(0), nTimerStopMinute(0),
		nIncSpeed(0.0), nIncFreq(0.0), nDecSpeed(0.0), nDecFreq(0.0),
		bCountLoop(FALSE), bInstantLoop(FALSE), bSetPositionAuto(FALSE),
		nLoopCount(0), nCurrentLoopCount(0), nCurPlayTab(0), dwLastTime(0),
		m_nBpm(120), dwFadeoutStartTime(0),
		m_dStartSeconds(0.0), m_dEndSeconds(0.0), m_hUpdateThread(0),
		m_hLyricsThread(0), m_bLyricsThreadAlive(FALSE), m_bRetryUpdate(FALSE),
		m_hPitchAnalyserThread(0), m_bPitchAnalyserThreadAlive(FALSE)
	{ }
	virtual ~CMainWnd() { }
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
	virtual void Tweet(std::string strMessage);
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
	CMenu_MainWnd m_menu;
	CDivider_MainWnd m_divider1;
	CToolBar_MainWnd m_toolBar;
	CTimeLabel_MainWnd m_timeLabel;
	CVideoScreen_MainWnd m_videoScreen;
	CTimeSlider_MainWnd m_timeSlider;
	CDivider2_MainWnd m_divider2;
	CExplorerBar m_explorerBar;
	CExplorer m_explorer;
	CSpeedLabel_MainWnd m_speedLabel;
	CSpeedSlider_MainWnd m_speedSlider;
	CFreqLabel_MainWnd m_freqLabel;
	CFreqSlider_MainWnd m_freqSlider;
	CPitchLabel_MainWnd m_pitchLabel;
	CPitchSlider_MainWnd m_pitchSlider;
	CDivider3_MainWnd m_divider3;
	CVolumeLabel_MainWnd m_volumeLabel;
	CVolumeSlider_MainWnd m_volumeSlider;
	CPanLabel_MainWnd m_panLabel;
	CPanSlider_MainWnd m_panSlider;
	CDivider4_MainWnd m_divider4;
	CEQ20Label_MainWnd m_eq20Label;
	CEQ20Slider_MainWnd m_eq20Slider;
	CEQ25Label_MainWnd m_eq25Label;
	CEQ25Slider_MainWnd m_eq25Slider;
	CEQ31_5Label_MainWnd m_eq31_5Label;
	CEQ31_5Slider_MainWnd m_eq31_5Slider;
	CEQ40Label_MainWnd m_eq40Label;
	CEQ40Slider_MainWnd m_eq40Slider;
	CEQ50Label_MainWnd m_eq50Label;
	CEQ50Slider_MainWnd m_eq50Slider;
	CEQ63Label_MainWnd m_eq63Label;
	CEQ63Slider_MainWnd m_eq63Slider;
	CEQ80Label_MainWnd m_eq80Label;
	CEQ80Slider_MainWnd m_eq80Slider;
	CEQ100Label_MainWnd m_eq100Label;
	CEQ100Slider_MainWnd m_eq100Slider;
	CEQ125Label_MainWnd m_eq125Label;
	CEQ125Slider_MainWnd m_eq125Slider;
	CEQ160Label_MainWnd m_eq160Label;
	CEQ160Slider_MainWnd m_eq160Slider;
	CEQ200Label_MainWnd m_eq200Label;
	CEQ200Slider_MainWnd m_eq200Slider;
	CEQ250Label_MainWnd m_eq250Label;
	CEQ250Slider_MainWnd m_eq250Slider;
	CEQ315Label_MainWnd m_eq315Label;
	CEQ315Slider_MainWnd m_eq315Slider;
	CEQ400Label_MainWnd m_eq400Label;
	CEQ400Slider_MainWnd m_eq400Slider;
	CEQ500Label_MainWnd m_eq500Label;
	CEQ500Slider_MainWnd m_eq500Slider;
	CEQ630Label_MainWnd m_eq630Label;
	CEQ630Slider_MainWnd m_eq630Slider;
	CEQ800Label_MainWnd m_eq800Label;
	CEQ800Slider_MainWnd m_eq800Slider;
	CEQ1KLabel_MainWnd m_eq1kLabel;
	CEQ1KSlider_MainWnd m_eq1kSlider;
	CEQ1_25KLabel_MainWnd m_eq1_25kLabel;
	CEQ1_25KSlider_MainWnd m_eq1_25kSlider;
	CEQ1_6KLabel_MainWnd m_eq1_6kLabel;
	CEQ1_6KSlider_MainWnd m_eq1_6kSlider;
	CEQ2KLabel_MainWnd m_eq2kLabel;
	CEQ2KSlider_MainWnd m_eq2kSlider;
	CEQ2_5KLabel_MainWnd m_eq2_5kLabel;
	CEQ2_5KSlider_MainWnd m_eq2_5kSlider;
	CEQ3_15KLabel_MainWnd m_eq3_15kLabel;
	CEQ3_15KSlider_MainWnd m_eq3_15kSlider;
	CEQ4KLabel_MainWnd m_eq4kLabel;
	CEQ4KSlider_MainWnd m_eq4kSlider;
	CEQ5KLabel_MainWnd m_eq5kLabel;
	CEQ5KSlider_MainWnd m_eq5kSlider;
	CEQ6_3KLabel_MainWnd m_eq6_3kLabel;
	CEQ6_3KSlider_MainWnd m_eq6_3kSlider;
	CEQ8KLabel_MainWnd m_eq8kLabel;
	CEQ8KSlider_MainWnd m_eq8kSlider;
	CEQ10KLabel_MainWnd m_eq10kLabel;
	CEQ10KSlider_MainWnd m_eq10kSlider;
	CEQ12_5KLabel_MainWnd m_eq12_5kLabel;
	CEQ12_5KSlider_MainWnd m_eq12_5kSlider;
	CEQ16KLabel_MainWnd m_eq16kLabel;
	CEQ16KSlider_MainWnd m_eq16kSlider;
	CEQ20KLabel_MainWnd m_eq20kLabel;
	CEQ20KSlider_MainWnd m_eq20kSlider;
	CDivider5_MainWnd m_divider5;
	CTab_MainWnd m_tab;
	std::vector<CPlayListView_MainWnd*> m_arrayList;
	CLimitSettingWnd_MainWnd limitSettingWnd;
	CKeySettingWnd_MainWnd keySettingWnd;
	COutKeySettingWnd_MainWnd outKeySettingWnd;
	CTimerPlayWnd_MainWnd timerPlayWnd;
	CPlayPositionWnd playPositionWnd;
	COpenURLWnd m_openURLWnd;
	CPlayRangeWnd playRangeWnd;
	CLAMECommandLineWnd m_lameCommandLineWnd;
	CReverbCustomizeWnd m_reverbCustomizeWnd;
	C3DReverbCustomizeWnd m_3dReverbCustomizeWnd;
	CDelayCustomizeWnd m_delayCustomizeWnd;
	CChorusCustomizeWnd m_chorusCustomizeWnd;
	CCompressorCustomizeWnd m_compressorCustomizeWnd;
	CFlangerCustomizeWnd m_flangerCustomizeWnd;
	CGargleCustomizeWnd m_gargleCustomizeWnd;
	CDistortionCustomizeWnd m_distortionCustomizeWnd;
	CPresetNameInputWnd presetNameInputWnd;
	CTwitterAuthorizeWnd m_twitterAuthorizeWnd;
	CTweetWnd m_tweetWnd;
	CABLoopPosWnd m_abLoopPosWnd;
	CIncSpeedWnd_MainWnd incSpeedWnd;
	CIncFreqWnd_MainWnd incFreqWnd;
	CDecSpeedWnd_MainWnd decSpeedWnd;
	CDecFreqWnd_MainWnd decFreqWnd;
	CCountLoopWnd_MainWnd countLoopWnd;
	CVideoScreenWnd_MainWnd videoScreenWnd;
	CMetronomeWnd_MainWnd metronomeWnd;
	CLyricsManager lyricsManager;
	CPitchAnalyser m_pitchAnalyser;

	CSound m_sound;
	CSound m_soundEffect; // 効果音

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

	CMenu_MainWnd & GetMenu() { return m_menu; }
	const CDivider_MainWnd & GetDivider1() const { return m_divider1; }
	CToolBar_MainWnd & GetToolBar() { return m_toolBar; }
	const CTimeLabel_MainWnd & GetTimeLabel() const { return m_timeLabel; }
	const CVideoScreen_MainWnd & GetVideoScreen() const {
		return m_videoScreen;
	}
	const CTimeSlider_MainWnd & GetTimeSlider() const { return m_timeSlider; }
	const CDivider2_MainWnd & GetDivider2() const { return m_divider2; }
	CExplorerBar & GetExplorerBar() { return m_explorerBar; }
	CExplorer & GetExplorer() { return m_explorer; }
	CSpeedLabel_MainWnd & GetSpeedLabel() { return m_speedLabel; }
	CSpeedSlider_MainWnd & GetSpeedSlider() { return m_speedSlider; }
	CFreqLabel_MainWnd & GetFreqLabel() { return m_freqLabel; }
	CFreqSlider_MainWnd & GetFreqSlider() {
		return m_freqSlider;
	}
	CPitchLabel_MainWnd & GetPitchLabel() { return m_pitchLabel; }
	CPitchSlider_MainWnd & GetPitchSlider() { return m_pitchSlider; }
	const CDivider3_MainWnd & GetDivider3() const { return m_divider3; }
	CVolumeLabel_MainWnd & GetVolumeLabel() { return m_volumeLabel; }
	CVolumeSlider_MainWnd & GetVolumeSlider() { return m_volumeSlider; }
	CPanLabel_MainWnd & GetPanLabel() { return m_panLabel; }
	CPanSlider_MainWnd & GetPanSlider() { return m_panSlider; }
	const CDivider4_MainWnd & GetDivider4() const { return m_divider4; }
	CEQ20Label_MainWnd & GetEQ20Label() { return m_eq20Label; }
	CEQ20Slider_MainWnd & GetEQ20Slider() { return m_eq20Slider; }
	CEQ25Label_MainWnd & GetEQ25Label() { return m_eq25Label; }
	CEQ25Slider_MainWnd & GetEQ25Slider() { return m_eq25Slider; }
	CEQ31_5Label_MainWnd & GetEQ31_5Label() { return m_eq31_5Label; }
	CEQ31_5Slider_MainWnd & GetEQ31_5Slider() { return m_eq31_5Slider; }
	CEQ40Label_MainWnd & GetEQ40Label() { return m_eq40Label; }
	CEQ40Slider_MainWnd & GetEQ40Slider() { return m_eq40Slider; }
	CEQ50Label_MainWnd & GetEQ50Label() { return m_eq50Label; }
	CEQ50Slider_MainWnd & GetEQ50Slider() { return m_eq50Slider; }
	CEQ63Label_MainWnd & GetEQ63Label() { return m_eq63Label; }
	CEQ63Slider_MainWnd & GetEQ63Slider() { return m_eq63Slider; }
	CEQ80Label_MainWnd & GetEQ80Label() { return m_eq80Label; }
	CEQ80Slider_MainWnd & GetEQ80Slider() { return m_eq80Slider; }
	CEQ100Label_MainWnd & GetEQ100Label() { return m_eq100Label; }
	CEQ100Slider_MainWnd & GetEQ100Slider() { return m_eq100Slider; }
	CEQ125Label_MainWnd & GetEQ125Label() { return m_eq125Label; }
	CEQ125Slider_MainWnd & GetEQ125Slider() { return m_eq125Slider; }
	CEQ160Label_MainWnd & GetEQ160Label() { return m_eq160Label; }
	CEQ160Slider_MainWnd & GetEQ160Slider() { return m_eq160Slider; }
	CEQ200Label_MainWnd & GetEQ200Label() { return m_eq200Label; }
	CEQ200Slider_MainWnd & GetEQ200Slider() { return m_eq200Slider; }
	CEQ250Label_MainWnd & GetEQ250Label() { return m_eq250Label; }
	CEQ250Slider_MainWnd & GetEQ250Slider() { return m_eq250Slider; }
	CEQ315Label_MainWnd & GetEQ315Label() { return m_eq315Label; }
	CEQ315Slider_MainWnd & GetEQ315Slider() { return m_eq315Slider; }
	CEQ400Label_MainWnd & GetEQ400Label() { return m_eq400Label; }
	CEQ400Slider_MainWnd & GetEQ400Slider() { return m_eq400Slider; }
	CEQ500Label_MainWnd & GetEQ500Label() { return m_eq500Label; }
	CEQ500Slider_MainWnd & GetEQ500Slider() { return m_eq500Slider; }
	CEQ630Label_MainWnd & GetEQ630Label() { return m_eq630Label; }
	CEQ630Slider_MainWnd & GetEQ630Slider() { return m_eq630Slider; }
	CEQ800Label_MainWnd & GetEQ800Label() { return m_eq800Label; }
	CEQ800Slider_MainWnd & GetEQ800Slider() { return m_eq800Slider; }
	CEQ1KLabel_MainWnd & GetEQ1KLabel() { return m_eq1kLabel; }
	CEQ1KSlider_MainWnd & GetEQ1KSlider() { return m_eq1kSlider; }
	CEQ1_25KLabel_MainWnd & GetEQ1_25KLabel() { return m_eq1_25kLabel; }
	CEQ1_25KSlider_MainWnd & GetEQ1_25KSlider() { return m_eq1_25kSlider; }
	CEQ1_6KLabel_MainWnd & GetEQ1_6KLabel() { return m_eq1_6kLabel; }
	CEQ1_6KSlider_MainWnd & GetEQ1_6KSlider() { return m_eq1_6kSlider; }
	CEQ2KLabel_MainWnd & GetEQ2KLabel() { return m_eq2kLabel; }
	CEQ2KSlider_MainWnd & GetEQ2KSlider() { return m_eq2kSlider; }
	CEQ2_5KLabel_MainWnd & GetEQ2_5KLabel() { return m_eq2_5kLabel; }
	CEQ2_5KSlider_MainWnd & GetEQ2_5KSlider() { return m_eq2_5kSlider; }
	CEQ3_15KLabel_MainWnd & GetEQ3_15KLabel() { return m_eq3_15kLabel; }
	CEQ3_15KSlider_MainWnd & GetEQ3_15KSlider() { return m_eq3_15kSlider; }
	CEQ4KLabel_MainWnd & GetEQ4KLabel() { return m_eq4kLabel; }
	CEQ4KSlider_MainWnd & GetEQ4KSlider() { return m_eq4kSlider; }
	CEQ5KLabel_MainWnd & GetEQ5KLabel() { return m_eq5kLabel; }
	CEQ5KSlider_MainWnd & GetEQ5KSlider() { return m_eq5kSlider; }
	CEQ6_3KLabel_MainWnd & GetEQ6_3KLabel() { return m_eq6_3kLabel; }
	CEQ6_3KSlider_MainWnd & GetEQ6_3KSlider() { return m_eq6_3kSlider; }
	CEQ8KLabel_MainWnd & GetEQ8KLabel() { return m_eq8kLabel; }
	CEQ8KSlider_MainWnd & GetEQ8KSlider() { return m_eq8kSlider; }
	CEQ10KLabel_MainWnd & GetEQ10KLabel() { return m_eq10kLabel; }
	CEQ10KSlider_MainWnd & GetEQ10KSlider() { return m_eq10kSlider; }
	CEQ12_5KLabel_MainWnd & GetEQ12_5KLabel() { return m_eq12_5kLabel; }
	CEQ12_5KSlider_MainWnd & GetEQ12_5KSlider() { return m_eq12_5kSlider; }
	CEQ16KLabel_MainWnd & GetEQ16KLabel() { return m_eq16kLabel; }
	CEQ16KSlider_MainWnd & GetEQ16KSlider() { return m_eq16kSlider; }
	CEQ20KLabel_MainWnd & GetEQ20KLabel() { return m_eq20kLabel; }
	CEQ20KSlider_MainWnd & GetEQ20KSlider() { return m_eq20kSlider; }
	const CDivider5_MainWnd & GetDivider5() const { return m_divider5; }
	CTab_MainWnd & GetTab() { return m_tab; }
	CPlayListView_MainWnd & GetPlayList() {
		int nSelect = m_tab.GetCurrentFocus();
		return *m_arrayList[nSelect];
	}
	CPlayListView_MainWnd & GetCurPlayList() {
		return *m_arrayList[nCurPlayTab];
	}
	CPlayListView_MainWnd & GetPlayList(int n) {
		return *m_arrayList[n];
	}
	std::vector<CPlayListView_MainWnd*> GetArrayList() {
		return m_arrayList;
	}
	CSound & GetSound() { return m_sound; }
	CPlayPositionWnd & GetPlayPositionWnd() { return playPositionWnd; }
	COpenURLWnd & GetOpenURLWnd() { return m_openURLWnd; }
	CPlayRangeWnd & GetPlayRangeWnd() { return playRangeWnd; }
	CLAMECommandLineWnd & GetLAMECommandLineWnd() {
		return m_lameCommandLineWnd;
	}
	CReverbCustomizeWnd & GetReverbCustomizeWnd() {
		return m_reverbCustomizeWnd;
	}
	C3DReverbCustomizeWnd & Get3DReverbCustomizeWnd() {
		return m_3dReverbCustomizeWnd;
	}
	CDelayCustomizeWnd & GetDelayCustomizeWnd() {
		return m_delayCustomizeWnd;
	}
	CChorusCustomizeWnd & GetChorusCustomizeWnd() {
		return m_chorusCustomizeWnd;
	}
	CCompressorCustomizeWnd & GetCompressorCustomizeWnd() {
		return m_compressorCustomizeWnd;
	}
	CFlangerCustomizeWnd & GetFlangerCustomizeWnd() {
		return m_flangerCustomizeWnd;
	}
	CGargleCustomizeWnd & GetGargleCustomizeWnd() {
		return m_gargleCustomizeWnd;
	}
	CPresetNameInputWnd & GetPresetNameInputWnd() {
		return presetNameInputWnd;
	}
	CTwitterAuthorizeWnd & GetTwitterAuthorizeWnd() {
		return m_twitterAuthorizeWnd;
	}
	CTweetWnd & GetTweetWnd() {
		return m_tweetWnd;
	}
	CABLoopPosWnd & GetABLoopPosWnd() {
		return m_abLoopPosWnd;
	}
	int GetTimeSliderHeight() {
		return m_menu.IsItemChecked(ID_TIMESLIDER) ? controlOffset * 2
			+ m_timeSlider.GetHeight() : 0;
	}
	CVideoScreenWnd_MainWnd & GetVideoScreenWnd() { return videoScreenWnd; }
	CLyricsManager & GetLyricsManager() { return lyricsManager; }
	CPitchAnalyser & GetPitchAnalyser() { return m_pitchAnalyser; }

	int GetControlBarHeight() {
		if(m_menu.IsItemChecked(ID_SPEED) || m_menu.IsItemChecked(ID_FREQ)
			|| m_menu.IsItemChecked(ID_PITCH)) {
			int nHeight = controlOffset;
			nHeight += m_divider2.GetHeight();
			if(m_menu.IsItemChecked(ID_SPEED)) {
				nHeight += controlOffset;
				nHeight += m_speedLabel.GetHeight() > m_speedSlider.GetHeight() ?
						   m_speedLabel.GetHeight() : m_speedSlider.GetHeight();
			}
			if(m_menu.IsItemChecked(ID_FREQ)) {
				nHeight += controlOffset;
				nHeight += m_freqLabel.GetHeight() >
						   m_freqSlider.GetHeight() ?
						   m_freqLabel.GetHeight() :
						   m_freqSlider.GetHeight();
			}
			if(m_menu.IsItemChecked(ID_PITCH)) {
				nHeight += controlOffset;
				nHeight += m_pitchLabel.GetHeight() > m_pitchSlider.GetHeight() ?
						   m_pitchLabel.GetHeight() : m_pitchSlider.GetHeight();
			}
			return nHeight;
		}
		else return 0;
	}
	int GetControlBar2Height() {
		if(m_menu.IsItemChecked(ID_VOLUME) || m_menu.IsItemChecked(ID_PAN)) {
			int nHeight = controlOffset;
			nHeight += m_divider3.GetHeight();
			if(m_menu.IsItemChecked(ID_VOLUME)) {
				nHeight += controlOffset;
				nHeight += m_volumeLabel.GetHeight() > m_volumeSlider.GetHeight() ?
						   m_volumeLabel.GetHeight() : m_volumeSlider.GetHeight();
			}
			if(m_menu.IsItemChecked(ID_PAN)) {
			nHeight += controlOffset;
				nHeight += m_panLabel.GetHeight() > m_panSlider.GetHeight() ?
						   m_panLabel.GetHeight() : m_panSlider.GetHeight();
			}
			return nHeight;
		}
		else return 0;
	}
	int GetEQHeight() {
		if(m_menu.IsItemChecked(ID_EQ)) {
			int nHeight = controlOffset;
			nHeight += m_divider4.GetHeight();
			nHeight += controlOffset * 2;
			if(m_menu.IsItemChecked(ID_EQ20))
				nHeight += m_eq20Label.GetHeight() > m_eq20Slider.GetHeight() ?
						   m_eq20Label.GetHeight() : m_eq20Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ25))
				nHeight += m_eq25Label.GetHeight() > m_eq25Slider.GetHeight() ?
						   m_eq25Label.GetHeight() : m_eq25Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ31_5))
				nHeight += m_eq31_5Label.GetHeight() > m_eq31_5Slider.GetHeight() ?
						   m_eq31_5Label.GetHeight() : m_eq31_5Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ40))
				nHeight += m_eq40Label.GetHeight() > m_eq40Slider.GetHeight() ?
						   m_eq40Label.GetHeight() : m_eq40Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ50))
				nHeight += m_eq50Label.GetHeight() > m_eq50Slider.GetHeight() ?
						   m_eq50Label.GetHeight() : m_eq50Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ63))
				nHeight += m_eq63Label.GetHeight() > m_eq63Slider.GetHeight() ?
						   m_eq63Label.GetHeight() : m_eq63Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ80))
				nHeight += m_eq80Label.GetHeight() > m_eq80Slider.GetHeight() ?
						   m_eq80Label.GetHeight() : m_eq80Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ100))
				nHeight += m_eq100Label.GetHeight() > m_eq100Slider.GetHeight() ?
						   m_eq100Label.GetHeight() : m_eq100Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ125))
				nHeight += m_eq125Label.GetHeight() > m_eq125Slider.GetHeight() ?
						   m_eq125Label.GetHeight() : m_eq125Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ160))
				nHeight += m_eq160Label.GetHeight() > m_eq160Slider.GetHeight() ?
						   m_eq160Label.GetHeight() : m_eq160Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ200))
				nHeight += m_eq200Label.GetHeight() > m_eq200Slider.GetHeight() ?
						   m_eq200Label.GetHeight() : m_eq200Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ250))
				nHeight += m_eq250Label.GetHeight() > m_eq250Slider.GetHeight() ?
						   m_eq250Label.GetHeight() : m_eq250Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ315))
				nHeight += m_eq315Label.GetHeight() > m_eq315Slider.GetHeight() ?
						   m_eq315Label.GetHeight() : m_eq315Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ400))
				nHeight += m_eq400Label.GetHeight() > m_eq400Slider.GetHeight() ?
						   m_eq400Label.GetHeight() : m_eq400Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ500))
				nHeight += m_eq500Label.GetHeight() > m_eq500Slider.GetHeight() ?
						   m_eq500Label.GetHeight() : m_eq500Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ630))
				nHeight += m_eq630Label.GetHeight() > m_eq630Slider.GetHeight() ?
						   m_eq630Label.GetHeight() : m_eq630Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ800))
				nHeight += m_eq800Label.GetHeight() > m_eq800Slider.GetHeight() ?
						   m_eq800Label.GetHeight() : m_eq800Slider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ1K))
				nHeight += m_eq1kLabel.GetHeight() > m_eq1kSlider.GetHeight() ?
						   m_eq1kLabel.GetHeight() : m_eq1kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ1_25K))
				nHeight += m_eq1_25kLabel.GetHeight() > m_eq1_25kSlider.GetHeight() ?
						   m_eq1_25kLabel.GetHeight() : m_eq1_25kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ1_6K))
				nHeight += m_eq1_6kLabel.GetHeight() > m_eq1_6kSlider.GetHeight() ?
						   m_eq1_6kLabel.GetHeight() : m_eq1_6kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ2K))
				nHeight += m_eq2kLabel.GetHeight() > m_eq2kSlider.GetHeight() ?
						   m_eq2kLabel.GetHeight() : m_eq2kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ2_5K))
				nHeight += m_eq2_5kLabel.GetHeight() > m_eq2_5kSlider.GetHeight() ?
						   m_eq2_5kLabel.GetHeight() : m_eq2_5kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ3_15K))
				nHeight += m_eq3_15kLabel.GetHeight() > m_eq3_15kSlider.GetHeight() ?
						   m_eq3_15kLabel.GetHeight() : m_eq3_15kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ4K))
				nHeight += m_eq4kLabel.GetHeight() > m_eq4kSlider.GetHeight() ?
						   m_eq4kLabel.GetHeight() : m_eq4kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ5K))
				nHeight += m_eq5kLabel.GetHeight() > m_eq5kSlider.GetHeight() ?
						   m_eq5kLabel.GetHeight() : m_eq5kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ6_3K))
				nHeight += m_eq6_3kLabel.GetHeight() > m_eq6_3kSlider.GetHeight() ?
						   m_eq6_3kLabel.GetHeight() : m_eq6_3kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ8K))
				nHeight += m_eq8kLabel.GetHeight() > m_eq8kSlider.GetHeight() ?
						   m_eq8kLabel.GetHeight() : m_eq8kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ10K))
				nHeight += m_eq10kLabel.GetHeight() > m_eq10kSlider.GetHeight() ?
						   m_eq10kLabel.GetHeight() : m_eq10kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ12_5K))
				nHeight += m_eq12_5kLabel.GetHeight() > m_eq12_5kSlider.GetHeight() ?
						   m_eq12_5kLabel.GetHeight() : m_eq12_5kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ16K))
				nHeight += m_eq16kLabel.GetHeight() > m_eq16kSlider.GetHeight() ?
						   m_eq16kLabel.GetHeight() : m_eq16kSlider.GetHeight();
			if(m_menu.IsItemChecked(ID_EQ20K))
				nHeight += m_eq20kLabel.GetHeight() > m_eq20kSlider.GetHeight() ?
						   m_eq20kLabel.GetHeight() : m_eq20kSlider.GetHeight();
			return nHeight;
		}
		else return 0;
	}

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