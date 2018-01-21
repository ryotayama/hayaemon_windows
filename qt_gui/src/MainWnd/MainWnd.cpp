//----------------------------------------------------------------------------
// MainWnd.cpp : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#include "MainWnd.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QTimer>
#include "../App.h"
#include "../Common/CommandList.h"
#include "../Common/Utils.h"
#include "../CountLoopWnd/CountLoopWnd_MainWnd.h"
#include "3DReverbCustomizeWnd.h"
#include "ABLoopPosWnd.h"
#include "DelayCustomizeWnd.h"
#include "PlayListView_MainWnd.h"
#include "Platform.h"
#include "ReverbCustomizeWnd.h"
#include "Utility.h"
//----------------------------------------------------------------------------
// ドロップされたファイルの追加
//----------------------------------------------------------------------------
CMainWnd::~CMainWnd()
{
	m_timeThreadRunning = false;
	m_timeThread->join();
}
//----------------------------------------------------------------------------
// ドロップされたファイルの追加
//----------------------------------------------------------------------------
void CMainWnd::AddDropFiles(const QList<QUrl> & urls, BOOL bClear)
{
	int nSelect = m_tab->GetCurrentFocus();
	int count = urls.size();
	int i = 0;

	QString ext = QFileInfo(urls.front().toLocalFile()).suffix();
	if(ext.compare("ini", Qt::CaseInsensitive) == 0) {
		return;
	}
	if(bClear) {
		m_arrayList[nSelect]->DeleteAllItems();
	}
	for(; i < count; i++) {
		auto &url = urls[i];
		QString path = url.isLocalFile() ? url.toLocalFile() : url.url();
		m_arrayList[nSelect]->AddFile(path);
	}

	if(m_arrayList[nCurPlayTab]->GetItemCount() <= 0) {
		m_sound.StreamFree();
		Stop();
	}

	if(bClear || m_sound.GetCurFileNum() <= 0) {
		m_sound.SetCurFileNum(0);
		PlayNext(bClear, TRUE);
	}

	SetPreviousNextMenuState();
}
//----------------------------------------------------------------------------
// マーカーの追加
//----------------------------------------------------------------------------
void CMainWnd::AddMarker()
{
	QWORD time = m_sound.ChannelGetPosition();
	SetABLoopA(time);

	if(!bMarkerPlay) SetMarkerPlay();

	if(bInstantLoop) SetPrevMarker();
}
//----------------------------------------------------------------------------
// 回数ループのチェック
//----------------------------------------------------------------------------
BOOL CMainWnd::CheckLoop()
{
	if(bCountLoop) {
		nCurrentLoopCount++;
		if(nCurrentLoopCount >= nLoopCount) {
			nCurrentLoopCount = 0;
			QWORD qwTime = m_sound.GetLoopPosA();
			std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
			QWORD length = m_sound.ChannelGetLength();
			int max = (int)arrayMarker.size();
			if(max > 0 && qwTime == 0)
				qwTime = arrayMarker[0];
			else {
				if(qwTime == arrayMarker[max - 1]) {
					SetTime(0);
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
						m_timeSlider.SetSelStart(0);
						m_timeSlider.SetSelEnd(arrayMarker[0] / 100000);
						m_sound.SetLoopPosA(0);
						m_sound.SetLoopPosB(arrayMarker[0]);
				}
			}
			else {
				bDone = TRUE;
				m_timeSlider.SetSelStart(0);
				m_timeSlider.SetSelEnd(length / 100000);
				m_sound.SetLoopPosA(0);
				m_sound.SetLoopPosB(length);
			}

			if(!bDone) {
				for(int i = 0; i < max; i++) {
					if(i + 1 < max) {
						if(arrayMarker[i] <= qwTime
							&& qwTime < arrayMarker[i + 1]) {
							bDone = TRUE;
							m_timeSlider.SetSelStart(arrayMarker[i] / 100000);
							m_timeSlider.SetSelEnd(arrayMarker[i + 1] / 100000);
							m_sound.SetLoopPosA(arrayMarker[i]);
							m_sound.SetLoopPosB(arrayMarker[i + 1]);
							break;
						}
					}
				}
			}

			if(!bDone) {
				if(arrayMarker[max - 1] <= qwTime && qwTime <= length) {
					bDone = TRUE;
					m_timeSlider.SetSelStart(arrayMarker[max - 1] / 100000);
					m_timeSlider.SetSelEnd(length / 100000);
					m_sound.SetLoopPosA(arrayMarker[max - 1]);
					m_sound.SetLoopPosB(length);
				}
			}
			return FALSE;
		}
		else return TRUE;
	}
	else return TRUE;
}
//----------------------------------------------------------------------------
// 各コントロールを作成
//----------------------------------------------------------------------------
BOOL CMainWnd::CreateControls()
{
	TCHAR chPath[255], buf[255];
	lstrcpy(chPath,
					ToTstring(m_rApp.GetFilePath() + QString("Setting.ini")).c_str());

	// ツールバーの作成
	if(!m_toolBar.Create()) {
		m_rApp.ShowError(tr("failed to create toolbar."));
		return FALSE;
	}

	// 再生時間表示用ラベルの作成
	if(!m_timeLabel.Create()) {
		m_rApp.ShowError(tr("failed to create time label."));
		return FALSE;
	}

	// 再生時間設定用スライダの作成
	if(!m_timeSlider.Create()) {
		m_rApp.ShowError(tr("failed to create time slider."));
		return FALSE;
	}

	// 再生速度表示用ラベルの作成
	if(!m_speedLabel.Create()) {
		m_rApp.ShowError(tr("failed to create speed label."));
		return FALSE;
	}

	// 再生速度設定用スライダの作成
	if(!m_speedSlider.Create()) {
		m_rApp.ShowError(tr("failed to create speed slider."));
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
	if(_nSpeedDecimalDigit == 0) m_menu.OnSetSpeedDecimal0MenuSelected();
	else if(_nSpeedDecimalDigit == 1)
		m_menu.OnSetSpeedDecimal1MenuSelected();
	else if(_nSpeedDecimalDigit == 2)
		m_menu.OnSetSpeedDecimal2MenuSelected();
	if(_dMinSpeed < 1.0) _dMinSpeed = 1.0;
	if(_dMaxSpeed > 5000.0) _dMaxSpeed = 5000.0;

	m_speedSlider.SetLimit(_dMinSpeed, _dMaxSpeed);
	m_speedLabel.SetLimit(_dMinSpeed, _dMaxSpeed);

	if(GetPrivateProfileInt(_T("Options"), _T("RecoverSpeed"), 0, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERSPEED);
		int speed = GetPrivateProfileInt(_T("Options"), _T("Speed"), 1000,
			chPath);
		m_speedLabel.SetSpeed((double)(speed
			/ pow(10.0, m_speedLabel.GetDecimalDigit())));
		m_speedSlider.SetThumbPos((LONG)speed, TRUE);
		SetSpeed((double)(speed
			/ pow(10.0, m_speedLabel.GetDecimalDigit())));
	}

	// 再生周波数表示用ラベルの作成
	if(!m_freqLabel.Create()) {
		m_rApp.ShowError(tr("failed to create frequency label."));
		return FALSE;
	}

	// 再生周波数設定用スライダの作成
	if(!m_freqSlider.Create()) {
		m_rApp.ShowError(tr("failed to create frequency slider."));
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
	if(_nFreqDecimalDigit == 0) m_menu.OnSetFreqDecimal0MenuSelected();
	else if(_nFreqDecimalDigit == 1) m_menu.OnSetFreqDecimal1MenuSelected();
	else if(_nFreqDecimalDigit == 2) m_menu.OnSetFreqDecimal2MenuSelected();
	if(_dMinFreq < 1.0) _dMinFreq = 1.0;
	if(_dMaxFreq > 5000.0) _dMaxFreq = 5000.0;

	m_freqSlider.SetLimit(_dMinFreq, _dMaxFreq);
	m_freqLabel.SetLimit(_dMinFreq, _dMaxFreq);

	if(GetPrivateProfileInt(_T("Options"), _T("RecoverFrequency"), 0,
			chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERFREQ);
		int freq = GetPrivateProfileInt(_T("Options"), _T("Frequency"),
					1000, chPath);
		m_freqLabel.SetFreq((double)(freq
			/ pow(10.0, m_freqLabel.GetDecimalDigit())));
		m_freqSlider.SetThumbPos((LONG)freq, TRUE);
		SetFreq((double)(freq
			/ pow(10.0, m_freqLabel.GetDecimalDigit())));
	}

	// 音程表示用ラベルの作成
	if(!m_pitchLabel.Create()) {
		m_rApp.ShowError(tr("failed to create pitch label."));
		return FALSE;
	}

	// 音程設定用スライダの作成
	if(!m_pitchSlider.Create()) {
		m_rApp.ShowError(tr("failed to create pitch slider."));
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
	if(_nPitchDecimalDigit == 0) m_menu.OnSetPitchDecimal0MenuSelected();
	else if(_nPitchDecimalDigit == 1)
		m_menu.OnSetPitchDecimal1MenuSelected();
	else if(_nPitchDecimalDigit == 2)
		m_menu.OnSetPitchDecimal2MenuSelected();

	if(_dMinPitch < -60.0) _dMinPitch = -60.0;
	if(_dMaxPitch > 60.0) _dMaxPitch = 60.0;

	m_pitchSlider.SetLimit(_dMinPitch, _dMaxPitch);
	m_pitchLabel.SetLimit(_dMinPitch, _dMaxPitch);

	if(GetPrivateProfileInt(_T("Options"), _T("RecoverPitch"), 0, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERPITCH);
		int pitch = GetPrivateProfileInt(_T("Options"), _T("Pitch"), 1000,
			chPath);
		m_pitchLabel.SetPitch((double)(pitch
			/ pow(10.0, m_pitchLabel.GetDecimalDigit())));
		m_pitchSlider.SetThumbPos((LONG)pitch, TRUE);
		SetPitch((double)(pitch
			/ pow(10.0, m_pitchLabel.GetDecimalDigit())));
	}

	// 音量表示用ラベルの作成
	if(!m_volumeLabel.Create()) {
		m_rApp.ShowError(tr("failed to create volume label."));
		return FALSE;
	}

	// 音量設定用スライダの作成
	if(!m_volumeSlider.Create()) {
		m_rApp.ShowError(tr("failed to create volume slider."));
		return FALSE;
	}
	if(GetPrivateProfileInt(_T("Options"), _T("RecoverVolume"), 1, chPath))
	{
		m_menu.SwitchItemChecked(ID_RECOVERVOLUME);
		int volume = GetPrivateProfileInt(_T("Options"), _T("Volume"), 1000,
			chPath);
		m_volumeLabel.SetVolume((double)(volume / 10.0));
		m_volumeSlider.SetThumbPos(volume);
		SetVolume((double)(volume / 10.0));
	}

	// パン表示用ラベルの作成
	if(!m_panLabel.Create()) {
		m_rApp.ShowError(tr("failed to create pan label."));
		return FALSE;
	}

	// パン設定用スライダの作成
	if(!m_panSlider.Create()) {
		m_rApp.ShowError(tr("failed to create pan slider."));
		return FALSE;
	}
	if(GetPrivateProfileInt(_T("Options"), _T("RecoverPan"), 0, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERPAN);
		int pan = GetPrivateProfileInt(_T("Options"), _T("Pan"), 0,
			chPath);
		m_panLabel.SetPan(pan);
		m_panSlider.SetThumbPos(pan);
		SetPan(pan);
	}

	m_eqItems = std::vector<EQItem>{
		{"20",    m_eq20Label,    m_eq20Slider,    ID_EQ20,    &CMainWnd::SetEQ20},
		{"25",    m_eq25Label,    m_eq25Slider,    ID_EQ25,    &CMainWnd::SetEQ25},
		{"31.5",  m_eq31_5Label,  m_eq31_5Slider,  ID_EQ31_5,  &CMainWnd::SetEQ31_5},
		{"40",    m_eq40Label,    m_eq40Slider,    ID_EQ40,    &CMainWnd::SetEQ40},
		{"50",    m_eq50Label,    m_eq50Slider,    ID_EQ50,    &CMainWnd::SetEQ50},
		{"63",    m_eq63Label,    m_eq63Slider,    ID_EQ63,    &CMainWnd::SetEQ63},
		{"80",    m_eq80Label,    m_eq80Slider,    ID_EQ80,    &CMainWnd::SetEQ80},
		{"100",   m_eq100Label,   m_eq100Slider,   ID_EQ100,   &CMainWnd::SetEQ100},
		{"125",   m_eq125Label,   m_eq125Slider,   ID_EQ125,   &CMainWnd::SetEQ125},
		{"160",   m_eq160Label,   m_eq160Slider,   ID_EQ160,   &CMainWnd::SetEQ160},
		{"200",   m_eq200Label,   m_eq200Slider,   ID_EQ200,   &CMainWnd::SetEQ200},
		{"250",   m_eq250Label,   m_eq250Slider,   ID_EQ250,   &CMainWnd::SetEQ250},
		{"315",   m_eq315Label,   m_eq315Slider,   ID_EQ315,   &CMainWnd::SetEQ315},
		{"400",   m_eq400Label,   m_eq400Slider,   ID_EQ400,   &CMainWnd::SetEQ400},
		{"500",   m_eq500Label,   m_eq500Slider,   ID_EQ500,   &CMainWnd::SetEQ500},
		{"630",   m_eq630Label,   m_eq630Slider,   ID_EQ630,   &CMainWnd::SetEQ630},
		{"800",   m_eq800Label,   m_eq800Slider,   ID_EQ800,   &CMainWnd::SetEQ800},
		{"1K",    m_eq1kLabel,    m_eq1kSlider,    ID_EQ1K,    &CMainWnd::SetEQ1K},
		{"1.25K", m_eq1_25kLabel, m_eq1_25kSlider, ID_EQ1_25K, &CMainWnd::SetEQ1_25K},
		{"1.6K",  m_eq1_6kLabel,  m_eq1_6kSlider,  ID_EQ1_6K,  &CMainWnd::SetEQ1_6K},
		{"2K",    m_eq2kLabel,    m_eq2kSlider,    ID_EQ2K,    &CMainWnd::SetEQ2K},
		{"2.5K",  m_eq2_5kLabel,  m_eq2_5kSlider,  ID_EQ2_5K,  &CMainWnd::SetEQ2_5K},
		{"3.15K", m_eq3_15kLabel, m_eq3_15kSlider, ID_EQ3_15K, &CMainWnd::SetEQ3_15K},
		{"4K",    m_eq4kLabel,    m_eq4kSlider,    ID_EQ4K,    &CMainWnd::SetEQ4K},
		{"5K",    m_eq5kLabel,    m_eq5kSlider,    ID_EQ5K,    &CMainWnd::SetEQ5K},
		{"6.3K",  m_eq6_3kLabel,  m_eq6_3kSlider,  ID_EQ6_3K,  &CMainWnd::SetEQ6_3K},
		{"8K",    m_eq8kLabel,    m_eq8kSlider,    ID_EQ8K,    &CMainWnd::SetEQ8K},
		{"10K",   m_eq10kLabel,   m_eq10kSlider,   ID_EQ10K,   &CMainWnd::SetEQ10K},
		{"12.5K", m_eq12_5kLabel, m_eq12_5kSlider, ID_EQ12_5K, &CMainWnd::SetEQ12_5K},
		{"16K",   m_eq16kLabel,   m_eq16kSlider,   ID_EQ16K,   &CMainWnd::SetEQ16K},
		{"20K",   m_eq20kLabel,   m_eq20kSlider,   ID_EQ20K,   &CMainWnd::SetEQ20K},
	};

	int row = 0;
	for (auto &item : m_eqItems) {
		auto label = new QLabel(eqGroupBox);
		label->setObjectName("eq" + item.title + "Label");
		label->setText(QString(item.title + "Hz : ").replace("K", " K"));

		auto spinbox = new QSpinBox(eqGroupBox);
		spinbox->setObjectName("eq" + item.title + "SpinBox");

		auto slider = new CSliderCtrlCore(eqGroupBox);
		slider->setObjectName("eq" + item.title + "Slider");
		slider->setOrientation(Qt::Horizontal);

		// イコライザ表示用ラベルの作成
		item.label.Init(label, spinbox, &item.slider);
		if(!item.label.Create()) {
			m_rApp.ShowError(
					QString(tr("failed to create EQ(%1Hz) label.")).arg(item.title));
			return FALSE;
		}

		// イコライザ設定用スライダの作成
		item.slider.Init(slider, &item.label,
										 std::bind(item.setEQ, this, std::placeholders::_1));
		if(!item.slider.Create()) {
			m_rApp.ShowError(
					QString(tr("failed to create EQ(%1Hz) slider.")).arg(item.title));
			return FALSE;
		}

		label->setVisible(false);
		spinbox->setVisible(false);
		slider->setVisible(false);

		eqLayout->addWidget(label, row, 0);
		eqLayout->addWidget(spinbox, row, 1);
		eqLayout->addWidget(slider, row, 2);
		row++;

		auto action =
				new QAction(QString(item.title + "Hz").replace("K", " K"), this);
		action->setCheckable(true);
		action->setChecked(false);
		connect(action, &QAction::toggled,
						[&] (bool checked) {
							m_menu.CheckItem(item.menuId,
															 checked ? MF_CHECKED : MF_UNCHECKED);
							SetEQVisible(m_menu.IsItemChecked(ID_EQ));
						});
		menuViewEQ->addAction(action);
		m_menu.m_actionMap.insert({item.menuId, action});
	}
	if(GetPrivateProfileInt(_T("Options"), _T("RecoverEQ"), 0, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVEREQ);
		for (auto &item : m_eqItems) {
			tstring key = ToTstring("EQ" + item.title);
			int eq = GetPrivateProfileInt(_T("Options"), key.c_str(), 0,
				chPath);
			item.label.SetEQ(eq);
			item.slider.SetThumbPos(eq);
			(this->*item.setEQ)((LONG)eq);
		}
	}

	// タブの作成
	m_arrayList.push_back(new CPlayListView_MainWnd(*this, m_tab));
	m_tab->addTab(m_arrayList[0], tr("No Title"));
	// プレイリスト用リストビューの作成
	if(!m_arrayList[0]->Create()) {
		m_rApp.ShowError(tr("failed to create playlist."));
		return FALSE;
	}

	SetContextMenus();
	
	return TRUE;
}
//----------------------------------------------------------------------------
// マーカーの削除
//----------------------------------------------------------------------------
void CMainWnd::DeleteMarker()
{
	std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
	QWORD length = m_sound.ChannelGetLength();
	int max = (int)arrayMarker.size();
	for(int i = 0; i < max; i++) {
		if(arrayMarker[i] == m_sound.GetLoopPosB()) {
			m_sound.EraseMarker(i);
			SetTime(m_sound.ChannelGetPosition());
			break;
		}
	}
}
//----------------------------------------------------------------------------
// 指定した%再生周波数を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownFreq(double freq)
{
	double dCalc = pow(10.0, m_freqSlider.GetDecimalDigit());
	int newFreq = m_freqSlider.GetThumbPos() - (int)(freq
		* dCalc);
	m_freqLabel.SetFreq((double)(newFreq / dCalc));
}
//----------------------------------------------------------------------------
// 指定した数値×半音分音程を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownPitch(double pitch)
{
	double dCalc = pow(10.0, m_pitchSlider.GetDecimalDigit());
	int newPitch = m_pitchSlider.GetThumbPos() - (int)(pitch * dCalc);
	m_pitchLabel.SetPitch((double)(newPitch / dCalc));
}
//----------------------------------------------------------------------------
// 指定した%再生速度を下げる
//----------------------------------------------------------------------------
void CMainWnd::DownSpeed(double speed)
{
	double dCalc = pow(10.0, m_speedSlider.GetDecimalDigit());
	int newSpeed = m_speedSlider.GetThumbPos() - (int)(speed * dCalc);
	m_speedLabel.SetSpeed((double)(newSpeed / dCalc));
}
//----------------------------------------------------------------------------
// 早送り
//----------------------------------------------------------------------------
void CMainWnd::Forward()
{
	double dPos = m_sound.ChannelGetSecondsPosition();
	double dDifference = 1.0;
	dDifference *= m_sound.GetTempo() / 100.0;
	dDifference *= m_sound.GetSampleRate() / 100.0;
	if(dDifference < 1.0) dDifference = 1.0;
	SetTime(m_sound.ChannelSeconds2Bytes(dPos + dDifference));
}
//----------------------------------------------------------------------------
// 指定した秒数進む
//----------------------------------------------------------------------------
void CMainWnd::ForwardSeconds(int seconds)
{
	double pos = m_sound.ChannelGetSecondsPosition();
	pos += seconds;
	SetSeconds(pos);
}
//----------------------------------------------------------------------------
// 頭出し
//----------------------------------------------------------------------------
void CMainWnd::Head()
{
	if(bMarkerPlay) SetTime(m_sound.GetLoopPosA());
	else SetTime(0);
}
//----------------------------------------------------------------------------
// ファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenFile(const QString & lpszFilePath, int nCount)
{
	if(m_sound.IsABLoopA()) SetABLoopA();
	if(m_sound.IsABLoopB()) SetABLoopB();
	if(bMarkerPlay) SetMarkerPlay();
	BOOL bRet = FALSE;
	bRet = m_sound.StreamCreateFile(ToTstring(lpszFilePath).c_str(), FALSE,
																	nCount);
	if(!bRet) {
		KillTimer(IDT_TIME);
		m_timeLabel.SetTime(0, 0);
		m_timeSlider.SetTime(0, 10);
		m_toolBar.SetPlayingState(FALSE);
		return FALSE;
	}
	m_sound.ClearMarker();
	SetAllEffects();
	m_toolBar.SetPlayingState(FALSE);
	if(m_menu.IsItemChecked(ID_REVERSE)) {
		m_timeLabel.SetTime(m_sound.ChannelGetSecondsLength(),
							m_sound.ChannelGetSecondsLength());
		m_timeSlider.SetTime(m_sound.ChannelGetLength(),
							 m_sound.ChannelGetLength());
	}
	else {
		m_timeLabel.SetTime(0, m_sound.ChannelGetSecondsLength());
		m_timeSlider.SetTime(0, m_sound.ChannelGetLength());
	}

	return TRUE;
}
//----------------------------------------------------------------------------
// INI ファイルを開く
//----------------------------------------------------------------------------
void CMainWnd::OpenInitFile()
{
	TCHAR chPath[255];
	lstrcpy(chPath,
					ToTstring(m_rApp.GetFilePath() + QString("Setting.ini")).c_str());

	if(GetPrivateProfileInt(_T("Visible"), _T("eq20"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ20);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq25"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ25);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq31_5"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ31_5);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq40"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ40);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq50"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ50);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq63"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ63);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq80"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ80);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq100"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ100);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq125"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ125);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq160"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ160);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq200"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ200);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq250"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ250);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq315"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ315);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq400"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ400);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq500"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ500);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq630"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ630);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq800"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ800);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq1k"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ1K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq1_25k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ1_25K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq1_6k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ1_6K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq2k"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ2K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq2_5k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ2_5K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq3_15k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ3_15K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq4k"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ4K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq5k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ5K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq6_3k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ6_3K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq8k"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ8K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq10k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ10K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq12_5k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ12_5K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq16k"), 1, chPath))
		m_menu.SwitchEQVisible(ID_EQ16K);
	if(GetPrivateProfileInt(_T("Visible"), _T("eq20k"), 0, chPath))
		m_menu.SwitchEQVisible(ID_EQ20K);

	// 再生モードの設定
	if(GetPrivateProfileInt(_T("PlayMode"), _T("RecoverSingleLoop"), 1,
			chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERSLOOP);
		if(GetPrivateProfileInt(_T("PlayMode"), _T("SingleLoop"), 0,
				chPath))
			SetSingleLoop();
	}
	if(GetPrivateProfileInt(_T("PlayMode"), _T("RecoverAllLoop"), 1,
			chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERALOOP);
		if(GetPrivateProfileInt(_T("PlayMode"), _T("AllLoop"), 0, chPath))
			SetAllLoop(true);
	}
	if(GetPrivateProfileInt(_T("PlayMode"), _T("RecoverRandom"), 1,
			chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERRANDOM);
		if(GetPrivateProfileInt(_T("PlayMode"), _T("Random"), 0, chPath))
			SetRandom(true);
	}
}
//----------------------------------------------------------------------------
// INI ファイルを開く
//----------------------------------------------------------------------------
void CMainWnd::OpenInitFileAfterShow()
{
	tstring initFilePath =
			ToTstring(m_rApp.GetFilePath() + QString("Setting.ini"));

	TCHAR buf[255];

	// 再生モードの設定
	GetPrivateProfileString(_T("PlayMode"), _T("RecoverContinue"), _T("1"), 
		buf, 255, initFilePath.c_str());
	int _bRecoverContinue = _ttoi(buf);
	GetPrivateProfileString(_T("PlayMode"), _T("Continue"), _T("1"), buf, 255, 
		initFilePath.c_str());
	int _bContinue = _ttoi(buf);
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

	// 再生モードの復元
	if(_bRecoverContinue) {
		m_menu.SwitchItemChecked(ID_RECOVERCONTINUE);
		SetContinue(_bContinue);
	}
	if(_bRecoverInstantLoop) {
		m_menu.SwitchItemChecked(ID_RECOVERINSTANTLOOP);
		if(_bInstantLoop) SetInstantLoop();
	}
	if(_bRecoverSetPositionAuto) {
		m_menu.SwitchItemChecked(ID_RECOVERSETPOSITIONAUTO);
		if(_bSetPositionAuto) SetPositionAuto();
	}
	if(_bRecoverReverse) {
		m_menu.SwitchItemChecked(ID_RECOVERREVERSE);
		if(_bReverse) SetReverse();
	}
	if(_bRecoverRecord) {
		m_menu.SwitchItemChecked(ID_RECOVERRECORD);
		if(_bRecord) SetRecord();
	}
	if(_bNormalize) SetNormalize();

	isInitFileRead = TRUE;
}
//----------------------------------------------------------------------------
// 次のファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenNext()
{
	if(m_menu.IsItemChecked(ID_RANDOM)) return OpenRandom();

	// 開くべきファイルを探す

	int i = m_sound.GetCurFileNum();
	for(; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++) {
		QString filePath;
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, &filePath);
		m_sound.SetCurFileNum(i + 1);
		if(OpenFile(filePath)) {
			QString chTitle;
			m_arrayList[nCurPlayTab]->GetItemText(i, 2, &chTitle);
			chTitle += " - ";
			chTitle += m_rApp.GetName();
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
	int i = m_sound.GetCurFileNum();

	if(m_menu.IsItemChecked(ID_RANDOM)) {
		m_arrayList[nCurPlayTab]->SetPlayOrder(m_sound.GetCurFileNum()-1, -1);
		int nMax = m_arrayList[nCurPlayTab]->GetMaxPlayOrder();
		i = 0;
		std::vector<int> orders = m_arrayList[nCurPlayTab]->GetOrders();
		for(; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++)
			if(nMax == orders[i]) break;

		m_arrayList[nCurPlayTab]->SetPlayOrder(i, -1);
		QString szFilePath;
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, &szFilePath);
		m_sound.SetCurFileNum(i+1);
		BOOL bRet = OpenFile(szFilePath);
		if(bRet) {
			QString chTitle;
			m_arrayList[nCurPlayTab]->GetItemText(i, 2, &chTitle);
			chTitle += " - ";
			chTitle += m_rApp.GetName();
			SetCaption(chTitle);
			m_arrayList[nCurPlayTab]->SetPlayOrder(i);
			m_arrayList[nCurPlayTab]->ScrollToItem(i);
		}
		else {
			m_arrayList[nCurPlayTab]->DeleteItem(i);
			m_arrayList[nCurPlayTab]->ResetNumber();
		}

		SetPreviousNextMenuState();

		// 次に開くべきファイルが見つからなかった場合
		if(!bRet) return FALSE;

		return TRUE;
	}

	// 開くべきファイルを探す
	i = m_sound.GetCurFileNum() - 2;
	for(; i >= 0; i--) {
		QString filePath;
		m_arrayList[nCurPlayTab]->GetItemText(i, 7, &filePath);
		m_sound.SetCurFileNum(i+1);
		if(OpenFile(filePath)) {
			QString chTitle;
			m_arrayList[nCurPlayTab]->GetItemText(i, 2, &chTitle);
			chTitle += " - ";
			chTitle += m_rApp.GetName();
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

	int i = m_sound.GetCurFileNum();

	// 未再生のファイルを探す
	std::vector<int> list;
	std::vector<int> order = m_arrayList[nCurPlayTab]->GetOrders();
	for(int i = 0; i < m_arrayList[nCurPlayTab]->GetItemCount(); i++) {
		if(order[i] < 0) list.push_back(i);
	}
	BOOL bRet = FALSE;
	for(int i = 0; i < (int)list.size(); i++) {
		srand(time(nullptr));
		QString szFilePath;
		int n = rand() % list.size();
		int nItem = list[n];
		m_arrayList[nCurPlayTab]->GetItemText(nItem, 7, &szFilePath);
		m_sound.SetCurFileNum(nItem+1);
		bRet = OpenFile(szFilePath);
		if(bRet) {
			QString chTitle;
			m_arrayList[nCurPlayTab]->GetItemText(nItem, 2, &chTitle);
			chTitle += " - ";
			chTitle += m_rApp.GetName();
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
	if(m_sound.ChannelIsStopped() || m_sound.ChannelIsPausing())
		// 停止中か既に一時停止中だった場合は、再生
		Play();
	else {
		m_sound.ChannelPause();
		KillTimer(IDT_TIME);
		m_toolBar.SetPausingState(TRUE);
		m_arrayList[nCurPlayTab]->SetPausing(m_sound.GetCurFileNum() - 1);
	}
}
//----------------------------------------------------------------------------
// 再生
//----------------------------------------------------------------------------
BOOL CMainWnd::Play()
{
	m_sound.ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
	if(!m_sound.ChannelPlay()) {
		// 再生に失敗
		KillTimer(IDT_TIME);
		m_timeLabel.SetTime(0, 0);
		m_timeSlider.SetTime(0, 10);
		m_toolBar.SetPlayingState(FALSE);
		return FALSE;
	}
	m_toolBar.SetPlayingState(TRUE);
	SetTimer(IDT_TIME, 200);
	m_arrayList[nCurPlayTab]->SetPlaying(m_sound.GetCurFileNum() - 1);
	return TRUE;
}
//----------------------------------------------------------------------------
// 次のファイルを再生
//----------------------------------------------------------------------------
void CMainWnd::PlayNext(BOOL bPlay, BOOL bFadeoutCancel)
{
	// bPlay : かならず再生するかどうか

	BOOL bStopped = m_sound.ChannelIsStopped() && !bPlay;
	BOOL bPausing = m_sound.ChannelIsPausing() && !bPlay;
	BOOL bBassCopy = m_menu.IsItemChecked(ID_BASSCOPY);
	BOOL bDrumsCopy = m_menu.IsItemChecked(ID_CYMBALCOPY);

	// 次に再生すべきファイルを探す
	while(1) {
		if(OpenNext()) {
			if(Play()) break;
			else continue;
		}
		else {
			BOOL isLoop = m_sound.IsLoop();
			m_sound.SetLoop(FALSE);
			Stop();
			if(!m_sound.IsLoop()
					&& m_arrayList[nCurPlayTab]->GetItemCount() > 0
					&& (m_menu.IsItemChecked(ID_RANDOM)
					|| m_sound.GetCurFileNum() > 1)) {
				m_sound.SetCurFileNum(0);
				OpenNext();
			}
			m_sound.SetLoop(isLoop);
			if(m_menu.IsItemChecked(ID_ALOOP)) Play();
			break;
		}
	}

	m_sound.ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
	if(m_sound.ChannelIsActive()) {
		m_menu.CheckItem(ID_BASSCOPY, bBassCopy ?
										MF_CHECKED : MF_UNCHECKED);
		m_menu.CheckItem(ID_CYMBALCOPY, bDrumsCopy ?
										MF_CHECKED : MF_UNCHECKED);
		if(bPausing) Pause();
		else if(bStopped || !m_menu.IsItemChecked(ID_CONTINUE)) {
			BOOL isLoop = m_sound.IsLoop();
			m_sound.SetLoop(TRUE);
			Stop();
			m_sound.SetLoop(isLoop);
		}
	}
}
//----------------------------------------------------------------------------
// 前のファイルを再生
//----------------------------------------------------------------------------
void CMainWnd::PlayPrevious()
{
	BOOL bStopped = m_sound.ChannelIsStopped();
	BOOL bPausing = m_sound.ChannelIsPausing();

	// 再生すべきファイルを探す
	BOOL bEnd = FALSE; // 後ろから検索しなおしたかどうか
	while(1) {
		if(OpenPrevious()) {
			if(Play()) break;
			else continue;
		}
		else {
			if(m_menu.IsItemChecked(ID_ALOOP) && !bEnd) {
				bEnd = TRUE;
				m_sound.SetCurFileNum(
					m_arrayList[nCurPlayTab]->GetItemCount()+1);
				continue;
			}
			Stop();
			Play();
			break;
		}
	}

	if(m_sound.ChannelIsActive()) {
		if(bPausing) Pause();
		else if(bStopped) {
			BOOL isLoop = m_sound.IsLoop();
			m_sound.SetLoop(TRUE);
			Stop();
			m_sound.SetLoop(isLoop);
		}
	}
}
//----------------------------------------------------------------------------
// 再生周波数をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetFreq()
{
	m_freqLabel.SetFreq(100.0);
}
//----------------------------------------------------------------------------
// 音程をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetPitch()
{
	m_pitchLabel.SetPitch(0.0);
}
//----------------------------------------------------------------------------
// 再生速度をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetSpeed()
{
	m_speedLabel.SetSpeed(100.0);
}
//----------------------------------------------------------------------------
// 音量をデフォルトに戻す
//----------------------------------------------------------------------------
void CMainWnd::ResetVolume()
{
	m_volumeLabel.SetVolume(100.0);
}
//----------------------------------------------------------------------------
// 巻き戻し
//----------------------------------------------------------------------------
void CMainWnd::Rewind()
{
	double dPos = m_sound.ChannelGetSecondsPosition(), dDifference = 1.0;
	dDifference *= m_sound.GetTempo() / 100.0;
	dDifference *= m_sound.GetSampleRate() / 100.0;
	if(dDifference < 1.0) dDifference = 1.0;
	SetTime(m_sound.ChannelSeconds2Bytes(dPos - dDifference));
}
//----------------------------------------------------------------------------
// 指定した秒数戻る
//----------------------------------------------------------------------------
void CMainWnd::ReturnSeconds(int seconds)
{
	double pos = m_sound.ChannelGetSecondsPosition();
	pos -= seconds;
	SetSeconds(pos);
}
//----------------------------------------------------------------------------
// AB ループ A の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopA(QWORD pos)
{
	m_sound.SetLoopPosA(pos);
	m_sound.AddMarker(pos);

	BOOL bDone = FALSE; // 範囲を設定したかどうか
	std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
	QWORD length = m_sound.ChannelGetLength();
	int max = (int)arrayMarker.size();
	for(int i = 0; i < max; i++) {
		if(i + 1 < max) {
			if(arrayMarker[i] <= pos && pos < arrayMarker[i + 1]) {
				bDone = TRUE;
				m_timeSlider.SetSelRangeEnabled(true);
				m_timeSlider.SetSelStart(arrayMarker[i] / 100000);
				m_timeSlider.SetSelEnd(arrayMarker[i + 1] / 100000);
				m_sound.SetLoopPosB(arrayMarker[i + 1]);
				break;
			}
		}
	}

	if(!bDone) {
		// 追加したマーカーの位置が一番最後の場合
		if(arrayMarker[max - 1] <= pos && pos <= length) {
			bDone = TRUE;
			m_timeSlider.SetSelRangeEnabled(true);
			m_timeSlider.SetSelStart(arrayMarker[max - 1] / 100000);
			m_timeSlider.SetSelEnd(length / 100000);
			m_sound.SetLoopPosB(length);
		}
	}
}
//----------------------------------------------------------------------------
// AB ループ A の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopA()
{
	m_sound.ClearMarker();
	BOOL bLoop = !m_sound.IsABLoopA();
	m_sound.SetABLoopA(bLoop);
	m_toolBar.SetABLoopState(bLoop, m_sound.IsABLoopB());
	m_menu.SetABLoopState(bLoop, m_sound.IsABLoopB());

	if(bLoop && m_sound.IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オン

		// 現在の再生位置にＡＢループのＡを設定
		QWORD time = m_sound.ChannelGetPosition();
		m_timeSlider.SetSelStart((LONG)(time / 100000));
		m_sound.SetLoopPosA(time);
	}
	else if(bLoop && !m_sound.IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オフ

		m_timeSlider.SetSelRangeEnabled(true);

		// 現在の再生位置にＡＢループのＡを設定
		QWORD time = m_sound.ChannelGetPosition();
		m_timeSlider.SetSelStart((LONG)time / 100000);
		m_sound.SetLoopPosA(time);

		m_timeSlider.SetSelEnd(
			(LONG)(m_sound.ChannelGetLength() / 100000));
	}
	else if(!bLoop && m_sound.IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オン

		m_timeSlider.SetSelStart(0L);
	}
	else if(!bLoop && !m_sound.IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オフ

		m_timeSlider.SetSelStart(0L);
		m_timeSlider.SetSelEnd(0L);
		m_timeSlider.SetSelRangeEnabled(false);
	}
}
//----------------------------------------------------------------------------
// AB ループ A の設定（秒）
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopA_Sec(double dTime)
{
	if(dTime == m_sound.GetLoopPosB_sec()) return;
	if(m_sound.GetLoopPosB_sec() < dTime) return;
	QWORD time = m_sound.ChannelSeconds2Bytes(dTime);
	m_sound.ClearMarker();
	BOOL bLoop = m_sound.IsABLoopA();
	m_sound.SetABLoopA(bLoop);
	m_toolBar.SetABLoopState(bLoop, m_sound.IsABLoopB());
	m_menu.SetABLoopState(bLoop, m_sound.IsABLoopB());

	if(bLoop && m_sound.IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オン

		m_timeSlider.SetSelStart((LONG)(time / 100000));
		m_sound.SetLoopPosA(time);
		if(m_sound.ChannelGetPosition() < time)
			m_sound.ChannelSetPosition(time);
	}
	else if(bLoop && !m_sound.IsABLoopB()) {
		// Ａループ：オン
		// Ｂループ：オフ

		m_timeSlider.SetSelRangeEnabled(true);

		m_timeSlider.SetSelStart((LONG)(time / 100000));
		m_sound.SetLoopPosA(time);

		m_timeSlider.SetSelEnd((LONG)(m_sound.ChannelGetLength() / 100000));

		if(m_sound.ChannelGetPosition() < time)
			m_sound.ChannelSetPosition(time);
	}
	else if(!bLoop && m_sound.IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オン

		m_timeSlider.SetSelStart(0L);
	}
	else if(!bLoop && !m_sound.IsABLoopB()) {
		// Ａループ：オフ
		// Ｂループ：オフ

		m_timeSlider.SetSelStart(0L);
		m_timeSlider.SetSelEnd(0L);
		m_timeSlider.SetSelRangeEnabled(false);
	}
}
//----------------------------------------------------------------------------
// AB ループ B の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopB()
{
	m_sound.ClearMarker();
	BOOL bLoop = !m_sound.IsABLoopB();
	m_sound.SetABLoopB(bLoop);
	m_toolBar.SetABLoopState(m_sound.IsABLoopA(), bLoop);
	m_menu.SetABLoopState(m_sound.IsABLoopA(), bLoop);

	if(m_sound.IsABLoopA() && bLoop) {
		// Ａループ：オン
		// Ｂループ：オン

		// 現在の再生位置にＡＢループのＢを設定
		QWORD time = m_sound.ChannelGetPosition();
		m_timeSlider.SetSelEnd((LONG)(time / 100000));
		m_sound.SetLoopPosB(time);

		// Ａの位置に再生位置を移す
		SetTime(m_sound.GetLoopPosA());
	}
	else if(m_sound.IsABLoopA() && !bLoop) {
		// Ａループ：オン
		// Ｂループ：オフ

		m_timeSlider.SetSelEnd((LONG)(m_sound.ChannelGetLength() / 100000));		
	}
	else if(!m_sound.IsABLoopA() && bLoop) {
		// Ａループ：オフ
		// Ｂループ：オン

		m_timeSlider.SetSelRangeEnabled(true);
		m_timeSlider.SetSelStart(0L);

		// 現在の再生位置にＡＢループのＢを設定
		QWORD time = m_sound.ChannelGetPosition();
		m_timeSlider.SetSelEnd((LONG)(time / 100000));
		m_sound.SetLoopPosB(time);

		SetTime(0);
	}
	else if(!m_sound.IsABLoopA() && !bLoop) {
		// Ａループ：オフ
		// Ｂループ：オフ

		m_timeSlider.SetSelStart(0L);
		m_timeSlider.SetSelEnd(0L);
		m_timeSlider.SetSelRangeEnabled(false);
	}
}
//----------------------------------------------------------------------------
// AB ループ B の設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopB_Sec(double dTime)
{
	if(dTime == m_sound.GetLoopPosA_sec()) return;
	if(dTime < m_sound.GetLoopPosA_sec()) return;
	QWORD time = m_sound.ChannelSeconds2Bytes(dTime);
	m_sound.ClearMarker();
	BOOL bLoop = m_sound.IsABLoopB();
	m_sound.SetABLoopB(bLoop);
	m_toolBar.SetABLoopState(m_sound.IsABLoopA(), bLoop);
	m_menu.SetABLoopState(m_sound.IsABLoopA(), bLoop);

	if(m_sound.IsABLoopA() && bLoop) {
		// Ａループ：オン
		// Ｂループ：オン

		m_timeSlider.SetSelEnd((LONG)(time / 100000));
		m_sound.SetLoopPosB(time);

		// Ａの位置に再生位置を移す
		SetTime(m_sound.GetLoopPosA());
	}
	else if(m_sound.IsABLoopA() && !bLoop) {
		// Ａループ：オン
		// Ｂループ：オフ

		m_timeSlider.SetSelEnd((LONG)(m_sound.ChannelGetLength() / 100000));		
	}
	else if(!m_sound.IsABLoopA() && bLoop) {
		// Ａループ：オフ
		// Ｂループ：オン

		m_timeSlider.SetSelRangeEnabled(true);
		m_timeSlider.SetSelStart(0L);

		m_timeSlider.SetSelEnd((LONG)(time / 100000));
		m_sound.SetLoopPosB(time);

		SetTime(0);
	}
	else if(!m_sound.IsABLoopA() && !bLoop) {
		// Ａループ：オフ
		// Ｂループ：オフ

		m_timeSlider.SetSelStart(0L);
		m_timeSlider.SetSelEnd(0L);
		m_timeSlider.SetSelRangeEnabled(false);
	}
}
//----------------------------------------------------------------------------
// AB ループ A の位置設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopASetting()
{
	CABLoopPosWnd dlg(*this, TRUE);
	dlg.exec();
}
//----------------------------------------------------------------------------
// AB ループ B の位置設定
//----------------------------------------------------------------------------
void CMainWnd::SetABLoopBSetting()
{
	CABLoopPosWnd dlg(*this, FALSE);
	dlg.exec();
}
//----------------------------------------------------------------------------
// 全曲ループ
//----------------------------------------------------------------------------
void CMainWnd::SetAllLoop(bool bAllLoop)
{
	m_menu.CheckItem(ID_ALOOP, bAllLoop ? MF_CHECKED : MF_UNCHECKED);
	m_toolBar.CheckButton(ID_ALOOP, bAllLoop);

	SetPreviousNextMenuState();
}
//----------------------------------------------------------------------------
// 全てのエフェクトを設定
//----------------------------------------------------------------------------
void CMainWnd::SetAllEffects()
{
	SetOnlyLeft(m_menu.IsItemChecked(ID_ONLYLEFT));
	SetOnlyRight(m_menu.IsItemChecked(ID_ONLYRIGHT));
	SetChangeLR(m_menu.IsItemChecked(ID_CHANGELR));
	SetMonoral(m_menu.IsItemChecked(ID_MONORAL));
	SetNormalize(m_menu.IsItemChecked(ID_NORMALIZE));
	SetVocalCancel(m_menu.IsItemChecked(ID_VOCALCANCEL));
	SetReverse(m_menu.IsItemChecked(ID_REVERSE));
	SetSpeed((double)(m_speedSlider.GetThumbPos()
		/ pow(10.0, m_speedLabel.GetDecimalDigit())));
	SetFreq((double)(m_freqSlider.GetThumbPos()
		/ pow(10.0, m_freqLabel.GetDecimalDigit())));
	SetPitch((double)(m_pitchSlider.GetThumbPos()
		/ pow(10.0, m_pitchLabel.GetDecimalDigit())));
	SetVolume((double)m_volumeSlider.GetThumbPos() / 10.0);
	SetPan(m_panSlider.GetThumbPos());
	SetEQ20(m_eq20Slider.GetThumbPos());
	SetEQ25(m_eq25Slider.GetThumbPos());
	SetEQ31_5(m_eq31_5Slider.GetThumbPos());
	SetEQ40(m_eq40Slider.GetThumbPos());
	SetEQ50(m_eq50Slider.GetThumbPos());
	SetEQ63(m_eq63Slider.GetThumbPos());
	SetEQ80(m_eq80Slider.GetThumbPos());
	SetEQ100(m_eq100Slider.GetThumbPos());
	SetEQ125(m_eq125Slider.GetThumbPos());
	SetEQ160(m_eq160Slider.GetThumbPos());
	SetEQ200(m_eq200Slider.GetThumbPos());
	SetEQ250(m_eq250Slider.GetThumbPos());
	SetEQ315(m_eq315Slider.GetThumbPos());
	SetEQ400(m_eq400Slider.GetThumbPos());
	SetEQ500(m_eq500Slider.GetThumbPos());
	SetEQ630(m_eq630Slider.GetThumbPos());
	SetEQ800(m_eq800Slider.GetThumbPos());
	SetEQ1K(m_eq1kSlider.GetThumbPos());
	SetEQ1_25K(m_eq1_25kSlider.GetThumbPos());
	SetEQ1_6K(m_eq1_6kSlider.GetThumbPos());
	SetEQ2K(m_eq2kSlider.GetThumbPos());
	SetEQ2_5K(m_eq2_5kSlider.GetThumbPos());
	SetEQ3_15K(m_eq3_15kSlider.GetThumbPos());
	SetEQ4K(m_eq4kSlider.GetThumbPos());
	SetEQ5K(m_eq5kSlider.GetThumbPos());
	SetEQ6_3K(m_eq6_3kSlider.GetThumbPos());
	SetEQ8K(m_eq8kSlider.GetThumbPos());
	SetEQ10K(m_eq10kSlider.GetThumbPos());
	SetEQ12_5K(m_eq12_5kSlider.GetThumbPos());
	SetEQ16K(m_eq16kSlider.GetThumbPos());
	SetEQ20K(m_eq20kSlider.GetThumbPos());
	SetReverb(bReverb);
	Set3DReverb(b3DReverb);
	SetDelay(bDelay);
}
//----------------------------------------------------------------------------
// 連続再生
//----------------------------------------------------------------------------
void CMainWnd::SetContinue(bool bContinue)
{
	m_menu.CheckItem(ID_CONTINUE, bContinue ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 再生速度の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetSpeedVisible(bool bSpeedVisible)
{
	int nCmdShow = bSpeedVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bSpeedVisible ? MF_CHECKED : MF_UNCHECKED;
	if(bSpeedVisible
		|| m_menu.IsItemChecked(ID_FREQ)
		|| m_menu.IsItemChecked(ID_PITCH))
		speedGroupBox->show();
	else speedGroupBox->hide();
	m_speedLabel.Show(nCmdShow);
	m_speedSlider.Show(nCmdShow);
	m_menu.CheckItem(ID_SPEED, uCheck);
}
//----------------------------------------------------------------------------
// 再生周波数の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetFreqVisible(bool bFreqVisible)
{
	int nCmdShow = bFreqVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bFreqVisible ? MF_CHECKED : MF_UNCHECKED;
	if(m_menu.IsItemChecked(ID_SPEED)
		|| bFreqVisible
		|| m_menu.IsItemChecked(ID_PITCH))
		speedGroupBox->show();
	else speedGroupBox->hide();
	m_freqLabel.Show(nCmdShow);
	m_freqSlider.Show(nCmdShow);
	m_menu.CheckItem(ID_FREQ, uCheck);
}
//----------------------------------------------------------------------------
// 音程の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPitchVisible(bool bPitchVisible)
{
	int nCmdShow = bPitchVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bPitchVisible ? MF_CHECKED : MF_UNCHECKED;
	if(m_menu.IsItemChecked(ID_SPEED)
		|| m_menu.IsItemChecked(ID_FREQ)
		|| bPitchVisible)
		speedGroupBox->show();
	else speedGroupBox->hide();
	m_pitchLabel.Show(nCmdShow);
	m_pitchSlider.Show(nCmdShow);
	m_menu.CheckItem(ID_PITCH, uCheck);
}
//----------------------------------------------------------------------------
// 音量の表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetVolumeVisible(bool bVolumeVisible)
{
	int nCmdShow = bVolumeVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bVolumeVisible ? MF_CHECKED : MF_UNCHECKED;
	if(bVolumeVisible || m_menu.IsItemChecked(ID_PAN))
		volumeGroupBox->show();
	else volumeGroupBox->hide();
	m_volumeLabel.Show(nCmdShow);
	m_volumeSlider.Show(nCmdShow);
	m_menu.CheckItem(ID_VOLUME, uCheck);
}
//----------------------------------------------------------------------------
// パンの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPanVisible(bool bPanVisible)
{
	int nCmdShow = bPanVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bPanVisible ? MF_CHECKED : MF_UNCHECKED;
	if(m_menu.IsItemChecked(ID_VOLUME) || bPanVisible) volumeGroupBox->show();
	else volumeGroupBox->hide();
	m_panLabel.Show(nCmdShow);
	m_panSlider.Show(nCmdShow);
	m_menu.CheckItem(ID_PAN, uCheck);
}
//----------------------------------------------------------------------------
// 回数ループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetCountLoop()
{
	if(bMarkerPlay) {
		CCountLoopWnd_MainWnd dlg(*this);
		dlg.exec();
	}
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
	m_menu.CheckItem(ID_COUNTLOOP, bCountLoop ? MF_CHECKED : MF_UNCHECKED);
	if(bCountLoop) Head();
}
//----------------------------------------------------------------------------
// マーカーのクリア
//----------------------------------------------------------------------------
void CSound::ClearMarker()
{
	m_arrayMarker.clear();
}
//----------------------------------------------------------------------------
// イコライザ ( 20Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ20(LONG lEQ20)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ20(20, 0.7f, (float)lEQ20);
}
//----------------------------------------------------------------------------
// イコライザ ( 25Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ25(LONG lEQ25)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ25(25, 0.7f, (float)lEQ25);
}
//----------------------------------------------------------------------------
// イコライザ ( 31.5Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ31_5(LONG lEQ31_5)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ31_5(31.5, 0.7f, (float)lEQ31_5);
}
//----------------------------------------------------------------------------
// イコライザ ( 40Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ40(LONG lEQ40)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ40(40, 0.7f, (float)lEQ40);
}
//----------------------------------------------------------------------------
// イコライザ ( 50Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ50(LONG lEQ50)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ50(50, 0.7f, (float)lEQ50);
}
//----------------------------------------------------------------------------
// イコライザ ( 63Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ63(LONG lEQ63)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ63(63, 0.7f, (float)lEQ63);
}
//----------------------------------------------------------------------------
// イコライザ ( 80Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ80(LONG lEQ80)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ80(80, 0.7f, (float)lEQ80);
}
//----------------------------------------------------------------------------
// イコライザ ( 100Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ100(LONG lEQ100)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ100(100, 0.7f, (float)lEQ100);
}
//----------------------------------------------------------------------------
// イコライザ ( 125Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ125(LONG lEQ125)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ125(125, 0.7f, (float)lEQ125);
}
//----------------------------------------------------------------------------
// イコライザ ( 160Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ160(LONG lEQ160)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ160(160, 0.7f, (float)lEQ160);
}
//----------------------------------------------------------------------------
// イコライザ ( 200Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ200(LONG lEQ200)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ200(200, 0.7f, (float)lEQ200);
}
//----------------------------------------------------------------------------
// イコライザ ( 250Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ250(LONG lEQ250)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ250(250, 0.7f, (float)lEQ250);
}
//----------------------------------------------------------------------------
// イコライザ ( 315Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ315(LONG lEQ315)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ315(315, 0.7f, (float)lEQ315);
}
//----------------------------------------------------------------------------
// イコライザ ( 400Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ400(LONG lEQ400)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ400(400, 0.7f, (float)lEQ400);
}
//----------------------------------------------------------------------------
// イコライザ ( 500Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ500(LONG lEQ500)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ500(500, 0.7f, (float)lEQ500);
}
//----------------------------------------------------------------------------
// イコライザ ( 630Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ630(LONG lEQ630)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ630(630, 0.7f, (float)lEQ630);
}
//----------------------------------------------------------------------------
// イコライザ ( 800Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ800(LONG lEQ800)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ800(800, 0.7f, (float)lEQ800);
}
//----------------------------------------------------------------------------
// イコライザ ( 1KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1K(LONG lEQ1K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ1K(1000, 0.7f, (float)lEQ1K);
}
//----------------------------------------------------------------------------
// イコライザ ( 1.25KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1_25K(LONG lEQ1_25K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ1_25K(1250, 0.7f, (float)lEQ1_25K);
}
//----------------------------------------------------------------------------
// イコライザ ( 1.6KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1_6K(LONG lEQ1_6K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ1_6K(1600, 0.7f, (float)lEQ1_6K);
}
//----------------------------------------------------------------------------
// イコライザ ( 2KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ2K(LONG lEQ2K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ2K(2000, 0.7f, (float)lEQ2K);
}
//----------------------------------------------------------------------------
// イコライザ ( 2.5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ2_5K(LONG lEQ2_5K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ2_5K(2500, 0.7f, (float)lEQ2_5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 3.15KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ3_15K(LONG lEQ3_15K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ3_15K(3150, 0.7f, (float)lEQ3_15K);
}
//----------------------------------------------------------------------------
// イコライザ ( 4KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ4K(LONG lEQ4K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ4K(4000, 0.7f, (float)lEQ4K);
}
//----------------------------------------------------------------------------
// イコライザ ( 5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ5K(LONG lEQ5K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ5K(5000, 0.7f, (float)lEQ5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 6.3KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ6_3K(LONG lEQ6_3K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ6_3K(6300, 0.7f, (float)lEQ6_3K);
}
//----------------------------------------------------------------------------
// イコライザ ( 8KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ8K(LONG lEQ8K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ8K(8000, 0.7f, (float)lEQ8K);
}
//----------------------------------------------------------------------------
// イコライザ ( 10KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ10K(LONG lEQ10K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ10K(10000, 0.7f, (float)lEQ10K);
}
//----------------------------------------------------------------------------
// イコライザ ( 12.5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ12_5K(LONG lEQ12_5K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ12_5K(12500, 0.7f, (float)lEQ12_5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 16KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ16K(LONG lEQ16K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ16K(16000, 0.7f, (float)lEQ16K);
}
//----------------------------------------------------------------------------
// イコライザ ( 20KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ20K(LONG lEQ20K)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetEQ20K(20000, 0.7f, (float)lEQ20K);
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
	m_eq20Label.SetEQ(lEQ20);
	m_eq25Label.SetEQ(lEQ25);
	m_eq31_5Label.SetEQ(lEQ31_5);
	m_eq40Label.SetEQ(lEQ40);
	m_eq50Label.SetEQ(lEQ50);
	m_eq63Label.SetEQ(lEQ63);
	m_eq80Label.SetEQ(lEQ80);
	m_eq100Label.SetEQ(lEQ100);
	m_eq125Label.SetEQ(lEQ125);
	m_eq160Label.SetEQ(lEQ160);
	m_eq200Label.SetEQ(lEQ200);
	m_eq250Label.SetEQ(lEQ250);
	m_eq315Label.SetEQ(lEQ315);
	m_eq400Label.SetEQ(lEQ400);
	m_eq500Label.SetEQ(lEQ500);
	m_eq630Label.SetEQ(lEQ630);
	m_eq800Label.SetEQ(lEQ800);
	m_eq1kLabel.SetEQ(lEQ1K);
	m_eq1_25kLabel.SetEQ(lEQ1_25K);
	m_eq1_6kLabel.SetEQ(lEQ1_6K);
	m_eq2kLabel.SetEQ(lEQ2K);
	m_eq2_5kLabel.SetEQ(lEQ2_5K);
	m_eq3_15kLabel.SetEQ(lEQ3_15K);
	m_eq4kLabel.SetEQ(lEQ4K);
	m_eq5kLabel.SetEQ(lEQ5K);
	m_eq6_3kLabel.SetEQ(lEQ6_3K);
	m_eq8kLabel.SetEQ(lEQ8K);
	m_eq10kLabel.SetEQ(lEQ10K);
	m_eq12_5kLabel.SetEQ(lEQ12_5K);
	m_eq16kLabel.SetEQ(lEQ16K);
	m_eq20kLabel.SetEQ(lEQ20K);
}
//----------------------------------------------------------------------------
// グラフィックイコライザの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQVisible(bool bEQVisible)
{
	int nCmdShow = bEQVisible ? SW_SHOW : SW_HIDE;
	UINT uCheck = bEQVisible ? MF_CHECKED : MF_UNCHECKED;
	m_eq20Label.Show(m_menu.IsItemChecked(ID_EQ20) ? nCmdShow : SW_HIDE);
	m_eq20Slider.Show(m_menu.IsItemChecked(ID_EQ20) ? nCmdShow : SW_HIDE);
	m_eq25Label.Show(m_menu.IsItemChecked(ID_EQ25) ? nCmdShow : SW_HIDE);
	m_eq25Slider.Show(m_menu.IsItemChecked(ID_EQ25) ? nCmdShow : SW_HIDE);
	m_eq31_5Label.Show(m_menu.IsItemChecked(ID_EQ31_5) ? nCmdShow : SW_HIDE);
	m_eq31_5Slider.Show(m_menu.IsItemChecked(ID_EQ31_5) ? nCmdShow : SW_HIDE);
	m_eq40Label.Show(m_menu.IsItemChecked(ID_EQ40) ? nCmdShow : SW_HIDE);
	m_eq40Slider.Show(m_menu.IsItemChecked(ID_EQ40) ? nCmdShow : SW_HIDE);
	m_eq50Label.Show(m_menu.IsItemChecked(ID_EQ50) ? nCmdShow : SW_HIDE);
	m_eq50Slider.Show(m_menu.IsItemChecked(ID_EQ50) ? nCmdShow : SW_HIDE);
	m_eq63Label.Show(m_menu.IsItemChecked(ID_EQ63) ? nCmdShow : SW_HIDE);
	m_eq63Slider.Show(m_menu.IsItemChecked(ID_EQ63) ? nCmdShow : SW_HIDE);
	m_eq80Label.Show(m_menu.IsItemChecked(ID_EQ80) ? nCmdShow : SW_HIDE);
	m_eq80Slider.Show(m_menu.IsItemChecked(ID_EQ80) ? nCmdShow : SW_HIDE);
	m_eq100Label.Show(m_menu.IsItemChecked(ID_EQ100) ? nCmdShow : SW_HIDE);
	m_eq100Slider.Show(m_menu.IsItemChecked(ID_EQ100) ? nCmdShow : SW_HIDE);
	m_eq125Label.Show(m_menu.IsItemChecked(ID_EQ125) ? nCmdShow : SW_HIDE);
	m_eq125Slider.Show(m_menu.IsItemChecked(ID_EQ125) ? nCmdShow : SW_HIDE);
	m_eq160Label.Show(m_menu.IsItemChecked(ID_EQ160) ? nCmdShow : SW_HIDE);
	m_eq160Slider.Show(m_menu.IsItemChecked(ID_EQ160) ? nCmdShow : SW_HIDE);
	m_eq200Label.Show(m_menu.IsItemChecked(ID_EQ200) ? nCmdShow : SW_HIDE);
	m_eq200Slider.Show(m_menu.IsItemChecked(ID_EQ200) ? nCmdShow : SW_HIDE);
	m_eq250Label.Show(m_menu.IsItemChecked(ID_EQ250) ? nCmdShow : SW_HIDE);
	m_eq250Slider.Show(m_menu.IsItemChecked(ID_EQ250) ? nCmdShow : SW_HIDE);
	m_eq315Label.Show(m_menu.IsItemChecked(ID_EQ315) ? nCmdShow : SW_HIDE);
	m_eq315Slider.Show(m_menu.IsItemChecked(ID_EQ315) ? nCmdShow : SW_HIDE);
	m_eq400Label.Show(m_menu.IsItemChecked(ID_EQ400) ? nCmdShow : SW_HIDE);
	m_eq400Slider.Show(m_menu.IsItemChecked(ID_EQ400) ? nCmdShow : SW_HIDE);
	m_eq500Label.Show(m_menu.IsItemChecked(ID_EQ500) ? nCmdShow : SW_HIDE);
	m_eq500Slider.Show(m_menu.IsItemChecked(ID_EQ500) ? nCmdShow : SW_HIDE);
	m_eq630Label.Show(m_menu.IsItemChecked(ID_EQ630) ? nCmdShow : SW_HIDE);
	m_eq630Slider.Show(m_menu.IsItemChecked(ID_EQ630) ? nCmdShow : SW_HIDE);
	m_eq800Label.Show(m_menu.IsItemChecked(ID_EQ800) ? nCmdShow : SW_HIDE);
	m_eq800Slider.Show(m_menu.IsItemChecked(ID_EQ800) ? nCmdShow : SW_HIDE);
	m_eq1kLabel.Show(m_menu.IsItemChecked(ID_EQ1K) ? nCmdShow : SW_HIDE);
	m_eq1kSlider.Show(m_menu.IsItemChecked(ID_EQ1K) ? nCmdShow : SW_HIDE);
	m_eq1_25kLabel.Show(m_menu.IsItemChecked(ID_EQ1_25K) ? nCmdShow : SW_HIDE);
	m_eq1_25kSlider.Show(m_menu.IsItemChecked(ID_EQ1_25K) ? nCmdShow : SW_HIDE);
	m_eq1_6kLabel.Show(m_menu.IsItemChecked(ID_EQ1_6K) ? nCmdShow : SW_HIDE);
	m_eq1_6kSlider.Show(m_menu.IsItemChecked(ID_EQ1_6K) ? nCmdShow : SW_HIDE);
	m_eq2kLabel.Show(m_menu.IsItemChecked(ID_EQ2K) ? nCmdShow : SW_HIDE);
	m_eq2kSlider.Show(m_menu.IsItemChecked(ID_EQ2K) ? nCmdShow : SW_HIDE);
	m_eq2_5kLabel.Show(m_menu.IsItemChecked(ID_EQ2_5K) ? nCmdShow : SW_HIDE);
	m_eq2_5kSlider.Show(m_menu.IsItemChecked(ID_EQ2_5K) ? nCmdShow : SW_HIDE);
	m_eq3_15kLabel.Show(m_menu.IsItemChecked(ID_EQ3_15K) ? nCmdShow : SW_HIDE);
	m_eq3_15kSlider.Show(m_menu.IsItemChecked(ID_EQ3_15K) ? nCmdShow : SW_HIDE);
	m_eq4kLabel.Show(m_menu.IsItemChecked(ID_EQ4K) ? nCmdShow : SW_HIDE);
	m_eq4kSlider.Show(m_menu.IsItemChecked(ID_EQ4K) ? nCmdShow : SW_HIDE);
	m_eq5kLabel.Show(m_menu.IsItemChecked(ID_EQ5K) ? nCmdShow : SW_HIDE);
	m_eq5kSlider.Show(m_menu.IsItemChecked(ID_EQ5K) ? nCmdShow : SW_HIDE);
	m_eq6_3kLabel.Show(m_menu.IsItemChecked(ID_EQ6_3K) ? nCmdShow : SW_HIDE);
	m_eq6_3kSlider.Show(m_menu.IsItemChecked(ID_EQ6_3K) ? nCmdShow : SW_HIDE);
	m_eq8kLabel.Show(m_menu.IsItemChecked(ID_EQ8K) ? nCmdShow : SW_HIDE);
	m_eq8kSlider.Show(m_menu.IsItemChecked(ID_EQ8K) ? nCmdShow : SW_HIDE);
	m_eq10kLabel.Show(m_menu.IsItemChecked(ID_EQ10K) ? nCmdShow : SW_HIDE);
	m_eq10kSlider.Show(m_menu.IsItemChecked(ID_EQ10K) ? nCmdShow : SW_HIDE);
	m_eq12_5kLabel.Show(m_menu.IsItemChecked(ID_EQ12_5K) ? nCmdShow : SW_HIDE);
	m_eq12_5kSlider.Show(m_menu.IsItemChecked(ID_EQ12_5K) ? nCmdShow : SW_HIDE);
	m_eq16kLabel.Show(m_menu.IsItemChecked(ID_EQ16K) ? nCmdShow : SW_HIDE);
	m_eq16kSlider.Show(m_menu.IsItemChecked(ID_EQ16K) ? nCmdShow : SW_HIDE);
	m_eq20kLabel.Show(m_menu.IsItemChecked(ID_EQ20K) ? nCmdShow : SW_HIDE);
	m_eq20kSlider.Show(m_menu.IsItemChecked(ID_EQ20K) ? nCmdShow : SW_HIDE);
	m_menu.CheckItem(ID_EQ, uCheck);
}
//----------------------------------------------------------------------------
// マーカー追加時にループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetInstantLoop()
{
	bInstantLoop = !bInstantLoop;
	m_menu.CheckItem(ID_INSTANTLOOP, bInstantLoop ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// マーカー位置変更時に再生位置変更の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPositionAuto()
{
	bSetPositionAuto = !bSetPositionAuto;
	m_menu.CheckItem(ID_SETPOSITIONAUTO, bSetPositionAuto
		? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// マーカーの設定
//----------------------------------------------------------------------------
void CMainWnd::SetMarkerPlay()
{
	bMarkerPlay = !bMarkerPlay;
	m_sound.SetABLoopA(bMarkerPlay);
	m_sound.SetABLoopB(bMarkerPlay);
	m_toolBar.SetMarkerPlayState(bMarkerPlay);
	SetCountLoop(FALSE, 0);
	m_menu.EnableItem(ID_COUNTLOOP, bMarkerPlay ? MFS_ENABLED : MFS_DISABLED);
	m_menu.EnableItem(ID_SLOOP, bMarkerPlay ? MFS_DISABLED : MFS_ENABLED);
	m_menu.EnableItem(ID_ALOOP, bMarkerPlay ? MFS_DISABLED : MFS_ENABLED);
	m_menu.EnableItem(ID_RANDOM, bMarkerPlay ? MFS_DISABLED : MFS_ENABLED);
	m_menu.CheckItem(ID_MARKERPLAY, bMarkerPlay ? MF_CHECKED : MF_UNCHECKED);
	SetPreviousNextMenuState();

	if(!bMarkerPlay) {
		m_timeSlider.SetSelStart(0);
		m_timeSlider.SetSelEnd(0);
	}
	m_timeSlider.SetSelRangeEnabled(bMarkerPlay ? true : false);
	if(bMarkerPlay) {
		QWORD qwTime = m_sound.ChannelGetPosition();
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
		QWORD length = m_sound.ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0) {
			if(0 <= qwTime && qwTime < arrayMarker[0]) {
					bDone = TRUE;
					m_timeSlider.SetSelStart(0);
					m_timeSlider.SetSelEnd(arrayMarker[0] / 100000);
					m_sound.SetLoopPosA(0);
					m_sound.SetLoopPosB(arrayMarker[0]);
			}
		}
		else {
			bDone = TRUE;
			m_timeSlider.SetSelStart(0);
			m_timeSlider.SetSelEnd(length / 100000);
			m_sound.SetLoopPosA(0);
			m_sound.SetLoopPosB(length);
		}

		if(!bDone) {
			for(int i = 0; i < max; i++) {
				if(i + 1 < max) {
					if(arrayMarker[i] <= qwTime && qwTime < arrayMarker[i + 1])
					{
						bDone = TRUE;
						m_timeSlider.SetSelStart(arrayMarker[i] / 100000);
						m_timeSlider.SetSelEnd(arrayMarker[i + 1] / 100000);
						m_sound.SetLoopPosA(arrayMarker[i]);
						m_sound.SetLoopPosB(arrayMarker[i + 1]);
						break;
					}
				}
			}
		}

		if(!bDone) {
			if(arrayMarker[max - 1] <= qwTime && qwTime <= length) {
				bDone = TRUE;
				m_timeSlider.SetSelStart(arrayMarker[max - 1] / 100000);
				m_timeSlider.SetSelEnd(length / 100000);
				m_sound.SetLoopPosA(arrayMarker[max - 1]);
				m_sound.SetLoopPosB(length);
			}
		}
	}
}
//----------------------------------------------------------------------------
// 左右入れ替え
//----------------------------------------------------------------------------
void CMainWnd::SetChangeLR()
{
	BOOL bChangeLR = !m_menu.IsItemChecked(ID_CHANGELR);
	if(bChangeLR) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyRight(false);
		SetOnlyLeft(false);
	}
	m_sound.SetChangeLR(bChangeLR);
	m_menu.CheckItem(ID_CHANGELR, bChangeLR ? MF_CHECKED : MF_UNCHECKED);
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
	m_sound.SetChangeLR(bChangeLR);
	m_menu.CheckItem(ID_CHANGELR, bChangeLR ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 聴覚トレーニング
//----------------------------------------------------------------------------
void CMainWnd::SetEarTraining()
{
	BOOL bEarTraining = !m_menu.IsItemChecked(ID_EARTRAINING);
	m_menu.CheckItem(ID_EARTRAINING, bEarTraining ? MF_CHECKED : MF_UNCHECKED);
	if(bEarTraining) {
		if(m_menu.IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu.IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu.IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		OnTimer(IDT_EARTRAINING);
		SetTimer(IDT_EARTRAINING, 3000);
	}
	else {
		KillTimer(IDT_EARTRAINING);
		m_menu.OnEQFlatMenuSelected();
		m_panLabel.SetPan(0);
	}
}
//----------------------------------------------------------------------------
// 聴覚トレーニング
//----------------------------------------------------------------------------
void CMainWnd::SetEarTraining(BOOL bEarTraining)
{
	m_menu.CheckItem(ID_EARTRAINING, bEarTraining ? MF_CHECKED : MF_UNCHECKED);
	if(bEarTraining) {
		if(m_menu.IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu.IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu.IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		OnTimer(IDT_EARTRAINING);
		SetTimer(IDT_EARTRAINING, 3000);
	}
	else {
		KillTimer(IDT_EARTRAINING);
		m_menu.OnEQFlatMenuSelected();
	}
}
//----------------------------------------------------------------------------
// ノーマライズ
//----------------------------------------------------------------------------
void CMainWnd::SetNormalize()
{
	BOOL bNormalize = !m_menu.IsItemChecked(ID_NORMALIZE);
	m_sound.SetNormalize(bNormalize);
	m_menu.CheckItem(ID_NORMALIZE, bNormalize ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ノーマライズ
//----------------------------------------------------------------------------
void CMainWnd::SetNormalize(BOOL bNormalize)
{
	m_sound.SetNormalize(bNormalize);
	m_menu.CheckItem(ID_NORMALIZE, bNormalize ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 歌へたモード
//----------------------------------------------------------------------------
void CMainWnd::SetNoSense()
{
	BOOL bNoSense = !m_menu.IsItemChecked(ID_NOSENSE);
	m_menu.CheckItem(ID_NOSENSE, bNoSense ? MF_CHECKED : MF_UNCHECKED);
	if(bNoSense) {
		if(m_menu.IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu.IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu.IsItemChecked(ID_BASSCOPY)) m_menu.OnBassCopyMenuSelected();
		if(m_menu.IsItemChecked(ID_CYMBALCOPY))
			m_menu.OnDrumsCopyMenuSelected();
		m_nLastDecimalDigit_pitch = m_pitchSlider.GetDecimalDigit();
		m_nLastDecimalDigit_speed = m_speedSlider.GetDecimalDigit();
		m_menu.OnSetPitchDecimal2MenuSelected();
		m_menu.OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel.SetPitch(0.0);
		m_speedLabel.SetSpeed(100.0);
		SetTimer(IDT_NOSENSE, 80);
	}
	else {
		KillTimer(IDT_NOSENSE);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		if(m_nLastDecimalDigit_pitch == 0)
			m_menu.OnSetPitchDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 1)
			m_menu.OnSetPitchDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 2)
			m_menu.OnSetPitchDecimal2MenuSelected();
		if(m_nLastDecimalDigit_speed == 0)
			m_menu.OnSetSpeedDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_speed == 1)
			m_menu.OnSetSpeedDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_speed == 2)
			m_menu.OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel.SetPitch(0.0);
		m_speedLabel.SetSpeed(100.0);
	}
}
//----------------------------------------------------------------------------
// 歌へたモード
//----------------------------------------------------------------------------
void CMainWnd::SetNoSense(BOOL bNoSense)
{
	m_menu.CheckItem(ID_NOSENSE, bNoSense ? MF_CHECKED : MF_UNCHECKED);
	if(bNoSense) {
		if(m_menu.IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu.IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu.IsItemChecked(ID_BASSCOPY)) m_menu.OnBassCopyMenuSelected();
		if(m_menu.IsItemChecked(ID_CYMBALCOPY))
			m_menu.OnDrumsCopyMenuSelected();
		m_nLastDecimalDigit_pitch = m_pitchSlider.GetDecimalDigit();
		m_nLastDecimalDigit_speed = m_speedSlider.GetDecimalDigit();
		m_menu.OnSetPitchDecimal2MenuSelected();
		m_menu.OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel.SetPitch(0.0);
		m_speedLabel.SetSpeed(100.0);
		SetTimer(IDT_NOSENSE, 80);
	}
	else {
		KillTimer(IDT_NOSENSE);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		if(m_nLastDecimalDigit_pitch == 0)
			m_menu.OnSetPitchDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 1)
			m_menu.OnSetPitchDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_pitch == 2)
			m_menu.OnSetPitchDecimal2MenuSelected();
		if(m_nLastDecimalDigit_speed == 0)
			m_menu.OnSetSpeedDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_speed == 1)
			m_menu.OnSetSpeedDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_speed == 2)
			m_menu.OnSetSpeedDecimal2MenuSelected();
		m_pitchLabel.SetPitch(0.0);
		m_speedLabel.SetSpeed(100.0);
	}
}
//----------------------------------------------------------------------------
// 次のマーカーへ
//----------------------------------------------------------------------------
void CMainWnd::SetNextMarker()
{
	if(bMarkerPlay) {
		QWORD qwTime = m_sound.GetLoopPosA();
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
		QWORD length = m_sound.ChannelGetLength();
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
	BOOL bOnlyLeft = !m_menu.IsItemChecked(ID_ONLYLEFT);
	if(bOnlyLeft) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound.SetOnlyLeft(bOnlyLeft);
	m_menu.CheckItem(ID_ONLYLEFT, bOnlyLeft ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 左のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyLeft(BOOL bOnlyLeft)
{
	if(bOnlyLeft) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetChangeLR(false);
		SetOnlyRight(false);
	}
	m_sound.SetOnlyLeft(bOnlyLeft);
	m_menu.CheckItem(ID_ONLYLEFT, bOnlyLeft ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 右のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyRight()
{
	BOOL bOnlyRight = !m_menu.IsItemChecked(ID_ONLYRIGHT);
	if(bOnlyRight) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetChangeLR(false);
	}
	m_sound.SetOnlyRight(bOnlyRight);
	m_menu.CheckItem(ID_ONLYRIGHT, bOnlyRight ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 右のみ再生
//----------------------------------------------------------------------------
void CMainWnd::SetOnlyRight(BOOL bOnlyRight)
{
	if(bOnlyRight) {
		SetMonoral(false);
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetChangeLR(false);
	}
	m_sound.SetOnlyRight(bOnlyRight);
	m_menu.CheckItem(ID_ONLYRIGHT, bOnlyRight ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 前へ・次へメニューの表示状態を設定
//----------------------------------------------------------------------------
void CMainWnd::SetPreviousNextMenuState()
{
	if(m_sound.GetCurFileNum() <= 0) return;

	// 前へメニューの使用可・不可を設定
	if(m_menu.IsItemChecked(ID_RANDOM)) {
		if(!m_menu.IsItemChecked(ID_ALOOP)
			&& m_arrayList[nCurPlayTab]->GetMaxPlayOrder() == 1)
			m_menu.EnableItem(ID_PREV, MFS_DISABLED);
		else m_menu.EnableItem(ID_PREV, MFS_ENABLED);
	}
	else {
		if(!bMarkerPlay && !m_menu.IsItemChecked(ID_ALOOP)
			&& m_sound.GetCurFileNum() == 1)
			m_menu.EnableItem(ID_PREV, MFS_DISABLED);
		else m_menu.EnableItem(ID_PREV, MFS_ENABLED);
	}

	// 次へメニューの使用可・不可を設定
	if(m_menu.IsItemChecked(ID_RANDOM)) {
		if(!m_menu.IsItemChecked(ID_ALOOP)
			&& m_arrayList[nCurPlayTab]->GetMaxPlayOrder()
			== m_arrayList[nCurPlayTab]->GetItemCount())
			m_menu.EnableItem(ID_NEXT, MFS_DISABLED);
		else m_menu.EnableItem(ID_NEXT, MFS_ENABLED);
	}
	else {
		if(!bMarkerPlay && !m_menu.IsItemChecked(ID_ALOOP)
			&& m_sound.GetCurFileNum()
			== m_arrayList[nCurPlayTab]->GetItemCount())
			m_menu.EnableItem(ID_NEXT, MFS_DISABLED);
		else m_menu.EnableItem(ID_NEXT, MFS_ENABLED);
	}
}
//----------------------------------------------------------------------------
// 前のマーカーへ
//----------------------------------------------------------------------------
void CMainWnd::SetPrevMarker()
{
	if(bMarkerPlay) {
		QWORD qwTime = m_sound.GetLoopPosA();
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
		QWORD length = m_sound.ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0 && qwTime == arrayMarker[0]) {
			bDone = TRUE;
			m_timeSlider.SetSelStart(0);
			m_timeSlider.SetSelEnd(arrayMarker[0] / 100000);
			SetTime(0);
			return;
		}

		for(int i = 1; i < max; i++) {
			if(qwTime == arrayMarker[i]) {
				bDone = TRUE;
				m_timeSlider.SetSelStart(arrayMarker[i - 1] / 100000);
				m_timeSlider.SetSelEnd(arrayMarker[i] / 100000);
				SetTime(arrayMarker[i - 1]);
				return;
			}
		}
	}
}
//----------------------------------------------------------------------------
// ランダム再生の設定
//----------------------------------------------------------------------------
void CMainWnd::SetRandom(bool bRandom)
{
	m_menu.CheckItem(ID_RANDOM, bRandom ? MF_CHECKED : MF_UNCHECKED);
	m_toolBar.CheckButton(ID_RANDOM, bRandom);

	m_arrayList[nCurPlayTab]->ClearPlayOrder();
	if(bRandom)
		m_arrayList[nCurPlayTab]->SetPlayOrder(m_sound.GetCurFileNum()-1);

	SetPreviousNextMenuState();
}
//----------------------------------------------------------------------------
// リバーブをかける
//----------------------------------------------------------------------------
void CMainWnd::SetReverb(BOOL bReverb)
{
	this->bReverb = bReverb;
	m_sound.SetReverb(bReverb);
}
//----------------------------------------------------------------------------
// ３Ｄリバーブをかける
//----------------------------------------------------------------------------
void CMainWnd::Set3DReverb(BOOL b3DReverb)
{
	this->b3DReverb = b3DReverb;
	m_sound.Set3DReverb(b3DReverb);
}
//----------------------------------------------------------------------------
// ディレイをかける
//----------------------------------------------------------------------------
void CMainWnd::SetDelay(BOOL bDelay)
{
	this->bDelay = bDelay;
	m_sound.SetDelay(bDelay);
}
//----------------------------------------------------------------------------
// 電池切れ
//----------------------------------------------------------------------------
void CMainWnd::SetLowBattery()
{
	BOOL bLowBattery = !m_menu.IsItemChecked(ID_LOWBATTERY);
	m_menu.CheckItem(ID_LOWBATTERY, bLowBattery ? MF_CHECKED : MF_UNCHECKED);
	if(bLowBattery) {
		if(m_menu.IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu.IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_nLastDecimalDigit_freq = m_freqSlider.GetDecimalDigit();
		m_menu.OnSetFreqDecimal2MenuSelected();
		m_menu.OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_LOWBATTERY, 20);
	}
	else {
		KillTimer(IDT_LOWBATTERY);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_menu.OnEQFlatMenuSelected();
		if(m_nLastDecimalDigit_freq == 0)
			m_menu.OnSetFreqDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_freq == 1)
			m_menu.OnSetFreqDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_freq == 2)
			m_menu.OnSetFreqDecimal2MenuSelected();
		m_freqLabel.SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// 電池切れ
//----------------------------------------------------------------------------
void CMainWnd::SetLowBattery(BOOL bLowBattery)
{
	m_menu.CheckItem(ID_LOWBATTERY, bLowBattery ? MF_CHECKED : MF_UNCHECKED);
	if(bLowBattery) {
		if(m_menu.IsItemChecked(ID_RECORD)) SetRecord(FALSE);
		if(m_menu.IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_nLastDecimalDigit_freq = m_freqSlider.GetDecimalDigit();
		m_menu.OnSetFreqDecimal2MenuSelected();
		m_menu.OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_LOWBATTERY, 20);
	}
	else {
		KillTimer(IDT_LOWBATTERY);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_menu.OnEQFlatMenuSelected();
		if(m_nLastDecimalDigit_freq == 0)
			m_menu.OnSetFreqDecimal0MenuSelected();
		else if(m_nLastDecimalDigit_freq == 1)
			m_menu.OnSetFreqDecimal1MenuSelected();
		else if(m_nLastDecimalDigit_freq == 2)
			m_menu.OnSetFreqDecimal2MenuSelected();
		m_freqLabel.SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// 逆回転再生
//----------------------------------------------------------------------------
void CMainWnd::SetReverse()
{
	BOOL bReverse = !m_menu.IsItemChecked(ID_REVERSE);
	if(bReverse) {
		if(m_sound.IsABLoopA()) SetABLoopA();
		if(m_sound.IsABLoopB()) SetABLoopB();
	}
	m_sound.SetReverse(bReverse);
	m_menu.CheckItem(ID_REVERSE, bReverse ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 逆回転再生
//----------------------------------------------------------------------------
void CMainWnd::SetReverse(BOOL bReverse)
{
	if(bReverse) {
		if(m_sound.IsABLoopA()) SetABLoopA();
		if(m_sound.IsABLoopB()) SetABLoopB();
	}
	m_sound.SetReverse(bReverse);
	m_menu.CheckItem(ID_REVERSE, bReverse ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 古びたレコード再生
//----------------------------------------------------------------------------
void CMainWnd::SetRecord()
{
	BOOL bRecord = !m_menu.IsItemChecked(ID_RECORD);
	SetRecordNoise(bRecord);
	m_menu.CheckItem(ID_RECORD, bRecord ? MF_CHECKED : MF_UNCHECKED);
	if(bRecord) {
		if(m_menu.IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu.IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_menu.OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_RECORD, 750);
	}
	else {
		KillTimer(IDT_RECORD);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_menu.OnEQFlatMenuSelected();
		m_freqLabel.SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// 古びたレコード再生
//----------------------------------------------------------------------------
void CMainWnd::SetRecord(BOOL bRecord)
{
	SetRecordNoise(bRecord);
	m_menu.CheckItem(ID_RECORD, bRecord ? MF_CHECKED : MF_UNCHECKED);
	if(bRecord) {
		if(m_menu.IsItemChecked(ID_LOWBATTERY)) SetLowBattery(FALSE);
		if(m_menu.IsItemChecked(ID_NOSENSE)) SetNoSense(FALSE);
		m_menu.OnEQMiddleHighestMenuSelected();
		SetTimer(IDT_RECORD, 750);
	}
	else {
		KillTimer(IDT_RECORD);
		nFreqVelo = 0.0;
		nFreqAccel = 0.0;
		m_freqLabel.SetFreq(100.0);
	}
}
//----------------------------------------------------------------------------
// レコードノイズの設定
//----------------------------------------------------------------------------
void CMainWnd::SetRecordNoise(BOOL bRecordNoise)
{
	m_menu.UncheckSoundEffectMenu();
	m_menu.CheckItem(ID_RECORDNOISE, bRecordNoise ? MF_CHECKED : MF_UNCHECKED);
	if(bRecordNoise) {
		m_soundEffect.StreamCreateFile((ToTstring(m_rApp.GetFilePath())
									+ _T("sound\\RecordNoise.wav")).c_str());
		m_soundEffect.ChannelPlay();
		m_soundEffect.SetABLoopA(TRUE);
		m_soundEffect.SetABLoopB(TRUE);
		QWORD qwPosA = m_soundEffect.ChannelSeconds2Bytes(1.417);
		QWORD qwPosB = m_soundEffect.ChannelSeconds2Bytes(7.653);
		m_soundEffect.SetLoopPosA(qwPosA);
		m_soundEffect.SetLoopPosB(qwPosB);
	}
	else m_soundEffect.ChannelStop();
}
//----------------------------------------------------------------------------
// １曲ループの設定
//----------------------------------------------------------------------------
void CMainWnd::SetSingleLoop()
{
	m_sound.SetLoop(!m_sound.IsLoop());
	m_menu.SetSingleLoopState(m_sound.IsLoop());
	m_toolBar.SetSingleLoopState(m_sound.IsLoop());
}
//----------------------------------------------------------------------------
// 再生速度の設定
//----------------------------------------------------------------------------
void CMainWnd::SetSpeed(double dSpeed)
{
	m_sound.SetTempo((float)dSpeed);
}
//----------------------------------------------------------------------------
// 再生周波数の設定
//----------------------------------------------------------------------------
void CMainWnd::SetFreq(double dFreq)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetSampleRate((float)dFreq);
}
//----------------------------------------------------------------------------
// 音程の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPitch(double dPitch)
{
	m_menu.CheckItem(ID_BASSCOPY, MF_UNCHECKED);
	m_menu.CheckItem(ID_CYMBALCOPY, MF_UNCHECKED);
	m_sound.SetPitch((float)dPitch);
}
//----------------------------------------------------------------------------
// モノラル化
//----------------------------------------------------------------------------
void CMainWnd::SetMonoral()
{
	BOOL bMonoral = !m_menu.IsItemChecked(ID_MONORAL);
	if(bMonoral) {
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound.SetMonoral(bMonoral);
	m_menu.CheckItem(ID_MONORAL, bMonoral ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// モノラル化
//----------------------------------------------------------------------------
void CMainWnd::SetMonoral(BOOL bMonoral)
{
	if(bMonoral) {
		SetVocalCancel(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound.SetMonoral(bMonoral);
	m_menu.CheckItem(ID_MONORAL, bMonoral ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ボーカルキャンセル
//----------------------------------------------------------------------------
void CMainWnd::SetVocalCancel()
{
	BOOL bVocalCancel = !m_menu.IsItemChecked(ID_VOCALCANCEL);
	if(bVocalCancel) {
		SetMonoral(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound.SetVocalCancel(bVocalCancel);
	m_menu.CheckItem(ID_VOCALCANCEL, bVocalCancel ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ボーカルキャンセル
//----------------------------------------------------------------------------
void CMainWnd::SetVocalCancel(BOOL bVocalCancel)
{
	if(bVocalCancel) {
		SetMonoral(false);
		SetOnlyLeft(false);
		SetOnlyRight(false);
		SetChangeLR(false);
	}
	m_sound.SetVocalCancel(bVocalCancel);
	m_menu.CheckItem(ID_VOCALCANCEL, bVocalCancel ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 音量の設定
//----------------------------------------------------------------------------
void CMainWnd::SetVolume(double nVolume)
{
	m_sound.ChannelSetVolume((float)nVolume);
}
//----------------------------------------------------------------------------
// 波音の設定
//----------------------------------------------------------------------------
void CMainWnd::SetWave(BOOL bWave)
{
	m_menu.UncheckSoundEffectMenu();
	m_menu.CheckItem(ID_WAVE, bWave ? MF_CHECKED : MF_UNCHECKED);
	if(bWave) {
		m_soundEffect.StreamCreateFile((ToTstring(m_rApp.GetFilePath())
									+ _T("sound\\Wave.mp3")).c_str());
		m_soundEffect.ChannelPlay();
		m_soundEffect.SetABLoopA(TRUE);
		m_soundEffect.SetABLoopB(TRUE);
		QWORD qwPosA = m_soundEffect.ChannelSeconds2Bytes(0.283);
		QWORD qwPosB = m_soundEffect.ChannelSeconds2Bytes(39.399);
		m_soundEffect.SetLoopPosA(qwPosA);
		m_soundEffect.SetLoopPosB(qwPosB);
	}
	else m_soundEffect.ChannelStop();
}
//----------------------------------------------------------------------------
// 時間の設定（秒数）
//----------------------------------------------------------------------------
void CMainWnd::SetSeconds(double fSeconds)
{
	SetTime(m_sound.ChannelSeconds2Bytes(fSeconds));
}
//----------------------------------------------------------------------------
// 時間の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTime(QWORD qwTime, BOOL bReset)
{
	if(bMarkerPlay) {
		BOOL bDone = FALSE; // 範囲を設定したかどうか
		std::vector<QWORD> arrayMarker = m_sound.GetArrayMarker();
		QWORD length = m_sound.ChannelGetLength();
		int max = (int)arrayMarker.size();
		if(max > 0) {
			if(0 <= qwTime && qwTime < arrayMarker[0]) {
					bDone = TRUE;
					m_timeSlider.SetSelStart(0);
					m_timeSlider.SetSelEnd(arrayMarker[0] / 100000);
					m_sound.SetLoopPosA(0);
					m_sound.SetLoopPosB(arrayMarker[0]);
			}
		}
		else {
			bDone = TRUE;
			m_timeSlider.SetSelStart(0);
			m_timeSlider.SetSelEnd(length / 100000);
			m_sound.SetLoopPosA(0);
			m_sound.SetLoopPosB(length);
		}

		if(!bDone) {
			for(int i = 0; i < max; i++) {
				if(i + 1 < max) {
					if(arrayMarker[i] <= qwTime && qwTime < arrayMarker[i + 1])
					{
						bDone = TRUE;
						m_timeSlider.SetSelStart(arrayMarker[i] / 100000);
						m_timeSlider.SetSelEnd(arrayMarker[i + 1] / 100000);
						m_sound.SetLoopPosA(arrayMarker[i]);
						m_sound.SetLoopPosB(arrayMarker[i + 1]);
						break;
					}
				}
			}
		}

		if(!bDone) {
			if(arrayMarker[max - 1] <= qwTime && qwTime <= length) {
				bDone = TRUE;
				m_timeSlider.SetSelStart(arrayMarker[max - 1] / 100000);
				m_timeSlider.SetSelEnd(length / 100000);
				m_sound.SetLoopPosA(arrayMarker[max - 1]);
				m_sound.SetLoopPosB(length);
			}
		}
	}
	if(m_sound.IsABLoopA() && qwTime < m_sound.GetLoopPosA())
		qwTime = m_sound.GetLoopPosA();
	if(m_sound.IsABLoopB()
	   && qwTime > m_sound.GetLoopPosB() - m_sound.ChannelGetFreq())
		qwTime = m_sound.GetLoopPosB() - (QWORD)m_sound.ChannelGetFreq();
	if(qwTime < 0) qwTime = 0;
	else if(qwTime > m_sound.ChannelGetLength() - m_sound.ChannelGetFreq())
		qwTime = m_sound.ChannelGetLength() - (QWORD)m_sound.ChannelGetFreq();
	if(bReset) m_sound.ChannelSetPosition(qwTime);
	ShowTime();
}
//----------------------------------------------------------------------------
// ３Ｄリバーブのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::Show3DReverbCustomizeWnd()
{
	C3DReverbCustomizeWnd dlg(*this);
	dlg.exec();
}
//----------------------------------------------------------------------------
// ディレイのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowDelayCustomizeWnd()
{
	CDelayCustomizeWnd dlg(*this);
	dlg.exec();
}
//----------------------------------------------------------------------------
// パンの設定
//----------------------------------------------------------------------------
void CMainWnd::SetPan(int nPan)
{
	m_sound.ChannelSetPan(nPan);
}
//----------------------------------------------------------------------------
// リバーブのカスタマイズ用ウィンドウの表示
//----------------------------------------------------------------------------
void CMainWnd::ShowReverbCustomizeWnd()
{
	CReverbCustomizeWnd dlg(*this);
	dlg.exec();
}
//----------------------------------------------------------------------------
// 再生時間の表示
//----------------------------------------------------------------------------
void CMainWnd::ShowTime(BOOL bReset)
{
	m_timeLabel.SetTime(m_sound.ChannelGetSecondsPosition(),
						m_sound.ChannelGetSecondsLength(), bReset);
	m_timeSlider.SetThumbPos((LONG)(m_sound.ChannelGetPosition() / 100000));
}
//----------------------------------------------------------------------------
// 巻き戻しの開始
//----------------------------------------------------------------------------
void CMainWnd::StartRewind()
{
	StopForward();
	m_menu.CheckItem(ID_REWIND, MF_CHECKED);
	if(bMarkerPlay)
		m_toolBar.SetState(ID_PREVMARKER, TBSTATE_CHECKED | TBSTATE_ENABLED);
	else m_toolBar.SetState(ID_HEAD, TBSTATE_CHECKED | TBSTATE_ENABLED);
	SetTimer(IDT_REWIND, 100);
	m_bRewinding = true;
}
//----------------------------------------------------------------------------
// 巻き戻しの停止
//----------------------------------------------------------------------------
void CMainWnd::StopRewind()
{
	if(!m_bRewinding) {
		return;
	}
	m_menu.CheckItem(ID_REWIND, MF_UNCHECKED);
	if(bMarkerPlay) m_toolBar.SetState(ID_PREVMARKER, TBSTATE_ENABLED);
	else m_toolBar.SetState(ID_HEAD, TBSTATE_ENABLED);
	KillTimer(IDT_REWIND);
	m_bRewinding = false;
}
//----------------------------------------------------------------------------
// 早送りの開始
//----------------------------------------------------------------------------
void CMainWnd::StartForward()
{
	StopRewind();
	m_menu.CheckItem(ID_FORWARD, MF_CHECKED);
	if(bMarkerPlay)
		m_toolBar.SetState(ID_NEXTMARKER, TBSTATE_CHECKED | TBSTATE_ENABLED);
	else m_toolBar.SetState(ID_NEXT, TBSTATE_CHECKED | TBSTATE_ENABLED);
	SetTimer(IDT_FORWARD, 100);
	m_bForwarding = true;
}
//----------------------------------------------------------------------------
// 早送りの停止
//----------------------------------------------------------------------------
void CMainWnd::StopForward()
{
	if(!m_bForwarding) {
		return;
	}
	m_menu.CheckItem(ID_FORWARD, MF_UNCHECKED);
	if(bMarkerPlay) m_toolBar.SetState(ID_NEXTMARKER, TBSTATE_ENABLED);
	else m_toolBar.SetState(ID_NEXT, TBSTATE_ENABLED);
	KillTimer(IDT_FORWARD);
	m_bForwarding = false;
}
//----------------------------------------------------------------------------
// 停止
//----------------------------------------------------------------------------
void CMainWnd::Stop(BOOL bForce)
{
	KillTimer(IDT_TIME);
	SetCountLoop(FALSE, 0);
	m_sound.ChannelStop();
	SetTime(0);
	m_toolBar.SetPlayingState(FALSE);
	m_arrayList[nCurPlayTab]->SetPlaying(-1);
	m_sound.ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
	if(m_arrayList[nCurPlayTab]->GetItemCount() == 0)
		SetCaption(m_rApp.GetName());
}
//----------------------------------------------------------------------------
// 指定した%再生周波数を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpFreq(double freq)
{
	double dCalc = pow(10.0, m_freqSlider.GetDecimalDigit());
	int newFreq = m_freqSlider.GetThumbPos() + (int)(freq * dCalc);
	m_freqLabel.SetFreq((double)(newFreq / dCalc));
}
//----------------------------------------------------------------------------
// 指定した数値×半音分音程を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpPitch(double pitch)
{
	double dCalc = pow(10.0, m_pitchSlider.GetDecimalDigit());
	int newPitch = m_pitchSlider.GetThumbPos() + (int)(pitch * dCalc);
	m_pitchLabel.SetPitch((double)(newPitch / dCalc));
}
//----------------------------------------------------------------------------
// 指定した%再生速度を上げる
//----------------------------------------------------------------------------
void CMainWnd::UpSpeed(double speed)
{
	double dCalc = pow(10.0, m_speedSlider.GetDecimalDigit());
	int newSpeed = m_speedSlider.GetThumbPos() + (int)(speed * dCalc);
	m_speedLabel.SetSpeed((double)(newSpeed / dCalc));
}
//----------------------------------------------------------------------------
// INI ファイルの書き込み
//----------------------------------------------------------------------------
void CMainWnd::WriteInitFile()
{
	if(!isInitFileRead) return;

	tstring initFilePath =
			ToTstring(m_rApp.GetFilePath() + QString("Setting.ini"));

	TCHAR buf[255];

	// 表示・非表示の設定
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERSPEEDVISIBLE) ? 1 : 0 ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverSpeed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_SPEED) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Speed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERFREQVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverFrequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_FREQ) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Frequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERPITCHVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverPitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_PITCH) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Pitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERVOLUMEVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverVolume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_VOLUME) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Volume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERPANVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverPan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_PAN) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("Pan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVEREQVISIBLE) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("RecoverEQ"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ20) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq20"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ25) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq25"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ31_5) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq31_5"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ40) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq40"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ50) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq50"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ63) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq63"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ80) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq80"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ100) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq100"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ125) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq125"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ160) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq160"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ200) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq200"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ250) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq250"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ315) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq315"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ400) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq400"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ500) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq500"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ630) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq630"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ800) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq800"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ1K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq1k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ1_25K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq1_25k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ1_6K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq1_6k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ2K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq2k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ2_5K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq2_5k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ3_15K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq3_15k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ4K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq4k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ5K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq5k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ6_3K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq6_3k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ8K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq8k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ10K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq10k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ12_5K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq12_5k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ16K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq16k"), buf,
		 initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_EQ20K) ? 1 : 0);
	WritePrivateProfileString(_T("Visible"), _T("eq20k"), buf,
		 initFilePath.c_str());

	// 再生モードの設定
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERSLOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverSingleLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_sound.IsLoop() ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("SingleLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERALOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverAllLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_ALOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("AllLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERRANDOM) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverRandom"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RANDOM) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Random"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERCONTINUE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverContinue"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_CONTINUE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Continue"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERINSTANTLOOP) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverInstantLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), bInstantLoop ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("InstantLoop"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"),
		m_menu.IsItemChecked(ID_RECOVERSETPOSITIONAUTO) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverSetPositionAuto"), 
		buf, initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), bSetPositionAuto ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("SetPositionAuto"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERREVERSE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverReverse"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_REVERSE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Reverse"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERRECORD) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("RecoverRecord"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECORD) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Record"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_NORMALIZE) ? 1 : 0);
	WritePrivateProfileString(_T("PlayMode"), _T("Normalize"), buf, 
		initFilePath.c_str());

	// その他の設定
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERSPEED) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverSpeed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_speedSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Speed"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERFREQ) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverFrequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_freqSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Frequency"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERPITCH) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverPitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_pitchSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Pitch"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERVOLUME) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverVolume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_volumeSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Volume"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVERPAN) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverPan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_panSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("Pan"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_menu.IsItemChecked(ID_RECOVEREQ) ? 1 : 0);
	WritePrivateProfileString(_T("Options"), _T("RecoverEQ"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq20Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ20"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq25Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ25"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq31_5Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ31.5"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq40Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ40"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq50Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ50"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq63Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ63"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq80Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ80"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq100Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ100"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq125Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ125"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq160Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ160"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq200Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ200"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq250Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ250"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq315Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ315"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq400Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ400"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq500Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ500"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq630Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ630"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq800Slider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ800"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1_25kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1.25K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq1_6kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ1.6K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq2kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ2K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq2_5kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ2.5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq3_15kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ3.15K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq4kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ4K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq5kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq6_3kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ6.3K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq8kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ8K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq10kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ10K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq12_5kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ12.5K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq16kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ16K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_eq20kSlider.GetThumbPos());
	WritePrivateProfileString(_T("Options"), _T("EQ20K"), buf, 
		initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_speedSlider.GetRangeMin()
		/ pow(10.0, m_speedSlider.GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MinimumSpeed"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%4.1f"), m_speedSlider.GetRangeMax()
		/ pow(10.0, m_speedSlider.GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MaximumSpeed"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_speedSlider.GetDecimalDigit());
	WritePrivateProfileString(_T("Options"), _T("SpeedDecimalDigit"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_freqSlider.GetRangeMin()
		/ pow(10.0, m_freqSlider.GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MinimumFrequency"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%4.1f"), m_freqSlider.GetRangeMax()
		/ pow(10.0, m_freqSlider.GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MaximumFrequency"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_freqSlider.GetDecimalDigit());
	WritePrivateProfileString(_T("Options"), _T("FrequencyDecimalDigit"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_pitchSlider.GetRangeMin()
		/ pow(10.0, m_pitchSlider.GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MinimumPitch"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%3.1f"), m_pitchSlider.GetRangeMax()
		/ pow(10.0, m_pitchSlider.GetDecimalDigit()));
	WritePrivateProfileString(_T("Options"), _T("MaximumPitch"), buf,
							  initFilePath.c_str());
	_stprintf_s(buf, _T("%d"), m_pitchSlider.GetDecimalDigit());
	WritePrivateProfileString(_T("Options"), _T("PitchDecimalDigit"), buf,
							  initFilePath.c_str());
}
//----------------------------------------------------------------------------
// 閉じられようとしている
//----------------------------------------------------------------------------
void CMainWnd::OnClose()
{
	WriteInitFile();
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CMainWnd::OnCreate()
{
	Ui::MainWnd::setupUi(this);
#if __APPLE__
	menuBar()->setNativeMenuBar(false);
#endif
	setAcceptDrops(true);

	// メニューの作成
	if(!m_menu.Create()) {
		m_rApp.ShowError(tr("failed to create menu."));
		return FALSE;
	}

	TCHAR chPath[255];
	lstrcpy(chPath,
					ToTstring(m_rApp.GetFilePath() + QString("Setting.ini")).c_str());

	BOOL bSpeedVisible = TRUE, bFreqVisible = TRUE, bPitchVisible = TRUE,
		bVolumeVisible = TRUE, bPanVisible = TRUE, bEQVisible = TRUE;
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverSpeed"), 1, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERSPEEDVISIBLE);
		bSpeedVisible = GetPrivateProfileInt(_T("Visible"), _T("Speed"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverFrequency"), 1, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERFREQVISIBLE);
		bFreqVisible = GetPrivateProfileInt(_T("Visible"), _T("Frequency"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverPitch"), 1, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERPITCHVISIBLE);
		bPitchVisible = GetPrivateProfileInt(_T("Visible"), _T("Pitch"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverVolume"), 1, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERVOLUMEVISIBLE);
		bVolumeVisible = GetPrivateProfileInt(_T("Visible"), _T("Volume"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverPan"), 1, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVERPANVISIBLE);
		bPanVisible = GetPrivateProfileInt(_T("Visible"), _T("Pan"), 1,
			chPath);
	}
	if(GetPrivateProfileInt(_T("Visible"), _T("RecoverEQ"), 1, chPath)) {
		m_menu.SwitchItemChecked(ID_RECOVEREQVISIBLE);
		bEQVisible = GetPrivateProfileInt(_T("Visible"), _T("EQ"), 0,
			chPath);
	}

	if(!CreateControls())
		return FALSE;

	if(bSpeedVisible) SetSpeedVisible(true);
	if(bFreqVisible) SetFreqVisible(true);
	if(bPitchVisible) SetPitchVisible(true);
	if(bVolumeVisible) SetVolumeVisible(true);
	if(bPanVisible) SetPanVisible(true);
	if(bEQVisible) SetEQVisible(true);

	m_timeLabel.SetTime(0, 0);

	OpenInitFile();

	// bass の初期化
	if(!m_sound.Init()) {
		m_rApp.ShowError(tr("failed to init BASS.DLL."));
		return FALSE;
	}

	OpenInitFileAfterShow();

	SetPreviousNextMenuState();

	m_timeThreadRunning = true;
	m_timeThread.reset(
			new std::thread(std::bind(&CMainWnd::UpdateTimeThreadProc, this)));

	return TRUE;
}
//----------------------------------------------------------------------------
// タイマーの周期が来た
//----------------------------------------------------------------------------
void CMainWnd::OnTimer(UINT id)
{
	switch(id)
	{
	case IDT_TIME:
		if(m_bFinish) {
			m_bFinish = FALSE;
			KillTimer(IDT_TIME);
			if(m_menu.IsItemChecked(ID_CONTINUE))
				PlayNext(TRUE, TRUE);
			else PlayNext(FALSE, TRUE);
		}
		break;
	case IDT_REWIND:
		Rewind();
		break;
	case IDT_FORWARD:
		Forward();
		break;
	case IDT_RECORD:
		if(!m_sound.ChannelIsStopped() && !m_sound.ChannelIsPausing()) {
			double freq_org = (double)(m_freqSlider.GetThumbPos()
				/ pow(10.0, m_freqSlider.GetDecimalDigit()));
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

				// 90 〜 100 の間で動くようにする
				if(freq <= 90.0) freq = 90.0;
				if(freq >= 100.0) freq = 100.0;

				m_freqLabel.SetFreq(freq);
			}
		}
		break;
	case IDT_LOWBATTERY:
		if(!m_sound.ChannelIsStopped() && !m_sound.ChannelIsPausing()) {
			double freq_org = (double)(m_freqSlider.GetThumbPos()
				/ pow(10.0, m_freqSlider.GetDecimalDigit()));
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

				// 65 〜 70 の間で動くようにする
				if(freq <= 65.0) freq = 65.0;
				if(freq >= 70.0) freq = 70.0;

				m_freqLabel.SetFreq(freq);
			}
		}
		break;
	case IDT_NOSENSE:
		if(m_sound.ChannelGetSecondsPosition() <= 10.0) {
			m_pitchLabel.SetPitch(0.0);
			m_speedLabel.SetSpeed(100.0);
		}
		else if(!m_sound.ChannelIsStopped() && !m_sound.ChannelIsPausing()) {
			double pitch_org = (double)(m_pitchSlider.GetThumbPos()
				/ pow(10.0, m_pitchSlider.GetDecimalDigit()));
					// 現在の音程

			if(m_sound.ChannelGetSecondsPosition() > 30.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 1000.0;
			else if(m_sound.ChannelGetSecondsPosition() > 20.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 2000.0;
			else nFreqVelo = CUtils::GetRandom(-100, 100) / 5000.0;
			if(pitch_org <= -2.0 && nFreqVelo < 0.0) nFreqVelo *= -1.0;
			if(pitch_org >= 2.0 && nFreqVelo > 0.0) nFreqVelo *= -1.0;

			// 音程に差分を加える
			if(nFreqVelo != 0.0) {
				double pitch = pitch_org + nFreqVelo;

				// ♭2 〜 ♯2 の間で動くようにする
				// if(pitch < -2.0) pitch = -2.0;
				// if(pitch > 2.0) pitch = 2.0;

				m_pitchLabel.SetPitch(pitch);
			}

			double speed_org = (double)(m_speedSlider.GetThumbPos()
				/ pow(10.0, m_speedSlider.GetDecimalDigit()));
					// 現在の速度

			if(m_sound.ChannelGetSecondsPosition() > 30.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 1000.0;
			else if(m_sound.ChannelGetSecondsPosition() > 20.0)
				nFreqVelo = CUtils::GetRandom(-100, 100) / 2000.0;
			else nFreqVelo = CUtils::GetRandom(-100, 100) / 5000.0;
			if(speed_org <= -90.0 && nFreqVelo < 0.0) nFreqVelo *= -1.0;
			if(speed_org >= 110.0 && nFreqVelo > 0.0) nFreqVelo *= -1.0;

			// 速度に差分を加える
			if(nFreqVelo != 0.0) {
				double speed = speed_org + nFreqVelo;

				// -90 〜 ♯2 の間で動くようにする
				// if(speed < -90.0) speed = -90.0;
				// if(speed > 110.0) speed = 110.0;

				m_speedLabel.SetSpeed(speed);
			}
		}
		break;
	case IDT_EARTRAINING:
		{
			srand(time(nullptr));
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
			m_panLabel.SetPan(nPan);
		}
		break;
	}
}
//----------------------------------------------------------------------------
// 時間表示の更新用スレッド
//----------------------------------------------------------------------------
void CMainWnd::UpdateTimeThreadProc(void * pParam)
{
	CMainWnd* pMainWnd = (CMainWnd *)pParam;
	while(1) {
		if(!pMainWnd->m_timeThreadRunning) {
			break;
		}
		pMainWnd->ShowTime(FALSE);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
//----------------------------------------------------------------------------
// 各種コントロールにコンテキストメニューを割り当てる
//----------------------------------------------------------------------------
void CMainWnd::SetContextMenus()
{
	// Speed
	QWidget * speedWidgets[] = { speedLabel, speedSlider };
	for (auto w : speedWidgets) {
		w->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(w, &QWidget::customContextMenuRequested,
						std::bind(&CMainWnd::ShowContextMenu, this, w, menuSpeed,
											actionSpeedVisible, tr("Show Speed Control(&S)"),
											&CMainWnd::SetSpeedVisible, std::placeholders::_1));
	}
	// Frequency
	QWidget * freqWidgets[] = { freqLabel, freqSlider };
	for (auto w : freqWidgets) {
		w->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(w, &QWidget::customContextMenuRequested,
						std::bind(&CMainWnd::ShowContextMenu, this, w, menuFreq,
											actionFreqVisible, tr("Show Frequency Control(&S)"),
											&CMainWnd::SetFreqVisible, std::placeholders::_1));
	}
	// Pitch
	QWidget * pitchWidgets[] = { pitchLabel, pitchSlider };
	for (auto w : pitchWidgets) {
		w->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(w, &QWidget::customContextMenuRequested,
						std::bind(&CMainWnd::ShowContextMenu, this, w, menuPitch,
											actionPitchVisible, tr("Show Pitch Control(&S)"),
											&CMainWnd::SetPitchVisible, std::placeholders::_1));
	}
	// Volume
	QWidget * volumeWidgets[] = { volumeLabel, volumeSlider };
	for (auto w : volumeWidgets) {
		w->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(w, &QWidget::customContextMenuRequested,
						std::bind(&CMainWnd::ShowContextMenu, this, w, menuVolume,
											actionVolumeVisible, tr("Show Volume Control(&S)"),
											&CMainWnd::SetVolumeVisible, std::placeholders::_1));
	}
	// Pan
	QWidget * panWidgets[] = { panLabel, panSlider };
	for (auto w : panWidgets) {
		w->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(w, &QWidget::customContextMenuRequested,
						std::bind(&CMainWnd::ShowContextMenu, this, w, nullptr,
											actionPanVisible, tr("Show Pan Control(&S)"),
											&CMainWnd::SetPanVisible, std::placeholders::_1));
	}
}
//----------------------------------------------------------------------------
// コンテキストメニューを作成
//----------------------------------------------------------------------------
void CMainWnd::ShowContextMenu(QWidget * widget, QMenu * menu,
															 QAction * visibilityAction,
															 const QString &title,
															 void (CMainWnd::*callback)(bool visible),
															 const QPoint & pos)
{
	QMenu contextMenu;
	if (menu != nullptr) {
		for (auto action : menu->actions()) {
			contextMenu.addAction(action);
		}
	}
	if (visibilityAction != nullptr) {
		auto act = new QAction(title, &contextMenu);
		act->setCheckable(true);
		act->setChecked(visibilityAction->isChecked());
		connect(act, &QAction::toggled, this, callback);
		contextMenu.addSeparator();
		contextMenu.addAction(act);
	}

	contextMenu.exec(widget->mapToGlobal(pos));
}
//----------------------------------------------------------------------------
// 終了イベント
//----------------------------------------------------------------------------
void CMainWnd::closeEvent(QCloseEvent * event)
{
	OnClose();
	event->accept();
}
//----------------------------------------------------------------------------
// Qt固有の実装
//----------------------------------------------------------------------------
void CMainWnd::dragEnterEvent(QDragEnterEvent * e)
{
	e->acceptProposedAction();
}
void CMainWnd::dropEvent(QDropEvent * e)
{
	AddDropFiles(e->mimeData()->urls(), TRUE);
}
void CMainWnd::KillTimer(UINT_PTR nIDEvent)
{
	auto it = m_timers.find(nIDEvent);
	if(it == m_timers.end()) {
		return;
	}
	it->second->stop();
}
void CMainWnd::SetCaption(const QString & lpWindowName)
{
	setWindowTitle(lpWindowName);
}
void CMainWnd::SetTimer(UINT_PTR nIDEvent, UINT nElapse)
{
	QTimer *timer;
	auto it = m_timers.find(nIDEvent);
	if(it == m_timers.end()) {
		timer = new QTimer(this);
		connect(timer, &QTimer::timeout,
						std::bind(&CMainWnd::OnTimer, this, static_cast<UINT>(nIDEvent)));
		m_timers.insert({nIDEvent, timer});
	} else {
		timer = it->second;
	}
	timer->setInterval(nElapse);
	timer->start();
}
//----------------------------------------------------------------------------
