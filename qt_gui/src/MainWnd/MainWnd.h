//----------------------------------------------------------------------------
// MainWnd.h : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH

class CApp;
class CPlayListView_MainWnd;
class QTimer;
class QUrl;
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>
#include <QList>
#include <QMainWindow>
#include "../Common/Define.h"
#include "Menu_MainWnd.h"
#include "PanLabel_MainWnd.h"
#include "PanSlider_MainWnd.h"
#include "Sound.h"
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

	CMainWnd(CApp & app): m_rApp(app), m_menu(*this), m_toolBar(*this),
		m_timeLabel(*this), m_timeSlider(*this), m_volumeLabel(*this),
		m_volumeSlider(*this), m_panLabel(*this), m_panSlider(*this),
		m_sound(*this), m_bFinish(FALSE), nCurPlayTab(0),
		m_timeThreadRunning(false) { }
	virtual ~CMainWnd();

	virtual void AddDropFiles(const QList<QUrl> & urls, BOOL bClear);
	virtual BOOL Create() { return OnCreate(); }
	virtual BOOL CreateControls();
	virtual BOOL OpenFile(const QString & lpszFilePath, int nCount = 1);
	virtual BOOL OpenNext();
	virtual void Pause();
	virtual BOOL Play();
	virtual void PlayNext(BOOL bPlay, BOOL bFadeoutCancel);
	virtual void ResetVolume();
	virtual void SetAllEffects();
	virtual void SetVolumeVisible(bool bVolumeVisible);
	virtual void SetPanVisible(bool bPanVisible);
	virtual void SetVolume(double nVolume);
	virtual void SetTime(QWORD qwTime, BOOL bReset = TRUE);
	virtual void SetPan(int nPan);
	virtual void ShowTime(BOOL bReset = TRUE);
	virtual void Stop(BOOL bForce = TRUE);

	virtual LRESULT OnCreate();
	virtual void OnTimer(UINT id);

	static void UpdateTimeThreadProc(void * pParam);

protected: // メンバ変数

	CApp & m_rApp;
	CMenu_MainWnd m_menu;
	CToolBar_MainWnd m_toolBar;
	CTimeLabel_MainWnd m_timeLabel;
	CTimeSlider_MainWnd m_timeSlider;
	CVolumeLabel_MainWnd m_volumeLabel;
	CVolumeSlider_MainWnd m_volumeSlider;
	CPanLabel_MainWnd m_panLabel;
	CPanSlider_MainWnd m_panSlider;
	std::vector<CPlayListView_MainWnd*> m_arrayList;

	CSound m_sound;

	BOOL m_bFinish; // 再生が完了したかどうか
	int nCurPlayTab; // 現在再生中のファイルが存在しているタブ
	std::unique_ptr<std::thread> m_timeThread;
	bool m_timeThreadRunning;

public: // 定数

	// タイマー ID
	enum {
		IDT_TIME = 11,
	};

public: // メンバ変数の取得・設定

	CVolumeLabel_MainWnd & GetVolumeLabel() { return m_volumeLabel; }
	CVolumeSlider_MainWnd & GetVolumeSlider() { return m_volumeSlider; }
	CPanLabel_MainWnd & GetPanLabel() { return m_panLabel; }
	CPanSlider_MainWnd & GetPanSlider() { return m_panSlider; }
	CPlayListView_MainWnd & GetCurPlayList() {
		return *m_arrayList[nCurPlayTab];
	}
	CSound & GetSound() { return m_sound; }
 	void SetFinish(BOOL bFinish) { m_bFinish = bFinish; }

private:

	void SetContextMenus();
	void ShowContextMenu(QWidget * widget, QMenu * menu,
											 QAction * visibilityAction, const QString &title,
											 void (CMainWnd::*callback)(bool visible),
											 const QPoint & pos);
	void dragEnterEvent(QDragEnterEvent * e) final;
	void dropEvent(QDropEvent * e) final;
	// Qtのラッパー
	virtual void KillTimer(UINT_PTR nIDEvent);
	virtual void SetCaption(const QString & lpWindowName);
	virtual void SetTimer(UINT_PTR nIDEvent, UINT nElapse);

	std::unordered_map<UINT_PTR, QTimer *> m_timers;
};
//----------------------------------------------------------------------------

#endif
