//----------------------------------------------------------------------------
// Menu_MainWnd.h : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef Menu_MainWndH
#define Menu_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// メインウィンドウ用メニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMenu_MainWnd : public QObject
{
public: // 関数

	CMenu_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	virtual BOOL Create();
	void OnPauseMenuSelected();
	void OnStopMenuSelected();
	void OnResetVolumeMenuSelected();
	void OnSetVolume0MenuSelected();
	void OnSetVolume10MenuSelected();
	void OnSetVolume20MenuSelected();
	void OnSetVolume30MenuSelected();
	void OnSetVolume40MenuSelected();
	void OnSetVolume50MenuSelected();
	void OnSetVolume60MenuSelected();
	void OnSetVolume70MenuSelected();
	void OnSetVolume80MenuSelected();
	void OnSetVolume90MenuSelected();
	void OnSetVolume100MenuSelected();

private: // メンバ変数

	CMainWnd & m_rMainWnd;

private:
	// Qtのラッパー
	void CreateConnections();
};
//----------------------------------------------------------------------------

#endif
