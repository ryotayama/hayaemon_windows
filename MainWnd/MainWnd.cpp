//----------------------------------------------------------------------------
// MainWnd.cpp : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include <vector>
#include <shlwapi.h>
#include <shlobj.h>
#include <math.h>
#include <process.h>
#include "../resource.h"
#include "../App.h"
#include "../Common/basswasapi.h"
#include "../Common/Utils.h"
#include "../Common/oauth.h"
#include "../Common/socket.h"
#include "../CountLoopWnd/CountLoopWnd_MainWnd.h"
#include "../DecFreqWnd/DecFreqWnd_MainWnd.h"
#include "../DecSpeedWnd/DecSpeedWnd_MainWnd.h"
#include "../IncFreqWnd/IncFreqWnd_MainWnd.h"
#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
#include "../KeySettingWnd/KeySettingWnd_MainWnd.h"
#include "../LimitSettingWnd/LimitSettingWnd_MainWnd.h"
#include "../MetronomeWnd/MetronomeWnd_MainWnd.h"
#include "../OutKeySettingWnd/OutKeySettingWnd_MainWnd.h"
#include "../TimerPlayWnd/TimerPlayWnd_MainWnd.h"
#include "../VideoScreenWnd/VideoScreenWnd_MainWnd.h"
#include "3DReverbCustomizeWnd.h"
#include "ABLoopPosWnd.h"
#include "AllSaveWnd_MainWnd.h"
#include "ChorusCustomizeWnd.h"
#include "CompressorCustomizeWnd.h"
#include "DelayCustomizeWnd.h"
#include "DistortionCustomizeWnd.h"
#include "Divider2_MainWnd.h"
#include "Divider3_MainWnd.h"
#include "Divider4_MainWnd.h"
#include "Divider5_MainWnd.h"
#include "Divider_MainWnd.h"
#include "EQ100Label_MainWnd.h"
#include "EQ100Slider_MainWnd.h"
#include "EQ10KLabel_MainWnd.h"
#include "EQ10KSlider_MainWnd.h"
#include "EQ125Label_MainWnd.h"
#include "EQ125Slider_MainWnd.h"
#include "EQ12_5KLabel_MainWnd.h"
#include "EQ12_5KSlider_MainWnd.h"
#include "EQ160Label_MainWnd.h"
#include "EQ160Slider_MainWnd.h"
#include "EQ16KLabel_MainWnd.h"
#include "EQ16KSlider_MainWnd.h"
#include "EQ1KLabel_MainWnd.h"
#include "EQ1KSlider_MainWnd.h"
#include "EQ1_25KLabel_MainWnd.h"
#include "EQ1_25KSlider_MainWnd.h"
#include "EQ1_6KLabel_MainWnd.h"
#include "EQ1_6KSlider_MainWnd.h"
#include "EQ200Label_MainWnd.h"
#include "EQ200Slider_MainWnd.h"
#include "EQ20KLabel_MainWnd.h"
#include "EQ20KSlider_MainWnd.h"
#include "EQ20Label_MainWnd.h"
#include "EQ20Slider_MainWnd.h"
#include "EQ250Label_MainWnd.h"
#include "EQ250Slider_MainWnd.h"
#include "EQ25Label_MainWnd.h"
#include "EQ25Slider_MainWnd.h"
#include "EQ2KLabel_MainWnd.h"
#include "EQ2KSlider_MainWnd.h"
#include "EQ2_5KLabel_MainWnd.h"
#include "EQ2_5KSlider_MainWnd.h"
#include "EQ315Label_MainWnd.h"
#include "EQ315Slider_MainWnd.h"
#include "EQ31_5Label_MainWnd.h"
#include "EQ31_5Slider_MainWnd.h"
#include "EQ3_15KLabel_MainWnd.h"
#include "EQ3_15KSlider_MainWnd.h"
#include "EQ400Label_MainWnd.h"
#include "EQ400Slider_MainWnd.h"
#include "EQ40Label_MainWnd.h"
#include "EQ40Slider_MainWnd.h"
#include "EQ4KLabel_MainWnd.h"
#include "EQ4KSlider_MainWnd.h"
#include "EQ500Label_MainWnd.h"
#include "EQ500Slider_MainWnd.h"
#include "EQ50Label_MainWnd.h"
#include "EQ50Slider_MainWnd.h"
#include "EQ5KLabel_MainWnd.h"
#include "EQ5KSlider_MainWnd.h"
#include "EQ630Label_MainWnd.h"
#include "EQ630Slider_MainWnd.h"
#include "EQ63Label_MainWnd.h"
#include "EQ63Slider_MainWnd.h"
#include "EQ6_3KLabel_MainWnd.h"
#include "EQ6_3KSlider_MainWnd.h"
#include "EQ800Label_MainWnd.h"
#include "EQ800Slider_MainWnd.h"
#include "EQ80Label_MainWnd.h"
#include "EQ80Slider_MainWnd.h"
#include "EQ8KLabel_MainWnd.h"
#include "EQ8KSlider_MainWnd.h"
#include "Explorer.h"
#include "ExplorerBar.h"
#include "FlangerCustomizeWnd.h"
#include "FreqLabel_MainWnd.h"
#include "FreqSlider_MainWnd.h"
#include "GargleCustomizeWnd.h"
#include "LAMECommandLineWnd.h"
#include "LyricsManager.h"
#include "M3UFile.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "OpenURLWnd.h"
#include "PanLabel_MainWnd.h"
#include "PanSlider_MainWnd.h"
#include "PitchAnalyser.h"
#include "PitchLabel_MainWnd.h"
#include "PitchSlider_MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "PlayPositionWnd.h"
#include "PlayRangeWnd.h"
#include "PresetNameInputWnd.h"
#include "ReverbCustomizeWnd.h"
#include "RMenu_Taskbar.h"
#include "Sound.h"
#include "SpeedLabel_MainWnd.h"
#include "SpeedSlider_MainWnd.h"
#include "Tab_MainWnd.h"
#include "TimeLabel_MainWnd.h"
#include "TimeSlider_MainWnd.h"
#include "ToolBar_MainWnd.h"
#include "TweetWnd.h"
#include "TwitterAuthorizeWnd.h"
#include "VideoScreen_MainWnd.h"
#include "VolumeLabel_MainWnd.h"
#include "VolumeSlider_MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CMainWnd::CMainWnd(CApp & app)
	: m_rApp(app), m_menu(new CMenu_MainWnd(app, *this)),
		m_divider1(new CDivider_MainWnd(app, *this)),
		m_toolBar(new CToolBar_MainWnd(app, *this)),
		m_timeLabel(new CTimeLabel_MainWnd(app, *this)),
		m_videoScreen(new CVideoScreen_MainWnd(app, *this)),
		m_timeSlider(new CTimeSlider_MainWnd(app, *this)),
		m_divider2(new CDivider2_MainWnd(app, *this)),
		m_explorerBar(new CExplorerBar(app, *this)),
		m_explorer(new CExplorer(app, *this)),
		m_speedLabel(new CSpeedLabel_MainWnd(app, *this)),
		m_speedSlider(new CSpeedSlider_MainWnd(app, *this)),
		m_freqLabel(new CFreqLabel_MainWnd(app, *this)),
		m_freqSlider(new CFreqSlider_MainWnd(app, *this)),
		m_pitchLabel(new CPitchLabel_MainWnd(app, *this)),
		m_pitchSlider(new CPitchSlider_MainWnd(app, *this)),
		m_divider3(new CDivider3_MainWnd(app, *this)),
		m_volumeLabel(new CVolumeLabel_MainWnd(app, *this)),
		m_volumeSlider(new CVolumeSlider_MainWnd(app, *this)),
		m_panLabel(new CPanLabel_MainWnd(app, *this)),
		m_panSlider(new CPanSlider_MainWnd(app, *this)),
		m_divider4(new CDivider4_MainWnd(app, *this)),
		m_eq20Label(new CEQ20Label_MainWnd(m_rApp, *this)),
		m_eq20Slider(new CEQ20Slider_MainWnd(m_rApp, *this)),
		m_eq25Label(new CEQ25Label_MainWnd(m_rApp, *this)),
		m_eq25Slider(new CEQ25Slider_MainWnd(m_rApp, *this)),
		m_eq31_5Label(new CEQ31_5Label_MainWnd(m_rApp, *this)),
		m_eq31_5Slider(new CEQ31_5Slider_MainWnd(m_rApp, *this)),
		m_eq40Label(new CEQ40Label_MainWnd(m_rApp, *this)),
		m_eq40Slider(new CEQ40Slider_MainWnd(m_rApp, *this)),
		m_eq50Label(new CEQ50Label_MainWnd(m_rApp, *this)),
		m_eq50Slider(new CEQ50Slider_MainWnd(m_rApp, *this)),
		m_eq63Label(new CEQ63Label_MainWnd(m_rApp, *this)),
		m_eq63Slider(new CEQ63Slider_MainWnd(m_rApp, *this)),
		m_eq80Label(new CEQ80Label_MainWnd(m_rApp, *this)),
		m_eq80Slider(new CEQ80Slider_MainWnd(m_rApp, *this)),
		m_eq100Label(new CEQ100Label_MainWnd(m_rApp, *this)),
		m_eq100Slider(new CEQ100Slider_MainWnd(m_rApp, *this)),
		m_eq125Label(new CEQ125Label_MainWnd(m_rApp, *this)),
		m_eq125Slider(new CEQ125Slider_MainWnd(m_rApp, *this)),
		m_eq160Label(new CEQ160Label_MainWnd(m_rApp, *this)),
		m_eq160Slider(new CEQ160Slider_MainWnd(m_rApp, *this)),
		m_eq200Label(new CEQ200Label_MainWnd(m_rApp, *this)),
		m_eq200Slider(new CEQ200Slider_MainWnd(m_rApp, *this)),
		m_eq250Label(new CEQ250Label_MainWnd(m_rApp, *this)),
		m_eq250Slider(new CEQ250Slider_MainWnd(m_rApp, *this)),
		m_eq315Label(new CEQ315Label_MainWnd(m_rApp, *this)),
		m_eq315Slider(new CEQ315Slider_MainWnd(m_rApp, *this)),
		m_eq400Label(new CEQ400Label_MainWnd(m_rApp, *this)),
		m_eq400Slider(new CEQ400Slider_MainWnd(m_rApp, *this)),
		m_eq500Label(new CEQ500Label_MainWnd(m_rApp, *this)),
		m_eq500Slider(new CEQ500Slider_MainWnd(m_rApp, *this)),
		m_eq630Label(new CEQ630Label_MainWnd(m_rApp, *this)),
		m_eq630Slider(new CEQ630Slider_MainWnd(m_rApp, *this)),
		m_eq800Label(new CEQ800Label_MainWnd(m_rApp, *this)),
		m_eq800Slider(new CEQ800Slider_MainWnd(m_rApp, *this)),
		m_eq1kLabel(new CEQ1KLabel_MainWnd(m_rApp, *this)),
		m_eq1kSlider(new CEQ1KSlider_MainWnd(m_rApp, *this)),
		m_eq1_25kLabel(new CEQ1_25KLabel_MainWnd(m_rApp, *this)),
		m_eq1_25kSlider(new CEQ1_25KSlider_MainWnd(m_rApp, *this)),
		m_eq1_6kLabel(new CEQ1_6KLabel_MainWnd(m_rApp, *this)),
		m_eq1_6kSlider(new CEQ1_6KSlider_MainWnd(m_rApp, *this)),
		m_eq2kLabel(new CEQ2KLabel_MainWnd(m_rApp, *this)),
		m_eq2kSlider(new CEQ2KSlider_MainWnd(m_rApp, *this)),
		m_eq2_5kLabel(new CEQ2_5KLabel_MainWnd(m_rApp, *this)),
		m_eq2_5kSlider(new CEQ2_5KSlider_MainWnd(m_rApp, *this)),
		m_eq3_15kLabel(new CEQ3_15KLabel_MainWnd(m_rApp, *this)),
		m_eq3_15kSlider(new CEQ3_15KSlider_MainWnd(m_rApp, *this)),
		m_eq4kLabel(new CEQ4KLabel_MainWnd(m_rApp, *this)),
		m_eq4kSlider(new CEQ4KSlider_MainWnd(m_rApp, *this)),
		m_eq5kLabel(new CEQ5KLabel_MainWnd(m_rApp, *this)),
		m_eq5kSlider(new CEQ5KSlider_MainWnd(m_rApp, *this)),
		m_eq6_3kLabel(new CEQ6_3KLabel_MainWnd(m_rApp, *this)),
		m_eq6_3kSlider(new CEQ6_3KSlider_MainWnd(m_rApp, *this)),
		m_eq8kLabel(new CEQ8KLabel_MainWnd(m_rApp, *this)),
		m_eq8kSlider(new CEQ8KSlider_MainWnd(m_rApp, *this)),
		m_eq10kLabel(new CEQ10KLabel_MainWnd(m_rApp, *this)),
		m_eq10kSlider(new CEQ10KSlider_MainWnd(m_rApp, *this)),
		m_eq12_5kLabel(new CEQ12_5KLabel_MainWnd(m_rApp, *this)),
		m_eq12_5kSlider(new CEQ12_5KSlider_MainWnd(m_rApp, *this)),
		m_eq16kLabel(new CEQ16KLabel_MainWnd(m_rApp, *this)),
		m_eq16kSlider(new CEQ16KSlider_MainWnd(m_rApp, *this)),
		m_eq20kLabel(new CEQ20KLabel_MainWnd(m_rApp, *this)),
		m_eq20kSlider(new CEQ20KSlider_MainWnd(m_rApp, *this)),
		m_divider5(new CDivider5_MainWnd(app, *this)),
		m_tab(new CTab_MainWnd(app, *this)),
		limitSettingWnd(new CLimitSettingWnd_MainWnd(m_rApp, *this)),
		keySettingWnd(new CKeySettingWnd_MainWnd(m_rApp, *this)),
		outKeySettingWnd(new COutKeySettingWnd_MainWnd(m_rApp, *this)),
		timerPlayWnd(new CTimerPlayWnd_MainWnd(m_rApp, *this)),
		playPositionWnd(new CPlayPositionWnd(m_rApp, *this)),
		m_openURLWnd(new COpenURLWnd(m_rApp, *this)),
		playRangeWnd(new CPlayRangeWnd(m_rApp, *this)),
		m_lameCommandLineWnd(new CLAMECommandLineWnd(m_rApp, *this)),
		m_reverbCustomizeWnd(new CReverbCustomizeWnd(m_rApp, *this)),
		m_3dReverbCustomizeWnd(new C3DReverbCustomizeWnd(m_rApp, *this)),
		m_delayCustomizeWnd(new CDelayCustomizeWnd(m_rApp, *this)),
		m_chorusCustomizeWnd(new CChorusCustomizeWnd(m_rApp, *this)),
		m_compressorCustomizeWnd(new CCompressorCustomizeWnd(m_rApp, *this)),
		m_flangerCustomizeWnd(new CFlangerCustomizeWnd(m_rApp, *this)),
		m_gargleCustomizeWnd(new CGargleCustomizeWnd(m_rApp, *this)),
		m_distortionCustomizeWnd(new CDistortionCustomizeWnd(m_rApp, *this)),
		presetNameInputWnd(new CPresetNameInputWnd(m_rApp, *this)),
		m_twitterAuthorizeWnd(new CTwitterAuthorizeWnd(m_rApp, *this)),
		m_tweetWnd(new CTweetWnd(m_rApp, *this)),
		m_abLoopPosWnd(new CABLoopPosWnd(m_rApp, *this)),
		incSpeedWnd(new CIncSpeedWnd_MainWnd(m_rApp, *this)),
		incFreqWnd(new CIncFreqWnd_MainWnd(m_rApp, *this)),
		decSpeedWnd(new CDecSpeedWnd_MainWnd(m_rApp, *this)),
		decFreqWnd(new CDecFreqWnd_MainWnd(m_rApp, *this)),
		countLoopWnd(new CCountLoopWnd_MainWnd(m_rApp, *this)),
		videoScreenWnd(new CVideoScreenWnd_MainWnd(m_rApp, *this)),
		metronomeWnd(new CMetronomeWnd_MainWnd(m_rApp, *this)),
		lyricsManager(new CLyricsManager(m_rApp, *this)),
		m_pitchAnalyser(new CPitchAnalyser(m_rApp, *this)),
		m_sound(new CSound(app, *this)),
		m_soundEffect(new CSound(app, *this, FALSE)),
		controlOffset(5), isInitFileRead(FALSE), bTimerPlay(FALSE),
		bTimerPlayNextDay(FALSE), bTimerStop(FALSE), bTimerStopNextDay(FALSE),
		bReverb(FALSE), b3DReverb(FALSE), bDelay(FALSE), bChorus(FALSE),
		bCompressor(FALSE), bFlanger(FALSE), bGargle(FALSE), bDistortion(FALSE),
		bMarkerPlay(FALSE), bCountLoop(FALSE), bInstantLoop(FALSE),
		bSetPositionAuto(FALSE), m_bVideo(FALSE), m_bFullScreen(FALSE),
		m_bFinish(FALSE), m_bExplorerResizing(FALSE),
		m_bVideoScreenResizing(FALSE), nMinWidth(0), nTimerPlayHour(0),
		nTimerPlayMinute(0), nTimerStopHour(0), nTimerStopMinute(0),
		nIncSpeed(0.0), nIncFreq(0.0), nDecSpeed(0.0), nDecFreq(0.0),
		nFreqVelo(0.0), nFreqAccel(0.0), nLoopCount(0), nCurrentLoopCount(0),
		nCurPlayTab(0), dwLastTime(0), m_nBpm(120), dwFadeoutStartTime(0),
		m_dStartSeconds(0.0), m_dEndSeconds(0.0),
		m_strLAMECommandLine(_T("--preset cbr 192")), m_hUpdateThread(0),
		m_bRetryUpdate(FALSE), m_hLyricsThread(0), m_bLyricsThreadAlive(FALSE),
		m_hPitchAnalyserThread(0), m_bPitchAnalyserThreadAlive(FALSE)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CMainWnd::~CMainWnd() = default;
//----------------------------------------------------------------------------
// ドロップされたファイルの追加
//----------------------------------------------------------------------------
void CMainWnd::AddDropFiles(HDROP hdrop, BOOL bClear)
{
	int nSelect = m_tab->GetCurrentFocus();
	int count = DragQueryFile(hdrop, 0xffffffff, NULL, MAX_PATH);
	int i = 0;
	TCHAR szPathName[MAX_PATH];
	DragQueryFile(hdrop, i, szPathName, MAX_PATH);

	TCHAR chExt[_MAX_EXT];
	_tsplitpath_s(szPathName, NULL, 0, NULL, 0, NULL, 0, chExt, _MAX_EXT);

	if(_tcsicmp(chExt, _T(".ini")) == 0) {
		LoadSettings(szPathName);
		return;
	}
	if(bClear) {
		ChangeCurPlayTab();
		m_arrayList[nSelect]->DeleteAllItems();
	}
	for(; i < count; i++) {
		TCHAR szPathName[MAX_PATH];
		DragQueryFile(hdrop, i, szPathName, MAX_PATH);

		m_arrayList[nSelect]->AddFile(szPathName);
	}

	if(m_arrayList[nCurPlayTab]->GetItemCount() <= 0) {
		m_sound->StreamFree();
		Stop();
	}

	if(bClear || m_sound->GetCurFileNum() <= 0) {
		m_sound->SetCurFileNum(0);
		PlayNext(bClear, TRUE);
	}

	SetPreviousNextMenuState();

	StartUpdateInfo();
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CMainWnd::AddFile(LPCTSTR lpszFilePath)
{
	int nSelect = m_tab->GetCurrentFocus();
	m_arrayList[nSelect]->AddFile(lpszFilePath);
}
//----------------------------------------------------------------------------
// マーカーの追加
//----------------------------------------------------------------------------
void CMainWnd::AddMarker()
{
	QWORD time = m_sound->ChannelGetPosition();
	SetABLoopA(time);

	if(!bMarkerPlay) SetMarkerPlay();

	if(bInstantLoop) SetPrevMarker();
}
//----------------------------------------------------------------------------
// プリセットの追加
//----------------------------------------------------------------------------
void CMainWnd::AddPreset()
{
	presetNameInputWnd->Create();
}
//----------------------------------------------------------------------------
// プリセットの追加
//----------------------------------------------------------------------------
void CMainWnd::AddPreset(tstring str)
{
	SavePreset(str.c_str());
}
//----------------------------------------------------------------------------
// 現在再生中のタブを変更
//----------------------------------------------------------------------------
void CMainWnd::ChangeCurPlayTab()
{
	for(int i = 0; i < (int)m_arrayList.size(); i++)
		m_arrayList[i]->SetPlaying(-1);
	nCurPlayTab = m_tab->GetCurrentFocus();
}
//----------------------------------------------------------------------------
// 回数ループのチェック
//----------------------------------------------------------------------------
BOOL CMainWnd::CheckLoop()
{
	if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
		if(m_menu->IsItemChecked(ID_INCSPEED) && nIncSpeedMode == 2)
			UpSpeed(nIncSpeed);
		if(m_menu->IsItemChecked(ID_INCFREQ) && nIncFreqMode == 2)
			UpFreq(nIncFreq);
		if(m_menu->IsItemChecked(ID_DECSPEED) && nDecSpeedMode == 2)
			DownSpeed(nDecSpeed);
		if(m_menu->IsItemChecked(ID_DECFREQ) && nDecFreqMode == 2)
			DownFreq(nDecFreq);
	}

	if(bCountLoop) {
		nCurrentLoopCount++;
		if(nCurrentLoopCount >= nLoopCount) {
			nCurrentLoopCount = 0;
			QWORD qwTime = m_sound->GetLoopPosA();
			std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
			QWORD length = m_sound->ChannelGetLength();
			int max = (int)arrayMarker.size();
			if(max > 0 && qwTime == 0)
				qwTime = arrayMarker[0];
			else {
				if(qwTime == arrayMarker[max - 1]) {
					if(m_menu->IsItemChecked(ID_PLAYRANGE))
						SetSeconds(m_dStartSeconds);
					else SetTime(0);
					return FALSE;
				}
				else {
					for(int i = 0; i < max - 1; i++) {
						if(qwTime == arrayMarker[i]) {
							qwTime = arrayMarker[i + 1];
							break;
						}
					}
				}
			}

			BOOL bDone = FALSE; // 範囲を設定したかどうか
			if(max > 0) {
				if(0 <= qwTime && qwTime < arrayMarker[0]) {
						bDone = TRUE;
						SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
						SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
									(LPARAM)(arrayMarker[0] / 100000));
						m_sound->SetLoopPosA(0);
						m_sound->SetLoopPosB(arrayMarker[0]);
				}
			}
			else {
				bDone = TRUE;
				SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
				SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
							(LPARAM)(length / 100000));
				m_sound->SetLoopPosA(0);
				m_sound->SetLoopPosB(length);
			}

			if(!bDone) {
				for(int i = 0; i < max; i++) {
					if(i + 1 < max) {
						if(arrayMarker[i] <= qwTime
							&& qwTime < arrayMarker[i + 1]) {
							bDone = TRUE;
							SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
								(LPARAM)(arrayMarker[i] / 100000));
							SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
								(LPARAM)(arrayMarker[i + 1] / 100000));
							m_sound->SetLoopPosA(arrayMarker[i]);
							m_sound->SetLoopPosB(arrayMarker[i + 1]);
							break;
						}
					}
				}
			}

			if(!bDone) {
				if(arrayMarker[max - 1] <= qwTime && qwTime <= length) {
					bDone = TRUE;
					SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
						(LPARAM)(arrayMarker[max - 1] / 100000));
					SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
						(LPARAM)(length / 100000));
					m_sound->SetLoopPosA(arrayMarker[max - 1]);
					m_sound->SetLoopPosB(length);
				}
			}
			return FALSE;
		}
		else return TRUE;
	}
	else return TRUE;
}
//----------------------------------------------------------------------------
// 現在の再生位置をクリップボードにコピー
//----------------------------------------------------------------------------
void CMainWnd::CopyTime()
{
	double maxTime = m_sound->ChannelGetSecondsLength();

	double time = m_sound->ChannelGetSecondsPosition();

	if(time < 0.0f) time = 0.0f;

	int maxHour = (int)(maxTime / 3600) % 60;

	int hour = (int)(time / 3600) % 60;
	int second = (int)(time / 60) % 60;
	int minute = (int)time % 60;

	TCHAR text[20];
	int nLength = 0;
	if(maxHour > 0) {
		_stprintf_s(text, _T("%02d:%02d:%02d"), hour, second, minute);
		nLength = 8;
	}
	else {
		_stprintf_s(text, _T("%02d:%02d"), second, minute);
		nLength = 5;
	}

	HGLOBAL hGlobal = 0;
	if(!(hGlobal = GlobalAlloc(GHND, (nLength+1) * sizeof(TCHAR)))) return;
	LPTSTR pDstStr = (LPTSTR)GlobalLock(hGlobal);
	LPTSTR pSrcStr = text;
	for(int i = 0; i < nLength; i++)
		*pDstStr++ = *pSrcStr++;
	GlobalUnlock(hGlobal);
	if(!OpenClipboard(m_hWnd)) {
		GlobalFree(hGlobal);
		return;
	}
	EmptyClipboard();
	SetClipboardData(CLIPBOARD_TXT_FMT, hGlobal);
	CloseClipboard();
}
//----------------------------------------------------------------------------
// 新しい再生リストを作成
//----------------------------------------------------------------------------
void CMainWnd::CreateNewList(BOOL bChangeFocus)
{
	int nSelect = !bChangeFocus ? m_tab->GetItemCount() : 
								 m_tab->GetCurrentFocus() + 1;
	m_arrayList.insert(m_arrayList.begin() + nSelect,
		new CPlayListView_MainWnd(m_rApp, *this));
	m_arrayList[nSelect]->Create();
	m_arrayList[nSelect]->ResetPos();
	m_arrayList[nSelect]->ResetSize();
	if(bChangeFocus) {
		for(int i = 0; i < (int)m_arrayList.size(); i++)
			m_arrayList[i]->Show(SW_HIDE);
		m_arrayList[nSelect]->Show(SW_SHOW);
	}
	m_tab->AddNewTab(bChangeFocus);
}
//----------------------------------------------------------------------------
// 各コントロールを作成
//----------------------------------------------------------------------------
BOOL CMainWnd::CreateControls(BOOL bFirst, BOOL bVideoScreenVisible,
	BOOL bTimeSliderVisible, BOOL bExplorerVisible, BOOL bSpeedVisible,
	BOOL bFreqVisible, BOOL bPitchVisible, BOOL bVolumeVisible,
	BOOL bPanVisible, BOOL bEQVisible, BOOL bTabVisible)
{
	TCHAR chPath[255], buf[255];
	lstrcpy(chPath, (m_rApp.GetFilePath() + _T("Setting.ini")).c_str());

	if(bFirst) {
		// 区切り線その１の作成
		if(!m_divider1->Create()) {
#if JP
			m_rApp.ShowError(_T("区切り線その１の作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create divider 1."));
#endif // JP
			return FALSE;
		}

		// ツールバーの作成
		if(!m_toolBar->Create()) {
#if JP
			m_rApp.ShowError(_T("ツールバーの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create toolbar."));
#endif // JP
			return FALSE;
		}

		// 再生時間表示用ラベルの作成
		if(!m_timeLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("再生時間表示用ラベルの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create time label."));
#endif // JP
			return FALSE;
		}
	}

	// ビデオ画面の作成
	if(bVideoScreenVisible) {
		if(!m_videoScreen->Create()) {
#if JP
			m_rApp.ShowError(_T("ビデオ画面の作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create video screen."));
#endif // JP
			return FALSE;
		}
	}

	if(bTimeSliderVisible) {
		// 再生時間設定用スライダの作成
		if(!m_timeSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("再生時間設定用スライダの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create time slider."));
#endif // JP
			return FALSE;
		}
	}

	if(bFirst) {
		// 区切り線その２の作成
		if(!m_divider2->Create()) {
#if JP
			m_rApp.ShowError(_T("区切り線その２の作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create divider 2."));
#endif // JP
			return FALSE;
		}
	}

	if(bExplorerVisible) {
		// エクスプローラ用ツールバーの作成
		if(!m_explorerBar->Create()) {
#if JP
			m_rApp.ShowError(_T("エクスプローラ用ツールバーの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create explorer."));
#endif // JP
			return FALSE;
		}

		// エクスプローラの作成
		if(!m_explorer->Create()) {
#if JP
			m_rApp.ShowError(_T("エクスプローラの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create explorer."));
#endif // JP
			return FALSE;
		}

		GetPrivateProfileString(_T("Options"), _T("ExplorerPath"), _T(""), 
			buf, 255, chPath);
		if(_tcsicmp(buf, _T("")) != 0) {
			SetCurrentDirectory(buf);
			m_explorer->ShowFiles();
		}
	}

	if(bSpeedVisible) {
		// 再生速度表示用ラベルの作成
		if(!m_speedLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("再生速度表示用ラベルの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create speed label."));
#endif // JP
			return FALSE;
		}

		// 再生速度設定用スライダの作成
		if(!m_speedSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("再生速度設定用スライダの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create speed slider."));
#endif // JP
			return FALSE;
		}

		GetPrivateProfileString(_T("Options"), _T("MinimumSpeed"), _T("10.0"),
			buf, 255, chPath);
		double _dMinSpeed = (double)_tstof(buf);
		GetPrivateProfileString(_T("Options"), _T("MaximumSpeed"), _T("1200.0"),
			buf, 255, chPath);
		double _dMaxSpeed = (double)_tstof(buf);
		GetPrivateProfileString(_T("Options"), _T("SpeedDecimalDigit"), _T("1"),
			buf, 255, chPath);
		int _nSpeedDecimalDigit = (int)_ttoi(buf);
		if(_nSpeedDecimalDigit == 0) m_menu->OnSetSpeedDecimal0MenuSelected();
		else if(_nSpeedDecimalDigit == 1)
			m_menu->OnSetSpeedDecimal1MenuSelected();
		else if(_nSpeedDecimalDigit == 2)
			m_menu->OnSetSpeedDecimal2MenuSelected();
		if(_dMinSpeed < 1.0) _dMinSpeed = 1.0;
		if(_dMaxSpeed > 5000.0) _dMaxSpeed = 5000.0;

		m_speedSlider->SetLimit(_dMinSpeed, _dMaxSpeed);
		m_speedLabel->SetLimit(_dMinSpeed, _dMaxSpeed);

		if(GetPrivateProfileInt(_T("Options"), _T("RecoverSpeed"), 0, chPath)) {
			m_menu->SwitchItemChecked(ID_RECOVERSPEED);
			int speed = GetPrivateProfileInt(_T("Options"), _T("Speed"), 1000,
				chPath);
			m_speedLabel->SetSpeed((double)(speed
				/ pow(10.0, m_speedLabel->GetDecimalDigit())));
			m_speedSlider->SetThumbPos((LONG)speed, TRUE);
			SetSpeed((double)(speed
				/ pow(10.0, m_speedLabel->GetDecimalDigit())));
		}
	}

	if(bFreqVisible) {
		// 再生周波数表示用ラベルの作成
		if(!m_freqLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("再生周波数表示用ラベルの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create frequency label."));
#endif // JP
			return FALSE;
		}

		// 再生周波数設定用スライダの作成
		if(!m_freqSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("再生周波数設定用スライダの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create frequency slider."));
#endif // JP
			return FALSE;
		}

		GetPrivateProfileString(_T("Options"), _T("MinimumFrequency"),
			_T("10.0"), 
			buf, 255, chPath);
		double _dMinFreq = (double)_tstof(buf);
		GetPrivateProfileString(_T("Options"), _T("MaximumFrequency"), 
			_T("1200.0"), buf, 255, chPath);
		double _dMaxFreq = (double)_tstof(buf);
		GetPrivateProfileString(_T("Options"), _T("FrequencyDecimalDigit"),
			_T("1"), buf, 255, chPath);
		int _nFreqDecimalDigit = (int)_ttoi(buf);
		if(_nFreqDecimalDigit == 0) m_menu->OnSetFreqDecimal0MenuSelected();
		else if(_nFreqDecimalDigit == 1) m_menu->OnSetFreqDecimal1MenuSelected();
		else if(_nFreqDecimalDigit == 2) m_menu->OnSetFreqDecimal2MenuSelected();
		if(_dMinFreq < 1.0) _dMinFreq = 1.0;
		if(_dMaxFreq > 5000.0) _dMaxFreq = 5000.0;

		m_freqSlider->SetLimit(_dMinFreq, _dMaxFreq);
		m_freqLabel->SetLimit(_dMinFreq, _dMaxFreq);

		if(GetPrivateProfileInt(_T("Options"), _T("RecoverFrequency"), 0,
				chPath)) {
			m_menu->SwitchItemChecked(ID_RECOVERFREQ);
			int freq = GetPrivateProfileInt(_T("Options"), _T("Frequency"),
						1000, chPath);
			m_freqLabel->SetFreq((double)(freq
				/ pow(10.0, m_freqLabel->GetDecimalDigit())));
			m_freqSlider->SetThumbPos((LONG)freq, TRUE);
			SetFreq((double)(freq
				/ pow(10.0, m_freqLabel->GetDecimalDigit())));
		}
	}

	if(bPitchVisible) {
		// 音程表示用ラベルの作成
		if(!m_pitchLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("音程表示用ラベルの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create pitch label."));
#endif // JP
			return FALSE;
		}

		// 音程設定用スライダの作成
		if(!m_pitchSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("音程設定用スライダの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create pitch slider."));
#endif // JP
			return FALSE;
		}

		GetPrivateProfileString(_T("Options"), _T("MinimumPitch"), _T("-24.0"), 
			buf, 255, chPath);
		double _dMinPitch = (double)_tstof(buf);
		GetPrivateProfileString(_T("Options"), _T("MaximumPitch"), _T("24.0"),
			buf, 255, chPath);
		double _dMaxPitch = (double)_tstof(buf);
		GetPrivateProfileString(_T("Options"), _T("PitchDecimalDigit"), _T("1"),
			buf, 255, chPath);
		int _nPitchDecimalDigit = (int)_ttoi(buf);
		if(_nPitchDecimalDigit == 0) m_menu->OnSetPitchDecimal0MenuSelected();
		else if(_nPitchDecimalDigit == 1)
			m_menu->OnSetPitchDecimal1MenuSelected();
		else if(_nPitchDecimalDigit == 2)
			m_menu->OnSetPitchDecimal2MenuSelected();

		if(_dMinPitch < -60.0) _dMinPitch = -60.0;
		if(_dMaxPitch > 60.0) _dMaxPitch = 60.0;

		m_pitchSlider->SetLimit(_dMinPitch, _dMaxPitch);
		m_pitchLabel->SetLimit(_dMinPitch, _dMaxPitch);

		if(GetPrivateProfileInt(_T("Options"), _T("RecoverPitch"), 0, chPath)) {
			m_menu->SwitchItemChecked(ID_RECOVERPITCH);
			int pitch = GetPrivateProfileInt(_T("Options"), _T("Pitch"), 1000,
				chPath);
			m_pitchLabel->SetPitch((double)(pitch
				/ pow(10.0, m_pitchLabel->GetDecimalDigit())));
			m_pitchSlider->SetThumbPos((LONG)pitch, TRUE);
			SetPitch((double)(pitch
				/ pow(10.0, m_pitchLabel->GetDecimalDigit())));
		}
	}

	if(bFirst) {
		// 区切り線その３の作成
		if(!m_divider3->Create()) {
#if JP
			m_rApp.ShowError(_T("区切り線その３の作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create divider 3."));
#endif // JP
			return FALSE;
		}
	}

	if(bVolumeVisible) {
		// 音量表示用ラベルの作成
		if(!m_volumeLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("音量表示用ラベルの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create volume label."));
#endif // JP
			return FALSE;
		}

		// 音量設定用スライダの作成
		if(!m_volumeSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("音量設定用スライダの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create volume slider."));
#endif // JP
			return FALSE;
		}
		if(GetPrivateProfileInt(_T("Options"), _T("RecoverVolume"), 1, chPath))
		{
			m_menu->SwitchItemChecked(ID_RECOVERVOLUME);
			int volume = GetPrivateProfileInt(_T("Options"), _T("Volume"), 1000,
				chPath);
			m_volumeLabel->SetVolume((double)(volume / 10.0));
			m_volumeSlider->SetThumbPos(volume);
			SetVolume((double)(volume / 10.0));
		}
	}

	if(bFirst) {
		// イコライザ ( 12.5KHz ) 表示用ラベルの作成
		if(!m_eq12_5kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 12.5KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(12.5KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 12.5KHz ) 設定用スライダの作成
		if(!m_eq12_5kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 12.5KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(12.5KHz) slider."));
#endif // JP
			return FALSE;
		}
	}

	if(bPanVisible) {
		// パン表示用ラベルの作成
		if(!m_panLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("パン表示用ラベルの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create pan label."));
#endif // JP
			return FALSE;
		}

		// パン設定用スライダの作成
		if(!m_panSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("パン設定用スライダの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create pan slider."));
#endif // JP
			return FALSE;
		}
		if(GetPrivateProfileInt(_T("Options"), _T("RecoverPan"), 0, chPath)) {
			m_menu->SwitchItemChecked(ID_RECOVERPAN);
			int pan = GetPrivateProfileInt(_T("Options"), _T("Pan"), 0,
				chPath);
			m_panLabel->SetPan(pan);
			m_panSlider->SetThumbPos(pan);
			SetPan(pan);
		}
	}

	if(bFirst) {
		// 区切り線その４の作成
		if(!m_divider4->Create()) {
#if JP
			m_rApp.ShowError(_T("区切り線その４の作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create divider 4."));
#endif // JP
			return FALSE;
		}
	}

	if(bEQVisible) {
		// イコライザ ( 20Hz ) 表示用ラベルの作成
		if(!m_eq20Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 20Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(20Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 20Hz ) 設定用スライダの作成
		if(!m_eq20Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 20Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(20Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 25Hz ) 表示用ラベルの作成
		if(!m_eq25Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 25Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(25Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 25Hz ) 設定用スライダの作成
		if(!m_eq25Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 25Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(25Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 31.5Hz ) 表示用ラベルの作成
		if(!m_eq31_5Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 31.5Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(31.5Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 31.5Hz ) 設定用スライダの作成
		if(!m_eq31_5Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 31.5Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(31.5Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 40Hz ) 表示用ラベルの作成
		if(!m_eq40Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 40Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(40Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 40Hz ) 設定用スライダの作成
		if(!m_eq40Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 40Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(40Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 50Hz ) 表示用ラベルの作成
		if(!m_eq50Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 50Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(50Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 50Hz ) 設定用スライダの作成
		if(!m_eq50Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 50Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(50Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 63Hz ) 表示用ラベルの作成
		if(!m_eq63Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 63Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(63Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 63Hz ) 設定用スライダの作成
		if(!m_eq63Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 63Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(63Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 80Hz ) 表示用ラベルの作成
		if(!m_eq80Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 80Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(80Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 80Hz ) 設定用スライダの作成
		if(!m_eq80Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 80Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(80Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 100Hz ) 表示用ラベルの作成
		if(!m_eq100Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 100Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(100Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 100Hz ) 設定用スライダの作成
		if(!m_eq100Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 100Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(100Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 125Hz ) 表示用ラベルの作成
		if(!m_eq125Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 125Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(125Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 125Hz ) 設定用スライダの作成
		if(!m_eq125Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 125Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(125Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 160Hz ) 表示用ラベルの作成
		if(!m_eq160Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 160Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(160Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 160Hz ) 設定用スライダの作成
		if(!m_eq160Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 160Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(160Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 200Hz ) 表示用ラベルの作成
		if(!m_eq200Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 200Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(200Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 200Hz ) 設定用スライダの作成
		if(!m_eq200Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 200Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(200Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 250Hz ) 表示用ラベルの作成
		if(!m_eq250Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 250Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(250Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 250Hz ) 設定用スライダの作成
		if(!m_eq250Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 250Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(250Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 315Hz ) 表示用ラベルの作成
		if(!m_eq315Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 315Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(315Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 315Hz ) 設定用スライダの作成
		if(!m_eq315Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 315Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(315Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 400Hz ) 表示用ラベルの作成
		if(!m_eq400Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 400Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(400Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 400Hz ) 設定用スライダの作成
		if(!m_eq400Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 400Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(400Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 500Hz ) 表示用ラベルの作成
		if(!m_eq500Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 500Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(500Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 500Hz ) 設定用スライダの作成
		if(!m_eq500Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 500Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(500Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 630Hz ) 表示用ラベルの作成
		if(!m_eq630Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 630Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(630Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 630Hz ) 設定用スライダの作成
		if(!m_eq630Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 630Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(630Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 800Hz ) 表示用ラベルの作成
		if(!m_eq800Label->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 800Hz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(800Hz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 800Hz ) 設定用スライダの作成
		if(!m_eq800Slider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 800Hz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(800Hz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 1KHz ) 表示用ラベルの作成
		if(!m_eq1kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 1KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(1KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 1KHz ) 設定用スライダの作成
		if(!m_eq1kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 1KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(1KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 1.25KHz ) 表示用ラベルの作成
		if(!m_eq1_25kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 1.25KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(1.25KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 1.25KHz ) 設定用スライダの作成
		if(!m_eq1_25kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 1.25KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(1.25KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 1.6KHz ) 表示用ラベルの作成
		if(!m_eq1_6kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 1.6KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(1.6KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 1.6KHz ) 設定用スライダの作成
		if(!m_eq1_6kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 1.6KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(1.6KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 2KHz ) 表示用ラベルの作成
		if(!m_eq2kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 2KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(2KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 2KHz ) 設定用スライダの作成
		if(!m_eq2kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 2KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(2KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 2.5KHz ) 表示用ラベルの作成
		if(!m_eq2_5kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 2.5KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(2.5KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 2.5KHz ) 設定用スライダの作成
		if(!m_eq2_5kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 2.5KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(2.5KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 3.15KHz ) 表示用ラベルの作成
		if(!m_eq3_15kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 3.15KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(3.15KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 3.15KHz ) 設定用スライダの作成
		if(!m_eq3_15kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 3.15KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(3.15KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 4KHz ) 表示用ラベルの作成
		if(!m_eq4kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 4KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(4KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 4KHz ) 設定用スライダの作成
		if(!m_eq4kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 4KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(4KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 5KHz ) 表示用ラベルの作成
		if(!m_eq5kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 5KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(5KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 5KHz ) 設定用スライダの作成
		if(!m_eq5kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 5KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(5KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 6.3KHz ) 表示用ラベルの作成
		if(!m_eq6_3kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 6.3KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(6.3KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 6.3KHz ) 設定用スライダの作成
		if(!m_eq6_3kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 6.3KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(6.3KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 8KHz ) 表示用ラベルの作成
		if(!m_eq8kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 8KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(8KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 8KHz ) 設定用スライダの作成
		if(!m_eq8kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 8KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(8KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 10KHz ) 表示用ラベルの作成
		if(!m_eq10kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 10KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(10KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 10KHz ) 設定用スライダの作成
		if(!m_eq10kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 10KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(10KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 16KHz ) 表示用ラベルの作成
		if(!m_eq16kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 16KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(16KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 16KHz ) 設定用スライダの作成
		if(!m_eq16kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 16KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(16KHz) slider."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 20KHz ) 表示用ラベルの作成
		if(!m_eq20kLabel->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 20KHz ) 表示用ラベルの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(20KHz) label."));
#endif // JP
			return FALSE;
		}

		// イコライザ ( 20KHz ) 設定用スライダの作成
		if(!m_eq20kSlider->Create()) {
#if JP
			m_rApp.ShowError(_T("イコライザ ( 20KHz ) 設定用スライダの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create EQ(20KHz) slider."));
#endif // JP
			return FALSE;
		}
		if(GetPrivateProfileInt(_T("Options"), _T("RecoverEQ"), 0, chPath)) {
			m_menu->SwitchItemChecked(ID_RECOVEREQ);
			int eq20 = GetPrivateProfileInt(_T("Options"), _T("EQ20"), 0,
				chPath);
			m_eq20Label->SetEQ20(eq20);
			m_eq20Slider->SetThumbPos(eq20);
			SetEQ20((LONG)eq20);
			int eq25 = GetPrivateProfileInt(_T("Options"), _T("EQ25"), 0,
				chPath);
			m_eq25Label->SetEQ25(eq25);
			m_eq25Slider->SetThumbPos(eq25);
			SetEQ25((LONG)eq25);
			int eq31_5 = GetPrivateProfileInt(_T("Options"), _T("EQ31.5"), 0,
				chPath);
			m_eq31_5Label->SetEQ31_5(eq31_5);
			m_eq31_5Slider->SetThumbPos(eq31_5);
			SetEQ31_5((LONG)eq31_5);
			int eq40 = GetPrivateProfileInt(_T("Options"), _T("EQ40"), 0,
				chPath);
			m_eq40Label->SetEQ40(eq40);
			m_eq40Slider->SetThumbPos(eq40);
			SetEQ40((LONG)eq40);
			int eq50 = GetPrivateProfileInt(_T("Options"), _T("EQ50"), 0,
				chPath);
			m_eq50Label->SetEQ50(eq50);
			m_eq50Slider->SetThumbPos(eq50);
			SetEQ50((LONG)eq50);
			int eq63 = GetPrivateProfileInt(_T("Options"), _T("EQ63"), 0,
				chPath);
			m_eq63Label->SetEQ63(eq63);
			m_eq63Slider->SetThumbPos(eq63);
			SetEQ63((LONG)eq63);
			int eq80 = GetPrivateProfileInt(_T("Options"), _T("EQ80"), 0,
				chPath);
			m_eq80Label->SetEQ80(eq80);
			m_eq80Slider->SetThumbPos(eq80);
			SetEQ80((LONG)eq80);
			int eq100 = GetPrivateProfileInt(_T("Options"), _T("EQ100"), 0,
				chPath);
			m_eq100Label->SetEQ100(eq100);
			m_eq100Slider->SetThumbPos(eq100);
			SetEQ100((LONG)eq100);
			int eq125 = GetPrivateProfileInt(_T("Options"), _T("EQ125"), 0,
				chPath);
			m_eq125Label->SetEQ125(eq125);
			m_eq125Slider->SetThumbPos(eq125);
			SetEQ125((LONG)eq125);
			int eq160 = GetPrivateProfileInt(_T("Options"), _T("EQ160"), 0,
				chPath);
			m_eq160Label->SetEQ160(eq160);
			m_eq160Slider->SetThumbPos(eq160);
			SetEQ160((LONG)eq160);
			int eq200 = GetPrivateProfileInt(_T("Options"), _T("EQ200"), 0,
				chPath);
			m_eq200Label->SetEQ200(eq200);
			m_eq200Slider->SetThumbPos(eq200);
			SetEQ200((LONG)eq200);
			int eq250 = GetPrivateProfileInt(_T("Options"), _T("EQ250"), 0,
				chPath);
			m_eq250Label->SetEQ250(eq250);
			m_eq250Slider->SetThumbPos(eq250);
			SetEQ250((LONG)eq250);
			int eq315 = GetPrivateProfileInt(_T("Options"), _T("EQ315"), 0,
				chPath);
			m_eq315Label->SetEQ315(eq315);
			m_eq315Slider->SetThumbPos(eq315);
			SetEQ315((LONG)eq315);
			int eq400 = GetPrivateProfileInt(_T("Options"), _T("EQ400"), 0,
				chPath);
			m_eq400Label->SetEQ400(eq400);
			m_eq400Slider->SetThumbPos(eq400);
			SetEQ400((LONG)eq400);
			int eq500 = GetPrivateProfileInt(_T("Options"), _T("EQ500"), 0,
				chPath);
			m_eq500Label->SetEQ500(eq500);
			m_eq500Slider->SetThumbPos(eq500);
			SetEQ500((LONG)eq500);
			int eq630 = GetPrivateProfileInt(_T("Options"), _T("EQ630"), 0,
				chPath);
			m_eq630Label->SetEQ630(eq630);
			m_eq630Slider->SetThumbPos(eq630);
			SetEQ630((LONG)eq630);
			int eq800 = GetPrivateProfileInt(_T("Options"), _T("EQ800"), 0,
				chPath);
			m_eq800Label->SetEQ800(eq800);
			m_eq800Slider->SetThumbPos(eq800);
			SetEQ800((LONG)eq800);
			int eq1k = GetPrivateProfileInt(_T("Options"), _T("EQ1K"), 0,
				chPath);
			m_eq1kLabel->SetEQ1K(eq1k);
			m_eq1kSlider->SetThumbPos(eq1k);
			SetEQ1K((LONG)eq1k);
			int eq1_25k = GetPrivateProfileInt(_T("Options"), _T("EQ1.25K"), 0,
				chPath);
			m_eq1_25kLabel->SetEQ1_25K(eq1_25k);
			m_eq1_25kSlider->SetThumbPos(eq1_25k);
			SetEQ1_25K((LONG)eq1_25k);
			int eq1_6k = GetPrivateProfileInt(_T("Options"), _T("EQ1.6K"), 0,
				chPath);
			m_eq1_6kLabel->SetEQ1_6K(eq1_6k);
			m_eq1_6kSlider->SetThumbPos(eq1_6k);
			SetEQ1_6K((LONG)eq1_6k);
			int eq2k = GetPrivateProfileInt(_T("Options"), _T("EQ2K"), 0,
				chPath);
			m_eq2kLabel->SetEQ2K(eq2k);
			m_eq2kSlider->SetThumbPos(eq2k);
			SetEQ2K((LONG)eq2k);
			int eq2_5k = GetPrivateProfileInt(_T("Options"), _T("EQ2.5K"), 0,
				chPath);
			m_eq2_5kLabel->SetEQ2_5K(eq2_5k);
			m_eq2_5kSlider->SetThumbPos(eq2_5k);
			SetEQ2_5K((LONG)eq2_5k);
			int eq3_15k = GetPrivateProfileInt(_T("Options"), _T("EQ3.15K"), 0,
				chPath);
			m_eq3_15kLabel->SetEQ3_15K(eq3_15k);
			m_eq3_15kSlider->SetThumbPos(eq3_15k);
			SetEQ3_15K((LONG)eq3_15k);
			int eq4k = GetPrivateProfileInt(_T("Options"), _T("EQ4K"), 0,
				chPath);
			m_eq4kLabel->SetEQ4K(eq4k);
			m_eq4kSlider->SetThumbPos(eq4k);
			SetEQ4K((LONG)eq4k);
			int eq5k = GetPrivateProfileInt(_T("Options"), _T("EQ5K"), 0,
				chPath);
			m_eq5kLabel->SetEQ5K(eq5k);
			m_eq5kSlider->SetThumbPos(eq5k);
			SetEQ5K((LONG)eq5k);
			int eq6_3k = GetPrivateProfileInt(_T("Options"), _T("EQ6.3K"), 0,
				chPath);
			m_eq6_3kLabel->SetEQ6_3K(eq6_3k);
			m_eq6_3kSlider->SetThumbPos(eq6_3k);
			SetEQ6_3K((LONG)eq6_3k);
			int eq8k = GetPrivateProfileInt(_T("Options"), _T("EQ8K"), 0,
				chPath);
			m_eq8kLabel->SetEQ8K(eq8k);
			m_eq8kSlider->SetThumbPos(eq8k);
			SetEQ8K((LONG)eq8k);
			int eq10k = GetPrivateProfileInt(_T("Options"), _T("EQ10K"), 0,
				chPath);
			m_eq10kLabel->SetEQ10K(eq10k);
			m_eq10kSlider->SetThumbPos(eq10k);
			SetEQ10K((LONG)eq10k);
			int eq12_5k = GetPrivateProfileInt(_T("Options"), _T("EQ12.5K"), 0,
				chPath);
			m_eq12_5kLabel->SetEQ12_5K(eq12_5k);
			m_eq12_5kSlider->SetThumbPos(eq12_5k);
			SetEQ12_5K((LONG)eq12_5k);
			int eq16k = GetPrivateProfileInt(_T("Options"), _T("EQ16K"), 0,
				chPath);
			m_eq16kLabel->SetEQ16K(eq16k);
			m_eq16kSlider->SetThumbPos(eq16k);
			SetEQ16K((LONG)eq16k);
			int eq20k = GetPrivateProfileInt(_T("Options"), _T("EQ20K"), 0,
				chPath);
			m_eq20kLabel->SetEQ20K(eq20k);
			m_eq20kSlider->SetThumbPos(eq20k);
			SetEQ20K((LONG)eq20k);
		}
		m_eq12_5kLabel->ResetPos();
		m_eq12_5kSlider->ResetPos();
	}

	if(bFirst) {
		// 区切り線その５の作成
		if(!m_divider5->Create()) {
#if JP
			m_rApp.ShowError(_T("区切り線その５の作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create divider 5."));
#endif // JP
			return FALSE;
		}
	}

	if(bFirst) {
		// タブの作成
		if(!m_tab->Create()) {
#if JP
			m_rApp.ShowError(_T("タブの作成に失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create tab."));
#endif // JP
			return FALSE;
		}
		m_arrayList.push_back(new CPlayListView_MainWnd(m_rApp, *this));
		// プレイリスト用リストビューの作成
		if(!m_arrayList[0]->Create()) {
#if JP
			m_rApp.ShowError(_T("プレイリスト用リストビューの作成に")
							 _T("失敗しました。"));
#else // JP
			m_rApp.ShowError(_T("failed to create playlist."));
#endif // JP
			return FALSE;
		}
	}

	if(bExplorerVisible)
		SetWindowPos(*m_explorer, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	return TRUE;
}
//----------------------------------------------------------------------------
// 再生リストの削除
//----------------------------------------------------------------------------
void CMainWnd::DeleteArrayList(int nList)
{
	int nArrayCount = (int)m_arrayList.size();
	if(nArrayCount == 1) {
		m_arrayList[0]->DeleteAllItems();
		m_sound->StreamFree();
		Stop();
	}
	else {
		if(nCurPlayTab == nList) {
			m_sound->StreamFree();
			Stop();
		}
		for(int i = 0; i < nArrayCount; i++) m_arrayList[i]->Show(SW_HIDE);
		CPlayListView_MainWnd* pList = m_arrayList[nList];
		m_arrayList.erase(m_arrayList.begin() + nList);
		delete pList;
		int nShow = nList > 0 ? nList - 1 : nList;
		m_arrayList[nShow]->Show(SW_SHOW);
		if(nCurPlayTab == nList) {
			nCurPlayTab = nShow;
			m_sound->SetCurFileNum(0);
			OpenNext();
		}
	}
}
//----------------------------------------------------------------------------
// マーカーの削除
//----------------------------------------------------------------------------
void CMainWnd::DeleteMarker()
{
	std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
	QWORD length = m_sound->ChannelGetLength();
	int max = (int)arrayMarker.size();
	for(int i = 0; i < max; i++) {
		if(arrayMarker[i] == m_sound->GetLoopPosB()) {
			m_sound->EraseMarker(i);
			SetTime(m_sound->ChannelGetPosition());
			break;
		}
	}
}
//----------------------------------------------------------------------------
// プリセットの削除
//----------------------------------------------------------------------------
void CMainWnd::DeletePreset()
{
	tstring initFilePath = m_rApp.GetFilePath() + _T("Setting.ini");

	int nCount = GetMenuItemCount(m_menu->GetPresetMenu());
	BOOL bHit = FALSE;
	TCHAR chSec[255], chNextSec[255], buf[255];
	for(int i = 1; i < nCount; i++)
	{
		if(m_menu->IsItemChecked(ID_PRESET+i)) bHit = TRUE;
		if(bHit) {
			_stprintf_s(chSec, _T("Preset%d"), i);
			_stprintf_s(chNextSec, _T("Preset%d"), i+1);
			GetPrivateProfileString(chNextSec, _T("Name"), _T(""), buf, 255,
				initFilePath.c_str());
			DeleteMenu(m_menu->GetPresetMenu(), ID_PRESET+i, MF_BYCOMMAND);
			if(_tcsicmp(buf, _T("")) == 0) {
				WritePrivateProfileString(chSec, NULL, NULL,
					initFilePath.c_str());
			}
			else {
				m_menu->GetPresetMenu().Insert(ID_PRESET+i+1, MF_BYCOMMAND,
					ID_PRESET+i, buf);
				WritePrivateProfileString(chSec, _T("Name"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Speed"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Speed"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Frequency"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Frequency"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Pitch"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Pitch"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Volume"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Volume"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Pan"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Pan"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ20"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ20"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ25"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ25"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ31.5"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ31.5"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ40"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ40"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ50"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ50"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ63"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ63"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ80"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ80"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ100"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ100"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ125"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ125"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ160"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ160"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ200"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ200"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ250"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ250"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ315"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ315"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ400"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ400"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ500"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ500"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ630"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ630"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ800"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ800"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ1K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ1K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ1.25K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ1.25K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ1.6K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ1.6K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ2K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ2K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ2.5K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ2.5K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ3.15K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ3.15K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ4K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ4K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ5K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ5K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ6.3K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ6.3K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ8K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ8K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ10K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ10K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ12.5K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ12.5K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ16K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ16K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EQ20K"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EQ20K"), buf, 
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ReverbDefault"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ReverbDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ReverbCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ReverbCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ReverbCustomize_Gain"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ReverbCustomize_Gain"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ReverbCustomize_RevMix"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ReverbCustomize_RevMix"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ReverbCustomize_RevTime"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ReverbCustomize_RevTime"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ReverbCustomize_High"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ReverbCustomize_High"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbDefault"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbPaddedCell"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbPaddedCell"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbRoom"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbBathRoom"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbBathRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbLivingRoom"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbLivingRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbStoneRoom"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbStoneRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbAuditorium"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbAuditorium"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbConcertHall"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbConcertHall"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbCave"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbCave"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbArena"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbArena"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbHangar"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbHangar"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCarpetedHallway"), _T(""), buf,  255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbCarpetedHallway"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbHallway"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbHallway"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbStoneCorridor"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbStoneCorridor"),
					buf,initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbAlley"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbAlley"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbForest"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbForest"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbCity"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbCity"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbMountains"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbMountains"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbQuarry"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbQuarry"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbPlain"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbPlain"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbParkingLot"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbParkingLot"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbSewerPipe"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbSewerPipe"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbUnderWater"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbUnderWater"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbSmallRoom"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbSmallRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbMediumRoom"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbMediumRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbLargeRoom"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbLargeRoom"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbMediumHall"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbMediumHall"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbLargeHall"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbLargeHall"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbPlate"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbPlate"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("3DReverbCustomize_Room"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbCustomize_Room"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_RoomHF"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("3DReverbCustomize_RoomHF"),
					buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_RoomRolloffFactor"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_RoomRolloffFactor"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_DecayTime"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_DecayTime"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_DecayHFRatio"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_DecayHFRatio"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_Reflections"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_Reflections"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_ReflectionsDelay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_ReflectionsDelay"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_Reverb"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_Reverb"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_ReverbDelay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_ReverbDelay"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_Diffusion"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_Diffusion"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_Density"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_Density"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("3DReverbCustomize_HFReference"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("3DReverbCustomize_HFReference"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayDefault"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayShort"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayShort"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayMedium"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayMedium"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayLong"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayLong"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayStereoShort"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayStereoShort"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayStereoMedium"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayStereoMedium"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayStereoLong"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayStereoLong"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayMountain"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayMountain"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayBig"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayBig"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayStereoBig"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayStereoBig"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayDoubling"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayDoubling"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayDoubleKick"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayDoubleKick"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DelayCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DelayCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DelayCustomize_WetDryMix"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DelayCustomize_WetDryMix"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DelayCustomize_Feedback"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DelayCustomize_Feedback"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DelayCustomize_LeftDelay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DelayCustomize_LeftDelay"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DelayCustomize_RightDelay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DelayCustomize_RightDelay"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DelayCustomize_PanDelay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DelayCustomize_PanDelay"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ChorusDefault"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ChorusDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ChorusCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ChorusCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ChorusCustomize_WetDryMix"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("ChorusCustomize_WetDryMix"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ChorusCustomize_Depth"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("ChorusCustomize_Depth"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ChorusCustomize_Feedback"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("ChorusCustomize_Feedback"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ChorusCustomize_Frequency"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("ChorusCustomize_Frequency"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ChorusCustomize_Waveform"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("ChorusCustomize_Waveform"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("ChorusCustomize_Delay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("ChorusCustomize_Delay"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("CompressorDefault"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("CompressorDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("CompressorCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("CompressorCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("CompressorCustomize_Gain"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("CompressorCustomize_Gain"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("CompressorCustomize_Attack"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("CompressorCustomize_Attack"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("CompressorCustomize_Release"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("CompressorCustomize_Release"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("CompressorCustomize_Threshold"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("CompressorCustomize_Threshold"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("CompressorCustomize_Ratio"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("CompressorCustomize_Ratio"), buf, initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("CompressorCustomize_Predelay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("CompressorCustomize_Predelay"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("FlangerDefault"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("FlangerDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("FlangerCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("FlangerCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("FlangerCustomize_WetDryMix"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("FlangerCustomize_WetDryMix"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("FlangerCustomize_Depth"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("FlangerCustomize_Depth"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("FlangerCustomize_Feedback"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("FlangerCustomize_Feedback"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("FlangerCustomize_Frequency"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("FlangerCustomize_Frequency"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("FlangerCustomize_Waveform"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("FlangerCustomize_Waveform"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("FlangerCustomize_Delay"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("FlangerCustomize_Delay"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("GargleDefault"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("GargleDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("GargleCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("GargleCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("GargleCustomize_RateHz"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("GargleCustomize_RateHz"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("GargleCustomize_WaveShape"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("GargleCustomize_WaveShape"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DistortionDefault"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DistortionDefault"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("DistortionCustomize"),
					_T(""), buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("DistortionCustomize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DistortionCustomize_Gain"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DistortionCustomize_Gain"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DistortionCustomize_Edge"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DistortionCustomize_Edge"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DistortionCustomize_PostEQCenterFrequency"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DistortionCustomize_PostEQCenterFrequency"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DistortionCustomize_PostEQBandwidth"), _T(""), buf, 255,
					initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DistortionCustomize_PostEQBandwidth"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec,
					_T("DistortionCustomize_PreLowpassCutoff"), _T(""), buf,
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec,
					_T("DistortionCustomize_PreLowpassCutoff"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Normalize"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Normalize"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("VocalCancel"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("VocalCancel"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Reverse"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Reverse"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Record"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Record"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("LowBattery"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("LowBattery"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("NoSense"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("NoSense"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("BassCopy"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("BassCopy"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("EarTraining"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("EarTraining"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("Monoral"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("Monoral"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("OnlyLeft"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("OnlyLeft"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("OnlyRight"), _T(""),
					buf, 255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("OnlyRight"), buf,
					initFilePath.c_str());
				GetPrivateProfileString(chNextSec, _T("ChangeLR"), _T(""), buf, 
					255, initFilePath.c_str());
				WritePrivateProfileString(chSec, _T("ChangeLR"), buf,
					initFilePath.c_str());
			}
		}
	}
	if(GetMenuItemCount(m_menu->GetPresetMenu()) == 3)
		DeleteMenu(m_menu->GetPresetMenu(), 2, MF_BYPOSITION);
}
//----------------------------------------------------------------------------
// 指定した%再生周波数を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownFreq(double freq)
{
	double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
	int newFreq = m_freqSlider->GetThumbPos() - (int)(freq
		* dCalc);
	int nMinFreq = m_freqSlider->GetRangeMin();
	if(newFreq < nMinFreq) newFreq = nMinFreq;
	m_freqLabel->SetFreq((double)(newFreq / dCalc));
	m_freqSlider->SetThumbPos((LONG)newFreq, TRUE);
	SetFreq((double)(newFreq / dCalc));
}
//----------------------------------------------------------------------------
// 指定した数値×半音分音程を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownPitch(double pitch)
{
	double dCalc = pow(10.0, m_pitchSlider->GetDecimalDigit());
	int newPitch = m_pitchSlider->GetThumbPos() - (int)(pitch * dCalc);
	int nMinPitch = m_pitchSlider->GetRangeMin();
	if(newPitch < nMinPitch) newPitch = nMinPitch;
	m_pitchLabel->SetPitch((double)(newPitch / dCalc));
	m_pitchSlider->SetThumbPos((LONG)newPitch, TRUE);
	SetPitch((double)(newPitch / dCalc));
}
//----------------------------------------------------------------------------
// 指定した%再生速度を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownSpeed(double speed)
{
	double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
	int newSpeed = m_speedSlider->GetThumbPos() - (int)(speed * dCalc);
	int nMinSpeed = m_speedSlider->GetRangeMin();
	if(newSpeed < nMinSpeed) newSpeed = nMinSpeed;
	m_speedLabel->SetSpeed((double)(newSpeed / dCalc));
	m_speedSlider->SetThumbPos((LONG)newSpeed, TRUE);
	SetSpeed((double)(newSpeed / dCalc));
}
//----------------------------------------------------------------------------
// 指定した%音量を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownVolume(int volume)
{
	int newVolume = m_volumeSlider->GetThumbPos() - (int)(volume * 10);
	if(newVolume < 0) newVolume = 0;
	m_volumeLabel->SetVolume((double)(newVolume / 10.0));
	m_volumeSlider->SetThumbPos((LONG)newVolume, TRUE);
	SetVolume((double)(newVolume / 10.0));
}
//----------------------------------------------------------------------------
// 早送り
//----------------------------------------------------------------------------
void CMainWnd::Forward()
{
	double dPos = m_sound->ChannelGetSecondsPosition();
	double dDifference = 1.0;
	dDifference *= m_sound->GetTempo() / 100.0;
	dDifference *= m_sound->GetSampleRate() / 100.0;
	if(dDifference < 1.0) dDifference = 1.0;
	SetTime(m_sound->ChannelSeconds2Bytes(dPos + dDifference));
}
//----------------------------------------------------------------------------
// 指定した秒数進む
//----------------------------------------------------------------------------
void CMainWnd::ForwardSeconds(int seconds)
{
	double pos = m_sound->ChannelGetSecondsPosition();
	pos += seconds;
	SetSeconds(pos);
}
//----------------------------------------------------------------------------
// 設定状態の読み込み
//----------------------------------------------------------------------------
void CMainWnd::LoadSettings(const PCTSTR & pFilePath)
{
	TCHAR buf[255];

	GetPrivateProfileString(_T("Options"), _T("Speed"), _T(""), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		double speed = _ttof(buf);
		double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
		m_speedLabel->SetSpeed(speed);
		m_speedSlider->SetThumbPos((LONG)(speed * dCalc), TRUE);
		SetSpeed(speed);
	}
	GetPrivateProfileString(_T("Options"), _T("Frequency"), _T(""), buf, 
		255, pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		double freq = _ttof(buf);
		double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
		m_freqLabel->SetFreq(freq);
		m_freqSlider->SetThumbPos((LONG)(freq * dCalc), TRUE);
		SetFreq(freq);
	}
	GetPrivateProfileString(_T("Options"), _T("Pitch"), _T(""), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		double pitch = _ttof(buf);
		double dCalc = pow(10.0, m_pitchSlider->GetDecimalDigit());
		m_pitchLabel->SetPitch(pitch);
		m_pitchSlider->SetThumbPos((LONG)(pitch * dCalc), TRUE);
		SetPitch(pitch);
	}
	GetPrivateProfileString(_T("Options"), _T("Volume"), _T(""), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int volume = _ttoi(buf);
		m_volumeLabel->SetVolume((double)(volume / 10.0));
		m_volumeSlider->SetThumbPos((LONG)volume, TRUE);
		SetVolume((double)(volume / 10.0));
	}
	GetPrivateProfileString(_T("Options"), _T("Pan"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int pan = _ttoi(buf);
		m_panLabel->SetPan(pan);
		m_panSlider->SetThumbPos((LONG)pan, TRUE);
		SetPan(pan);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ20"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq20Label->SetEQ20(eq);
		m_eq20Slider->SetThumbPos(eq);
		SetEQ20((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ25"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq25Label->SetEQ25(eq);
		m_eq25Slider->SetThumbPos(eq);
		SetEQ25((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ31.5"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq31_5Label->SetEQ31_5(eq);
		m_eq31_5Slider->SetThumbPos(eq);
		SetEQ31_5((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ40"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq40Label->SetEQ40(eq);
		m_eq40Slider->SetThumbPos(eq);
		SetEQ40((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ50"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq50Label->SetEQ50(eq);
		m_eq50Slider->SetThumbPos(eq);
		SetEQ50((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ63"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq63Label->SetEQ63(eq);
		m_eq63Slider->SetThumbPos(eq);
		SetEQ63((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ80"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq80Label->SetEQ80(eq);
		m_eq80Slider->SetThumbPos(eq);
		SetEQ80((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ100"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq100Label->SetEQ100(eq);
		m_eq100Slider->SetThumbPos(eq);
		SetEQ100((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ125"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq125Label->SetEQ125(eq);
		m_eq125Slider->SetThumbPos(eq);
		SetEQ125((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ160"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq160Label->SetEQ160(eq);
		m_eq160Slider->SetThumbPos(eq);
		SetEQ160((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ200"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq200Label->SetEQ200(eq);
		m_eq200Slider->SetThumbPos(eq);
		SetEQ200((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ250"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq250Label->SetEQ250(eq);
		m_eq250Slider->SetThumbPos(eq);
		SetEQ250((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ315"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq315Label->SetEQ315(eq);
		m_eq315Slider->SetThumbPos(eq);
		SetEQ315((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ400"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq400Label->SetEQ400(eq);
		m_eq400Slider->SetThumbPos(eq);
		SetEQ400((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ500"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq500Label->SetEQ500(eq);
		m_eq500Slider->SetThumbPos(eq);
		SetEQ500((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ630"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq630Label->SetEQ630(eq);
		m_eq630Slider->SetThumbPos(eq);
		SetEQ630((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ800"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq800Label->SetEQ800(eq);
		m_eq800Slider->SetThumbPos(eq);
		SetEQ800((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ1K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq1kLabel->SetEQ1K(eq);
		m_eq1kSlider->SetThumbPos(eq);
		SetEQ1K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ1.25K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq1_25kLabel->SetEQ1_25K(eq);
		m_eq1_25kSlider->SetThumbPos(eq);
		SetEQ1_25K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ1.6K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq1_6kLabel->SetEQ1_6K(eq);
		m_eq1_6kSlider->SetThumbPos(eq);
		SetEQ1_6K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ2K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq2kLabel->SetEQ2K(eq);
		m_eq2kSlider->SetThumbPos(eq);
		SetEQ2K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ2.5K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq2_5kLabel->SetEQ2_5K(eq);
		m_eq2_5kSlider->SetThumbPos(eq);
		SetEQ2_5K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ3.15K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq3_15kLabel->SetEQ3_15K(eq);
		m_eq3_15kSlider->SetThumbPos(eq);
		SetEQ3_15K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ4K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq4kLabel->SetEQ4K(eq);
		m_eq4kSlider->SetThumbPos(eq);
		SetEQ4K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ5K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq5kLabel->SetEQ5K(eq);
		m_eq5kSlider->SetThumbPos(eq);
		SetEQ5K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ6.3K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq6_3kLabel->SetEQ6_3K(eq);
		m_eq6_3kSlider->SetThumbPos(eq);
		SetEQ6_3K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ8K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq8kLabel->SetEQ8K(eq);
		m_eq8kSlider->SetThumbPos(eq);
		SetEQ8K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ10K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq10kLabel->SetEQ10K(eq);
		m_eq10kSlider->SetThumbPos(eq);
		SetEQ10K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ12.5K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq12_5kLabel->SetEQ12_5K(eq);
		m_eq12_5kSlider->SetThumbPos(eq);
		SetEQ12_5K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ16K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq16kLabel->SetEQ16K(eq);
		m_eq16kSlider->SetThumbPos(eq);
		SetEQ16K((LONG)eq);
	}
	GetPrivateProfileString(_T("Options"), _T("EQ20K"), _T("0"), buf, 255, 
		pFilePath);
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq20kLabel->SetEQ20K(eq);
		m_eq20kSlider->SetThumbPos(eq);
		SetEQ20K((LONG)eq);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("ReverbDefault"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_REVERB_DEFAULT))
		m_menu->OnReverbDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("ReverbCustomize"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_REVERB_CUSTOMIZE)) {
		TCHAR chGain[255], chRevMix[255], chRevTime[255], chHigh[255];
		GetPrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_Gain"),
			_T("0"), chGain, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_RevMix"),
			_T("0"), chRevMix, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_RevTime"),
			_T("0"), chRevTime, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_High"),
			_T("0"), chHigh, 255, pFilePath);
		m_menu->SetReverb((float)_ttof(chGain), (float)_ttof(chRevMix),
						 (float)_ttof(chRevTime), (float)_ttof(chHigh),
						 ID_REVERB_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbDefault"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_DEFAULT))
		m_menu->On3DReverbDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbPaddedCell"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PADDEDCELL))
		m_menu->On3DReverbPaddedCellMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbRoom"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_ROOM))
		m_menu->On3DReverbRoomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbBathRoom"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_BATHROOM))
		m_menu->On3DReverbBathroomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbLivingRoom"), _T("0"),
		buf,255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_LIVINGROOM))
		m_menu->On3DReverbLivingRoomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbStoneRoom"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_STONEROOM))
		m_menu->On3DReverbStoneRoomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbAuditorium"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_AUDITORIUM))
		m_menu->On3DReverbAuditoriumMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbConcertHall"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CONCERTHALL))
		m_menu->On3DReverbConcertHallMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCave"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CAVE))
		m_menu->On3DReverbCaveMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbArena"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_ARENA))
		m_menu->On3DReverbArenaMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbHangar"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_HANGAR))
		m_menu->On3DReverbHangarMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCarpetedHallway"),
		_T("0"), buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CARPETEDHALLWAY))
		m_menu->On3DReverbCarpetedHallwayMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbHallway"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_HALLWAY))
		m_menu->On3DReverbHallwayMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbStoneCorridor"),
		_T("0"), buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_STONECORRIDOR))
		m_menu->On3DReverbStoneCorridorMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbAlley"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_ALLEY))
		m_menu->On3DReverbAlleyMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbForest"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_FOREST))
		m_menu->On3DReverbForestMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCity"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CITY))
		m_menu->On3DReverbCityMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbMountains"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_MOUNTAINS))
		m_menu->On3DReverbMountainsMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbQuarry"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_QUARRY))
		m_menu->On3DReverbQuarryMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbPlain"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PLAIN))
		m_menu->On3DReverbPlainMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbParkingLot"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PARKINGLOT))
		m_menu->On3DReverbParkingLotMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbSewerPipe"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_SEWERPIPE))
		m_menu->On3DReverbSewerPipeMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbUnderWater"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_UNDERWATER))
		m_menu->On3DReverbUnderwaterMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbSmallRoom"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_SMALLROOM))
		m_menu->On3DReverbSmallRoomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbMediumRoom"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_MEDIUMROOM))
		m_menu->On3DReverbMediumRoomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbLargeRoom"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_LARGEROOM))
		m_menu->On3DReverbLargeRoomMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbMediumHall"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_MEDIUMHALL))
		m_menu->On3DReverbMediumHallMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbLargeHall"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_LARGEHALL))
		m_menu->On3DReverbLargeHallMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbPlate"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PLATE))
		m_menu->On3DReverbPlateMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CUSTOMIZE)) {
		TCHAR chRoom[255], chRoomHF[255], chRoomRolloffFactor[255],
			  chDecayTime[255], chDecayHFRatio[255], chReflections[255],
			  chReflectionsDelay[255], chReverb[255], chReverbDelay[255],
			  chDiffusion[255], chDensity[255], chHFReference[255];
		GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Room"),
			_T("0"), chRoom, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_RoomHF"),
			_T("0"), chRoomHF, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_RoomRolloffFactor"), _T("0"),
			chRoomRolloffFactor, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_DecayTime"), _T("0"), chDecayTime, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_DecayHFRatio"), _T("0"), chDecayHFRatio, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_Reflections"), _T("0"), chReflections, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_ReflectionsDelay"), _T("0"),
			chReflectionsDelay, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Reverb"),
			_T("0"), chReverb, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_ReverbDelay"), _T("0"), chReverbDelay, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_Diffusion"), _T("0"), chDiffusion, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Density"),
			_T("0"), chDensity, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("3DReverbCustomize_HFReference"), _T("0"), chHFReference, 255,
			pFilePath);
		m_menu->Set3DReverb(_ttoi(chRoom), _ttoi(chRoomHF),
			(float)_ttof(chRoomRolloffFactor), (float)_ttof(chDecayTime),
			(float)_ttof(chDecayHFRatio), _ttoi(chReflections),
			(float)_ttof(chReflectionsDelay), _ttoi(chReverb),
			(float)_ttof(chReverbDelay), (float)_ttof(chDiffusion),
			(float)_ttof(chDensity), (float)_ttof(chHFReference),
			ID_3DREVERB_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("DelayDefault"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_DEFAULT))
		m_menu->OnDelayDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayShort"), _T("0"), buf, 255,
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_SHORT))
		m_menu->OnDelayShortMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayMedium"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_MEDIUM))
		m_menu->OnDelayMediumMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayLong"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_LONG))
		m_menu->OnDelayLongMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayStereoShort"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOSHORT))
		m_menu->OnDelayStereoShortMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayStereoMedium"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOMEDIUM))
		m_menu->OnDelayStereoMediumMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayStereoLong"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOLONG))
		m_menu->OnDelayStereoLongMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayMountain"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_MOUNTAIN))
		m_menu->OnDelayMountainMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayBig"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_BIG))
		m_menu->OnDelayBigMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayStereoBig"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOBIG))
		m_menu->OnDelayStereoBigMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayDoubling"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_DOUBLING))
		m_menu->OnDelayDoublingMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayDoubleKick"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_DOUBLEKICK))
		m_menu->OnDelayDoubleKickMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DelayCustomize"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_CUSTOMIZE)) {
		TCHAR chWetDryMix[255], chFeedback[255], chLeftDelay[255],
			  chRightDelay[255], chPanDelay[255];
		GetPrivateProfileString(_T("PlayMode"), _T("DelayCustomize_WetDryMix"),
			_T("0"), chWetDryMix, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("DelayCustomize_Feedback"),
			_T("0"), chFeedback, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("DelayCustomize_LeftDelay"),
			_T("0"), chLeftDelay, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("DelayCustomize_RightDelay"), _T("0"), chRightDelay, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("DelayCustomize_PanDelay"),
			_T("0"), chPanDelay, 255, pFilePath);
		m_menu->SetDelay((float)_ttof(chWetDryMix), (float)_ttof(chFeedback),
			(float)_ttof(chLeftDelay), (float)_ttof(chRightDelay),
			(BOOL)_ttoi(chPanDelay), ID_DELAY_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("ChorusDefault"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CHORUS_DEFAULT))
		m_menu->OnChorusDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CHORUS_CUSTOMIZE)) {
		TCHAR chWetDryMix[255], chDepth[255], chFeedback[255], chFrequency[255],
			  chWaveForm[255], chDelay[255];
		GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_WetDryMix"),
			_T("0"), chWetDryMix, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Depth"),
			_T("0"), chDepth, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Feedback"),
			_T("0"), chFeedback, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Frequency"),
			_T("0"), chFrequency, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Waveform"),
			_T("0"), chWaveForm, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Delay"),
			_T("0"), chDelay, 255, pFilePath);
		m_menu->SetChorus((float)_ttof(chWetDryMix), (float)_ttof(chDepth),
			(float)_ttof(chFeedback), (float)_ttof(chFrequency),
			(DWORD)_ttoi(chWaveForm), (float)_ttof(chDelay),
			BASS_DX8_PHASE_90, ID_CHORUS_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("CompressorDefault"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_COMPRESSOR_DEFAULT))
		m_menu->OnCompressorDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("CompressorCustomize"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_COMPRESSOR_CUSTOMIZE)) {
		TCHAR chGain[255], chAttack[255], chRelease[255], chThreshold[255],
			  chRatio[255], chPredelay[255];
		GetPrivateProfileString(_T("PlayMode"), _T("CompressorCustomize_Gain"),
			_T("0"), chGain, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("CompressorCustomize_Attack"), _T("0"), chAttack, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("CompressorCustomize_Release"), _T("0"), chRelease, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("CompressorCustomize_Threshold"), _T("0"), chThreshold, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("CompressorCustomize_Ratio"),
			_T("0"), chRatio, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("CompressorCustomize_Predelay"), _T("0"), chPredelay, 255,
			pFilePath);
		m_menu->SetCompressor((float)_ttof(chGain), (float)_ttof(chAttack),
			(float)_ttof(chRelease), (float)_ttof(chThreshold),
			(float)_ttof(chRatio), (float)_ttof(chPredelay),
			ID_COMPRESSOR_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("FlangerDefault"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_FLANGER_DEFAULT))
		m_menu->OnFlangerDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("FlangerCustomize"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_FLANGER_CUSTOMIZE)) {
		TCHAR chWetDryMix[255], chDepth[255], chFeedback[255], chFrequency[255],
			  chWaveform[255], chDelay[255];
		GetPrivateProfileString(_T("PlayMode"),
			_T("FlangerCustomize_WetDryMix"), _T("0"), chWetDryMix, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Depth"),
			_T("0"), chDepth, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Feedback"),
			_T("0"), chFeedback, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("FlangerCustomize_Frequency"), _T("0"), chFrequency, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Waveform"),
			_T("0"), chWaveform, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Delay"),
			_T("0"), chDelay, 255, pFilePath);
		m_menu->SetFlanger((float)_ttof(chWetDryMix), (float)_ttof(chDepth),
			(float)_ttof(chFeedback), (float)_ttof(chFrequency),
			(DWORD)_ttoi(chWaveform), (float)_ttof(chDelay),
			BASS_DX8_PHASE_90, ID_FLANGER_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("GargleDefault"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_GARGLE_DEFAULT))
		m_menu->OnGargleDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("GargleCustomize"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_GARGLE_CUSTOMIZE)) {
		TCHAR chRateHz[255], chWaveShape[255];
		GetPrivateProfileString(_T("PlayMode"),
			_T("GargleCustomize_RateHz"), _T("0"), chRateHz, 255,
			pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("GargleCustomize_WaveShape"),
			_T("0"), chWaveShape, 255, pFilePath);
		m_menu->SetGargle((DWORD)_ttoi(chRateHz), (DWORD)_ttoi(chWaveShape),
			ID_GARGLE_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("DistortionDefault"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DISTORTION_DEFAULT))
		m_menu->OnDistortionDefaultMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DistortionCustomize"), _T("0"),
		buf, 255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DISTORTION_CUSTOMIZE)) {
		TCHAR chGain[255], chEdge[255], chPostEQCenterFrequency[255],
			  chPostEQBandwidth[255], chPreLowpassCutoff[255];
		GetPrivateProfileString(_T("PlayMode"),
			_T("DistortionCustomize_Gain"), _T("0"), chGain, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"), _T("DistortionCustomize_Edge"),
			_T("0"), chEdge, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("DistortionCustomize_PostEQCenterFrequency"), _T("0"),
			chPostEQCenterFrequency, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("DistortionCustomize_PostEQBandwidth"), _T("0"),
			chPostEQBandwidth, 255, pFilePath);
		GetPrivateProfileString(_T("PlayMode"),
			_T("DistortionCustomize_PreLowpassCutoff"), _T("0"),
			chPreLowpassCutoff, 255, pFilePath);
		m_menu->SetDistortion((float)_ttof(chGain), (float)_ttof(chEdge),
			(float)_ttof(chPostEQCenterFrequency),
			(float)_ttof(chPostEQBandwidth),
			(float)_ttof(chPreLowpassCutoff),
			ID_DISTORTION_CUSTOMIZE);
	}
	GetPrivateProfileString(_T("PlayMode"), _T("Normalize"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_NORMALIZE))
		SetNormalize();
	GetPrivateProfileString(_T("PlayMode"), _T("VocalCancel"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_VOCALCANCEL))
		SetVocalCancel();
	GetPrivateProfileString(_T("PlayMode"), _T("Reverse"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_REVERSE))
		SetReverse();
	GetPrivateProfileString(_T("PlayMode"), _T("Record"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_RECORD))
		SetRecord();
	GetPrivateProfileString(_T("PlayMode"), _T("LowBattery"), _T("0"), buf, 255,
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_LOWBATTERY))
		SetLowBattery();
	GetPrivateProfileString(_T("PlayMode"), _T("NoSense"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_NOSENSE))
		SetNoSense();
	GetPrivateProfileString(_T("PlayMode"), _T("BassCopy"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_BASSCOPY))
		m_menu->OnBassCopyMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("DrumsCopy"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CYMBALCOPY))
		m_menu->OnDrumsCopyMenuSelected();
	GetPrivateProfileString(_T("PlayMode"), _T("EarTraining"), _T("0"), buf,
		255, pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_EARTRAINING))
		SetEarTraining();
	GetPrivateProfileString(_T("PlayMode"), _T("Monoral"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_MONORAL))
		SetMonoral();
	GetPrivateProfileString(_T("PlayMode"), _T("OnlyLeft"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_ONLYLEFT))
		SetOnlyLeft();
	GetPrivateProfileString(_T("PlayMode"), _T("OnlyRight"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_ONLYRIGHT))
		SetOnlyRight();
	GetPrivateProfileString(_T("PlayMode"), _T("ChangeLR"), _T("0"), buf, 255, 
		pFilePath);
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CHANGELR))
		SetChangeLR();
}
//----------------------------------------------------------------------------
// リストの移動
//----------------------------------------------------------------------------
void CMainWnd::MoveList(int nFrom, int nTo)
{
	CPlayListView_MainWnd* pList = m_arrayList[nFrom];
	if(nFrom < nTo) m_arrayList.insert(m_arrayList.begin() + nTo + 1, pList);
	else m_arrayList.insert(m_arrayList.begin() + nTo, pList);
	if(nFrom < nTo) m_arrayList.erase(m_arrayList.begin() + nFrom);
	else m_arrayList.erase(m_arrayList.begin() + nFrom + 1);
	m_tab->SetCurrentFocus(nTo);
	if(nFrom < nCurPlayTab && nCurPlayTab <= nTo) nCurPlayTab--;
	else if(nFrom == nCurPlayTab) nCurPlayTab = nTo;
	else if(nTo <= nCurPlayTab && nCurPlayTab < nFrom) nCurPlayTab++;
}
//----------------------------------------------------------------------------
// 頭出し
//----------------------------------------------------------------------------
void CMainWnd::Head()
{
	if(bMarkerPlay) SetTime(m_sound->GetLoopPosA());
	else if(m_menu->IsItemChecked(ID_PLAYRANGE)) SetSeconds(m_dStartSeconds);
	else SetTime(0);
}
//----------------------------------------------------------------------------
// ファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenFile(LPCTSTR lpszFilePath, int nCount)
{
	if(m_sound->IsABLoopA()) SetABLoopA();
	if(m_sound->IsABLoopB()) SetABLoopB();
	if(bMarkerPlay) SetMarkerPlay();
	m_sound->StopASIO();
	m_sound->StopWASAPI();
	BOOL bRet = FALSE;
	if(m_menu->IsItemChecked(ID_QUALITY_WASAPI)) m_sound->StartWASAPI();
	if(PathIsURL(lpszFilePath)) bRet = m_sound->StreamCreateURL(lpszFilePath);
	else bRet = m_sound->StreamCreateFile(lpszFilePath, FALSE, nCount);
	if(!bRet) {
		m_menu->SetFileLoadState(FALSE);
		KillTimer(IDT_TIME);
		m_timeLabel->SetTime(0, 0);
		m_timeSlider->SetTime(0, 10);
		m_toolBar->SetPlayingState(FALSE);
		return FALSE;
	}
	if(m_menu->IsItemChecked(ID_QUALITY_ASIO)) m_sound->StartASIO();
	m_sound->ClearMarker();
	SetAllEffects();
	m_menu->SetFileLoadState(TRUE);
	m_toolBar->SetPlayingState(FALSE);
	if(m_menu->IsItemChecked(ID_REVERSE)) {
		if(m_menu->IsItemChecked(ID_PLAYRANGE)) SetSeconds(m_dEndSeconds);
		else {
			m_timeLabel->SetTime(m_sound->ChannelGetSecondsLength(),
								m_sound->ChannelGetSecondsLength());
			m_timeSlider->SetTime(m_sound->ChannelGetLength(),
								 m_sound->ChannelGetLength());
		}
	}
	else {
		if(m_menu->IsItemChecked(ID_PLAYRANGE)) SetSeconds(m_dStartSeconds);
		else {
			m_timeLabel->SetTime(0, m_sound->ChannelGetSecondsLength());
			m_timeSlider->SetTime(0, m_sound->ChannelGetLength());
		}
	}

	StartUpdateInfo();
	if(m_hLyricsThread) {
		m_bLyricsThreadAlive = FALSE;
		DWORD dwExitCode = STILL_ACTIVE;
		while(dwExitCode == STILL_ACTIVE)
			GetExitCodeThread(m_hLyricsThread, &dwExitCode);
		m_hLyricsThread = 0;
	}
	lyricsManager->ClearScreen();
	if(!m_bVideo && m_menu->IsItemChecked(ID_LYRICS) &&
			lyricsManager->IsLyricsRead()) {
		m_bLyricsThreadAlive = TRUE;
		m_hLyricsThread = (HANDLE)_beginthread(
			&CMainWnd::UpdateLyricsThreadProc, 0, this);
	}
	if(!m_bVideo) lyricsManager->Read(lpszFilePath);
	StartLyrics();
	StartPitchAnalyser();
	return TRUE;
}
//----------------------------------------------------------------------------
// INI ファイルを開く
//----------------------------------------------------------------------------
void CMainWnd::OpenInitFile()
{
	TCHAR chPath[255], buf[255];
	lstrcpy(chPath, (m_rApp.GetFilePath() + _T("Setting.ini")).c_str());

	if(GetPrivateProfileInt(_T("Visible"), _T("eq20"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ20);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq25"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ25);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq31_5"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ31_5);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq40"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ40);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq50"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ50);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq63"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ63);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq80"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ80);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq100"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ100);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq125"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ125);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq160"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ160);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq200"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ200);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq250"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ250);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq315"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ315);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq400"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ400);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq500"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ500);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq630"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ630);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq800"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ800);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq1k"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ1K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq1_25k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ1_25K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq1_6k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ1_6K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq2k"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ2K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq2_5k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ2_5K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq3_15k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ3_15K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq4k"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ4K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq5k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ5K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq6_3k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ6_3K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq8k"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ8K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq10k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ10K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq12_5k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ12_5K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq16k"), 1, chPath))
		m_menu->SwitchEQVisible(ID_EQ16K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq20k"), 0, chPath))
		m_menu->SwitchEQVisible(ID_EQ20K);
	GetPrivateProfileString(_T("Options"), _T("Toolbar"), _T("Small"), buf,
		255, chPath);
	if(lstrcmp(buf, _T("Large")) == 0) m_menu->OnToolbarLSizeMenuSelected();
	if(lstrcmp(buf, _T("Medium")) == 0) m_menu->OnToolbarMSizeMenuSelected();
	int nCount   = SendMessage(*m_toolBar, TB_BUTTONCOUNT, 0, 0);
	BOOL bFirst = TRUE;
	std::vector<TBBUTTON> m_arrayButton = m_toolBar->GetArrayButton();
	for(int i = 0; i < (int)m_arrayButton.size(); i++) {
		TCHAR key[255];
		_stprintf_s(key, _T("ToolBar%d"), i);
		GetPrivateProfileString(_T("Visible"), key, _T("-1"), buf, 255,
			chPath);
		int nCommand = _ttoi(buf);
		if(nCommand == -1) break;
		if(bFirst) {
			bFirst = FALSE;
			int b = SendMessage(*m_toolBar, TB_BUTTONCOUNT, 0, 0);
			for(int j = 0; j < b; j++)
				SendMessage(*m_toolBar, TB_DELETEBUTTON, 0, 0);
		}
		for(int j = 0; j < (int)m_arrayButton.size(); j++) {
			if(nCommand == m_arrayButton[j].idCommand) {
				SendMessage(*m_toolBar, TB_ADDBUTTONS, 1,
					(LPARAM)&m_arrayButton[j]);
				break;
			}
		}
		m_toolBar->SetPlayingState(!m_sound->ChannelIsStopped());
		m_toolBar->SetPausingState(m_sound->ChannelIsPausing());
		m_toolBar->CheckButton(ID_ALOOP, m_menu->IsItemChecked(ID_ALOOP));
		m_toolBar->CheckButton(ID_RANDOM, m_menu->IsItemChecked(ID_RANDOM));
		m_toolBar->SetSingleLoopState(m_sound->IsLoop());
		m_toolBar->SetMarkerPlayState(bMarkerPlay);
		if(!bMarkerPlay)
			m_toolBar->SetABLoopState(m_sound->IsABLoopA(), m_sound->IsABLoopB());
		m_toolBar->CheckButton(ID_PLAYLIST, m_menu->IsItemChecked(ID_PLAYLIST));
		m_toolBar->CheckButton(ID_EXPLORER, m_menu->IsItemChecked(ID_EXPLORER));
	}

	// 再生モードの設定
	if(GetPrivateProfileInt(_T("PlayMode"), _T("RecoverSingleLoop"), 1,
			chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERSLOOP);
		if(GetPrivateProfileInt(_T("PlayMode"), _T("SingleLoop"), 0,
				chPath))
			SetSingleLoop();
	}
	if(GetPrivateProfileInt(_T("PlayMode"), _T("RecoverAllLoop"), 1,
			chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERALOOP);
		if(GetPrivateProfileInt(_T("PlayMode"), _T("AllLoop"), 0, chPath))
			SetAllLoop();
	}
	if(GetPrivateProfileInt(_T("PlayMode"), _T("RecoverRandom"), 1,
			chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERRANDOM);
		if(GetPrivateProfileInt(_T("PlayMode"), _T("Random"), 0, chPath))
			SetRandom();
	}

	// その他の設定
	if(GetPrivateProfileInt(_T("Window"), _T("RecoverPos"), 0, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERWPOS);
		WINDOWPLACEMENT wndPlace;
		ZeroMemory(&wndPlace, sizeof(WINDOWPLACEMENT));
		wndPlace.length = sizeof(WINDOWPLACEMENT);
		wndPlace.rcNormalPosition.left
			= GetPrivateProfileInt(_T("Window"), _T("Left"), 0, chPath);
		wndPlace.rcNormalPosition.top
			= GetPrivateProfileInt(_T("Window"), _T("Top"), 0, chPath);
		SetWindowPlacement(m_hWnd, &wndPlace);
	}
	if(GetPrivateProfileInt(_T("Window"), _T("RecoverSize"), 0, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERWSIZE);
		SetSize(GetPrivateProfileInt(_T("Window"), _T("Width"), 320, chPath),
			GetPrivateProfileInt(_T("Window"), _T("Height"), 240, chPath));
		if(GetPrivateProfileInt(_T("Window"), _T("Zoomed"), 0, chPath))
			Show(SW_MAXIMIZE);
		else Show(m_rApp.GetNCmdShow());
	}
	else Show(m_rApp.GetNCmdShow());
}
//----------------------------------------------------------------------------
// INI ファイルを開く
//----------------------------------------------------------------------------
void CMainWnd::OpenInitFileAfterShow()
{
	tstring initFilePath = m_rApp.GetFilePath() + _T("Setting.ini");

	TCHAR buf[255];

	// ビデオ画面表示内容の設定
	if(!GetPrivateProfileInt(_T("Visible"), _T("Lyrics"), 1,
			initFilePath.c_str()))
		m_menu->OnLyricsMenuSelected();
	if(GetPrivateProfileInt(_T("Visible"), _T("PitchAnalyser"), 0,
			initFilePath.c_str()))
		m_menu->OnPitchAnalyserMenuSelected();

	// 再生モードの設定
	GetPrivateProfileString(_T("PlayMode"), _T("RecoverContinue"), _T("1"), 
		buf, 255, initFilePath.c_str());
	int _bRecoverContinue = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("Continue"), _T("1"), buf, 255, 
		initFilePath.c_str());
	int _bContinue = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("SameArtist"), _T("0"), buf, 255,
		initFilePath.c_str());
	int _bSameArtist = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("RecoverInstantLoop"), _T("1"), 
		buf, 255, initFilePath.c_str());
	int _bRecoverInstantLoop = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("RecoverSetPositionAuto"), 
		_T("1"), buf, 255, initFilePath.c_str());
	int _bRecoverSetPositionAuto = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("RecoverReverse"), _T("1"), buf,
		255, initFilePath.c_str());
	int _bRecoverReverse = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("RecoverRecord"), _T("1"), buf,
		255, initFilePath.c_str());
	int _bRecoverRecord = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("InstantLoop"), _T("1"), buf,
		255, initFilePath.c_str());
	int _bInstantLoop = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("SetPositionAuto"), _T("0"),
		buf, 255, initFilePath.c_str());
	int _bSetPositionAuto = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("Reverse"), _T("0"), buf, 255,
		initFilePath.c_str());
	int _bReverse = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("Record"), _T("0"), buf, 255,
		initFilePath.c_str());
	int _bRecord = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("Normalize"), _T("0"), buf, 255,
		initFilePath.c_str());
	int _bNormalize = _ttoi(buf);

	// ショートカットキー設定
	TCHAR szKey[32767];
	CCommandList cmdlist;
	if (GetPrivateProfileSection(_T("KeySetting"), szKey, 32767,
		initFilePath.c_str())) {
		m_rApp.GetAccelTable().Destroy();
		for(TCHAR * ptr = szKey; *ptr != NULL; ptr += lstrlen(ptr) + 1) {
			tstring strShortCut = ptr;
			BYTE fVirt = FVIRTKEY;
			if(strShortCut.find(_T("Ctrl")) != tstring::npos)
				fVirt |= FCONTROL;
			if(strShortCut.find(_T("Alt")) != tstring::npos) fVirt |= FALT;
			if(strShortCut.find(_T("Shift")) != tstring::npos) fVirt |= FSHIFT;
			UINT key = 0;
			if(strShortCut.rfind(_T("+"), strShortCut.rfind(_T("=")) - 2)
				!= tstring::npos) {
				int from = strShortCut.rfind(_T("+"),
					strShortCut.rfind(_T("=")) - 2) + 2;
				int len = strShortCut.rfind(_T("=")) - from;
				key = m_rApp.GetAccelTable().GetKeyFromString(
					strShortCut.substr(from, len));
			}
			else {
				int len = strShortCut.rfind(_T("="));
				key = m_rApp.GetAccelTable().GetKeyFromString(
					UnEscapeKeystr(strShortCut.substr(0, len)));
			}

			WORD cmd = cmdlist.GetCommandId(strShortCut.substr(
				strShortCut.rfind(_T("=")) + 1));
			m_rApp.GetAccelTable().Add(fVirt, key, cmd);
		}
	}
	else
		m_rApp.GetAccelTable().SetDefault();

	// グローバルホットキー設定
	TCHAR szOutKey[32767];
	GetPrivateProfileSection(_T("OutKeySetting"), szOutKey, 32767, 
		initFilePath.c_str());
	if(!(HWND)*outKeySettingWnd) outKeySettingWnd->Create();
	for(TCHAR * ptr = szOutKey; *ptr != NULL; ptr += lstrlen(ptr) + 1) {
		tstring strShortCut = ptr;
		BYTE fVirt = 0;
		UINT bfMods = 0;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos) {
			fVirt |= MOD_CONTROL;
			bfMods |= HOTKEYF_CONTROL;
		}
		if(strShortCut.find(_T("Alt")) != tstring::npos) {
			fVirt |= MOD_ALT;
			bfMods |= HOTKEYF_ALT;
		}
		if(strShortCut.find(_T("Shift")) != tstring::npos) {
			fVirt |= MOD_SHIFT;
			bfMods |= HOTKEYF_SHIFT;
		}
		UINT key = 0;
		if(strShortCut.rfind(_T("+"), strShortCut.rfind(_T("=")) - 2)
			!= tstring::npos) {
			int from = strShortCut.rfind(_T("+"), strShortCut.rfind(_T("="))
				- 2) + 2;
			int len = strShortCut.rfind(_T("=")) - from;
			key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.substr(
				from, len));
		}
		else {
			int len = strShortCut.rfind(_T("="));
			key = m_rApp.GetAccelTable().GetKeyFromString(UnEscapeKeystr(
				strShortCut.substr(0, len)));
		}

		WORD cmd = cmdlist.GetCommandId(strShortCut.substr(strShortCut.rfind(
			_T("="))+1));
		if(RegisterHotKey(m_hWnd, cmd, fVirt, key))
			outKeySettingWnd->AddList(key, bfMods, strShortCut.substr(
			strShortCut.rfind(_T("="))+1));
	}
	outKeySettingWnd->Close();

	// その他の設定
	GetPrivateProfileString(_T("Options"), _T("LAMECommandLine"),
		_T("--preset cbr 192"), buf, 255, initFilePath.c_str());
	m_strLAMECommandLine = buf;
	GetPrivateProfileString(_T("Options"), _T("DoubleRun"), _T("1"), buf, 255, 
		initFilePath.c_str());
	int _bDoubleRun = _ttoi(buf);
	GetPrivateProfileString(_T("Options"), _T("TopMost"), _T("0"), buf, 255, 
		initFilePath.c_str());
	int _bTopMost = _ttoi(buf);
	GetPrivateProfileString(_T("Options"), _T("TaskTray"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_ttoi(buf)) m_menu->CheckItem(ID_TASKTRAY, MF_CHECKED);
	GetPrivateProfileString(_T("Options"), _T("SaveFormat"), _T("WAVE"), buf, 
		255, initFilePath.c_str());
	strSaveFormat = buf;
	GetPrivateProfileString(_T("Options"), _T("RecoverList"), _T("1"), buf, 
		255, initFilePath.c_str());
	int _bRecoverList = _ttoi(buf);
	GetPrivateProfileString(_T("Options"), _T("FadeoutStop"), _T("0"), buf, 
		255, initFilePath.c_str());
	if(_ttoi(buf)) m_menu->CheckItem(ID_FADEOUTSTOP, MF_CHECKED);
	GetPrivateProfileString(_T("Options"), _T("FadeoutStopTime"), _T("3000"),
		buf, 255, initFilePath.c_str());
	if(_ttoi(buf) == 1000) m_menu->OnFadeout1SecMenuSelected();
	else if(_ttoi(buf) == 2000) m_menu->OnFadeout2SecMenuSelected();
	else if(_ttoi(buf) == 4000) m_menu->OnFadeout4SecMenuSelected();
	else if(_ttoi(buf) == 5000) m_menu->OnFadeout5SecMenuSelected();
	else if(_ttoi(buf) == 6000) m_menu->OnFadeout6SecMenuSelected();
	else if(_ttoi(buf) == 7000) m_menu->OnFadeout7SecMenuSelected();
	else if(_ttoi(buf) == 8000) m_menu->OnFadeout8SecMenuSelected();
	else if(_ttoi(buf) == 9000) m_menu->OnFadeout9SecMenuSelected();
	else if(_ttoi(buf) == 10000) m_menu->OnFadeout10SecMenuSelected();
	else m_menu->OnFadeout3SecMenuSelected();

	GetPrivateProfileString(_T("Options"), _T("FadeoutNext"), _T("0"), buf, 
		255, initFilePath.c_str());
	if(_ttoi(buf)) m_menu->CheckItem(ID_FADEOUTNEXT, MF_CHECKED);
	GetPrivateProfileString(_T("Options"), _T("FadeoutNextTime"), _T("3000"),
		buf, 255, initFilePath.c_str());
	if(_ttoi(buf) == 1000) m_menu->OnFadeoutNext1SecMenuSelected();
	else if(_ttoi(buf) == 2000) m_menu->OnFadeoutNext2SecMenuSelected();
	else if(_ttoi(buf) == 4000) m_menu->OnFadeoutNext4SecMenuSelected();
	else if(_ttoi(buf) == 5000) m_menu->OnFadeoutNext5SecMenuSelected();
	else if(_ttoi(buf) == 6000) m_menu->OnFadeoutNext6SecMenuSelected();
	else if(_ttoi(buf) == 7000) m_menu->OnFadeoutNext7SecMenuSelected();
	else if(_ttoi(buf) == 8000) m_menu->OnFadeoutNext8SecMenuSelected();
	else if(_ttoi(buf) == 9000) m_menu->OnFadeoutNext9SecMenuSelected();
	else if(_ttoi(buf) == 10000) m_menu->OnFadeoutNext10SecMenuSelected();
	else m_menu->OnFadeoutNext3SecMenuSelected();

	// プリセットの設定
	int i = 1;
	TCHAR section[255];
	while(TRUE) {
		_stprintf_s(section, _T("Preset%d"), i);
		GetPrivateProfileString(section, _T("Name"), _T(""), buf, 255,
			initFilePath.c_str());
		if(_tcsicmp(buf, _T("")) == 0) break;
		else {
			if(i == 1) m_menu->GetPresetMenu().AppendSeparator();
			m_menu->GetPresetMenu().Append(MFS_ENABLED, ID_PRESET + i, buf);
		}
		i++;
	}

	// 再生モードの復元
	if(_bRecoverContinue) {
		m_menu->SwitchItemChecked(ID_RECOVERCONTINUE);
		if(!_bContinue) SetContinue();
	}
	if(_bSameArtist) m_menu->SwitchItemChecked(ID_SAMEARTIST);
	if(_bRecoverInstantLoop) {
		m_menu->SwitchItemChecked(ID_RECOVERINSTANTLOOP);
		if(_bInstantLoop) SetInstantLoop();
	}
	if(_bRecoverSetPositionAuto) {
		m_menu->SwitchItemChecked(ID_RECOVERSETPOSITIONAUTO);
		if(_bSetPositionAuto) SetPositionAuto();
	}
	if(_bRecoverReverse) {
		m_menu->SwitchItemChecked(ID_RECOVERREVERSE);
		if(_bReverse) SetReverse();
	}
	if(_bRecoverRecord) {
		m_menu->SwitchItemChecked(ID_RECOVERRECORD);
		if(_bRecord) SetRecord();
	}
	if(_bNormalize) SetNormalize();

	if(_bDoubleRun) SetDoubleRun();
	if(_bTopMost) SetTopMost();
	if(_bRecoverList) {
		m_menu->SwitchItemChecked(ID_RECOVERLIST);

		tstring m3uFilePath = m_rApp.GetFilePath() + _T("Init.m3u8");
		AddFile(m3uFilePath.c_str());
		DeleteFile(m3uFilePath.c_str());

		for(int i = 0; ; i++) {
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("Title%d"), i);
			GetPrivateProfileString(_T("PlayList"), chKey, _T(""), buf, 255,
									initFilePath.c_str());
			if(lstrcmp(buf, _T("")) == 0) break;
			else {
				if(i > 0) CreateNewList(FALSE);
				m_tab->SetItem(buf, i);
				if(i == 0) m_tab->SetCurrentFocus(0);
			}
		}
		InvalidateRect(NULL, TRUE);
		Update();
		for(int i = 0; i < (int)m_arrayList.size(); i++) {
			MSG msg;
			int j = 0;
			while(TRUE) {
				if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
					if(GetMessage(&msg, NULL, 0, 0) > 0) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				else {
					// ウィンドウが閉じられたら終了
					if(!IsWindow(m_hWnd)) return;

					TCHAR filePath[MAX_PATH];
					TCHAR chKey[255];
					_stprintf_s(chKey, _T("Item%d-%d"), i, j);
					GetPrivateProfileString(_T("PlayList"), chKey, _T(""), 
						filePath, 255, initFilePath.c_str());
					tstring str = filePath;
					if(str == _T("")) break;
					else m_arrayList[i]->AddFile(str.c_str());
					j++;
				}
			}
			int nColCount = Header_GetItemCount(
				ListView_GetHeader(*m_arrayList[i]));
			int* pnOrderArray = new int[nColCount];
			for(int j = 0; j < nColCount; j++) {
				TCHAR chKey[255];
				_stprintf_s(chKey, _T("ListColumn%dWidth%d"), i, j);
				GetPrivateProfileString(_T("Options"), chKey, _T("-1"), buf, 
					255, initFilePath.c_str());
				int nWidth = _ttoi(buf);
				if(nWidth >= 0) ListView_SetColumnWidth(*m_arrayList[i], j,
									nWidth);
			}
			for(int j = 0; j < nColCount; j++) {
				TCHAR chKey[255];
				_stprintf_s(chKey, _T("ListColumn%dOrder%d"), i, j);
				TCHAR chReturn[255];
				_stprintf_s(chReturn, _T("%d"), j);
				GetPrivateProfileString(_T("Options"), chKey, chReturn, buf,
					255, initFilePath.c_str());
				pnOrderArray[j] = _ttoi(buf);
			}
			ListView_SetColumnOrderArray(*m_arrayList[i], nColCount, 
				pnOrderArray);
			delete pnOrderArray;
			if(i == 0) {
				if(m_arrayList[0]->GetItemCount() > 0) {
					m_sound->SetCurFileNum(0);
					PlayNext(FALSE, TRUE);
				}
			}
		}
		StartUpdateInfo();

		GetPrivateProfileString(_T("Options"), _T("CurPlayTab"), _T("0"), buf, 
			255, initFilePath.c_str());
		m_tab->SetCurrentFocus(_ttoi(buf));
		ChangeCurPlayTab();
		GetPrivateProfileString(_T("Options"), _T("CurFileNum"), _T("-1"), buf, 
			255, initFilePath.c_str());
		if(_ttoi(buf) + 1 <= GetCurPlayList().GetItemCount()
				&& _ttoi(buf) >= 0) {
			Play(_ttoi(buf));
			Stop(TRUE);
		}
	}
	GetPrivateProfileString(_T("Options"), _T("RecoverPlayPos"), _T("0"), 
		buf, 255, initFilePath.c_str());
	if(_bRecoverList && _ttoi(buf)) {
		m_menu->CheckItem(ID_RECOVERPLAYPOS, MF_CHECKED);
		int i = 0;
		while(TRUE) {
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("MarkerPos%d"), i + 1);
			int nMarkerPos;
			if((nMarkerPos = GetPrivateProfileInt(_T("Options"), chKey, 0,
					initFilePath.c_str())) > 0) {
				m_sound->ChannelSetPosition(nMarkerPos);
				AddMarker();
			}
			else break;
			i++;
		}
		GetPrivateProfileString(_T("Options"), _T("PlayPos"), _T("0.0"), buf,
			255, initFilePath.c_str());
		if((double)(int)_ttof(buf) > 0.0)
			SetTime(m_sound->ChannelSeconds2Bytes((double)(int)_ttof(buf)));
		if(!bMarkerPlay) {
			GetPrivateProfileString(_T("Options"), _T("ABLoopPosB"),
				_T("-1.000"), buf, 255, initFilePath.c_str());
			if(_ttof(buf) >= 0.0) {
				SetABLoopB();
				SetABLoopB_Sec(_ttof(buf));
			}
			GetPrivateProfileString(_T("Options"), _T("ABLoopPosA"),
				_T("-1.000"), buf, 255, initFilePath.c_str());
			if(_ttof(buf) >= 0.0) {
				SetABLoopA();
				SetABLoopA_Sec(_ttof(buf));
			}
		}
	}

	m_arrayList[0]->InvalidateRect(NULL, TRUE);
	m_arrayList[0]->Update();

	isInitFileRead = TRUE;
}
//----------------------------------------------------------------------------
// 次のファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenNext()
{
	if(m_menu->IsItemChecked(ID_RANDOM)) return OpenRandom();

	// 開くべきファイルを探す

	int i = m_sound->GetCurFileNum();
	if(m_sound->GetNSFCount() > 0
			&& m_sound->GetNSFCurrent() < m_sound->GetNSFCount()) {
		TCHAR filePath[MAX_PATH];
		m_arrayList[nCurPlayTab]->GetItemText(i - 1, 7, filePath, MAX_PATH);
		if(OpenFile(filePath, m_sound->GetNSFCurrent() + 1)) {
			TCHAR chTitle[255];
			m_arrayList[nCurPlayTab]->GetItemText(i - 1, 2, chTitle, 255);
			TCHAR chNSFCount[255];
			_stprintf_s(chNSFCount, _T("(%d/%d)"), m_sound->GetNSFCurrent(),
				m_sound->GetNSFCount());
			lstrcat(chTitle, chNSFCount);
			lstrcat(chTitle, _T(" - "));
			lstrcat(chTitle, m_rApp.GetName().c_str());
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->ScrollToItem(i - 1);
			return TRUE;
		}
	}
	m_sound->SetNSFCurrent(0);
	TCHAR chArtist[255];
	m_arrayList[nCurPlayTab]->GetItemText(i - 1, 3, chArtist, 255);
	for(; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++) {
		m_arrayList[nCurPlayTab]->SetPlayOrder(i, -1);
		TCHAR filePath[MAX_PATH];
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, filePath, MAX_PATH);
		TCHAR chNewArtist[255];
		m_arrayList[nCurPlayTab]->GetItemText(i, 3, chNewArtist, 255);
		if(m_menu->IsItemChecked(ID_SAMEARTIST) &&
				(lstrcmp(chArtist, chNewArtist) != 0)) {
			if(i == m_arrayList[nCurPlayTab]->GetItemCount() - 1) i = -1;
			continue;
		}
		m_sound->SetCurFileNum(i + 1);
		if(OpenFile(filePath)) {
			TCHAR chTitle[255];
			m_arrayList[nCurPlayTab]->GetItemText(i, 2, chTitle, 255);
			if(m_sound->GetNSFCount() > 0) {
				TCHAR chNSFCount[255];
				_stprintf_s(chNSFCount, _T("(%d/%d)"), m_sound->GetNSFCurrent(),
					m_sound->GetNSFCount());
				lstrcat(chTitle, chNSFCount);
			}
			lstrcat(chTitle, _T(" - "));
			lstrcat(chTitle, m_rApp.GetName().c_str());
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->ScrollToItem(i);
			break;
		}
		else {
			// 開けなかったファイルを削除
			m_arrayList[nCurPlayTab]->DeleteItem(i);
			m_arrayList[nCurPlayTab]->ResetNumber();

			i--; // 削除した分、ひとつ前に戻す
		}
	}

	m_arrayList[nCurPlayTab]->InvalidateRect(NULL, TRUE);
	SetPreviousNextMenuState();

	// 次に開くべきファイルが見つからなかった場合
	if(i >= m_arrayList[nCurPlayTab]->GetItemCount()) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// 前のファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenPrevious()
{
	int i = m_sound->GetCurFileNum();
	if(m_sound->GetNSFCount() > 0
			&& m_sound->GetNSFCurrent() < m_sound->GetNSFCount()
			&& m_sound->GetNSFCurrent() > 1) {
		TCHAR filePath[MAX_PATH];
		m_arrayList[nCurPlayTab]->GetItemText(i - 1, 7, filePath, MAX_PATH);
		if(OpenFile(filePath, m_sound->GetNSFCurrent() - 1)) {
			TCHAR chTitle[255];
			m_arrayList[nCurPlayTab]->GetItemText(i - 1, 2, chTitle, 255);
			TCHAR chNSFCount[255];
			_stprintf_s(chNSFCount, _T("(%d/%d)"), m_sound->GetNSFCurrent(),
				m_sound->GetNSFCount());
			lstrcat(chTitle, chNSFCount);
			lstrcat(chTitle, _T(" - "));
			lstrcat(chTitle, m_rApp.GetName().c_str());
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->ScrollToItem(i - 1);
			return TRUE;
		}
	}
	m_sound->SetNSFCurrent(0);

	TCHAR chArtist[255];
	m_arrayList[nCurPlayTab]->GetItemText(i - 1, 3, chArtist, 255);
	if(m_menu->IsItemChecked(ID_RANDOM)) {
		m_arrayList[nCurPlayTab]->SetPlayOrder(m_sound->GetCurFileNum()-1, -1);
		int nMax = m_arrayList[nCurPlayTab]->GetMaxPlayOrder();
		i = 0;
		std::vector<int> orders = m_arrayList[nCurPlayTab]->GetOrders();
		for(; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++)
			if(nMax == orders[i]) break;

		m_arrayList[nCurPlayTab]->SetPlayOrder(i, -1);
		TCHAR szFilePath[MAX_PATH];
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, szFilePath, MAX_PATH);
		m_sound->SetCurFileNum(i+1);
		BOOL bRet = OpenFile(szFilePath);
		if(bRet) {
			TCHAR chTitle[255];
			m_arrayList[nCurPlayTab]->GetItemText(i, 2, chTitle, 255);
			if(m_sound->GetNSFCount() > 0) {
				TCHAR chNSFCount[255];
				_stprintf_s(chNSFCount, _T("(%d/%d)"), m_sound->GetNSFCurrent(),
					m_sound->GetNSFCount());
				lstrcat(chTitle, chNSFCount);
			}
			lstrcat(chTitle, _T(" - "));
			lstrcat(chTitle, m_rApp.GetName().c_str());
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->SetPlayOrder(i);
			m_arrayList[nCurPlayTab]->ScrollToItem(i);
		}
		else {
			m_arrayList[nCurPlayTab]->DeleteItem(i);
			m_arrayList[nCurPlayTab]->ResetNumber();
		}

		m_arrayList[nCurPlayTab]->InvalidateRect(NULL, TRUE);
		SetPreviousNextMenuState();

		// 次に開くべきファイルが見つからなかった場合
		if(!bRet) return FALSE;

		return TRUE;
	}

	// 開くべきファイルを探す
	i = m_sound->GetCurFileNum() - 2;
	for(; i >= 0; i--) {
		TCHAR filePath[MAX_PATH];
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, filePath, MAX_PATH);
		TCHAR chNewArtist[255];
		m_arrayList[nCurPlayTab]->GetItemText(i, 3, chNewArtist, 255);
		if(m_menu->IsItemChecked(ID_SAMEARTIST) &&
				(lstrcmp(chArtist, chNewArtist) != 0)) {
			if(i == 0) i = m_arrayList[nCurPlayTab]->GetItemCount() - 1;
			continue;
		}
		m_sound->SetCurFileNum(i+1);
		if(OpenFile(filePath)) {
			TCHAR chTitle[255];
			m_arrayList[nCurPlayTab]->GetItemText(i, 2, chTitle, 255);
			if(m_sound->GetNSFCount() > 0) {
				TCHAR chNSFCount[255];
				_stprintf_s(chNSFCount, _T("(%d/%d)"), m_sound->GetNSFCurrent(),
					m_sound->GetNSFCount());
				lstrcat(chTitle, chNSFCount);
			}
			lstrcat(chTitle, _T(" - "));
			lstrcat(chTitle, m_rApp.GetName().c_str());
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->ScrollToItem(i);
			break;
		}
		else {
			// 開けなかったファイルを削除
			m_arrayList[nCurPlayTab]->DeleteItem(i);
			m_arrayList[nCurPlayTab]->ResetNumber();
		}
	}

	m_arrayList[nCurPlayTab]->InvalidateRect(NULL, TRUE);
	SetPreviousNextMenuState();

	// 開くべきファイルが見つからなかった場合
	if(i < 0) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// ランダムにファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenRandom()
{
	// すでにすべてのファイルを再生済みの場合
	if(m_arrayList[nCurPlayTab]->GetMaxPlayOrder()
			== m_arrayList[nCurPlayTab]->GetItemCount() - 1)
		m_arrayList[nCurPlayTab]->ClearPlayOrder();

	int i = m_sound->GetCurFileNum();
	TCHAR chArtist[255];
	m_arrayList[nCurPlayTab]->GetItemText(i - 1, 3, chArtist, 255);

	// 未再生のファイルを探す
	std::vector<int> list;
	std::vector<int> order = m_arrayList[nCurPlayTab]->GetOrders();
	for(int i = 0; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++) {
		TCHAR chNewArtist[255];
		m_arrayList[nCurPlayTab]->GetItemText(i, 3, chNewArtist, 255);
		if(m_menu->IsItemChecked(ID_SAMEARTIST) &&
				(lstrcmp(chArtist, chNewArtist) != 0))
			continue;
		if(order[i] < 0) list.push_back(i);
	}
	BOOL bRet = FALSE;
	for(int i = 0; i < (int)list.size(); i++) {
		srand(timeGetTime());
		TCHAR szFilePath[MAX_PATH];
		int n = rand() % list.size();
		int nItem = list[n];
		m_arrayList[nCurPlayTab]->GetItemText(nItem, 7, szFilePath, MAX_PATH);
		m_sound->SetCurFileNum(nItem+1);
		bRet = OpenFile(szFilePath);
		if(bRet) {
			TCHAR chTitle[255];
			m_arrayList[nCurPlayTab]->GetItemText(nItem, 2, chTitle, 255);
			if(m_sound->GetNSFCount() > 0) {
				TCHAR chNSFCount[255];
				_stprintf_s(chNSFCount, _T("(%d/%d)"), m_sound->GetNSFCurrent(),
					m_sound->GetNSFCount());
				lstrcat(chTitle, chNSFCount);
			}
			lstrcat(chTitle, _T(" - "));
			lstrcat(chTitle, m_rApp.GetName().c_str());
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->SetPlayOrder(nItem);
			m_arrayList[nCurPlayTab]->ScrollToItem(nItem);
			break;
		}
		else {
			m_arrayList[nCurPlayTab]->DeleteItem(nItem);
			m_arrayList[nCurPlayTab]->ResetNumber();
			list.erase(list.begin() + n);
		}
	}

	m_arrayList[nCurPlayTab]->InvalidateRect(NULL, TRUE);
	SetPreviousNextMenuState();

	// 次に開くべきファイルが見つからなかった場合
	if(!bRet) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// 一時停止
//----------------------------------------------------------------------------
void CMainWnd::Pause()
{
	if(m_sound->ChannelIsStopped() || m_sound->ChannelIsPausing())
		// 停止中か既に一時停止中だった場合は、再生
		Play();
	else if(m_menu->IsItemChecked(ID_QUALITY_WASAPI) &&
			!BASS_WASAPI_IsStarted()) {
		m_sound->ResumeWASAPI();
		m_toolBar->SetPlayingState(TRUE);
		SetTimer(IDT_TIME, 200);
		m_arrayList[nCurPlayTab]->SetPlaying(m_sound->GetCurFileNum() - 1);
	}
	else {
		if(m_menu->IsItemChecked(ID_QUALITY_WASAPI))
			m_sound->PauseWASAPI();
		else m_sound->ChannelPause();
		KillTimer(IDT_TIME);
		m_toolBar->SetPausingState(TRUE);
		m_arrayList[nCurPlayTab]->SetPausing(m_sound->GetCurFileNum() - 1);
	}
}
//----------------------------------------------------------------------------
// 再生
//----------------------------------------------------------------------------
BOOL CMainWnd::Play()
{
	KillTimer(IDT_FADEOUT);
	KillTimer(IDT_FADEOUTNEXT);
	dwFadeoutStartTime = 0;
	m_sound->ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
	if(!m_sound->ChannelPlay() && !m_menu->IsItemChecked(ID_QUALITY_WASAPI)) {
		// 再生に失敗
		m_menu->SetFileLoadState(FALSE);
		KillTimer(IDT_TIME);
		m_timeLabel->SetTime(0, 0);
		m_timeSlider->SetTime(0, 10);
		m_toolBar->SetPlayingState(FALSE);
		return FALSE;
	}
	if(m_menu->IsItemChecked(ID_QUALITY_WASAPI)) m_sound->ResumeWASAPI();
	m_toolBar->SetPlayingState(TRUE);
	SetTimer(IDT_TIME, 200);
	m_arrayList[nCurPlayTab]->SetPlaying(m_sound->GetCurFileNum() - 1);
	return TRUE;
}
//----------------------------------------------------------------------------
// 番号を指定して再生
//----------------------------------------------------------------------------
void CMainWnd::Play(int n)
{
	m_sound->SetCurFileNum(n);
	if(m_menu->IsItemChecked(ID_RANDOM))
		m_arrayList[nCurPlayTab]->FixPlayOrder(n);
	BOOL bRandom = m_menu->IsItemChecked(ID_RANDOM);
	if(bRandom) m_menu->OnRandomMenuSelected();
	m_sound->SetNSFCount(0);
	PlayNext(TRUE, TRUE);
	if(bRandom) {
		m_menu->OnRandomMenuSelected();
		m_arrayList[nCurPlayTab]->SetPlayOrder(n);
	}
}
//----------------------------------------------------------------------------
// 次のファイルを再生
//----------------------------------------------------------------------------
void CMainWnd::PlayNext(BOOL bPlay, BOOL bFadeoutCancel)
{
	// bPlay : かならず再生するかどうか

	if(!bPlay && !bFadeoutCancel && !m_sound->ChannelIsStopped() &&
	   !m_sound->ChannelIsPausing() && dwFadeoutStartTime == 0 &&
	   m_menu->IsItemChecked(ID_FADEOUTNEXT)) {
		dwFadeoutStartTime = timeGetTime();
		SetTimer(IDT_FADEOUTNEXT, 1);
	}
	else {
		KillTimer(IDT_FADEOUT);
		KillTimer(IDT_FADEOUTNEXT);
		dwFadeoutStartTime = 0;
		BOOL bStopped = m_sound->ChannelIsStopped() && !bPlay;
		BOOL bPausing = m_sound->ChannelIsPausing() && !bPlay;
		BOOL bBassCopy = m_menu->IsItemChecked(ID_BASSCOPY);
		BOOL bDrumsCopy = m_menu->IsItemChecked(ID_CYMBALCOPY);

		// 次に再生すべきファイルを探す
		while(1) {
			if(OpenNext()) {
				if(Play()) break;
				else continue;
			}
			else {
				BOOL isLoop = m_sound->IsLoop();
				m_sound->SetLoop(FALSE);
				Stop();
				if(!m_sound->IsLoop()
						&& m_arrayList[nCurPlayTab]->GetItemCount() > 0
						&& (m_menu->IsItemChecked(ID_RANDOM)
						|| m_sound->GetCurFileNum() > 1)) {
					m_sound->SetCurFileNum(0);
					m_arrayList[nCurPlayTab]->ClearPlayOrder();
					OpenNext();
				}
				m_sound->SetLoop(isLoop);
				if(m_menu->IsItemChecked(ID_ALOOP)) Play();
				break;
			}
		}

		m_sound->ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
		if(m_sound->ChannelIsActive()) {
			m_menu->CheckItem(ID_BASSCOPY, bBassCopy ?
											MF_CHECKED : MF_UNCHECKED);
			m_menu->CheckItem(ID_CYMBALCOPY, bDrumsCopy ?
											MF_CHECKED : MF_UNCHECKED);
			if(bPausing) Pause();
			else if(bStopped || !m_menu->IsItemChecked(ID_CONTINUE)) {
				BOOL isLoop = m_sound->IsLoop();
				m_sound->SetLoop(TRUE);
				Stop();
				m_sound->SetLoop(isLoop);
			}
		}
	}
}
//----------------------------------------------------------------------------
// 前のファイルを再生
//----------------------------------------------------------------------------
void CMainWnd::PlayPrevious()
{
	BOOL bStopped = m_sound->ChannelIsStopped();
	BOOL bPausing = m_sound->ChannelIsPausing();

	// 再生すべきファイルを探す
	BOOL bEnd = FALSE; // 後ろから検索しなおしたかどうか
	while(1) {
		if(OpenPrevious()) {
			if(Play()) break;
			else continue;
		}
		else {
			if(m_menu->IsItemChecked(ID_ALOOP) && !bEnd) {
				bEnd = TRUE;
				m_sound->SetCurFileNum(
					m_arrayList[nCurPlayTab]->GetItemCount()+1);
				continue;
			}
			Stop();
			Play();
			break;
		}
	}

	if(m_sound->ChannelIsActive()) {
		if(bPausing) Pause();
		else if(bStopped) {
			BOOL isLoop = m_sound->IsLoop();
			m_sound->SetLoop(TRUE);
			Stop();
			m_sound->SetLoop(isLoop);
		}
	}
}
//----------------------------------------------------------------------------
// 全てのコントロールの位置を再設定
//----------------------------------------------------------------------------
void CMainWnd::ResetAllControlPos()
{
	if(IsZoomed(m_hWnd)) {
		if(m_menu->IsItemChecked(ID_PLAYLIST)) {
			for(int i = 0; i < (int)m_arrayList.size(); i++)
				m_arrayList[i]->InitSize();
		}
	}
	m_explorerBar->ResetPos();
	m_explorer->ResetPos();
	m_videoScreen->ResetPos(); m_videoScreen->ResetWidth();
	m_timeSlider->ResetPos(); m_timeSlider->ResetSize();
	m_divider2->ResetPos();
	m_speedLabel->ResetPos(); m_speedSlider->ResetPos();
	m_speedSlider->ResetSize();
	m_freqLabel->ResetPos(); m_freqSlider->ResetPos();
	m_freqSlider->ResetSize();
	m_pitchLabel->ResetPos(); m_pitchSlider->ResetPos();
	m_pitchSlider->ResetSize();
	m_divider3->ResetPos(); m_divider3->ResetSize();
	m_volumeLabel->ResetPos(); m_volumeSlider->ResetPos();
	m_volumeSlider->ResetSize();
	m_panLabel->ResetPos(); m_panSlider->ResetPos();
	m_panSlider->ResetSize();
	m_divider4->ResetPos(); m_divider4->ResetSize();
	m_eq20Label->ResetPos(); m_eq20Slider->ResetPos();
	m_eq20Slider->ResetSize();
	m_eq25Label->ResetPos(); m_eq25Slider->ResetPos();
	m_eq25Slider->ResetSize();
	m_eq31_5Label->ResetPos(); m_eq31_5Slider->ResetPos();
	m_eq31_5Slider->ResetSize();
	m_eq40Label->ResetPos(); m_eq40Slider->ResetPos();
	m_eq40Slider->ResetSize();
	m_eq50Label->ResetPos(); m_eq50Slider->ResetPos();
	m_eq50Slider->ResetSize();
	m_eq63Label->ResetPos(); m_eq63Slider->ResetPos();
	m_eq63Slider->ResetSize();
	m_eq80Label->ResetPos(); m_eq80Slider->ResetPos();
	m_eq80Slider->ResetSize();
	m_eq100Label->ResetPos(); m_eq100Slider->ResetPos();
	m_eq100Slider->ResetSize();
	m_eq125Label->ResetPos(); m_eq125Slider->ResetPos();
	m_eq125Slider->ResetSize();
	m_eq160Label->ResetPos(); m_eq160Slider->ResetPos();
	m_eq160Slider->ResetSize();
	m_eq200Label->ResetPos(); m_eq200Slider->ResetPos();
	m_eq200Slider->ResetSize();
	m_eq250Label->ResetPos(); m_eq250Slider->ResetPos();
	m_eq250Slider->ResetSize();
	m_eq315Label->ResetPos(); m_eq315Slider->ResetPos();
	m_eq315Slider->ResetSize();
	m_eq400Label->ResetPos(); m_eq400Slider->ResetPos();
	m_eq400Slider->ResetSize();
	m_eq500Label->ResetPos(); m_eq500Slider->ResetPos();
	m_eq500Slider->ResetSize();
	m_eq630Label->ResetPos(); m_eq630Slider->ResetPos();
	m_eq630Slider->ResetSize();
	m_eq800Label->ResetPos(); m_eq800Slider->ResetPos();
	m_eq800Slider->ResetSize();
	m_eq1kLabel->ResetPos(); m_eq1kSlider->ResetPos();
	m_eq1kSlider->ResetSize();
	m_eq1_25kLabel->ResetPos(); m_eq1_25kSlider->ResetPos();
	m_eq1_25kSlider->ResetSize();
	m_eq1_6kLabel->ResetPos(); m_eq1_6kSlider->ResetPos();
	m_eq1_6kSlider->ResetSize();
	m_eq2kLabel->ResetPos(); m_eq2kSlider->ResetPos();
	m_eq2kSlider->ResetSize();
	m_eq2_5kLabel->ResetPos(); m_eq2_5kSlider->ResetPos();
	m_eq2_5kSlider->ResetSize();
	m_eq3_15kLabel->ResetPos(); m_eq3_15kSlider->ResetPos();
	m_eq3_15kSlider->ResetSize();
	m_eq4kLabel->ResetPos(); m_eq4kSlider->ResetPos();
	m_eq4kSlider->ResetSize();
	m_eq5kLabel->ResetPos(); m_eq5kSlider->ResetPos();
	m_eq5kSlider->ResetSize();
	m_eq6_3kLabel->ResetPos(); m_eq6_3kSlider->ResetPos();
	m_eq6_3kSlider->ResetSize();
	m_eq8kLabel->ResetPos(); m_eq8kSlider->ResetPos();
	m_eq8kSlider->ResetSize();
	m_eq10kLabel->ResetPos(); m_eq10kSlider->ResetPos();
	m_eq10kSlider->ResetSize();
	m_eq12_5kLabel->ResetPos(); m_eq12_5kSlider->ResetPos();
	m_eq12_5kSlider->ResetSize();
	m_eq16kLabel->ResetPos(); m_eq16kSlider->ResetPos();
	m_eq16kSlider->ResetSize();
	m_eq20kLabel->ResetPos(); m_eq20kSlider->ResetPos();
	m_eq20kSlider->ResetSize();
	m_divider5->ResetPos(); m_divider5->ResetSize();
	m_tab->ResetPos(); m_tab->ResetWidth();
	for(int i = 0;i < (int)m_arrayList.size(); i++) {
		m_arrayList[i]->ResetPos();
		m_arrayList[i]->ResetWidth();
	}
	InvalidateRect(NULL, TRUE);
}
//----------------------------------------------------------------------------
// 現在読み込んでいるファイル番号の再設定
//----------------------------------------------------------------------------
void CMainWnd::ResetCurFileNum()
{
	for(int i = 0; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++) {
		TCHAR filePath[MAX_PATH];
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, filePath, MAX_PATH);
		tstring strFilePath = filePath;
		if(filePath == m_sound->GetCurFileName())
			m_sound->SetCurFileNum(i+1);
	}
}
//----------------------------------------------------------------------------
// 再生周波数をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetFreq()
{
	double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
	m_freqLabel->SetFreq(100.0);
	m_freqSlider->SetThumbPos((int)(100 * dCalc), TRUE);
	SetFreq(100.0);
}
//----------------------------------------------------------------------------
// 音程をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetPitch()
{
	m_pitchLabel->SetPitch(0.0);
	m_pitchSlider->SetThumbPos(0, TRUE);
	SetPitch(0.0);
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CMainWnd::ResetSize()
{
	BOOL bZoomed = FALSE;
	if(IsZoomed(m_hWnd)) {
		bZoomed = TRUE;
		Show(SW_NORMAL);
	}
	POINT pt;
	int nSelect = m_tab->GetCurrentFocus();
	if(m_menu->IsItemChecked(ID_PLAYLIST)) {
		if(m_menu->IsItemChecked(ID_TAB)) {
			pt.y = m_tab->GetTop();
			ScreenToClient(m_hWnd, &pt);
			int nHeight = pt.y + m_tab->GetHeight();
			SetClientSize(GetClientWidth(), nHeight, TRUE);
			m_tab->ResetPos(); m_tab->ResetSize();
			for(int i = 0;i < (int)m_arrayList.size(); i++) {
				m_arrayList[i]->ResetPos();
				m_arrayList[i]->ResetSize();
			}
		}
		else {
			pt.y = m_arrayList[nSelect]->GetTop();
			ScreenToClient(m_hWnd, &pt);
			int nHeight = pt.y + m_arrayList[nSelect]->GetHeight();
			SetClientSize(GetClientWidth(), nHeight, TRUE);
		}
	}
	else if(m_menu->IsItemChecked(ID_EQ)) {
		pt.y = m_eq20kLabel->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nLabelBottom = pt.y + m_eq20kLabel->GetHeight();
		pt.y = m_eq20kSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nSliderBottom = pt.y + m_eq20kSlider->GetHeight();
		int nBigger = nLabelBottom > nSliderBottom
			? nLabelBottom : nSliderBottom;
		SetClientSize(GetClientWidth(), nBigger + controlOffset, TRUE);
	}
	else if(m_menu->IsItemChecked(ID_PAN)) {
		pt.y = m_panLabel->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nPanLabelBottom = pt.y + m_panLabel->GetHeight();
		pt.y = m_panSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nPanSliderBottom = pt.y + m_panSlider->GetHeight();
		int nBigger = nPanLabelBottom > nPanSliderBottom ? nPanLabelBottom
			: nPanSliderBottom;
		SetClientSize(GetClientWidth(), nBigger + controlOffset, TRUE);
	}
	else if(m_menu->IsItemChecked(ID_VOLUME)) {
		pt.y = m_volumeLabel->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nVolumeLabelBottom = pt.y + m_volumeLabel->GetHeight();
		pt.y = m_volumeSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nVolumeSliderBottom = pt.y + m_volumeSlider->GetHeight();
		int nBigger = nVolumeLabelBottom > nVolumeSliderBottom ? nVolumeLabelBottom
			: nVolumeSliderBottom;
		SetClientSize(GetClientWidth(), nBigger + controlOffset, TRUE);
	}
	else if(m_menu->IsItemChecked(ID_PITCH)) {
		pt.y = m_pitchLabel->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nPitchLabelBottom = pt.y + m_pitchLabel->GetHeight();
		pt.y = m_pitchSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nPitchSliderBottom = pt.y + m_pitchSlider->GetHeight();
		int nBigger = nPitchLabelBottom > nPitchSliderBottom
			? nPitchLabelBottom : nPitchSliderBottom;
		SetClientSize(GetClientWidth(), nBigger + controlOffset, TRUE);
	}
	else if(m_menu->IsItemChecked(ID_FREQ)) {
		pt.y = m_freqLabel->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nFreqLabelBottom = pt.y + m_freqLabel->GetHeight();
		pt.y = m_freqSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nFreqSliderBottom = pt.y + m_freqSlider->GetHeight();
		int nBigger = nFreqLabelBottom > nFreqSliderBottom
			? nFreqLabelBottom : nFreqSliderBottom;
		SetClientSize(GetClientWidth(), nBigger + controlOffset, TRUE);
	}
	else if(m_menu->IsItemChecked(ID_SPEED)) {
		pt.y = m_speedLabel->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nSpeedLabelBottom = pt.y + m_speedLabel->GetHeight();
		pt.y = m_speedSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nSpeedSliderBottom = pt.y + m_speedSlider->GetHeight();
		int nBigger = nSpeedLabelBottom > nSpeedSliderBottom
			? nSpeedLabelBottom : nSpeedSliderBottom;
		SetClientSize(GetClientWidth(), nBigger + controlOffset, TRUE);
	}
	else if(m_menu->IsItemChecked(ID_TIMESLIDER)) {
		pt.y = m_timeSlider->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nTimeSliderBottom = pt.y + m_timeSlider->GetHeight();
		SetClientSize(GetClientWidth(), nTimeSliderBottom + controlOffset,
			TRUE);
	}
	else if(m_menu->IsItemChecked(ID_VIDEOSCREEN)) {
		pt.y = m_videoScreen->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nVideoScreenBottom = pt.y + m_videoScreen->GetHeight();
		SetClientSize(GetClientWidth(), nVideoScreenBottom,
			TRUE);
	}
	else {
		pt.y = m_toolBar->GetTop();
		ScreenToClient(m_hWnd, &pt);
		SetClientSize(GetClientWidth(), pt.y + m_toolBar->GetHeight(), TRUE);
	}
	if(bZoomed && GetHeight() > GetSystemMetrics(SM_CYVIRTUALSCREEN)) {
		if(m_menu->IsItemChecked(ID_PLAYLIST)) {
			for(int i = 0; i < (int)m_arrayList.size(); i++)
				m_arrayList[i]->InitSize();
		}
		pt.y = m_arrayList[nSelect]->GetTop();
		ScreenToClient(m_hWnd, &pt);
		int nHeight = pt.y + m_arrayList[nSelect]->GetHeight();
		if(nHeight > GetSystemMetrics(SM_CYVIRTUALSCREEN)) {
			if(m_menu->IsItemChecked(ID_VIDEOSCREEN)) {
				int nVideoScreenHeight = m_videoScreen->GetHeight() -
					(nHeight - GetSystemMetrics(SM_CYVIRTUALSCREEN));
				if(nVideoScreenHeight <= 0) nVideoScreenHeight = 1;
				m_videoScreen->SetSize(m_videoScreen->GetWidth(),
					nVideoScreenHeight);
			}
		}
	}
	if(bZoomed) Show(SW_MAXIMIZE);
	m_arrayList[nSelect]->InvalidateRect(NULL, TRUE);
	InvalidateRect(NULL, TRUE);
}
//----------------------------------------------------------------------------
// 再生速度をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetSpeed()
{
	double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
	m_speedLabel->SetSpeed(100.0);
	m_speedSlider->SetThumbPos((int)(100 * dCalc), TRUE);
	SetSpeed(100.0);
}
//----------------------------------------------------------------------------
// 音量をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetVolume()
{
	m_volumeLabel->SetVolume(100.0);
	m_volumeSlider->SetThumbPos(1000, TRUE);
	SetVolume(100.0);
}
//----------------------------------------------------------------------------
// 巻き戻し
//----------------------------------------------------------------------------
void CMainWnd::Rewind()
{
	double dPos = m_sound->ChannelGetSecondsPosition(), dDifference = 1.0;
	dDifference *= m_sound->GetTempo() / 100.0;
	dDifference *= m_sound->GetSampleRate() / 100.0;
	if(dDifference < 1.0) dDifference = 1.0;
	SetTime(m_sound->ChannelSeconds2Bytes(dPos - dDifference));
}
//----------------------------------------------------------------------------
// 指定した秒数戻る
//----------------------------------------------------------------------------
void CMainWnd::ReturnSeconds(int seconds)
{
	double pos = m_sound->ChannelGetSecondsPosition();
	pos -= seconds;
	SetSeconds(pos);
}
//----------------------------------------------------------------------------
// プリセットの保存
//----------------------------------------------------------------------------
void CMainWnd::SavePreset(PCTSTR pName)
{
	tstring initFilePath = m_rApp.GetFilePath() + _T("Setting.ini");

	int i = 1;
	TCHAR section[255];
	TCHAR buf[255];
	BOOL bOld = FALSE;
	while(TRUE) {
		_stprintf_s(section, _T("Preset%d"), i);
		GetPrivateProfileString(section, _T("Name"), _T(""), buf, 255,
			initFilePath.c_str());
		if(_tcsicmp(buf, _T("")) == 0) break;
		else if(_tcsicmp(buf, pName) == 0) {
			bOld = TRUE;
			break;
		}
		i++;
	}

	if(!bOld) {
		if(i == 1) m_menu->GetPresetMenu().AppendSeparator();
		m_menu->GetPresetMenu().Append(MFS_ENABLED, ID_PRESET + i, pName);
	}

	// プリセット名の設定
	WritePrivateProfileString(section, _T("Name"), pName,
		initFilePath.c_str());

	_stprintf_s(buf, _T("%4.2f"), (double)(m_speedSlider->GetThumbPos()
		/ pow(10.0, m_speedLabel->GetDecimalDigit())));
	WritePrivateProfileString(section, _T("Speed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%4.2f"), (double)(m_freqSlider->GetThumbPos()
		/ pow(10.0, m_freqLabel->GetDecimalDigit())));
	WritePrivateProfileString(section, _T("Frequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%2.2f"), (double)(m_pitchSlider->GetThumbPos()
		/ pow(10.0, m_pitchLabel->GetDecimalDigit())));
	WritePrivateProfileString(section, _T("Pitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_volumeSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("Volume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_panSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("Pan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq20Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ20"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq25Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ25"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq31_5Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ31.5"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq40Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ40"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq50Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ50"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq63Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ63"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq80Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ80"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq100Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ100"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq125Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ125"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq160Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ160"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq200Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ200"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq250Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ250"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq315Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ315"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq400Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ400"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq500Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ500"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq630Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ630"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq800Slider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ800"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ1K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1_25kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ1.25K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1_6kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ1.6K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq2kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ2K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq2_5kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ2.5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq3_15kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ3.15K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq4kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ4K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq5kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq6_3kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ6.3K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq8kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ8K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq10kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ10K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq12_5kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ12.5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq16kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ16K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq20kSlider->GetThumbPos());
	WritePrivateProfileString(section, _T("EQ20K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERB_DEFAULT));
	WritePrivateProfileString(section, _T("ReverbDefault"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERB_CUSTOMIZE));
	WritePrivateProfileString(section, _T("ReverbCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_REVERB bdr;
	BOOL bReverb = m_sound->GetReverb(&bdr);
	int nGain = bReverb ? (int)bdr.fInGain : 0;
	TCHAR chGain[255], chRevMix[255], chRevTime[255], chHigh[255];
	_stprintf_s(chGain, _T("%d"), nGain);
	WritePrivateProfileString(section, _T("ReverbCustomize_Gain"), chGain, 
		initFilePath.c_str());
	int nRevMix = bReverb ? (int)bdr.fReverbMix : 0;
	_stprintf_s(chRevMix, _T("%d"), nRevMix);
	WritePrivateProfileString(section, _T("ReverbCustomize_RevMix"), chRevMix, 
		initFilePath.c_str());
	double dRevTime = bReverb ? bdr.fReverbTime : 1000.0;
	_stprintf_s(chRevTime, _T("%4.3f"), dRevTime);
	WritePrivateProfileString(section, _T("ReverbCustomize_RevTime"), chRevTime,
		initFilePath.c_str());
	double dHigh = bReverb ? bdr.fHighFreqRTRatio : 0.001;
	_stprintf_s(chHigh, _T("%4.3f"), dHigh);
	WritePrivateProfileString(section, _T("ReverbCustomize_High"), chHigh, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_DEFAULT));
	WritePrivateProfileString(section, _T("3DReverbDefault"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PADDEDCELL));
	WritePrivateProfileString(section, _T("3DReverbPaddedCell"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_ROOM));
	WritePrivateProfileString(section, _T("3DReverbRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_BATHROOM));
	WritePrivateProfileString(section, _T("3DReverbBathRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_LIVINGROOM));
	WritePrivateProfileString(section, _T("3DReverbLivingRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_STONEROOM));
	WritePrivateProfileString(section, _T("3DReverbStoneRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_AUDITORIUM));
	WritePrivateProfileString(section, _T("3DReverbAuditorium"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CONCERTHALL));
	WritePrivateProfileString(section, _T("3DReverbConcertHall"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CAVE));
	WritePrivateProfileString(section, _T("3DReverbCave"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_ARENA));
	WritePrivateProfileString(section, _T("3DReverbArena"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_HANGAR));
	WritePrivateProfileString(section, _T("3DReverbHangar"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_3DREVERB_CARPETEDHALLWAY));
	WritePrivateProfileString(section, _T("3DReverbCarpetedHallway"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_HALLWAY));
	WritePrivateProfileString(section, _T("3DReverbHallway"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_STONECORRIDOR));
	WritePrivateProfileString(section, _T("3DReverbStoneCorridor"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_ALLEY));
	WritePrivateProfileString(section, _T("3DReverbAlley"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_FOREST));
	WritePrivateProfileString(section, _T("3DReverbForest"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CITY));
	WritePrivateProfileString(section, _T("3DReverbCity"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_MOUNTAINS));
	WritePrivateProfileString(section, _T("3DReverbMountains"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_QUARRY));
	WritePrivateProfileString(section, _T("3DReverbQuarry"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PLAIN));
	WritePrivateProfileString(section, _T("3DReverbPlain"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PARKINGLOT));
	WritePrivateProfileString(section, _T("3DReverbParkingLot"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_SEWERPIPE));
	WritePrivateProfileString(section, _T("3DReverbSewerPipe"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_UNDERWATER));
	WritePrivateProfileString(section, _T("3DReverbUnderWater"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_SMALLROOM));
	WritePrivateProfileString(section, _T("3DReverbSmallRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_MEDIUMROOM));
	WritePrivateProfileString(section, _T("3DReverbMediumRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_LARGEROOM));
	WritePrivateProfileString(section, _T("3DReverbLargeRoom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_MEDIUMHALL));
	WritePrivateProfileString(section, _T("3DReverbMediumHall"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_LARGEHALL));
	WritePrivateProfileString(section, _T("3DReverbLargeHall"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PLATE));
	WritePrivateProfileString(section, _T("3DReverbPlate"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CUSTOMIZE));
	WritePrivateProfileString(section, _T("3DReverbCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_I3DL2REVERB bdir;
	BOOL b3DReverb = m_sound->Get3DReverb(&bdir);

	int lRoom = b3DReverb ? bdir.lRoom : -1000;
	int lRoomHF = b3DReverb ? bdir.lRoomHF : -100;
	float flRoomRolloffFactor = b3DReverb ? bdir.flRoomRolloffFactor : 0.0f;
	float flDecayTime = b3DReverb ? bdir.flDecayTime : 1.49f;
	float flDecayHFRatio = b3DReverb ? bdir.flDecayHFRatio : 0.83f;
	int lReflections = b3DReverb ? bdir.lReflections : -2602;
	float flReflectionsDelay = b3DReverb ? bdir.flReflectionsDelay : 0.007f;
	int lReverb = b3DReverb ? bdir.lReverb : 200;
	float flReverbDelay = b3DReverb ? bdir.flReverbDelay : 0.011f;
	float flDiffusion = b3DReverb ? bdir.flDiffusion : 100.0f;
	float flDensity = b3DReverb ? bdir.flDensity : 100.0f;
	float flHFReference = b3DReverb ? bdir.flHFReference : 5000.0f;

	TCHAR chRoom[255], chRoomHF[255], chRoomRolloffFactor[255],
			chDecayTime[255], chDecayHFRatio[255], chReflections[255],
			chReflectionsDelay[255], chReverb[255], chReverbDelay[255],
			chDiffusion[255], chDensity[255], chHFReference[255];

	_stprintf_s(chRoom, _T("%d"), lRoom);
	WritePrivateProfileString(section, _T("3DReverbCustomize_Room"), chRoom, 
		initFilePath.c_str());
	_stprintf_s(chRoomHF, _T("%d"), lRoomHF);
	WritePrivateProfileString(section, _T("3DReverbCustomize_RoomHF"), chRoomHF,
		initFilePath.c_str());
	_stprintf_s(chRoomRolloffFactor, _T("%4.3f"), flRoomRolloffFactor);
	WritePrivateProfileString(section,
		_T("3DReverbCustomize_RoomRolloffFactor"),
		chRoomRolloffFactor, initFilePath.c_str());
	_stprintf_s(chDecayTime, _T("%4.3f"), flDecayTime);
	WritePrivateProfileString(section, _T("3DReverbCustomize_DecayTime"),
		chDecayTime, initFilePath.c_str());
	_stprintf_s(chDecayHFRatio, _T("%4.3f"), flDecayHFRatio);
	WritePrivateProfileString(section, _T("3DReverbCustomize_DecayHFRatio"),
		chDecayHFRatio, initFilePath.c_str());
	_stprintf_s(chReflections, _T("%d"), lReflections);
	WritePrivateProfileString(section, _T("3DReverbCustomize_Reflections"),
		chReflections, initFilePath.c_str());
	_stprintf_s(chReflectionsDelay, _T("%4.3f"), flReflectionsDelay);
	WritePrivateProfileString(section, _T("3DReverbCustomize_ReflectionsDelay"),
		chReflectionsDelay, initFilePath.c_str());
	_stprintf_s(chReverb, _T("%d"), lReverb);
	WritePrivateProfileString(section, _T("3DReverbCustomize_Reverb"), chReverb,
		initFilePath.c_str());
	_stprintf_s(chReverbDelay, _T("%4.3f"), flReverbDelay);
	WritePrivateProfileString(section, _T("3DReverbCustomize_ReverbDelay"),
		chReverbDelay, initFilePath.c_str());
	_stprintf_s(chDiffusion, _T("%4.3f"), flDiffusion);
	WritePrivateProfileString(section, _T("3DReverbCustomize_Diffusion"),
		chDiffusion, initFilePath.c_str());
	_stprintf_s(chDensity, _T("%4.3f"), flDensity);
	WritePrivateProfileString(section, _T("3DReverbCustomize_Density"),
		chDensity, initFilePath.c_str());
	_stprintf_s(chHFReference, _T("%4.3f"), flHFReference);
	WritePrivateProfileString(section, _T("3DReverbCustomize_HFReference"),
		chHFReference, initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_DEFAULT));
	WritePrivateProfileString(section, _T("DelayDefault"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_SHORT));
	WritePrivateProfileString(section, _T("DelayShort"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_MEDIUM));
	WritePrivateProfileString(section, _T("DelayMedium"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_LONG));
	WritePrivateProfileString(section, _T("DelayLong"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOSHORT));
	WritePrivateProfileString(section, _T("DelayStereoShort"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOMEDIUM));
	WritePrivateProfileString(section, _T("DelayStereoMedium"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOLONG));
	WritePrivateProfileString(section, _T("DelayStereoLong"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_MOUNTAIN));
	WritePrivateProfileString(section, _T("DelayMountain"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_BIG));
	WritePrivateProfileString(section, _T("DelayBig"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOBIG));
	WritePrivateProfileString(section, _T("DelayStereoBig"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_DOUBLING));
	WritePrivateProfileString(section, _T("DelayDoubling"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_DOUBLEKICK));
	WritePrivateProfileString(section, _T("DelayDoubleKick"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_CUSTOMIZE));
	WritePrivateProfileString(section, _T("DelayCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_ECHO bde;
	BOOL bDelay = m_sound->GetDelay(&bde);
	float fWetDryMix = bDelay ? bde.fWetDryMix : 8.0f;
	float fFeedback = bDelay ? bde.fFeedback : 50.0f;
	float fLeftDelay = bDelay ? bde.fLeftDelay : 600.0f;
	float fRightDelay = bDelay ? bde.fRightDelay : 300.0f;
	int lPanDelay = bDelay ? bde.lPanDelay : 1;
	TCHAR chWetDryMix[255], chFeedback[255], chLeftDelay[255],
		  chRightDelay[255], chPanDelay[255];
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chLeftDelay, _T("%4.3f"), fLeftDelay);
	_stprintf_s(chRightDelay, _T("%4.3f"), fRightDelay);
	_stprintf_s(chPanDelay, _T("%d"), lPanDelay);
	WritePrivateProfileString(section, _T("DelayCustomize_WetDryMix"),
		chWetDryMix, initFilePath.c_str());
	WritePrivateProfileString(section, _T("DelayCustomize_Feedback"),
		chFeedback, initFilePath.c_str());
	WritePrivateProfileString(section, _T("DelayCustomize_LeftDelay"),
		chLeftDelay, initFilePath.c_str());
	WritePrivateProfileString(section, _T("DelayCustomize_RightDelay"),
		chRightDelay, initFilePath.c_str());
	WritePrivateProfileString(section, _T("DelayCustomize_PanDelay"),
		chPanDelay, initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CHORUS_DEFAULT));
	WritePrivateProfileString(section, _T("ChorusDefault"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CHORUS_CUSTOMIZE));
	WritePrivateProfileString(section, _T("ChorusCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_CHORUS bdc;
	BOOL bChorus = m_sound->GetChorus(&bdc);
	fWetDryMix = bChorus ? bdc.fWetDryMix : 50.0f;
	float fDepth = bChorus ? bdc.fDepth : 10.0f;
	fFeedback = bChorus ? bdc.fFeedback : 25.0f;
	float fFrequency = bChorus ? bdc.fFrequency : 1.1f;
	int lWaveForm = bChorus ? bdc.lWaveform : 1;
	float fDelay = bChorus ? bdc.fDelay : 16.0f;
	TCHAR chDepth[255], chFrequency[255], chWaveForm[255], chDelay[255];
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chDepth, _T("%4.3f"), fDepth);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chFrequency, _T("%4.3f"), fFrequency);
	_stprintf_s(chWaveForm, _T("%d"), lWaveForm);
	_stprintf_s(chDelay, _T("%4.3f"), fDelay);
	WritePrivateProfileString(section, _T("ChorusCustomize_WetDryMix"),
		chWetDryMix, initFilePath.c_str());
	WritePrivateProfileString(section, _T("ChorusCustomize_Depth"),
		chDepth, initFilePath.c_str());
	WritePrivateProfileString(section, _T("ChorusCustomize_Feedback"),
		chFeedback, initFilePath.c_str());
	WritePrivateProfileString(section, _T("ChorusCustomize_Frequency"),
		chFrequency, initFilePath.c_str());
	WritePrivateProfileString(section, _T("ChorusCustomize_Waveform"),
		chWaveForm, initFilePath.c_str());
	WritePrivateProfileString(section, _T("ChorusCustomize_Delay"),
		chDelay, initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_COMPRESSOR_DEFAULT));
	WritePrivateProfileString(section, _T("CompressorDefault"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_COMPRESSOR_CUSTOMIZE));
	WritePrivateProfileString(section, _T("CompressorCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_COMPRESSOR bdcmp;
	BOOL bCompressor = m_sound->GetCompressor(&bdcmp);
	float fGain = bCompressor ? bdcmp.fGain : 0.0f;
	float fAttack = bCompressor ? bdcmp.fAttack : 10.0f;
	float fRelease = bCompressor ? bdcmp.fRelease : 200.0f;
	float fThreshold = bCompressor ? bdcmp.fThreshold : -20.0f;
	float fRatio = bCompressor ? bdcmp.fRatio : 3.0f;
	float fPredelay = bCompressor ? bdcmp.fPredelay : 4.0f;
	TCHAR chAttack[255], chRelease[255], chThreshold[255],
		  chRatio[255], chPredelay[255];
	_stprintf_s(chGain, _T("%4.3f"), fGain);
	_stprintf_s(chAttack, _T("%4.3f"), fAttack);
	_stprintf_s(chRelease, _T("%4.3f"), fRelease);
	_stprintf_s(chThreshold, _T("%4.3f"), fThreshold);
	_stprintf_s(chRatio, _T("%4.3f"), fRatio);
	_stprintf_s(chPredelay, _T("%4.3f"), fPredelay);
	WritePrivateProfileString(section, _T("CompressorCustomize_Gain"),
		chGain, initFilePath.c_str());
	WritePrivateProfileString(section, _T("CompressorCustomize_Attack"),
		chAttack, initFilePath.c_str());
	WritePrivateProfileString(section, _T("CompressorCustomize_Release"),
		chRelease, initFilePath.c_str());
	WritePrivateProfileString(section, _T("CompressorCustomize_Threshold"),
		chThreshold, initFilePath.c_str());
	WritePrivateProfileString(section, _T("CompressorCustomize_Ratio"),
		chRatio, initFilePath.c_str());
	WritePrivateProfileString(section, _T("CompressorCustomize_Predelay"),
		chPredelay, initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FLANGER_DEFAULT));
	WritePrivateProfileString(section, _T("FlangerDefault"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FLANGER_CUSTOMIZE));
	WritePrivateProfileString(section, _T("FlangerCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_FLANGER bdf;
	BOOL bFlanger = m_sound->GetFlanger(&bdf);
	fWetDryMix = bFlanger ? bdf.fWetDryMix : 50.0f;
	fDepth = bFlanger ? bdf.fDepth : 100.0f;
	fFeedback = bFlanger ? bdf.fFeedback : -50.0f;
	fFrequency = bFlanger ? bdf.fFrequency : 0.25f;
	lWaveForm = bFlanger ? bdf.lWaveform : 1;
	fDelay = bFlanger ? bdf.fDelay : 2.0f;

	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chDepth, _T("%4.3f"), fDepth);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chFrequency, _T("%4.3f"), fFrequency);
	_stprintf_s(chWaveForm, _T("%d"), lWaveForm);
	_stprintf_s(chDelay, _T("%4.3f"), fDelay);
	WritePrivateProfileString(section, _T("FlangerCustomize_WetDryMix"),
		chWetDryMix, initFilePath.c_str());
	WritePrivateProfileString(section, _T("FlangerCustomize_Depth"),
		chDepth, initFilePath.c_str());
	WritePrivateProfileString(section, _T("FlangerCustomize_Feedback"),
		chFeedback, initFilePath.c_str());
	WritePrivateProfileString(section, _T("FlangerCustomize_Frequency"),
		chFrequency, initFilePath.c_str());
	WritePrivateProfileString(section, _T("FlangerCustomize_Waveform"),
		chWaveForm, initFilePath.c_str());
	WritePrivateProfileString(section, _T("FlangerCustomize_Delay"),
		chDelay, initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_GARGLE_DEFAULT));
	WritePrivateProfileString(section, _T("GargleDefault"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_GARGLE_CUSTOMIZE));
	WritePrivateProfileString(section, _T("GargleCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_GARGLE bdg;
	BOOL bGargle = m_sound->GetGargle(&bdg);
	int nRateHz = bGargle ? bdg.dwRateHz : 20;
	int nWaveShape = bGargle ? bdg.dwWaveShape : 0;
	TCHAR chRateHz[255], chWaveShape[255];
	_stprintf_s(chRateHz, _T("%d"), nRateHz);
	_stprintf_s(chWaveShape, _T("%d"), nWaveShape);
	WritePrivateProfileString(section, _T("GargleCustomize_RateHz"),
		chRateHz, initFilePath.c_str());
	WritePrivateProfileString(section, _T("GargleCustomize_WaveShape"),
		chWaveShape, initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DISTORTION_DEFAULT));
	WritePrivateProfileString(section, _T("DistortionDefault"), buf, 
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DISTORTION_CUSTOMIZE));
	WritePrivateProfileString(section, _T("DistortionCustomize"), buf, 
		initFilePath.c_str());
	BASS_DX8_DISTORTION bdd;
	BOOL bDistortion = m_sound->GetDistortion(&bdd);
	fGain = bDistortion ? bdd.fGain : -18.0f;
	float fEdge = bDistortion ? bdd.fEdge : 15.0f;
	float fPostEQCenterFrequency =
		bDistortion ? bdd.fPostEQCenterFrequency : 2400.0f;
	float fPostEQBandwidth = bDistortion ? bdd.fPostEQBandwidth : 2400.0f;
	float fPreLowpassCutoff = bDistortion ? bdd.fPreLowpassCutoff : 8000.0f;
	TCHAR chEdge[255], chPostEQCenterFrequency[255],
		  chPostEQBandwidth[255], chPreLowpassCutoff[255];
	_stprintf_s(chGain, _T("%4.3f"), fGain);
	_stprintf_s(chEdge, _T("%4.3f"), fEdge);
	_stprintf_s(chPostEQCenterFrequency, _T("%4.3f"), fPostEQCenterFrequency);
	_stprintf_s(chPostEQBandwidth, _T("%4.3f"), fPostEQBandwidth);
	_stprintf_s(chPreLowpassCutoff, _T("%4.3f"), fPreLowpassCutoff);
	WritePrivateProfileString(section, _T("DistortionCustomize_Gain"),
		chGain, initFilePath.c_str());
	WritePrivateProfileString(section, _T("DistortionCustomize_Edge"),
		chEdge, initFilePath.c_str());
	WritePrivateProfileString(section,
		_T("DistortionCustomize_PostEQCenterFrequency"),
		chPostEQCenterFrequency, initFilePath.c_str());
	WritePrivateProfileString(section,
		_T("DistortionCustomize_PostEQBandwidth"), chPostEQBandwidth,
		initFilePath.c_str());
	WritePrivateProfileString(section,
		_T("DistortionCustomize_PreLowpassCutoff"), chPreLowpassCutoff,
		initFilePath.c_str());

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_NORMALIZE));
	WritePrivateProfileString(section, _T("Normalize"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_VOCALCANCEL));
	WritePrivateProfileString(section, _T("VocalCancel"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERSE));
	WritePrivateProfileString(section, _T("Reverse"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECORD));
	WritePrivateProfileString(section, _T("Record"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_LOWBATTERY));
	WritePrivateProfileString(section, _T("LowBattery"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_NOSENSE));
	WritePrivateProfileString(section, _T("NoSense"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_BASSCOPY));
	WritePrivateProfileString(section, _T("BassCopy"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CYMBALCOPY));
	WritePrivateProfileString(section, _T("DrumsCopy"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EARTRAINING));
	WritePrivateProfileString(section, _T("EarTraining"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_MONORAL));
	WritePrivateProfileString(section, _T("Monoral"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_ONLYLEFT));
	WritePrivateProfileString(section, _T("OnlyLeft"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_ONLYRIGHT));
	WritePrivateProfileString(section, _T("OnlyRight"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CHANGELR));
	WritePrivateProfileString(section, _T("ChangeLR"), buf, 
		initFilePath.c_str());
}
//----------------------------------------------------------------------------
// 設定状態の保存
//----------------------------------------------------------------------------
void CMainWnd::SaveSettings(const PCTSTR & pFilePath)
{
	TCHAR buf[255];

	_stprintf_s(buf, _T("%4.2f"), (double)(m_speedSlider->GetThumbPos()
		/ pow(10.0, m_speedLabel->GetDecimalDigit())));
	WritePrivateProfileString(_T("Options"), _T("Speed"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%4.2f"), (double)(m_freqSlider->GetThumbPos()
		/ pow(10.0, m_freqLabel->GetDecimalDigit())));
	WritePrivateProfileString(_T("Options"), _T("Frequency"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%2.2f"), (double)(m_pitchSlider->GetThumbPos()
		/ pow(10.0, m_pitchLabel->GetDecimalDigit())));
	WritePrivateProfileString(_T("Options"), _T("Pitch"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_volumeSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Volume"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_panSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Pan"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq20Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ20"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq25Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ25"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq31_5Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ31.5"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq40Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ40"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq50Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ50"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq63Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ63"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq80Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ80"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq100Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ100"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq125Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ125"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq160Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ160"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq200Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ200"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq250Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ250"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq315Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ315"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq400Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ400"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq500Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ500"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq630Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ630"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq800Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ800"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq1kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq1_25kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1.25K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq1_6kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1.6K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq2kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ2K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq2_5kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ2.5K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq3_15kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ3.15K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq4kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ4K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq5kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ5K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq6_3kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ6.3K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq8kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ8K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq10kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ10K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq12_5kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ12.5K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq16kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ16K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_eq20kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ20K"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERB_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("ReverbDefault"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERB_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("ReverbCustomize"), buf, 
		pFilePath);
	BASS_DX8_REVERB bdr;
	BOOL bReverb = m_sound->GetReverb(&bdr);
	int nGain = bReverb ? (int)bdr.fInGain : 0;
	TCHAR chGain[255], chRevMix[255], chRevTime[255], chHigh[255];
	_stprintf_s(chGain, _T("%d"), nGain);
	WritePrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_Gain"),
		chGain, pFilePath);
	int nRevMix = bReverb ? (int)bdr.fReverbMix : 0;
	_stprintf_s(chRevMix, _T("%d"), nRevMix);
	WritePrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_RevMix"),
		chRevMix, pFilePath);
	double dRevTime = bReverb ? bdr.fReverbTime : 1000.0;
	_stprintf_s(chRevTime, _T("%4.3f"), dRevTime);
	WritePrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_RevTime"),
		chRevTime, pFilePath);
	double dHigh = bReverb ? bdr.fHighFreqRTRatio : 0.001;
	_stprintf_s(chHigh, _T("%4.3f"), dHigh);
	WritePrivateProfileString(_T("PlayMode"), _T("ReverbCustomize_High"),
		chHigh, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbDefault"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PADDEDCELL));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbPaddedCell"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_ROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_BATHROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbBathRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_LIVINGROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbLivingRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_STONEROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbStoneRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_AUDITORIUM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbAuditorium"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CONCERTHALL));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbConcertHall"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CAVE));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCave"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_ARENA));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbArena"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_HANGAR));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbHangar"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_3DREVERB_CARPETEDHALLWAY));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCarpetedHallway"),
		buf, pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_HALLWAY));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbHallway"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_STONECORRIDOR));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbStoneCorridor"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_ALLEY));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbAlley"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_FOREST));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbForest"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CITY));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCity"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_MOUNTAINS));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbMountains"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_QUARRY));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbQuarry"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PLAIN));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbPlain"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PARKINGLOT));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbParkingLot"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_SEWERPIPE));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbSewerPipe"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_UNDERWATER));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbUnderWater"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_SMALLROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbSmallRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_MEDIUMROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbMediumRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_LARGEROOM));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbLargeRoom"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_MEDIUMHALL));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbMediumHall"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_LARGEHALL));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbLargeHall"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_PLATE));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbPlate"), buf, 
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_3DREVERB_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize"), buf, 
		pFilePath);
	BASS_DX8_I3DL2REVERB bdir;
	BOOL b3DReverb = m_sound->Get3DReverb(&bdir);

	int lRoom = b3DReverb ? bdir.lRoom : -1000;
	int lRoomHF = b3DReverb ? bdir.lRoomHF : -100;
	float flRoomRolloffFactor = b3DReverb ? bdir.flRoomRolloffFactor : 0.0f;
	float flDecayTime = b3DReverb ? bdir.flDecayTime : 1.49f;
	float flDecayHFRatio = b3DReverb ? bdir.flDecayHFRatio : 0.83f;
	int lReflections = b3DReverb ? bdir.lReflections : -2602;
	float flReflectionsDelay = b3DReverb ? bdir.flReflectionsDelay : 0.007f;
	int lReverb = b3DReverb ? bdir.lReverb : 200;
	float flReverbDelay = b3DReverb ? bdir.flReverbDelay : 0.011f;
	float flDiffusion = b3DReverb ? bdir.flDiffusion : 100.0f;
	float flDensity = b3DReverb ? bdir.flDensity : 100.0f;
	float flHFReference = b3DReverb ? bdir.flHFReference : 5000.0f;

	TCHAR chRoom[255], chRoomHF[255], chRoomRolloffFactor[255],
			chDecayTime[255], chDecayHFRatio[255], chReflections[255],
			chReflectionsDelay[255], chReverb[255], chReverbDelay[255],
			chDiffusion[255], chDensity[255], chHFReference[255];

	_stprintf_s(chRoom, _T("%d"), lRoom);
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Room"),
		chRoom, pFilePath);
	_stprintf_s(chRoomHF, _T("%d"), lRoomHF);
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_RoomHF"),
		chRoomHF, pFilePath);
	_stprintf_s(chRoomRolloffFactor, _T("%4.3f"), flRoomRolloffFactor);
	WritePrivateProfileString(_T("PlayMode"),
		_T("3DReverbCustomize_RoomRolloffFactor"),
		chRoomRolloffFactor, pFilePath);
	_stprintf_s(chDecayTime, _T("%4.3f"), flDecayTime);
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_DecayTime"),
		chDecayTime, pFilePath);
	_stprintf_s(chDecayHFRatio, _T("%4.3f"), flDecayHFRatio);
	WritePrivateProfileString(_T("PlayMode"),
		_T("3DReverbCustomize_DecayHFRatio"), chDecayHFRatio, pFilePath);
	_stprintf_s(chReflections, _T("%d"), lReflections);
	WritePrivateProfileString(_T("PlayMode"),
		_T("3DReverbCustomize_Reflections"), chReflections, pFilePath);
	_stprintf_s(chReflectionsDelay, _T("%4.3f"), flReflectionsDelay);
	WritePrivateProfileString(_T("PlayMode"),
		_T("3DReverbCustomize_ReflectionsDelay"), chReflectionsDelay,
		pFilePath);
	_stprintf_s(chReverb, _T("%d"), lReverb);
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Reverb"),
		chReverb, pFilePath);
	_stprintf_s(chReverbDelay, _T("%4.3f"), flReverbDelay);
	WritePrivateProfileString(_T("PlayMode"),
		_T("3DReverbCustomize_ReverbDelay"), chReverbDelay, pFilePath);
	_stprintf_s(chDiffusion, _T("%4.3f"), flDiffusion);
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Diffusion"),
		chDiffusion, pFilePath);
	_stprintf_s(chDensity, _T("%4.3f"), flDensity);
	WritePrivateProfileString(_T("PlayMode"), _T("3DReverbCustomize_Density"),
		chDensity, pFilePath);
	_stprintf_s(chHFReference, _T("%4.3f"), flHFReference);
	WritePrivateProfileString(_T("PlayMode"),
		_T("3DReverbCustomize_HFReference"), chHFReference, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayDefault"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_SHORT));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayShort"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_MEDIUM));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayMedium"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_LONG));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayLong"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOSHORT));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayStereoShort"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOMEDIUM));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayStereoMedium"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOLONG));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayStereoLong"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_MOUNTAIN));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayMountain"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_BIG));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayBig"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_STEREOBIG));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayStereoBig"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_DOUBLING));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayDoubling"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_DOUBLEKICK));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayDoubleKick"), buf, 
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DELAY_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("DelayCustomize"), buf, 
		pFilePath);
	BASS_DX8_ECHO bde;
	BOOL bDelay = m_sound->GetDelay(&bde);
	float fWetDryMix = bDelay ? bde.fWetDryMix : 8.0f;
	float fFeedback = bDelay ? bde.fFeedback : 50.0f;
	float fLeftDelay = bDelay ? bde.fLeftDelay : 600.0f;
	float fRightDelay = bDelay ? bde.fRightDelay : 300.0f;
	int lPanDelay = bDelay ? bde.lPanDelay : 1;
	TCHAR chWetDryMix[255], chFeedback[255], chLeftDelay[255],
		  chRightDelay[255], chPanDelay[255];
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chLeftDelay, _T("%4.3f"), fLeftDelay);
	_stprintf_s(chRightDelay, _T("%4.3f"), fRightDelay);
	_stprintf_s(chPanDelay, _T("%d"), lPanDelay);
	WritePrivateProfileString(_T("PlayMode"), _T("DelayCustomize_WetDryMix"),
		chWetDryMix, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("DelayCustomize_Feedback"),
		chFeedback, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("DelayCustomize_LeftDelay"),
		chLeftDelay, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("DelayCustomize_RightDelay"),
		chRightDelay, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("DelayCustomize_PanDelay"),
		chPanDelay, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CHORUS_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusDefault"), buf, 
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CHORUS_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize"), buf, 
		pFilePath);
	BASS_DX8_CHORUS bdc;
	BOOL bChorus = m_sound->GetChorus(&bdc);
	fWetDryMix = bChorus ? bdc.fWetDryMix : 50.0f;
	float fDepth = bChorus ? bdc.fDepth : 10.0f;
	fFeedback = bChorus ? bdc.fFeedback : 25.0f;
	float fFrequency = bChorus ? bdc.fFrequency : 1.1f;
	int lWaveForm = bChorus ? bdc.lWaveform : 1;
	float fDelay = bChorus ? bdc.fDelay : 16.0f;
	TCHAR chDepth[255], chFrequency[255], chWaveForm[255], chDelay[255];
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chDepth, _T("%4.3f"), fDepth);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chFrequency, _T("%4.3f"), fFrequency);
	_stprintf_s(chWaveForm, _T("%d"), lWaveForm);
	_stprintf_s(chDelay, _T("%4.3f"), fDelay);
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_WetDryMix"),
		chWetDryMix, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Depth"),
		chDepth, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Feedback"),
		chFeedback, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Frequency"),
		chFrequency, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Waveform"),
		chWaveForm, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("ChorusCustomize_Delay"),
		chDelay, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_COMPRESSOR_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("CompressorDefault"), buf, 
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_COMPRESSOR_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("CompressorCustomize"), buf, 
		pFilePath);
	BASS_DX8_COMPRESSOR bdcmp;
	BOOL bCompressor = m_sound->GetCompressor(&bdcmp);
	float fGain = bCompressor ? bdcmp.fGain : 0.0f;
	float fAttack = bCompressor ? bdcmp.fAttack : 10.0f;
	float fRelease = bCompressor ? bdcmp.fRelease : 200.0f;
	float fThreshold = bCompressor ? bdcmp.fThreshold : -20.0f;
	float fRatio = bCompressor ? bdcmp.fRatio : 3.0f;
	float fPredelay = bCompressor ? bdcmp.fPredelay : 4.0f;
	TCHAR chAttack[255], chRelease[255], chThreshold[255],
		  chRatio[255], chPredelay[255];
	_stprintf_s(chGain, _T("%4.3f"), fGain);
	_stprintf_s(chAttack, _T("%4.3f"), fAttack);
	_stprintf_s(chRelease, _T("%4.3f"), fRelease);
	_stprintf_s(chThreshold, _T("%4.3f"), fThreshold);
	_stprintf_s(chRatio, _T("%4.3f"), fRatio);
	_stprintf_s(chPredelay, _T("%4.3f"), fPredelay);
	WritePrivateProfileString(_T("PlayMode"), _T("CompressorCustomize_Gain"),
		chGain, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("CompressorCustomize_Attack"),
		chAttack, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("CompressorCustomize_Release"),
		chRelease, pFilePath);
	WritePrivateProfileString(_T("PlayMode"),
		_T("CompressorCustomize_Threshold"), chThreshold, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("CompressorCustomize_Ratio"),
		chRatio, pFilePath);
	WritePrivateProfileString(_T("PlayMode"),
		_T("CompressorCustomize_Predelay"), chPredelay, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FLANGER_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerDefault"), buf, 
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FLANGER_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize"), buf, 
		pFilePath);
	BASS_DX8_FLANGER bdf;
	BOOL bFlanger = m_sound->GetFlanger(&bdf);
	fWetDryMix = bFlanger ? bdf.fWetDryMix : 50.0f;
	fDepth = bFlanger ? bdf.fDepth : 10.0f;
	fFeedback = bFlanger ? bdf.fFeedback : 25.0f;
	fFrequency = bFlanger ? bdf.fFrequency : 1.1f;
	lWaveForm = bFlanger ? bdf.lWaveform : 1;
	fDelay = bFlanger ? bdf.fDelay : 16.0f;
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chDepth, _T("%4.3f"), fDepth);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chFrequency, _T("%4.3f"), fFrequency);
	_stprintf_s(chWaveForm, _T("%d"), lWaveForm);
	_stprintf_s(chDelay, _T("%4.3f"), fDelay);
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_WetDryMix"),
		chWetDryMix, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Depth"),
		chDepth, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Feedback"),
		chFeedback, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Frequency"),
		chFrequency, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Waveform"),
		chWaveForm, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("FlangerCustomize_Delay"),
		chDelay, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_GARGLE_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("GargleDefault"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_GARGLE_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("GargleCustomize"), buf, 
		pFilePath);
	BASS_DX8_GARGLE bdg;
	BOOL bGargle = m_sound->GetGargle(&bdg);
	int nRateHz = bGargle ? bdg.dwRateHz : 20;
	int nWaveShape = bGargle ? bdg.dwWaveShape : 0;
	TCHAR chRateHz[255], chWaveShape[255];
	_stprintf_s(chRateHz, _T("%d"), nRateHz);
	_stprintf_s(chWaveShape, _T("%d"), nWaveShape);
	WritePrivateProfileString(_T("PlayMode"), _T("GargleCustomize_RateHz"),
		chRateHz, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("GargleCustomize_WaveShape"),
		chWaveShape, pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DISTORTION_DEFAULT));
	WritePrivateProfileString(_T("PlayMode"), _T("DistortionDefault"), buf, 
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DISTORTION_CUSTOMIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("DistortionCustomize"), buf, 
		pFilePath);
	BASS_DX8_DISTORTION bdd;
	BOOL bDistortion = m_sound->GetDistortion(&bdd);
	fGain = bDistortion ? bdd.fGain : -18.0f;
	float fEdge = bDistortion ? bdd.fEdge : 15.0f;
	float fPostEQCenterFrequency =
		bDistortion ? bdd.fPostEQCenterFrequency : 2400.0f;
	float fPostEQBandwidth = bDistortion ? bdd.fPostEQBandwidth : 2400.0f;
	float fPreLowpassCutoff = bDistortion ? bdd.fPreLowpassCutoff : 8000.0f;
	TCHAR chEdge[255], chPostEQCenterFrequency[255],
		  chPostEQBandwidth[255], chPreLowpassCutoff[255];
	_stprintf_s(chGain, _T("%4.3f"), fGain);
	_stprintf_s(chEdge, _T("%4.3f"), fEdge);
	_stprintf_s(chPostEQCenterFrequency, _T("%4.3f"), fPostEQCenterFrequency);
	_stprintf_s(chPostEQBandwidth, _T("%4.3f"), fPostEQBandwidth);
	_stprintf_s(chPreLowpassCutoff, _T("%4.3f"), fPreLowpassCutoff);
	WritePrivateProfileString(_T("PlayMode"), _T("DistortionCustomize_Gain"),
		chGain, pFilePath);
	WritePrivateProfileString(_T("PlayMode"), _T("DistortionCustomize_Edge"),
		chEdge, pFilePath);
	WritePrivateProfileString(_T("PlayMode"),
		_T("DistortionCustomize_PostEQCenterFrequency"),
		chPostEQCenterFrequency, pFilePath);
	WritePrivateProfileString(_T("PlayMode"),
		_T("DistortionCustomize_PostEQBandwidth"), chPostEQBandwidth,
		pFilePath);
	WritePrivateProfileString(_T("PlayMode"),
		_T("DistortionCustomize_PreLowpassCutoff"), chPreLowpassCutoff,
		pFilePath);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_NORMALIZE));
	WritePrivateProfileString(_T("PlayMode"), _T("Normalize"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_VOCALCANCEL));
	WritePrivateProfileString(_T("PlayMode"), _T("VocalCancel"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERSE));
	WritePrivateProfileString(_T("PlayMode"), _T("Reverse"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECORD));
	WritePrivateProfileString(_T("PlayMode"), _T("Record"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_LOWBATTERY));
	WritePrivateProfileString(_T("PlayMode"), _T("LowBattery"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_NOSENSE));
	WritePrivateProfileString(_T("PlayMode"), _T("NoSense"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_BASSCOPY));
	WritePrivateProfileString(_T("PlayMode"), _T("BassCopy"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CYMBALCOPY));
	WritePrivateProfileString(_T("PlayMode"), _T("DrumsCopy"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EARTRAINING));
	WritePrivateProfileString(_T("PlayMode"), _T("EarTraining"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_MONORAL));
	WritePrivateProfileString(_T("PlayMode"), _T("Monoral"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_ONLYLEFT));
	WritePrivateProfileString(_T("PlayMode"), _T("OnlyLeft"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_ONLYRIGHT));
	WritePrivateProfileString(_T("PlayMode"), _T("OnlyRight"), buf, 
		pFilePath);
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CHANGELR));
	WritePrivateProfileString(_T("PlayMode"), _T("ChangeLR"), buf, 
		pFilePath);
}
//----------------------------------------------------------------------------
// AB ループ A の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopA(QWORD pos)
{
	m_sound->SetLoopPosA(pos);
	m_sound->AddMarker(pos);

	BOOL bDone = FALSE; // 範囲を設定したかどうか
	std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
	QWORD length = m_sound->ChannelGetLength();
	int max = (int)arrayMarker.size();
	for(int i = 0; i < max; i++) {
		if(i + 1 < max) {
			if(arrayMarker[i] <= pos && pos < arrayMarker[i + 1]) {
				bDone = TRUE;
				m_timeSlider->SetStyle(m_timeSlider->GetStyle()
					| TBS_ENABLESELRANGE);
				SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
					(LPARAM)(arrayMarker[i] / 100000));
				SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
					(LPARAM)(arrayMarker[i + 1] / 100000));
				m_sound->SetLoopPosB(arrayMarker[i + 1]);
				break;
			}
		}
	}

	if(!bDone) {
		// 追加したマーカーの位置が一番最後の場合
		if(arrayMarker[max - 1] <= pos && pos <= length) {
			bDone = TRUE;
			m_timeSlider->SetStyle(m_timeSlider->GetStyle()
				| TBS_ENABLESELRANGE);
			SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
				(LPARAM)(arrayMarker[max - 1] / 100000));
			SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, (LPARAM)(length
				/ 100000));
			m_sound->SetLoopPosB(length);
		}
	}
}
//----------------------------------------------------------------------------
// AB ループ A の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopA()
{
	m_sound->ClearMarker();
	BOOL bLoop = !m_sound->IsABLoopA();
	m_sound->SetABLoopA(bLoop);
	m_toolBar->SetABLoopState(bLoop, m_sound->IsABLoopB());
	m_menu->SetABLoopState(bLoop, m_sound->IsABLoopB());

	if(bLoop && m_sound->IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オン

		// 現在の再生位置にＡＢループのＡを設定
		QWORD time = m_sound->ChannelGetPosition();
		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, (LONG)(time
			/ 100000));
		m_sound->SetLoopPosA(time);
	}
	else if(bLoop && !m_sound->IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オフ

		m_timeSlider->SetStyle(m_timeSlider->GetStyle() | TBS_ENABLESELRANGE);

		// 現在の再生位置にＡＢループのＡを設定
		QWORD time = m_sound->ChannelGetPosition();
		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, (LONG)(time
			/ 100000));
		m_sound->SetLoopPosA(time);

		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
			(LONG)(m_sound->ChannelGetLength() / 100000));
	}
	else if(!bLoop && m_sound->IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オン

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
	}
	else if(!bLoop && !m_sound->IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オフ

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, 0L);
		m_timeSlider->SetStyle(m_timeSlider->GetStyle() & ~TBS_ENABLESELRANGE);
	}
}
//----------------------------------------------------------------------------
// AB ループ A の設定（秒）
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopA_Sec(double dTime)
{
	if(dTime == m_sound->GetLoopPosB_sec()) return;
	if(m_sound->GetLoopPosB_sec() < dTime) return;
	QWORD time = m_sound->ChannelSeconds2Bytes(dTime);
	m_sound->ClearMarker();
	BOOL bLoop = m_sound->IsABLoopA();
	m_sound->SetABLoopA(bLoop);
	m_toolBar->SetABLoopState(bLoop, m_sound->IsABLoopB());
	m_menu->SetABLoopState(bLoop, m_sound->IsABLoopB());

	if(bLoop && m_sound->IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オン

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, (LONG)(time
			/ 100000));
		m_sound->SetLoopPosA(time);
		if(m_sound->ChannelGetPosition() < time)
			m_sound->ChannelSetPosition(time);
	}
	else if(bLoop && !m_sound->IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オフ

		m_timeSlider->SetStyle(m_timeSlider->GetStyle() | TBS_ENABLESELRANGE);

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, (LONG)(time
			/ 100000));
		m_sound->SetLoopPosA(time);

		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
			(LONG)(m_sound->ChannelGetLength() / 100000));

		if(m_sound->ChannelGetPosition() < time)
			m_sound->ChannelSetPosition(time);
	}
	else if(!bLoop && m_sound->IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オン

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
	}
	else if(!bLoop && !m_sound->IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オフ

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, 0L);
		m_timeSlider->SetStyle(m_timeSlider->GetStyle() & ~TBS_ENABLESELRANGE);
	}
}
//----------------------------------------------------------------------------
// AB ループ B の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopB()
{
	m_sound->ClearMarker();
	BOOL bLoop = !m_sound->IsABLoopB();
	m_sound->SetABLoopB(bLoop);
	m_toolBar->SetABLoopState(m_sound->IsABLoopA(), bLoop);
	m_menu->SetABLoopState(m_sound->IsABLoopA(), bLoop);

	if(m_sound->IsABLoopA() && bLoop) {
		// Ａループ：オン
		// Ｂループ：オン

		// 現在の再生位置にＡＢループのＢを設定
		QWORD time = m_sound->ChannelGetPosition();
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, (LONG)(time / 100000));
		m_sound->SetLoopPosB(time);

		// Ａの位置に再生位置を移す
		SetTime(m_sound->GetLoopPosA());
	}
	else if(m_sound->IsABLoopA() && !bLoop) {
		// Ａループ：オン
		// Ｂループ：オフ

		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
					(LONG)(m_sound->ChannelGetLength() / 100000));		
	}
	else if(!m_sound->IsABLoopA() && bLoop) {
		// Ａループ：オフ
		// Ｂループ：オン

		m_timeSlider->SetStyle(m_timeSlider->GetStyle() | TBS_ENABLESELRANGE);
		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);

		// 現在の再生位置にＡＢループのＢを設定
		QWORD time = m_sound->ChannelGetPosition();
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, (LONG)(time / 100000));
		m_sound->SetLoopPosB(time);

		SetTime(0);
	}
	else if(!m_sound->IsABLoopA() && !bLoop) {
		// Ａループ：オフ
		// Ｂループ：オフ

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, 0L);
		m_timeSlider->SetStyle(m_timeSlider->GetStyle() & ~TBS_ENABLESELRANGE);
	}
}
//----------------------------------------------------------------------------
// AB ループ B の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopB_Sec(double dTime)
{
	if(dTime == m_sound->GetLoopPosA_sec()) return;
	if(dTime < m_sound->GetLoopPosA_sec()) return;
	QWORD time = m_sound->ChannelSeconds2Bytes(dTime);
	m_sound->ClearMarker();
	BOOL bLoop = m_sound->IsABLoopB();
	m_sound->SetABLoopB(bLoop);
	m_toolBar->SetABLoopState(m_sound->IsABLoopA(), bLoop);
	m_menu->SetABLoopState(m_sound->IsABLoopA(), bLoop);

	if(m_sound->IsABLoopA() && bLoop) {
		// Ａループ：オン
		// Ｂループ：オン

		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, (LONG)(time / 100000));
		m_sound->SetLoopPosB(time);

		// Ａの位置に再生位置を移す
		SetTime(m_sound->GetLoopPosA());
	}
	else if(m_sound->IsABLoopA() && !bLoop) {
		// Ａループ：オン
		// Ｂループ：オフ

		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
					(LONG)(m_sound->ChannelGetLength() / 100000));		
	}
	else if(!m_sound->IsABLoopA() && bLoop) {
		// Ａループ：オフ
		// Ｂループ：オン

		m_timeSlider->SetStyle(m_timeSlider->GetStyle() | TBS_ENABLESELRANGE);
		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);

		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, (LONG)(time / 100000));
		m_sound->SetLoopPosB(time);

		SetTime(0);
	}
	else if(!m_sound->IsABLoopA() && !bLoop) {
		// Ａループ：オフ
		// Ｂループ：オフ

		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, 0L);
		m_timeSlider->SetStyle(m_timeSlider->GetStyle() & ~TBS_ENABLESELRANGE);
	}
}
//----------------------------------------------------------------------------
// AB ループ A の位置設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopASetting()
{
	m_abLoopPosWnd->Create(TRUE);
}
//----------------------------------------------------------------------------
// AB ループ B の位置設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopBSetting()
{
	m_abLoopPosWnd->Create(FALSE);
}
//----------------------------------------------------------------------------
// 全曲ループ
//----------------------------------------------------------------------------
void CMainWnd::SetAllLoop()
{
	BOOL bAllLoop = !m_menu->IsItemChecked(ID_ALOOP);
	m_menu->CheckItem(ID_ALOOP, bAllLoop ? MF_CHECKED : MF_UNCHECKED);
	m_toolBar->CheckButton(ID_ALOOP, bAllLoop);

	SetPreviousNextMenuState();
}
//----------------------------------------------------------------------------
// 全てのエフェクトを設定
//----------------------------------------------------------------------------
void CMainWnd::SetAllEffects()
{
	SetOnlyLeft(m_menu->IsItemChecked(ID_ONLYLEFT));
	SetOnlyRight(m_menu->IsItemChecked(ID_ONLYRIGHT));
	SetChangeLR(m_menu->IsItemChecked(ID_CHANGELR));
	SetMonoral(m_menu->IsItemChecked(ID_MONORAL));
	SetNormalize(m_menu->IsItemChecked(ID_NORMALIZE));
	SetVocalCancel(m_menu->IsItemChecked(ID_VOCALCANCEL));
	SetReverse(m_menu->IsItemChecked(ID_REVERSE));
	SetSpeed((double)(m_speedSlider->GetThumbPos()
		/ pow(10.0, m_speedLabel->GetDecimalDigit())));
	SetFreq((double)(m_freqSlider->GetThumbPos()
		/ pow(10.0, m_freqLabel->GetDecimalDigit())));
	SetPitch((double)(m_pitchSlider->GetThumbPos()
		/ pow(10.0, m_pitchLabel->GetDecimalDigit())));
	SetVolume((double)m_volumeSlider->GetThumbPos() / 10.0);
	SetPan(m_panSlider->GetThumbPos());
	SetEQ20(m_eq20Slider->GetThumbPos());
	SetEQ25(m_eq25Slider->GetThumbPos());
	SetEQ31_5(m_eq31_5Slider->GetThumbPos());
	SetEQ40(m_eq40Slider->GetThumbPos());
	SetEQ50(m_eq50Slider->GetThumbPos());
	SetEQ63(m_eq63Slider->GetThumbPos());
	SetEQ80(m_eq80Slider->GetThumbPos());
	SetEQ100(m_eq100Slider->GetThumbPos());
	SetEQ125(m_eq125Slider->GetThumbPos());
	SetEQ160(m_eq160Slider->GetThumbPos());
	SetEQ200(m_eq200Slider->GetThumbPos());
	SetEQ250(m_eq250Slider->GetThumbPos());
	SetEQ315(m_eq315Slider->GetThumbPos());
	SetEQ400(m_eq400Slider->GetThumbPos());
	SetEQ500(m_eq500Slider->GetThumbPos());
	SetEQ630(m_eq630Slider->GetThumbPos());
	SetEQ800(m_eq800Slider->GetThumbPos());
	SetEQ1K(m_eq1kSlider->GetThumbPos());
	SetEQ1_25K(m_eq1_25kSlider->GetThumbPos());
	SetEQ1_6K(m_eq1_6kSlider->GetThumbPos());
	SetEQ2K(m_eq2kSlider->GetThumbPos());
	SetEQ2_5K(m_eq2_5kSlider->GetThumbPos());
	SetEQ3_15K(m_eq3_15kSlider->GetThumbPos());
	SetEQ4K(m_eq4kSlider->GetThumbPos());
	SetEQ5K(m_eq5kSlider->GetThumbPos());
	SetEQ6_3K(m_eq6_3kSlider->GetThumbPos());
	SetEQ8K(m_eq8kSlider->GetThumbPos());
	SetEQ10K(m_eq10kSlider->GetThumbPos());
	SetEQ12_5K(m_eq12_5kSlider->GetThumbPos());
	SetEQ16K(m_eq16kSlider->GetThumbPos());
	SetEQ20K(m_eq20kSlider->GetThumbPos());
	SetReverb(bReverb);
	Set3DReverb(b3DReverb);
	SetDelay(bDelay);
	SetChorus(bChorus);
	SetCompressor(bCompressor);
	SetFlanger(bFlanger);
	SetGargle(bGargle);
	SetDistortion(bDistortion);
}
//----------------------------------------------------------------------------
// 連続再生
//----------------------------------------------------------------------------
void CMainWnd::SetContinue()
{
	BOOL bContinue = !m_menu->IsItemChecked(ID_CONTINUE);
	m_menu->CheckItem(ID_CONTINUE, bContinue ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ビデオ画面の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetVideoScreenVisible()
{
	BOOL bVideoScreenVisible = !m_menu->IsItemChecked(ID_VIDEOSCREEN);

	int nCmdShow = bVideoScreenVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bVideoScreenVisible ? MF_CHECKED : MF_UNCHECKED;
	m_videoScreen->Show(nCmdShow);
	m_menu->CheckItem(ID_VIDEOSCREEN, uCheck);
	m_videoScreen->SetSize(GetClientWidth(), 240);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 再生位置スライダの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetTimeSliderVisible()
{
	BOOL bTimeSliderVisible = !m_menu->IsItemChecked(ID_TIMESLIDER);

	int nCmdShow = bTimeSliderVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bTimeSliderVisible ? MF_CHECKED : MF_UNCHECKED;
	m_timeSlider->Show(nCmdShow);
	m_menu->CheckItem(ID_TIMESLIDER, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// エクスプローラの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetExplorerVisible()
{
	BOOL bExplorerVisible = !m_menu->IsItemChecked(ID_EXPLORER);

	int nCmdShow = bExplorerVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bExplorerVisible ? MF_CHECKED : MF_UNCHECKED;
	m_explorerBar->Show(nCmdShow);
	if(!bExplorerVisible)
		SetClientSize(GetClientWidth() - m_explorer->GetWidth(),
			GetClientHeight(), TRUE);
	m_explorer->Show(nCmdShow);
	m_menu->CheckItem(ID_EXPLORER, uCheck);
	m_toolBar->CheckButton(ID_EXPLORER, bExplorerVisible);
	if(bExplorerVisible) {
		SetClientSize(GetClientWidth() + m_explorer->GetWidth(),
			GetClientHeight(), TRUE);
		SetFocus(*m_explorer);
	}
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 再生速度の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetSpeedVisible()
{
	BOOL bSpeedVisible = !m_menu->IsItemChecked(ID_SPEED);

	int nCmdShow = bSpeedVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bSpeedVisible ? MF_CHECKED : MF_UNCHECKED;
	if(bSpeedVisible || m_menu->IsItemChecked(ID_EXPLORER)
		|| m_menu->IsItemChecked(ID_FREQ)
		|| m_menu->IsItemChecked(ID_PITCH))
		m_divider2->Show(SW_SHOW);
	else m_divider2->Show(SW_HIDE);
	m_speedLabel->Show(nCmdShow);
	m_speedSlider->Show(nCmdShow);
	m_menu->CheckItem(ID_SPEED, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 再生周波数の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetFreqVisible()
{
	BOOL bFreqVisible = !m_menu->IsItemChecked(ID_FREQ);

	int nCmdShow = bFreqVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bFreqVisible ? MF_CHECKED : MF_UNCHECKED;
	if(m_menu->IsItemChecked(ID_EXPLORER) || m_menu->IsItemChecked(ID_SPEED)
		|| bFreqVisible
		|| m_menu->IsItemChecked(ID_PITCH))
		m_divider2->Show(SW_SHOW);
	else m_divider2->Show(SW_HIDE);
	m_freqLabel->Show(nCmdShow);
	m_freqSlider->Show(nCmdShow);
	m_menu->CheckItem(ID_FREQ, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 音程の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPitchVisible()
{
	BOOL bPitchVisible = !m_menu->IsItemChecked(ID_PITCH);

	int nCmdShow = bPitchVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bPitchVisible ? MF_CHECKED : MF_UNCHECKED;
	if(m_menu->IsItemChecked(ID_EXPLORER) || m_menu->IsItemChecked(ID_SPEED)
		|| m_menu->IsItemChecked(ID_FREQ)
		|| bPitchVisible)
		m_divider2->Show(SW_SHOW);
	else m_divider2->Show(SW_HIDE);
	m_pitchLabel->Show(nCmdShow);
	m_pitchSlider->Show(nCmdShow);
	m_menu->CheckItem(ID_PITCH, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 音量の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetVolumeVisible()
{
	BOOL bVolumeVisible = !m_menu->IsItemChecked(ID_VOLUME);

	int nCmdShow = bVolumeVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bVolumeVisible ? MF_CHECKED : MF_UNCHECKED;
	if(bVolumeVisible || m_menu->IsItemChecked(ID_PAN))
		m_divider3->Show(SW_SHOW);
	else m_divider3->Show(SW_HIDE);
	m_volumeLabel->Show(nCmdShow);
	m_volumeSlider->Show(nCmdShow);
	m_menu->CheckItem(ID_VOLUME, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// パンの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPanVisible()
{
	BOOL bPanVisible = !m_menu->IsItemChecked(ID_PAN);

	int nCmdShow = bPanVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bPanVisible ? MF_CHECKED : MF_UNCHECKED;
	if(m_menu->IsItemChecked(ID_VOLUME) || bPanVisible) m_divider3->Show(SW_SHOW);
	else m_divider3->Show(SW_HIDE);
	m_panLabel->Show(nCmdShow);
	m_panSlider->Show(nCmdShow);
	m_menu->CheckItem(ID_PAN, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 回数ループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetCountLoop()
{
	if(bMarkerPlay) countLoopWnd->Create();
}
//----------------------------------------------------------------------------
// 回数ループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetCountLoop(int nCount)
{
	nCurrentLoopCount = 0;
	if(nCount == 0) {
		nLoopCount = 0;
		SetCountLoop(FALSE, 0);
	}
	else {
		nLoopCount = nCount;
		SetCountLoop(TRUE, nLoopCount);
	}
}
//----------------------------------------------------------------------------
// 回数ループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetCountLoop(BOOL bCountLoop, int nCount)
{
	this->bCountLoop = bCountLoop;
	m_menu->CheckItem(ID_COUNTLOOP, bCountLoop ? MF_CHECKED : MF_UNCHECKED);
	if(bCountLoop) Head();
}
//----------------------------------------------------------------------------
// 多重起動の設定
//----------------------------------------------------------------------------
void CMainWnd::SetDoubleRun()
{
	BOOL bDoubleRun = !m_menu->IsItemChecked(ID_DOUBLERUN);
	m_menu->CheckItem(ID_DOUBLERUN, bDoubleRun ? MF_CHECKED : MF_UNCHECKED);
	WriteInitFile();
}
//----------------------------------------------------------------------------
// イコライザ ( 20Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ20(LONG lEQ20)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ20(20, 0.7f, (float)lEQ20);
}
//----------------------------------------------------------------------------
// イコライザ ( 25Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ25(LONG lEQ25)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ25(25, 0.7f, (float)lEQ25);
}
//----------------------------------------------------------------------------
// イコライザ ( 31.5Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ31_5(LONG lEQ31_5)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ31_5(31.5, 0.7f, (float)lEQ31_5);
}
//----------------------------------------------------------------------------
// イコライザ ( 40Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ40(LONG lEQ40)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ40(40, 0.7f, (float)lEQ40);
}
//----------------------------------------------------------------------------
// イコライザ ( 50Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ50(LONG lEQ50)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ50(50, 0.7f, (float)lEQ50);
}
//----------------------------------------------------------------------------
// イコライザ ( 63Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ63(LONG lEQ63)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ63(63, 0.7f, (float)lEQ63);
}
//----------------------------------------------------------------------------
// イコライザ ( 80Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ80(LONG lEQ80)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ80(80, 0.7f, (float)lEQ80);
}
//----------------------------------------------------------------------------
// イコライザ ( 100Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ100(LONG lEQ100)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ100(100, 0.7f, (float)lEQ100);
}
//----------------------------------------------------------------------------
// イコライザ ( 125Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ125(LONG lEQ125)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ125(125, 0.7f, (float)lEQ125);
}
//----------------------------------------------------------------------------
// イコライザ ( 160Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ160(LONG lEQ160)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ160(160, 0.7f, (float)lEQ160);
}
//----------------------------------------------------------------------------
// イコライザ ( 200Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ200(LONG lEQ200)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ200(200, 0.7f, (float)lEQ200);
}
//----------------------------------------------------------------------------
// イコライザ ( 250Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ250(LONG lEQ250)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ250(250, 0.7f, (float)lEQ250);
}
//----------------------------------------------------------------------------
// イコライザ ( 315Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ315(LONG lEQ315)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ315(315, 0.7f, (float)lEQ315);
}
//----------------------------------------------------------------------------
// イコライザ ( 400Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ400(LONG lEQ400)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ400(400, 0.7f, (float)lEQ400);
}
//----------------------------------------------------------------------------
// イコライザ ( 500Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ500(LONG lEQ500)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ500(500, 0.7f, (float)lEQ500);
}
//----------------------------------------------------------------------------
// イコライザ ( 630Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ630(LONG lEQ630)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ630(630, 0.7f, (float)lEQ630);
}
//----------------------------------------------------------------------------
// イコライザ ( 800Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ800(LONG lEQ800)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ800(800, 0.7f, (float)lEQ800);
}
//----------------------------------------------------------------------------
// イコライザ ( 1KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1K(LONG lEQ1K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ1K(1000, 0.7f, (float)lEQ1K);
}
//----------------------------------------------------------------------------
// イコライザ ( 1.25KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1_25K(LONG lEQ1_25K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ1_25K(1250, 0.7f, (float)lEQ1_25K);
}
//----------------------------------------------------------------------------
// イコライザ ( 1.6KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1_6K(LONG lEQ1_6K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ1_6K(1600, 0.7f, (float)lEQ1_6K);
}
//----------------------------------------------------------------------------
// イコライザ ( 2KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ2K(LONG lEQ2K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ2K(2000, 0.7f, (float)lEQ2K);
}
//----------------------------------------------------------------------------
// イコライザ ( 2.5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ2_5K(LONG lEQ2_5K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ2_5K(2500, 0.7f, (float)lEQ2_5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 3.15KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ3_15K(LONG lEQ3_15K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ3_15K(3150, 0.7f, (float)lEQ3_15K);
}
//----------------------------------------------------------------------------
// イコライザ ( 4KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ4K(LONG lEQ4K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ4K(4000, 0.7f, (float)lEQ4K);
}
//----------------------------------------------------------------------------
// イコライザ ( 5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ5K(LONG lEQ5K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ5K(5000, 0.7f, (float)lEQ5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 6.3KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ6_3K(LONG lEQ6_3K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ6_3K(6300, 0.7f, (float)lEQ6_3K);
}
//----------------------------------------------------------------------------
// イコライザ ( 8KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ8K(LONG lEQ8K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ8K(8000, 0.7f, (float)lEQ8K);
}
//----------------------------------------------------------------------------
// イコライザ ( 10KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ10K(LONG lEQ10K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ10K(10000, 0.7f, (float)lEQ10K);
}
//----------------------------------------------------------------------------
// イコライザ ( 12.5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ12_5K(LONG lEQ12_5K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ12_5K(12500, 0.7f, (float)lEQ12_5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 16KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ16K(LONG lEQ16K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ16K(16000, 0.7f, (float)lEQ16K);
}
//----------------------------------------------------------------------------
// イコライザ ( 20KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ20K(LONG lEQ20K)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetEQ20K(20000, 0.7f, (float)lEQ20K);
}
//----------------------------------------------------------------------------
// イコライザの設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ(LONG lEQ20, LONG lEQ25, LONG lEQ31_5, LONG lEQ40,
					 LONG lEQ50, LONG lEQ63, LONG lEQ80, LONG lEQ100,
					 LONG lEQ125, LONG lEQ160, LONG lEQ200, LONG lEQ250,
					 LONG lEQ315, LONG lEQ400, LONG lEQ500, LONG lEQ630,
					 LONG lEQ800, LONG lEQ1K, LONG lEQ1_25K, LONG lEQ1_6K,
					 LONG lEQ2K, LONG lEQ2_5K, LONG lEQ3_15K, LONG lEQ4K,
					 LONG lEQ5K, LONG lEQ6_3K, LONG lEQ8K, LONG lEQ10K,
					 LONG lEQ12_5K, LONG lEQ16K, LONG lEQ20K)
{
	m_menu->UncheckPresetMenu();
	m_eq20Label->SetEQ20(lEQ20); m_eq20Slider->SetThumbPos(lEQ20);
	SetEQ20(lEQ20);
	m_eq25Label->SetEQ25(lEQ25); m_eq25Slider->SetThumbPos(lEQ25);
	SetEQ25(lEQ25);
	m_eq31_5Label->SetEQ31_5(lEQ31_5); m_eq31_5Slider->SetThumbPos(lEQ31_5);
	SetEQ31_5(lEQ31_5);
	m_eq40Label->SetEQ40(lEQ40); m_eq40Slider->SetThumbPos(lEQ40);
	SetEQ40(lEQ40);
	m_eq50Label->SetEQ50(lEQ50); m_eq50Slider->SetThumbPos(lEQ50);
	SetEQ50(lEQ50);
	m_eq63Label->SetEQ63(lEQ63); m_eq63Slider->SetThumbPos(lEQ63);
	SetEQ63(lEQ63);
	m_eq80Label->SetEQ80(lEQ80); m_eq80Slider->SetThumbPos(lEQ80);
	SetEQ80(lEQ80);
	m_eq100Label->SetEQ100(lEQ100); m_eq100Slider->SetThumbPos(lEQ100);
	SetEQ100(lEQ100);
	m_eq125Label->SetEQ125(lEQ125); m_eq125Slider->SetThumbPos(lEQ125);
	SetEQ125(lEQ125);
	m_eq160Label->SetEQ160(lEQ160); m_eq160Slider->SetThumbPos(lEQ160);
	SetEQ160(lEQ160);
	m_eq200Label->SetEQ200(lEQ200); m_eq200Slider->SetThumbPos(lEQ200);
	SetEQ200(lEQ200);
	m_eq250Label->SetEQ250(lEQ250); m_eq250Slider->SetThumbPos(lEQ250);
	SetEQ250(lEQ250);
	m_eq315Label->SetEQ315(lEQ315); m_eq315Slider->SetThumbPos(lEQ315);
	SetEQ315(lEQ315);
	m_eq400Label->SetEQ400(lEQ400); m_eq400Slider->SetThumbPos(lEQ400);
	SetEQ400(lEQ400);
	m_eq500Label->SetEQ500(lEQ500); m_eq500Slider->SetThumbPos(lEQ500);
	SetEQ500(lEQ500);
	m_eq630Label->SetEQ630(lEQ630); m_eq630Slider->SetThumbPos(lEQ630);
	SetEQ630(lEQ630);
	m_eq800Label->SetEQ800(lEQ800); m_eq800Slider->SetThumbPos(lEQ800);
	SetEQ800(lEQ800);
	m_eq1kLabel->SetEQ1K(lEQ1K); m_eq1kSlider->SetThumbPos(lEQ1K);
	SetEQ1K(lEQ1K);
	m_eq1_25kLabel->SetEQ1_25K(lEQ1_25K); m_eq1_25kSlider->SetThumbPos(lEQ1_25K);
	SetEQ1_25K(lEQ1_25K);
	m_eq1_6kLabel->SetEQ1_6K(lEQ1_6K); m_eq1_6kSlider->SetThumbPos(lEQ1_6K);
	SetEQ1_6K(lEQ1_6K);
	m_eq2kLabel->SetEQ2K(lEQ2K); m_eq2kSlider->SetThumbPos(lEQ2K);
	SetEQ2K(lEQ2K);
	m_eq2_5kLabel->SetEQ2_5K(lEQ2_5K); m_eq2_5kSlider->SetThumbPos(lEQ2_5K);
	SetEQ2_5K(lEQ2_5K);
	m_eq3_15kLabel->SetEQ3_15K(lEQ3_15K); m_eq3_15kSlider->SetThumbPos(lEQ3_15K);
	SetEQ3_15K(lEQ3_15K);
	m_eq4kLabel->SetEQ4K(lEQ4K); m_eq4kSlider->SetThumbPos(lEQ4K);
	SetEQ4K(lEQ4K);
	m_eq5kLabel->SetEQ5K(lEQ5K); m_eq5kSlider->SetThumbPos(lEQ5K);
	SetEQ5K(lEQ5K);
	m_eq6_3kLabel->SetEQ6_3K(lEQ6_3K); m_eq6_3kSlider->SetThumbPos(lEQ6_3K);
	SetEQ6_3K(lEQ6_3K);
	m_eq8kLabel->SetEQ8K(lEQ8K); m_eq8kSlider->SetThumbPos(lEQ8K);
	SetEQ8K(lEQ8K);
	m_eq10kLabel->SetEQ10K(lEQ10K); m_eq10kSlider->SetThumbPos(lEQ10K);
	SetEQ10K(lEQ10K);
	m_eq12_5kLabel->SetEQ12_5K(lEQ12_5K); m_eq12_5kSlider->SetThumbPos(lEQ12_5K);
	SetEQ12_5K(lEQ12_5K);
	m_eq16kLabel->SetEQ16K(lEQ16K); m_eq16kSlider->SetThumbPos(lEQ16K);
	SetEQ16K(lEQ16K);
	m_eq20kLabel->SetEQ20K(lEQ20K); m_eq20kSlider->SetThumbPos(lEQ20K);
	SetEQ20K(lEQ20K);
}
//----------------------------------------------------------------------------
// グラフィックイコライザの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQVisible()
{
	BOOL bEQVisible = !m_menu->IsItemChecked(ID_EQ);

	int nCmdShow = bEQVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bEQVisible ? MF_CHECKED : MF_UNCHECKED;
	m_divider4->Show(nCmdShow);
	m_eq20Label->Show(m_menu->IsItemChecked(ID_EQ20) ? nCmdShow : SW_HIDE);
	m_eq20Slider->Show(m_menu->IsItemChecked(ID_EQ20) ? nCmdShow : SW_HIDE);
	m_eq25Label->Show(m_menu->IsItemChecked(ID_EQ25) ? nCmdShow : SW_HIDE);
	m_eq25Slider->Show(m_menu->IsItemChecked(ID_EQ25) ? nCmdShow : SW_HIDE);
	m_eq31_5Label->Show(m_menu->IsItemChecked(ID_EQ31_5) ? nCmdShow : SW_HIDE);
	m_eq31_5Slider->Show(m_menu->IsItemChecked(ID_EQ31_5) ? nCmdShow : SW_HIDE);
	m_eq40Label->Show(m_menu->IsItemChecked(ID_EQ40) ? nCmdShow : SW_HIDE);
	m_eq40Slider->Show(m_menu->IsItemChecked(ID_EQ40) ? nCmdShow : SW_HIDE);
	m_eq50Label->Show(m_menu->IsItemChecked(ID_EQ50) ? nCmdShow : SW_HIDE);
	m_eq50Slider->Show(m_menu->IsItemChecked(ID_EQ50) ? nCmdShow : SW_HIDE);
	m_eq63Label->Show(m_menu->IsItemChecked(ID_EQ63) ? nCmdShow : SW_HIDE);
	m_eq63Slider->Show(m_menu->IsItemChecked(ID_EQ63) ? nCmdShow : SW_HIDE);
	m_eq80Label->Show(m_menu->IsItemChecked(ID_EQ80) ? nCmdShow : SW_HIDE);
	m_eq80Slider->Show(m_menu->IsItemChecked(ID_EQ80) ? nCmdShow : SW_HIDE);
	m_eq100Label->Show(m_menu->IsItemChecked(ID_EQ100) ? nCmdShow : SW_HIDE);
	m_eq100Slider->Show(m_menu->IsItemChecked(ID_EQ100) ? nCmdShow : SW_HIDE);
	m_eq125Label->Show(m_menu->IsItemChecked(ID_EQ125) ? nCmdShow : SW_HIDE);
	m_eq125Slider->Show(m_menu->IsItemChecked(ID_EQ125) ? nCmdShow : SW_HIDE);
	m_eq160Label->Show(m_menu->IsItemChecked(ID_EQ160) ? nCmdShow : SW_HIDE);
	m_eq160Slider->Show(m_menu->IsItemChecked(ID_EQ160) ? nCmdShow : SW_HIDE);
	m_eq200Label->Show(m_menu->IsItemChecked(ID_EQ200) ? nCmdShow : SW_HIDE);
	m_eq200Slider->Show(m_menu->IsItemChecked(ID_EQ200) ? nCmdShow : SW_HIDE);
	m_eq250Label->Show(m_menu->IsItemChecked(ID_EQ250) ? nCmdShow : SW_HIDE);
	m_eq250Slider->Show(m_menu->IsItemChecked(ID_EQ250) ? nCmdShow : SW_HIDE);
	m_eq315Label->Show(m_menu->IsItemChecked(ID_EQ315) ? nCmdShow : SW_HIDE);
	m_eq315Slider->Show(m_menu->IsItemChecked(ID_EQ315) ? nCmdShow : SW_HIDE);
	m_eq400Label->Show(m_menu->IsItemChecked(ID_EQ400) ? nCmdShow : SW_HIDE);
	m_eq400Slider->Show(m_menu->IsItemChecked(ID_EQ400) ? nCmdShow : SW_HIDE);
	m_eq500Label->Show(m_menu->IsItemChecked(ID_EQ500) ? nCmdShow : SW_HIDE);
	m_eq500Slider->Show(m_menu->IsItemChecked(ID_EQ500) ? nCmdShow : SW_HIDE);
	m_eq630Label->Show(m_menu->IsItemChecked(ID_EQ630) ? nCmdShow : SW_HIDE);
	m_eq630Slider->Show(m_menu->IsItemChecked(ID_EQ630) ? nCmdShow : SW_HIDE);
	m_eq800Label->Show(m_menu->IsItemChecked(ID_EQ800) ? nCmdShow : SW_HIDE);
	m_eq800Slider->Show(m_menu->IsItemChecked(ID_EQ800) ? nCmdShow : SW_HIDE);
	m_eq1kLabel->Show(m_menu->IsItemChecked(ID_EQ1K) ? nCmdShow : SW_HIDE);
	m_eq1kSlider->Show(m_menu->IsItemChecked(ID_EQ1K) ? nCmdShow : SW_HIDE);
	m_eq1_25kLabel->Show(m_menu->IsItemChecked(ID_EQ1_25K) ? nCmdShow : SW_HIDE);
	m_eq1_25kSlider->Show(m_menu->IsItemChecked(ID_EQ1_25K) ? nCmdShow : SW_HIDE);
	m_eq1_6kLabel->Show(m_menu->IsItemChecked(ID_EQ1_6K) ? nCmdShow : SW_HIDE);
	m_eq1_6kSlider->Show(m_menu->IsItemChecked(ID_EQ1_6K) ? nCmdShow : SW_HIDE);
	m_eq2kLabel->Show(m_menu->IsItemChecked(ID_EQ2K) ? nCmdShow : SW_HIDE);
	m_eq2kSlider->Show(m_menu->IsItemChecked(ID_EQ2K) ? nCmdShow : SW_HIDE);
	m_eq2_5kLabel->Show(m_menu->IsItemChecked(ID_EQ2_5K) ? nCmdShow : SW_HIDE);
	m_eq2_5kSlider->Show(m_menu->IsItemChecked(ID_EQ2_5K) ? nCmdShow : SW_HIDE);
	m_eq3_15kLabel->Show(m_menu->IsItemChecked(ID_EQ3_15K) ? nCmdShow : SW_HIDE);
	m_eq3_15kSlider->Show(m_menu->IsItemChecked(ID_EQ3_15K) ? nCmdShow : SW_HIDE);
	m_eq4kLabel->Show(m_menu->IsItemChecked(ID_EQ4K) ? nCmdShow : SW_HIDE);
	m_eq4kSlider->Show(m_menu->IsItemChecked(ID_EQ4K) ? nCmdShow : SW_HIDE);
	m_eq5kLabel->Show(m_menu->IsItemChecked(ID_EQ5K) ? nCmdShow : SW_HIDE);
	m_eq5kSlider->Show(m_menu->IsItemChecked(ID_EQ5K) ? nCmdShow : SW_HIDE);
	m_eq6_3kLabel->Show(m_menu->IsItemChecked(ID_EQ6_3K) ? nCmdShow : SW_HIDE);
	m_eq6_3kSlider->Show(m_menu->IsItemChecked(ID_EQ6_3K) ? nCmdShow : SW_HIDE);
	m_eq8kLabel->Show(m_menu->IsItemChecked(ID_EQ8K) ? nCmdShow : SW_HIDE);
	m_eq8kSlider->Show(m_menu->IsItemChecked(ID_EQ8K) ? nCmdShow : SW_HIDE);
	m_eq10kLabel->Show(m_menu->IsItemChecked(ID_EQ10K) ? nCmdShow : SW_HIDE);
	m_eq10kSlider->Show(m_menu->IsItemChecked(ID_EQ10K) ? nCmdShow : SW_HIDE);
	m_eq12_5kLabel->Show(m_menu->IsItemChecked(ID_EQ12_5K) ? nCmdShow : SW_HIDE);
	m_eq12_5kSlider->Show(m_menu->IsItemChecked(ID_EQ12_5K) ? nCmdShow : SW_HIDE);
	m_eq16kLabel->Show(m_menu->IsItemChecked(ID_EQ16K) ? nCmdShow : SW_HIDE);
	m_eq16kSlider->Show(m_menu->IsItemChecked(ID_EQ16K) ? nCmdShow : SW_HIDE);
	m_eq20kLabel->Show(m_menu->IsItemChecked(ID_EQ20K) ? nCmdShow : SW_HIDE);
	m_eq20kSlider->Show(m_menu->IsItemChecked(ID_EQ20K) ? nCmdShow : SW_HIDE);
	m_menu->CheckItem(ID_EQ, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// フルスクリーンの設定
//----------------------------------------------------------------------------
void CMainWnd::SetFullScreen()
{
	m_bFullScreen = !m_bFullScreen;
	if(m_bFullScreen) {
		videoScreenWnd->Create();
		m_sound->ChannelSetWindow();
	}
	else {
		m_sound->ChannelSetWindow();
		m_sound->ResetSize(0, 0, m_videoScreen->GetWidth(),
							m_videoScreen->GetHeight());
		videoScreenWnd->Close();
		SetFocus(m_hWnd);
	}
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん速くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetIncFreq()
{
	incFreqWnd->Create();
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん速くする設定（時間ごと）
//----------------------------------------------------------------------------
void CMainWnd::SetIncFreq(double nSecond, double nIncFreq)
{
	if(nSecond == 0.0 || nIncFreq == 0.0) {
		this->nIncFreq = 0.0;
		SetIncFreq(FALSE, 0);
		nIncFreqMode = 0;
	}
	else {
		this->nIncFreq = nIncFreq;
		SetIncFreq(TRUE, nSecond);
		nIncFreqMode = 1;
	}
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん速くする設定（ループごと）
//----------------------------------------------------------------------------
void CMainWnd::SetIncFreq(double nIncFreq)
{
	BOOL bIncFreq;
	if(nIncFreq == 0.0) {
		this->nIncFreq = 0.0;
		bIncFreq = FALSE;
		nIncFreqMode = 0;
	}
	else {
		this->nIncFreq = nIncFreq;
		bIncFreq = TRUE;
		nIncFreqMode = 2;
	}
	m_menu->CheckItem(ID_INCFREQ,
		bIncFreq ? MF_CHECKED : MF_UNCHECKED);
	KillTimer(IDT_INCFREQ);
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん速くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetIncFreq(BOOL bIncFreq, double nSecond)
{
	m_menu->CheckItem(ID_INCFREQ,
		bIncFreq ? MF_CHECKED : MF_UNCHECKED);
	if(bIncFreq) SetTimer(IDT_INCFREQ, (int)(nSecond * 1000));
	else KillTimer(IDT_INCFREQ);
}
//----------------------------------------------------------------------------
// だんだん速くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetIncSpeed()
{
	incSpeedWnd->Create();
}
//----------------------------------------------------------------------------
// だんだん速くする設定（時間ごと）
//----------------------------------------------------------------------------
void CMainWnd::SetIncSpeed(double nSecond, double nIncSpeed)
{
	if(nSecond == 0.0 || nIncSpeed == 0.0) {
		this->nIncSpeed = 0.0;
		SetIncSpeed(FALSE, 0);
		nIncSpeedMode = 0;
	}
	else {
		this->nIncSpeed = nIncSpeed;
		SetIncSpeed(TRUE, nSecond);
		nIncSpeedMode = 1;
	}
}
//----------------------------------------------------------------------------
// だんだん速くする設定（ループごと）
//----------------------------------------------------------------------------
void CMainWnd::SetIncSpeed(double nIncSpeed)
{
	BOOL bIncSpeed;
	if(nIncSpeed == 0.0) {
		this->nIncSpeed = 0.0;
		bIncSpeed = FALSE;
		nIncSpeedMode = 0;
	}
	else {
		this->nIncSpeed = nIncSpeed;
		bIncSpeed = TRUE;
		nIncSpeedMode = 2;
	}
	m_menu->CheckItem(ID_INCSPEED, bIncSpeed ? MF_CHECKED : MF_UNCHECKED);
	KillTimer(IDT_INCSPEED);
}
//----------------------------------------------------------------------------
// だんだん速くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetIncSpeed(BOOL bIncSpeed, double nSecond)
{
	m_menu->CheckItem(ID_INCSPEED, bIncSpeed ? MF_CHECKED : MF_UNCHECKED);
	if(bIncSpeed) SetTimer(IDT_INCSPEED, (int)(nSecond * 1000));
	else KillTimer(IDT_INCSPEED);
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん遅くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetDecFreq()
{
	decFreqWnd->Create();
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん遅くする設定（時間ごと）
//----------------------------------------------------------------------------
void CMainWnd::SetDecFreq(double nSecond, double nDecFreq)
{
	if(nSecond == 0.0 || nDecFreq == 0.0) {
		this->nDecFreq = 0.0;
		SetDecFreq(FALSE, 0);
		nDecFreqMode = 0;
	}
	else {
		this->nDecFreq = nDecFreq;
		SetDecFreq(TRUE, nSecond);
		nDecFreqMode = 1;
	}
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん遅くする設定（ループごと）
//----------------------------------------------------------------------------
void CMainWnd::SetDecFreq(double nDecFreq)
{
	BOOL bDecFreq;
	if(nDecFreq == 0.0) {
		this->nDecFreq = 0.0;
		bDecFreq = FALSE;
		nDecFreqMode = 0;
	}
	else {
		this->nDecFreq = nDecFreq;
		bDecFreq = TRUE;
		nDecFreqMode = 2;
	}
	m_menu->CheckItem(ID_DECFREQ,
		bDecFreq ? MF_CHECKED : MF_UNCHECKED);
	KillTimer(IDT_DECFREQ);
}
//----------------------------------------------------------------------------
// 再生周波数をだんだん遅くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetDecFreq(BOOL bDecFreq, double nSecond)
{
	m_menu->CheckItem(ID_DECFREQ,
		bDecFreq ? MF_CHECKED : MF_UNCHECKED);
	if(bDecFreq) SetTimer(IDT_DECFREQ, (int)(nSecond * 1000));
	else KillTimer(IDT_DECFREQ);
}
//----------------------------------------------------------------------------
// だんだん遅くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetDecSpeed()
{
	decSpeedWnd->Create();
}
//----------------------------------------------------------------------------
// だんだん遅くする設定（時間ごと）
//----------------------------------------------------------------------------
void CMainWnd::SetDecSpeed(double nSecond, double nDecSpeed)
{
	if(nSecond == 0.0 || nDecSpeed == 0.0) {
		this->nDecSpeed = 0.0;
		SetDecSpeed(FALSE, 0);
		nDecSpeedMode = 0;
	}
	else {
		this->nDecSpeed = nDecSpeed;
		SetDecSpeed(TRUE, nSecond);
		nDecSpeedMode = 1;
	}
}
//----------------------------------------------------------------------------
// だんだん遅くする設定（ループごと）
//----------------------------------------------------------------------------
void CMainWnd::SetDecSpeed(double nDecSpeed)
{
	BOOL bDecSpeed;
	if(nDecSpeed == 0.0) {
		this->nDecSpeed = 0.0;
		bDecSpeed = FALSE;
		nDecSpeedMode = 0;
	}
	else {
		this->nDecSpeed = nDecSpeed;
		bDecSpeed = TRUE;
		nDecSpeedMode = 2;
	}
	m_menu->CheckItem(ID_DECSPEED, bDecSpeed ? MF_CHECKED : MF_UNCHECKED);
	KillTimer(IDT_DECSPEED);
}
//----------------------------------------------------------------------------
// だんだん遅くする設定
//----------------------------------------------------------------------------
void CMainWnd::SetDecSpeed(BOOL bDecSpeed, double nSecond)
{
	m_menu->CheckItem(ID_DECSPEED, bDecSpeed ? MF_CHECKED : MF_UNCHECKED);
	if(bDecSpeed) SetTimer(IDT_DECSPEED, (int)(nSecond * 1000));
	else KillTimer(IDT_DECSPEED);
}
//----------------------------------------------------------------------------
// マーカー追加時にループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetInstantLoop()
{
	bInstantLoop = !bInstantLoop;
	m_menu->CheckItem(ID_INSTANTLOOP, bInstantLoop ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// マーカー位置変更時に再生位置変更の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPositionAuto()
{
	bSetPositionAuto = !bSetPositionAuto;
	m_menu->CheckItem(ID_SETPOSITIONAUTO, bSetPositionAuto
		? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ショートカットキーの設定
//----------------------------------------------------------------------------
void CMainWnd::SetKeySetting()
{
	if(!(HWND)*keySettingWnd) keySettingWnd->Create();
	EnableWindow(m_hWnd, FALSE);
	keySettingWnd->Show(SW_SHOW);
	keySettingWnd->Update();
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CMainWnd::SetLimit()
{
	limitSettingWnd->Create();
}
//----------------------------------------------------------------------------
// 最大値／最小値の設定
//----------------------------------------------------------------------------
void CMainWnd::SetLimit(double dMinSpeed, double dMaxSpeed,
						double dMinFreq, double dMaxFreq,
						double dMinPitch, double dMaxPitch)
{
	m_speedSlider->SetLimit(dMinSpeed, dMaxSpeed);
	m_speedLabel->SetLimit(dMinSpeed, dMaxSpeed);
	m_freqSlider->SetLimit(dMinFreq, dMaxFreq);
	m_freqLabel->SetLimit(dMinFreq, dMaxFreq);
	m_pitchSlider->SetLimit(dMinPitch, dMaxPitch);
	m_pitchLabel->SetLimit(dMinPitch, dMaxPitch);
}
//----------------------------------------------------------------------------
// マーカーの設定
//----------------------------------------------------------------------------
void CMainWnd::SetMarkerPlay()
{
	bMarkerPlay = !bMarkerPlay;
	m_sound->SetABLoopA(bMarkerPlay);
	m_sound->SetABLoopB(bMarkerPlay);
	m_toolBar->SetMarkerPlayState(bMarkerPlay);
	SetCountLoop(FALSE, 0);
	m_menu->EnableItem(ID_COUNTLOOP, bMarkerPlay ? MFS_ENABLED : MFS_DISABLED);
	m_menu->EnableItem(ID_SLOOP, bMarkerPlay ? MFS_DISABLED : MFS_ENABLED);
	m_menu->EnableItem(ID_ALOOP, bMarkerPlay ? MFS_DISABLED : MFS_ENABLED);
	m_menu->EnableItem(ID_RANDOM, bMarkerPlay ? MFS_DISABLED : MFS_ENABLED);
	m_menu->CheckItem(ID_MARKERPLAY, bMarkerPlay ? MF_CHECKED : MF_UNCHECKED);
	SetPreviousNextMenuState();

	if(!bMarkerPlay) {
		SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
		SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, 0L);
	}
	m_timeSlider->SetStyle(bMarkerPlay ? (m_timeSlider->GetStyle()
		| TBS_ENABLESELRANGE) : (m_timeSlider->GetStyle()
		& ~TBS_ENABLESELRANGE));
	if(bMarkerPlay) {
		QWORD qwTime = m_sound->ChannelGetPosition();
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
		QWORD length = m_sound->ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0) {
			if(0 <= qwTime && qwTime < arrayMarker[0]) {
					bDone = TRUE;
					SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
					SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
						(LPARAM)(arrayMarker[0] / 100000));
					m_sound->SetLoopPosA(0);
					m_sound->SetLoopPosB(arrayMarker[0]);
			}
		}
		else {
			bDone = TRUE;
			SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
			SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
						(LPARAM)(length / 100000));
			m_sound->SetLoopPosA(0);
			m_sound->SetLoopPosB(length);
		}

		if(!bDone) {
			for(int i = 0; i < max; i++) {
				if(i + 1 < max) {
					if(arrayMarker[i] <= qwTime && qwTime < arrayMarker[i + 1])
					{
						bDone = TRUE;
						SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 
							(LPARAM)(arrayMarker[i] / 100000));
						SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
							(LPARAM)(arrayMarker[i + 1] / 100000));
						m_sound->SetLoopPosA(arrayMarker[i]);
						m_sound->SetLoopPosB(arrayMarker[i + 1]);
						break;
					}
				}
			}
		}

		if(!bDone) {
			if(arrayMarker[max - 1] <= qwTime && qwTime <= length) {
				bDone = TRUE;
				SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
					(LPARAM)(arrayMarker[max - 1] / 100000));
				SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
					(LPARAM)(length / 100000));
				m_sound->SetLoopPosA(arrayMarker[max - 1]);
				m_sound->SetLoopPosB(length);
			}
		}
	}
}
//----------------------------------------------------------------------------
// メトロノームの設定
//----------------------------------------------------------------------------
void CMainWnd::SetMetronome()
{
	metronomeWnd->Create();
}
//----------------------------------------------------------------------------
// メトロノームの設定
//----------------------------------------------------------------------------
void CMainWnd::SetMetronome(int nBpm)
{
	StopMetronome();
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	m_nBpm = nBpm;
	m_nInterval = 60000 / m_nBpm;
	SetTimer(IDT_METRONOME, 1);
}
//----------------------------------------------------------------------------
// メトロノームの停止
//----------------------------------------------------------------------------
void CMainWnd::StopMetronome()
{
	KillTimer(IDT_METRONOME);
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
}
//----------------------------------------------------------------------------
// 左右入れ替え
//----------------------------------------------------------------------------
void CMainWnd::SetChangeLR()
{
	BOOL bChangeLR = !m_menu->IsItemChecked(ID_CHANGELR);
	if(bChangeLR) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyRight(false);
		SetOnlyLeft(false);
	}
	m_sound->SetChangeLR(bChangeLR);
	m_menu->CheckItem(ID_CHANGELR, bChangeLR ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 左右入れ替え
//----------------------------------------------------------------------------
void CMainWnd::SetChangeLR(BOOL bChangeLR)
{
	if(bChangeLR) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyRight(false);
		SetOnlyLeft(false);
	}
	m_sound->SetChangeLR(bChangeLR);
	m_menu->CheckItem(ID_CHANGELR, bChangeLR ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 聴覚トレーニング
//----------------------------------------------------------------------------
void CMainWnd::SetEarTraining()
{
	BOOL bEarTraining = !m_menu->IsItemChecked(ID_EARTRAINING);
	m_menu->CheckItem(ID_EARTRAINING, bEarTraining ? MF_CHECKED : MF_UNCHECKED);
	if(bEarTraining) {
		if(m_menu->IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu->IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu->IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		OnTimer(IDT_EARTRAINING);
		SetTimer(IDT_EARTRAINING, 3000);
	}
	else {
		KillTimer(IDT_EARTRAINING);
		m_menu->OnEQFlatMenuSelected();
		m_panLabel->SetPan(0);
		m_panSlider->SetThumbPos(0);
		SetPan(0);
	}
}
//----------------------------------------------------------------------------
// 聴覚トレーニング
//----------------------------------------------------------------------------
void CMainWnd::SetEarTraining(BOOL bEarTraining)
{
	m_menu->CheckItem(ID_EARTRAINING, bEarTraining ? MF_CHECKED : MF_UNCHECKED);
	if(bEarTraining) {
		if(m_menu->IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu->IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu->IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		OnTimer(IDT_EARTRAINING);
		SetTimer(IDT_EARTRAINING, 3000);
	}
	else {
		KillTimer(IDT_EARTRAINING);
		m_menu->OnEQFlatMenuSelected();
	}
}
//----------------------------------------------------------------------------
// フォーカスを次のコントロール設定
//----------------------------------------------------------------------------
void CMainWnd::SetFocusNextControl()
{
	int nSelect = m_tab->GetCurrentFocus();
	HWND arHWnd[28] = {*m_timeSlider, m_speedLabel->GetEdit(), *m_speedSlider, 
		m_freqLabel->GetEdit(), *m_freqSlider, m_pitchLabel->GetEdit(),
		*m_pitchSlider, m_volumeLabel->GetEdit(), *m_volumeSlider,
		m_panLabel->GetEdit(), *m_panSlider, m_eq125Label->GetEdit(),
		*m_eq125Slider, m_eq250Label->GetEdit(), *m_eq250Slider,
		m_eq500Label->GetEdit(), *m_eq500Slider, m_eq1kLabel->GetEdit(),
		*m_eq1kSlider, m_eq2kLabel->GetEdit(), *m_eq2kSlider,
		m_eq4kLabel->GetEdit(), *m_eq4kSlider, m_eq8kLabel->GetEdit(),
		*m_eq8kSlider, m_eq16kLabel->GetEdit(), *m_eq16kSlider,
		*m_arrayList[nSelect]};

	HWND hFocusWnd = GetFocus();
	BOOL bHit = FALSE;
	int i = 0;
	for(; i < 28; i++) {
		if(arHWnd[i] == hFocusWnd) {
			bHit = TRUE;
			break;
		}
	}
	if(GetKeyState(VK_SHIFT) < 0) {
		if(!bHit) {
			for(int i = 27; i >= 0; i--) {
				if(IsWindowVisible(arHWnd[i])) {
					SetFocus(arHWnd[i]);
					break;
				}
			}
		}
		else {
			do {
				if(--i < 0) i = 27;
				if(IsWindowVisible(arHWnd[i])) {
					SetFocus(arHWnd[i]);
					break;
				}
			}
			while(arHWnd[i] != hFocusWnd);
		}
	}
	else {
		if(!bHit) {
			for(int i = 0; i < 28; i++) {
				if(IsWindowVisible(arHWnd[i])) {
					SetFocus(arHWnd[i]);
					break;
				}
			}
		}
		else {
			do {
				if(++i > 27) i = 0;
				if(IsWindowVisible(arHWnd[i]))
				{
					SetFocus(arHWnd[i]);
					break;
				}
			}
			while(arHWnd[i] != hFocusWnd);
		}
	}
}
//----------------------------------------------------------------------------
// 次のタブにフォーカスを設定
//----------------------------------------------------------------------------
void CMainWnd::SetFocusNextTab()
{
	int nFocus = m_tab->GetCurrentFocus();
	if(GetKeyState(VK_SHIFT) < 0) {
		nFocus--;
		if(nFocus < 0) nFocus = m_tab->GetItemCount() - 1;
	}
	else {
		nFocus++;
		if(nFocus >= m_tab->GetItemCount()) nFocus = 0;
	}
	m_tab->SetCurrentFocus(nFocus);
}
//----------------------------------------------------------------------------
// ノーマライズ
//----------------------------------------------------------------------------
void CMainWnd::SetNormalize()
{
	m_menu->UncheckPresetMenu();
	BOOL bNormalize = !m_menu->IsItemChecked(ID_NORMALIZE);
	m_sound->SetNormalize(bNormalize);
	m_menu->CheckItem(ID_NORMALIZE, bNormalize ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ノーマライズ
//----------------------------------------------------------------------------
void CMainWnd::SetNormalize(BOOL bNormalize)
{
	m_menu->UncheckPresetMenu();
	m_sound->SetNormalize(bNormalize);
	m_menu->CheckItem(ID_NORMALIZE, bNormalize ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 歌へたモード
//----------------------------------------------------------------------------
void CMainWnd::SetNoSense()
{
	m_menu->UncheckPresetMenu();
	BOOL bNoSense = !m_menu->IsItemChecked(ID_NOSENSE);
	m_menu->CheckItem(ID_NOSENSE, bNoSense ? MF_CHECKED : MF_UNCHECKED);
	if(bNoSense) {
		if(m_menu->IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu->IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu->IsItemChecked(ID_BASSCOPY)) m_menu->OnBassCopyMenuSelected();
		if(m_menu->IsItemChecked(ID_CYMBALCOPY))
			m_menu->OnDrumsCopyMenuSelected();
		m_nLastDecimalDigit_pitch = m_pitchSlider->GetDecimalDigit();
		m_nLastDecimalDigit_speed = m_speedSlider->GetDecimalDigit();
		m_menu->OnSetPitchDecimal2MenuSelected();
		m_menu->OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel->SetPitch(0.0);
		m_pitchSlider->SetThumbPos(0, TRUE);
		SetPitch(0.0);
		double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
		m_speedLabel->SetSpeed(100.0);
		m_speedSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetSpeed(100.0);
		SetTimer(IDT_NOSENSE, 80);
	}
	else {
		KillTimer(IDT_NOSENSE);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		if(m_nLastDecimalDigit_pitch == 0)
			m_menu->OnSetPitchDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 1)
			m_menu->OnSetPitchDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 2)
			m_menu->OnSetPitchDecimal2MenuSelected();
		if(m_nLastDecimalDigit_speed == 0)
			m_menu->OnSetSpeedDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_speed == 1)
			m_menu->OnSetSpeedDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_speed == 2)
			m_menu->OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel->SetPitch(0.0);
		m_pitchSlider->SetThumbPos(0, TRUE);
		SetPitch(0.0);
		double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
		m_speedLabel->SetSpeed(100.0);
		m_speedSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetSpeed(100.0);
	}
}
//----------------------------------------------------------------------------
// 歌へたモード
//----------------------------------------------------------------------------
void CMainWnd::SetNoSense(BOOL bNoSense)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_NOSENSE, bNoSense ? MF_CHECKED : MF_UNCHECKED);
	if(bNoSense) {
		if(m_menu->IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu->IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu->IsItemChecked(ID_BASSCOPY)) m_menu->OnBassCopyMenuSelected();
		if(m_menu->IsItemChecked(ID_CYMBALCOPY))
			m_menu->OnDrumsCopyMenuSelected();
		m_nLastDecimalDigit_pitch = m_pitchSlider->GetDecimalDigit();
		m_nLastDecimalDigit_speed = m_speedSlider->GetDecimalDigit();
		m_menu->OnSetPitchDecimal2MenuSelected();
		m_menu->OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel->SetPitch(0.0);
		m_pitchSlider->SetThumbPos(0, TRUE);
		SetPitch(0.0);
		double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
		m_speedLabel->SetSpeed(100.0);
		m_speedSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetSpeed(100.0);
		SetTimer(IDT_NOSENSE, 80);
	}
	else {
		KillTimer(IDT_NOSENSE);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		if(m_nLastDecimalDigit_pitch == 0)
			m_menu->OnSetPitchDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 1)
			m_menu->OnSetPitchDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 2)
			m_menu->OnSetPitchDecimal2MenuSelected();
		if(m_nLastDecimalDigit_speed == 0)
			m_menu->OnSetSpeedDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_speed == 1)
			m_menu->OnSetSpeedDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_speed == 2)
			m_menu->OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel->SetPitch(0.0);
		m_pitchSlider->SetThumbPos(0, TRUE);
		SetPitch(0.0);
		double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
		m_speedLabel->SetSpeed(100.0);
		m_speedSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetSpeed(100.0);
	}
}
//----------------------------------------------------------------------------
// 次のマーカーへ
//----------------------------------------------------------------------------
void CMainWnd::SetNextMarker()
{
	if(bMarkerPlay) {
		QWORD qwTime = m_sound->GetLoopPosA();
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
		QWORD length = m_sound->ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0 && qwTime == 0) {
			bDone = TRUE;
			SetTime(arrayMarker[0]);
			return;
		}

		for(int i = 0; i < max - 1; i++) {
			if(qwTime == arrayMarker[i]) {
				bDone = TRUE;
				SetTime(arrayMarker[i + 1]);
				return;
			}
		}
	}
}
//----------------------------------------------------------------------------
// 左のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyLeft()
{
	m_menu->UncheckPresetMenu();
	BOOL bOnlyLeft = !m_menu->IsItemChecked(ID_ONLYLEFT);
	if(bOnlyLeft) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound->SetOnlyLeft(bOnlyLeft);
	m_menu->CheckItem(ID_ONLYLEFT, bOnlyLeft ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 左のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyLeft(BOOL bOnlyLeft)
{
	m_menu->UncheckPresetMenu();
	if(bOnlyLeft) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetChangeLR(false);
		SetOnlyRight(false);
	}
	m_sound->SetOnlyLeft(bOnlyLeft);
	m_menu->CheckItem(ID_ONLYLEFT, bOnlyLeft ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 右のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyRight()
{
	m_menu->UncheckPresetMenu();
	BOOL bOnlyRight = !m_menu->IsItemChecked(ID_ONLYRIGHT);
	if(bOnlyRight) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetChangeLR(false);
	}
	m_sound->SetOnlyRight(bOnlyRight);
	m_menu->CheckItem(ID_ONLYRIGHT, bOnlyRight ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 右のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyRight(BOOL bOnlyRight)
{
	m_menu->UncheckPresetMenu();
	if(bOnlyRight) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetChangeLR(false);
	}
	m_sound->SetOnlyRight(bOnlyRight);
	m_menu->CheckItem(ID_ONLYRIGHT, bOnlyRight ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// グローバルホットキーの設定
//----------------------------------------------------------------------------
void CMainWnd::SetOutKeySetting()
{
	if(!(HWND)*outKeySettingWnd) outKeySettingWnd->Create();
	EnableWindow(m_hWnd, FALSE);
	outKeySettingWnd->Show(SW_SHOW);
	outKeySettingWnd->Update();
}
//----------------------------------------------------------------------------
// 再生リストの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPlayListVisible()
{
	BOOL bListVisible = !m_menu->IsItemChecked(ID_PLAYLIST);

	int nCmdShow = bListVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bListVisible ? MF_CHECKED : MF_UNCHECKED;
	m_divider5->Show(nCmdShow);
	m_tab->Show(nCmdShow);
	int nSelect = m_tab->GetCurrentFocus();
	m_arrayList[nSelect]->Show(nCmdShow);
	m_menu->CheckItem(ID_PLAYLIST, uCheck);
	m_toolBar->CheckButton(ID_PLAYLIST, bListVisible);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// プリセットの設定
//----------------------------------------------------------------------------
void CMainWnd::SetPreset(int n)
{
	tstring initFilePath = m_rApp.GetFilePath() + _T("Setting.ini");

	TCHAR section[255];
	TCHAR buf[255];
	_stprintf_s(section, _T("Preset%d"), n);
	GetPrivateProfileString(section, _T("Name"), _T(""), buf, 255,
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) == 0) return;

	GetPrivateProfileString(section, _T("Speed"), _T(""), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		double speed = _ttof(buf);
		double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
		m_speedLabel->SetSpeed(speed);
		m_speedSlider->SetThumbPos((LONG)(speed * dCalc), TRUE);
		SetSpeed(speed);
	}
	GetPrivateProfileString(section, _T("Frequency"), _T(""), buf, 
		255, initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		double freq = _ttof(buf);
		double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
		m_freqLabel->SetFreq(freq);
		m_freqSlider->SetThumbPos((LONG)(freq * dCalc), TRUE);
		SetFreq(freq);
	}
	GetPrivateProfileString(section, _T("Pitch"), _T(""), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		double pitch = _ttof(buf);
		double dCalc = pow(10.0, m_pitchSlider->GetDecimalDigit());
		m_pitchLabel->SetPitch(pitch);
		m_pitchSlider->SetThumbPos((LONG)(pitch * dCalc), TRUE);
		SetPitch(pitch);
	}
	GetPrivateProfileString(section, _T("Volume"), _T(""), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int volume = _ttoi(buf);
		m_volumeLabel->SetVolume((double)(volume / 10.0));
		m_volumeSlider->SetThumbPos((LONG)volume, TRUE);
		SetVolume((double)(volume / 10.0));
	}
	GetPrivateProfileString(section, _T("Pan"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int pan = _ttoi(buf);
		m_panLabel->SetPan(pan);
		m_panSlider->SetThumbPos((LONG)pan, TRUE);
		SetPan(pan);
	}
	GetPrivateProfileString(section, _T("EQ20"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq20Label->SetEQ20(eq);
		m_eq20Slider->SetThumbPos(eq);
		SetEQ20((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ25"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq25Label->SetEQ25(eq);
		m_eq25Slider->SetThumbPos(eq);
		SetEQ25((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ31.5"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq31_5Label->SetEQ31_5(eq);
		m_eq31_5Slider->SetThumbPos(eq);
		SetEQ31_5((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ40"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq40Label->SetEQ40(eq);
		m_eq40Slider->SetThumbPos(eq);
		SetEQ40((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ50"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq50Label->SetEQ50(eq);
		m_eq50Slider->SetThumbPos(eq);
		SetEQ50((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ63"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq63Label->SetEQ63(eq);
		m_eq63Slider->SetThumbPos(eq);
		SetEQ63((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ80"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq80Label->SetEQ80(eq);
		m_eq80Slider->SetThumbPos(eq);
		SetEQ80((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ100"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq100Label->SetEQ100(eq);
		m_eq100Slider->SetThumbPos(eq);
		SetEQ100((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ125"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq125Label->SetEQ125(eq);
		m_eq125Slider->SetThumbPos(eq);
		SetEQ125((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ160"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq160Label->SetEQ160(eq);
		m_eq160Slider->SetThumbPos(eq);
		SetEQ160((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ200"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq200Label->SetEQ200(eq);
		m_eq200Slider->SetThumbPos(eq);
		SetEQ200((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ250"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq250Label->SetEQ250(eq);
		m_eq250Slider->SetThumbPos(eq);
		SetEQ250((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ315"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq315Label->SetEQ315(eq);
		m_eq315Slider->SetThumbPos(eq);
		SetEQ315((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ400"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq400Label->SetEQ400(eq);
		m_eq400Slider->SetThumbPos(eq);
		SetEQ400((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ500"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq500Label->SetEQ500(eq);
		m_eq500Slider->SetThumbPos(eq);
		SetEQ500((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ630"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq630Label->SetEQ630(eq);
		m_eq630Slider->SetThumbPos(eq);
		SetEQ630((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ800"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq800Label->SetEQ800(eq);
		m_eq800Slider->SetThumbPos(eq);
		SetEQ800((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ1K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq1kLabel->SetEQ1K(eq);
		m_eq1kSlider->SetThumbPos(eq);
		SetEQ1K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ1.25K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq1_25kLabel->SetEQ1_25K(eq);
		m_eq1_25kSlider->SetThumbPos(eq);
		SetEQ1_25K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ1.6K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq1_6kLabel->SetEQ1_6K(eq);
		m_eq1_6kSlider->SetThumbPos(eq);
		SetEQ1_6K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ2K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq2kLabel->SetEQ2K(eq);
		m_eq2kSlider->SetThumbPos(eq);
		SetEQ2K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ2.5K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq2_5kLabel->SetEQ2_5K(eq);
		m_eq2_5kSlider->SetThumbPos(eq);
		SetEQ2_5K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ3.15K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq3_15kLabel->SetEQ3_15K(eq);
		m_eq3_15kSlider->SetThumbPos(eq);
		SetEQ3_15K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ4K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq4kLabel->SetEQ4K(eq);
		m_eq4kSlider->SetThumbPos(eq);
		SetEQ4K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ5K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq5kLabel->SetEQ5K(eq);
		m_eq5kSlider->SetThumbPos(eq);
		SetEQ5K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ6.3K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq6_3kLabel->SetEQ6_3K(eq);
		m_eq6_3kSlider->SetThumbPos(eq);
		SetEQ6_3K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ8K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq8kLabel->SetEQ8K(eq);
		m_eq8kSlider->SetThumbPos(eq);
		SetEQ8K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ10K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq10kLabel->SetEQ10K(eq);
		m_eq10kSlider->SetThumbPos(eq);
		SetEQ10K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ12.5K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq12_5kLabel->SetEQ12_5K(eq);
		m_eq12_5kSlider->SetThumbPos(eq);
		SetEQ12_5K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ16K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq16kLabel->SetEQ16K(eq);
		m_eq16kSlider->SetThumbPos(eq);
		SetEQ16K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("EQ20K"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if(_tcsicmp(buf, _T("")) != 0) {
		int eq = _ttoi(buf);
		m_eq20kLabel->SetEQ20K(eq);
		m_eq20kSlider->SetThumbPos(eq);
		SetEQ20K((LONG)eq);
	}
	GetPrivateProfileString(section, _T("ReverbDefault"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_REVERB_DEFAULT))
		m_menu->OnReverbDefaultMenuSelected();

	GetPrivateProfileString(section, _T("ReverbCustomize"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_REVERB_CUSTOMIZE)) {
		TCHAR chGain[255], chRevMix[255], chRevTime[255], chHigh[255];
		GetPrivateProfileString(section, _T("ReverbCustomize_Gain"), _T("0"),
			chGain, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ReverbCustomize_RevMix"), _T("0"),
			chRevMix, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ReverbCustomize_RevTime"), _T("0"),
			chRevTime, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ReverbCustomize_High"), _T("0"),
			chHigh, 255, initFilePath.c_str());
		m_menu->SetReverb((float)_ttof(chGain), (float)_ttof(chRevMix),
						 (float)_ttof(chRevTime), (float)_ttof(chHigh),
						 ID_REVERB_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("3DReverbDefault"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_DEFAULT))
		m_menu->On3DReverbDefaultMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbPaddedCell"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PADDEDCELL))
		m_menu->On3DReverbPaddedCellMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbRoom"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_ROOM))
		m_menu->On3DReverbRoomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbBathRoom"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_BATHROOM))
		m_menu->On3DReverbBathroomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbLivingRoom"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_LIVINGROOM))
		m_menu->On3DReverbLivingRoomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbStoneRoom"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_STONEROOM))
		m_menu->On3DReverbStoneRoomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbAuditorium"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_AUDITORIUM))
		m_menu->On3DReverbAuditoriumMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbConcertHall"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CONCERTHALL))
		m_menu->On3DReverbConcertHallMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbCave"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CAVE))
		m_menu->On3DReverbCaveMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbArena"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_ARENA))
		m_menu->On3DReverbArenaMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbHangar"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_HANGAR))
		m_menu->On3DReverbHangarMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbCarpetedHallway"), _T("0"),
		buf, 255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CARPETEDHALLWAY))
		m_menu->On3DReverbCarpetedHallwayMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbHallway"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_HALLWAY))
		m_menu->On3DReverbHallwayMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbStoneCorridor"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_STONECORRIDOR))
		m_menu->On3DReverbStoneCorridorMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbAlley"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_ALLEY))
		m_menu->On3DReverbAlleyMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbForest"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_FOREST))
		m_menu->On3DReverbForestMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbCity"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CITY))
		m_menu->On3DReverbCityMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbMountains"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_MOUNTAINS))
		m_menu->On3DReverbMountainsMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbQuarry"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_QUARRY))
		m_menu->On3DReverbQuarryMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbPlain"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PLAIN))
		m_menu->On3DReverbPlainMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbParkingLot"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PARKINGLOT))
		m_menu->On3DReverbParkingLotMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbSewerPipe"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_SEWERPIPE))
		m_menu->On3DReverbSewerPipeMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbUnderWater"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_UNDERWATER))
		m_menu->On3DReverbUnderwaterMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbSmallRoom"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_SMALLROOM))
		m_menu->On3DReverbSmallRoomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbMediumRoom"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_MEDIUMROOM))
		m_menu->On3DReverbMediumRoomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbLargeRoom"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_LARGEROOM))
		m_menu->On3DReverbLargeRoomMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbMediumHall"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_MEDIUMHALL))
		m_menu->On3DReverbMediumHallMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbLargeHall"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_LARGEHALL))
		m_menu->On3DReverbLargeHallMenuSelected();
	GetPrivateProfileString(section, _T("3DReverbPlate"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_PLATE))
		m_menu->On3DReverbPlateMenuSelected();

	GetPrivateProfileString(section, _T("3DReverbCustomize"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_3DREVERB_CUSTOMIZE)) {
		TCHAR chRoom[255], chRoomHF[255], chRoomRolloffFactor[255],
			  chDecayTime[255], chDecayHFRatio[255], chReflections[255],
			  chReflectionsDelay[255], chReverb[255], chReverbDelay[255],
			  chDiffusion[255], chDensity[255], chHFReference[255];
		GetPrivateProfileString(section, _T("3DReverbCustomize_Room"),
			_T("0"), chRoom, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("3DReverbCustomize_RoomHF"),
			_T("0"), chRoomHF, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("3DReverbCustomize_RoomRolloffFactor"), _T("0"),
			chRoomRolloffFactor, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("3DReverbCustomize_DecayTime"),
			_T("0"), chDecayTime, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("3DReverbCustomize_DecayHFRatio"), _T("0"), chDecayHFRatio, 255,
			initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("3DReverbCustomize_Reflections"), _T("0"), chReflections, 255,
			initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("3DReverbCustomize_ReflectionsDelay"), _T("0"),
			chReflectionsDelay, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("3DReverbCustomize_Reverb"),
			_T("0"), chReverb, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("3DReverbCustomize_ReverbDelay"), _T("0"), chReverbDelay, 255,
			initFilePath.c_str());
		GetPrivateProfileString(section, _T("3DReverbCustomize_Diffusion"),
			_T("0"), chDiffusion, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("3DReverbCustomize_Density"),
			_T("0"), chDensity, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("3DReverbCustomize_HFReference"), _T("0"), chHFReference, 255,
			initFilePath.c_str());
		m_menu->Set3DReverb(_ttoi(chRoom), _ttoi(chRoomHF),
			(float)_ttof(chRoomRolloffFactor), (float)_ttof(chDecayTime),
			(float)_ttof(chDecayHFRatio), _ttoi(chReflections),
			(float)_ttof(chReflectionsDelay), _ttoi(chReverb),
			(float)_ttof(chReverbDelay), (float)_ttof(chDiffusion),
			(float)_ttof(chDensity), (float)_ttof(chHFReference),
			ID_3DREVERB_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("DelayDefault"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_DEFAULT))
		m_menu->OnDelayDefaultMenuSelected();
	GetPrivateProfileString(section, _T("DelayShort"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_SHORT))
		m_menu->OnDelayShortMenuSelected();
	GetPrivateProfileString(section, _T("DelayMedium"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_MEDIUM))
		m_menu->OnDelayMediumMenuSelected();
	GetPrivateProfileString(section, _T("DelayLong"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_LONG))
		m_menu->OnDelayLongMenuSelected();
	GetPrivateProfileString(section, _T("DelayStereoShort"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOSHORT))
		m_menu->OnDelayStereoShortMenuSelected();
	GetPrivateProfileString(section, _T("DelayStereoMedium"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOMEDIUM))
		m_menu->OnDelayStereoMediumMenuSelected();
	GetPrivateProfileString(section, _T("DelayStereoLong"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOLONG))
		m_menu->OnDelayStereoLongMenuSelected();
	GetPrivateProfileString(section, _T("DelayMountain"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_MOUNTAIN))
		m_menu->OnDelayMountainMenuSelected();
	GetPrivateProfileString(section, _T("DelayBig"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_BIG))
		m_menu->OnDelayBigMenuSelected();
	GetPrivateProfileString(section, _T("DelayStereoBig"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_STEREOBIG))
		m_menu->OnDelayStereoBigMenuSelected();
	GetPrivateProfileString(section, _T("DelayDoubling"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_DOUBLING))
		m_menu->OnDelayDoublingMenuSelected();
	GetPrivateProfileString(section, _T("DelayDoubleKick"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_DOUBLEKICK))
		m_menu->OnDelayDoubleKickMenuSelected();

	GetPrivateProfileString(section, _T("DelayCustomize"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DELAY_CUSTOMIZE)) {
		TCHAR chWetDryMix[255], chFeedback[255], chLeftDelay[255],
			  chRightDelay[255], chPanDelay[255];
		GetPrivateProfileString(section, _T("DelayCustomize_WetDryMix"),
			_T("0"), chWetDryMix, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("DelayCustomize_Feedback"),
			_T("0"), chFeedback, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("DelayCustomize_LeftDelay"),
			_T("0"), chLeftDelay, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("DelayCustomize_RightDelay"), _T("0"), chRightDelay, 255,
			initFilePath.c_str());
		GetPrivateProfileString(section, _T("DelayCustomize_PanDelay"),
			_T("0"), chPanDelay, 255, initFilePath.c_str());
		m_menu->SetDelay((float)_ttof(chWetDryMix), (float)_ttof(chFeedback),
			(float)_ttof(chLeftDelay), (float)_ttof(chRightDelay),
			(BOOL)_ttoi(chPanDelay), ID_DELAY_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("ChorusDefault"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CHORUS_DEFAULT))
		m_menu->OnChorusDefaultMenuSelected();

	GetPrivateProfileString(section, _T("ChorusCustomize"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CHORUS_CUSTOMIZE)) {
		TCHAR chWetDryMix[255], chDepth[255], chFeedback[255], chFrequency[255],
			  chWaveForm[255], chDelay[255];
		GetPrivateProfileString(section, _T("ChorusCustomize_WetDryMix"),
			_T("0"), chWetDryMix, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ChorusCustomize_Depth"),
			_T("0"), chDepth, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ChorusCustomize_Feedback"),
			_T("0"), chFeedback, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ChorusCustomize_Frequency"),
			_T("0"), chFrequency, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ChorusCustomize_Waveform"),
			_T("0"), chWaveForm, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("ChorusCustomize_Delay"),
			_T("0"), chDelay, 255, initFilePath.c_str());
		m_menu->SetChorus((float)_ttof(chWetDryMix), (float)_ttof(chDepth),
			(float)_ttof(chFeedback), (float)_ttof(chFrequency),
			(DWORD)_ttoi(chWaveForm), (float)_ttof(chDelay),
			BASS_DX8_PHASE_90, ID_CHORUS_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("CompressorDefault"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_COMPRESSOR_DEFAULT))
		m_menu->OnCompressorDefaultMenuSelected();

	GetPrivateProfileString(section, _T("CompressorCustomize"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_COMPRESSOR_CUSTOMIZE)) {
		TCHAR chGain[255], chAttack[255], chRelease[255], chThreshold[255],
			  chRatio[255], chPredelay[255];
		GetPrivateProfileString(section, _T("CompressorCustomize_Gain"),
			_T("0"), chGain, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("CompressorCustomize_Attack"),
			_T("0"), chAttack, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("CompressorCustomize_Release"),
			_T("0"), chRelease, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("CompressorCustomize_Threshold"),
			_T("0"), chThreshold, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("CompressorCustomize_Ratio"),
			_T("0"), chRatio, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("CompressorCustomize_Predelay"),
			_T("0"), chPredelay, 255, initFilePath.c_str());
		m_menu->SetCompressor((float)_ttof(chGain), (float)_ttof(chAttack),
			(float)_ttof(chRelease), (float)_ttof(chThreshold),
			(float)_ttof(chRatio), (float)_ttof(chPredelay),
			ID_COMPRESSOR_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("FlangerDefault"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_FLANGER_DEFAULT))
		m_menu->OnFlangerDefaultMenuSelected();

	GetPrivateProfileString(section, _T("FlangerCustomize"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_FLANGER_CUSTOMIZE)) {
		TCHAR chWetDryMix[255], chDepth[255], chFeedback[255], chFrequency[255],
			  chWaveForm[255], chDelay[255];
		GetPrivateProfileString(section, _T("FlangerCustomize_WetDryMix"),
			_T("0"), chWetDryMix, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("FlangerCustomize_Depth"),
			_T("0"), chDepth, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("FlangerCustomize_Feedback"),
			_T("0"), chFeedback, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("FlangerCustomize_Frequency"),
			_T("0"), chFrequency, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("FlangerCustomize_Waveform"),
			_T("0"), chWaveForm, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("FlangerCustomize_Delay"),
			_T("0"), chDelay, 255, initFilePath.c_str());
		m_menu->SetFlanger((float)_ttof(chWetDryMix), (float)_ttof(chDepth),
			(float)_ttof(chFeedback), (float)_ttof(chFrequency),
			(DWORD)_ttoi(chWaveForm), (float)_ttof(chDelay),
			BASS_DX8_PHASE_ZERO, ID_FLANGER_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("GargleDefault"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_GARGLE_DEFAULT))
		m_menu->OnGargleDefaultMenuSelected();
	GetPrivateProfileString(section, _T("GargleCustomize"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_GARGLE_CUSTOMIZE)) {
		TCHAR chRateHz[255], chWaveShape[255];
		GetPrivateProfileString(section, _T("GargleCustomize_RateHz"),
			_T("0"), chRateHz, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("GargleCustomize_WaveShape"),
			_T("0"), chWaveShape, 255, initFilePath.c_str());
		m_menu->SetGargle((DWORD)_ttoi(chRateHz), (DWORD)_ttoi(chWaveShape),
			ID_GARGLE_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("DistortionDefault"), _T("0"), buf, 255,
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DISTORTION_DEFAULT))
		m_menu->OnDistortionDefaultMenuSelected();

	GetPrivateProfileString(section, _T("DistortionCustomize"), _T("0"), buf,
		255, initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_DISTORTION_CUSTOMIZE)) {
		TCHAR chGain[255], chEdge[255], chPostEQCenterFrequency[255],
			  chPostEQBandwidth[255], chPreLowpassCutoff[255];
		GetPrivateProfileString(section, _T("DistortionCustomize_Gain"),
			_T("0"), chGain, 255, initFilePath.c_str());
		GetPrivateProfileString(section, _T("DistortionCustomize_Edge"),
			_T("0"), chEdge, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("DistortionCustomize_PostEQCenterFrequency"),
			_T("0"), chPostEQCenterFrequency, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("DistortionCustomize_PostEQBandwidth"),
			_T("0"), chPostEQBandwidth, 255, initFilePath.c_str());
		GetPrivateProfileString(section,
			_T("DistortionCustomize_PreLowpassCutoff"), _T("0"),
			chPreLowpassCutoff, 255, initFilePath.c_str());
		m_menu->SetDistortion((float)_ttof(chGain), (float)_ttof(chEdge),
			(float)_ttof(chPostEQCenterFrequency),
			(float)_ttof(chPostEQBandwidth),
			(float)_ttof(chPreLowpassCutoff), ID_DISTORTION_CUSTOMIZE);
	}

	GetPrivateProfileString(section, _T("Normalize"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_NORMALIZE))
		SetNormalize();
	GetPrivateProfileString(section, _T("VocalCancel"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_VOCALCANCEL))
		SetVocalCancel();
	GetPrivateProfileString(section, _T("Reverse"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_REVERSE))
		SetReverse();
	GetPrivateProfileString(section, _T("Record"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_RECORD))
		SetRecord();
	GetPrivateProfileString(section, _T("LowBattery"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_LOWBATTERY))
		SetLowBattery();
	GetPrivateProfileString(section, _T("NoSense"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_NOSENSE))
		SetNoSense();
	GetPrivateProfileString(section, _T("BassCopy"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_BASSCOPY))
		m_menu->OnBassCopyMenuSelected();
	GetPrivateProfileString(section, _T("DrumsCopy"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CYMBALCOPY))
		m_menu->OnDrumsCopyMenuSelected();
	GetPrivateProfileString(section, _T("EarTraining"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_EARTRAINING))
		SetEarTraining();
	GetPrivateProfileString(section, _T("Monoral"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_MONORAL))
		SetMonoral();
	GetPrivateProfileString(section, _T("OnlyLeft"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_ONLYLEFT))
		SetOnlyLeft();
	GetPrivateProfileString(section, _T("OnlyRight"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_ONLYRIGHT))
		SetOnlyRight();
	GetPrivateProfileString(section, _T("ChangeLR"), _T("0"), buf, 255, 
		initFilePath.c_str());
	if((BOOL)_ttoi(buf) && !m_menu->IsItemChecked(ID_CHANGELR))
		SetChangeLR();
}
//----------------------------------------------------------------------------
// 前へ・次へメニューの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPreviousNextMenuState()
{
	if(m_sound->GetCurFileNum() <= 0) return;

	// 前へメニューの使用可・不可を設定
	if(m_sound->GetNSFCount() > 0)
		m_menu->EnableItem(ID_PREV, MFS_ENABLED);
	else if(m_menu->IsItemChecked(ID_RANDOM)) {
		if(!m_menu->IsItemChecked(ID_ALOOP)
			&& m_arrayList[nCurPlayTab]->GetMaxPlayOrder() == 1)
			m_menu->EnableItem(ID_PREV, MFS_DISABLED);
		else m_menu->EnableItem(ID_PREV, MFS_ENABLED);
	}
	else {
		if(!bMarkerPlay && !m_menu->IsItemChecked(ID_ALOOP)
			&& m_sound->GetCurFileNum() == 1)
			m_menu->EnableItem(ID_PREV, MFS_DISABLED);
		else m_menu->EnableItem(ID_PREV, MFS_ENABLED);
	}

	// 次へメニューの使用可・不可を設定
	if(m_sound->GetNSFCount() > 0)
		m_menu->EnableItem(ID_NEXT, MFS_ENABLED);
	else if(m_menu->IsItemChecked(ID_RANDOM)) {
		if(!m_menu->IsItemChecked(ID_ALOOP)
			&& m_arrayList[nCurPlayTab]->GetMaxPlayOrder()
			== m_arrayList[nCurPlayTab]->GetItemCount())
			m_menu->EnableItem(ID_NEXT, MFS_DISABLED);
		else m_menu->EnableItem(ID_NEXT, MFS_ENABLED);
	}
	else {
		if(!bMarkerPlay && !m_menu->IsItemChecked(ID_ALOOP)
			&& m_sound->GetCurFileNum()
			== m_arrayList[nCurPlayTab]->GetItemCount())
			m_menu->EnableItem(ID_NEXT, MFS_DISABLED);
		else m_menu->EnableItem(ID_NEXT, MFS_ENABLED);
	}
}
//----------------------------------------------------------------------------
// 前のマーカーへ
//----------------------------------------------------------------------------
void CMainWnd::SetPrevMarker()
{
	if(bMarkerPlay) {
		QWORD qwTime = m_sound->GetLoopPosA();
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
		QWORD length = m_sound->ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0 && qwTime == arrayMarker[0]) {
			bDone = TRUE;
			SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
			SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
				(LPARAM)(arrayMarker[0] / 100000));
			SetTime(0);
			return;
		}

		for(int i = 1; i < max; i++) {
			if(qwTime == arrayMarker[i]) {
				bDone = TRUE;
				SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
					(LPARAM)(arrayMarker[i - 1] / 100000));
				SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
					(LPARAM)(arrayMarker[i] / 100000));
				SetTime(arrayMarker[i - 1]);
				return;
			}
		}
	}
}
//----------------------------------------------------------------------------
// ランダム再生の設定
//----------------------------------------------------------------------------
void CMainWnd::SetRandom()
{
	BOOL bRandom = !m_menu->IsItemChecked(ID_RANDOM);
	m_menu->CheckItem(ID_RANDOM, bRandom ? MF_CHECKED : MF_UNCHECKED);
	m_toolBar->CheckButton(ID_RANDOM, bRandom);

	m_arrayList[nCurPlayTab]->ClearPlayOrder();
	if(bRandom)
		m_arrayList[nCurPlayTab]->SetPlayOrder(m_sound->GetCurFileNum()-1);

	SetPreviousNextMenuState();
}
//----------------------------------------------------------------------------
// リバーブをかける
//----------------------------------------------------------------------------
void CMainWnd::SetReverb(BOOL bReverb)
{
	m_menu->UncheckPresetMenu();
	this->bReverb = bReverb;
	m_sound->SetReverb(bReverb);
}
//----------------------------------------------------------------------------
// ３Ｄリバーブをかける
//----------------------------------------------------------------------------
void CMainWnd::Set3DReverb(BOOL b3DReverb)
{
	m_menu->UncheckPresetMenu();
	this->b3DReverb = b3DReverb;
	m_sound->Set3DReverb(b3DReverb);
}
//----------------------------------------------------------------------------
// ディレイをかける
//----------------------------------------------------------------------------
void CMainWnd::SetDelay(BOOL bDelay)
{
	m_menu->UncheckPresetMenu();
	this->bDelay = bDelay;
	m_sound->SetDelay(bDelay);
}
//----------------------------------------------------------------------------
// コーラスをかける
//----------------------------------------------------------------------------
void CMainWnd::SetChorus(BOOL bChorus)
{
	m_menu->UncheckPresetMenu();
	this->bChorus = bChorus;
	m_sound->SetChorus(bChorus);
}
//----------------------------------------------------------------------------
// コンプレッサーをかける
//----------------------------------------------------------------------------
void CMainWnd::SetCompressor(BOOL bCompressor)
{
	m_menu->UncheckPresetMenu();
	this->bCompressor = bCompressor;
	m_sound->SetCompressor(bCompressor);
}
//----------------------------------------------------------------------------
// フランジャーをかける
//----------------------------------------------------------------------------
void CMainWnd::SetFlanger(BOOL bFlanger)
{
	m_menu->UncheckPresetMenu();
	this->bFlanger = bFlanger;
	m_sound->SetFlanger(bFlanger);
}
//----------------------------------------------------------------------------
// ガーグルをかける
//----------------------------------------------------------------------------
void CMainWnd::SetGargle(BOOL bGargle)
{
	m_menu->UncheckPresetMenu();
	this->bGargle = bGargle;
	m_sound->SetGargle(bGargle);
}
//----------------------------------------------------------------------------
// ディストーションをかける
//----------------------------------------------------------------------------
void CMainWnd::SetDistortion(BOOL bDistortion)
{
	m_menu->UncheckPresetMenu();
	this->bDistortion = bDistortion;
	m_sound->SetDistortion(bDistortion);
}
//----------------------------------------------------------------------------
// LAMEコマンドラインオプションの設定
//----------------------------------------------------------------------------
void CMainWnd::SetLAMECommandLine(tstring strLAMECommandLine)
{
	m_strLAMECommandLine = strLAMECommandLine;
}
//----------------------------------------------------------------------------
// 電池切れ
//----------------------------------------------------------------------------
void CMainWnd::SetLowBattery()
{
	m_menu->UncheckPresetMenu();
	BOOL bLowBattery = !m_menu->IsItemChecked(ID_LOWBATTERY);
	m_menu->CheckItem(ID_LOWBATTERY, bLowBattery ? MF_CHECKED : MF_UNCHECKED);
	if(bLowBattery) {
		if(m_menu->IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu->IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_nLastDecimalDigit_freq = m_freqSlider->GetDecimalDigit();
		m_menu->OnSetFreqDecimal2MenuSelected();
		if(!m_menu->IsItemChecked(ID_DISTORTION_DEFAULT))
			m_menu->OnDistortionDefaultMenuSelected();
		m_menu->OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_LOWBATTERY, 20);
	}
	else {
		KillTimer(IDT_LOWBATTERY);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_menu->OnEQFlatMenuSelected();
		if(m_menu->IsItemChecked(ID_DISTORTION_DEFAULT))
			m_menu->OnDistortionDefaultMenuSelected();
		if(m_nLastDecimalDigit_freq == 0)
			m_menu->OnSetFreqDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_freq == 1)
			m_menu->OnSetFreqDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_freq == 2)
			m_menu->OnSetFreqDecimal2MenuSelected();
		double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
		m_freqLabel->SetFreq(100.0);
		m_freqSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// 電池切れ
//----------------------------------------------------------------------------
void CMainWnd::SetLowBattery(BOOL bLowBattery)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_LOWBATTERY, bLowBattery ? MF_CHECKED : MF_UNCHECKED);
	if(bLowBattery) {
		if(m_menu->IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu->IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_nLastDecimalDigit_freq = m_freqSlider->GetDecimalDigit();
		m_menu->OnSetFreqDecimal2MenuSelected();
		if(!m_menu->IsItemChecked(ID_DISTORTION_DEFAULT))
			m_menu->OnDistortionDefaultMenuSelected();
		m_menu->OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_LOWBATTERY, 20);
	}
	else {
		KillTimer(IDT_LOWBATTERY);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_menu->OnEQFlatMenuSelected();
		if(m_menu->IsItemChecked(ID_DISTORTION_DEFAULT))
			m_menu->OnDistortionDefaultMenuSelected();
		if(m_nLastDecimalDigit_freq == 0)
			m_menu->OnSetFreqDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_freq == 1)
			m_menu->OnSetFreqDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_freq == 2)
			m_menu->OnSetFreqDecimal2MenuSelected();
		double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
		m_freqLabel->SetFreq(100.0);
		m_freqSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// 逆回転再生
//----------------------------------------------------------------------------
void CMainWnd::SetReverse()
{
	m_menu->UncheckPresetMenu();
	BOOL bReverse = !m_menu->IsItemChecked(ID_REVERSE);
	if(bReverse) {
		if(m_sound->IsABLoopA()) SetABLoopA();
		if(m_sound->IsABLoopB()) SetABLoopB();
	}
	m_sound->SetReverse(bReverse);
	m_menu->CheckItem(ID_REVERSE, bReverse ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 逆回転再生
//----------------------------------------------------------------------------
void CMainWnd::SetReverse(BOOL bReverse)
{
	if(bReverse) {
		if(m_sound->IsABLoopA()) SetABLoopA();
		if(m_sound->IsABLoopB()) SetABLoopB();
	}
	m_menu->UncheckPresetMenu();
	m_sound->SetReverse(bReverse);
	m_menu->CheckItem(ID_REVERSE, bReverse ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 古びたレコード再生
//----------------------------------------------------------------------------
void CMainWnd::SetRecord()
{
	m_menu->UncheckPresetMenu();
	BOOL bRecord = !m_menu->IsItemChecked(ID_RECORD);
	SetRecordNoise(bRecord);
	m_menu->CheckItem(ID_RECORD, bRecord ? MF_CHECKED : MF_UNCHECKED);
	if(bRecord) {
		if(m_menu->IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu->IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_menu->OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_RECORD, 750);
	}
	else {
		KillTimer(IDT_RECORD);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_menu->OnEQFlatMenuSelected();
		double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
		m_freqLabel->SetFreq(100.0);
		m_freqSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// 古びたレコード再生
//----------------------------------------------------------------------------
void CMainWnd::SetRecord(BOOL bRecord)
{
	SetRecordNoise(bRecord);
	m_menu->CheckItem(ID_RECORD, bRecord ? MF_CHECKED : MF_UNCHECKED);
	if(bRecord) {
		if(m_menu->IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu->IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_menu->OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_RECORD, 750);
	}
	else {
		KillTimer(IDT_RECORD);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
		m_freqLabel->SetFreq(100.0);
		m_freqSlider->SetThumbPos((int)(100 * dCalc), TRUE);
		SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// レコードノイズの設定
//----------------------------------------------------------------------------
void CMainWnd::SetRecordNoise(BOOL bRecordNoise)
{
	m_menu->UncheckSoundEffectMenu();
	m_menu->CheckItem(ID_RECORDNOISE, bRecordNoise ? MF_CHECKED : MF_UNCHECKED);
	if(bRecordNoise) {
		m_soundEffect->StreamCreateFile((m_rApp.GetFilePath()
									+ _T("sound\\RecordNoise.wav")).c_str());
		m_soundEffect->ChannelPlay();
		m_soundEffect->SetABLoopA(TRUE);
		m_soundEffect->SetABLoopB(TRUE);
		QWORD qwPosA = m_soundEffect->ChannelSeconds2Bytes(1.417);
		QWORD qwPosB = m_soundEffect->ChannelSeconds2Bytes(7.653);
		m_soundEffect->SetLoopPosA(qwPosA);
		m_soundEffect->SetLoopPosB(qwPosB);
	}
	else m_soundEffect->ChannelStop();
}
//----------------------------------------------------------------------------
// １曲ループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetSingleLoop()
{
	m_sound->SetLoop(!m_sound->IsLoop());
	m_menu->SetSingleLoopState(m_sound->IsLoop());
	m_toolBar->SetSingleLoopState(m_sound->IsLoop());
}
//----------------------------------------------------------------------------
// 再生速度の設定
//----------------------------------------------------------------------------
void CMainWnd::SetSpeed(double dSpeed)
{
	m_menu->UncheckPresetMenu();
	m_sound->SetTempo((float)dSpeed);
	if(m_bVideo) m_sound->ChannelSetPosition(m_sound->ChannelGetPosition());
}
//----------------------------------------------------------------------------
// 再生周波数の設定
//----------------------------------------------------------------------------
void CMainWnd::SetFreq(double dFreq)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetSampleRate((float)dFreq);
	if(m_bVideo) m_sound->ChannelSetPosition(m_sound->ChannelGetPosition());
}
//----------------------------------------------------------------------------
// パンの設定
//----------------------------------------------------------------------------
void CMainWnd::SetPan(int nPan)
{
	m_menu->UncheckPresetMenu();
	m_sound->ChannelSetPan(nPan);
}
//----------------------------------------------------------------------------
// 音程の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPitch(double dPitch)
{
	m_menu->UncheckPresetMenu();
	m_menu->CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu->CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound->SetPitch((float)dPitch);
	if(m_bVideo) m_sound->ChannelSetPosition(m_sound->ChannelGetPosition());
}
//----------------------------------------------------------------------------
// 再生位置の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPlayPosition()
{
	playPositionWnd->Create();
}
//----------------------------------------------------------------------------
// 再生範囲の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPlayRange()
{
	m_menu->CheckItem(ID_PLAYRANGE, MF_UNCHECKED);
	playRangeWnd->Create();
}
//----------------------------------------------------------------------------
// 再生範囲の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPlayRange(double dStartSeconds, double dEndSeconds)
{
	m_dStartSeconds = dStartSeconds;
	m_dEndSeconds = dEndSeconds;
	m_menu->CheckItem(ID_PLAYRANGE, MF_CHECKED);
	double dCurPos = m_sound->ChannelGetSecondsPosition();
	if(dCurPos < m_dStartSeconds || m_dEndSeconds <= dCurPos)
		m_sound->ChannelSetSecondsPosition(m_dStartSeconds);
}
//----------------------------------------------------------------------------
// ビデオかどうかを設定
//----------------------------------------------------------------------------
void CMainWnd::SetVideo(BOOL bVideo)
{
	m_bVideo = bVideo;
	m_sound->SetVideo(bVideo);
}
//----------------------------------------------------------------------------
// モノラル化
//----------------------------------------------------------------------------
void CMainWnd::SetMonoral()
{
	m_menu->UncheckPresetMenu();
	BOOL bMonoral = !m_menu->IsItemChecked(ID_MONORAL);
	if(bMonoral) {
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound->SetMonoral(bMonoral);
	m_menu->CheckItem(ID_MONORAL, bMonoral ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// モノラル化
//----------------------------------------------------------------------------
void CMainWnd::SetMonoral(BOOL bMonoral)
{
	m_menu->UncheckPresetMenu();
	if(bMonoral) {
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound->SetMonoral(bMonoral);
	m_menu->CheckItem(ID_MONORAL, bMonoral ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ボーカルキャンセル
//----------------------------------------------------------------------------
void CMainWnd::SetVocalCancel()
{
	m_menu->UncheckPresetMenu();
	BOOL bVocalCancel = !m_menu->IsItemChecked(ID_VOCALCANCEL);
	if(bVocalCancel) {
		SetMonoral(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound->SetVocalCancel(bVocalCancel);
	m_menu->CheckItem(ID_VOCALCANCEL, bVocalCancel ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ボーカルキャンセル
//----------------------------------------------------------------------------
void CMainWnd::SetVocalCancel(BOOL bVocalCancel)
{
	m_menu->UncheckPresetMenu();
	if(bVocalCancel) {
		SetMonoral(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound->SetVocalCancel(bVocalCancel);
	m_menu->CheckItem(ID_VOCALCANCEL, bVocalCancel ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 音量の設定
//----------------------------------------------------------------------------
void CMainWnd::SetVolume(double nVolume)
{
	m_sound->ChannelSetVolume((float)nVolume);
}
//----------------------------------------------------------------------------
// 波音の設定
//----------------------------------------------------------------------------
void CMainWnd::SetWave(BOOL bWave)
{
	m_menu->UncheckSoundEffectMenu();
	m_menu->CheckItem(ID_WAVE, bWave ? MF_CHECKED : MF_UNCHECKED);
	if(bWave) {
		m_soundEffect->StreamCreateFile((m_rApp.GetFilePath()
									+ _T("sound\\Wave.mp3")).c_str());
		m_soundEffect->ChannelPlay();
		m_soundEffect->SetABLoopA(TRUE);
		m_soundEffect->SetABLoopB(TRUE);
		QWORD qwPosA = m_soundEffect->ChannelSeconds2Bytes(0.283);
		QWORD qwPosB = m_soundEffect->ChannelSeconds2Bytes(39.399);
		m_soundEffect->SetLoopPosA(qwPosA);
		m_soundEffect->SetLoopPosB(qwPosB);
	}
	else m_soundEffect->ChannelStop();
}
//----------------------------------------------------------------------------
// 時間の設定（秒数）
//----------------------------------------------------------------------------
void CMainWnd::SetSeconds(double fSeconds)
{
	SetTime(m_sound->ChannelSeconds2Bytes(fSeconds));
}
//----------------------------------------------------------------------------
// タブの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetTabVisible()
{
	BOOL bTabVisible = !m_menu->IsItemChecked(ID_TAB);

	int nCmdShow = bTabVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bTabVisible ? MF_CHECKED : MF_UNCHECKED;
	if(bTabVisible && m_menu->IsItemChecked(ID_PLAYLIST))
		m_divider5->Show(SW_SHOW);
	else m_divider5->Show(SW_HIDE);
	HWND hParentWnd = bTabVisible ? *m_tab : m_hWnd;
	for(int i = 0; i < (int)m_arrayList.size(); i++)
		m_arrayList[i]->SetParent(hParentWnd);
	m_tab->Show(nCmdShow);
	m_menu->CheckItem(ID_TAB, uCheck);
	ResetAllControlPos();
	ResetSize();
}
//----------------------------------------------------------------------------
// 時間の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTime(QWORD qwTime, BOOL bReset)
{
	if(bMarkerPlay) {
		this->nCurrentLoopCount = 0;

		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
		QWORD length = m_sound->ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0) {
			if(0 <= qwTime && qwTime < arrayMarker[0]) {
					bDone = TRUE;
					SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
					SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE, (LPARAM)(arrayMarker[0] / 100000));
					m_sound->SetLoopPosA(0);
					m_sound->SetLoopPosB(arrayMarker[0]);
			}
		}
		else {
			bDone = TRUE;
			SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE, 0L);
			SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
						(LPARAM)(length / 100000));
			m_sound->SetLoopPosA(0);
			m_sound->SetLoopPosB(length);
		}

		if(!bDone) {
			for(int i = 0; i < max; i++) {
				if(i + 1 < max) {
					if(arrayMarker[i] <= qwTime && qwTime < arrayMarker[i + 1])
					{
						bDone = TRUE;
						SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
							(LPARAM)(arrayMarker[i] / 100000));
						SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
							(LPARAM)(arrayMarker[i + 1] / 100000));
						m_sound->SetLoopPosA(arrayMarker[i]);
						m_sound->SetLoopPosB(arrayMarker[i + 1]);
						break;
					}
				}
			}
		}

		if(!bDone) {
			if(arrayMarker[max - 1] <= qwTime && qwTime <= length) {
				bDone = TRUE;
				SendMessage(*m_timeSlider, TBM_SETSELSTART, TRUE,
					(LPARAM)(arrayMarker[max - 1] / 100000));
				SendMessage(*m_timeSlider, TBM_SETSELEND, TRUE,
					(LPARAM)(length / 100000));
				m_sound->SetLoopPosA(arrayMarker[max - 1]);
				m_sound->SetLoopPosB(length);
			}
		}
	}
	if(m_sound->IsABLoopA() && qwTime < m_sound->GetLoopPosA())
		qwTime = m_sound->GetLoopPosA();
	if(m_sound->IsABLoopB()
	   && qwTime > m_sound->GetLoopPosB() - m_sound->ChannelGetFreq())
		qwTime = m_sound->GetLoopPosB() - (QWORD)m_sound->ChannelGetFreq();
	if(qwTime < 0) qwTime = 0;
	else if(qwTime > m_sound->ChannelGetLength() - m_sound->ChannelGetFreq())
		qwTime = m_sound->ChannelGetLength() - (QWORD)m_sound->ChannelGetFreq();
	if(bReset) m_sound->ChannelSetPosition(qwTime);
	ShowTime();
}
//----------------------------------------------------------------------------
// タイマー設定
//----------------------------------------------------------------------------
void CMainWnd::SetTimerPlay()
{
	timerPlayWnd->Create();
}
//----------------------------------------------------------------------------
// タイマー再生の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTimerPlay(int nHour, int nMinute)
{
	nTimerPlayHour = nHour;
	nTimerPlayMinute = nMinute;
	SYSTEMTIME st;
	GetLocalTime(&st);
	bTimerPlayNextDay = (nHour < st.wHour || (nHour == st.wHour
		&& nMinute < st.wMinute));
	SetTimerStop(FALSE);
	SetTimerPlay(TRUE);
}
//----------------------------------------------------------------------------
// タイマー再生の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTimerPlay(BOOL bTimerPlay)
{
	this->bTimerPlay = !bTimerPlay;
	m_menu->CheckItem(ID_TIMERPLAY, bTimerPlay ? MF_CHECKED : MF_UNCHECKED);
	if(bTimerPlay) SetTimer(IDT_TIMERPLAY, 1000);
	else KillTimer(IDT_TIMERPLAY);
}
//----------------------------------------------------------------------------
// タイマー停止の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTimerStop(int nHour, int nMinute)
{
	nTimerStopHour = nHour;
	nTimerStopMinute = nMinute;
	SYSTEMTIME st;
	GetLocalTime(&st);
	bTimerStopNextDay = (nHour < st.wHour || (nHour == st.wHour
		&& nMinute < st.wMinute));
	SetTimerPlay(FALSE);
	SetTimerStop(TRUE);
}
//----------------------------------------------------------------------------
// タイマー停止の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTimerStop(BOOL bTimerStop)
{
	this->bTimerStop = !bTimerStop;
	m_menu->CheckItem(ID_TIMERPLAY, bTimerStop ? MF_CHECKED : MF_UNCHECKED);
	if(bTimerStop) SetTimer(IDT_TIMERSTOP, 1000);
	else KillTimer(IDT_TIMERSTOP);
}
//----------------------------------------------------------------------------
// 最前面表示の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTopMost()
{
	LONG lStyle = GetExStyle();
	if(lStyle & WS_EX_TOPMOST) {
		SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE
			| SWP_NOMOVE);
		m_menu->CheckItem(ID_TOPMOST, MF_UNCHECKED);
	}
	else {
		SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE
			| SWP_NOMOVE);
		m_menu->CheckItem(ID_TOPMOST, MF_CHECKED);
	}
}
//----------------------------------------------------------------------------
// ３Ｄリバーブのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::Show3DReverbCustomizeWnd()
{
	m_3dReverbCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// コーラスのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowChorusCustomizeWnd()
{
	m_chorusCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// コンプレッサーのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowCompressorCustomizeWnd()
{
	m_compressorCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// ディレイのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowDelayCustomizeWnd()
{
	m_delayCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// ディストーションのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowDistortionCustomizeWnd()
{
	m_distortionCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// フランジャーのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowFlangerCustomizeWnd()
{
	m_flangerCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// ガーグルのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowGargleCustomizeWnd()
{
	m_gargleCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// LAMEコマンドラインオプション設定用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowLAMECommandLineWnd()
{
	m_lameCommandLineWnd->Create();
}
//----------------------------------------------------------------------------
// URLを開くウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowOpenURLWnd(BOOL bAdd)
{
	m_openURLWnd->Create(bAdd);
}
//----------------------------------------------------------------------------
// ファイルを開くダイアログの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowOpenFileDialog(BOOL bClear)
{
	TCHAR szFilesPath[MAX_PATH * 255] = _T("");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hInstance = GetModuleHandle(NULL);
	ofn.hwndOwner = m_hWnd;
#if JP
	ofn.lpstrFilter = _T("読込可能ファイル(*.wav;*.cda;*.mp*;*.ogg;*.wma;")
					  _T("*.aiff;*.aif;*.ape;*.flac;*.m4a;*.m4b;*.mp4;*.aac;")
					  _T("*.nsf;")
					  _T("*.avi;*.wmv;*.mkv;*.flv;*.ini;*.m3u;*.m3u8)\0*.wav;")
					  _T("*.cda;*.mp3;*.mp2;*.mp1;*.ogg;*.wma;*.aiff;*.aif;")
					  _T("*.ape;*.flac;*.m4a;*.m4b;*.mp4;*.aac;*.nsf;")
					  _T("*.avi;*.wmv;")
					  _T("*.mkv;*.flv;*.ini;*.m3u;*.m3u8\0")
					  _T("再生可能ファイル(*.wav;*.cda;*.mp*;*.ogg;*.wma;")
					  _T("*.aiff;*.aif;*.ape;*.flac;*.m4a;*.m4b;*.mp4;*.aac;")
					  _T("*.nsf;")
					  _T("*.avi;*.wmv;*.mkv;*.flv)\0*.wav;*.cda;*.mp3;*.mp2;")
					  _T("*.mp1;*.ogg;*.wma;*.aiff;*.aif;*.ape;*.flac;*.m4a;")
					  _T("*.m4b;*.mp4;*.aac;*.nsf;")
					  _T("*.avi;*.wmv;*.mkv;*.flv\0")
					  _T("WAVE ファイル(*.wav)\0*.wav\0")
					  _T("CDA ファイル(*.cda)\0*.cda\0")
					  _T("MP3 ファイル(*.mp3)\0*.mp3\0")
					  _T("MP2 ファイル(*.mp2)\0*.mp2\0")
					  _T("MP1 ファイル(*.mp1)\0*.mp1\0")
					  _T("Ogg Vorbis ファイル(*.ogg)\0*.ogg\0")
					  _T("AIFF ファイル(*.aiff;*.aif)\0*.aiff;*.aif\0")
					  _T("APE ファイル(*.ape)\0*.ape\0")
					  _T("FLAC ファイル(*.flac)\0*.flac\0")
					  _T("AAC ファイル(*.m4a;*.m4b;*.mp4;*.aac)\0*.m4a;*.m4b;")
					  _T("*.mp4;*.aac\0")
					  _T("NSF ファイル(*.nsf)\0*.nsf\0")
					  _T("AVI ファイル(*.avi)\0*.avi\0")
					  _T("WMV ファイル(*.wmv)\0*.wmv\0")
					  _T("MKV ファイル(*.mkv)\0*.mkv\0")
					  _T("FLV ファイル(*.flv)\0*.flv\0")
					  _T("設定状態ファイル(*.ini)\0*.ini\0")
					  _T("プレイリストファイル(*.m3u;*.m3u8)\0*.m3u;*.m3u8\0")
					  _T("すべてのファイル (*.*)\0*.*\0\0");
#else // JP
	ofn.lpstrFilter = _T("Readable file(*.wav;*.cda;*.mp*;*.ogg;*.wma;")
					  _T("*.aiff;*.aif;*.ape;*.flac;*.m4a;*.m4b;*.mp4;*.aac;")
					  _T("*.nsf;")
					  _T("*.avi;*.wmv;*.mkv;*.flv;*.ini;*.m3u;*.m3u8)\0*.wav;")
					  _T("*.cda;*.mp3;*.mp2;*.mp1;*.ogg;*.wma;*.aiff;*.aif;")
					  _T("*.ape;*.flac;*.m4a;*.m4b;*.mp4;*.aac;*.nsf;")
					  _T("*.avi;*.wmv;")
					  _T("*.mkv;*.flv;*.ini;*.m3u;*.m3u8\0")
					  _T("Playable file(*.wav;*.cda;*.mp*;*.ogg;*.wma;")
					  _T("*.aiff;*.aif;*.ape;*.flac;*.m4a;*.m4b;*.mp4;*.aac;")
					  _T("*.nsf;")
					  _T("*.avi;*.wmv;*.mkv;*.flv)\0*.wav;*.cda;*.mp3;*.mp2;")
					  _T("*.mp1;*.ogg;*.wma;*.aiff;*.aif;*.ape;*.flac;*.m4a;")
					  _T("*.m4b;*.mp4;*.aac;*.nsf;")
					  _T("*.avi;*.wmv;*.mkv;*.flv\0")
					  _T("WAVE file(*.wav)\0*.wav\0")
					  _T("CDA file(*.cda)\0*.cda\0")
					  _T("MP3 file(*.mp3)\0*.mp3\0")
					  _T("MP2 file(*.mp2)\0*.mp2\0")
					  _T("MP1 file(*.mp1)\0*.mp1\0")
					  _T("Ogg Vorbis file(*.ogg)\0*.ogg\0")
					  _T("AIFF file(*.aiff;*.aif)\0*.aiff;*.aif\0")
					  _T("APE file(*.ape)\0*.ape\0")
					  _T("FLAC file(*.flac)\0*.flac\0")
					  _T("AAC file(*.m4a;*.m4b;*.mp4;*.aac)\0*.m4a;*.m4b;")
					  _T("*.mp4;*.aac\0")
					  _T("NSF file(*.nsf)\0*.nsf\0")
					  _T("AVI file(*.avi)\0*.avi\0")
					  _T("WMV file(*.wmv)\0*.wmv\0")
					  _T("MKV file(*.mkv)\0*.mkv\0")
					  _T("FLV file(*.flv)\0*.flv\0")
					  _T("Settings file(*.ini)\0*.ini\0")
					  _T("Playlist file(*.m3u;*.m3u8)\0*.m3u;*.m3u8\0")
					  _T("All file (*.*)\0*.*\0\0");
#endif // JP
	ofn.lpstrFile = szFilesPath;
	ofn.nMaxFile = MAX_PATH * 255;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ALLOWMULTISELECT
		| OFN_HIDEREADONLY;

	if(GetOpenFileName(&ofn)) {
		TCHAR chExt[_MAX_EXT];
		_tsplitpath_s(szFilesPath, NULL, 0, NULL, 0, NULL, 0, chExt, _MAX_EXT);

		if(_tcsicmp(chExt, _T(".ini")) == 0) {
			LoadSettings(szFilesPath);
			return;
		}
		int nSelect = m_tab->GetCurrentFocus();
		if(bClear) {
			ChangeCurPlayTab();
			m_arrayList[nSelect]->DeleteAllItems();
		}
		LPTSTR pszDirectoryPath = szFilesPath;
		LPTSTR pszFileName = szFilesPath;
		BOOL bAdd = FALSE; // ファイルを追加したかどうか
		while(1) {
			for(int i = lstrlen(pszFileName); i >= 0; i--)
				pszFileName++;
			TCHAR szFilePath[MAX_PATH];
			lstrcpy(szFilePath, pszDirectoryPath);
			if(*pszFileName == _T('\0')) {
				// 文字列おわり
				if(!bAdd) // まだ追加されていない場合
					m_arrayList[nSelect]->AddFile(szFilePath);
				break;
			}

			lstrcat(szFilePath, _T("\\"));
			lstrcat(szFilePath, pszFileName);

			m_arrayList[nSelect]->AddFile(szFilePath);
			bAdd = TRUE;
		}

		if(m_arrayList[nSelect]->GetItemCount() <= 0) {
			m_sound->StreamFree();
			Stop();
		}
		else if(!(!bClear && m_sound->GetCurFileNum() > 0)) {
			m_sound->SetCurFileNum(0);
			PlayNext(bClear, TRUE);
		}

		SetPreviousNextMenuState();
		StartUpdateInfo();
	}
}
//----------------------------------------------------------------------------
// フォルダを開くダイアログの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowOpenFolderDialog(BOOL bClear)
{
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	TCHAR szDir[MAX_PATH] = _T("");
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;

	// Shell の標準のアロケータを取得
	if(SUCCEEDED(SHGetMalloc(&pMalloc))) {
		// BROWSEINFO 構造体を埋める
		ZeroMemory(&bi,sizeof(bi));
		bi.hwndOwner = m_hWnd;
#if JP
		bi.lpszTitle = _T("開くフォルダを選択して下さい");
#else // JP
		bi.lpszTitle = _T("Select directory");
#endif // JP
		bi.ulFlags = BIF_RETURNONLYFSDIRS;

		// フォルダの参照ダイアログボックスの表示
		pidl = SHBrowseForFolder(&bi);

		if(pidl) {
			// PIDL をファイルシステムのパスに変換
			if(SHGetPathFromIDList(pidl,szDir)) {
				int nSelect = m_tab->GetCurrentFocus();
				if(bClear) {
					ChangeCurPlayTab();
					m_arrayList[nSelect]->DeleteAllItems();
				}
				m_arrayList[nSelect]->AddFile(szDir);
				LPTSTR pszDirectoryPath = szDir;
				LPTSTR pszFileName = szDir;
				while(1) {
					for(int i = lstrlen(pszFileName); i >= 0; i--)
						pszFileName++;
					TCHAR szFilePath[MAX_PATH];
					lstrcpy(szFilePath, pszDirectoryPath);
					if(*pszFileName == _T('\0')) {
						// 文字列おわり
						if(m_arrayList[nSelect]->GetItemCount() == 0)
							m_arrayList[nSelect]->AddFile(szFilePath);
						break;
					}

					lstrcat(szFilePath, _T("\\"));
					lstrcat(szFilePath, pszFileName);

					m_arrayList[nSelect]->AddFile(szFilePath);
				}

				if(m_arrayList[nSelect]->GetItemCount() <= 0) {
					m_sound->StreamFree();
					Stop();
				}
				else if(!(!bClear && m_sound->GetCurFileNum() > 0)) {
					m_sound->SetCurFileNum(0);
					PlayNext(bClear, TRUE);
				}

				SetPreviousNextMenuState();
			}

			// SHBrowseForFolder によって割り当てられた PIDL を解放
			pMalloc->Free(pidl);
			StartUpdateInfo();
		}

		// Shell のアロケータを開放
		pMalloc->Release();
	}
}
//----------------------------------------------------------------------------
// リバーブのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowReverbCustomizeWnd()
{
	m_reverbCustomizeWnd->Create();
}
//----------------------------------------------------------------------------
// ファイルを保存ダイアログの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowSaveFileDialog()
{
	TCHAR filePath[MAX_PATH] = _T("");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hInstance = GetModuleHandle(NULL);
	ofn.hwndOwner = m_hWnd;
#if JP
	ofn.lpstrFilter = _T("WAVE ファイル(*.wav)\0*.wav\0")
					  _T("MP3 ファイル(*.mp3)\0*.mp3\0")
					  _T("Ogg Vorbis ファイル(*.ogg)\0*.ogg\0")
					  _T("設定状態(*.ini)\0*.ini\0")
					  _T("絶対パス プレイリストファイル(*.m3u)\0*.m3u\0")
					  _T("相対パス プレイリストファイル(*.m3u)\0*.m3u\0")
					  _T("絶対パス プレイリストファイル(*.m3u8)\0*.m3u8\0")
					  _T("相対パス プレイリストファイル(*.m3u8)\0*.m3u8\0")
					  _T("\0");
#else // JP
	ofn.lpstrFilter = _T("WAVE file(*.wav)\0*.wav\0")
					  _T("MP3 file(*.mp3)\0*.mp3\0")
					  _T("Ogg Vorbis file(*.ogg)\0*.ogg\0")
					  _T("Settings(*.ini)\0*.ini\0")
					  _T("Absolute path playlist file(*.m3u)\0*.m3u\0")
					  _T("Relative path playlist file(*.m3u)\0*.m3u\0")
					  _T("Absolute path playlist file(*.m3u8)\0*.m3u8\0")
					  _T("Relative path playlist file(*.m3u8)\0*.m3u8\0")
					  _T("\0");
#endif // JP
	if(strSaveFormat == _T("MP3")) ofn.nFilterIndex = 2;
	else if(strSaveFormat == _T("OGG")) ofn.nFilterIndex = 3;
	else ofn.nFilterIndex = 1;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

	while(1) {
		BOOL bRet = GetSaveFileName(&ofn);
		if(!bRet) break;

		// 拡張子が指定されなかった場合は、追加
		BOOL bAdd = FALSE; // 拡張子を追加したかどうか
		TCHAR ext[_MAX_EXT];
		_tsplitpath_s(filePath, NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);
		if(ofn.nFilterIndex == 1 && lstrcmpi(ext, _T(".wav")) != 0) {
			lstrcat(filePath, _T(".wav"));
			bAdd = TRUE;
		}
		else if(ofn.nFilterIndex == 2 && lstrcmpi(ext, _T(".mp3")) != 0) {
			lstrcat(filePath, _T(".mp3"));
			bAdd = TRUE;
		}
		else if(ofn.nFilterIndex == 3 && lstrcmpi(ext, _T(".ogg")) != 0) {
			lstrcat(filePath, _T(".ogg"));
			bAdd = TRUE;
		}
		else if(ofn.nFilterIndex == 4 && lstrcmpi(ext, _T(".ini")) != 0) {
			lstrcat(filePath, _T(".ini"));
			bAdd = TRUE;
		}
		else if((ofn.nFilterIndex == 5 || ofn.nFilterIndex == 6) &&
				 lstrcmpi(ext, _T(".m3u")) != 0) {
			lstrcat(filePath, _T(".m3u"));
			bAdd = TRUE;
		}
		else if((ofn.nFilterIndex == 7 || ofn.nFilterIndex == 8) &&
				 lstrcmpi(ext, _T(".m3u8")) != 0) {
			lstrcat(filePath, _T(".m3u8"));
			bAdd = TRUE;
		}

		// 既に存在する場合は、上書き確認
		if(bAdd && GetFileAttributes(filePath) != 0xFFFFFFFF) {
			tstring str = filePath;
#if JP
			str += _T(" は既に存在します。\n上書きしますか?");
#else // JP
			str += _T(" already exists.\nOverride?");
#endif // JP
			int nRet = MessageBox(0, str.c_str(),
#if JP
								  _T("名前を付けて保存"),
#else // JP
								  _T("Save"),
#endif // JP
								  MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2);
			if(nRet != IDYES)
			continue;
		}

		if(ofn.nFilterIndex == 1 || ofn.nFilterIndex == 2 ||
		   ofn.nFilterIndex == 3) {
			// 音声ファイル

			// 入力・出力ファイルが同一ファイルだった場合は、エラー
			if(lstrcmpi(filePath, m_sound->GetCurFileName().c_str()) == 0) {
				MessageBox(m_hWnd,
#if JP
					_T("同一ファイルの上書きには対応していません。"),
					_T("名前を付けて保存"),
#else // JP
					_T("This software can't override input/output same file."),
					_T("Save"),
#endif // JP
					MB_ICONEXCLAMATION);
				continue;
			}

			if(ofn.nFilterIndex == 1) { // WAVE
				strSaveFormat = _T("WAVE");
				WriteInitFile();
				m_sound->SaveFile(filePath, 0);
			}
			else if(ofn.nFilterIndex == 2) { // MP3
				strSaveFormat = _T("MP3");
				WriteInitFile();
				m_sound->SaveFile(filePath, 1);
			}
			else { // Ogg Vorbis
				strSaveFormat = _T("OGG");
				WriteInitFile();
				m_sound->SaveFile(filePath, 2);
			}
		}
		else if(ofn.nFilterIndex == 4) // 設定状態
			SaveSettings(filePath);
		else {
			// プレイリストファイル
			
			tstring str = _T("");
			for(int i = 0; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++) {
				TCHAR sFilePath[MAX_PATH];
				m_arrayList[nCurPlayTab]->GetItemText(i, 7, sFilePath,
													  MAX_PATH);
				if(ofn.nFilterIndex == 6 || ofn.nFilterIndex == 8) {
					TCHAR sFileRelativePath[MAX_PATH];
					if(PathRelativePathTo(sFileRelativePath, filePath,
						FILE_ATTRIBUTE_ARCHIVE, sFilePath,
						FILE_ATTRIBUTE_ARCHIVE))
						str += sFileRelativePath;
					else str += sFilePath;
				}
				else str += sFilePath;
				str += _T("\n");
			}

			CM3UFile file;
			file.Save(filePath, str, ofn.nFilterIndex >= 6);
		}

		break;
	}
}
//----------------------------------------------------------------------------
// 一括変換ダイアログの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowSaveAllFileDialog()
{
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	TCHAR szDir[MAX_PATH] = _T("");
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;

	// Shell の標準のアロケータを取得
	if(SUCCEEDED(SHGetMalloc(&pMalloc))) {
		// BROWSEINFO 構造体を埋める
		ZeroMemory(&bi,sizeof(bi));
		bi.hwndOwner = m_hWnd;
#if JP
		bi.lpszTitle = _T("出力先のフォルダを選択して下さい");
#else // JP
		bi.lpszTitle = _T("Select output directory");
#endif // JP
		bi.ulFlags = BIF_RETURNONLYFSDIRS;

		// フォルダの参照ダイアログボックスの表示
		pidl = SHBrowseForFolder(&bi);

		if(pidl) {
			// PIDL をファイルシステムのパスに変換
			if(SHGetPathFromIDList(pidl,szDir)) {
				CAllSaveWnd_MainWnd wnd(m_rApp, *this);
				wnd.Create();
#if JP
				wnd.SetCaption(_T("一括変換設定"));
#else // JP
				wnd.SetCaption(_T("Save all"));
#endif // JP
				wnd.Show(SW_SHOW);
				wnd.Update();

				MSG msg;
				while(!wnd.IsOk()) {
					if(!IsWindow(wnd)) {
						pMalloc->Free(pidl);

						pMalloc->Release();

						return;
					}

					if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
						if(GetMessage(&msg, NULL, 0, 0) > 0) {
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
					}
				}
				int nFormat = wnd.GetFormat();
				wnd.Close();

				if(nFormat == 1) { // MP3
					tstring strLamePath = m_rApp.GetFilePath()
										  + _T("lame.exe");
					if(GetFileAttributes(strLamePath.c_str()) == 0xFFFFFFFF) {
#if JP
						MessageBox(m_hWnd, _T("MP3形式での保存には、LAME.EXE")
							_T("が必要です。\nHayaemon.exeと同じディレクトリ")
							_T("にLAME.EXEを置いて下さい。"),
							_T("名前を付けて保存"), MB_ICONINFORMATION);
#else // JP
						MessageBox(m_hWnd, _T("To save MP3 file, lame.exe ")
							_T("is required.\nPut lame.exe in the same ")
							_T("directory as hayaemon.exe."),
							_T("Save file"), MB_ICONINFORMATION);
#endif // JP
						pMalloc->Free(pidl);
						pMalloc->Release();
						return;
					}
				}
				else if(nFormat == 2) { // OGG
					tstring strLamePath = m_rApp.GetFilePath()
										  + _T("oggenc.exe");
					if(GetFileAttributes(strLamePath.c_str()) == 0xFFFFFFFF) {
#if JP
						MessageBox(m_hWnd, _T("Ogg Vorbis形式での保存には、")
							_T("oggenc.exeが必要です。\nHayaemon.exeと同じ")
							_T("ディレクトリにoggenc.exeを置いて下さい。"),
							_T("名前を付けて保存"), MB_ICONINFORMATION);
#else // JP
						MessageBox(m_hWnd, _T("To save Ogg Vorbis file, ")
							_T("lame.exe is required.\nPut oggenc.exe in the ")
							_T("same directory as hayaemon.exe."),
							_T("Save file"), MB_ICONINFORMATION);
#endif // JP
						pMalloc->Free(pidl);
						pMalloc->Release();
						return;
					}
				}

				// 現在読み込んでいるファイルを一時的に退避
				tstring curFileName = m_sound->GetCurFileName();
				KillTimer(IDT_TIME);
				QWORD curPos = m_sound->ChannelGetPosition();
				BOOL bPlaying = FALSE;
				if(m_sound->ChannelPause()) bPlaying = TRUE;
				m_sound->ChannelStop();

				// 全てのファイルを変換
				for(int i = 0; i < m_arrayList[nCurPlayTab]->GetItemCount();
					i++) {
					tstring str = szDir;
					str += _T("\\");
					TCHAR sFilePath[MAX_PATH];
					m_arrayList[nCurPlayTab]->GetItemText(i, 7, sFilePath,
														  MAX_PATH);
					str += CUtils::GetFileNameWithoutExt(sFilePath);

					// ファイルの存在チェック
					int n = 2;
					TCHAR szNum[10];
					tstring strFormat, str2 = str + strFormat;
					if(nFormat == 0) strFormat = _T(".wav");
					else if (nFormat == 1) strFormat = _T(".mp3");
					else if (nFormat == 2) strFormat = _T(".ogg");
					if(GetFileAttributes((str2 + strFormat).c_str()) == 0xFFFFFFFF)
						str += strFormat;
					else {
						do {
							_stprintf_s(szNum, _T("%d"), n++);
							str2 = str;
							str2 += (tstring)_T("(") + szNum + _T(")");
							str2 += strFormat;
						}
						while(GetFileAttributes(str2.c_str()) != 0xFFFFFFFF);
						str += (tstring)_T("(") + szNum + _T(")");
						str += strFormat;
					}

					m_sound->SetCurFileName(sFilePath);
						// 保存したいファイルに変更
					if(nFormat == 0) { // WAVE
						strSaveFormat = _T("WAVE");
						WriteInitFile();
						m_sound->SaveFile(str.c_str(), 0);
					}
					else if(nFormat == 1) { // MP3
						strSaveFormat = _T("MP3");
						WriteInitFile();
						m_sound->SaveFile(str.c_str(), 1);
					}
					else {
						strSaveFormat = _T("OGG");
						WriteInitFile();
						m_sound->SaveFile(str.c_str(), 2);
					}
				}

				m_sound->StopASIO();
				m_sound->StopWASAPI();
				m_sound->StreamCreateFile(curFileName.c_str());
				if(m_menu->IsItemChecked(ID_QUALITY_WASAPI))
					m_sound->StartWASAPI();
				else if(m_menu->IsItemChecked(ID_QUALITY_ASIO))
					m_sound->StartASIO();
				SetAllEffects();
				if(curPos > 0) m_sound->ChannelSetPosition(curPos);
				if(bPlaying) Pause();
			}

			// SHBrowseForFolder によって割り当てられた PIDL を解放
			pMalloc->Free(pidl);
		}

		// Shell のアロケータを開放
		pMalloc->Release();
	}
}
//----------------------------------------------------------------------------
// 再生時間の表示
//----------------------------------------------------------------------------
void CMainWnd::ShowTime(BOOL bReset)
{
	m_timeLabel->SetTime(m_sound->ChannelGetSecondsPosition(),
						m_sound->ChannelGetSecondsLength(), bReset);
	m_timeSlider->SetThumbPos((LONG)(m_sound->ChannelGetPosition() / 100000));
}
//----------------------------------------------------------------------------
// 巻き戻しの開始
//----------------------------------------------------------------------------
void CMainWnd::StartRewind()
{
	StopForward();
	m_menu->CheckItem(ID_REWIND, MF_CHECKED);
	if(bMarkerPlay)
		m_toolBar->SetState(ID_PREVMARKER, TBSTATE_CHECKED | TBSTATE_ENABLED);
	else m_toolBar->SetState(ID_HEAD, TBSTATE_CHECKED | TBSTATE_ENABLED);
	SetTimer(IDT_REWIND, 100);
}
//----------------------------------------------------------------------------
// 巻き戻しの停止
//----------------------------------------------------------------------------
void CMainWnd::StopRewind()
{
	m_menu->CheckItem(ID_REWIND, MF_UNCHECKED);
	if(bMarkerPlay) m_toolBar->SetState(ID_PREVMARKER, TBSTATE_ENABLED);
	else m_toolBar->SetState(ID_HEAD, TBSTATE_ENABLED);
	KillTimer(IDT_REWIND);
}
//----------------------------------------------------------------------------
// 早送りの開始
//----------------------------------------------------------------------------
void CMainWnd::StartForward()
{
	StopRewind();
	m_menu->CheckItem(ID_FORWARD, MF_CHECKED);
	if(bMarkerPlay)
		m_toolBar->SetState(ID_NEXTMARKER, TBSTATE_CHECKED | TBSTATE_ENABLED);
	else m_toolBar->SetState(ID_NEXT, TBSTATE_CHECKED | TBSTATE_ENABLED);
	SetTimer(IDT_FORWARD, 100);
}
//----------------------------------------------------------------------------
// 歌詞の表示を開始
//----------------------------------------------------------------------------
void CMainWnd::StartLyrics()
{
	if(m_hLyricsThread) {
		m_bLyricsThreadAlive = FALSE;
		DWORD dwExitCode = STILL_ACTIVE;
		while(dwExitCode == STILL_ACTIVE)
			GetExitCodeThread(m_hLyricsThread, &dwExitCode);
		m_hLyricsThread = 0;
	}
	lyricsManager->ClearScreen();
	if(!m_bVideo && m_menu->IsItemChecked(ID_VIDEOSCREEN) &&
			m_menu->IsItemChecked(ID_LYRICS) &&
			lyricsManager->IsLyricsRead()) {
		m_bLyricsThreadAlive = TRUE;
		m_hLyricsThread = (HANDLE)_beginthread(
			&CMainWnd::UpdateLyricsThreadProc, 0, this);
	}
}
//----------------------------------------------------------------------------
// ピッチアナライザを開始
//----------------------------------------------------------------------------
void CMainWnd::StartPitchAnalyser()
{
	if(m_hPitchAnalyserThread) {
		m_bPitchAnalyserThreadAlive = FALSE;
		DWORD dwExitCode = STILL_ACTIVE;
		while(dwExitCode == STILL_ACTIVE)
			GetExitCodeThread(m_hPitchAnalyserThread, &dwExitCode);
		m_hPitchAnalyserThread = 0;
	}
	m_pitchAnalyser->ClearScreen();
	if(!m_bVideo && m_menu->IsItemChecked(ID_VIDEOSCREEN) &&
			m_menu->IsItemChecked(ID_PITCHANALYSER)) {
		m_bPitchAnalyserThreadAlive = TRUE;
		m_hPitchAnalyserThread = (HANDLE)_beginthread(
			&CMainWnd::UpdatePitchAnalyserThreadProc, 0, this);
	}
}
//----------------------------------------------------------------------------
// 情報の更新を開始
//----------------------------------------------------------------------------
void CMainWnd::StartUpdateInfo()
{
	DWORD dwExitCode;
	GetExitCodeThread(m_hUpdateThread, &dwExitCode);
	if(dwExitCode == STILL_ACTIVE) {
		m_bRetryUpdate = TRUE;
		return;
	}
	if(!m_hUpdateThread) CloseHandle(m_hUpdateThread);
	m_hUpdateThread = (HANDLE)_beginthread(&CMainWnd::UpdateThreadProc, 0,
		this);
	SetThreadPriority(m_hUpdateThread, THREAD_PRIORITY_TIME_CRITICAL);
}
//----------------------------------------------------------------------------
// 早送りの停止
//----------------------------------------------------------------------------
void CMainWnd::StopForward()
{
	m_menu->CheckItem(ID_FORWARD, MF_UNCHECKED);
	if(bMarkerPlay) m_toolBar->SetState(ID_NEXTMARKER, TBSTATE_ENABLED);
	else m_toolBar->SetState(ID_NEXT, TBSTATE_ENABLED);
	KillTimer(IDT_FORWARD);
}
//----------------------------------------------------------------------------
// 停止
//----------------------------------------------------------------------------
void CMainWnd::Stop(BOOL bForce)
{
	if(!bForce && dwFadeoutStartTime == 0 &&
	   m_menu->IsItemChecked(ID_FADEOUTSTOP)) {
		dwFadeoutStartTime = timeGetTime();
		SetTimer(IDT_FADEOUT, 1);
	}
	else {
		KillTimer(IDT_FADEOUT);
		KillTimer(IDT_FADEOUTNEXT);
		dwFadeoutStartTime = 0;
		KillTimer(IDT_TIME);
		SetCountLoop(FALSE, 0);
		if(m_menu->IsItemChecked(ID_QUALITY_WASAPI))
			m_sound->PauseWASAPI();
		else m_sound->ChannelStop();
		if(m_menu->IsItemChecked(ID_PLAYRANGE)) SetSeconds(m_dStartSeconds);
		else SetTime(0);
		ShowTime();
		m_toolBar->SetPlayingState(FALSE);
		m_arrayList[nCurPlayTab]->SetPlaying(-1);
		if(m_menu->IsItemChecked(ID_RECORD)) {
			nFreqVelo = 0.0;
			nFreqAccel = 0.0;
			m_freqLabel->SetFreq(100.0);
			m_freqSlider->SetThumbPos((LONG)1000, TRUE);
			SetFreq(100.0);
		}
		m_sound->ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
		if(m_arrayList[nCurPlayTab]->GetItemCount() == 0)
			SetCaption(m_rApp.GetName().c_str());
	}
}
//----------------------------------------------------------------------------
// Twitterでつぶやく
//----------------------------------------------------------------------------
void CMainWnd::Tweet()
{
	tstring initFilePath = m_rApp.GetFilePath() + _T("Setting.ini");

	TCHAR chKey[255], chSecret[255];
	GetPrivateProfileString(_T("Twitter"), _T("Key"), _T(""), chKey, 255,
		initFilePath.c_str());
	GetPrivateProfileString(_T("Twitter"), _T("Secret"), _T(""), chSecret, 255,
		initFilePath.c_str());
	if(_tcsicmp(chKey, _T("")) == 0 || _tcsicmp(chSecret, _T("")) == 0) {
		m_twitterAuthorizeWnd->Create();
		return;
	}
	else Socket::initialize();
	m_tweetWnd->Create();
}
//----------------------------------------------------------------------------
// Twitterでつぶやく
//----------------------------------------------------------------------------
void CMainWnd::Tweet(std::string strMessage)
{
	std::string initFilePath = m_rApp.GetFilePathA() + "Setting.ini";

	char chKey[255], chSecret[255];
	GetPrivateProfileStringA("Twitter", "Key", "", chKey, 255,
		initFilePath.c_str());
	GetPrivateProfileStringA("Twitter", "Secret", "", chSecret, 255,
		initFilePath.c_str());
	if(strcmp(chKey, "") == 0 || strcmp(chSecret, "") == 0) {
		m_twitterAuthorizeWnd->Create();
		return;
	}
	int n;
	wchar_t ucs2[1000];
	char utf8[1000];
	n = MultiByteToWideChar(CP_ACP, 0, strMessage.c_str(), strMessage.size(),
		ucs2, 1000);
	n = WideCharToMultiByte(CP_UTF8, 0, ucs2, n, utf8, 1000, 0, 0);
	strMessage.assign(utf8, n);

	std::string uri = "http://api.twitter.com/1/statuses/update.xml";
	uri += "?status=";
	uri += oauth_url_escape(strMessage.c_str());

	std::string c_key = "npkW3TKg8JqvELAlkqCfiA";
	std::string c_secret = "pl502twI6r6tkL7ApH2ElN9Hb1Un4qWvLNpb149IC8";
	std::string postarg;
	std::string req_url = oauth_sign_url2(uri.c_str(), &postarg, OA_HMAC, 0,
		c_key.c_str(), c_secret.c_str(), chKey, chSecret);
	std::string reply = oauth_http_post(req_url.c_str(), postarg.c_str(),
		false);
}
//----------------------------------------------------------------------------
// 指定した%再生周波数を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpFreq(double freq)
{
	double dCalc = pow(10.0, m_freqSlider->GetDecimalDigit());
	int newFreq = m_freqSlider->GetThumbPos() + (int)(freq * dCalc);
	int nMaxFreq = m_freqSlider->GetRangeMax();
	if(newFreq > nMaxFreq) newFreq = nMaxFreq;
	m_freqLabel->SetFreq((double)(newFreq / dCalc));
	m_freqSlider->SetThumbPos((LONG)newFreq, TRUE);
	SetFreq((double)(newFreq / dCalc));
}
//----------------------------------------------------------------------------
// 指定した数値×半音分音程を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpPitch(double pitch)
{
	double dCalc = pow(10.0, m_pitchSlider->GetDecimalDigit());
	int newPitch = m_pitchSlider->GetThumbPos() + (int)(pitch * dCalc);
	int nMaxPitch = m_pitchSlider->GetRangeMax();
	if(newPitch > nMaxPitch) newPitch = nMaxPitch;
	m_pitchLabel->SetPitch((double)(newPitch / dCalc));
	m_pitchSlider->SetThumbPos((LONG)newPitch, TRUE);
	SetPitch((double)(newPitch / dCalc));
}
//----------------------------------------------------------------------------
// 指定した%再生速度を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpSpeed(double speed)
{
	double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
	int newSpeed = m_speedSlider->GetThumbPos() + (int)(speed * dCalc);
	int nMaxSpeed = m_speedSlider->GetRangeMax();
	if(newSpeed > nMaxSpeed) newSpeed = nMaxSpeed;
	m_speedLabel->SetSpeed((double)(newSpeed / dCalc));
	m_speedSlider->SetThumbPos((LONG)newSpeed, TRUE);
	SetSpeed((double)(newSpeed / dCalc));
}
//----------------------------------------------------------------------------
// 指定した%音量を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpVolume(int volume)
{
	int newVolume = m_volumeSlider->GetThumbPos() + (int)(volume * 10);
	if(newVolume > 1000) newVolume = 1000;
	m_volumeLabel->SetVolume((double)(newVolume / 10.0));
	m_volumeSlider->SetThumbPos((LONG)newVolume, TRUE);
	SetVolume((double)(newVolume / 10.0));
}
//----------------------------------------------------------------------------
// INI ファイルの書き込み
//----------------------------------------------------------------------------
void CMainWnd::WriteInitFile()
{
	if(!isInitFileRead) return;

	tstring initFilePath = m_rApp.GetFilePath() + _T("Setting.ini");

	TCHAR buf[255];

	// ウィンドウの設定
    WINDOWPLACEMENT wndPlace;
    wndPlace.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(m_hWnd, &wndPlace);

	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERWPOS) ? 1 : 0);
	WritePrivateProfileString(_T("Window"), _T("RecoverPos"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), wndPlace.rcNormalPosition.left);
	WritePrivateProfileString(_T("Window"), _T("Left"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), wndPlace.rcNormalPosition.top);
	WritePrivateProfileString(_T("Window"), _T("Top"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERWSIZE) ? 1 : 0);
	WritePrivateProfileString(_T("Window"), _T("RecoverSize"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), wndPlace.rcNormalPosition.right 
		- wndPlace.rcNormalPosition.left);
	WritePrivateProfileString(_T("Window"), _T("Width"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), wndPlace.rcNormalPosition.bottom 
		- wndPlace.rcNormalPosition.top);
	WritePrivateProfileString(_T("Window"), _T("Height"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), (wndPlace.showCmd == SW_SHOWMAXIMIZED ||
		wndPlace.showCmd == SW_MAXIMIZE) ? 1 : 0);
	WritePrivateProfileString(_T("Window"), _T("Zoomed"), buf, 
		initFilePath.c_str());

	// 表示・非表示の設定
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERVIDEOSCREENVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverVideoScreen"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_VIDEOSCREEN) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("VideoScreen"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_LYRICS) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Lyrics"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_PITCHANALYSER) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("PitchAnalyser"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERTIMESLIDERVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverTimeSlider"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_TIMESLIDER) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("TimeSlider"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EXPLORER) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Explorer"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERSPEEDVISIBLE) ? 1 : 0 ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverSpeed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_SPEED) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Speed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERFREQVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverFrequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FREQ) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Frequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERPITCHVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverPitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_PITCH) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Pitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERVOLUMEVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverVolume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_VOLUME) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Volume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERPANVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverPan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_PAN) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Pan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVEREQVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverEQ"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ20) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq20"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ25) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq25"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ31_5) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq31_5"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ40) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq40"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ50) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq50"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ63) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq63"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ80) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq80"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ100) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq100"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ125) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq125"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ160) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq160"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ200) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq200"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ250) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq250"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ315) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq315"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ400) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq400"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ500) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq500"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ630) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq630"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ800) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq800"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ1K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq1k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ1_25K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq1_25k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ1_6K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq1_6k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ2K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq2k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ2_5K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq2_5k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ3_15K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq3_15k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ4K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq4k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ5K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq5k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ6_3K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq6_3k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ8K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq8k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ10K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq10k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ12_5K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq12_5k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ16K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq16k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_EQ20K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq20k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_TAB) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Tab"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERLISTVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverPlayList"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_PLAYLIST) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("PlayList"), buf, 
		initFilePath.c_str());
	int nCount   = SendMessage(*m_toolBar, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < (int)m_toolBar->GetArrayButton().size(); i++) {
		TBBUTTON btn;
		ZeroMemory(&btn, sizeof(TBBUTTON));
		SendMessage(*m_toolBar, TB_GETBUTTON, i, (LPARAM)&btn);
		TCHAR key[255];
		_stprintf_s(key, _T("ToolBar%d"), i);
		_stprintf_s(buf, _T("%d"), i < nCount ? btn.idCommand : -1);
		WritePrivateProfileString(_T("Visible"), key, buf,
			initFilePath.c_str());
	}

	// 再生モードの設定
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERSLOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverSingleLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_sound->IsLoop() ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("SingleLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERALOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverAllLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_ALOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("AllLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERRANDOM) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverRandom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RANDOM) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Random"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERCONTINUE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverContinue"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_CONTINUE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Continue"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_SAMEARTIST) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("SameArtist"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERINSTANTLOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverInstantLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), bInstantLoop ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("InstantLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu->IsItemChecked(ID_RECOVERSETPOSITIONAUTO) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverSetPositionAuto"), 
		buf, initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), bSetPositionAuto ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("SetPositionAuto"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERREVERSE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverReverse"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_REVERSE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Reverse"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERRECORD) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverRecord"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECORD) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Record"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_NORMALIZE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Normalize"), buf, 
		initFilePath.c_str());

	// ショートカットキー設定
	CCommandList cmdlist;
	WritePrivateProfileSection(_T("KeySetting"), NULL, initFilePath.c_str());
	CAcceleratorTable & accelTable = m_rApp.GetAccelTable();
	int nAccel = accelTable.GetNum();
	for(int i = 0; i < nAccel; i++) {
		WritePrivateProfileString(_T("KeySetting"),
			EscapeKeystr(accelTable.GetShortCut(i).c_str()),
			cmdlist.GetCommandName(accelTable.GetCommandId(i)).c_str(),
			initFilePath.c_str());
	}

	// グローバルホットキー設定
	WritePrivateProfileSection(_T("OutKeySetting"), NULL, 
		initFilePath.c_str());
	CListView & list = outKeySettingWnd->GetList();
	for(int i = 0; i < list.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		TCHAR szCommand[255];
		list.GetItemText(i, 0, szShortCut, 255);
		list.GetItemText(i, 1, szCommand, 255);

		WritePrivateProfileString(_T("OutKeySetting"),
			EscapeKeystr(szShortCut),
			szCommand,
			initFilePath.c_str());
	}

	// その他の設定
	WritePrivateProfileString(_T("Options"), _T("LAMECommandLine"),
		m_strLAMECommandLine.c_str(), initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERSPEED) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverSpeed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_speedSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Speed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERFREQ) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverFrequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_freqSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Frequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERPITCH) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverPitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_pitchSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Pitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERVOLUME) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverVolume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_volumeSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Volume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERPAN) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverPan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_panSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Pan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVEREQ) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverEQ"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq20Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ20"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq25Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ25"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq31_5Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ31.5"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq40Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ40"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq50Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ50"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq63Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ63"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq80Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ80"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq100Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ100"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq125Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ125"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq160Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ160"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq200Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ200"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq250Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ250"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq315Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ315"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq400Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ400"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq500Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ500"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq630Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ630"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq800Slider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ800"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1_25kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1.25K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1_6kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1.6K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq2kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ2K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq2_5kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ2.5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq3_15kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ3.15K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq4kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ4K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq5kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq6_3kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ6.3K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq8kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ8K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq10kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ10K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq12_5kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ12.5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq16kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ16K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq20kSlider->GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ20K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERLIST) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverList"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_DOUBLERUN) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("DoubleRun"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), GetExStyle() & WS_EX_TOPMOST ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("TopMost"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_TASKTRAY) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("TaskTray"), buf,
		initFilePath.c_str());
	WritePrivateProfileString(_T("Options"), _T("SaveFormat"), 
		strSaveFormat.c_str(), initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_speedSlider->GetRangeMin()
		/ pow(10.0, m_speedSlider->GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MinimumSpeed"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%4.1f"), m_speedSlider->GetRangeMax()
		/ pow(10.0, m_speedSlider->GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MaximumSpeed"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_speedSlider->GetDecimalDigit());
	WritePrivateProfileString(_T("Options"), _T("SpeedDecimalDigit"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_freqSlider->GetRangeMin()
		/ pow(10.0, m_freqSlider->GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MinimumFrequency"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%4.1f"), m_freqSlider->GetRangeMax()
		/ pow(10.0, m_freqSlider->GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MaximumFrequency"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_freqSlider->GetDecimalDigit());
	WritePrivateProfileString(_T("Options"), _T("FrequencyDecimalDigit"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_pitchSlider->GetRangeMin()
		/ pow(10.0, m_pitchSlider->GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MinimumPitch"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_pitchSlider->GetRangeMax()
		/ pow(10.0, m_pitchSlider->GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MaximumPitch"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_pitchSlider->GetDecimalDigit());
	WritePrivateProfileString(_T("Options"), _T("PitchDecimalDigit"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FADEOUTSTOP) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("FadeoutStop"), buf,
		initFilePath.c_str());
	if(m_menu->IsItemChecked(ID_FADEOUTSTOP1SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("1000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP2SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("2000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP4SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("4000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP5SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("5000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP6SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("6000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP7SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("7000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP8SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("8000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP9SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("9000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTSTOP10SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("10000"), initFilePath.c_str());
	else
		WritePrivateProfileString(_T("Options"), _T("FadeoutStopTime"),
		_T("3000"), initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_FADEOUTNEXT) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("FadeoutNext"), buf,
		initFilePath.c_str());
	if(m_menu->IsItemChecked(ID_FADEOUTNEXT1SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("1000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT2SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("2000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT4SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("4000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT5SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("5000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT6SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("6000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT7SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("7000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT8SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("8000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT9SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("9000"), initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_FADEOUTNEXT10SEC))
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("10000"), initFilePath.c_str());
	else
		WritePrivateProfileString(_T("Options"), _T("FadeoutNextTime"),
		_T("3000"), initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), nCurPlayTab);
	WritePrivateProfileString(_T("Options"), _T("CurPlayTab"), buf,
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_sound->GetCurFileNum() - 1);
	WritePrivateProfileString(_T("Options"), _T("CurFileNum"), buf,
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu->IsItemChecked(ID_RECOVERPLAYPOS) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverPlayPos"), buf,
		initFilePath.c_str());
	_stprintf_s(buf, _T("%f"), m_sound->ChannelGetSecondsPosition());
	WritePrivateProfileString(_T("Options"), _T("PlayPos"), buf,
		initFilePath.c_str());
	if(m_sound->IsABLoopA())
		_stprintf_s(buf, _T("%.3f"), m_sound->GetLoopPosA_sec());
	else _stprintf_s(buf, _T("%.3f"), -1.000);
	WritePrivateProfileString(_T("Options"), _T("ABLoopPosA"), buf,
		initFilePath.c_str());
	if(m_sound->IsABLoopB())
		_stprintf_s(buf, _T("%.3f"), m_sound->GetLoopPosB_sec());
	else _stprintf_s(buf, _T("%.3f"), -1.000);
	WritePrivateProfileString(_T("Options"), _T("ABLoopPosB"), buf,
		initFilePath.c_str());
	if(bMarkerPlay) {
		std::vector<QWORD> arrayMarker = m_sound->GetArrayMarker();
		int max = (int)arrayMarker.size();
		int i = 0;
		for(; i < max; i++) {
			_stprintf_s(buf, _T("%d"), arrayMarker[i]);
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("MarkerPos%d"), i + 1);
			WritePrivateProfileString(_T("Options"), chKey, buf,
				initFilePath.c_str());
		}
		while(TRUE) {
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("MarkerPos%d"), i + 1);
			if(GetPrivateProfileInt(_T("Options"), chKey, 0,
					initFilePath.c_str()) > 0)
				WritePrivateProfileString(_T("Options"), chKey, NULL,
					initFilePath.c_str());
			else break;
			i++;
		}
	}
	else {
		int i = 0;
		while(TRUE) {
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("MarkerPos%d"), i + 1);
			if(GetPrivateProfileInt(_T("Options"), chKey, 0,
					initFilePath.c_str()) > 0)
				WritePrivateProfileString(_T("Options"), chKey, NULL,
					initFilePath.c_str());
			else break;
			i++;
		}
	}
	for(int i = 0; i < (int)m_arrayList.size(); i++) {
		int nColCount = Header_GetItemCount(
			ListView_GetHeader(*m_arrayList[i]));
		int* pnOrderArray = new int[nColCount];
		ListView_GetColumnOrderArray(*m_arrayList[i], nColCount, pnOrderArray);
		for(int j = 0; j < nColCount; j++) {
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("ListColumn%dWidth%d"), i, j);
			int nWidth = ListView_GetColumnWidth(*m_arrayList[i], j);
			TCHAR chValue[255];
			_stprintf_s(chValue, _T("%d"), nWidth);
			WritePrivateProfileString(_T("Options"), chKey, chValue,
									  initFilePath.c_str());
		}
		for(int j = 0; j < nColCount; j++) {
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("ListColumn%dOrder%d"), i, j);
			TCHAR chValue[255];
			_stprintf_s(chValue, _T("%d"), pnOrderArray[j]);
			WritePrivateProfileString(_T("Options"), chKey, chValue,
									  initFilePath.c_str());
		}
		delete pnOrderArray;
	}
	WritePrivateProfileString(_T("PlayList"), NULL, NULL, 
		initFilePath.c_str());
	for(int i = 0; i < (int)m_arrayList.size(); i++) {
		TCHAR chKey[255];
		_stprintf_s(chKey, _T("Title%d"), i);
		TCHAR chValue[255];
		TCITEM tc;
		tc.mask = TCIF_TEXT;
		tc.pszText = chValue;
		tc.cchTextMax = 255;
		SendMessage(*m_tab, TCM_GETITEM, i, (LPARAM)&tc);
		WritePrivateProfileString(_T("PlayList"), chKey, chValue,
									  initFilePath.c_str());
		for(int j = 0; j < (int)m_arrayList[i]->GetItemCount(); j++) {
			TCHAR filePath[MAX_PATH];
			m_arrayList[i]->GetItemText(j, 7, filePath, MAX_PATH);
			TCHAR chKey[255];
			_stprintf_s(chKey, _T("Item%d-%d"), i, j);
			WritePrivateProfileString(_T("PlayList"), chKey, filePath,
									  initFilePath.c_str());
		}
	}
	if(m_menu->IsItemChecked(ID_TOOLBAR_SIZES))
		WritePrivateProfileString(_T("Options"), _T("Toolbar"), _T("Small"), 
			initFilePath.c_str());
	else if(m_menu->IsItemChecked(ID_TOOLBAR_SIZEM))
		WritePrivateProfileString(_T("Options"), _T("Toolbar"), _T("Medium"), 
			initFilePath.c_str());
	else
		WritePrivateProfileString(_T("Options"), _T("Toolbar"), _T("Large"), 
			initFilePath.c_str());
	WritePrivateProfileString(_T("Options"), _T("ExplorerPath"),
		m_explorerBar->GetEdit().GetText().c_str(),  initFilePath.c_str());
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CMainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_menu->OnCommand(id, hwndCtl, codeNotify);
	else if(hwndCtl == (HWND)*m_toolBar)
		m_toolBar->OnCommand(id, hwndCtl, codeNotify);
	CSnapWnd::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// 閉じられようとしている
//----------------------------------------------------------------------------
void CMainWnd::OnClose()
{
	if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) Pause();

	Show(SW_HIDE);
	WriteInitFile();

	NOTIFYICONDATA ni;
	ZeroMemory(&ni, sizeof(NOTIFYICONDATA));
	ni.cbSize = sizeof(NOTIFYICONDATA);
	ni.hWnd = m_hWnd;
	ni.uID = 1;
	Shell_NotifyIcon(NIM_DELETE, &ni);

	CSnapWnd::OnClose();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_hVideoScreenBrush = CreateSolidBrush(RGB(0, 0, 0));

	SetMainWnd(true); // メインウィンドウに設定
	SetStyle(WS_OVERLAPPEDWINDOW);
	SetExStyle(WS_EX_ACCEPTFILES);
	SetIcon(LoadIcon(GetModuleHandle(NULL), (LPCTSTR)IDI_ICON1), TRUE);
	SetIcon(LoadIcon(GetModuleHandle(NULL), (LPCTSTR)IDI_ICON1), FALSE);
	SetSize(340, 240);

	// メニューの作成
	if(!m_menu->Create() || !SetMenu(*m_menu)) {
#if JP
		m_rApp.ShowError(_T("メニューの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create menu."));
#endif // JP
		return FALSE;
	}

	TCHAR chPath[255];
	lstrcpy(chPath, (m_rApp.GetFilePath() + _T("Setting.ini")).c_str());

	BOOL bVideoScreenVisible = TRUE, bTimeSliderVisible = TRUE,
		bSpeedVisible = TRUE, bFreqVisible = TRUE, bPitchVisible = TRUE,
		bVolumeVisible = TRUE, bPanVisible = TRUE, bEQVisible = TRUE,
		bListVisible = TRUE;
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverVideoScreen"), 1, chPath))
	{
		m_menu->SwitchItemChecked(ID_RECOVERVIDEOSCREENVISIBLE);
		bVideoScreenVisible = GetPrivateProfileInt(_T("Visible"),
								_T("VideoScreen"), 0, chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverTimeSlider"), 1, chPath))
	{
		m_menu->SwitchItemChecked(ID_RECOVERTIMESLIDERVISIBLE);
		bTimeSliderVisible = GetPrivateProfileInt(_T("Visible"),
								_T("TimeSlider"), 1, chPath);
	}
	BOOL bExplorerVisible = GetPrivateProfileInt(_T("Visible"), _T("Explorer"),
								0, chPath);
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverSpeed"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERSPEEDVISIBLE);
		bSpeedVisible = GetPrivateProfileInt(_T("Visible"), _T("Speed"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverFrequency"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERFREQVISIBLE);
		bFreqVisible = GetPrivateProfileInt(_T("Visible"), _T("Frequency"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverPitch"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERPITCHVISIBLE);
		bPitchVisible = GetPrivateProfileInt(_T("Visible"), _T("Pitch"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverVolume"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERVOLUMEVISIBLE);
		bVolumeVisible = GetPrivateProfileInt(_T("Visible"), _T("Volume"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverPan"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERPANVISIBLE);
		bPanVisible = GetPrivateProfileInt(_T("Visible"), _T("Pan"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverEQ"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVEREQVISIBLE);
		bEQVisible = GetPrivateProfileInt(_T("Visible"), _T("EQ"), 0,
			chPath);
	}
	BOOL bTabVisible = GetPrivateProfileInt(_T("Visible"), _T("Tab"), 1,
						chPath);
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverPlayList"), 1, chPath)) {
		m_menu->SwitchItemChecked(ID_RECOVERLISTVISIBLE);
		bListVisible = GetPrivateProfileInt(_T("Visible"), _T("PlayList"), 1,
			chPath);
	}

	if(!CreateControls(TRUE, bVideoScreenVisible, bTimeSliderVisible,
			bExplorerVisible, bSpeedVisible, bFreqVisible, bPitchVisible,
			bVolumeVisible, bPanVisible, bEQVisible, bTabVisible))
		return FALSE;
	if(bVideoScreenVisible) SetVideoScreenVisible();
	if(bTimeSliderVisible) SetTimeSliderVisible();
	if(bExplorerVisible) SetExplorerVisible();
	if(bSpeedVisible) SetSpeedVisible();
	if(bFreqVisible) SetFreqVisible();
	if(bPitchVisible) SetPitchVisible();
	if(bVolumeVisible) SetVolumeVisible();
	if(bPanVisible) SetPanVisible();
	if(bEQVisible) SetEQVisible();
	if(bListVisible) SetPlayListVisible();
	if(!bTabVisible) SetTabVisible();

	int nWidth = m_toolBar->GetWidth() + m_timeLabel->GetWidth()
				 + controlOffset * 2;
	POINT pt;
	pt.y = m_toolBar->GetTop();
	ScreenToClient(m_hWnd, &pt);
	int nHeight = pt.y + m_toolBar->GetHeight();
	SetClientSize(nWidth, nHeight, TRUE);
	nMinWidth = GetWidth();
	m_timeLabel->SetTime(0, 0);

	SetCaption(m_rApp.GetName().c_str());
	OpenInitFile();
	Update();
	if(!CreateControls(FALSE, !bVideoScreenVisible, !bTimeSliderVisible,
			!bExplorerVisible, !bSpeedVisible, !bFreqVisible, !bPitchVisible,
			!bVolumeVisible, !bPanVisible, !bEQVisible, !bTabVisible))
		return FALSE;

	// bass の初期化
	if(!m_sound->Init(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("BASS の初期化に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to init BASS.DLL."));
#endif // JP
		return FALSE;
	}

	OpenInitFileAfterShow();

	// アイコンにドロップされたファイルを読み込む
	for(int i = 1; i < __argc; i++)
		m_arrayList[0]->AddFile(__targv[i]);

	if(__argc > 1) {
		nCurPlayTab = 0;
		Play(m_arrayList[0]->GetItemCount()-1);
		StartUpdateInfo();
	}

	SetPreviousNextMenuState();

	tstring strClick = m_rApp.GetFilePath() + _T("sound\\click.wav");
	HANDLE fh = CreateFile(strClick.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(fh,NULL);
	lpSound = (LPCTSTR)HeapAlloc(GetProcessHeap(),
								 HEAP_ZERO_MEMORY, dwFileSize);
	ReadFile(fh, (LPVOID)lpSound, dwFileSize, &dwFileSize, NULL);
	CloseHandle(fh);

	HANDLE hHandle = (HANDLE)_beginthread(&CMainWnd::UpdateTimeThreadProc,
		0, this);

	return CSnapWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// 背景色の設定
//----------------------------------------------------------------------------
HBRUSH CMainWnd::OnCtlColorStatic(HDC hDc, HWND hWnd)
{
	if(hWnd == *m_videoScreen) return m_hVideoScreenBrush;
	return CFrameWnd::OnCtlColorStatic(hDc, hWnd);
}
//----------------------------------------------------------------------------
// 終了
//----------------------------------------------------------------------------
void CMainWnd::OnDestroy()
{
	DeleteObject(m_hVideoScreenBrush);
	KillTimer(IDT_METRONOME);
	HeapFree(GetProcessHeap(), 0, (LPVOID)lpSound);
	for(int i = 0; i < (int)m_arrayList.size(); i++) {
		CPlayListView_MainWnd* pList = m_arrayList[i];
		delete pList;
	}
	CSnapWnd::OnDestroy();
}
//----------------------------------------------------------------------------
// ファイルがドロップされた
//----------------------------------------------------------------------------
void CMainWnd::OnDropFiles(HDROP hdrop)
{
	AddDropFiles(hdrop, TRUE);
	CSnapWnd::OnDropFiles(hdrop);
}
//----------------------------------------------------------------------------
// 最大・最小サイズの設定
//----------------------------------------------------------------------------
void CMainWnd::OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo)
{
	int nItemWidth = 0;
	if(m_menu->IsItemChecked(ID_TOOLBAR_SIZES))
		nItemWidth = 20;
	else if(m_menu->IsItemChecked(ID_TOOLBAR_SIZEM))
		nItemWidth = 24;
	else nItemWidth = 28;
	int nWidth = m_timeLabel->GetWidth() + 20;

	int nCount = SendMessage(*m_toolBar, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < (int)nCount; i++) {
		TBBUTTON btn;
		ZeroMemory(&btn, sizeof(TBBUTTON));
		SendMessage(*m_toolBar, TB_GETBUTTON, i, (LPARAM)&btn);
		if(btn.idCommand == 0) nWidth += 7;
		else nWidth += nItemWidth;
	}

	lpMinMaxInfo->ptMinTrackSize.x = nWidth;

	if(!IsZoomed(m_hWnd)) {
		if(m_arrayList.size() > 0 && m_menu->IsItemChecked(ID_PLAYLIST)) {
			int nHeight = m_arrayList[nCurPlayTab]->GetTop() - GetTop()
						  + m_arrayList[0]->GetMinSize()
						  + GetSystemMetrics(SM_CYBORDER)
						  + GetSystemMetrics(SM_CYEDGE);
			lpMinMaxInfo->ptMinTrackSize.y = nHeight;
		}
		else if(m_menu->IsItemChecked(ID_EQ)) {
			int nEQLabelBottom = m_eq20kLabel->GetTop()
				+ m_eq20kLabel->GetHeight();
			int nEQSliderBottom = m_eq20kSlider->GetTop()
				+ m_eq20kSlider->GetHeight();
			int nBigger = nEQLabelBottom > nEQSliderBottom
				? nEQLabelBottom : nEQSliderBottom;
			lpMinMaxInfo->ptMinTrackSize.y = nBigger + controlOffset * 2
				- GetTop();
		}
		else if(m_menu->IsItemChecked(ID_PAN)) {
			int nPanLabelBottom = m_panLabel->GetTop() + m_panLabel->GetHeight();
			int nPanSliderBottom = m_panSlider->GetTop()
				+ m_panSlider->GetHeight();
			int nBigger = nPanLabelBottom > nPanSliderBottom
				? nPanLabelBottom : nPanSliderBottom;
			lpMinMaxInfo->ptMinTrackSize.y = nBigger + controlOffset * 2
				- GetTop();
		}
		else if(m_menu->IsItemChecked(ID_VOLUME)) {
			int nVolumeLabelBottom = m_volumeLabel->GetTop() + m_volumeLabel->GetHeight();
			int nVolumeSliderBottom = m_volumeSlider->GetTop()
				+ m_volumeSlider->GetHeight();
			int nBigger = nVolumeLabelBottom > nVolumeSliderBottom
				? nVolumeLabelBottom : nVolumeSliderBottom;
			lpMinMaxInfo->ptMinTrackSize.y = nBigger + controlOffset * 2
				- GetTop();
		}
		else if(m_menu->IsItemChecked(ID_PITCH)) {
			int nPitchLabelBottom = m_pitchLabel->GetTop()
				+ m_pitchLabel->GetHeight();
			int nPitchSliderBottom = m_pitchSlider->GetTop()
				+ m_pitchSlider->GetHeight();
			int nBigger = nPitchLabelBottom > nPitchSliderBottom
				? nPitchLabelBottom : nPitchSliderBottom;
			lpMinMaxInfo->ptMinTrackSize.y = nBigger + controlOffset * 2
				- GetTop();
		}
		else if(m_menu->IsItemChecked(ID_FREQ)) {
			int nFreqLabelBottom = m_freqLabel->GetTop()
				+ m_freqLabel->GetHeight();
			int nFreqSliderBottom = m_freqSlider->GetTop()
				+ m_freqSlider->GetHeight();
			int nBigger = nFreqLabelBottom > nFreqSliderBottom
				? nFreqLabelBottom : nFreqSliderBottom;
			lpMinMaxInfo->ptMinTrackSize.y = nBigger + controlOffset * 2
				- GetTop();
		}
		else if(m_menu->IsItemChecked(ID_SPEED)) {
			int nSpeedLabelBottom = m_speedLabel->GetTop()
				+ m_speedLabel->GetHeight();
			int nSpeedSliderBottom = m_speedSlider->GetTop()
				+ m_speedSlider->GetHeight();
			int nBigger = nSpeedLabelBottom > nSpeedSliderBottom
				? nSpeedLabelBottom : nSpeedSliderBottom;
			lpMinMaxInfo->ptMinTrackSize.y = nBigger + controlOffset * 2
				- GetTop();
		}
		else if(m_menu->IsItemChecked(ID_TIMESLIDER)) {
			lpMinMaxInfo->ptMinTrackSize.y = m_timeSlider->GetTop()
				+ m_timeSlider->GetHeight() + controlOffset * 2 - GetTop();
		}
		else {
			lpMinMaxInfo->ptMinTrackSize.y = m_toolBar->GetTop()
				+ m_toolBar->GetHeight() + controlOffset - GetTop();
		}
		if(m_menu->IsItemChecked(ID_VIDEOSCREEN)
			&& !m_menu->IsItemChecked(ID_PLAYLIST))
			lpMinMaxInfo->ptMinTrackSize.y -= m_videoScreen->GetHeight();
	}

	CSnapWnd::OnGetMinMaxInfo(lpMinMaxInfo);
}
//----------------------------------------------------------------------------
// ホットキーが送られた
//----------------------------------------------------------------------------
void CMainWnd::OnHotKey(int idHotKey, UINT fuModifiers, UINT vk)
{
	m_menu->OnCommand(idHotKey, 0, 0);
	CFrameWnd::OnHotKey(idHotKey, fuModifiers, vk);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CMainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) SetFocusNextTab();
		else SetFocusNextControl();
	}
	CFrameWnd::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// 左クリックが押された
//----------------------------------------------------------------------------
void CMainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	POINT pt;
	pt.y = m_toolBar->GetTop();
	ScreenToClient(m_hWnd, &pt);

	int nToolBarBottom = pt.y + m_toolBar->GetHeight() + controlOffset;
	int nVideoBottom = nToolBarBottom + m_videoScreen->GetHeight();

	int nDrag = GetSystemMetrics(SM_CXDRAG);
	if(m_menu->IsItemChecked(ID_EXPLORER) && m_explorer->GetWidth() <= x &&
			x <= m_explorer->GetWidth() + nDrag && nToolBarBottom <= y) {
		m_bExplorerResizing = TRUE;
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		SetCapture(m_hWnd);
	}
	if(m_menu->IsItemChecked(ID_VIDEOSCREEN) && m_explorer->GetWidth() <= x &&
			nVideoBottom - nDrag / 2 <= y && y <= nVideoBottom + nDrag / 2) {
		m_bVideoScreenResizing = TRUE;
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		SetCapture(m_hWnd);
	}

	CSnapWnd::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// 左クリックが離された
//----------------------------------------------------------------------------
void CMainWnd::OnLButtonUp(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		m_bExplorerResizing = FALSE;
		m_bVideoScreenResizing = FALSE;
		ReleaseCapture();
		ResetAllControlPos();
		ResetSize();
	}

	CSnapWnd::OnLButtonUp(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// マウスが動かされた
//----------------------------------------------------------------------------
void CMainWnd::OnMouseMove(int x, int y, UINT keyFlags)
{
	POINT pt;
	pt.y = m_toolBar->GetTop();
	ScreenToClient(m_hWnd, &pt);

	int nToolBarBottom = pt.y + m_toolBar->GetHeight() + controlOffset;
	int nVideoBottom = nToolBarBottom + m_videoScreen->GetHeight();

	if(GetCapture() == m_hWnd) {
		if(m_bExplorerResizing) {
			m_explorerBar->SetSize(x, m_explorerBar->GetHeight());
			m_explorer->SetSize(x, m_explorer->GetHeight());
			SetWindowPos(*m_explorerBar, HWND_TOP, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE);
			SetWindowPos(*m_explorer, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE |
				SWP_NOSIZE);
		}
		else if(m_bVideoScreenResizing) {
			m_videoScreen->SetSize(m_videoScreen->GetWidth(), y - nToolBarBottom);
			m_videoScreen->ResetSize();
		}
	}

	CSnapWnd::OnMouseMove(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// コモンコントロールからの通知が来た
//----------------------------------------------------------------------------
LRESULT CMainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->hwndFrom == (HWND)*m_timeSlider) {
		switch(pnmhdr->code)
		{
		case NM_CUSTOMDRAW:
			LPNMCUSTOMDRAW lpCustomDraw = (LPNMCUSTOMDRAW)pnmhdr;

			if(lpCustomDraw->dwDrawStage == CDDS_PREPAINT)
				return CDRF_NOTIFYITEMDRAW;
			else if(lpCustomDraw->dwDrawStage == CDDS_ITEMPREPAINT)
				return CDRF_NOTIFYPOSTPAINT;
			else if(lpCustomDraw->dwDrawStage == CDDS_ITEMPOSTPAINT) {
				if(lpCustomDraw->dwItemSpec == TBCD_CHANNEL) {
					if(bMarkerPlay) {
						COLORREF color = ::GetSysColor(COLOR_HIGHLIGHT);
						HBRUSH hBrush = CreateSolidBrush(color);

						RECT rc;
						m_timeSlider->GetSelRect(&rc);

						int width = rc.right - rc.left;
						int height = rc.bottom - rc.top;

						QWORD length = m_sound->ChannelGetLength();
						std::vector<QWORD> arrayMarker
							= m_sound->GetArrayMarker();
						for(int i = 0; i < (int)arrayMarker.size(); i++) {
							double rate = (double)(int)(arrayMarker[i]
								/ 100000) / (double)(int)(length / 100000);
							lpCustomDraw->rc.left = LONG(rc.left + width
								* rate + 0.5);
							lpCustomDraw->rc.top = rc.top + 3;
							lpCustomDraw->rc.right = lpCustomDraw->rc.left + 1;
							lpCustomDraw->rc.bottom = rc.bottom - 3;
							FillRect(lpCustomDraw->hdc,
								&lpCustomDraw->rc, hBrush);
						}

						DeleteObject(hBrush);

						return CDRF_SKIPDEFAULT;
					}
				}
			}
			break;
		}
	}
	else if(pnmhdr->hwndFrom == (HWND)*m_toolBar)
	{
		LPTBNOTIFY ptbn = (LPTBNOTIFY)pnmhdr;
		switch(pnmhdr->code)
		{
		case TBN_BEGINDRAG:
			m_toolBar->OnBeginDrag((NMTOOLBAR *)pnmhdr);
			break;
		case TBN_ENDDRAG:
			m_toolBar->OnEndDrag((NMTOOLBAR *)pnmhdr);
			break;
		case TBN_QUERYINSERT:
			return TRUE;
		case TBN_QUERYDELETE:
			return TRUE;
		case TBN_GETBUTTONINFO:
			{
				std::vector<TBBUTTON> m_arrayButton
					= m_toolBar->GetArrayButton();
				int n = ptbn->iItem;
				if (n >= (int)m_arrayButton.size())
					return FALSE;
				ptbn->tbButton = m_arrayButton[n];
				CCommandList cmdlist;
				tstring text
					= cmdlist.GetCommandName(m_arrayButton[n].idCommand);
				ptbn->cchText = sizeof(text.c_str());
				_tcscpy_s(ptbn->pszText, text.length() + 1, text.c_str());
				return TRUE;
				break;
			}
		case TBN_RESET:
			{
				std::vector<TBBUTTON> m_arrayButton
					= m_toolBar->GetArrayButton();
				int b = SendMessage(*m_toolBar, TB_BUTTONCOUNT, 0, 0);
				for(int i = 0; i < b; i++)
					SendMessage(*m_toolBar, TB_DELETEBUTTON, 0, 0);
				SendMessage(*m_toolBar, TB_ADDBUTTONS, 23,
					(LPARAM)&m_arrayButton[0]);
				m_toolBar->SetPlayingState(!m_sound->ChannelIsStopped());
				m_toolBar->SetPausingState(m_sound->ChannelIsPausing());
				m_toolBar->CheckButton(ID_ALOOP,
					m_menu->IsItemChecked(ID_ALOOP));
				m_toolBar->CheckButton(ID_RANDOM,
					m_menu->IsItemChecked(ID_RANDOM));
				m_toolBar->SetMarkerPlayState(bMarkerPlay);
				if(!bMarkerPlay)
					m_toolBar->SetABLoopState(m_sound->IsABLoopA(),
						m_sound->IsABLoopB());
				m_toolBar->SetSingleLoopState(m_sound->IsLoop());
				m_toolBar->CheckButton(ID_PLAYLIST,
					m_menu->IsItemChecked(ID_PLAYLIST));
				m_toolBar->CheckButton(ID_EXPLORER,
					m_menu->IsItemChecked(ID_EXPLORER));
				break;
			}
		case TBN_ENDADJUST:
		case TBN_TOOLBARCHANGE:
			m_toolBar->SetPlayingState(!m_sound->ChannelIsStopped());
			m_toolBar->SetPausingState(m_sound->ChannelIsPausing());
			m_toolBar->CheckButton(ID_ALOOP,
				m_menu->IsItemChecked(ID_ALOOP));
			m_toolBar->CheckButton(ID_RANDOM,
				m_menu->IsItemChecked(ID_RANDOM));
			m_toolBar->SetMarkerPlayState(bMarkerPlay);
			if(!bMarkerPlay)
				m_toolBar->SetABLoopState(m_sound->IsABLoopA(),
					m_sound->IsABLoopB());
			m_toolBar->SetSingleLoopState(m_sound->IsLoop());
			m_toolBar->CheckButton(ID_PLAYLIST,
				m_menu->IsItemChecked(ID_PLAYLIST));
			m_toolBar->CheckButton(ID_EXPLORER,
				m_menu->IsItemChecked(ID_EXPLORER));
			break;
		}
	}
	else if(pnmhdr->hwndFrom == (HWND)*m_explorer) {
		switch(pnmhdr->code)
		{
		case LVN_GETDISPINFO:
			m_explorer->OnGetDispInfo(pnmhdr);
			break;
		case LVN_COLUMNCLICK:
			m_explorer->Sort((NMLISTVIEW *)pnmhdr);
			break;
		case LVN_BEGINDRAG:
			m_explorer->OnBeginDrag((NM_LISTVIEW *)pnmhdr);
			break;
		}
	}
	else if(pnmhdr->hwndFrom == (HWND)*m_tab) {
		switch(pnmhdr->code)
		{
		case TCN_SELCHANGE:
			int nSelect = m_tab->GetCurrentFocus();
			for(int i = 0; i < (int)m_arrayList.size(); i++)
				m_arrayList[i]->Show(SW_HIDE);
			m_arrayList[nSelect]->Show(SW_SHOW);
			break;
		}
	}

	for(int i = 0; i < (int)m_arrayList.size(); i++)
	{
		if(pnmhdr->hwndFrom == (HWND)*m_arrayList[i])
		{
			switch(pnmhdr->code)
			{
			case NM_CUSTOMDRAW:
				return m_arrayList[i]->OnCustomDraw((NMLVCUSTOMDRAW *)pnmhdr);
			case LVN_BEGINDRAG:
				m_arrayList[i]->OnBeginDrag((NM_LISTVIEW *)pnmhdr);
				break;
			case LVN_BEGINLABELEDIT:
				return m_arrayList[i]->OnBeginLabelEdit((NM_LISTVIEW *)pnmhdr);
				break;
			case LVN_COLUMNCLICK:
				m_arrayList[i]->Sort((NMLISTVIEW *)pnmhdr);
				ResetCurFileNum();
				break;
			}
		}
	}
	return CSnapWnd::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
// サイズが変更された
//----------------------------------------------------------------------------
void CMainWnd::OnSize(UINT state, int cx, int cy)
{
	m_divider1->ResetSize(); m_timeLabel->ResetPos();
	ShowTime();
	if(m_menu->IsItemChecked(ID_EXPLORER)) m_explorer->ResetSize();
	m_videoScreen->ResetPos();
	m_videoScreen->ResetSize(); m_timeSlider->ResetPos();
	m_timeSlider->ResetSize(); m_divider2->ResetPos();
	m_divider2->ResetSize(); m_speedLabel->ResetPos();
	m_speedSlider->ResetPos(); m_speedSlider->ResetSize();
	m_freqLabel->ResetPos(); m_freqSlider->ResetPos();
	m_freqSlider->ResetSize(); m_pitchLabel->ResetPos();
	m_pitchSlider->ResetPos(); m_pitchSlider->ResetSize();
	m_divider3->ResetPos(); m_divider3->SetSize(cx, 2);
	m_volumeLabel->ResetPos(); m_volumeSlider->ResetPos();
	m_volumeSlider->ResetSize(); m_panLabel->ResetPos();
	m_panSlider->ResetPos(); m_panSlider->ResetSize();
	m_divider4->ResetPos(); m_divider4->SetSize(cx, 2);
	m_eq20Label->ResetPos(); m_eq20Slider->ResetPos();
	m_eq20Slider->ResetSize();
	m_eq25Label->ResetPos(); m_eq25Slider->ResetPos();
	m_eq25Slider->ResetSize();
	m_eq31_5Label->ResetPos(); m_eq31_5Slider->ResetPos();
	m_eq31_5Slider->ResetSize();
	m_eq40Label->ResetPos(); m_eq40Slider->ResetPos();
	m_eq40Slider->ResetSize();
	m_eq50Label->ResetPos(); m_eq50Slider->ResetPos();
	m_eq50Slider->ResetSize();
	m_eq63Label->ResetPos(); m_eq63Slider->ResetPos();
	m_eq63Slider->ResetSize();
	m_eq80Label->ResetPos(); m_eq80Slider->ResetPos();
	m_eq80Slider->ResetSize();
	m_eq100Label->ResetPos(); m_eq100Slider->ResetPos();
	m_eq100Slider->ResetSize();
	m_eq125Label->ResetPos(); m_eq125Slider->ResetPos();
	m_eq125Slider->ResetSize();
	m_eq160Label->ResetPos(); m_eq160Slider->ResetPos();
	m_eq160Slider->ResetSize();
	m_eq200Label->ResetPos(); m_eq200Slider->ResetPos();
	m_eq200Slider->ResetSize();
	m_eq250Label->ResetPos(); m_eq250Slider->ResetPos();
	m_eq250Slider->ResetSize();
	m_eq315Label->ResetPos(); m_eq315Slider->ResetPos();
	m_eq315Slider->ResetSize();
	m_eq400Label->ResetPos(); m_eq400Slider->ResetPos();
	m_eq400Slider->ResetSize();
	m_eq500Label->ResetPos(); m_eq500Slider->ResetPos();
	m_eq500Slider->ResetSize();
	m_eq630Label->ResetPos(); m_eq630Slider->ResetPos();
	m_eq630Slider->ResetSize();
	m_eq800Label->ResetPos(); m_eq800Slider->ResetPos();
	m_eq800Slider->ResetSize();
	m_eq1kLabel->ResetPos(); m_eq1kSlider->ResetPos();
	m_eq1kSlider->ResetSize();
	m_eq1_25kLabel->ResetPos(); m_eq1_25kSlider->ResetPos();
	m_eq1_25kSlider->ResetSize();
	m_eq1_6kLabel->ResetPos(); m_eq1_6kSlider->ResetPos();
	m_eq1_6kSlider->ResetSize();
	m_eq2kLabel->ResetPos(); m_eq2kSlider->ResetPos();
	m_eq2kSlider->ResetSize();
	m_eq2_5kLabel->ResetPos(); m_eq2_5kSlider->ResetPos();
	m_eq2_5kSlider->ResetSize();
	m_eq3_15kLabel->ResetPos(); m_eq3_15kSlider->ResetPos();
	m_eq3_15kSlider->ResetSize();
	m_eq4kLabel->ResetPos(); m_eq4kSlider->ResetPos();
	m_eq4kSlider->ResetSize();
	m_eq5kLabel->ResetPos(); m_eq5kSlider->ResetPos();
	m_eq5kSlider->ResetSize();
	m_eq6_3kLabel->ResetPos(); m_eq6_3kSlider->ResetPos();
	m_eq6_3kSlider->ResetSize();
	m_eq8kLabel->ResetPos(); m_eq8kSlider->ResetPos();
	m_eq8kSlider->ResetSize();
	m_eq10kLabel->ResetPos(); m_eq10kSlider->ResetPos();
	m_eq10kSlider->ResetSize();
	m_eq12_5kLabel->ResetPos(); m_eq12_5kSlider->ResetPos();
	m_eq12_5kSlider->ResetSize();
	m_eq16kLabel->ResetPos(); m_eq16kSlider->ResetPos();
	m_eq16kSlider->ResetSize();
	m_eq20kLabel->ResetPos(); m_eq20kSlider->ResetPos();
	m_eq20kSlider->ResetSize();
	m_divider5->ResetPos(); m_divider5->SetSize(cx, 2);
	m_tab->ResetPos(); m_tab->ResetSize();
	for(int i = 0; i < (int)m_arrayList.size(); i++) {
		m_arrayList[i]->ResetPos();
		m_arrayList[i]->ResetSize();
	}
	CSnapWnd::OnSize(state, cx, cy);
}
//----------------------------------------------------------------------------
// システムコマンドが送られた
//----------------------------------------------------------------------------
void CMainWnd::OnSysCommand(UINT cmd, int x, int y)
{
	if(cmd == SC_MINIMIZE && m_menu->IsItemChecked(ID_TASKTRAY)) {
		NOTIFYICONDATA ni;
		ZeroMemory(&ni, sizeof(NOTIFYICONDATA));
		ni.cbSize = sizeof(NOTIFYICONDATA);
		ni.hIcon = LoadIcon(GetModuleHandle(NULL), (LPCTSTR)IDI_ICON1);
		ni.hWnd = m_hWnd;
		ni.uCallbackMessage = WM_TRAY;
		ni.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		ni.uID = 1;
#if JP
		_tcscpy_s(ni.szTip, _tcslen(_T("聞々ハヤえもん")) + 1,
				  _T("聞々ハヤえもん"));
#else // JP
		_tcscpy_s(ni.szTip, _tcslen(_T("Hayaemon")) + 1,
				  _T("Hayaemon"));
#endif // JP
		Shell_NotifyIcon(NIM_ADD, &ni);
		Show(SW_HIDE);
		return;
	}
	CSnapWnd::OnSysCommand(cmd, x, y);
}
//----------------------------------------------------------------------------
// タスクトレイメッセージが送られた
//----------------------------------------------------------------------------
void CMainWnd::OnTray(UINT uMsg)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		NOTIFYICONDATA ni;
		ZeroMemory(&ni, sizeof(NOTIFYICONDATA));
		ni.cbSize = sizeof(NOTIFYICONDATA);
		ni.hWnd = m_hWnd;
		ni.uID = 1;
		Shell_NotifyIcon(NIM_DELETE, &ni);
		Show(SW_SHOW);
		SetForegroundWindow(m_hWnd);
		break;
	case WM_RBUTTONUP:
		CRMenu_Taskbar rMenu(*this);
		rMenu.Create();
		POINT pt;
		GetCursorPos(&pt);
		SetForegroundWindow(m_hWnd);
		TrackPopupMenu(rMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, 
					   m_hWnd, NULL);
		break;
	}
}
//----------------------------------------------------------------------------
// 横にスクロールされた
//----------------------------------------------------------------------------
void CMainWnd::OnHScroll(HWND hwndCtl, UINT code, int pos)
{
	if(hwndCtl == (HWND)*m_timeSlider)
		m_timeSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_speedSlider)
		m_speedSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_freqSlider)
		m_freqSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_pitchSlider)
		m_pitchSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_volumeSlider)
		m_volumeSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_panSlider)
		m_panSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq20Slider)
		m_eq20Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq25Slider)
		m_eq25Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq31_5Slider)
		m_eq31_5Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq40Slider)
		m_eq40Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq50Slider)
		m_eq50Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq63Slider)
		m_eq63Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq80Slider)
		m_eq80Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq100Slider)
		m_eq100Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq125Slider)
		m_eq125Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq160Slider)
		m_eq160Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq200Slider)
		m_eq200Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq250Slider)
		m_eq250Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq315Slider)
		m_eq315Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq400Slider)
		m_eq400Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq500Slider)
		m_eq500Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq630Slider)
		m_eq630Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq800Slider)
		m_eq800Slider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq1kSlider)
		m_eq1kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq1_25kSlider)
		m_eq1_25kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq1_6kSlider)
		m_eq1_6kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq2kSlider)
		m_eq2kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq2_5kSlider)
		m_eq2_5kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq3_15kSlider)
		m_eq3_15kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq4kSlider)
		m_eq4kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq5kSlider)
		m_eq5kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq6_3kSlider)
		m_eq6_3kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq8kSlider)
		m_eq8kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq10kSlider)
		m_eq10kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq12_5kSlider)
		m_eq12_5kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq16kSlider)
		m_eq16kSlider->OnHScroll(hwndCtl, code, pos);
	else if(hwndCtl == (HWND)*m_eq20kSlider)
		m_eq20kSlider->OnHScroll(hwndCtl, code, pos);
	CSnapWnd::OnHScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
// カーソル設定のタイミングが来た
//----------------------------------------------------------------------------
BOOL CMainWnd::OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg)
{
	// カーソルの位置を得る
	POINT ptCsr;
	GetCursorPos(&ptCsr);
	ScreenToClient(m_hWnd, &ptCsr);

	POINT pt;
	pt.y = m_toolBar->GetTop();
	ScreenToClient(m_hWnd, &pt);

	int nToolBarBottom = pt.y + m_toolBar->GetHeight() + controlOffset;
	int nVideoBottom = nToolBarBottom + m_videoScreen->GetHeight();

	// カーソルの設定
	int nDrag = GetSystemMetrics(SM_CXDRAG);
	if(m_explorer->GetWidth() <= ptCsr.x &&
			ptCsr.x <= m_explorer->GetWidth() + nDrag &&
			nToolBarBottom <= ptCsr.y) {
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return FALSE;
	}
	else if(m_explorer->GetWidth() <= ptCsr.x &&
			nVideoBottom - nDrag / 2 <= ptCsr.y &&
			ptCsr.y <= nVideoBottom + nDrag / 2) {
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		return FALSE;
	}

	return CSnapWnd::OnSetCursor(hwndCursor, codeHitTest, msg);
}
//----------------------------------------------------------------------------
// タイマーの周期が来た
//----------------------------------------------------------------------------
void CMainWnd::OnTimer(UINT id)
{
	switch(id)
	{
	case IDT_FADEOUT:
	{
		DWORD dwCurTime = timeGetTime();
		DWORD dwInterval = dwCurTime - dwFadeoutStartTime;
		DWORD dwFadeTime;
		if(m_menu->IsItemChecked(ID_FADEOUTSTOP1SEC)) dwFadeTime = 1000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP2SEC)) dwFadeTime = 2000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP4SEC)) dwFadeTime = 4000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP5SEC)) dwFadeTime = 5000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP6SEC)) dwFadeTime = 6000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP7SEC)) dwFadeTime = 7000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP8SEC)) dwFadeTime = 8000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP9SEC)) dwFadeTime = 9000;
		else if(m_menu->IsItemChecked(ID_FADEOUTSTOP10SEC)) dwFadeTime = 10000;
		else dwFadeTime = 3000;
		if(dwInterval >= dwFadeTime) Stop();
		else {
			double dVolume = pow(((double)dwFadeTime - (double)dwInterval)
								/ (double)dwFadeTime, 2.0);
			m_sound->ChannelSetAttribute(BASS_ATTRIB_VOL, (float)dVolume);
		}
		break;
	}
	case IDT_FADEOUTNEXT:
	{
		DWORD dwCurTime = timeGetTime();
		DWORD dwInterval = dwCurTime - dwFadeoutStartTime;
		DWORD dwFadeTime;
		if(m_menu->IsItemChecked(ID_FADEOUTNEXT1SEC)) dwFadeTime = 1000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT2SEC)) dwFadeTime = 2000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT4SEC)) dwFadeTime = 4000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT5SEC)) dwFadeTime = 5000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT6SEC)) dwFadeTime = 6000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT7SEC)) dwFadeTime = 7000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT8SEC)) dwFadeTime = 8000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT9SEC)) dwFadeTime = 9000;
		else if(m_menu->IsItemChecked(ID_FADEOUTNEXT10SEC)) dwFadeTime = 10000;
		else dwFadeTime = 3000;
		if(dwInterval >= dwFadeTime) PlayNext(FALSE, TRUE);
		else {
			double dVolume = pow(((double)dwFadeTime - (double)dwInterval)
								/ (double)dwFadeTime, 2.0);
			m_sound->ChannelSetAttribute(BASS_ATTRIB_VOL, (float)dVolume);
		}
		break;
	}
	case IDT_METRONOME:
	{
		DWORD dwTime = timeGetTime();
		if(dwTime >= dwLastTime + m_nInterval || dwTime < dwLastTime) {
			dwLastTime = dwTime;
			PlaySound(lpSound, NULL, SND_ASYNC | SND_MEMORY);
		}
		break;
	}
	case IDT_INCFREQ:
		if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			UpFreq(nIncFreq);
		}
		break;
	case IDT_INCSPEED:
		if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			UpSpeed(nIncSpeed);
		}
		break;
	case IDT_DECFREQ:
		if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			DownFreq(nDecFreq);
		}
		break;
	case IDT_DECSPEED:
		if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			DownSpeed(nDecSpeed);
		}
		break;
	case IDT_TIME:
		if(m_bFinish) {
			m_bFinish = FALSE;
			KillTimer(IDT_TIME);
			if(dwFadeoutStartTime == 0 && m_menu->IsItemChecked(ID_CONTINUE))
				PlayNext(TRUE, TRUE);
			else PlayNext(FALSE, TRUE);
		}
		else if(m_menu->IsItemChecked(ID_PLAYRANGE)) {
			if(m_sound->ChannelGetSecondsPosition() >= m_dEndSeconds) {
				KillTimer(IDT_TIME);
				if(dwFadeoutStartTime == 0 && m_menu->IsItemChecked(ID_CONTINUE))
					PlayNext(FALSE, FALSE);
				else PlayNext(FALSE, FALSE);
			}
		}
		CSnapWnd::OnTimer(id);
		break;
	case IDT_REWIND:
		if(GetTickCount() - m_toolBar->GetRewindClickTime() > 250) Rewind();
		break;
	case IDT_FORWARD:
		if(GetTickCount() - m_toolBar->GetRewindClickTime() > 250) Forward();
		break;
	case IDT_RECORD:
		if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			double freq_org = (double)(m_freqSlider->GetThumbPos()
				/ pow(10.0, m_freqSlider->GetDecimalDigit()));
					// 現在の周波数

			// 加速度の設定
			// 周波数が98以上の場合 : -0.1
			// 　　　　98未満の場合 : +0.1
			nFreqAccel = freq_org >= 98 ? -0.1 : 0.1;

			// 周波数の差分に加速度を加える
			nFreqVelo += nFreqAccel;

			// 周波数に差分を加える
			if(nFreqVelo != 0.0) {
				double freq = freq_org + nFreqVelo;

				// 90 ～ 100 の間で動くようにする
				if(freq <= 90.0) freq = 90.0;
				if(freq >= 100.0) freq = 100.0;

				m_freqLabel->SetFreq(freq);
				m_freqSlider->SetThumbPos((LONG)(freq
					* pow(10.0, m_freqSlider->GetDecimalDigit())), TRUE);
				SetFreq(freq);
			}
		}
		break;
	case IDT_LOWBATTERY:
		if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			double freq_org = (double)(m_freqSlider->GetThumbPos()
				/ pow(10.0, m_freqSlider->GetDecimalDigit()));
					// 現在の周波数

			// 加速度の設定
			// 周波数が68以上の場合 : -0.02
			// 　　　　68未満の場合 : +0.01
			nFreqAccel = freq_org >= 68 ? -0.02 : 0.01;

			// 周波数の差分に加速度を加える
			nFreqVelo += nFreqAccel;

			// 周波数に差分を加える
			if(nFreqVelo != 0.0) {
				double freq = freq_org + nFreqVelo;

				// 65 ～ 70 の間で動くようにする
				if(freq <= 65.0) freq = 65.0;
				if(freq >= 70.0) freq = 70.0;

				m_freqLabel->SetFreq(freq);
				m_freqSlider->SetThumbPos((LONG)(freq
					* pow(10.0, m_freqSlider->GetDecimalDigit())), TRUE);
				SetFreq(freq);
			}
		}
		break;
	case IDT_NOSENSE:
		if(m_sound->ChannelGetSecondsPosition() <= 10.0) {
			m_pitchLabel->SetPitch(0.0);
			m_pitchSlider->SetThumbPos(0, TRUE);
			SetPitch(0.0);
			double dCalc = pow(10.0, m_speedSlider->GetDecimalDigit());
			m_speedLabel->SetSpeed(100.0);
			m_speedSlider->SetThumbPos((int)(100 * dCalc), TRUE);
			SetSpeed(100.0);
		}
		else if(!m_sound->ChannelIsStopped() && !m_sound->ChannelIsPausing()) {
			double pitch_org = (double)(m_pitchSlider->GetThumbPos()
				/ pow(10.0, m_pitchSlider->GetDecimalDigit()));
					// 現在の音程

			if(m_sound->ChannelGetSecondsPosition() > 30.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 1000.0;
			else if(m_sound->ChannelGetSecondsPosition() > 20.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 2000.0;
			else nFreqVelo = CUtils::GetRandom(-100, 100) / 5000.0;
			if(pitch_org <= -2.0 && nFreqVelo < 0.0) nFreqVelo *= -1.0;
			if(pitch_org >= 2.0 && nFreqVelo > 0.0) nFreqVelo *= -1.0;

			// 音程に差分を加える
			if(nFreqVelo != 0.0) {
				double pitch = pitch_org + nFreqVelo;

				// ♭2 ～ ♯2 の間で動くようにする
				// if(pitch < -2.0) pitch = -2.0;
				// if(pitch > 2.0) pitch = 2.0;

				m_pitchLabel->SetPitch(pitch);
				m_pitchSlider->SetThumbPos((LONG)(pitch
					* pow(10.0, m_pitchSlider->GetDecimalDigit())), TRUE);
				SetPitch(pitch);
			}

			double speed_org = (double)(m_speedSlider->GetThumbPos()
				/ pow(10.0, m_speedSlider->GetDecimalDigit()));
					// 現在の速度

			if(m_sound->ChannelGetSecondsPosition() > 30.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 1000.0;
			else if(m_sound->ChannelGetSecondsPosition() > 20.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 2000.0;
			else nFreqVelo = CUtils::GetRandom(-100, 100) / 5000.0;
			if(speed_org <= -90.0 && nFreqVelo < 0.0) nFreqVelo *= -1.0;
			if(speed_org >= 110.0 && nFreqVelo > 0.0) nFreqVelo *= -1.0;

			// 速度に差分を加える
			if(nFreqVelo != 0.0) {
				double speed = speed_org + nFreqVelo;

				// -90 ～ ♯2 の間で動くようにする
				// if(speed < -90.0) speed = -90.0;
				// if(speed > 110.0) speed = 110.0;

				m_speedLabel->SetSpeed(speed);
				m_speedSlider->SetThumbPos((LONG)(speed
					* pow(10.0, m_speedSlider->GetDecimalDigit())), TRUE);
				SetSpeed(speed);
			}
		}
		break;
	case IDT_EARTRAINING:
		{
			srand(timeGetTime());
			int nEQ20 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ25 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ31_5 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ40 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ50 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ63 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ80 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ100 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ125 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ160 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ200 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ250 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ315 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ400 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ500 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ630 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ800 = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ1K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ1_25K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ1_6K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ2K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ2_5K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ3_15K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ4K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ5K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ6_3K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ8K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ10K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ12_5K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ16K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nEQ20K = -15 + (int)(rand() * (15 - -15 + 1.0) / (1.0 + RAND_MAX));
			int nPan = -100 + (int)(rand() * (100 - -100 + 1.0) / (1.0 + RAND_MAX));
			SetEQ(nEQ20, nEQ25, nEQ31_5, nEQ40,
				  nEQ50, nEQ63, nEQ80, nEQ100,
				  nEQ125, nEQ160, nEQ200, nEQ250,
				  nEQ315, nEQ400, nEQ500, nEQ630,
				  nEQ800, nEQ1K, nEQ1_25K, nEQ1_6K,
				  nEQ2K, nEQ2_5K, nEQ3_15K, nEQ4K,
				  nEQ5K, nEQ6_3K, nEQ8K, nEQ10K,
				  nEQ12_5K, nEQ16K, nEQ20K);
			m_panLabel->SetPan(nPan);
			m_panSlider->SetThumbPos(nPan);
			SetPan(nPan);
		}
		break;
	case IDT_TIMERPLAY:
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			if(bTimerPlayNextDay) { // 翌日になったかどうかの判定
				if(st.wHour < nTimerPlayHour || st.wHour == nTimerPlayHour
					&& st.wMinute <= nTimerPlayMinute)
					bTimerPlayNextDay = FALSE;
			}

			if(!bTimerPlayNextDay) {
				if(st.wHour > nTimerPlayHour || (st.wHour == nTimerPlayHour
					&& st.wMinute >= nTimerPlayMinute)) {
					if(m_sound->ChannelIsStopped()
						|| m_sound->ChannelIsPausing())
						Play();
					SetTimerPlay(FALSE);
				}
			}
		}
		break;
	case IDT_TIMERSTOP:
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			if(bTimerStopNextDay) { // 翌日になったかどうかの判定
				if(st.wHour < nTimerStopHour || st.wHour == nTimerStopHour
					&& st.wMinute <= nTimerStopMinute)
					bTimerStopNextDay = FALSE;
			}

			if(!bTimerStopNextDay) {
				if(st.wHour > nTimerStopHour || (st.wHour == nTimerStopHour
					&& st.wMinute >= nTimerStopMinute)) {
					if(m_sound->ChannelIsActive()) Pause();
					SetTimerStop(FALSE);
				}
			}
		}
		break;
	}
}
//----------------------------------------------------------------------------
// ショートカットキー文字列のエスケープ（iniファイル書き出し用）
//----------------------------------------------------------------------------
#define ESC_LEFTBRACKET _T("U005B")
#define ESC_SEMICOLON   _T("U003B")
const TCHAR* CMainWnd::EscapeKeystr(const TCHAR* src)
{
	if (!_tcscmp(src, _T("["))) return ESC_LEFTBRACKET;
	if (!_tcscmp(src, _T(";"))) return ESC_SEMICOLON;

	return src;
}
//----------------------------------------------------------------------------
// ショートカットキー文字列のアンエスケープ（iniファイル読み込み用）
//----------------------------------------------------------------------------
const tstring CMainWnd::UnEscapeKeystr(const tstring src)
{
	if (src == ESC_LEFTBRACKET) return tstring(_T("["));
	if (src == ESC_SEMICOLON) return tstring(_T(";"));
	return src;
}
//----------------------------------------------------------------------------
LRESULT CMainWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_COPYDATA:
		// 多重起動をしようとした時に元のウィンドウに送られるコマンドライン引数
		COPYDATASTRUCT * cd = (COPYDATASTRUCT *)lParam;

		TCHAR ** pStr = (TCHAR **)&cd->lpData;

		*pStr += lstrlen(*pStr) + 1;

		// アイコンにドロップされたファイルを読み込む
		m_arrayList[nCurPlayTab]->DeleteAllItems();
		for(int i = 1; i < (int)cd->dwData; i++) {
			m_arrayList[nCurPlayTab]->AddFile(*pStr);
			*pStr += lstrlen(*pStr) + 1;
		}

		if(m_arrayList[nCurPlayTab]->GetItemCount() <= 0) {
			m_sound->StreamFree();
			Stop();
		}
		else {
			m_sound->SetCurFileNum(0);
			PlayNext(TRUE, TRUE);
			StartUpdateInfo();
		}
		SetPreviousNextMenuState();
		break;
	}
	return CSnapWnd::WindowProc(uMsg, wParam, lParam);
}
//----------------------------------------------------------------------------
// 情報の更新用スレッド
//----------------------------------------------------------------------------
void CMainWnd::UpdateThreadProc(void * pParam)
{
	CMainWnd* pMainWnd = (CMainWnd *)pParam;
	for(int i = 0; i < (int)pMainWnd->GetArrayList().size(); i++) {
		for(int j = 0; j < pMainWnd->GetPlayList(i).GetItemCount(); j++) {
			if(pMainWnd->IsRetryUpdate()) i = 0, j = 0;
			pMainWnd->GetPlayList(i).UpdateItemInfo(j);
		}
	}
	ExitThread(0);
}
//----------------------------------------------------------------------------
// 時間表示の更新用スレッド
//----------------------------------------------------------------------------
void CMainWnd::UpdateTimeThreadProc(void * pParam)
{
	CMainWnd* pMainWnd = (CMainWnd *)pParam;
	while(1) {
		pMainWnd->ShowTime(FALSE);
		Sleep(1000);
	}
}
//----------------------------------------------------------------------------
// 歌詞表示の更新用スレッド
//----------------------------------------------------------------------------
void CMainWnd::UpdateLyricsThreadProc(void * pParam)
{
	CMainWnd* pMainWnd = (CMainWnd *)pParam;
	while(IsWindowVisible(*pMainWnd) && pMainWnd->IsLyricsThreadAlive()
			&& pMainWnd->GetMenu().IsItemChecked(ID_LYRICS)
			&& pMainWnd->GetMenu().IsItemChecked(ID_VIDEOSCREEN)) {
		pMainWnd->GetLyricsManager().Update(
			pMainWnd->GetSound().ChannelGetSecondsPosition()
		);
		Sleep(200);
	}
	pMainWnd->GetLyricsManager().ClearScreen();
	ExitThread(0);
}
//----------------------------------------------------------------------------
// ピッチアナライザの更新用スレッド
//----------------------------------------------------------------------------
void CMainWnd::UpdatePitchAnalyserThreadProc(void * pParam)
{
	CMainWnd* pMainWnd = (CMainWnd *)pParam;
	while(IsWindowVisible(*pMainWnd) && pMainWnd->IsPitchAnalyserThreadAlive()
		&& pMainWnd->GetMenu().IsItemChecked(ID_PITCHANALYSER))
	{
		pMainWnd->GetPitchAnalyser().Update(
			pMainWnd->GetSound().ChannelGetSecondsPosition()
		);
		Sleep(1);
	}
	pMainWnd->GetPitchAnalyser().ClearScreen();
	ExitThread(0);
}
//----------------------------------------------------------------------------
// 選択中のプレイリストビューを取得
//----------------------------------------------------------------------------
CPlayListView_MainWnd & CMainWnd::GetPlayList()
{
	int nSelect = m_tab->GetCurrentFocus();
	return *m_arrayList[nSelect];
}
//----------------------------------------------------------------------------
// 再生時間設定用スライダの高さを取得
//----------------------------------------------------------------------------
int CMainWnd::GetTimeSliderHeight()
{
	return m_menu->IsItemChecked(ID_TIMESLIDER) ? controlOffset * 2
		+ m_timeSlider->GetHeight() : 0;
}
//----------------------------------------------------------------------------
// 再生時間, 再生周波数, 音程設定用コントロールの高さの総和を取得
//----------------------------------------------------------------------------
int CMainWnd::GetControlBarHeight()
{
	if(m_menu->IsItemChecked(ID_SPEED) || m_menu->IsItemChecked(ID_FREQ)
		|| m_menu->IsItemChecked(ID_PITCH)) {
		int nHeight = controlOffset;
		nHeight += m_divider2->GetHeight();
		if(m_menu->IsItemChecked(ID_SPEED)) {
			nHeight += controlOffset;
			nHeight += m_speedLabel->GetHeight() > m_speedSlider->GetHeight() ?
						 m_speedLabel->GetHeight() : m_speedSlider->GetHeight();
		}
		if(m_menu->IsItemChecked(ID_FREQ)) {
			nHeight += controlOffset;
			nHeight += m_freqLabel->GetHeight() >
						 m_freqSlider->GetHeight() ?
						 m_freqLabel->GetHeight() :
						 m_freqSlider->GetHeight();
		}
		if(m_menu->IsItemChecked(ID_PITCH)) {
			nHeight += controlOffset;
			nHeight += m_pitchLabel->GetHeight() > m_pitchSlider->GetHeight() ?
						 m_pitchLabel->GetHeight() : m_pitchSlider->GetHeight();
		}
		return nHeight;
	}
	else return 0;
}
//----------------------------------------------------------------------------
// 音量, パン設定用コントロールの高さの総和を取得
//----------------------------------------------------------------------------
int CMainWnd::GetControlBar2Height()
{
	if(m_menu->IsItemChecked(ID_VOLUME) || m_menu->IsItemChecked(ID_PAN)) {
		int nHeight = controlOffset;
		nHeight += m_divider3->GetHeight();
		if(m_menu->IsItemChecked(ID_VOLUME)) {
			nHeight += controlOffset;
			nHeight += m_volumeLabel->GetHeight() > m_volumeSlider->GetHeight() ?
						 m_volumeLabel->GetHeight() : m_volumeSlider->GetHeight();
		}
		if(m_menu->IsItemChecked(ID_PAN)) {
		nHeight += controlOffset;
			nHeight += m_panLabel->GetHeight() > m_panSlider->GetHeight() ?
						 m_panLabel->GetHeight() : m_panSlider->GetHeight();
		}
		return nHeight;
	}
	else return 0;
}
//----------------------------------------------------------------------------
// イコライザ設定用コントロールの高さの総和を取得
//----------------------------------------------------------------------------
int CMainWnd::GetEQHeight()
{
	if(m_menu->IsItemChecked(ID_EQ)) {
		int nHeight = controlOffset;
		nHeight += m_divider4->GetHeight();
		nHeight += controlOffset * 2;
		if(m_menu->IsItemChecked(ID_EQ20))
			nHeight += m_eq20Label->GetHeight() > m_eq20Slider->GetHeight() ?
						 m_eq20Label->GetHeight() : m_eq20Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ25))
			nHeight += m_eq25Label->GetHeight() > m_eq25Slider->GetHeight() ?
						 m_eq25Label->GetHeight() : m_eq25Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ31_5))
			nHeight += m_eq31_5Label->GetHeight() > m_eq31_5Slider->GetHeight() ?
						 m_eq31_5Label->GetHeight() : m_eq31_5Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ40))
			nHeight += m_eq40Label->GetHeight() > m_eq40Slider->GetHeight() ?
						 m_eq40Label->GetHeight() : m_eq40Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ50))
			nHeight += m_eq50Label->GetHeight() > m_eq50Slider->GetHeight() ?
						 m_eq50Label->GetHeight() : m_eq50Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ63))
			nHeight += m_eq63Label->GetHeight() > m_eq63Slider->GetHeight() ?
						 m_eq63Label->GetHeight() : m_eq63Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ80))
			nHeight += m_eq80Label->GetHeight() > m_eq80Slider->GetHeight() ?
						 m_eq80Label->GetHeight() : m_eq80Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ100))
			nHeight += m_eq100Label->GetHeight() > m_eq100Slider->GetHeight() ?
						 m_eq100Label->GetHeight() : m_eq100Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ125))
			nHeight += m_eq125Label->GetHeight() > m_eq125Slider->GetHeight() ?
						 m_eq125Label->GetHeight() : m_eq125Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ160))
			nHeight += m_eq160Label->GetHeight() > m_eq160Slider->GetHeight() ?
						 m_eq160Label->GetHeight() : m_eq160Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ200))
			nHeight += m_eq200Label->GetHeight() > m_eq200Slider->GetHeight() ?
						 m_eq200Label->GetHeight() : m_eq200Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ250))
			nHeight += m_eq250Label->GetHeight() > m_eq250Slider->GetHeight() ?
						 m_eq250Label->GetHeight() : m_eq250Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ315))
			nHeight += m_eq315Label->GetHeight() > m_eq315Slider->GetHeight() ?
						 m_eq315Label->GetHeight() : m_eq315Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ400))
			nHeight += m_eq400Label->GetHeight() > m_eq400Slider->GetHeight() ?
						 m_eq400Label->GetHeight() : m_eq400Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ500))
			nHeight += m_eq500Label->GetHeight() > m_eq500Slider->GetHeight() ?
						 m_eq500Label->GetHeight() : m_eq500Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ630))
			nHeight += m_eq630Label->GetHeight() > m_eq630Slider->GetHeight() ?
						 m_eq630Label->GetHeight() : m_eq630Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ800))
			nHeight += m_eq800Label->GetHeight() > m_eq800Slider->GetHeight() ?
						 m_eq800Label->GetHeight() : m_eq800Slider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ1K))
			nHeight += m_eq1kLabel->GetHeight() > m_eq1kSlider->GetHeight() ?
						 m_eq1kLabel->GetHeight() : m_eq1kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ1_25K))
			nHeight += m_eq1_25kLabel->GetHeight() > m_eq1_25kSlider->GetHeight() ?
						 m_eq1_25kLabel->GetHeight() : m_eq1_25kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ1_6K))
			nHeight += m_eq1_6kLabel->GetHeight() > m_eq1_6kSlider->GetHeight() ?
						 m_eq1_6kLabel->GetHeight() : m_eq1_6kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ2K))
			nHeight += m_eq2kLabel->GetHeight() > m_eq2kSlider->GetHeight() ?
						 m_eq2kLabel->GetHeight() : m_eq2kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ2_5K))
			nHeight += m_eq2_5kLabel->GetHeight() > m_eq2_5kSlider->GetHeight() ?
						 m_eq2_5kLabel->GetHeight() : m_eq2_5kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ3_15K))
			nHeight += m_eq3_15kLabel->GetHeight() > m_eq3_15kSlider->GetHeight() ?
						 m_eq3_15kLabel->GetHeight() : m_eq3_15kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ4K))
			nHeight += m_eq4kLabel->GetHeight() > m_eq4kSlider->GetHeight() ?
						 m_eq4kLabel->GetHeight() : m_eq4kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ5K))
			nHeight += m_eq5kLabel->GetHeight() > m_eq5kSlider->GetHeight() ?
						 m_eq5kLabel->GetHeight() : m_eq5kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ6_3K))
			nHeight += m_eq6_3kLabel->GetHeight() > m_eq6_3kSlider->GetHeight() ?
						 m_eq6_3kLabel->GetHeight() : m_eq6_3kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ8K))
			nHeight += m_eq8kLabel->GetHeight() > m_eq8kSlider->GetHeight() ?
						 m_eq8kLabel->GetHeight() : m_eq8kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ10K))
			nHeight += m_eq10kLabel->GetHeight() > m_eq10kSlider->GetHeight() ?
						 m_eq10kLabel->GetHeight() : m_eq10kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ12_5K))
			nHeight += m_eq12_5kLabel->GetHeight() > m_eq12_5kSlider->GetHeight() ?
						 m_eq12_5kLabel->GetHeight() : m_eq12_5kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ16K))
			nHeight += m_eq16kLabel->GetHeight() > m_eq16kSlider->GetHeight() ?
						 m_eq16kLabel->GetHeight() : m_eq16kSlider->GetHeight();
		if(m_menu->IsItemChecked(ID_EQ20K))
			nHeight += m_eq20kLabel->GetHeight() > m_eq20kSlider->GetHeight() ?
						 m_eq20kLabel->GetHeight() : m_eq20kSlider->GetHeight();
		return nHeight;
	}
	else return 0;
}
//----------------------------------------------------------------------------
