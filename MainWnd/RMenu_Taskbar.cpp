//----------------------------------------------------------------------------
// RMenu_Taskbar.cpp : タスクバー用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../Common/CommandList.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "RMenu_Taskbar.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CRMenu_Taskbar::Create()
{
	CMenu::CreatePopup();
#if JP
	// ファイルメニュー
	Append(GetItemFlags(ID_OPENFILE), ID_OPENFILE,
						_T("ファイルを開く(&O)..."));
	Append(GetItemFlags(ID_ADDFILE), ID_ADDFILE, _T("ファイルを追加(&P)..."));
	Append(GetItemFlags(ID_OPENFOLDER), ID_OPENFOLDER,
						_T("フォルダを開く(&F)..."));
	Append(GetItemFlags(ID_ADDFOLDER), ID_ADDFOLDER,
						_T("フォルダを追加(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_SAVEFILE), ID_SAVEFILE, _T("保存(&S)..."));
	Append(GetItemFlags(ID_SAVEALLFILE), ID_SAVEALLFILE,
						_T("一括変換(&A)..."));
	AppendSeparator();

	// 再生メニュー
	Append(GetItemFlags(ID_PAUSE), ID_PAUSE, _T("再生/一時停止(&P)"));
	Append(GetItemFlags(ID_STOP), ID_STOP, _T("停止(&S)"));
	Append(GetItemFlags(ID_HEAD), ID_HEAD, _T("頭出し(&T)"));
	Append(GetItemFlags(ID_PREV), ID_PREV, _T("前へ(&V)"));
	Append(GetItemFlags(ID_NEXT), ID_NEXT, _T("次へ(&N)"));
	Append(GetItemFlags(ID_REWIND), ID_REWIND, _T("巻き戻し(&R)"));
	Append(GetItemFlags(ID_FORWARD), ID_FORWARD, _T("早送り(&A)"));
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(GetItemFlags(ID_RETURN1SEC), ID_RETURN1SEC,
						_T("1秒戻る(&1)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN2SEC), ID_RETURN2SEC,
						_T("2秒戻る(&2)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN3SEC), ID_RETURN3SEC,
						_T("3秒戻る(&3)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN5SEC), ID_RETURN5SEC,
						_T("5秒戻る(&5)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN10SEC), ID_RETURN10SEC,
						_T("10秒戻る(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, _T("戻る(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD1SEC), ID_FORWARD1SEC,
						 _T("1秒進む(&1)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD2SEC), ID_FORWARD2SEC,
						 _T("2秒進む(&2)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD3SEC), ID_FORWARD3SEC,
						 _T("3秒進む(&3)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD5SEC), ID_FORWARD5SEC,
						 _T("5秒進む(&5)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD10SEC), ID_FORWARD10SEC,
						 _T("10秒進む(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, _T("進む(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_SLOOP), ID_SLOOP, _T("１曲ループ(&1)"));
	Append(GetItemFlags(ID_ALOOP), ID_ALOOP, _T("全曲ループ(&T)"));
	Append(GetItemFlags(ID_RANDOM), ID_RANDOM, _T("ランダム再生(&H)"));
	Append(GetItemFlags(ID_CONTINUE), ID_CONTINUE, _T("連続再生(&C)"));

	// エフェクトメニュー
	m_effectMenu.CreatePopup();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(GetItemFlags(ID_RESETSPEED), ID_RESETSPEED,
					   _T("デフォルトに戻す(&R)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DOWN0_1SPEED), ID_DOWN0_1SPEED,
					   _T("0.1%下げる(&0)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN1SPEED), ID_DOWN1SPEED,
					   _T("1%下げる(&1)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN2SPEED), ID_DOWN2SPEED,
					   _T("2%下げる(&2)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN3SPEED), ID_DOWN3SPEED,
					   _T("3%下げる(&3)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN5SPEED), ID_DOWN5SPEED,
					   _T("5%下げる(&5)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN10SPEED), ID_DOWN10SPEED,
					   _T("10%下げる(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_UP0_1SPEED), ID_UP0_1SPEED,
					   _T("0.1%上げる(&Z)"));
	m_speedMenu.Append(GetItemFlags(ID_UP1SPEED), ID_UP1SPEED,
					   _T("1%上げる(&A)"));
	m_speedMenu.Append(GetItemFlags(ID_UP2SPEED), ID_UP2SPEED,
					   _T("2%上げる(&B)"));
	m_speedMenu.Append(GetItemFlags(ID_UP3SPEED), ID_UP3SPEED,
					   _T("3%上げる(&C)"));
	m_speedMenu.Append(GetItemFlags(ID_UP5SPEED), ID_UP5SPEED,
					   _T("5%上げる(&D)"));
	m_speedMenu.Append(GetItemFlags(ID_UP10SPEED), ID_UP10SPEED,
					   _T("10%上げる(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DECSPEED), ID_DECSPEED,
					   _T("だんだん遅くする(&D)..."));
	m_speedMenu.Append(GetItemFlags(ID_INCSPEED), ID_INCSPEED,
					   _T("だんだん速くする(&D)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu,
						_T("再生速度(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(GetItemFlags(ID_RESETFREQ), ID_RESETFREQ,
					  _T("デフォルトに戻す(&R)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DOWN0_1FREQ), ID_DOWN0_1FREQ,
					  _T("0.1%下げる(&0)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN1FREQ), ID_DOWN1FREQ,
					  _T("1%下げる(&1)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN2FREQ), ID_DOWN2FREQ,
					  _T("2%下げる(&2)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN3FREQ), ID_DOWN3FREQ,
					  _T("3%下げる(&3)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN5FREQ), ID_DOWN5FREQ,
					  _T("5%下げる(&5)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN10FREQ), ID_DOWN10FREQ,
					  _T("10%下げる(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_UP0_1FREQ), ID_UP0_1FREQ,
					  _T("0.1%上げる(&Z)"));
	m_freqMenu.Append(GetItemFlags(ID_UP1FREQ), ID_UP1FREQ,
					  _T("1%上げる(&A)"));
	m_freqMenu.Append(GetItemFlags(ID_UP2FREQ), ID_UP2FREQ,
					  _T("2%上げる(&B)"));
	m_freqMenu.Append(GetItemFlags(ID_UP3FREQ), ID_UP3FREQ,
					  _T("3%上げる(&C)"));
	m_freqMenu.Append(GetItemFlags(ID_UP5FREQ), ID_UP5FREQ,
					  _T("5%上げる(&D)"));
	m_freqMenu.Append(GetItemFlags(ID_UP10FREQ), ID_UP10FREQ,
					  _T("10%上げる(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DECFREQ), ID_DECFREQ,
					  _T("だんだん遅くする(&F)..."));
	m_freqMenu.Append(GetItemFlags(ID_INCFREQ), ID_INCFREQ,
					  _T("だんだん速くする(&F)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu,
						_T("再生周波数(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(GetItemFlags(ID_RESETPITCH), ID_RESETPITCH,
					   _T("デフォルトに戻す(&R)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_DOWN1PITCH), ID_DOWN1PITCH,
					   _T("半音下げる(&1)"));
	m_pitchMenu.Append(GetItemFlags(ID_DOWN2PITCH), ID_DOWN2PITCH,
					   _T("全音下げる(&2)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_UP1PITCH), ID_UP1PITCH,
					   _T("半音上げる(&A)"));
	m_pitchMenu.Append(GetItemFlags(ID_UP2PITCH), ID_UP2PITCH,
					   _T("全音上げる(&B)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu,
						_T("音程(&P)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQFLAT), ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGHEST), ID_EQLOWHIGHEST,
						  _T("低音強調（最強）(&A)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGH), ID_EQLOWHIGH,
						  _T("低音強調（強）(&B)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWMIDDLE), ID_EQLOWMIDDLE,
						  _T("低音強調（中）(&C)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOW), ID_EQLOWLOW,
						  _T("低音強調（弱）(&D)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOWEST), ID_EQLOWLOWEST,
						  _T("低音強調（最弱）(&E)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGHEST), ID_EQMIDDLEHIGHEST,
						  _T("中音強調（最強）(&G)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGH), ID_EQMIDDLEHIGH,
						  _T("中音強調（強）(&H)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEMIDDLE), ID_EQMIDDLEMIDDLE,
						  _T("中音強調（中）(&I)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOW), ID_EQMIDDLELOW,
						  _T("中音強調（弱）(&J)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOWEST), ID_EQMIDDLELOWEST,
						  _T("中音強調（最弱）(&K)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGHEST), ID_EQHIGHHIGHEST,
						  _T("高音強調（最強）(&L)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGH), ID_EQHIGHHIGH,
						  _T("高音強調（強）(&M)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHMIDDLE), ID_EQHIGHMIDDLE,
						  _T("高音強調（中）(&N)"));

	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOW), ID_EQHIGHLOW,
						  _T("高音強調（弱）(&O)"));

	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOWEST), ID_EQHIGHLOWEST,
						  _T("高音強調（最弱）(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu,
						_T("EQプリセット(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_DEFAULT), ID_3DREVERB_DEFAULT,
						_T("デフォルト(&D)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PADDEDCELL),
						ID_3DREVERB_PADDEDCELL,
						_T("クッション張りの安全室(&P)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ROOM), ID_3DREVERB_ROOM,
						_T("部屋(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_BATHROOM), ID_3DREVERB_BATHROOM,
						_T("浴室(&B)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LIVINGROOM),
						ID_3DREVERB_LIVINGROOM, _T("リビング(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONEROOM), ID_3DREVERB_STONEROOM,
						_T("石室(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_AUDITORIUM),
						ID_3DREVERB_AUDITORIUM, _T("講堂(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CONCERTHALL),
						ID_3DREVERB_CONCERTHALL, _T("コンサートホール(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CAVE), ID_3DREVERB_CAVE,
						_T("洞窟(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ARENA), ID_3DREVERB_ARENA,
						_T("アリーナ(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HANGAR), ID_3DREVERB_HANGAR,
						_T("納屋(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CARPETEDHALLWAY),
						ID_3DREVERB_CARPETEDHALLWAY,
						_T("カーペットを敷いた廊下(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HALLWAY), ID_3DREVERB_HALLWAY,
						_T("廊下(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONECORRIDOR),
						ID_3DREVERB_STONECORRIDOR, _T("石の廊下(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ALLEY), ID_3DREVERB_ALLEY,
						_T("裏通り(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_FOREST), ID_3DREVERB_FOREST,
						_T("森林(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CITY), ID_3DREVERB_CITY,
						_T("都市(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MOUNTAINS), ID_3DREVERB_MOUNTAINS,
						_T("山(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_QUARRY), ID_3DREVERB_QUARRY,
						_T("採石場(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLAIN), ID_3DREVERB_PLAIN,
						_T("平野(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PARKINGLOT),
						ID_3DREVERB_PARKINGLOT, _T("駐車場(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SEWERPIPE), ID_3DREVERB_SEWERPIPE,
						_T("下水管(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_UNDERWATER),
						ID_3DREVERB_UNDERWATER, _T("水中(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SMALLROOM), ID_3DREVERB_SMALLROOM,
						_T("小部屋(&S)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMROOM),
						ID_3DREVERB_MEDIUMROOM, _T("中部屋(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEROOM), ID_3DREVERB_LARGEROOM,
						_T("大部屋(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMHALL),
						ID_3DREVERB_MEDIUMHALL, _T("中ホール(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEHALL), ID_3DREVERB_LARGEHALL,
						_T("大ホール(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLATE), ID_3DREVERB_PLATE,
						_T("プレート(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu,
						_T("３Ｄリバーブ(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DEFAULT), ID_DELAY_DEFAULT,
					   _T("デフォルト(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_SHORT), ID_DELAY_SHORT,
					   _T("短いエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MEDIUM), ID_DELAY_MEDIUM,
					   _T("中ぐらいのエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_LONG), ID_DELAY_LONG,
					   _T("長いエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOSHORT),
					   ID_DELAY_STEREOSHORT, _T("ステレオの短いエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOMEDIUM),
					   ID_DELAY_STEREOMEDIUM,
					   _T("ステレオの中ぐらいのエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOLONG), ID_DELAY_STEREOLONG,
					   _T("ステレオの長いエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MOUNTAIN), ID_DELAY_MOUNTAIN,
					   _T("山びこ(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_BIG), ID_DELAY_BIG,
					   _T("大きいエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOBIG), ID_DELAY_STEREOBIG,
					   _T("ステレオの大きいエコー(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLING), ID_DELAY_DOUBLING,
					   _T("ダブリング(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLEKICK), ID_DELAY_DOUBLEKICK,
					   _T("ダブルキック(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu,
						_T("ディレイ(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(GetItemFlags(ID_CHORUS_DEFAULT), ID_CHORUS_DEFAULT,
						_T("デフォルト(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("コーラス(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(GetItemFlags(ID_COMPRESSOR_DEFAULT),
							ID_COMPRESSOR_DEFAULT, _T("デフォルト(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("コンプレッサー(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(GetItemFlags(ID_FLANGER_DEFAULT), ID_FLANGER_DEFAULT,
						 _T("デフォルト(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("フランジャー(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(GetItemFlags(ID_GARGLE_DEFAULT), ID_GARGLE_DEFAULT,
						_T("デフォルト(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("ガーグル(&G)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(GetItemFlags(ID_DISTORTION_DEFAULT),
							ID_DISTORTION_DEFAULT, _T("デフォルト(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("ディストーション(&D)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_NORMALIZE), ID_NORMALIZE,
						_T("ノーマライズ(&N)"));
	m_effectMenu.Append(GetItemFlags(ID_VOCALCANCEL), ID_VOCALCANCEL,
						_T("ボーカルキャンセル(&V)"));
	m_effectMenu.Append(GetItemFlags(ID_REVERSE), ID_REVERSE,
						_T("逆回転再生(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_RECORD), ID_RECORD,
						_T("古びたレコード再生(&F)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_MONORAL), ID_MONORAL,
						_T("モノラル(&M)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYLEFT), ID_ONLYLEFT,
						_T("左のみ再生(&L)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYRIGHT), ID_ONLYRIGHT,
						_T("右のみ再生(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_CHANGELR), ID_CHANGELR,
						_T("左右入れ替え(&C)"));
	Append(MF_POPUP | MF_MENUBARBREAK, (UINT_PTR)(HMENU)m_effectMenu,
		   _T("エフェクト(&E)"));
	AppendSeparator();

	// システムメニュー
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVIDEOSCREENVISIBLE),
								ID_RECOVERVIDEOSCREENVISIBLE,
								_T("ビデオ画面(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERTIMESLIDERVISIBLE),
								ID_RECOVERTIMESLIDERVISIBLE,
								_T("再生位置スライダ(&T)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERSPEEDVISIBLE),
								ID_RECOVERSPEEDVISIBLE,
								_T("再生速度(&S)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERFREQVISIBLE),
								ID_RECOVERFREQVISIBLE,
								_T("再生周波数(&F)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPITCHVISIBLE),
								ID_RECOVERPITCHVISIBLE,
								_T("音程(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVOLUMEVISIBLE),
								ID_RECOVERVOLUMEVISIBLE,
								_T("音量(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPANVISIBLE),
								ID_RECOVERPANVISIBLE,
								_T("パン(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVEREQVISIBLE),
								ID_RECOVEREQVISIBLE,
								_T("グラフィックイコライザ(&G)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERLISTVISIBLE),
								ID_RECOVERLISTVISIBLE, _T("再生リスト(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu,
						  _T("表示状態(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSLOOP),
								 ID_RECOVERSLOOP, _T("１曲ループ(&1)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERALOOP),
								 ID_RECOVERALOOP, _T("全曲ループ(&T)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRANDOM),
								 ID_RECOVERRANDOM, _T("ランダム再生(&H)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERCONTINUE),
								 ID_RECOVERCONTINUE, _T("連続再生(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERINSTANTLOOP),
								 ID_RECOVERINSTANTLOOP,
								 _T("マーカー追加時にループ(&I)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSETPOSITIONAUTO),
								 ID_RECOVERSETPOSITIONAUTO,
								 _T("マーカー位置変更時に再生位置変更(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERREVERSE),
								 ID_RECOVERREVERSE, _T("逆回転再生(&R)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRECORD),
								 ID_RECOVERRECORD,
								 _T("古びたレコード再生(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu,
						  _T("再生モード(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWPOS), ID_RECOVERWPOS,
						  _T("ウィンドウ位置(&P)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWSIZE), ID_RECOVERWSIZE,
						  _T("ウィンドウサイズ(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERSPEED), ID_RECOVERSPEED,
						  _T("再生速度(&S)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERFREQ),
						  ID_RECOVERFREQ, _T("再生周波数(&F)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPITCH), ID_RECOVERPITCH,
						  _T("音程(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERVOLUME), ID_RECOVERVOLUME,
						  _T("音量(&V)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPAN), ID_RECOVERPAN,
						  _T("パン(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVEREQ), ID_RECOVEREQ,
						  _T("グラフィックイコライザ(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERLIST), ID_RECOVERLIST,
						  _T("再生リスト(&P)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, _T("復元(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_KEYSETTING), ID_KEYSETTING,
		   _T("ショートカットキー設定(&K)..."));
	Append(GetItemFlags(ID_OUTKEYSETTING), ID_OUTKEYSETTING,
		   _T("グローバルホットキー設定(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_TIMERPLAY), ID_TIMERPLAY,
		   _T("タイマー設定(&T)..."));
	Append(GetItemFlags(ID_PLAYPOSITION), ID_PLAYPOSITION,
		   _T("再生位置(&P)..."));
	Append(GetItemFlags(ID_FADEOUTSTOP), ID_FADEOUTSTOP,
		   _T("再生停止時にフェードアウト(&F)"));
	Append(GetItemFlags(ID_FADEOUTNEXT), ID_FADEOUTNEXT,
		   _T("曲の切替時にフェードアウト(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_METRONOME), ID_METRONOME,
		   _T("メトロノーム機能(&M)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_DOUBLERUN), ID_DOUBLERUN, _T("多重起動(&D)"));
	Append(GetItemFlags(ID_TOPMOST), ID_TOPMOST, _T("最前面表示(&S)"));
	Append(GetItemFlags(ID_COPYTIME), ID_COPYTIME,
		   _T("現在の再生位置をコピー(&C)"));
	AppendSeparator();

	// ヘルプメニュー
	Append(GetItemFlags(ID_MANUAL), ID_MANUAL, _T("マニュアル(&M)..."));
	Append(GetItemFlags(ID_VERSIONINFO), ID_VERSIONINFO,
		   _T("バージョン情報(&A)..."));

	AppendSeparator();
	Append(MFS_ENABLED, ID_RESTORE, _T("元のサイズに戻す(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_EXIT), ID_EXIT, _T("終了(&X)"));
#else // JP
	// ファイルメニュー
	Append(GetItemFlags(ID_OPENFILE), ID_OPENFILE, _T("Open files(&O)..."));
	Append(GetItemFlags(ID_ADDFILE), ID_ADDFILE, _T("Add files(&P)..."));
	Append(GetItemFlags(ID_OPENFOLDER), ID_OPENFOLDER,
		   _T("Open directory(&F)..."));
	Append(GetItemFlags(ID_ADDFOLDER), ID_ADDFOLDER,
		   _T("Add directory(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_SAVEFILE), ID_SAVEFILE, _T("Save(&S)..."));
	Append(GetItemFlags(ID_SAVEALLFILE), ID_SAVEALLFILE,
		   _T("Save all(&A)..."));
	AppendSeparator();

	// 再生メニュー
	Append(GetItemFlags(ID_PAUSE), ID_PAUSE, _T("Play/Pause(&P)"));
	Append(GetItemFlags(ID_STOP), ID_STOP, _T("Stop(&S)"));
	Append(GetItemFlags(ID_HEAD), ID_HEAD, _T("Head(&T)"));
	Append(GetItemFlags(ID_PREV), ID_PREV, _T("Previous(&V)"));
	Append(GetItemFlags(ID_NEXT), ID_NEXT, _T("Next(&N)"));
	Append(GetItemFlags(ID_REWIND), ID_REWIND, _T("Rewind(&R)"));
	Append(GetItemFlags(ID_FORWARD), ID_FORWARD, _T("Forward(&A)"));
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(GetItemFlags(ID_RETURN1SEC), ID_RETURN1SEC,
						_T("Rewind 1 sec.(&1)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN2SEC), ID_RETURN2SEC,
						_T("Rewind 2 sec.(&2)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN3SEC), ID_RETURN3SEC,
						_T("Rewind 3 sec.(&3)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN5SEC), ID_RETURN5SEC,
						_T("Rewind 5 sec.(&5)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN10SEC), ID_RETURN10SEC,
						_T("Rewind 10 sec.(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, _T("Rewind(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD1SEC), ID_FORWARD1SEC,
						 _T("Forward 1 sec.(&1)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD2SEC), ID_FORWARD2SEC,
						 _T("Forward 2 sec.(&2)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD3SEC), ID_FORWARD3SEC,
						 _T("Forward 3 sec.(&3)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD5SEC), ID_FORWARD5SEC,
						 _T("Forward 5 sec.(&5)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD10SEC), ID_FORWARD10SEC,
						 _T("Forward 10 sec.(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, _T("Forward(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_SLOOP), ID_SLOOP, _T("Single loop(&1)"));
	Append(GetItemFlags(ID_ALOOP), ID_ALOOP, _T("All loop(&T)"));
	Append(GetItemFlags(ID_RANDOM), ID_RANDOM, _T("Random play(&H)"));
	Append(GetItemFlags(ID_CONTINUE), ID_CONTINUE, _T("Continuous play(&C)"));

	// エフェクトメニュー
	m_effectMenu.CreatePopup();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(GetItemFlags(ID_RESETSPEED), ID_RESETSPEED,
					   _T("Reset Speed(&R)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DOWN0_1SPEED), ID_DOWN0_1SPEED,
					   _T("Turn down 0.1%(&0)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN1SPEED), ID_DOWN1SPEED,
					   _T("Turn down 1%(&1)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN2SPEED), ID_DOWN2SPEED,
					   _T("Turn down 2%(&2)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN3SPEED), ID_DOWN3SPEED,
					   _T("Turn down 3%(&3)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN5SPEED), ID_DOWN5SPEED,
					   _T("Turn down 5%(&5)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN10SPEED), ID_DOWN10SPEED,
					   _T("Turn down 10%(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_UP0_1SPEED), ID_UP0_1SPEED,
					   _T("Turn up 0.1%(&Z)"));
	m_speedMenu.Append(GetItemFlags(ID_UP1SPEED), ID_UP1SPEED,
					   _T("Turn up 1%(&A)"));
	m_speedMenu.Append(GetItemFlags(ID_UP2SPEED), ID_UP2SPEED,
					   _T("Turn up 2%(&B)"));
	m_speedMenu.Append(GetItemFlags(ID_UP3SPEED), ID_UP3SPEED,
					   _T("Turn up 3%(&C)"));
	m_speedMenu.Append(GetItemFlags(ID_UP5SPEED), ID_UP5SPEED,
					   _T("Turn up 5%(&D)"));
	m_speedMenu.Append(GetItemFlags(ID_UP10SPEED), ID_UP10SPEED,
					   _T("Turn up 10%(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DECSPEED), ID_DECSPEED,
					   _T("Decrease(&D)..."));
	m_speedMenu.Append(GetItemFlags(ID_INCSPEED), ID_INCSPEED,
					   _T("Increase(&D)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu,
					   _T("Speed(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(GetItemFlags(ID_RESETFREQ), ID_RESETFREQ,
					  _T("Reset Frequency(&R)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DOWN0_1FREQ), ID_DOWN0_1FREQ,
					  _T("Turn down 0.1%(&0)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN1FREQ), ID_DOWN1FREQ,
					  _T("Turn down 1%(&1)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN2FREQ), ID_DOWN2FREQ,
					  _T("Turn down 2%(&2)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN3FREQ), ID_DOWN3FREQ,
					  _T("Turn down 3%(&3)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN5FREQ), ID_DOWN5FREQ,
					  _T("Turn down 5%(&5)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN10FREQ), ID_DOWN10FREQ,
					  _T("Turn down 10%(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_UP0_1FREQ), ID_UP0_1FREQ,
					  _T("Turn up 0.1%(&Z)"));
	m_freqMenu.Append(GetItemFlags(ID_UP1FREQ), ID_UP1FREQ,
					  _T("Turn up 1%(&A)"));
	m_freqMenu.Append(GetItemFlags(ID_UP2FREQ), ID_UP2FREQ,
					  _T("Turn up 2%(&B)"));
	m_freqMenu.Append(GetItemFlags(ID_UP3FREQ), ID_UP3FREQ,
					  _T("Turn up 3%(&C)"));
	m_freqMenu.Append(GetItemFlags(ID_UP5FREQ), ID_UP5FREQ,
					  _T("Turn up 5%(&D)"));
	m_freqMenu.Append(GetItemFlags(ID_UP10FREQ), ID_UP10FREQ,
					  _T("Turn up 10%(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DECFREQ), ID_DECFREQ,
					  _T("Decrease(&F)..."));
	m_freqMenu.Append(GetItemFlags(ID_INCFREQ), ID_INCFREQ,
					  _T("Increase(&F)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu,
						_T("Frequency(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(GetItemFlags(ID_RESETPITCH), ID_RESETPITCH,
					   _T("Reset pitch(&R)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_DOWN1PITCH), ID_DOWN1PITCH,
					   _T("Flat(&1)"));
	m_pitchMenu.Append(GetItemFlags(ID_DOWN2PITCH), ID_DOWN2PITCH,
					   _T("Double flat(&2)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_UP1PITCH), ID_UP1PITCH,
					   _T("Sharp(&A)"));
	m_pitchMenu.Append(GetItemFlags(ID_UP2PITCH), ID_UP2PITCH,
					   _T("Double sharp(&B)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu,
						_T("Pitch(&P)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQFLAT), ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGHEST), ID_EQLOWHIGHEST,
						  _T("Boost low(strongest)(&A)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGH), ID_EQLOWHIGH,
						  _T("Boost low(strong)(&B)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWMIDDLE), ID_EQLOWMIDDLE,
						  _T("Boost low(middle)(&C)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOW), ID_EQLOWLOW,
						  _T("Boost low(weak)(&D)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOWEST), ID_EQLOWLOWEST,
						  _T("Boost low(weakest)(&E)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGHEST), ID_EQMIDDLEHIGHEST,
						  _T("Boost middle(strongest)(&G)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGH), ID_EQMIDDLEHIGH,
						  _T("Boost middle(strong)(&H)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEMIDDLE), ID_EQMIDDLEMIDDLE,
						  _T("Boost middle(middle)(&I)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOW), ID_EQMIDDLELOW,
						  _T("Boost middle(weak)(&J)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOWEST), ID_EQMIDDLELOWEST,
						  _T("Boost middle(weakest)(&K)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGHEST), ID_EQHIGHHIGHEST,
						  _T("Boost high(strongest)(&L)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGH), ID_EQHIGHHIGH,
						  _T("Boost high(strong)(&M)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHMIDDLE), ID_EQHIGHMIDDLE,
						  _T("Boost high(middle)(&N)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOW), ID_EQHIGHLOW,
						  _T("Boost high(weak)(&O)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOWEST), ID_EQHIGHLOWEST,
						  _T("Boost high(weakest)(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu,
						_T("EQ preset(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_DEFAULT), ID_3DREVERB_DEFAULT,
						_T("Default(&D)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PADDEDCELL),
						ID_3DREVERB_PADDEDCELL, _T("Padded Cell(&P)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ROOM), ID_3DREVERB_ROOM,
						_T("Room(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_BATHROOM), ID_3DREVERB_BATHROOM,
						_T("Bathroom(&B)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LIVINGROOM),
						ID_3DREVERB_LIVINGROOM, _T("Living Room(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONEROOM), ID_3DREVERB_STONEROOM,
						_T("Stone Room(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_AUDITORIUM),
						ID_3DREVERB_AUDITORIUM, _T("Auditorium(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CONCERTHALL),
						ID_3DREVERB_CONCERTHALL, _T("Concert Hall(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CAVE), ID_3DREVERB_CAVE,
						_T("Cave(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ARENA), ID_3DREVERB_ARENA,
						_T("Arena(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HANGAR), ID_3DREVERB_HANGAR,
						_T("Hangar(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CARPETEDHALLWAY),
						ID_3DREVERB_CARPETEDHALLWAY, _T("Carpeted Hallway(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HALLWAY), ID_3DREVERB_HALLWAY,
						_T("Hallway(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONECORRIDOR),
						ID_3DREVERB_STONECORRIDOR, _T("Stone Corridor(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ALLEY), ID_3DREVERB_ALLEY,
						_T("Alley(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_FOREST), ID_3DREVERB_FOREST,
						_T("Forest(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CITY), ID_3DREVERB_CITY,
						_T("City(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MOUNTAINS), ID_3DREVERB_MOUNTAINS,
						_T("Mountains(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_QUARRY), ID_3DREVERB_QUARRY,
						_T("Quarry(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLAIN), ID_3DREVERB_PLAIN,
						_T("Plain(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PARKINGLOT),
						ID_3DREVERB_PARKINGLOT, _T("Parking Lot(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SEWERPIPE), ID_3DREVERB_SEWERPIPE,
						_T("Sewer Pipe(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_UNDERWATER),
						ID_3DREVERB_UNDERWATER, _T("Underwater(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SMALLROOM), ID_3DREVERB_SMALLROOM,
						_T("Small Room(&S)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMROOM),
						ID_3DREVERB_MEDIUMROOM, _T("Medium Room(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEROOM), ID_3DREVERB_LARGEROOM,
						_T("Large Room(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMHALL),
						ID_3DREVERB_MEDIUMHALL, _T("Medium Hall(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEHALL), ID_3DREVERB_LARGEHALL,
						_T("Large Hall(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLATE), ID_3DREVERB_PLATE,
						_T("Plate(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu,
						_T("Reverb(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DEFAULT), ID_DELAY_DEFAULT,
					   _T("Default(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_SHORT), ID_DELAY_SHORT,
					   _T("Short Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MEDIUM), ID_DELAY_MEDIUM,
					   _T("Medium Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_LONG), ID_DELAY_LONG,
					   _T("Long Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOSHORT),
					   ID_DELAY_STEREOSHORT, _T("Stereo Short Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOMEDIUM),
					   ID_DELAY_STEREOMEDIUM, _T("Stereo Medium Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOLONG), ID_DELAY_STEREOLONG,
					   _T("Stereo Long Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MOUNTAIN), ID_DELAY_MOUNTAIN,
					   _T("Mountain Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_BIG), ID_DELAY_BIG,
					   _T("Big Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOBIG), ID_DELAY_STEREOBIG,
					   _T("Stereo Big Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLING), ID_DELAY_DOUBLING,
					   _T("Doubling(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLEKICK), ID_DELAY_DOUBLEKICK,
					   _T("Double Kick(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu,
						_T("Delay(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(GetItemFlags(ID_CHORUS_DEFAULT), ID_CHORUS_DEFAULT,
						_T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("Chorus(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(GetItemFlags(ID_COMPRESSOR_DEFAULT),
							ID_COMPRESSOR_DEFAULT, _T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("Compressor(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(GetItemFlags(ID_FLANGER_DEFAULT), ID_FLANGER_DEFAULT,
							_T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("Flanger(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(GetItemFlags(ID_GARGLE_DEFAULT), ID_GARGLE_DEFAULT,
							_T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("Gargle(&F)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(GetItemFlags(ID_DISTORTION_DEFAULT), ID_DISTORTION_DEFAULT, _T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("Distortion(&D)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_NORMALIZE), ID_NORMALIZE,
						_T("Normalize(&N)"));
	m_effectMenu.Append(GetItemFlags(ID_VOCALCANCEL), ID_VOCALCANCEL,
						_T("Vocal cancel(&V)"));
	m_effectMenu.Append(GetItemFlags(ID_REVERSE), ID_REVERSE,
						_T("Reverse play(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_RECORD), ID_RECORD,
						_T("Old record play(&F)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_MONORAL), ID_MONORAL,
						_T("Monoral(&M)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYLEFT), ID_ONLYLEFT,
						_T("Only left(&L)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYRIGHT), ID_ONLYRIGHT,
						_T("Only right(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_CHANGELR), ID_CHANGELR,
						_T("Change LR(&C)"));
	Append(MF_POPUP | MF_MENUBARBREAK, (UINT_PTR)(HMENU)m_effectMenu,
		   _T("Effect(&E)"));
	AppendSeparator();

	// システムメニュー
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVIDEOSCREENVISIBLE),
								ID_RECOVERVIDEOSCREENVISIBLE,
								_T("Video screen(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERTIMESLIDERVISIBLE),
								ID_RECOVERTIMESLIDERVISIBLE,
								_T("Position slider(&T)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERSPEEDVISIBLE),
								ID_RECOVERSPEEDVISIBLE, _T("Speed(&S)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERFREQVISIBLE),
								ID_RECOVERFREQVISIBLE, _T("Frequency(&F)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPITCHVISIBLE),
								ID_RECOVERPITCHVISIBLE, _T("Pitch(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVOLUMEVISIBLE),
								ID_RECOVERVOLUMEVISIBLE,
								_T("Volume(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPANVISIBLE),
								ID_RECOVERPANVISIBLE,
								_T("Pan(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVEREQVISIBLE),
								ID_RECOVEREQVISIBLE,
								_T("Graphic Equalizer(&G)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERLISTVISIBLE),
								ID_RECOVERLISTVISIBLE, _T("Playlist(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu,
						  _T("Visible(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSLOOP),
								 ID_RECOVERSLOOP, _T("Single loop(&1)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERALOOP),
								 ID_RECOVERALOOP, _T("All loop(&T)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRANDOM),
								 ID_RECOVERRANDOM, _T("Random(&H)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERCONTINUE),
								 ID_RECOVERCONTINUE, _T("Continue(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERINSTANTLOOP),
								 ID_RECOVERINSTANTLOOP,
								_T("Loop when adding a marker(&I)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSETPOSITIONAUTO),
								 ID_RECOVERSETPOSITIONAUTO,
								 _T("Set position automatic when ")
								 _T("adjusting marker position(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERREVERSE),
								 ID_RECOVERREVERSE, _T("Reverse(&R)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRECORD),
								 ID_RECOVERRECORD, _T("Record(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu,
						  _T("Play mode(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWPOS), ID_RECOVERWPOS,
						  _T("Window position(&P)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWSIZE), ID_RECOVERWSIZE,
						  _T("Window size(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERSPEED), ID_RECOVERSPEED,
						  _T("Speed(&S)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERFREQ),
						  ID_RECOVERFREQ, _T("Frequency(&F)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPITCH), ID_RECOVERPITCH,
						  _T("Pitch(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERVOLUME), ID_RECOVERVOLUME,
						  _T("Volume(&V)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPAN), ID_RECOVERPAN,
						  _T("Pan(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVEREQ), ID_RECOVEREQ,
						  _T("Graphic Equalizer(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERLIST), ID_RECOVERLIST,
						  _T("Playlist(&P)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, _T("Recover(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_KEYSETTING), ID_KEYSETTING,
		   _T("Shortcut key setting(&K)..."));
	Append(GetItemFlags(ID_OUTKEYSETTING), ID_OUTKEYSETTING,
		   _T("Global hot key setting(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_TIMERPLAY), ID_TIMERPLAY,
		   _T("Timer setting(&T)..."));
	Append(GetItemFlags(ID_PLAYPOSITION), ID_PLAYPOSITION,
		   _T("Play position(&P)..."));
	Append(GetItemFlags(ID_FADEOUTSTOP), ID_FADEOUTSTOP,
		   _T("Fade out stop(&F)"));
	Append(GetItemFlags(ID_FADEOUTNEXT), ID_FADEOUTNEXT,
		   _T("Fade out next(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_METRONOME), ID_METRONOME, _T("Metronome(&M)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_DOUBLERUN), ID_DOUBLERUN,
		   _T("Double runnable(&D)"));
	Append(GetItemFlags(ID_TOPMOST), ID_TOPMOST, _T("Bring window top(&S)"));
	Append(GetItemFlags(ID_TASKTRAY), ID_TASKTRAY,
		   _T("Minimize to system tray(&T)"));
	Append(GetItemFlags(ID_COPYTIME), ID_COPYTIME,
		   _T("Copy current position to clipboard(&C)"));
	AppendSeparator();

	// ヘルプメニュー
	Append(GetItemFlags(ID_MANUAL), ID_MANUAL, _T("Manual(&M)..."));
	Append(GetItemFlags(ID_VERSIONINFO), ID_VERSIONINFO, _T("Version(&A)..."));

	AppendSeparator();
	Append(MFS_ENABLED, ID_RESTORE, _T("Restore(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_EXIT), ID_EXIT, _T("Exit(&X)"));
#endif // JP
	if(!m_hMenu)
		return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// アイテムのフラグを得る
//----------------------------------------------------------------------------
UINT CRMenu_Taskbar::GetItemFlags(UINT uID)
{
	CMenu & rMenu = (CMenu &)m_rParent.GetMenu();
	return rMenu.GetState(uID);
}
//----------------------------------------------------------------------------
