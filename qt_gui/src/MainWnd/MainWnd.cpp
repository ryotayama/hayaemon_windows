//----------------------------------------------------------------------------
// MainWnd.cpp : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#include "MainWnd.h"
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
#include "PlayListView_MainWnd.h"
#include "Platform.h"
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
}
//----------------------------------------------------------------------------
// 各コントロールを作成
//----------------------------------------------------------------------------
BOOL CMainWnd::CreateControls()
{
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

	double _dMinSpeed = 10.0;
	double _dMaxSpeed = 1200.0;
	int _nSpeedDecimalDigit = 1;
	if(_nSpeedDecimalDigit == 0) m_menu.OnSetSpeedDecimal0MenuSelected();
	else if(_nSpeedDecimalDigit == 1)
		m_menu.OnSetSpeedDecimal1MenuSelected();
	else if(_nSpeedDecimalDigit == 2)
		m_menu.OnSetSpeedDecimal2MenuSelected();

	m_speedSlider.SetLimit(_dMinSpeed, _dMaxSpeed);
	m_speedLabel.SetLimit(_dMinSpeed, _dMaxSpeed);

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

	double _dMinFreq = 10.0;
	double _dMaxFreq = 1200.0;
	int _nFreqDecimalDigit = 1;
	if(_nFreqDecimalDigit == 0) m_menu.OnSetFreqDecimal0MenuSelected();
	else if(_nFreqDecimalDigit == 1) m_menu.OnSetFreqDecimal1MenuSelected();
	else if(_nFreqDecimalDigit == 2) m_menu.OnSetFreqDecimal2MenuSelected();

	m_freqSlider.SetLimit(_dMinFreq, _dMaxFreq);
	m_freqLabel.SetLimit(_dMinFreq, _dMaxFreq);

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

	double _dMinPitch = -24.0;
	double _dMaxPitch = 24.0;
	int _nPitchDecimalDigit = 1;
	if(_nPitchDecimalDigit == 0) m_menu.OnSetPitchDecimal0MenuSelected();
	else if(_nPitchDecimalDigit == 1)
		m_menu.OnSetPitchDecimal1MenuSelected();
	else if(_nPitchDecimalDigit == 2)
		m_menu.OnSetPitchDecimal2MenuSelected();

	if(_dMinPitch < -60.0) _dMinPitch = -60.0;
	if(_dMaxPitch > 60.0) _dMaxPitch = 60.0;

	m_pitchSlider.SetLimit(_dMinPitch, _dMaxPitch);
	m_pitchLabel.SetLimit(_dMinPitch, _dMaxPitch);

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
// ファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenFile(const QString & lpszFilePath, int nCount)
{
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
	SetAllEffects();
	m_toolBar.SetPlayingState(FALSE);
	m_timeLabel.SetTime(0, m_sound.ChannelGetSecondsLength());
	m_timeSlider.SetTime(0, m_sound.ChannelGetLength());

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
}
//----------------------------------------------------------------------------
// INI ファイルを開く
//----------------------------------------------------------------------------
void CMainWnd::OpenInitFileAfterShow()
{
	isInitFileRead = TRUE;
}
//----------------------------------------------------------------------------
// 次のファイルを開く
//----------------------------------------------------------------------------
BOOL CMainWnd::OpenNext()
{
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

	// 次に開くべきファイルが見つからなかった場合
	if(i >= m_arrayList[nCurPlayTab]->GetItemCount()) return FALSE;

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
					&& m_sound.GetCurFileNum() > 1) {
				m_sound.SetCurFileNum(0);
				OpenNext();
			}
			m_sound.SetLoop(isLoop);
			break;
		}
	}

	m_sound.ChannelSetAttribute(BASS_ATTRIB_VOL, 1.0f);
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
// 全てのエフェクトを設定
//----------------------------------------------------------------------------
void CMainWnd::SetAllEffects()
{
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
// イコライザ ( 20Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ20(LONG lEQ20)
{
	m_sound.SetEQ20(20, 0.7f, (float)lEQ20);
}
//----------------------------------------------------------------------------
// イコライザ ( 25Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ25(LONG lEQ25)
{
	m_sound.SetEQ25(25, 0.7f, (float)lEQ25);
}
//----------------------------------------------------------------------------
// イコライザ ( 31.5Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ31_5(LONG lEQ31_5)
{
	m_sound.SetEQ31_5(31.5, 0.7f, (float)lEQ31_5);
}
//----------------------------------------------------------------------------
// イコライザ ( 40Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ40(LONG lEQ40)
{
	m_sound.SetEQ40(40, 0.7f, (float)lEQ40);
}
//----------------------------------------------------------------------------
// イコライザ ( 50Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ50(LONG lEQ50)
{
	m_sound.SetEQ50(50, 0.7f, (float)lEQ50);
}
//----------------------------------------------------------------------------
// イコライザ ( 63Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ63(LONG lEQ63)
{
	m_sound.SetEQ63(63, 0.7f, (float)lEQ63);
}
//----------------------------------------------------------------------------
// イコライザ ( 80Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ80(LONG lEQ80)
{
	m_sound.SetEQ80(80, 0.7f, (float)lEQ80);
}
//----------------------------------------------------------------------------
// イコライザ ( 100Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ100(LONG lEQ100)
{
	m_sound.SetEQ100(100, 0.7f, (float)lEQ100);
}
//----------------------------------------------------------------------------
// イコライザ ( 125Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ125(LONG lEQ125)
{
	m_sound.SetEQ125(125, 0.7f, (float)lEQ125);
}
//----------------------------------------------------------------------------
// イコライザ ( 160Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ160(LONG lEQ160)
{
	m_sound.SetEQ160(160, 0.7f, (float)lEQ160);
}
//----------------------------------------------------------------------------
// イコライザ ( 200Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ200(LONG lEQ200)
{
	m_sound.SetEQ200(200, 0.7f, (float)lEQ200);
}
//----------------------------------------------------------------------------
// イコライザ ( 250Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ250(LONG lEQ250)
{
	m_sound.SetEQ250(250, 0.7f, (float)lEQ250);
}
//----------------------------------------------------------------------------
// イコライザ ( 315Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ315(LONG lEQ315)
{
	m_sound.SetEQ315(315, 0.7f, (float)lEQ315);
}
//----------------------------------------------------------------------------
// イコライザ ( 400Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ400(LONG lEQ400)
{
	m_sound.SetEQ400(400, 0.7f, (float)lEQ400);
}
//----------------------------------------------------------------------------
// イコライザ ( 500Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ500(LONG lEQ500)
{
	m_sound.SetEQ500(500, 0.7f, (float)lEQ500);
}
//----------------------------------------------------------------------------
// イコライザ ( 630Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ630(LONG lEQ630)
{
	m_sound.SetEQ630(630, 0.7f, (float)lEQ630);
}
//----------------------------------------------------------------------------
// イコライザ ( 800Hz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ800(LONG lEQ800)
{
	m_sound.SetEQ800(800, 0.7f, (float)lEQ800);
}
//----------------------------------------------------------------------------
// イコライザ ( 1KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1K(LONG lEQ1K)
{
	m_sound.SetEQ1K(1000, 0.7f, (float)lEQ1K);
}
//----------------------------------------------------------------------------
// イコライザ ( 1.25KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1_25K(LONG lEQ1_25K)
{
	m_sound.SetEQ1_25K(1250, 0.7f, (float)lEQ1_25K);
}
//----------------------------------------------------------------------------
// イコライザ ( 1.6KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ1_6K(LONG lEQ1_6K)
{
	m_sound.SetEQ1_6K(1600, 0.7f, (float)lEQ1_6K);
}
//----------------------------------------------------------------------------
// イコライザ ( 2KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ2K(LONG lEQ2K)
{
	m_sound.SetEQ2K(2000, 0.7f, (float)lEQ2K);
}
//----------------------------------------------------------------------------
// イコライザ ( 2.5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ2_5K(LONG lEQ2_5K)
{
	m_sound.SetEQ2_5K(2500, 0.7f, (float)lEQ2_5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 3.15KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ3_15K(LONG lEQ3_15K)
{
	m_sound.SetEQ3_15K(3150, 0.7f, (float)lEQ3_15K);
}
//----------------------------------------------------------------------------
// イコライザ ( 4KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ4K(LONG lEQ4K)
{
	m_sound.SetEQ4K(4000, 0.7f, (float)lEQ4K);
}
//----------------------------------------------------------------------------
// イコライザ ( 5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ5K(LONG lEQ5K)
{
	m_sound.SetEQ5K(5000, 0.7f, (float)lEQ5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 6.3KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ6_3K(LONG lEQ6_3K)
{
	m_sound.SetEQ6_3K(6300, 0.7f, (float)lEQ6_3K);
}
//----------------------------------------------------------------------------
// イコライザ ( 8KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ8K(LONG lEQ8K)
{
	m_sound.SetEQ8K(8000, 0.7f, (float)lEQ8K);
}
//----------------------------------------------------------------------------
// イコライザ ( 10KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ10K(LONG lEQ10K)
{
	m_sound.SetEQ10K(10000, 0.7f, (float)lEQ10K);
}
//----------------------------------------------------------------------------
// イコライザ ( 12.5KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ12_5K(LONG lEQ12_5K)
{
	m_sound.SetEQ12_5K(12500, 0.7f, (float)lEQ12_5K);
}
//----------------------------------------------------------------------------
// イコライザ ( 16KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ16K(LONG lEQ16K)
{
	m_sound.SetEQ16K(16000, 0.7f, (float)lEQ16K);
}
//----------------------------------------------------------------------------
// イコライザ ( 20KHz ) の設定
//----------------------------------------------------------------------------
void CMainWnd::SetEQ20K(LONG lEQ20K)
{
	m_sound.SetEQ20K(20000, 0.7f, (float)lEQ20K);
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
	m_sound.SetSampleRate((float)dFreq);
}
//----------------------------------------------------------------------------
// 音程の設定
//----------------------------------------------------------------------------
void CMainWnd::SetPitch(double dPitch)
{
	m_sound.SetPitch((float)dPitch);
}
//----------------------------------------------------------------------------
// 音量の設定
//----------------------------------------------------------------------------
void CMainWnd::SetVolume(double nVolume)
{
	m_sound.ChannelSetVolume((float)nVolume);
}
//----------------------------------------------------------------------------
// 時間の設定
//----------------------------------------------------------------------------
void CMainWnd::SetTime(QWORD qwTime, BOOL bReset)
{
	if(qwTime < 0) qwTime = 0;
	else if(qwTime > m_sound.ChannelGetLength() - m_sound.ChannelGetFreq())
		qwTime = m_sound.ChannelGetLength() - (QWORD)m_sound.ChannelGetFreq();
	if(bReset) m_sound.ChannelSetPosition(qwTime);
	ShowTime();
}
//----------------------------------------------------------------------------
// パンの設定
//----------------------------------------------------------------------------
void CMainWnd::SetPan(int nPan)
{
	m_sound.ChannelSetPan(nPan);
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
// 停止
//----------------------------------------------------------------------------
void CMainWnd::Stop(BOOL bForce)
{
	KillTimer(IDT_TIME);
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

	if(!CreateControls())
		return FALSE;

	SetSpeedVisible(true);
	SetFreqVisible(true);
	SetPitchVisible(true);
	SetVolumeVisible(true);
	SetPanVisible(true);
	SetEQVisible(true);

	m_timeLabel.SetTime(0, 0);

	OpenInitFile();

	// bass の初期化
	if(!m_sound.Init()) {
		m_rApp.ShowError(tr("failed to init BASS.DLL."));
		return FALSE;
	}

	OpenInitFileAfterShow();

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
			PlayNext(FALSE, TRUE);
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
