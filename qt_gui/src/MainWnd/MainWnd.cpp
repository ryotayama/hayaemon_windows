//----------------------------------------------------------------------------
// MainWnd.cpp : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#include "MainWnd.h"
#include <chrono>
#include <functional>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QTimer>
#include "../App.h"
#include "../Common/CommandList.h"
#include "PlayListView_MainWnd.h"
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
	SetVolume((double)m_volumeSlider.GetThumbPos() / 10.0);
	SetPan(m_panSlider.GetThumbPos());
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
// 作成された
//----------------------------------------------------------------------------
LRESULT CMainWnd::OnCreate()
{
	Ui::MainWnd::setupUi(this);
	setAcceptDrops(true);

	// メニューの作成
	if(!m_menu.Create()) {
		m_rApp.ShowError(tr("failed to create menu."));
		return FALSE;
	}

	if(!CreateControls())
		return FALSE;

	SetVolumeVisible(true);
	SetPanVisible(true);

	m_timeLabel.SetTime(0, 0);

	// bass の初期化
	if(!m_sound.Init()) {
		m_rApp.ShowError(tr("failed to init BASS.DLL."));
		return FALSE;
	}

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
	auto act = new QAction(title, &contextMenu);
	act->setCheckable(true);
	act->setChecked(visibilityAction->isChecked());
	connect(act, &QAction::toggled, this, callback);
	contextMenu.addSeparator();
	contextMenu.addAction(act);

	contextMenu.exec(widget->mapToGlobal(pos));
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
