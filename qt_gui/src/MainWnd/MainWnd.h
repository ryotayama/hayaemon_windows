//----------------------------------------------------------------------------
// MainWnd.h : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH

class CApp;
class CPlayListView_MainWnd;
class QSound;
class QTimer;
class QUrl;
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>
#include <QList>
#include <QMainWindow>
#include "../Common/Define.h"
#include "EQLabel_MainWnd.h"
#include "EQSlider_MainWnd.h"
#include "FreqLabel_MainWnd.h"
#include "FreqSlider_MainWnd.h"
#include "Menu_MainWnd.h"
#include "PanLabel_MainWnd.h"
#include "PanSlider_MainWnd.h"
#include "PitchLabel_MainWnd.h"
#include "PitchSlider_MainWnd.h"
#include "Sound.h"
#include "SpeedLabel_MainWnd.h"
#include "SpeedSlider_MainWnd.h"
#include "TimeLabel_MainWnd.h"
#include "TimeSlider_MainWnd.h"
#include "ToolBar_MainWnd.h"
#include "VolumeLabel_MainWnd.h"
#include "VolumeSlider_MainWnd.h"
#include "ui_MainWnd.h"
//----------------------------------------------------------------------------
// メインウィンドウの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMainWnd : public QMainWindow, public Ui::MainWnd
{
	Q_OBJECT

public: // 関数

	CMainWnd(CApp & app): m_rApp(app), m_menu(app, *this), m_toolBar(*this),
		m_timeLabel(*this), m_timeSlider(*this),
		m_speedLabel(*this), m_speedSlider(*this), m_freqLabel(*this),
		m_freqSlider(*this), m_pitchLabel(*this), m_pitchSlider(*this),
		m_volumeLabel(*this), m_volumeSlider(*this), m_panLabel(*this),
		m_panSlider(*this), m_eq20Label(*this), m_eq20Slider(*this),
		m_eq25Label(*this), m_eq25Slider(*this),
		m_eq31_5Label(*this), m_eq31_5Slider(*this),
		m_eq40Label(*this), m_eq40Slider(*this),
		m_eq50Label(*this), m_eq50Slider(*this),
		m_eq63Label(*this), m_eq63Slider(*this),
		m_eq80Label(*this), m_eq80Slider(*this),
		m_eq100Label(*this), m_eq100Slider(*this),
		m_eq125Label(*this), m_eq125Slider(*this),
		m_eq160Label(*this), m_eq160Slider(*this),
		m_eq200Label(*this), m_eq200Slider(*this),
		m_eq250Label(*this), m_eq250Slider(*this),
		m_eq315Label(*this), m_eq315Slider(*this),
		m_eq400Label(*this), m_eq400Slider(*this),
		m_eq500Label(*this), m_eq500Slider(*this),
		m_eq630Label(*this), m_eq630Slider(*this),
		m_eq800Label(*this), m_eq800Slider(*this),
		m_eq1kLabel(*this), m_eq1kSlider(*this),
		m_eq1_25kLabel(*this), m_eq1_25kSlider(*this),
		m_eq1_6kLabel(*this), m_eq1_6kSlider(*this),
		m_eq2kLabel(*this), m_eq2kSlider(*this),
		m_eq2_5kLabel(*this), m_eq2_5kSlider(*this),
		m_eq3_15kLabel(*this), m_eq3_15kSlider(*this),
		m_eq4kLabel(*this), m_eq4kSlider(*this),
		m_eq5kLabel(*this), m_eq5kSlider(*this),
		m_eq6_3kLabel(*this), m_eq6_3kSlider(*this),
		m_eq8kLabel(*this), m_eq8kSlider(*this),
		m_eq10kLabel(*this), m_eq10kSlider(*this),
		m_eq12_5kLabel(*this), m_eq12_5kSlider(*this),
		m_eq16kLabel(*this), m_eq16kSlider(*this),
		m_eq20kLabel(*this), m_eq20kSlider(*this),
		m_sound(app, *this), m_soundEffect(app, *this, FALSE),
		isInitFileRead(FALSE), bTimerPlay(FALSE), bTimerPlayNextDay(FALSE),
		bTimerStop(FALSE), bTimerStopNextDay(FALSE), bReverb(FALSE),
		b3DReverb(FALSE), bDelay(FALSE), bChorus(FALSE), bCompressor(FALSE),
		bFlanger(FALSE), bGargle(FALSE), bDistortion(FALSE), bMarkerPlay(FALSE),
		bCountLoop(FALSE), bInstantLoop(FALSE), bSetPositionAuto(FALSE),
		m_bFinish(FALSE), nTimerPlayHour(0), nTimerPlayMinute(0), nTimerStopHour(0),
		nTimerStopMinute(0), nIncSpeed(0), nIncFreq(0), nDecSpeed(0), nDecFreq(0),
		nFreqVelo(0), nFreqAccel(0), nLoopCount(0), nCurrentLoopCount(0),
		nIncSpeedMode(0), nIncFreqMode(0), nDecSpeedMode(0), nDecFreqMode(0),
		nCurPlayTab(0), dwLastTime(0), lpSound(nullptr), m_nBpm(120),
		m_nInterval(0), dwFadeoutStartTime(0), m_nLastDecimalDigit_pitch(0),
		m_nLastDecimalDigit_freq(0), m_nLastDecimalDigit_speed(0),
		m_dStartSeconds(0.0), m_dEndSeconds(0.0),
		m_strLAMECommandLine(_T("--preset cbr 192")), m_updateThreadRunning(false),
		m_timeThreadRunning(false), m_bRetryUpdate(FALSE), m_bForwarding(false),
		m_bRewinding(false) { }
	virtual ~CMainWnd();

	virtual void AddDropFiles(const QList<QUrl> & urls, BOOL bClear);
	virtual void AddFile(const QString & lpszFilePath);
	virtual void AddMarker();
	virtual void AddPreset();
	virtual void AddPreset(tstring strPreset);
	virtual void ChangeCurPlayTab();
	virtual BOOL CheckLoop();
	virtual void CopyTime();
	virtual BOOL Create() { return OnCreate(); }
	virtual void CreateNewList(BOOL bChangeFocus = TRUE);
	virtual BOOL CreateControls();
	virtual void DeleteArrayList(int nList);
	virtual void DeleteMarker();
	virtual void DeletePreset();
	virtual void DownFreq(double freq);
	virtual void DownPitch(double pitch);
	virtual void DownSpeed(double speed);
	virtual void Forward();
	virtual void ForwardSeconds(int seconds);
	virtual void Head();
	virtual void LoadSettings(const PCTSTR & pFilePath);
	virtual BOOL OpenFile(const QString & lpszFilePath, int nCount = 1);
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
	virtual void ResetFreq();
	virtual void ResetPitch();
	virtual void ResetSize();
	virtual void ResetSpeed();
	virtual void ResetVolume();
	virtual void Rewind();
	virtual void ReturnSeconds(int seconds);
	virtual void SavePreset(PCTSTR pFilePath);
	virtual void SaveSettings(const PCTSTR & pFilePath);
	virtual void SaveSettings(const QString & filePath);
	virtual void SetABLoopA(QWORD pos);
	virtual void SetABLoopA();
	virtual void SetABLoopA_Sec(double dTime);
	virtual void SetABLoopB();
	virtual void SetABLoopB_Sec(double dTime);
	virtual void SetABLoopASetting();
	virtual void SetABLoopBSetting();
	virtual void SetAllLoop(bool bAllLoop = true);
	virtual void SetAllEffects();
	virtual void SetContinue(bool bContinue);
	virtual void SetTimeSliderVisible(bool bTimeSliderVisible);
	virtual void SetExplorerVisible(bool bExplorerVisible);
	virtual void SetSpeedVisible(bool bSpeedVisible);
	virtual void SetFreqVisible(bool bFreqVisible);
	virtual void SetPitchVisible(bool bPitchVisible);
	virtual void SetVolumeVisible(bool bVolumeVisible);
	virtual void SetPanVisible(bool bPanVisible);
	virtual void SetCountLoop();
	virtual void SetCountLoop(int nCount);
	virtual void SetCountLoop(BOOL nCountLoop, int nCount);
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
	virtual void SetEQVisible(bool bEQVisible);
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
	virtual void SetPlayListVisible(bool bListVisible);
	virtual void SetPreset(int n);
	virtual void SetPreviousNextMenuState();
	virtual void SetPrevMarker();
	virtual void SetRandom(bool bRandom = true);
	virtual void SetReverse();
	virtual void SetReverse(BOOL bReverse);
	virtual void SetRecord();
	virtual void SetRecord(BOOL bRecord);
	virtual void SetRecordNoise(BOOL bRecordNoise);
	virtual void SetSeconds(double fSeconds);
	virtual void SetSingleLoop();
	virtual void SetSpeed(double dSpeed);
	virtual void SetTabVisible(bool bTabVisible);
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
	virtual void ShowOpenURLWnd(BOOL bAdd = FALSE);
	virtual void ShowOpenFileDialog(BOOL bClear);
	virtual void ShowOpenFolderDialog(BOOL bClear);
	virtual void ShowSaveFileDialog();
	virtual void ShowSaveAllFileDialog();
	virtual void ShowReverbCustomizeWnd();
	virtual void ShowTime(BOOL bReset = TRUE);
	virtual void StartRewind();
	virtual void StartForward();
	virtual void StartUpdateInfo();
	virtual void StopRewind();
	virtual void StopForward();
	virtual void Stop(BOOL bForce = TRUE);
	virtual void UpFreq(double freq);
	virtual void UpPitch(double pitch);
	virtual void UpSpeed(double speed);
	virtual void WriteInitFile();

	// メッセージ
	virtual void OnClose();
	virtual LRESULT OnCreate();
	virtual void OnTimer(UINT id);

	static void UpdateThreadProc(void * pParam);
	static void UpdateTimeThreadProc(void * pParam);

protected: // メンバ変数

	CApp & m_rApp;
	CMenu_MainWnd m_menu;
	CToolBar_MainWnd m_toolBar;
	CTimeLabel_MainWnd m_timeLabel;
	CTimeSlider_MainWnd m_timeSlider;
	CSpeedLabel_MainWnd m_speedLabel;
	CSpeedSlider_MainWnd m_speedSlider;
	CFreqLabel_MainWnd m_freqLabel;
	CFreqSlider_MainWnd m_freqSlider;
	CPitchLabel_MainWnd m_pitchLabel;
	CPitchSlider_MainWnd m_pitchSlider;
	CVolumeLabel_MainWnd m_volumeLabel;
	CVolumeSlider_MainWnd m_volumeSlider;
	CPanLabel_MainWnd m_panLabel;
	CPanSlider_MainWnd m_panSlider;
	CEQLabel_MainWnd m_eq20Label;
	CEQSlider_MainWnd m_eq20Slider;
	CEQLabel_MainWnd m_eq25Label;
	CEQSlider_MainWnd m_eq25Slider;
	CEQLabel_MainWnd m_eq31_5Label;
	CEQSlider_MainWnd m_eq31_5Slider;
	CEQLabel_MainWnd m_eq40Label;
	CEQSlider_MainWnd m_eq40Slider;
	CEQLabel_MainWnd m_eq50Label;
	CEQSlider_MainWnd m_eq50Slider;
	CEQLabel_MainWnd m_eq63Label;
	CEQSlider_MainWnd m_eq63Slider;
	CEQLabel_MainWnd m_eq80Label;
	CEQSlider_MainWnd m_eq80Slider;
	CEQLabel_MainWnd m_eq100Label;
	CEQSlider_MainWnd m_eq100Slider;
	CEQLabel_MainWnd m_eq125Label;
	CEQSlider_MainWnd m_eq125Slider;
	CEQLabel_MainWnd m_eq160Label;
	CEQSlider_MainWnd m_eq160Slider;
	CEQLabel_MainWnd m_eq200Label;
	CEQSlider_MainWnd m_eq200Slider;
	CEQLabel_MainWnd m_eq250Label;
	CEQSlider_MainWnd m_eq250Slider;
	CEQLabel_MainWnd m_eq315Label;
	CEQSlider_MainWnd m_eq315Slider;
	CEQLabel_MainWnd m_eq400Label;
	CEQSlider_MainWnd m_eq400Slider;
	CEQLabel_MainWnd m_eq500Label;
	CEQSlider_MainWnd m_eq500Slider;
	CEQLabel_MainWnd m_eq630Label;
	CEQSlider_MainWnd m_eq630Slider;
	CEQLabel_MainWnd m_eq800Label;
	CEQSlider_MainWnd m_eq800Slider;
	CEQLabel_MainWnd m_eq1kLabel;
	CEQSlider_MainWnd m_eq1kSlider;
	CEQLabel_MainWnd m_eq1_25kLabel;
	CEQSlider_MainWnd m_eq1_25kSlider;
	CEQLabel_MainWnd m_eq1_6kLabel;
	CEQSlider_MainWnd m_eq1_6kSlider;
	CEQLabel_MainWnd m_eq2kLabel;
	CEQSlider_MainWnd m_eq2kSlider;
	CEQLabel_MainWnd m_eq2_5kLabel;
	CEQSlider_MainWnd m_eq2_5kSlider;
	CEQLabel_MainWnd m_eq3_15kLabel;
	CEQSlider_MainWnd m_eq3_15kSlider;
	CEQLabel_MainWnd m_eq4kLabel;
	CEQSlider_MainWnd m_eq4kSlider;
	CEQLabel_MainWnd m_eq5kLabel;
	CEQSlider_MainWnd m_eq5kSlider;
	CEQLabel_MainWnd m_eq6_3kLabel;
	CEQSlider_MainWnd m_eq6_3kSlider;
	CEQLabel_MainWnd m_eq8kLabel;
	CEQSlider_MainWnd m_eq8kSlider;
	CEQLabel_MainWnd m_eq10kLabel;
	CEQSlider_MainWnd m_eq10kSlider;
	CEQLabel_MainWnd m_eq12_5kLabel;
	CEQSlider_MainWnd m_eq12_5kSlider;
	CEQLabel_MainWnd m_eq16kLabel;
	CEQSlider_MainWnd m_eq16kSlider;
	CEQLabel_MainWnd m_eq20kLabel;
	CEQSlider_MainWnd m_eq20kSlider;
	std::vector<CPlayListView_MainWnd*> m_arrayList;

	CSound m_sound;
	CSound m_soundEffect; // 効果音

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
	BOOL m_bFinish; // 再生が完了したかどうか
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
	QSound * lpSound; // 音（メトロノーム用）
	int m_nBpm; // テンポ（メトロノーム用）
	int m_nInterval; // 間隔（メトロノーム用）
	DWORD dwFadeoutStartTime; // フェードアウト開始時間
	int m_nLastDecimalDigit_pitch; // 前回の小数点桁数（音程）
	int m_nLastDecimalDigit_freq; // 前回の小数点桁数（再生周波数）
	int m_nLastDecimalDigit_speed; // 前回の小数点桁数（再生速度）
	double m_dStartSeconds; // 再生範囲の開始位置
	double m_dEndSeconds; // 再生範囲の停止位置
	tstring m_strLAMECommandLine;
	std::thread m_updateThread;
	bool m_updateThreadRunning;
	BOOL m_bRetryUpdate;
	std::unique_ptr<std::thread> m_timeThread;
	bool m_timeThreadRunning;
	bool m_bForwarding;
	bool m_bRewinding;

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
	CExplorerBar & GetExplorerBar() { return *m_explorerBar; }
	CExplorer & GetExplorer() { return *m_explorer; }
	CSpeedLabel_MainWnd & GetSpeedLabel() { return m_speedLabel; }
	CSpeedSlider_MainWnd & GetSpeedSlider() { return m_speedSlider; }
	CFreqLabel_MainWnd & GetFreqLabel() { return m_freqLabel; }
	CFreqSlider_MainWnd & GetFreqSlider() {
		return m_freqSlider;
	}
	CPitchLabel_MainWnd & GetPitchLabel() { return m_pitchLabel; }
	CPitchSlider_MainWnd & GetPitchSlider() { return m_pitchSlider; }
	CVolumeLabel_MainWnd & GetVolumeLabel() { return m_volumeLabel; }
	CVolumeSlider_MainWnd & GetVolumeSlider() { return m_volumeSlider; }
	CPanLabel_MainWnd & GetPanLabel() { return m_panLabel; }
	CPanSlider_MainWnd & GetPanSlider() { return m_panSlider; }
	CTab_MainWnd & GetTab() { return *m_tab; }
	CPlayListView_MainWnd & GetPlayList() {
		int nSelect = m_tab->GetCurrentFocus();
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

	int GetBpm() const { return m_nBpm; }

	BOOL IsMarkerPlay() const { return bMarkerPlay; }
	BOOL IsSetPositionAuto() const { return bSetPositionAuto; }
	BOOL IsRetryUpdate() {
		BOOL bRetryUpdate = m_bRetryUpdate;
		m_bRetryUpdate = FALSE;
		return bRetryUpdate;
	}
	void SetFinish(BOOL bFinish) { m_bFinish = bFinish; }

	tstring GetStrSaveFormat() { return strSaveFormat; }
	tstring GetStrLAMECommandLine() { return m_strLAMECommandLine; }

public:

	// Qtのラッパー
	virtual void KillTimer(UINT_PTR nIDEvent);

private:

	struct EQItem {
		QString title;
		CEQLabel_MainWnd & label;
		CEQSlider_MainWnd & slider;
		UINT menuId;
		void (CMainWnd::*setEQ)(LONG);
	};

	void SetContextMenus();
	void ShowContextMenu(QWidget * widget, QMenu * menu,
											 QAction * visibilityAction, const QString &title,
											 void (CMainWnd::*callback)(bool visible),
											 const QPoint & pos);
	void closeEvent(QCloseEvent *event) final;
	void dragEnterEvent(QDragEnterEvent * e) final;
	void dropEvent(QDropEvent * e) final;
	// Qtのラッパー
	virtual void SetCaption(const QString & lpWindowName);
	virtual void SetTimer(UINT_PTR nIDEvent, UINT nElapse);

	std::unordered_map<UINT_PTR, QTimer *> m_timers;
	std::vector<EQItem> m_eqItems;
};
//----------------------------------------------------------------------------

#endif
