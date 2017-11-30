//----------------------------------------------------------------------------
// MainWnd.h : メインウィンドウの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH

class CApp;
class CPlayListView_MainWnd;
class QTimer;
class QUrl;
#include <unordered_map>
#include <vector>
#include <QList>
#include <QMainWindow>
#include "../Common/Define.h"
#include "Menu_MainWnd.h"
#include "Sound.h"
#include "ToolBar_MainWnd.h"
#include "ui_MainWnd.h"
//----------------------------------------------------------------------------
// メインウィンドウの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMainWnd : public QMainWindow, public Ui::MainWnd
{
  Q_OBJECT

public: // 関数

	CMainWnd(CApp & app): m_rApp(app), m_menu(*this), m_toolBar(*this),
		nCurPlayTab(0) { }

	virtual void AddDropFiles(const QList<QUrl> & urls, BOOL bClear);
	virtual BOOL Create() { return OnCreate(); }
	virtual BOOL CreateControls();
	virtual BOOL OpenFile(const QString & lpszFilePath, int nCount = 1);
	virtual BOOL OpenNext();
	virtual void Pause();
	virtual BOOL Play();
	virtual void PlayNext(BOOL bPlay, BOOL bFadeoutCancel);
	virtual void SetTime(QWORD qwTime, BOOL bReset = TRUE);
	virtual void Stop(BOOL bForce = TRUE);

	virtual LRESULT OnCreate();

protected: // メンバ変数

	CApp & m_rApp;
	CMenu_MainWnd m_menu;
	CToolBar_MainWnd m_toolBar;
	std::vector<CPlayListView_MainWnd*> m_arrayList;

	CSound m_sound;

	int nCurPlayTab; // 現在再生中のファイルが存在しているタブ

public: // 定数

	// タイマー ID
	enum {
		IDT_TIME = 11,
	};

public: // メンバ変数の取得・設定

	CPlayListView_MainWnd & GetCurPlayList() {
		return *m_arrayList[nCurPlayTab];
	}

private:

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
