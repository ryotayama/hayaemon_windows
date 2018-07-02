//----------------------------------------------------------------------------
// Menu_MainWnd.cpp : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <WinInet.h>
#include "../Common/CommandList.h"
#include "../Common/Utils.h"
#include "../App.h"
#include "FreqLabel_MainWnd.h"
#include "FreqSlider_MainWnd.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "PanLabel_MainWnd.h"
#include "PanSlider_MainWnd.h"
#include "PitchLabel_MainWnd.h"
#include "PitchSlider_MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "Sound.h"
#include "SpeedLabel_MainWnd.h"
#include "SpeedSlider_MainWnd.h"
#include "VolumeLabel_MainWnd.h"
#include "VolumeSlider_MainWnd.h"
#include "ToolBar_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CMenu_MainWnd::Create()
{
	CMenu::Create();
#if JP
	// ファイルメニュー
	m_fileMenu.CreatePopup();
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFILE, _T("開く(&O)...\tCtrl+O"));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFILE, _T("追加(&P)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFOLDER, _T("フォルダを開く(&F)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFOLDER, _T("フォルダを追加(&G)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENURL, _T("URLを開く(&O)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDURL, _T("URLを追加(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEFILE, _T("保存(&S)...\tCtrl+E"));
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEALLFILE, _T("一括変換(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_LAMECOMMANDLINE,
		_T("LAMEコマンドラインオプション(&L)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_EXIT, _T("終了(&X)\tAlt+F4"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_fileMenu, _T("ファイル(&F)"));

	// 編集メニュー
	m_editMenu.CreatePopup();
	m_editMenu.Append(MFS_ENABLED, ID_DELETE, _T("削除(&D)"));
	m_editMenu.Append(MFS_ENABLED, ID_SELECTALL, _T("すべて選択(&A)\tCtrl+A"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_editMenu, _T("編集(&E)"));

	// 表示メニュー
	m_viewMenu.CreatePopup();
	m_videoScreenMenu.CreatePopup();
	m_videoScreenMenu.Append(MFS_ENABLED, ID_VIDEOSCREEN, _T("表示(&V)"));
	m_videoScreenMenu.AppendSeparator();
	m_videoScreenMenu.Append(MFS_CHECKED, ID_LYRICS, _T("歌詞(&L)"));
	m_videoScreenMenu.Append(MFS_ENABLED, ID_PITCHANALYSER,
		_T("ピッチアナライザ(&P)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_videoScreenMenu,
		_T("ビデオ画面(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_TIMESLIDER, _T("再生位置スライダ(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_EXPLORER, _T("エクスプローラ(&E)"));
	m_viewMenu.Append(MFS_ENABLED, ID_SPEED, _T("再生速度(&S)"));
	m_viewMenu.Append(MFS_ENABLED, ID_FREQ, _T("再生周波数(&F)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PITCH, _T("音程(&P)"));
	m_viewMenu.Append(MFS_ENABLED, ID_VOLUME, _T("音量(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PAN, _T("パン(&P)"));
	m_eqMenu.CreatePopup();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ, _T("表示(&V)"));
	m_eqMenu.AppendSeparator();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20, _T("20 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ25, _T("25 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ31_5, _T("31.5 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ40, _T("40 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ50, _T("50 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ63, _T("63 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ80, _T("80 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ100, _T("100 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ125, _T("125 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ160, _T("160 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ200, _T("200 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ250, _T("250 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ315, _T("315 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ400, _T("400 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ500, _T("500 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ630, _T("630 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ800, _T("800 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1K, _T("1 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_25K, _T("1.25 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_6K, _T("1.6 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2K, _T("2 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2_5K, _T("2.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ3_15K, _T("3.15 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ4K, _T("4 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ5K, _T("5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ6_3K, _T("6.3 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ8K, _T("8 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ10K, _T("10 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ12_5K, _T("12.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ16K, _T("16 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20K, _T("20 KHz"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqMenu,
		_T("グラフィックイコライザ(&G)"));
	m_viewMenu.Append(MFS_CHECKED, ID_TAB, _T("タブ(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PLAYLIST, _T("再生リスト(&P)"));
	m_viewMenu.AppendSeparator();
	m_viewMenu.Append(MFS_ENABLED, ID_CLOSEALL, _T("全てのコントロールを閉じる(&C)"));
	m_viewMenu.AppendSeparator();
	m_toolbarMenu.CreatePopup();
	m_toolbarMenu.Append(MFS_CHECKED, ID_TOOLBAR_SIZES, _T("サイズ（小）(&S)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEM, _T("サイズ（中）(&M)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEL, _T("サイズ（大）(&L)"));
	m_toolbarMenu.AppendSeparator();
	m_toolbarMenu.Append(MFS_ENABLED, ID_CUSTOMIZETOOLBAR,
		_T("カスタマイズ(&T)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_toolbarMenu, _T("ツールバー"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_viewMenu, _T("表示(&V)"));

	// 再生メニュー
	m_playMenu.CreatePopup();
	m_playMenu.Append(MFS_ENABLED, ID_PAUSE, _T("再生/一時停止(&P)\tCtrl+P"));
	m_playMenu.Append(MFS_ENABLED, ID_STOP, _T("停止(&S)\tCtrl+S"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_HEAD, _T("頭出し(&T)\tCtrl+0"));
	m_playMenu.Append(MFS_ENABLED, ID_PREV, _T("前へ(&V)\tCtrl+B"));
	m_playMenu.Append(MFS_ENABLED, ID_NEXT, _T("次へ(&N)\tCtrl+F"));
	m_playMenu.Append(MFS_ENABLED, ID_REWIND, _T("巻き戻し(&R)\tCtrl+Shift+B"));
	m_playMenu.Append(MFS_ENABLED, ID_FORWARD, _T("早送り(&A)\tCtrl+Shift+F"));
	m_playMenu.AppendSeparator();
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN1SEC, _T("1秒戻る(&1)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN2SEC, _T("2秒戻る(&2)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN3SEC, _T("3秒戻る(&3)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN5SEC, _T("5秒戻る(&5)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN10SEC, _T("10秒戻る(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, _T("戻る(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD1SEC, _T("1秒進む(&1)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD2SEC, _T("2秒進む(&2)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD3SEC, _T("3秒進む(&3)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD5SEC, _T("5秒進む(&5)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD10SEC, _T("10秒進む(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, _T("進む(&F)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_SLOOP, _T("１曲ループ(&1)\tCtrl+1"));
	m_playMenu.Append(MF_ENABLED, ID_ALOOP, _T("全曲ループ(&T)\tCtrl+T"));
	m_playMenu.Append(MFS_ENABLED, ID_RANDOM, _T("ランダム再生(&H)\tCtrl+H"));
	m_playMenu.Append(MFS_ENABLED, ID_CONTINUE, _T("連続再生(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_SAMEARTIST, _T("同じアーティストの曲を再生(&S)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_A,
		_T("現在位置をABループ(A)に設定(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_B,
		_T("現在位置をABループ(B)に設定(&B)"));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_A_SETTING,
		_T("ABループ(A)の位置設定(&C)..."));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_B_SETTING,
		_T("ABループ(B)の位置設定(&D)..."));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_MARKERPLAY, _T("マーカー再生(&M)"));
	m_playMenu.Append(MFS_ENABLED, ID_ADDMARKER, _T("マーカー追加(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_DELETEMARKER, _T("マーカー削除(&D)"));
	m_playMenu.Append(MFS_DISABLED, ID_COUNTLOOP, _T("回数ループ(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_INSTANTLOOP, _T("マーカー追加時にループ(&I)"));
	m_playMenu.Append(MFS_ENABLED, ID_SETPOSITIONAUTO,
		_T("マーカー調整時の再生位置連動(&S)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_playMenu, _T("再生(&P)"));

	// エフェクトメニュー
	m_effectMenu.CreatePopup();
	m_presetMenu.CreatePopup();
	m_presetMenu.Append(MFS_ENABLED, ID_ADDPRESET, _T("現在の設定を追加(&A)"));
	m_presetMenu.Append(MFS_DISABLED, ID_DELETEPRESET, _T("選択中のプリセットを削除(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_presetMenu,
		_T("プリセット(&P)"));
	m_effectMenu.AppendSeparator();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(MFS_ENABLED, ID_RESETSPEED, _T("デフォルトに戻す(&R)"));
	m_speedMenu.AppendSeparator();
	m_setSpeedMenu.CreatePopup();
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_50, _T("50%(&A)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_60, _T("60%(&B)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_70, _T("70%(&C)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_80, _T("80%(&D)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_90, _T("90%(&E)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_100, _T("100%(&F)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_110, _T("110%(&G)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_120, _T("120%(&H)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_130, _T("130%(&I)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_140, _T("140%(&J)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_150, _T("150%(&K)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_160, _T("160%(&L)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_170, _T("170%(&M)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_180, _T("180%(&N)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_190, _T("190%(&O)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_200, _T("200%(&P)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_250, _T("250%(&Q)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_300, _T("300%(&R)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_350, _T("350%(&S)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_400, _T("400%(&T)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setSpeedMenu,
		_T("速度指定(&S)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN0_1SPEED, _T("0.1%下げる(&0)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN1SPEED, _T("1%下げる(&1)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN2SPEED, _T("2%下げる(&2)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN3SPEED, _T("3%下げる(&3)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN5SPEED, _T("5%下げる(&5)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN10SPEED, _T("10%下げる(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_UP0_1SPEED, _T("0.1%上げる(&Z)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP1SPEED, _T("1%上げる(&A)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP2SPEED, _T("2%上げる(&B)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP3SPEED, _T("3%上げる(&C)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP5SPEED, _T("5%上げる(&D)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP10SPEED, _T("10%上げる(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MF_ENABLED, ID_DECSPEED, _T("だんだん遅くする(&D)..."));
	m_speedMenu.Append(MF_ENABLED, ID_INCSPEED, _T("だんだん速くする(&D)..."));
	m_speedMenu.AppendSeparator();
	m_speedDecimalMenu.CreatePopup();
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_0, _T("0桁(&0)"));
	m_speedDecimalMenu.Append(MFS_CHECKED, ID_SPEEDDEC_1, _T("1桁(&1)"));
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_2, _T("2桁(&2)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedDecimalMenu, _T("小数点桁数"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu,
		_T("再生速度(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(MFS_ENABLED, ID_RESETFREQ, _T("デフォルトに戻す(&R)"));
	m_freqMenu.AppendSeparator();
	m_setFreqMenu.CreatePopup();
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_50, _T("50%(&A)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_60, _T("60%(&B)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_70, _T("70%(&C)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_80, _T("80%(&D)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_90, _T("90%(&E)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_100, _T("100%(&F)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_110, _T("110%(&G)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_120, _T("120%(&H)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_130, _T("130%(&I)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_140, _T("140%(&J)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_150, _T("150%(&K)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_160, _T("160%(&L)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_170, _T("170%(&M)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_180, _T("180%(&N)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_190, _T("190%(&O)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_200, _T("200%(&P)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_250, _T("250%(&Q)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_300, _T("300%(&R)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_350, _T("350%(&S)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_400, _T("400%(&T)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setFreqMenu,
		_T("周波数指定(&F)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN0_1FREQ, _T("0.1%下げる(&0)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN1FREQ, _T("1%下げる(&1)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN2FREQ, _T("2%下げる(&2)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN3FREQ, _T("3%下げる(&3)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN5FREQ, _T("5%下げる(&5)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN10FREQ, _T("10%下げる(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_UP0_1FREQ, _T("0.1%上げる(&Z)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP1FREQ, _T("1%上げる(&A)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP2FREQ, _T("2%上げる(&B)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP3FREQ, _T("3%上げる(&C)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP5FREQ, _T("5%上げる(&D)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP10FREQ, _T("10%上げる(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MF_ENABLED, ID_DECFREQ,
		_T("だんだん遅くする(&F)..."));
	m_freqMenu.Append(MF_ENABLED, ID_INCFREQ,
		_T("だんだん速くする(&F)..."));
	m_freqMenu.AppendSeparator();
	m_freqDecimalMenu.CreatePopup();
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_0, _T("0桁(&0)"));
	m_freqDecimalMenu.Append(MFS_CHECKED, ID_FREQDEC_1, _T("1桁(&1)"));
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_2, _T("2桁(&2)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqDecimalMenu, _T("小数点桁数"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu,
		_T("再生周波数(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(MFS_ENABLED, ID_RESETPITCH, _T("デフォルトに戻す(&R)"));
	m_pitchMenu.AppendSeparator();
	m_setPitchMenu.CreatePopup();
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F12, _T("♭12(&A)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F11, _T("♭11(&B)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F10, _T("♭10(&C)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F9, _T("♭9(&D)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F8, _T("♭8(&E)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F7, _T("♭7(&F)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F6, _T("♭6(&G)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F5, _T("♭5(&H)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F4, _T("♭4(&I)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F3, _T("♭3(&J)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F2, _T("♭2(&K)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F1, _T("♭1(&L)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_0, _T("0(&M)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S1, _T("♯1(&N)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S2, _T("♯2(&O)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S3, _T("♯3(&P)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S4, _T("♯4(&Q)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S5, _T("♯5(&R)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S6, _T("♯6(&S)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S7, _T("♯7(&T)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S8, _T("♯8(&U)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S9, _T("♯9(&V)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S10, _T("♯10(&W)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S11, _T("♯11(&X)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S12, _T("♯12(&Y)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setPitchMenu,
		_T("音程指定(&F)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1PITCH, _T("半音下げる(&1)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN2PITCH, _T("全音下げる(&2)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1OCTPITCH, _T("１オクターブ下げる(&3)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1PITCH, _T("半音上げる(&A)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP2PITCH, _T("全音上げる(&B)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1OCTPITCH, _T("１オクターブ上げる(&C)"));
	m_pitchMenu.AppendSeparator();
	m_pitchDecimalMenu.CreatePopup();
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_0, _T("0桁(&0)"));
	m_pitchDecimalMenu.Append(MFS_CHECKED, ID_PITCHDEC_1, _T("1桁(&1)"));
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_2, _T("2桁(&2)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchDecimalMenu, _T("小数点桁数"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu, _T("音程(&P)"));
	m_volumeMenu.CreatePopup();
	m_volumeMenu.Append(MFS_ENABLED, ID_RESETVOLUME, _T("デフォルトに戻す(&R)"));
	m_volumeMenu.AppendSeparator();
	m_setVolumeMenu.CreatePopup();
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_0, _T("0%(&A)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_10, _T("10%(&B)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_20, _T("20%(&C)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_30, _T("30%(&D)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_40, _T("40%(&E)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_50, _T("50%(&F)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_60, _T("60%(&G)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_70, _T("70%(&H)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_80, _T("80%(&I)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_90, _T("90%(&J)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_100, _T("100%(&K)"));
	m_volumeMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setVolumeMenu,
		_T("音量指定(&V)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_volumeMenu, _T("音量(&V)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWSUPER,
		_T("低音強調（超最強）(&A)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGHEST,
		_T("低音強調（最強）(&B)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGH,
		_T("低音強調（強）(&C)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWMIDDLE,
		_T("低音強調（中）(&D)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOW, _T("低音強調（弱）(&E)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOWEST,
		_T("低音強調（最弱）(&G)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLESUPER,
		_T("中音強調（超最強）(&H)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGHEST,
		_T("中音強調（最強）(&I)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGH, 
		_T("中音強調（強）(&J)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEMIDDLE, 
		_T("中音強調（中）(&K)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOW, 
		_T("中音強調（弱）(&L)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOWEST, 
		_T("中音強調（最弱）(&M)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHSUPER, 
		_T("高音強調（超最強）(&N)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGHEST, 
		_T("高音強調（最強）(&O)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGH, 
		_T("高音強調（強）(&P)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHMIDDLE, 
		_T("高音強調（中）(&Q)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOW, 
		_T("高音強調（弱）(&R)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOWEST, 
		_T("高音強調（最弱）(&S)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTSUPER,
		_T("低音カット（超最強）(&T)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGHEST,
		_T("低音カット（最強）(&U)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGH,
		_T("低音カット（強）(&V)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTMIDDLE,
		_T("低音カット（中）(&W)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOW,
		_T("低音カット（弱）(&X)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOWEST,
		_T("低音カット（最弱）(&Y)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTSUPER,
		_T("中音カット（超最強）(&Z)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGHEST,
		_T("中音カット（最強）(&0)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGH, 
		_T("中音カット（強）(&1)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTMIDDLE, 
		_T("中音カット（中）(&2)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOW, 
		_T("中音カット（弱）(&3)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOWEST, 
		_T("中音カット（最弱）(&4)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTSUPER, 
		_T("高音カット（超最強）(&5)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGHEST, 
		_T("高音カット（最強）(&6)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGH, 
		_T("高音カット（強）(&7)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTMIDDLE, 
		_T("高音カット（中）(&8)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOW, 
		_T("高音カット（弱）(&9)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOWEST, 
		_T("高音カット（最弱）(&0)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu, 
		_T("EQプリセット(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_DEFAULT, 
		_T("デフォルト(&D)"));
	m_reverbMenu.AppendSeparator();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_CUSTOMIZE, 
		_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu, 
		_T("リバーブ(&R)"));
	m_3dreverbMenu.CreatePopup();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_DEFAULT, 
		_T("デフォルト(&D)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PADDEDCELL, 
		_T("クッション張りの安全室(&P)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ROOM, _T("部屋(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_BATHROOM, _T("浴室(&B)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LIVINGROOM, _T("リビング(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONEROOM, _T("石室(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_AUDITORIUM, _T("講堂(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CONCERTHALL, 
		_T("コンサートホール(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CAVE, _T("洞窟(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ARENA, _T("アリーナ(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HANGAR, _T("納屋(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CARPETEDHALLWAY, 
		_T("カーペットを敷いた廊下(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HALLWAY, _T("廊下(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONECORRIDOR, 
		_T("石の廊下(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ALLEY, _T("裏通り(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_FOREST, _T("森林(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CITY, _T("都市(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MOUNTAINS, _T("山(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_QUARRY, _T("採石場(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLAIN, _T("平野(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PARKINGLOT, _T("駐車場(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SEWERPIPE, _T("下水管(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_UNDERWATER, _T("水中(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SMALLROOM, _T("小部屋(&S)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMROOM, _T("中部屋(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEROOM, _T("大部屋(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMHALL, _T("中ホール(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEHALL, _T("大ホール(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLATE, _T("プレート(&P)"));
	m_3dreverbMenu.AppendSeparator();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CUSTOMIZE, 
		_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_3dreverbMenu, 
		_T("３Ｄリバーブ(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DEFAULT, _T("デフォルト(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_SHORT, _T("短いエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MEDIUM, 
		_T("中ぐらいのエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_LONG, _T("長いエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOSHORT,
					   _T("ステレオの短いエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOMEDIUM,
					   _T("ステレオの中ぐらいのエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOLONG,
					   _T("ステレオの長いエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MOUNTAIN, _T("山びこ(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_BIG, _T("大きいエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOBIG,
					   _T("ステレオの大きいエコー(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLING, _T("ダブリング(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLEKICK, 
		_T("ダブルキック(&D)"));
	m_delayMenu.AppendSeparator();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_CUSTOMIZE, 
		_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu, 
		_T("ディレイ(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_DEFAULT, _T("デフォルト(&D)"));
	m_chorusMenu.AppendSeparator();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_CUSTOMIZE,
		_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("コーラス(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_DEFAULT,
							_T("デフォルト(&D)"));
	m_compressorMenu.AppendSeparator();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_CUSTOMIZE,
							_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("コンプレッサー(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_DEFAULT,
							_T("デフォルト(&D)"));
	m_flangerMenu.AppendSeparator();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_CUSTOMIZE,
							_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("フランジャー(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_DEFAULT,
							_T("デフォルト(&D)"));
	m_gargleMenu.AppendSeparator();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_CUSTOMIZE,
							_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("ガーグル(&G)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_DEFAULT, 
		_T("デフォルト(&D)"));
	m_distortionMenu.AppendSeparator();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_CUSTOMIZE, 
		_T("カスタマイズ(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("ディストーション(&D)"));
	m_effectMenu.AppendSeparator();
	m_soundEffectMenu.CreatePopup();
	m_soundEffectMenu.Append(MFS_ENABLED, ID_RECORDNOISE,
		_T("レコードノイズ(&R)"));
	m_soundEffectMenu.Append(MFS_ENABLED, ID_WAVE, _T("波音(&W)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_soundEffectMenu,
		_T("効果音(&S)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_NORMALIZE, _T("ノーマライズ(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_VOCALCANCEL, 
		_T("ボーカルキャンセル(&V)"));
	m_effectMenu.Append(MFS_ENABLED, ID_REVERSE, _T("逆回転再生(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_RECORD, _T("古びたレコード再生(&F)"));
	m_effectMenu.Append(MFS_ENABLED, ID_LOWBATTERY, _T("電池切れ(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_NOSENSE, _T("歌へたモード(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_BASSCOPY, _T("ベースの耳コピ(&B)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CYMBALCOPY,
		_T("ドラム（ハイハット、シンバル）の耳コピ(&D)"));
	m_effectMenu.Append(MFS_ENABLED, ID_EARTRAINING,
		_T("聴覚トレーニング(&E)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_MONORAL, _T("モノラル(&M)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYLEFT, _T("左のみ再生(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYRIGHT, _T("右のみ再生(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CHANGELR, _T("左右入れ替え(&C)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_RESETALL, _T("全てデフォルトに戻す(&D)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_effectMenu, _T("エフェクト(&E)"));

	// システムメニュー
	m_systemMenu.CreatePopup();
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVIDEOSCREENVISIBLE, 
		_T("ビデオ画面(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERTIMESLIDERVISIBLE, 
		_T("再生位置スライダ(&T)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERSPEEDVISIBLE, 
		_T("再生速度(&S)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERFREQVISIBLE, 
		_T("再生周波数(&F)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPITCHVISIBLE, 
		_T("音程(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVOLUMEVISIBLE, 
		_T("音量(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPANVISIBLE, 
		_T("パン(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVEREQVISIBLE, 
		_T("グラフィックイコライザ(&G)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERLISTVISIBLE, 
		_T("再生リスト(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu, 
		_T("表示状態(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSLOOP, 
		_T("１曲ループ(&1)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERALOOP, 
		_T("全曲ループ(&T)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRANDOM, 
		_T("ランダム再生(&H)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERCONTINUE,
		_T("連続再生(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERINSTANTLOOP, 
		_T("マーカー追加時にループ(&I)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSETPOSITIONAUTO, 
		_T("マーカー位置変更時に再生位置変更(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERREVERSE, 
		_T("逆回転再生(&R)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRECORD, 
		_T("古びたレコード再生(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu, 
		_T("再生モード(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWPOS, 
		_T("ウィンドウ位置(&P)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWSIZE, 
		_T("ウィンドウサイズ(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPLAYPOS, _T("再生位置(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERSPEED, _T("再生速度(&S)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERFREQ, 
		_T("再生周波数(&F)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPITCH, _T("音程(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERVOLUME, _T("音量(&V)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPAN, _T("パン(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVEREQ, 
		_T("グラフィックイコライザ(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERLIST, _T("再生リスト(&P)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, 
		_T("復元(&R)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_KEYSETTING, 
		_T("ショートカットキー設定(&K)..."));
	m_systemMenu.Append(MF_ENABLED, ID_OUTKEYSETTING, 
		_T("グローバルホットキー設定(&G)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_LIMIT, 
		_T("最大値／最小値の設定(&L)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TIMERPLAY, _T("タイマー設定(&T)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYRANGE, _T("再生範囲(&R)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYPOSITION, _T("再生位置(&P)..."));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTSTOP,
		_T("再生停止時にフェードアウト(&F)"));
	m_fadeoutMenu.CreatePopup();
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP1SEC, _T("1秒(&1)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP2SEC, _T("2秒(&2)"));
	m_fadeoutMenu.Append(MFS_CHECKED, ID_FADEOUTSTOP3SEC, _T("3秒(&3)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP4SEC, _T("4秒(&4)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP5SEC, _T("5秒(&5)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP6SEC, _T("6秒(&6)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP7SEC, _T("7秒(&7)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP8SEC, _T("8秒(&8)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP9SEC, _T("9秒(&9)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP10SEC, _T("10秒(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutMenu,
		_T("停止時フェードアウト時間(&G)"));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTNEXT, 
		_T("曲の切替時にフェードアウト(&F)"));
	m_fadeoutNextMenu.CreatePopup();
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT1SEC, _T("1秒(&1)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT2SEC, _T("2秒(&2)"));
	m_fadeoutNextMenu.Append(MFS_CHECKED, ID_FADEOUTNEXT3SEC, _T("3秒(&3)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT4SEC, _T("4秒(&4)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT5SEC, _T("5秒(&5)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT6SEC, _T("6秒(&6)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT7SEC, _T("7秒(&7)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT8SEC, _T("8秒(&8)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT9SEC, _T("9秒(&9)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT10SEC, _T("10秒(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutNextMenu,
		_T("切替時フェードアウト時間(&H)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TWEET, 
		_T("Twitterでつぶやく(&T)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_METRONOME, 
		_T("メトロノーム機能(&M)..."));
	m_systemMenu.AppendSeparator();
	m_qualityMenu.CreatePopup();
	m_qualityMenu.Append(MFS_CHECKED, ID_QUALITY_NORMAL, _T("ノーマル(&N)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_ASIO, _T("ASIO(&A)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_WASAPI, _T("WASAPI(&W)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_qualityMenu,
		_T("音質(&Q)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_DOUBLERUN, _T("多重起動(&D)"));
	m_systemMenu.Append(MF_ENABLED, ID_TOPMOST, _T("最前面表示(&S)"));
	m_systemMenu.Append(MF_ENABLED, ID_TASKTRAY, 
		_T("最小化時タスクトレイに格納(&T)"));
	m_systemMenu.Append(MF_ENABLED, ID_COPYTIME, 
		_T("現在の再生位置をクリップボードにコピー(&C)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_systemMenu, _T("システム(&S)"));

	CheckItem(ID_CONTINUE, MF_CHECKED);

	// ヘルプメニュー
	m_helpMenu.CreatePopup();
	m_helpMenu.Append(MFS_ENABLED, ID_MANUAL,
		_T("オンラインマニュアル(&M)..."));
	m_helpMenu.AppendSeparator();
	m_helpMenu.Append(MFS_ENABLED, ID_UPDATECHECK, 
		_T("アップデートの確認(&U)..."));
	m_helpMenu.Append(MFS_ENABLED, ID_VERSIONINFO, 
		_T("バージョン情報(&A)..."));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_helpMenu, _T("ヘルプ(&H)"));
#else // JP
	// ファイルメニュー
	m_fileMenu.CreatePopup();
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFILE, _T("Open(&O)...\tCtrl+O"));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFILE, _T("Add(&P)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFOLDER, _T("Open Directory(&F)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFOLDER, _T("Add Directory(&G)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENURL, _T("Open URL(&O)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDURL, _T("Add URL(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEFILE, _T("Save(&S)...\tCtrl+E"));
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEALLFILE, _T("Save All(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_LAMECOMMANDLINE,
		_T("LAME Command Line Option(&L)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_EXIT, _T("Exit(&X)\tAlt+F4"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_fileMenu, _T("File(&F)"));

	// 編集メニュー
	m_editMenu.CreatePopup();
	m_editMenu.Append(MFS_ENABLED, ID_DELETE, _T("Delete(&D)"));
	m_editMenu.Append(MFS_ENABLED, ID_SELECTALL, _T("Select All(&A)\tCtrl+A"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_editMenu, _T("Edit(&E)"));

	// 表示メニュー
	m_viewMenu.CreatePopup();
	m_videoScreenMenu.CreatePopup();
	m_videoScreenMenu.Append(MFS_ENABLED, ID_VIDEOSCREEN, _T("Visible(&V)"));
	m_videoScreenMenu.AppendSeparator();
	m_videoScreenMenu.Append(MFS_CHECKED, ID_LYRICS, _T("Lyrics(&L)"));
	m_videoScreenMenu.Append(MFS_ENABLED, ID_PITCHANALYSER,
		_T("Pitch Analyser(&P)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_videoScreenMenu,
		_T("Video Screen(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_TIMESLIDER, _T("Position Slider(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_EXPLORER, _T("Explorer(&E)"));
	m_viewMenu.Append(MFS_ENABLED, ID_SPEED, _T("Speed(&S)"));
	m_viewMenu.Append(MFS_ENABLED, ID_FREQ, _T("Frequency(&F)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PITCH, _T("Pitch(&P)"));
	m_viewMenu.Append(MFS_ENABLED, ID_VOLUME, _T("Volume(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PAN, _T("Pan(&P)"));
	m_eqMenu.CreatePopup();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ, _T("Visible(&V)"));
	m_eqMenu.AppendSeparator();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20, _T("20 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ25, _T("25 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ31_5, _T("31.5 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ40, _T("40 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ50, _T("50 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ63, _T("63 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ80, _T("80 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ100, _T("100 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ125, _T("125 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ160, _T("160 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ200, _T("200 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ250, _T("250 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ315, _T("315 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ400, _T("400 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ500, _T("500 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ630, _T("630 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ800, _T("800 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1K, _T("1 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_25K, _T("1.25 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_6K, _T("1.6 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2K, _T("2 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2_5K, _T("2.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ3_15K, _T("3.15 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ4K, _T("4 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ5K, _T("5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ6_3K, _T("6.3 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ8K, _T("8 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ10K, _T("10 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ12_5K, _T("12.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ16K, _T("16 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20K, _T("20 KHz"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqMenu,
		_T("EQ(&G)"));
	m_viewMenu.Append(MFS_CHECKED, ID_TAB, _T("Tab(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PLAYLIST, _T("Playlist(&P)"));
	m_viewMenu.AppendSeparator();
	m_viewMenu.Append(MFS_ENABLED, ID_CLOSEALL, _T("Close All(&C)"));
	m_viewMenu.AppendSeparator();
	m_toolbarMenu.CreatePopup();
	m_toolbarMenu.Append(MFS_CHECKED, ID_TOOLBAR_SIZES, _T("S size(&S)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEM, _T("M size(&M)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEL, _T("L size(&L)"));
	m_toolbarMenu.AppendSeparator();
	m_toolbarMenu.Append(MFS_ENABLED, ID_CUSTOMIZETOOLBAR,
		_T("Customize(&T)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_toolbarMenu, _T("Toolbar"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_viewMenu, _T("View(&V)"));

	// 再生メニュー
	m_playMenu.CreatePopup();
	m_playMenu.Append(MFS_ENABLED, ID_PAUSE, _T("Play/Pause(&P)\tCtrl+P"));
	m_playMenu.Append(MFS_ENABLED, ID_STOP, _T("Stop(&S)\tCtrl+S"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_HEAD, _T("Head(&T)\tCtrl+0"));
	m_playMenu.Append(MFS_ENABLED, ID_PREV, _T("Previous(&V)\tCtrl+B"));
	m_playMenu.Append(MFS_ENABLED, ID_NEXT, _T("Next(&N)\tCtrl+F"));
	m_playMenu.Append(MFS_ENABLED, ID_REWIND, _T("Rewind(&R)\tCtrl+Shift+B"));
	m_playMenu.Append(MFS_ENABLED, ID_FORWARD, 
		_T("Forward(&A)\tCtrl+Shift+F"));
	m_playMenu.AppendSeparator();
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN1SEC, _T("Rewind 1 sec.(&1)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN2SEC, _T("Rewind 2 sec.(&2)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN3SEC, _T("Rewind 3 sec.(&3)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN5SEC, _T("Rewind 5 sec.(&5)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN10SEC, _T("Rewind 10 sec.(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, 
		_T("Rewind(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD1SEC, 
		_T("Forward 1 sec.(&1)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD2SEC, 
		_T("Forward 2 sec.(&2)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD3SEC, 
		_T("Forward 3 sec.(&3)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD5SEC, 
		_T("Forward 5 sec.(&5)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD10SEC, 
		_T("Forward 10 sec.(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, 
		_T("Forward(&F)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_SLOOP, _T("Single Loop(&1)\tCtrl+1"));
	m_playMenu.Append(MF_ENABLED, ID_ALOOP, _T("All Loop(&T)\tCtrl+T"));
	m_playMenu.Append(MFS_ENABLED, ID_RANDOM, _T("Random Play(&H)\tCtrl+H"));
	m_playMenu.Append(MFS_ENABLED, ID_CONTINUE, _T("Continuous Play(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_SAMEARTIST, _T("Same Artist(&S)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_A,
		_T("Set AB Loop(A) To Current Position(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_B,
		_T("Set AB Loop(B) To Current Position(&B)"));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_A_SETTING,
		_T("AB Loop(A) Pos Setting(&C)..."));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_B_SETTING,
		_T("AB Loop(B) Pos Setting(&D)..."));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_MARKERPLAY, _T("Marker Play(&M)"));
	m_playMenu.Append(MFS_ENABLED, ID_ADDMARKER, _T("Add a Marker(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_DELETEMARKER, _T("Delete a Marker(&D)"));
	m_playMenu.Append(MFS_DISABLED, ID_COUNTLOOP, _T("Count Loop(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_INSTANTLOOP, 
		_T("Loop when adding a marker(&I)"));
	m_playMenu.Append(MFS_ENABLED, ID_SETPOSITIONAUTO, 
		_T("Set position automatic when adjusting marker position(&S)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_playMenu, _T("Play(&P)"));

	// エフェクトメニュー
	m_effectMenu.CreatePopup();
	m_presetMenu.CreatePopup();
	m_presetMenu.Append(MFS_ENABLED, ID_ADDPRESET, _T("Add Current Settings(&A)"));
	m_presetMenu.Append(MFS_DISABLED, ID_DELETEPRESET, _T("Delete Selected Preset(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_presetMenu,
		_T("Preset(&P)"));
	m_effectMenu.AppendSeparator();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(MFS_ENABLED, ID_RESETSPEED, _T("Reset Speed(&R)"));
	m_speedMenu.AppendSeparator();
	m_setSpeedMenu.CreatePopup();
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_50, _T("50%(&A)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_60, _T("60%(&B)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_70, _T("70%(&C)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_80, _T("80%(&D)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_90, _T("90%(&E)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_100, _T("100%(&F)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_110, _T("110%(&G)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_120, _T("120%(&H)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_130, _T("130%(&I)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_140, _T("140%(&J)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_150, _T("150%(&K)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_160, _T("160%(&L)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_170, _T("170%(&M)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_180, _T("180%(&N)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_190, _T("190%(&O)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_200, _T("200%(&P)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_250, _T("250%(&Q)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_300, _T("300%(&R)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_350, _T("350%(&S)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_400, _T("400%(&T)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setSpeedMenu,
		_T("Set Speed(&S)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN0_1SPEED, _T("Turn Down 0.1%(&0)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN1SPEED, _T("Turn Down 1%(&1)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN2SPEED, _T("Turn Down 2%(&2)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN3SPEED, _T("Turn Down 3%(&3)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN5SPEED, _T("Turn Down 5%(&5)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN10SPEED, _T("Turn Down 10%(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_UP0_1SPEED, _T("Turn Up 0.1%(&Z)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP1SPEED, _T("Turn Up 1%(&A)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP2SPEED, _T("Turn Up 2%(&B)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP3SPEED, _T("Turn Up 3%(&C)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP5SPEED, _T("Turn Up 5%(&D)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP10SPEED, _T("Turn Up 10%(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MF_ENABLED, ID_DECSPEED, _T("Decrease(&D)..."));
	m_speedMenu.Append(MF_ENABLED, ID_INCSPEED, _T("Increase(&D)..."));
	m_speedMenu.AppendSeparator();
	m_speedDecimalMenu.CreatePopup();
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_0, _T("0 digit(&0)"));
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_1, _T("1 digit(&1)"));
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_2, _T("2 digit(&2)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedDecimalMenu,
		_T("Decimal Digit"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu, 
		_T("Speed(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(MFS_ENABLED, ID_RESETFREQ, _T("Reset Frequency(&R)"));
	m_freqMenu.AppendSeparator();
	m_setFreqMenu.CreatePopup();
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_50, _T("50%(&A)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_60, _T("60%(&B)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_70, _T("70%(&C)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_80, _T("80%(&D)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_90, _T("90%(&E)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_100, _T("100%(&F)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_110, _T("110%(&G)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_120, _T("120%(&H)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_130, _T("130%(&I)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_140, _T("140%(&J)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_150, _T("150%(&K)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_160, _T("160%(&L)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_170, _T("170%(&M)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_180, _T("180%(&N)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_190, _T("190%(&O)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_200, _T("200%(&P)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_250, _T("250%(&Q)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_300, _T("300%(&R)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_350, _T("350%(&S)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_400, _T("400%(&T)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setFreqMenu,
		_T("Set Frequency(&F)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN0_1FREQ, _T("Turn Down 0.1%(&0)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN1FREQ, _T("Turn Down 1%(&1)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN2FREQ, _T("Turn Down 2%(&2)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN3FREQ, _T("Turn Down 3%(&3)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN5FREQ, _T("Turn Down 5%(&5)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN10FREQ, _T("Turn Down 10%(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_UP0_1FREQ, _T("Turn Up 0.1%(&Z)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP1FREQ, _T("Turn Up 1%(&A)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP2FREQ, _T("Turn Up 2%(&B)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP3FREQ, _T("Turn Up 3%(&C)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP5FREQ, _T("Turn Up 5%(&D)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP10FREQ, _T("Turn Up 10%(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MF_ENABLED, ID_DECFREQ, _T("Decrease(&F)..."));
	m_freqMenu.Append(MF_ENABLED, ID_INCFREQ, _T("Increase(&F)..."));
	m_freqMenu.AppendSeparator();
	m_freqDecimalMenu.CreatePopup();
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_0, _T("0 digit(&0)"));
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_1, _T("1 digit(&1)"));
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_2, _T("2 digit(&2)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqDecimalMenu,
		_T("Decimal Digit"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu, 
		_T("Frequency(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(MFS_ENABLED, ID_RESETPITCH, _T("Reset pitch(&R)"));
	m_pitchMenu.AppendSeparator();
	m_setPitchMenu.CreatePopup();
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F12, _T("♭12(&A)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F11, _T("♭11(&B)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F10, _T("♭10(&C)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F9, _T("♭9(&D)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F8, _T("♭8(&E)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F7, _T("♭7(&F)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F6, _T("♭6(&G)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F5, _T("♭5(&H)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F4, _T("♭4(&I)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F3, _T("♭3(&J)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F2, _T("♭2(&K)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F1, _T("♭1(&L)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_0, _T("0(&M)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S1, _T("♯1(&N)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S2, _T("♯2(&O)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S3, _T("♯3(&P)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S4, _T("♯4(&Q)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S5, _T("♯5(&R)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S6, _T("♯6(&S)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S7, _T("♯7(&T)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S8, _T("♯8(&U)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S9, _T("♯9(&V)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S10, _T("♯10(&W)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S11, _T("♯11(&X)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S12, _T("♯12(&Y)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setPitchMenu,
		_T("Set Pitch(&F)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1PITCH, _T("Flat(&1)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN2PITCH, _T("Double Flat(&2)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1OCTPITCH, _T("Down 1 Octave(&3)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1PITCH, _T("Sharp(&A)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP2PITCH, _T("Double Sharp(&B)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1OCTPITCH, _T("Up 1 Octave(&C)"));
	m_pitchMenu.AppendSeparator();
	m_pitchDecimalMenu.CreatePopup();
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_0, _T("0 digit(&0)"));
	m_pitchDecimalMenu.Append(MFS_CHECKED, ID_PITCHDEC_1, _T("1 digit(&1)"));
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_2, _T("2 digit(&2)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchDecimalMenu,
		_T("Decimal Digit"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu, 
		_T("Pitch(&P)"));
	m_volumeMenu.CreatePopup();
	m_volumeMenu.Append(MFS_ENABLED, ID_RESETVOLUME, _T("Reset Volume(&R)"));
	m_volumeMenu.AppendSeparator();
	m_setVolumeMenu.CreatePopup();
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_0, _T("0%(&A)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_10, _T("10%(&B)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_20, _T("20%(&C)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_30, _T("30%(&D)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_40, _T("40%(&E)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_50, _T("50%(&F)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_60, _T("60%(&G)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_70, _T("70%(&H)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_80, _T("80%(&I)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_90, _T("90%(&J)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_100, _T("100%(&K)"));
	m_volumeMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setVolumeMenu,
		_T("Set Volume(&V)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_volumeMenu,
		_T("Volume(&V)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWSUPER, 
		_T("Boost Low(Ultra-strong)(&A)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGHEST, 
		_T("Boost Low(Strongest)(&B)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGH, 
		_T("Boost Low(Strong)(&C)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWMIDDLE, 
		_T("Boost Low(Middle)(&D)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOW, _T("Boost Low(Weak)(&E)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOWEST, 
		_T("Boost Low(Weakest)(&G)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLESUPER, 
		_T("Boost Middle(Ultra-strong)(&H)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGHEST, 
		_T("Boost Middle(Strongest)(&I)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGH, 
		_T("Boost Middle(Strong)(&J)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEMIDDLE, 
		_T("Boost Middle(Middle)(&K)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOW, 
		_T("Boost Middle(Weak)(&L)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOWEST, 
		_T("Boost Middle(Weakest)(&M)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHSUPER, 
		_T("Boost High(Ultra-strong)(&N)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGHEST, 
		_T("Boost High(Strongest)(&O)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGH, 
		_T("Boost High(Strong)(&P)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHMIDDLE, 
		_T("Boost High(Middle)(&Q)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOW, 
		_T("Boost High(Weak)(&R)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOWEST, 
		_T("Boost High(Weakest)(&S)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTSUPER, 
		_T("Low Cut(Ultra-strong)(&T)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGHEST, 
		_T("Low Cut(Strongest)(&U)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGH, 
		_T("Low Cut(Strong)(&V)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTMIDDLE, 
		_T("Low Cut(Middle)(&W)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOW, _T("Low Cut(Weak)(&X)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOWEST, 
		_T("Low Cut(Weakest)(&Y)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTSUPER, 
		_T("Middle Cut(Ultra-strong)(&Z)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGHEST, 
		_T("Middle Cut(Strongest)(&0)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGH, 
		_T("Middle Cut(Strong)(&1)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTMIDDLE, 
		_T("Middle Cut(Middle)(&2)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOW, 
		_T("Middle Cut(Weak)(&3)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOWEST, 
		_T("Middle Cut(Weakest)(&4)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTSUPER, 
		_T("High Cut(Ultra-strong)(&5)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGHEST, 
		_T("High Cut(Strongest)(&6)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGH, 
		_T("High Cut(Strong)(&7)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTMIDDLE, 
		_T("High Cut(Middle)(&8)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOW, 
		_T("High Cut(Weak)(&9)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOWEST, 
		_T("High Cut(Weakest)(&0)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu, 
		_T("EQ Preset(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_DEFAULT, _T("Default(&D)"));
	m_reverbMenu.AppendSeparator();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_CUSTOMIZE, _T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu, 
		_T("Reverb(&R)"));
	m_3dreverbMenu.CreatePopup();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_DEFAULT, _T("Default(&D)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PADDEDCELL, 
		_T("Padded Cell(&P)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ROOM, _T("Room(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_BATHROOM, _T("Bathroom(&B)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LIVINGROOM, 
		_T("Living Room(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONEROOM, 
		_T("Stone Room(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_AUDITORIUM, 
		_T("Auditorium(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CONCERTHALL, 
		_T("Concert Hall(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CAVE, _T("Cave(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ARENA, _T("Arena(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HANGAR, _T("Hangar(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CARPETEDHALLWAY, 
		_T("Carpeted Hallway(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HALLWAY, _T("Hallway(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONECORRIDOR, 
		_T("Stone Corridor(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ALLEY, _T("Alley(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_FOREST, _T("Forest(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CITY, _T("City(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MOUNTAINS, _T("Mountains(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_QUARRY, _T("Quarry(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLAIN, _T("Plain(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PARKINGLOT, 
		_T("Parking Lot(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SEWERPIPE, 
		_T("Sewer Pipe(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_UNDERWATER, 
		_T("Underwater(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SMALLROOM, 
		_T("Small Room(&S)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMROOM, 
		_T("Medium Room(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEROOM, 
		_T("Large Room(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMHALL, 
		_T("Medium Hall(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEHALL, 
		_T("Large Hall(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLATE, _T("Plate(&P)"));
	m_3dreverbMenu.AppendSeparator();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CUSTOMIZE,
		_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_3dreverbMenu, 
		_T("3D Reverb(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DEFAULT, _T("Default(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_SHORT, _T("Short Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MEDIUM, _T("Medium Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_LONG, _T("Long Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOSHORT,
					   _T("Stereo Short Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOMEDIUM,
					   _T("Stereo Medium Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOLONG,
					   _T("Stereo Long Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MOUNTAIN, 
		_T("Mountain Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_BIG, _T("Big Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOBIG,
					   _T("Stereo Big Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLING, _T("Doubling(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLEKICK, 
		_T("Double Kick(&D)"));
	m_delayMenu.AppendSeparator();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_CUSTOMIZE, 
		_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu, 
		_T("Delay(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_DEFAULT, _T("Default(&D)"));
	m_chorusMenu.AppendSeparator();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_CUSTOMIZE, _T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("Chorus(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_DEFAULT,
							_T("Default(&D)"));
	m_compressorMenu.AppendSeparator();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_CUSTOMIZE,
							_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("Compressor(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_DEFAULT,
							_T("Default(&D)"));
	m_flangerMenu.AppendSeparator();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_CUSTOMIZE,
							_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("Flanger(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_DEFAULT,
							_T("Default(&D)"));
	m_gargleMenu.AppendSeparator();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_CUSTOMIZE,
							_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("Gargle(&F)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_DEFAULT, 
		_T("Default(&D)"));
	m_distortionMenu.AppendSeparator();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_CUSTOMIZE, 
		_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("Distortion(&D)"));
	m_effectMenu.AppendSeparator();
	m_soundEffectMenu.CreatePopup();
	m_soundEffectMenu.Append(MFS_ENABLED, ID_RECORDNOISE,
		_T("Record Noise(&R)"));
	m_soundEffectMenu.Append(MFS_ENABLED, ID_WAVE, _T("Wave(&W)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_soundEffectMenu,
		_T("Sound Effects(&S)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_NORMALIZE, _T("Normalize(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_VOCALCANCEL, _T("Vocal Cancel(&V)"));
	m_effectMenu.Append(MFS_ENABLED, ID_REVERSE, _T("Reverse Play(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_RECORD, _T("Old Record Play(&F)"));
	m_effectMenu.Append(MFS_ENABLED, ID_LOWBATTERY, _T("Low Battery(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_NOSENSE, _T("No Sense(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_BASSCOPY, _T("Transcribe Bass(&T)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CYMBALCOPY,
		_T("Transcribe Drums (Hi-Hat, Cymbals)(&H)"));
	m_effectMenu.Append(MFS_ENABLED, ID_EARTRAINING, _T("Ear Training(&E)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_MONORAL, _T("Monoral(&M)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYLEFT, _T("Only Left(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYRIGHT, _T("Only Right(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CHANGELR, _T("Change LR(&C)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_RESETALL, _T("Reset All(&R)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_effectMenu, _T("Effect(&E)"));

	// システムメニュー
	m_systemMenu.CreatePopup();
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVIDEOSCREENVISIBLE, 
		_T("Video Screen(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERTIMESLIDERVISIBLE, 
		_T("Position Slider(&T)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERSPEEDVISIBLE, 
		_T("Speed(&S)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERFREQVISIBLE, 
		_T("Frequency(&F)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPITCHVISIBLE, 
		_T("Pitch(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVOLUMEVISIBLE, 
		_T("Volume(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPANVISIBLE, 
		_T("PAN(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVEREQVISIBLE, 
		_T("Graphic Equalizer(&G)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERLISTVISIBLE, 
		_T("Playlist(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu, 
		_T("Visible(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSLOOP, 
		_T("Single Loop(&1)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERALOOP, 
		_T("All Loop(&T)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRANDOM, 
		_T("Random(&H)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERCONTINUE, 
		_T("Continue(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERINSTANTLOOP, 
		_T("Loop when adding a marker(&I)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSETPOSITIONAUTO, 
		_T("Set position automatic when adjusting marker position(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERREVERSE, 
		_T("Reverse(&R)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRECORD, 
		_T("Record(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu, 
		_T("Play Mode(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWPOS, 
		_T("Window Position(&P)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWSIZE, _T("Window Size(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPLAYPOS,
		_T("Play Position(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERSPEED, _T("Speed(&S)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERFREQ, 
		_T("Frequency(&F)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPITCH, _T("Pitch(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERVOLUME, _T("Volume(&V)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPAN, _T("Pan(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVEREQ, 
		_T("Graphic Equalizer(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERLIST, _T("Playlist(&P)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, 
		_T("Recover(&R)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_KEYSETTING, 
		_T("Shortcut Key Setting(&K)..."));
	m_systemMenu.Append(MF_ENABLED, ID_OUTKEYSETTING, 
		_T("Global Hot Key Setting(&G)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_LIMIT, _T("Max/Min Setting(&L)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TIMERPLAY, _T("Timer Setting(&T)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYRANGE, 
		_T("Play Range(&R)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYPOSITION, 
		_T("Play Position(&P)..."));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTSTOP, _T("Fade Out Stop(&F)"));
	m_fadeoutMenu.CreatePopup();
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP1SEC, _T("1 sec(&1)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP2SEC, _T("2 sec(&2)"));
	m_fadeoutMenu.Append(MFS_CHECKED, ID_FADEOUTSTOP3SEC, _T("3 sec(&3)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP4SEC, _T("4 sec(&4)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP5SEC, _T("5 sec(&5)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP6SEC, _T("6 sec(&6)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP7SEC, _T("7 sec(&7)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP8SEC, _T("8 sec(&8)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP9SEC, _T("9 sec(&9)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP10SEC, _T("10 sec(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutMenu,
		_T("Fade Out Stop Time(&G)"));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTNEXT, _T("Fade Out Next(&F)"));
	m_fadeoutNextMenu.CreatePopup();
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT1SEC, _T("1 sec(&1)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT2SEC, _T("2 sec(&2)"));
	m_fadeoutNextMenu.Append(MFS_CHECKED, ID_FADEOUTNEXT3SEC, _T("3 sec(&3)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT4SEC, _T("4 sec(&4)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT5SEC, _T("5 sec(&5)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT6SEC, _T("6 sec(&6)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT7SEC, _T("7 sec(&7)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT8SEC, _T("8 sec(&8)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT9SEC, _T("9 sec(&9)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT10SEC, _T("10 sec(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutNextMenu,
		_T("Fade Out Next Time(&H)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TWEET, _T("Tweet on Twitter(&T)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_METRONOME, _T("Metronome(&M)..."));
	m_systemMenu.AppendSeparator();
	m_qualityMenu.CreatePopup();
	m_qualityMenu.Append(MFS_CHECKED, ID_QUALITY_NORMAL, _T("Normal(&N)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_ASIO, _T("ASIO(&A)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_WASAPI, _T("WASAPI(&W)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_qualityMenu,
		_T("Quality(&Q)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_DOUBLERUN, _T("Double Runnable(&D)"));
	m_systemMenu.Append(MF_ENABLED, ID_TOPMOST, _T("Bring Window Top(&S)"));
	m_systemMenu.Append(MF_ENABLED, ID_TASKTRAY, 
		_T("Minimize to System Tray(&T)"));
	m_systemMenu.Append(MF_ENABLED, ID_COPYTIME, 
		_T("Copy Current Position to Clipboard(&C)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_systemMenu, _T("System(&S)"));

	CheckItem(ID_CONTINUE, MF_CHECKED);

	// ヘルプメニュー
	m_helpMenu.CreatePopup();
	m_helpMenu.Append(MFS_ENABLED, ID_MANUAL, _T("Manual(&M)..."));
	m_helpMenu.AppendSeparator();
	m_helpMenu.Append(MFS_ENABLED, ID_UPDATECHECK, _T("Update Check(&U)..."));
	m_helpMenu.Append(MFS_ENABLED, ID_VERSIONINFO, _T("Version(&A)..."));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_helpMenu, _T("Help(&H)"));
#endif // JP
	if(!m_hMenu || !(HMENU)m_fileMenu || !(HMENU)m_editMenu ||
	   !(HMENU)m_viewMenu || !(HMENU)m_playMenu || !(HMENU)m_returnMenu ||
	   !(HMENU)m_forwardMenu || !(HMENU)m_systemMenu ||
	   !(HMENU)m_recoveryMenu || !(HMENU)m_recoverVisibleMenu ||
	   !(HMENU)m_recoverPlayModeMenu || !(HMENU)m_helpMenu)
		return FALSE;
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
	BOOL bVisible = IsItemChecked(ID_EQ);
	if(bVisible) m_rMainWnd.SetEQVisible(); // 非表示にしておく
	CheckItem(uID, IsItemChecked(uID) ? MF_UNCHECKED : MF_CHECKED);
	if(bVisible) m_rMainWnd.SetEQVisible(); // 再表示
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
// 停止時フェードアウト時間メニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckFadeoutMenu()
{
	CheckItem(ID_FADEOUTSTOP1SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP2SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP3SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP4SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP5SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP6SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP7SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP8SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP9SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP10SEC, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 切替時フェードアウト時間メニューのチェックを外す
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckFadeoutNextMenu()
{
	CheckItem(ID_FADEOUTNEXT1SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT2SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT3SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT4SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT5SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT6SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT7SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT8SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT9SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT10SEC, MF_UNCHECKED);
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
	for(int i = 1; i < nCount; i++) CheckItem(ID_PRESET + i, MF_UNCHECKED);
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
// メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_OPENFILE:
		OnOpenFileMenuSelected();
		break;
	case ID_ADDFILE:
		OnAddFileMenuSelected();
		break;
	case ID_OPENFOLDER:
		OnOpenFolderMenuSelected();
		break;
	case ID_ADDFOLDER:
		OnAddFolderMenuSelected();
		break;
	case ID_OPENURL:
		OnOpenURLMenuSelected();
		break;
	case ID_ADDURL:
		OnAddURLMenuSelected();
		break;
	case ID_SAVEFILE:
		OnSaveFileMenuSelected();
		break;
	case ID_SAVEALLFILE:
		OnSaveAllFileMenuSelected();
		break;
	case ID_LAMECOMMANDLINE:
		OnLAMECommandLineMenuSelected();
		break;
	case ID_EXIT:
		OnExitMenuSelected();
		break;
	case ID_DELETE:
		OnDeleteMenuSelected();
		break;
	case ID_SELECTALL:
		OnSelectAllMenuSelected();
		break;
	case ID_VIDEOSCREEN:
		OnVideoScreenMenuSelected();
		break;
	case ID_LYRICS:
		OnLyricsMenuSelected();
		break;
	case ID_PITCHANALYSER:
		OnPitchAnalyserMenuSelected();
		break;
	case ID_TIMESLIDER:
		OnTimeSliderMenuSelected();
		break;
	case ID_EXPLORER:
		OnExplorerMenuSelected();
		break;
	case ID_SPEED:
		OnSpeedMenuSelected();
		break;
	case ID_FREQ:
		OnFreqMenuSelected();
		break;
	case ID_PITCH:
		OnPitchMenuSelected();
		break;
	case ID_VOLUME:
		OnVolumeMenuSelected();
		break;
	case ID_PAN:
		OnPanMenuSelected();
		break;
	case ID_EQ:
		OnEQMenuSelected();
		break;
	case ID_EQ20:
		OnEQ20MenuSelected();
		break;
	case ID_EQ25:
		OnEQ25MenuSelected();
		break;
	case ID_EQ31_5:
		OnEQ31_5MenuSelected();
		break;
	case ID_EQ40:
		OnEQ40MenuSelected();
		break;
	case ID_EQ50:
		OnEQ50MenuSelected();
		break;
	case ID_EQ63:
		OnEQ63MenuSelected();
		break;
	case ID_EQ80:
		OnEQ80MenuSelected();
		break;
	case ID_EQ100:
		OnEQ100MenuSelected();
		break;
	case ID_EQ125:
		OnEQ125MenuSelected();
		break;
	case ID_EQ160:
		OnEQ160MenuSelected();
		break;
	case ID_EQ200:
		OnEQ200MenuSelected();
		break;
	case ID_EQ250:
		OnEQ250MenuSelected();
		break;
	case ID_EQ315:
		OnEQ315MenuSelected();
		break;
	case ID_EQ400:
		OnEQ400MenuSelected();
		break;
	case ID_EQ500:
		OnEQ500MenuSelected();
		break;
	case ID_EQ630:
		OnEQ630MenuSelected();
		break;
	case ID_EQ800:
		OnEQ800MenuSelected();
		break;
	case ID_EQ1K:
		OnEQ1KMenuSelected();
		break;
	case ID_EQ1_25K:
		OnEQ1_25KMenuSelected();
		break;
	case ID_EQ1_6K:
		OnEQ1_6KMenuSelected();
		break;
	case ID_EQ2K:
		OnEQ2KMenuSelected();
		break;
	case ID_EQ2_5K:
		OnEQ2_5KMenuSelected();
		break;
	case ID_EQ3_15K:
		OnEQ3_15KMenuSelected();
		break;
	case ID_EQ4K:
		OnEQ4KMenuSelected();
		break;
	case ID_EQ5K:
		OnEQ5KMenuSelected();
		break;
	case ID_EQ6_3K:
		OnEQ6_3KMenuSelected();
		break;
	case ID_EQ8K:
		OnEQ8KMenuSelected();
		break;
	case ID_EQ10K:
		OnEQ10KMenuSelected();
		break;
	case ID_EQ12_5K:
		OnEQ12_5KMenuSelected();
		break;
	case ID_EQ16K:
		OnEQ16KMenuSelected();
		break;
	case ID_EQ20K:
		OnEQ20KMenuSelected();
		break;
	case ID_TAB:
		OnTabMenuSelected();
		break;
	case ID_PLAYLIST:
		OnPlayListMenuSelected();
		break;
	case ID_CLOSEALL:
		OnCloseAllMenuSelected();
		break;
	case ID_TOOLBAR_SIZES:
		OnToolbarSSizeMenuSelected();
		break;
	case ID_TOOLBAR_SIZEM:
		OnToolbarMSizeMenuSelected();
		break;
	case ID_TOOLBAR_SIZEL:
		OnToolbarLSizeMenuSelected();
		break;
	case ID_CUSTOMIZETOOLBAR:
		OnCustomizeToolbarMenuSelected();
		break;
	case ID_HEAD:
		OnHeadMenuSelected();
		break;
	case ID_PREV:
		OnPreviousMenuSelected();
		break;
	case ID_NEXT:
		OnNextMenuSelected();
		break;
	case ID_PAUSE:
		OnPauseMenuSelected();
		break;
	case ID_REWIND:
		OnRewindMenuSelected();
		break;
	case ID_FORWARD:
		OnForwardMenuSelected();
		break;
	case ID_PAUSE_RETURN1SEC:
		OnPauseAndReturn1SecMenuSelected();
		break;
	case ID_PAUSE_RETURN2SEC:
		OnPauseAndReturn2SecMenuSelected();
		break;
	case ID_PAUSE_RETURN3SEC:
		OnPauseAndReturn3SecMenuSelected();
		break;
	case ID_PAUSE_RETURN5SEC:
		OnPauseAndReturn5SecMenuSelected();
		break;
	case ID_PAUSE_RETURN10SEC:
		OnPauseAndReturn10SecMenuSelected();
		break;
	case ID_RETURN1SEC:
		OnReturn1SecMenuSelected();
		break;
	case ID_RETURN2SEC:
		OnReturn2SecMenuSelected();
		break;
	case ID_RETURN3SEC:
		OnReturn3SecMenuSelected();
		break;
	case ID_RETURN5SEC:
		OnReturn5SecMenuSelected();
		break;
	case ID_RETURN10SEC:
		OnReturn10SecMenuSelected();
		break;
	case ID_FORWARD1SEC:
		OnForward1SecMenuSelected();
		break;
	case ID_FORWARD2SEC:
		OnForward2SecMenuSelected();
		break;
	case ID_FORWARD3SEC:
		OnForward3SecMenuSelected();
		break;
	case ID_FORWARD5SEC:
		OnForward5SecMenuSelected();
		break;
	case ID_FORWARD10SEC:
		OnForward10SecMenuSelected();
		break;
	case ID_ADDPRESET:
		OnAddPresetMenuSelected();
		break;
	case ID_DELETEPRESET:
		OnDeletePresetMenuSelected();
		break;
	case ID_RESETSPEED:
		OnResetSpeedMenuSelected();
		break;
	case ID_SPEED_50:
		OnSetSpeed50MenuSelected();
		break;
	case ID_SPEED_60:
		OnSetSpeed60MenuSelected();
		break;
	case ID_SPEED_70:
		OnSetSpeed70MenuSelected();
		break;
	case ID_SPEED_80:
		OnSetSpeed80MenuSelected();
		break;
	case ID_SPEED_90:
		OnSetSpeed90MenuSelected();
		break;
	case ID_SPEED_100:
		OnSetSpeed100MenuSelected();
		break;
	case ID_SPEED_110:
		OnSetSpeed110MenuSelected();
		break;
	case ID_SPEED_120:
		OnSetSpeed120MenuSelected();
		break;
	case ID_SPEED_130:
		OnSetSpeed130MenuSelected();
		break;
	case ID_SPEED_140:
		OnSetSpeed140MenuSelected();
		break;
	case ID_SPEED_150:
		OnSetSpeed150MenuSelected();
		break;
	case ID_SPEED_160:
		OnSetSpeed160MenuSelected();
		break;
	case ID_SPEED_170:
		OnSetSpeed170MenuSelected();
		break;
	case ID_SPEED_180:
		OnSetSpeed180MenuSelected();
		break;
	case ID_SPEED_190:
		OnSetSpeed190MenuSelected();
		break;
	case ID_SPEED_200:
		OnSetSpeed200MenuSelected();
		break;
	case ID_SPEED_250:
		OnSetSpeed250MenuSelected();
		break;
	case ID_SPEED_300:
		OnSetSpeed300MenuSelected();
		break;
	case ID_SPEED_350:
		OnSetSpeed350MenuSelected();
		break;
	case ID_SPEED_400:
		OnSetSpeed400MenuSelected();
		break;
	case ID_DOWN0_1SPEED:
		OnDown0_1SpeedMenuSelected();
		break;
	case ID_DOWN1SPEED:
		OnDown1SpeedMenuSelected();
		break;
	case ID_DOWN2SPEED:
		OnDown2SpeedMenuSelected();
		break;
	case ID_DOWN3SPEED:
		OnDown3SpeedMenuSelected();
		break;
	case ID_DOWN5SPEED:
		OnDown5SpeedMenuSelected();
		break;
	case ID_DOWN10SPEED:
		OnDown10SpeedMenuSelected();
		break;
	case ID_UP0_1SPEED:
		OnUp0_1SpeedMenuSelected();
		break;
	case ID_UP1SPEED:
		OnUp1SpeedMenuSelected();
		break;
	case ID_UP2SPEED:
		OnUp2SpeedMenuSelected();
		break;
	case ID_UP3SPEED:
		OnUp3SpeedMenuSelected();
		break;
	case ID_UP5SPEED:
		OnUp5SpeedMenuSelected();
		break;
	case ID_UP10SPEED:
		OnUp10SpeedMenuSelected();
		break;
	case ID_RESETFREQ:
		OnResetFreqMenuSelected();
		break;
	case ID_FREQ_50:
		OnSetFreq50MenuSelected();
		break;
	case ID_FREQ_60:
		OnSetFreq60MenuSelected();
		break;
	case ID_FREQ_70:
		OnSetFreq70MenuSelected();
		break;
	case ID_FREQ_80:
		OnSetFreq80MenuSelected();
		break;
	case ID_FREQ_90:
		OnSetFreq90MenuSelected();
		break;
	case ID_FREQ_100:
		OnSetFreq100MenuSelected();
		break;
	case ID_FREQ_110:
		OnSetFreq110MenuSelected();
		break;
	case ID_FREQ_120:
		OnSetFreq120MenuSelected();
		break;
	case ID_FREQ_130:
		OnSetFreq130MenuSelected();
		break;
	case ID_FREQ_140:
		OnSetFreq140MenuSelected();
		break;
	case ID_FREQ_150:
		OnSetFreq150MenuSelected();
		break;
	case ID_FREQ_160:
		OnSetFreq160MenuSelected();
		break;
	case ID_FREQ_170:
		OnSetFreq170MenuSelected();
		break;
	case ID_FREQ_180:
		OnSetFreq180MenuSelected();
		break;
	case ID_FREQ_190:
		OnSetFreq190MenuSelected();
		break;
	case ID_FREQ_200:
		OnSetFreq200MenuSelected();
		break;
	case ID_FREQ_250:
		OnSetFreq250MenuSelected();
		break;
	case ID_FREQ_300:
		OnSetFreq300MenuSelected();
		break;
	case ID_FREQ_350:
		OnSetFreq350MenuSelected();
		break;
	case ID_FREQ_400:
		OnSetFreq400MenuSelected();
		break;
	case ID_DOWN0_1FREQ:
		OnDown0_1FreqMenuSelected();
		break;
	case ID_DOWN1FREQ:
		OnDown1FreqMenuSelected();
		break;
	case ID_DOWN2FREQ:
		OnDown2FreqMenuSelected();
		break;
	case ID_DOWN3FREQ:
		OnDown3FreqMenuSelected();
		break;
	case ID_DOWN5FREQ:
		OnDown5FreqMenuSelected();
		break;
	case ID_DOWN10FREQ:
		OnDown10FreqMenuSelected();
		break;
	case ID_UP0_1FREQ:
		OnUp0_1FreqMenuSelected();
		break;
	case ID_UP1FREQ:
		OnUp1FreqMenuSelected();
		break;
	case ID_UP2FREQ:
		OnUp2FreqMenuSelected();
		break;
	case ID_UP3FREQ:
		OnUp3FreqMenuSelected();
		break;
	case ID_UP5FREQ:
		OnUp5FreqMenuSelected();
		break;
	case ID_UP10FREQ:
		OnUp10FreqMenuSelected();
		break;
	case ID_RESETPITCH:
		OnResetPitchMenuSelected();
		break;
	case ID_PITCH_F12:
		OnSetPitchFlat12MenuSelected();
		break;
	case ID_PITCH_F11:
		OnSetPitchFlat11MenuSelected();
		break;
	case ID_PITCH_F10:
		OnSetPitchFlat10MenuSelected();
		break;
	case ID_PITCH_F9:
		OnSetPitchFlat9MenuSelected();
		break;
	case ID_PITCH_F8:
		OnSetPitchFlat8MenuSelected();
		break;
	case ID_PITCH_F7:
		OnSetPitchFlat7MenuSelected();
		break;
	case ID_PITCH_F6:
		OnSetPitchFlat6MenuSelected();
		break;
	case ID_PITCH_F5:
		OnSetPitchFlat5MenuSelected();
		break;
	case ID_PITCH_F4:
		OnSetPitchFlat4MenuSelected();
		break;
	case ID_PITCH_F3:
		OnSetPitchFlat3MenuSelected();
		break;
	case ID_PITCH_F2:
		OnSetPitchFlat2MenuSelected();
		break;
	case ID_PITCH_F1:
		OnSetPitchFlat1MenuSelected();
		break;
	case ID_PITCH_0:
		OnSetPitchNaturalMenuSelected();
		break;
	case ID_PITCH_S1:
		OnSetPitchSharp1MenuSelected();
		break;
	case ID_PITCH_S2:
		OnSetPitchSharp2MenuSelected();
		break;
	case ID_PITCH_S3:
		OnSetPitchSharp3MenuSelected();
		break;
	case ID_PITCH_S4:
		OnSetPitchSharp4MenuSelected();
		break;
	case ID_PITCH_S5:
		OnSetPitchSharp5MenuSelected();
		break;
	case ID_PITCH_S6:
		OnSetPitchSharp6MenuSelected();
		break;
	case ID_PITCH_S7:
		OnSetPitchSharp7MenuSelected();
		break;
	case ID_PITCH_S8:
		OnSetPitchSharp8MenuSelected();
		break;
	case ID_PITCH_S9:
		OnSetPitchSharp9MenuSelected();
		break;
	case ID_PITCH_S10:
		OnSetPitchSharp10MenuSelected();
		break;
	case ID_PITCH_S11:
		OnSetPitchSharp11MenuSelected();
		break;
	case ID_PITCH_S12:
		OnSetPitchSharp12MenuSelected();
		break;
	case ID_DOWN1PITCH:
		OnDown1PitchMenuSelected();
		break;
	case ID_DOWN2PITCH:
		OnDown2PitchMenuSelected();
		break;
	case ID_DOWN1OCTPITCH:
		OnDown1OctavePitchMenuSelected();
		break;
	case ID_UP1PITCH:
		OnUp1PitchMenuSelected();
		break;
	case ID_UP2PITCH:
		OnUp2PitchMenuSelected();
		break;
	case ID_UP1OCTPITCH:
		OnUp1OctavePitchMenuSelected();
		break;
	case ID_UPVOLUME:
		OnUpVolumeMenuSelected();
		break;
	case ID_DOWNVOLUME:
		OnDownVolumeMenuSelected();
		break;
	case ID_STOP:
		OnStopMenuSelected();
		break;
	case ID_SLOOP:
		OnSingleLoopMenuSelected();
		break;
	case ID_ALOOP:
		OnAllLoopMenuSelected();
		break;
	case ID_RANDOM:
		OnRandomMenuSelected();
		break;
	case ID_CONTINUE:
		OnContinueMenuSelected();
		break;
	case ID_SAMEARTIST:
		OnSameArtistMenuSelected();
		break;
	case ID_ABLOOP_A:
		OnABLoopAMenuSelected();
		break;
	case ID_ABLOOP_B:
		OnABLoopBMenuSelected();
		break;
	case ID_ABLOOP_A_SETTING:
		OnABLoopASettingMenuSelected();
		break;
	case ID_ABLOOP_B_SETTING:
		OnABLoopBSettingMenuSelected();
		break;
	case ID_MARKERPLAY:
		OnMarkerPlayMenuSelected();
		break;
	case ID_ADDMARKER:
		OnAddMarkerMenuSelected();
		break;
	case ID_DELETEMARKER:
		OnDeleteMarkerMenuSelected();
		break;
	case ID_COUNTLOOP:
		OnCountLoopMenuSelected();
		break;
	case ID_INSTANTLOOP:
		OnInstantLoopMenuSelected();
		break;
	case ID_SETPOSITIONAUTO:
		OnSetPositionAutoMenuSelected();
		break;
	case ID_RECORDNOISE:
		OnRecordNoiseMenuSelected();
		break;
	case ID_WAVE:
		OnWaveMenuSelected();
		break;
	case ID_NORMALIZE:
		OnNormalizeMenuSelected();
		break;
	case ID_VOCALCANCEL:
		OnVocalCancelMenuSelected();
		break;
	case ID_REVERSE:
		OnReverseMenuSelected();
		break;
	case ID_RECORD:
		OnRecordMenuSelected();
		break;
	case ID_LOWBATTERY:
		OnLowBatteryMenuSelected();
		break;
	case ID_NOSENSE:
		OnNoSenseMenuSelected();
		break;
	case ID_BASSCOPY:
		OnBassCopyMenuSelected();
		break;
	case ID_CYMBALCOPY:
		OnDrumsCopyMenuSelected();
		break;
	case ID_EARTRAINING:
		OnEarTrainingMenuSelected();
		break;
	case ID_MONORAL:
		OnMonoralMenuSelected();
		break;
	case ID_ONLYLEFT:
		OnOnlyLeftMenuSelected();
		break;
	case ID_ONLYRIGHT:
		OnOnlyRightMenuSelected();
		break;
	case ID_CHANGELR:
		OnChangeLRMenuSelected();
		break;
	case ID_RESETALL:
		OnResetAllMenuSelected();
		break;
	case ID_RECOVERVIDEOSCREENVISIBLE:
	case ID_RECOVERTIMESLIDERVISIBLE:
	case ID_RECOVERSPEEDVISIBLE:
	case ID_RECOVERFREQVISIBLE:
	case ID_RECOVERPITCHVISIBLE:
	case ID_RECOVERVOLUMEVISIBLE:
	case ID_RECOVERPANVISIBLE:
	case ID_RECOVEREQVISIBLE:
	case ID_RECOVERLISTVISIBLE:
	case ID_RECOVERSLOOP:
	case ID_RECOVERALOOP:
	case ID_RECOVERRANDOM:
	case ID_RECOVERCONTINUE:
	case ID_RECOVERINSTANTLOOP:
	case ID_RECOVERSETPOSITIONAUTO:
	case ID_RECOVERREVERSE:
	case ID_RECOVERRECORD:
	case ID_RECOVERWPOS:
	case ID_RECOVERWSIZE:
	case ID_RECOVERPLAYPOS:
	case ID_RECOVERSPEED:
	case ID_RECOVERFREQ:
	case ID_RECOVERPITCH:
	case ID_RECOVERVOLUME:
	case ID_RECOVERPAN:
	case ID_RECOVEREQ:
	case ID_RECOVERLIST:
		SwitchItemChecked(id);
		break;
	case ID_KEYSETTING:
		OnKeySettingMenuSelected();
		break;
	case ID_OUTKEYSETTING:
		OnOutKeySettingMenuSelected();
		break;
	case ID_LIMIT:
		OnLimitMenuSelected();
		break;
	case ID_TIMERPLAY:
		OnTimerPlayMenuSelected();
		break;
	case ID_PLAYRANGE:
		OnPlayRangeMenuSelected();
		break;
	case ID_PLAYPOSITION:
		OnPlayPositionMenuSelected();
		break;
	case ID_DECSPEED:
		OnDecSpeedMenuSelected();
		break;
	case ID_INCSPEED:
		OnIncSpeedMenuSelected();
		break;
	case ID_SPEEDDEC_0:
		OnSetSpeedDecimal0MenuSelected();
		break;
	case ID_SPEEDDEC_1:
		OnSetSpeedDecimal1MenuSelected();
		break;
	case ID_SPEEDDEC_2:
		OnSetSpeedDecimal2MenuSelected();
		break;
	case ID_DECFREQ:
		OnDecFreqMenuSelected();
		break;
	case ID_INCFREQ:
		OnIncFreqMenuSelected();
		break;
	case ID_FREQDEC_0:
		OnSetFreqDecimal0MenuSelected();
		break;
	case ID_FREQDEC_1:
		OnSetFreqDecimal1MenuSelected();
		break;
	case ID_FREQDEC_2:
		OnSetFreqDecimal2MenuSelected();
		break;
	case ID_PITCHDEC_0:
		OnSetPitchDecimal0MenuSelected();
		break;
	case ID_PITCHDEC_1:
		OnSetPitchDecimal1MenuSelected();
		break;
	case ID_PITCHDEC_2:
		OnSetPitchDecimal2MenuSelected();
		break;
	case ID_RESETVOLUME:
		OnResetVolumeMenuSelected();
		break;
	case ID_VOLUME_0:
		OnSetVolume0MenuSelected();
		break;
	case ID_VOLUME_10:
		OnSetVolume10MenuSelected();
		break;
	case ID_VOLUME_20:
		OnSetVolume20MenuSelected();
		break;
	case ID_VOLUME_30:
		OnSetVolume30MenuSelected();
		break;
	case ID_VOLUME_40:
		OnSetVolume40MenuSelected();
		break;
	case ID_VOLUME_50:
		OnSetVolume50MenuSelected();
		break;
	case ID_VOLUME_60:
		OnSetVolume60MenuSelected();
		break;
	case ID_VOLUME_70:
		OnSetVolume70MenuSelected();
		break;
	case ID_VOLUME_80:
		OnSetVolume80MenuSelected();
		break;
	case ID_VOLUME_90:
		OnSetVolume90MenuSelected();
		break;
	case ID_VOLUME_100:
		OnSetVolume100MenuSelected();
		break;
	case ID_FADEOUTSTOP:
		OnFadeoutMenuSelected();
		break;
	case ID_FADEOUTSTOP1SEC:
		OnFadeout1SecMenuSelected();
		break;
	case ID_FADEOUTSTOP2SEC:
		OnFadeout2SecMenuSelected();
		break;
	case ID_FADEOUTSTOP3SEC:
		OnFadeout3SecMenuSelected();
		break;
	case ID_FADEOUTSTOP4SEC:
		OnFadeout4SecMenuSelected();
		break;
	case ID_FADEOUTSTOP5SEC:
		OnFadeout5SecMenuSelected();
		break;
	case ID_FADEOUTSTOP6SEC:
		OnFadeout6SecMenuSelected();
		break;
	case ID_FADEOUTSTOP7SEC:
		OnFadeout7SecMenuSelected();
		break;
	case ID_FADEOUTSTOP8SEC:
		OnFadeout8SecMenuSelected();
		break;
	case ID_FADEOUTSTOP9SEC:
		OnFadeout9SecMenuSelected();
		break;
	case ID_FADEOUTSTOP10SEC:
		OnFadeout10SecMenuSelected();
		break;
	case ID_FADEOUTNEXT:
		OnFadeoutNextMenuSelected();
		break;
	case ID_FADEOUTNEXT1SEC:
		OnFadeoutNext1SecMenuSelected();
		break;
	case ID_FADEOUTNEXT2SEC:
		OnFadeoutNext2SecMenuSelected();
		break;
	case ID_FADEOUTNEXT3SEC:
		OnFadeoutNext3SecMenuSelected();
		break;
	case ID_FADEOUTNEXT4SEC:
		OnFadeoutNext4SecMenuSelected();
		break;
	case ID_FADEOUTNEXT5SEC:
		OnFadeoutNext5SecMenuSelected();
		break;
	case ID_FADEOUTNEXT6SEC:
		OnFadeoutNext6SecMenuSelected();
		break;
	case ID_FADEOUTNEXT7SEC:
		OnFadeoutNext7SecMenuSelected();
		break;
	case ID_FADEOUTNEXT8SEC:
		OnFadeoutNext8SecMenuSelected();
		break;
	case ID_FADEOUTNEXT9SEC:
		OnFadeoutNext9SecMenuSelected();
		break;
	case ID_FADEOUTNEXT10SEC:
		OnFadeoutNext10SecMenuSelected();
		break;
	case ID_TWEET:
		OnTweetMenuSelected();
		break;
	case ID_METRONOME:
		OnMetronomeMenuSelected();
		break;
	case ID_QUALITY_NORMAL:
		OnQualityNormalMenuSelected();
		break;
	case ID_QUALITY_ASIO:
		OnQualityASIOMenuSelected();
		break;
	case ID_QUALITY_WASAPI:
		OnQualityWASAPIMenuSelected();
		break;
	case ID_REVERB_DEFAULT:
		OnReverbDefaultMenuSelected();
		break;
	case ID_REVERB_CUSTOMIZE:
		OnReverbCustomizeMenuSelected();
		break;
	case ID_3DREVERB_DEFAULT:
		On3DReverbDefaultMenuSelected();
		break;
	case ID_3DREVERB_PADDEDCELL:
		On3DReverbPaddedCellMenuSelected();
		break;
	case ID_3DREVERB_ROOM:
		On3DReverbRoomMenuSelected();
		break;
	case ID_3DREVERB_BATHROOM:
		On3DReverbBathroomMenuSelected();
		break;
	case ID_3DREVERB_LIVINGROOM:
		On3DReverbLivingRoomMenuSelected();
		break;
	case ID_3DREVERB_STONEROOM:
		On3DReverbStoneRoomMenuSelected();
		break;
	case ID_3DREVERB_AUDITORIUM:
		On3DReverbAuditoriumMenuSelected();
		break;
	case ID_3DREVERB_CONCERTHALL:
		On3DReverbConcertHallMenuSelected();
		break;
	case ID_3DREVERB_CAVE:
		On3DReverbCaveMenuSelected();
		break;
	case ID_3DREVERB_ARENA:
		On3DReverbArenaMenuSelected();
		break;
	case ID_3DREVERB_HANGAR:
		On3DReverbHangarMenuSelected();
		break;
	case ID_3DREVERB_CARPETEDHALLWAY:
		On3DReverbCarpetedHallwayMenuSelected();
		break;
	case ID_3DREVERB_HALLWAY:
		On3DReverbHallwayMenuSelected();
		break;
	case ID_3DREVERB_STONECORRIDOR:
		On3DReverbStoneCorridorMenuSelected();
		break;
	case ID_3DREVERB_ALLEY:
		On3DReverbAlleyMenuSelected();
		break;
	case ID_3DREVERB_FOREST:
		On3DReverbForestMenuSelected();
		break;
	case ID_3DREVERB_CITY:
		On3DReverbCityMenuSelected();
		break;
	case ID_3DREVERB_MOUNTAINS:
		On3DReverbMountainsMenuSelected();
		break;
	case ID_3DREVERB_QUARRY:
		On3DReverbQuarryMenuSelected();
		break;
	case ID_3DREVERB_PLAIN:
		On3DReverbPlainMenuSelected();
		break;
	case ID_3DREVERB_PARKINGLOT:
		On3DReverbParkingLotMenuSelected();
		break;
	case ID_3DREVERB_SEWERPIPE:
		On3DReverbSewerPipeMenuSelected();
		break;
	case ID_3DREVERB_UNDERWATER:
		On3DReverbUnderwaterMenuSelected();
		break;
	case ID_3DREVERB_SMALLROOM:
		On3DReverbSmallRoomMenuSelected();
		break;
	case ID_3DREVERB_MEDIUMROOM:
		On3DReverbMediumRoomMenuSelected();
		break;
	case ID_3DREVERB_LARGEROOM:
		On3DReverbLargeRoomMenuSelected();
		break;
	case ID_3DREVERB_MEDIUMHALL:
		On3DReverbMediumHallMenuSelected();
		break;
	case ID_3DREVERB_LARGEHALL:
		On3DReverbLargeHallMenuSelected();
		break;
	case ID_3DREVERB_PLATE:
		On3DReverbPlateMenuSelected();
		break;
	case ID_3DREVERB_CUSTOMIZE:
		On3DReverbCustomizeMenuSelected();
		break;
	case ID_DELAY_DEFAULT:
		OnDelayDefaultMenuSelected();
		break;
	case ID_DELAY_SHORT:
		OnDelayShortMenuSelected();
		break;
	case ID_DELAY_MEDIUM:
		OnDelayMediumMenuSelected();
		break;
	case ID_DELAY_LONG:
		OnDelayLongMenuSelected();
		break;
	case ID_DELAY_STEREOSHORT:
		OnDelayStereoShortMenuSelected();
		break;
	case ID_DELAY_STEREOMEDIUM:
		OnDelayStereoMediumMenuSelected();
		break;
	case ID_DELAY_STEREOLONG:
		OnDelayStereoLongMenuSelected();
		break;
	case ID_DELAY_MOUNTAIN:
		OnDelayMountainMenuSelected();
		break;
	case ID_DELAY_BIG:
		OnDelayBigMenuSelected();
		break;
	case ID_DELAY_STEREOBIG:
		OnDelayStereoBigMenuSelected();
		break;
	case ID_DELAY_DOUBLING:
		OnDelayDoublingMenuSelected();
		break;
	case ID_DELAY_DOUBLEKICK:
		OnDelayDoubleKickMenuSelected();
		break;
	case ID_DELAY_CUSTOMIZE:
		OnDelayCustomizeMenuSelected();
		break;
	case ID_CHORUS_DEFAULT:
		OnChorusDefaultMenuSelected();
		break;
	case ID_CHORUS_CUSTOMIZE:
		OnChorusCustomizeMenuSelected();
		break;
	case ID_COMPRESSOR_DEFAULT:
		OnCompressorDefaultMenuSelected();
		break;
	case ID_COMPRESSOR_CUSTOMIZE:
		OnCompressorCustomizeMenuSelected();
		break;
	case ID_FLANGER_DEFAULT:
		OnFlangerDefaultMenuSelected();
		break;
	case ID_FLANGER_CUSTOMIZE:
		OnFlangerCustomizeMenuSelected();
		break;
	case ID_GARGLE_DEFAULT:
		OnGargleDefaultMenuSelected();
		break;
	case ID_GARGLE_CUSTOMIZE:
		OnGargleCustomizeMenuSelected();
		break;
	case ID_DISTORTION_DEFAULT:
		OnDistortionDefaultMenuSelected();
		break;
	case ID_DISTORTION_CUSTOMIZE:
		OnDistortionCustomizeMenuSelected();
		break;
	case ID_EQFLAT:
		OnEQFlatMenuSelected();
		break;
	case ID_EQLOWSUPER:
		OnEQLowSuperMenuSelected();
		break;
	case ID_EQLOWHIGHEST:
		OnEQLowHighestMenuSelected();
		break;
	case ID_EQLOWHIGH:
		OnEQLowHighMenuSelected();
		break;
	case ID_EQLOWMIDDLE:
		OnEQLowMiddleMenuSelected();
		break;
	case ID_EQLOWLOW:
		OnEQLowLowMenuSelected();
		break;
	case ID_EQLOWLOWEST:
		OnEQLowLowestMenuSelected();
		break;
	case ID_EQMIDDLESUPER:
		OnEQMiddleSuperMenuSelected();
		break;
	case ID_EQMIDDLEHIGHEST:
		OnEQMiddleHighestMenuSelected();
		break;
	case ID_EQMIDDLEHIGH:
		OnEQMiddleHighMenuSelected();
		break;
	case ID_EQMIDDLEMIDDLE:
		OnEQMiddleMiddleMenuSelected();
		break;
	case ID_EQMIDDLELOW:
		OnEQMiddleLowMenuSelected();
		break;
	case ID_EQMIDDLELOWEST:
		OnEQMiddleLowestMenuSelected();
		break;
	case ID_EQHIGHSUPER:
		OnEQHighSuperMenuSelected();
		break;
	case ID_EQHIGHHIGHEST:
		OnEQHighHighestMenuSelected();
		break;
	case ID_EQHIGHHIGH:
		OnEQHighHighMenuSelected();
		break;
	case ID_EQHIGHMIDDLE:
		OnEQHighMiddleMenuSelected();
		break;
	case ID_EQHIGHLOW:
		OnEQHighLowMenuSelected();
		break;
	case ID_EQHIGHLOWEST:
		OnEQHighLowestMenuSelected();
		break;
	case ID_EQLOWCUTSUPER:
		OnEQLowCutSuperMenuSelected();
		break;
	case ID_EQLOWCUTHIGHEST:
		OnEQLowCutHighestMenuSelected();
		break;
	case ID_EQLOWCUTHIGH:
		OnEQLowCutHighMenuSelected();
		break;
	case ID_EQLOWCUTMIDDLE:
		OnEQLowCutMiddleMenuSelected();
		break;
	case ID_EQLOWCUTLOW:
		OnEQLowCutLowMenuSelected();
		break;
	case ID_EQLOWCUTLOWEST:
		OnEQLowCutLowestMenuSelected();
		break;
	case ID_EQMIDDLECUTSUPER:
		OnEQMiddleCutSuperMenuSelected();
		break;
	case ID_EQMIDDLECUTHIGHEST:
		OnEQMiddleCutHighestMenuSelected();
		break;
	case ID_EQMIDDLECUTHIGH:
		OnEQMiddleCutHighMenuSelected();
		break;
	case ID_EQMIDDLECUTMIDDLE:
		OnEQMiddleCutMiddleMenuSelected();
		break;
	case ID_EQMIDDLECUTLOW:
		OnEQMiddleCutLowMenuSelected();
		break;
	case ID_EQMIDDLECUTLOWEST:
		OnEQMiddleCutLowestMenuSelected();
		break;
	case ID_EQHIGHCUTSUPER:
		OnEQHighCutSuperMenuSelected();
		break;
	case ID_EQHIGHCUTHIGHEST:
		OnEQHighCutHighestMenuSelected();
		break;
	case ID_EQHIGHCUTHIGH:
		OnEQHighCutHighMenuSelected();
		break;
	case ID_EQHIGHCUTMIDDLE:
		OnEQHighCutMiddleMenuSelected();
		break;
	case ID_EQHIGHCUTLOW:
		OnEQHighCutLowMenuSelected();
		break;
	case ID_EQHIGHCUTLOWEST:
		OnEQHighCutLowestMenuSelected();
		break;
	case ID_DOUBLERUN:
		OnDoubleRunMenuSelected();
		break;
	case ID_TOPMOST:
		OnTopMostMenuSelected();
		break;
	case ID_TASKTRAY:
		OnTaskTrayMenuSelected();
		break;
	case ID_COPYTIME:
		OnCopyTimeMenuSelected();
		break;
	case ID_MANUAL:
		OnManualMenuSelected();
		break;
	case ID_UPDATECHECK:
		OnUpdateCheckMenuSelected();
		break;
	case ID_VERSIONINFO:
		OnVersionInfoMenuSelected();
		break;
	case ID_RESTORE:
		OnRestoreMenuSelected();
		break;
	}
	if(id > ID_PRESET) OnPresetMenuSelected(id);
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
// ファイル → LAMEコマンドラインオプションメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLAMECommandLineMenuSelected()
{
	m_rMainWnd.ShowLAMECommandLineWnd();
}
//----------------------------------------------------------------------------
// ファイル → 終了メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnExitMenuSelected()
{
	m_rMainWnd.Close();
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
// 表示 → ビデオ画面メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVideoScreenMenuSelected()
{
	m_rMainWnd.SetVideoScreenVisible();
	m_rMainWnd.StartLyrics();
	m_rMainWnd.StartPitchAnalyser();
}
//----------------------------------------------------------------------------
// 表示 → 歌詞メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLyricsMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_LYRICS);
	CheckItem(ID_LYRICS, bChecked ? MF_CHECKED : MF_UNCHECKED);
	CheckItem(ID_PITCHANALYSER, MF_UNCHECKED);
	m_rMainWnd.StartLyrics();
	m_rMainWnd.StartPitchAnalyser();
}
//----------------------------------------------------------------------------
// 表示 → ピッチアナライザメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPitchAnalyserMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_PITCHANALYSER);
	CheckItem(ID_PITCHANALYSER, bChecked ? MF_CHECKED : MF_UNCHECKED);
	CheckItem(ID_LYRICS, MF_UNCHECKED);
	m_rMainWnd.StartLyrics();
	m_rMainWnd.StartPitchAnalyser();
}
//----------------------------------------------------------------------------
// 表示 → 再生位置スライダメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTimeSliderMenuSelected()
{
	m_rMainWnd.SetTimeSliderVisible();
}
//----------------------------------------------------------------------------
// 表示 → エクスプローラメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnExplorerMenuSelected()
{
	m_rMainWnd.SetExplorerVisible();
}
//----------------------------------------------------------------------------
// 表示 → 再生速度メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSpeedMenuSelected()
{
	m_rMainWnd.SetSpeedVisible();
}
//----------------------------------------------------------------------------
// 表示 → 再生周波数メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFreqMenuSelected()
{
	m_rMainWnd.SetFreqVisible();
}
//----------------------------------------------------------------------------
// 表示 → 音程メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPitchMenuSelected()
{
	m_rMainWnd.SetPitchVisible();
}
//----------------------------------------------------------------------------
// 表示 → 音量メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVolumeMenuSelected()
{
	m_rMainWnd.SetVolumeVisible();
}
//----------------------------------------------------------------------------
// 表示 → パンメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPanMenuSelected()
{
	m_rMainWnd.SetPanVisible();
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMenuSelected()
{
	m_rMainWnd.SetEQVisible();
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 20Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ20MenuSelected()
{
	SwitchEQVisible(ID_EQ20);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 25Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ25MenuSelected()
{
	SwitchEQVisible(ID_EQ25);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 31.5Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ31_5MenuSelected()
{
	SwitchEQVisible(ID_EQ31_5);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 40Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ40MenuSelected()
{
	SwitchEQVisible(ID_EQ40);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 50Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ50MenuSelected()
{
	SwitchEQVisible(ID_EQ50);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 63Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ63MenuSelected()
{
	SwitchEQVisible(ID_EQ63);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 80Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ80MenuSelected()
{
	SwitchEQVisible(ID_EQ80);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 100Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ100MenuSelected()
{
	SwitchEQVisible(ID_EQ100);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 125Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ125MenuSelected()
{
	SwitchEQVisible(ID_EQ125);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 160Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ160MenuSelected()
{
	SwitchEQVisible(ID_EQ160);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 200Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ200MenuSelected()
{
	SwitchEQVisible(ID_EQ200);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 250Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ250MenuSelected()
{
	SwitchEQVisible(ID_EQ250);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 315Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ315MenuSelected()
{
	SwitchEQVisible(ID_EQ315);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 400Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ400MenuSelected()
{
	SwitchEQVisible(ID_EQ400);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 500Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ500MenuSelected()
{
	SwitchEQVisible(ID_EQ500);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 630Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ630MenuSelected()
{
	SwitchEQVisible(ID_EQ630);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 800Hz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ800MenuSelected()
{
	SwitchEQVisible(ID_EQ800);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 1KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ1KMenuSelected()
{
	SwitchEQVisible(ID_EQ1K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 1.25KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ1_25KMenuSelected()
{
	SwitchEQVisible(ID_EQ1_25K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 1.6KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ1_6KMenuSelected()
{
	SwitchEQVisible(ID_EQ1_6K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 2KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ2KMenuSelected()
{
	SwitchEQVisible(ID_EQ2K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 2.5KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ2_5KMenuSelected()
{
	SwitchEQVisible(ID_EQ2_5K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 3.15KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ3_15KMenuSelected()
{
	SwitchEQVisible(ID_EQ3_15K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 4KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ4KMenuSelected()
{
	SwitchEQVisible(ID_EQ4K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 5KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ5KMenuSelected()
{
	SwitchEQVisible(ID_EQ5K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 6.3KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ6_3KMenuSelected()
{
	SwitchEQVisible(ID_EQ6_3K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 8KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ8KMenuSelected()
{
	SwitchEQVisible(ID_EQ8K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 10KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ10KMenuSelected()
{
	SwitchEQVisible(ID_EQ10K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 12.5KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ12_5KMenuSelected()
{
	SwitchEQVisible(ID_EQ12_5K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 16KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ16KMenuSelected()
{
	SwitchEQVisible(ID_EQ16K);
}
//----------------------------------------------------------------------------
// 表示 → グラフィックイコライザ → 20KHz メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ20KMenuSelected()
{
	SwitchEQVisible(ID_EQ20K);
}
//----------------------------------------------------------------------------
// 表示 → タブメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTabMenuSelected()
{
	m_rMainWnd.SetTabVisible();
}
//----------------------------------------------------------------------------
// 表示 → 再生リストメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayListMenuSelected()
{
	m_rMainWnd.SetPlayListVisible();
}
//----------------------------------------------------------------------------
// 表示 → 全てのコントロールを閉じるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCloseAllMenuSelected()
{
	if(IsItemChecked(ID_VIDEOSCREEN)) OnVideoScreenMenuSelected();
	if(IsItemChecked(ID_TIMESLIDER)) OnTimeSliderMenuSelected();
	if(IsItemChecked(ID_SPEED)) OnSpeedMenuSelected();
	if(IsItemChecked(ID_FREQ)) OnFreqMenuSelected();
	if(IsItemChecked(ID_PITCH)) OnPitchMenuSelected();
	if(IsItemChecked(ID_VOLUME)) OnVolumeMenuSelected();
	if(IsItemChecked(ID_PAN)) OnPanMenuSelected();
	if(IsItemChecked(ID_EQ)) OnEQMenuSelected();
	if(IsItemChecked(ID_PLAYLIST)) OnPlayListMenuSelected();
}
//----------------------------------------------------------------------------
// 表示 → ツールバー → サイズ（小）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnToolbarSSizeMenuSelected()
{
	m_rMainWnd.GetToolBar().SetSSize();
	m_rMainWnd.SetMinMax(520);
	m_rMainWnd.ResetAllControlPos();
	m_rMainWnd.ResetSize();
	CheckItem(ID_TOOLBAR_SIZES, MFS_CHECKED);
	CheckItem(ID_TOOLBAR_SIZEM, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEL, MFS_UNCHECKED);
}
//----------------------------------------------------------------------------
// 表示 → ツールバー → サイズ（中）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnToolbarMSizeMenuSelected()
{
	m_rMainWnd.GetToolBar().SetMSize();
	m_rMainWnd.SetMinMax(570);
	m_rMainWnd.ResetAllControlPos();
	m_rMainWnd.ResetSize();
	CheckItem(ID_TOOLBAR_SIZES, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEM, MFS_CHECKED);
	CheckItem(ID_TOOLBAR_SIZEL, MFS_UNCHECKED);
}
//----------------------------------------------------------------------------
// 表示 → ツールバー → サイズ（大）メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnToolbarLSizeMenuSelected()
{
	m_rMainWnd.GetToolBar().SetLSize();
	m_rMainWnd.SetMinMax(620);
	m_rMainWnd.ResetAllControlPos();
	m_rMainWnd.ResetSize();
	CheckItem(ID_TOOLBAR_SIZES, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEM, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEL, MFS_CHECKED);
}
//----------------------------------------------------------------------------
// 表示 → ツールバーのカスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCustomizeToolbarMenuSelected()
{
	SendMessage((HWND)m_rMainWnd.GetToolBar(), TB_CUSTOMIZE, 0, 0);
	m_rMainWnd.ShowTime();
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
void CMenu_MainWnd::OnRewindMenuSelected()
{
	if(IsItemChecked(ID_REWIND)) m_rMainWnd.StopRewind();
	else m_rMainWnd.StartRewind();
}
//----------------------------------------------------------------------------
// 再生 → 早送りメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForwardMenuSelected()
{
	if(IsItemChecked(ID_FORWARD)) m_rMainWnd.StopForward();
	else m_rMainWnd.StartForward();
}
//----------------------------------------------------------------------------
// 一時停止後1秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn1SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(1);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 一時停止後2秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn2SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(2);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 一時停止後3秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn3SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(3);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 一時停止後5秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn5SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(5);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// 一時停止後10秒戻るメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn10SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(10);
	m_rMainWnd.Pause();
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
	if(IsItemChecked(id)) {
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
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(50.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(50 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(50.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 60%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed60MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(60.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(60 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(60.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 70%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed70MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(70.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(70 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(70.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 80%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed80MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(80.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(80 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(80.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 90%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed90MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(90.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(90 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(90.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 100%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed100MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(100.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(100 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(100.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 110%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed110MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(110.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(110 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(110.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 120%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed120MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(120.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(120 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(120.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 130%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed130MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(130.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(130 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(130.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 140%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed140MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(140.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(140 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(140.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 150%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed150MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(150.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(150 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(150.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 160%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed160MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(160.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(160 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(160.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 170%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed170MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(170.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(170 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(170.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 180%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed180MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(180.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(180 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(180.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 190%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed190MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(190.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(190 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(190.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 200%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed200MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(200.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(200 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(200.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 250%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed250MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(250.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(250 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(250.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 300%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed300MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(300.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(300 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(300.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 350%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed350MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(350.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(350 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(350.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 400%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed400MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(400.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(400 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(400.0);
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
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(50.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(50 * dCalc), TRUE);
	m_rMainWnd.SetFreq(50.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 60%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq60MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(60.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(60 * dCalc), TRUE);
	m_rMainWnd.SetFreq(60.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 70%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq70MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(70.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(70 * dCalc), TRUE);
	m_rMainWnd.SetFreq(70.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 80%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq80MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(80.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(80 * dCalc), TRUE);
	m_rMainWnd.SetFreq(80.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 90%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq90MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(90.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(90 * dCalc), TRUE);
	m_rMainWnd.SetFreq(90.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 100%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq100MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(100.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(100 * dCalc), TRUE);
	m_rMainWnd.SetFreq(100.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 110%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq110MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(110.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(110 * dCalc), TRUE);
	m_rMainWnd.SetFreq(110.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 120%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq120MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(120.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(120 * dCalc), TRUE);
	m_rMainWnd.SetFreq(120.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 130%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq130MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(130.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(130 * dCalc), TRUE);
	m_rMainWnd.SetFreq(130.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 140%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq140MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(140.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(140 * dCalc), TRUE);
	m_rMainWnd.SetFreq(140.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 150%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq150MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(150.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(150 * dCalc), TRUE);
	m_rMainWnd.SetFreq(150.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 160%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq160MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(160.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(160 * dCalc), TRUE);
	m_rMainWnd.SetFreq(160.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 170%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq170MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(170.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(170 * dCalc), TRUE);
	m_rMainWnd.SetFreq(170.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 180%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq180MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(180.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(180 * dCalc), TRUE);
	m_rMainWnd.SetFreq(180.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 190%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq190MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(190.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(190 * dCalc), TRUE);
	m_rMainWnd.SetFreq(190.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 200%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq200MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(200.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(200 * dCalc), TRUE);
	m_rMainWnd.SetFreq(200.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 250%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq250MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(250.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(250 * dCalc), TRUE);
	m_rMainWnd.SetFreq(250.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 300%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq300MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(300.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(300 * dCalc), TRUE);
	m_rMainWnd.SetFreq(300.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 350%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq350MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(350.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(350 * dCalc), TRUE);
	m_rMainWnd.SetFreq(350.0);
}
//----------------------------------------------------------------------------
// 再生 → 再生速度 → 設定 → 400%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq400MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(400.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(400 * dCalc), TRUE);
	m_rMainWnd.SetFreq(400.0);
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
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-12.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-12 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-12.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭11メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat11MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-11.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-11 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-11.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭10メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat10MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-10.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-10 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-10.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭9メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat9MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-9.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-9 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-9.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭8メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat8MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-8.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-8 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-8.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭7メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat7MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-7.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-7 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-7.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭6メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat6MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-6.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-6 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-6.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭5メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat5MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-5.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-5 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-5.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭4メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat4MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-4.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-4 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-4.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭3メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat3MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-3.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-3 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-3.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭2メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat2MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-2.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-2 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-2.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♭1メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat1MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-1.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-1 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-1.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → 0メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchNaturalMenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(0.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(0 * dCalc), TRUE);
	m_rMainWnd.SetPitch(0.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯1メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp1MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(1.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(1 * dCalc), TRUE);
	m_rMainWnd.SetPitch(1.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯2メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp2MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(2.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(2 * dCalc), TRUE);
	m_rMainWnd.SetPitch(2.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯3メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp3MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(3.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(3 * dCalc), TRUE);
	m_rMainWnd.SetPitch(3.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯4メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp4MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(4.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(4 * dCalc), TRUE);
	m_rMainWnd.SetPitch(4.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯5メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp5MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(5.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(5 * dCalc), TRUE);
	m_rMainWnd.SetPitch(5.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯6メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp6MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(6.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(6 * dCalc), TRUE);
	m_rMainWnd.SetPitch(6.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯7メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp7MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(7.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(7 * dCalc), TRUE);
	m_rMainWnd.SetPitch(7.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯8メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp8MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(8.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(8 * dCalc), TRUE);
	m_rMainWnd.SetPitch(8.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯9メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp9MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(9.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(9 * dCalc), TRUE);
	m_rMainWnd.SetPitch(9.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯10メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp10MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(10.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(10 * dCalc), TRUE);
	m_rMainWnd.SetPitch(10.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯11メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp11MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(11.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(11 * dCalc), TRUE);
	m_rMainWnd.SetPitch(11.0);
}
//----------------------------------------------------------------------------
// 再生 → 音程 → 音程指定 → ♯12メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp12MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(12.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(12 * dCalc), TRUE);
	m_rMainWnd.SetPitch(12.0);
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
// 音量を1%上げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUpVolumeMenuSelected()
{
	m_rMainWnd.UpVolume(1);
}
//----------------------------------------------------------------------------
// 音量を1%下げるメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDownVolumeMenuSelected()
{
	m_rMainWnd.DownVolume(1);
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
void CMenu_MainWnd::OnAllLoopMenuSelected()
{
	m_rMainWnd.SetAllLoop();
}
//----------------------------------------------------------------------------
// 再生 → ランダム再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRandomMenuSelected()
{
	m_rMainWnd.SetRandom();
}
//----------------------------------------------------------------------------
// 再生 → 連続再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnContinueMenuSelected()
{
	m_rMainWnd.SetContinue();
}
//----------------------------------------------------------------------------
// 再生 → 同じアーティストの曲を再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSameArtistMenuSelected()
{
	SwitchItemChecked(ID_SAMEARTIST);
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
	BOOL bRecordNoise = !IsItemChecked(ID_RECORDNOISE);
	m_rMainWnd.SetRecordNoise(bRecordNoise);
}
//----------------------------------------------------------------------------
// 再生 → 波音メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnWaveMenuSelected()
{
	BOOL bWave = !IsItemChecked(ID_WAVE);
	m_rMainWnd.SetWave(bWave);
}
//----------------------------------------------------------------------------
// 再生 → ノーマライズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNormalizeMenuSelected()
{
	m_rMainWnd.SetNormalize();
}
//----------------------------------------------------------------------------
// 再生 → ボーカルキャンセルメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVocalCancelMenuSelected()
{
	m_rMainWnd.SetVocalCancel();
}
//----------------------------------------------------------------------------
// 再生 → 逆回転再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverseMenuSelected()
{
	m_rMainWnd.SetReverse();
}
//----------------------------------------------------------------------------
// 再生 → 古びたレコード再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRecordMenuSelected()
{
	m_rMainWnd.SetRecord();
}
//----------------------------------------------------------------------------
// 再生 → エフェクト → 電池切れメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLowBatteryMenuSelected()
{
	m_rMainWnd.SetLowBattery();
}
//----------------------------------------------------------------------------
// 再生 → エフェクト → 歌へたモードメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNoSenseMenuSelected()
{
	m_rMainWnd.SetNoSense();
}
//----------------------------------------------------------------------------
// エフェクト → ベースの耳コピメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnBassCopyMenuSelected()
{
	if(IsItemChecked(ID_NOSENSE)) m_rMainWnd.SetNoSense();
	BOOL bChecked = !IsItemChecked(ID_BASSCOPY);
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
void CMenu_MainWnd::OnEarTrainingMenuSelected()
{
	m_rMainWnd.SetEarTraining();
}
//----------------------------------------------------------------------------
// 再生 → モノラルメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMonoralMenuSelected()
{
	m_rMainWnd.SetMonoral();
}
//----------------------------------------------------------------------------
// 再生 → 左のみ再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOnlyLeftMenuSelected()
{
	m_rMainWnd.SetOnlyLeft();
}
//----------------------------------------------------------------------------
// 再生 → 右のみ再生メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOnlyRightMenuSelected()
{
	m_rMainWnd.SetOnlyRight();
}
//----------------------------------------------------------------------------
// 再生 → 左右入れ替えメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChangeLRMenuSelected()
{
	m_rMainWnd.SetChangeLR();
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
// システム → ショートカットキー設定メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnKeySettingMenuSelected()
{
	m_rMainWnd.SetKeySetting();
}
//----------------------------------------------------------------------------
// システム → グローバルホットキー設定メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOutKeySettingMenuSelected()
{
	m_rMainWnd.SetOutKeySetting();
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
	CheckItem(ID_PITCHDEC_1, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(0);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// システム → 音程 → 小数点桁数 → 1桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal1MenuSelected()
{
	CheckItem(ID_PITCHDEC_0, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_1, MF_CHECKED);
	CheckItem(ID_PITCHDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(1);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// システム → 音程 → 小数点桁数 → 2桁メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal2MenuSelected()
{
	CheckItem(ID_PITCHDEC_0, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_1, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_2, MF_CHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(2);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(2);
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
	m_rMainWnd.GetVolumeSlider().SetThumbPos(0, TRUE);
	m_rMainWnd.SetVolume(0.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 10%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume10MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(10.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(100, TRUE);
	m_rMainWnd.SetVolume(10.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 20%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume20MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(20.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(200, TRUE);
	m_rMainWnd.SetVolume(20.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 30%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume30MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(30.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(300, TRUE);
	m_rMainWnd.SetVolume(30.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 40%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume40MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(40.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(400, TRUE);
	m_rMainWnd.SetVolume(40.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 50%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume50MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(50.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(500, TRUE);
	m_rMainWnd.SetVolume(50.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 60%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume60MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(60.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(600, TRUE);
	m_rMainWnd.SetVolume(60.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 70%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume70MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(70.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(700, TRUE);
	m_rMainWnd.SetVolume(70.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 80%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume80MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(80.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(800, TRUE);
	m_rMainWnd.SetVolume(80.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 90%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume90MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(90.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(900, TRUE);
	m_rMainWnd.SetVolume(90.0);
}
//----------------------------------------------------------------------------
// エフェクト → 音量 → 100%メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume100MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(100.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(1000, TRUE);
	m_rMainWnd.SetVolume(100.0);
}
//----------------------------------------------------------------------------
// システム → 再生停止時にフェードアウトメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutMenuSelected()
{
	BOOL bCheck = !IsItemChecked(ID_FADEOUTSTOP);
	CheckItem(ID_FADEOUTSTOP, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 1秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout1SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP1SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 2秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout2SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP2SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 3秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout3SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP3SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 4秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout4SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP4SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 5秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout5SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP5SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 6秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout6SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP6SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 7秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout7SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP7SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 8秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout8SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP8SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 9秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout9SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP9SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 停止時フェードアウト時間 → 10秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout10SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP10SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 曲の切替時にフェードアウトメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNextMenuSelected()
{
	BOOL bCheck = !IsItemChecked(ID_FADEOUTNEXT);
	CheckItem(ID_FADEOUTNEXT, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 1秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext1SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT1SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 2秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext2SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT2SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 3秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext3SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT3SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 4秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext4SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT4SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 5秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext5SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT5SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 6秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext6SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT6SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 7秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext7SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT7SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 8秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext8SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT8SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 9秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext9SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT9SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → 切替時フェードアウト時間 → 10秒メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext10SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT10SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// システム → Twitterでつぶやくメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTweetMenuSelected()
{
	m_rMainWnd.Tweet();
}
//----------------------------------------------------------------------------
// システム → メトロノームメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMetronomeMenuSelected()
{
	m_rMainWnd.SetMetronome();
}
//----------------------------------------------------------------------------
// システム → 音質 → ノーマルメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnQualityNormalMenuSelected()
{
	CheckItem(ID_QUALITY_NORMAL, MFS_CHECKED);
	CheckItem(ID_QUALITY_ASIO, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_WASAPI, MFS_UNCHECKED);
	m_rMainWnd.GetSound().StopASIO();
	m_rMainWnd.GetSound().StopWASAPI();
}
//----------------------------------------------------------------------------
// システム → 音質 → ASIOメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnQualityASIOMenuSelected()
{
	CheckItem(ID_QUALITY_NORMAL, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_ASIO, MFS_CHECKED);
	CheckItem(ID_QUALITY_WASAPI, MFS_UNCHECKED);
	m_rMainWnd.GetSound().StopWASAPI();
	m_rMainWnd.GetSound().StartASIO();
}
//----------------------------------------------------------------------------
// システム → 音質 → WASAPIメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnQualityWASAPIMenuSelected()
{
	CheckItem(ID_QUALITY_NORMAL, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_ASIO, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_WASAPI, MFS_CHECKED);
	m_rMainWnd.GetSound().StopASIO();
	m_rMainWnd.GetSound().StartWASAPI();
}
//----------------------------------------------------------------------------
// システム → エフェクト → リバーブ → デフォルトメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverbDefaultMenuSelected()
{
	SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → リバーブ → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverbCustomizeMenuSelected()
{
	if(IsItemChecked(ID_REVERB_CUSTOMIZE))
		SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_CUSTOMIZE);
	else m_rMainWnd.ShowReverbCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → デフォルトメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbDefaultMenuSelected()
{
	Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Padded Cellメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPaddedCellMenuSelected()
{
	Set3DReverb(-1000, -6000, 0.0f, 0.17f, 0.10f, -1204, 0.001f, 207, 0.002f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_PADDEDCELL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbRoomMenuSelected()
{
	Set3DReverb(-1000, -454, 0.0f, 0.4f, 0.83f, -1646, 0.002f, 53, 0.003f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Bathroomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbBathroomMenuSelected()
{
	Set3DReverb(-1000, -1200, 0.0f, 1.49f, 0.54f, -370, 0.007f, 1030, 0.011f,
			  100.0f, 60.0f, 5000.0f, ID_3DREVERB_BATHROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → LivingRoomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLivingRoomMenuSelected()
{
	Set3DReverb(-1000, -6000, 0.0f, 0.50f, 0.10f, -1376, 0.003f, -1104, 0.004f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LIVINGROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → StoneRoomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbStoneRoomMenuSelected()
{
	Set3DReverb(-1000, -300, 0.0f, 2.31f, 0.64f, -711, 0.012f, 83, 0.017f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_STONEROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Auditoriumメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbAuditoriumMenuSelected()
{
	Set3DReverb(-1000, -476, 0.0f, 4.32f, 0.59f, -789, 0.020f, -289, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_AUDITORIUM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → ConcertHallメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbConcertHallMenuSelected()
{
	Set3DReverb(-1000, -500, 0.0f, 3.92f, 0.70f, -1230, 0.020f, -2, 0.029f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CONCERTHALL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Caveメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCaveMenuSelected()
{
	Set3DReverb(-1000, 0, 0.0f, 2.91f, 1.30f, -602, 0.015f, -302, 0.022f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CAVE);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Arenaメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbArenaMenuSelected()
{
	Set3DReverb(-1000, -698, 0.0f, 7.24f, 0.33f, -1166, 0.020f, 16, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ARENA);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Hangarメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbHangarMenuSelected()
{
	Set3DReverb(-1000, -1000, 0.0f,10.05f, 0.23f, -602, 0.020f, 198, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_HANGAR);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → CarpetedHallwayメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCarpetedHallwayMenuSelected()
{
	Set3DReverb(-1000, -4000, 0.0f, 0.30f, 0.10f, -1831, 0.002f, -1630, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CARPETEDHALLWAY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Hallwayメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbHallwayMenuSelected()
{
	Set3DReverb(-1000, -300, 0.0f, 1.49f, 0.59f, -1219, 0.007f, 441, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_HALLWAY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → StoneCorridorメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbStoneCorridorMenuSelected()
{
	Set3DReverb(-1000, -237, 0.0f, 2.70f, 0.79f, -1214, 0.013f, 395, 0.020f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_STONECORRIDOR);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Alleyメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbAlleyMenuSelected()
{
	Set3DReverb(-1000, -270, 0.0f, 1.49f, 0.86f, -1204, 0.007f, -4, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ALLEY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Forestメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbForestMenuSelected()
{
	Set3DReverb(-1000, -3300, 0.0f, 1.49f, 0.54f, -2560, 0.162f, -613, 0.088f,
			  79.0f, 100.0f, 5000.0f, ID_3DREVERB_FOREST);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Cityメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCityMenuSelected()
{
	Set3DReverb(-1000, -800, 0.0f, 1.49f, 0.67f, -2273, 0.007f, -2217, 0.011f,
			  50.0f, 100.0f, 5000.0f, ID_3DREVERB_CITY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Mountainsメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMountainsMenuSelected()
{
	Set3DReverb(-1000, -2500, 0.0f, 1.49f, 0.21f, -2780, 0.300f, -2014, 0.100f,
			  27.0f, 100.0f, 5000.0f, ID_3DREVERB_MOUNTAINS);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Quarryメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbQuarryMenuSelected()
{
	Set3DReverb(-1000, -1000, 0.0f, 1.49f, 0.83f,-10000, 0.061f, 500, 0.025f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_QUARRY);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Plainメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPlainMenuSelected()
{
	Set3DReverb(-1000, -2000, 0.0f, 1.49f, 0.50f, -2466, 0.179f, -2514, 0.100f,
			  21.0f, 100.0f, 5000.0f, ID_3DREVERB_PLAIN);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → ParkingLotメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbParkingLotMenuSelected()
{
	Set3DReverb(-1000, 0, 0.0f, 1.65f, 1.50f, -1363, 0.008f, -1153, 0.012f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_PARKINGLOT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → SewerPipeメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbSewerPipeMenuSelected()
{
	Set3DReverb(-1000, -1000, 0.0f, 2.81f, 0.14f, 429, 0.014f, 648, 0.021f,
			  80.0f, 60.0f, 5000.0f, ID_3DREVERB_SEWERPIPE);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Underwaterメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbUnderwaterMenuSelected()
{
	Set3DReverb(-1000, -4000, 0.0f, 1.49f, 0.10f, -449, 0.007f, 1700, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_UNDERWATER);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Small Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbSmallRoomMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.10f, 0.83f, -400, 0.005f, 500, 0.010f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_SMALLROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Medium Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMediumRoomMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.30f, 0.83f, -1000, 0.010f, -200, 0.020f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_MEDIUMROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Large Roomメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLargeRoomMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.50f, 0.83f, -1600, 0.020f, -1000, 0.040f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LARGEROOM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Medium Hallメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMediumHallMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.80f, 0.70f, -1300, 0.015f, -800, 0.030f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_MEDIUMHALL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Large Hallメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLargeHallMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.80f, 0.70f, -2000, 0.030f, -1400, 0.060f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LARGEHALL);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → Plateメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPlateMenuSelected()
{
	Set3DReverb(-1000, -200, 0.0f, 1.30f, 0.90f, 0, 0.002f, 0, 0.010f, 100.0f, 
			  75.0f, 5000.0f, ID_3DREVERB_PLATE);
}
//----------------------------------------------------------------------------
// システム → エフェクト → ３Ｄリバーブ → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCustomizeMenuSelected()
{
	if(IsItemChecked(ID_3DREVERB_CUSTOMIZE))
		Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f,
					100.0f, 100.0f, 5000.0f, ID_3DREVERB_CUSTOMIZE);
	else m_rMainWnd.Show3DReverbCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDefaultMenuSelected()
{
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Short Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayShortMenuSelected()
{
	SetDelay(15, 50, 150, 150, FALSE, ID_DELAY_SHORT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Medium Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayMediumMenuSelected()
{
	SetDelay(15, 50, 300, 300, FALSE, ID_DELAY_MEDIUM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Long Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayLongMenuSelected()
{
	SetDelay(15, 50, 600, 600, FALSE, ID_DELAY_LONG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stereo Short Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoShortMenuSelected()
{
	SetDelay(15, 50, 300, 150, TRUE, ID_DELAY_STEREOSHORT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stetreo Medium Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoMediumMenuSelected()
{
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_STEREOMEDIUM);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stereo Long Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoLongMenuSelected()
{
	SetDelay(15, 50, 1200, 600, TRUE, ID_DELAY_STEREOLONG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Mountain Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayMountainMenuSelected()
{
	SetDelay(20, 0, 1500, 1500, FALSE, ID_DELAY_MOUNTAIN);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Big Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayBigMenuSelected()
{
	SetDelay(40, 50, 300, 300, FALSE, ID_DELAY_BIG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Stereo Big Echoメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoBigMenuSelected()
{
	SetDelay(40, 50, 600, 300, TRUE, ID_DELAY_STEREOBIG);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Doublingメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDoublingMenuSelected()
{
	SetDelay(100, 0, 31, 1, TRUE, ID_DELAY_DOUBLING);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → Double Kickメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDoubleKickMenuSelected()
{
	SetDelay(50, 0, 100, 100, FALSE, ID_DELAY_DOUBLEKICK);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Delay → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayCustomizeMenuSelected()
{
	if(IsItemChecked(ID_DELAY_CUSTOMIZE))
		SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_CUSTOMIZE);
	else m_rMainWnd.ShowDelayCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Chorus → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChorusDefaultMenuSelected()
{
	SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
			  ID_CHORUS_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Chorus → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChorusCustomizeMenuSelected()
{
	if(IsItemChecked(ID_CHORUS_CUSTOMIZE))
		SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
				  ID_CHORUS_CUSTOMIZE);
	else m_rMainWnd.ShowChorusCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Compressor → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCompressorDefaultMenuSelected()
{
	SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
				  ID_COMPRESSOR_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Compressor → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCompressorCustomizeMenuSelected()
{
	if(IsItemChecked(ID_COMPRESSOR_CUSTOMIZE))
		SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
					  ID_COMPRESSOR_CUSTOMIZE);
	else m_rMainWnd.ShowCompressorCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Flanger → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFlangerDefaultMenuSelected()
{
	SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
			   ID_FLANGER_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Flanger → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFlangerCustomizeMenuSelected()
{
	if(IsItemChecked(ID_FLANGER_CUSTOMIZE))
		SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
				   ID_FLANGER_CUSTOMIZE);
	else m_rMainWnd.ShowFlangerCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Gargle → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnGargleDefaultMenuSelected()
{
	SetGargle(20, 0, ID_GARGLE_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Gargle → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnGargleCustomizeMenuSelected()
{
	if(IsItemChecked(ID_GARGLE_CUSTOMIZE))
		SetGargle(20, 0, ID_GARGLE_CUSTOMIZE);
	else m_rMainWnd.ShowGargleCustomizeWnd();
}
//----------------------------------------------------------------------------
// システム → エフェクト → Distortion → Defaultメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDistortionDefaultMenuSelected()
{
	SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
				  ID_DISTORTION_DEFAULT);
}
//----------------------------------------------------------------------------
// システム → エフェクト → Distortion → カスタマイズメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDistortionCustomizeMenuSelected()
{
	if(IsItemChecked(ID_DISTORTION_CUSTOMIZE))
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
// システム → 多重起動メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDoubleRunMenuSelected()
{
	m_rMainWnd.SetDoubleRun();
}
//----------------------------------------------------------------------------
// システム → 最前面表示メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTopMostMenuSelected()
{
	m_rMainWnd.SetTopMost();
}
//----------------------------------------------------------------------------
// システム → 最小化時タスクトレイに格納メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTaskTrayMenuSelected()
{
	BOOL bCheck = !IsItemChecked(ID_TASKTRAY);
	CheckItem(ID_TASKTRAY, bCheck ? MF_CHECKED : MF_UNCHECKED);
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
#if JP
	ShellExecute(m_rMainWnd, _T("open"),
				_T("http://soft.edolfzoku.com/hayaemon2/manual.html"), NULL,
				NULL, SW_SHOWDEFAULT);
#else // JP
	tstring manualPath = m_rApp.GetFilePath() + _T("manual\\index.html");
	ShellExecute(NULL, _T("open"), manualPath.c_str(), NULL, NULL, NULL);
#endif // JP
}
//----------------------------------------------------------------------------
// ヘルプ → アップデートの確認メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUpdateCheckMenuSelected()
{
	HINTERNET hInternet = InternetOpen(_T("VersionCheck"),
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hInternet == NULL) {
		MessageBox(m_rMainWnd, _T("インターネットに接続できません。"),
			_T("オフライン"), 0);
		CloseHandle(hInternet);
		return;
	}
	tstring strVersion = m_rApp.GetVersionInfo();
	strVersion = CUtils::Replace(strVersion, _T("."), _T(""));
	int nPos = strVersion.find(_T("β"), 0);
	tstring strFileName = _T("Hayaemon");
	if(nPos > 0) {
		int nNextVersion = _ttoi(strVersion.substr(0, nPos).c_str()) + 1;
		TCHAR chVersion[255];
		_stprintf_s(chVersion, _T("%d"), nNextVersion);
		strFileName += (tstring)chVersion + _T(".zip");
	}
	else {
		int nNextVersion = _ttoi(strVersion.substr(0, nPos).c_str()) + 2;
		TCHAR chVersion[255];
		_stprintf_s(chVersion, _T("%d"), nNextVersion);
		strFileName += (tstring)chVersion + _T(".zip");
	}
	HINTERNET hFile = InternetOpenUrl(hInternet,
		((tstring)_T("http://soft.edolfzoku.com/hayaemon2/")
			+ strFileName).c_str(), NULL, 0, 0, 0);
	TCHAR chBuf[512];
	DWORD dwLen = 512;
	HttpQueryInfo(hFile, HTTP_QUERY_CONTENT_LENGTH, chBuf, &dwLen, NULL);
	if(_ttoi(chBuf) > 2000000) {
#if JP
		int nButton = MessageBox(0,
			_T("最新版が公開されています。\n公式サイトにアクセスしますか？"),
			_T("確認"), MB_YESNO | MB_ICONQUESTION);
		if(nButton == IDYES)
			ShellExecute(m_rMainWnd, _T("open"),
				_T("http://soft.edolfzoku.com/hayaemon2/"), NULL, NULL,
				SW_SHOWDEFAULT);
#else // JP
		int nButton = MessageBox(0,
			_T("The latest version has been released.\n")
			_T("Do you want to access the official site?"),
			_T("Question"), MB_YESNO | MB_ICONQUESTION);
		if(nButton == IDYES)
			ShellExecute(m_rMainWnd, _T("open"),
				_T("http://en.edolfzoku.com/hayaemon2/"), NULL, NULL,
				SW_SHOWDEFAULT);
#endif // JP
	}
	else {
#if JP
		MessageBox(0, _T("お使いのバージョンは最新です。"), _T("情報"),
			MB_ICONINFORMATION);
#else // JP
		MessageBox(0, _T("Your version is latest."), _T("Information"),
			MB_ICONINFORMATION);
#endif // JP
	}
	CloseHandle(hInternet);
	CloseHandle(hFile);
}
//----------------------------------------------------------------------------
// ヘルプ → バージョン情報メニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVersionInfoMenuSelected()
{
	tstring str = m_rApp.GetName() + _T(" ");
	tstring strVersion = m_rApp.GetVersionInfo();
	int nPos = strVersion.find(_T("β"), 0);
	if(nPos > 0) {
		str += _T("Version ") + strVersion.substr(0, nPos);
#if JP
		str += _T(" β ");
#else // JP
		str += _T(" beta ");
#endif // JP
		str += strVersion.substr(nPos + 1);
	}
	else {
		str += _T("Version ") + strVersion +
#if JP
			   _T(" 安定版");
#else // JP
			   _T(" stable");
#endif // JP
	}
	str += _T("\n\n　") + m_rApp.GetAuthorName()
		+ _T(" <") + m_rApp.GetAuthorEMail() + _T(">\n　")
		+ m_rApp.GetAuthorWebSiteName() + _T(" : ") + m_rApp.GetAuthorURL();
	MessageBox(m_rMainWnd, str.c_str(),
#if JP
			   _T("バージョン情報"),
#else // JP
			   _T("Version"),
#endif // JP
			   0);
}
//----------------------------------------------------------------------------
// 元のサイズに戻すメニューが選択された
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRestoreMenuSelected()
{
	SendMessage(m_rMainWnd, WM_TRAY, 0L, WM_LBUTTONDOWN);
}
//----------------------------------------------------------------------------
