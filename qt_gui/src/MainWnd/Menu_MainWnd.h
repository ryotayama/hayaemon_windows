//----------------------------------------------------------------------------
// Menu_MainWnd.h : メインウィンドウ用メニューの作成・管理を行う
//----------------------------------------------------------------------------
#ifndef Menu_MainWndH
#define Menu_MainWndH

#include <unordered_map>
#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
class QAction;
//----------------------------------------------------------------------------
// メインウィンドウ用メニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CMenu_MainWnd : public QObject
{
public: // 関数

	CMenu_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	virtual BOOL Create();
	void OnVolumeMenuSelected(bool checked);
	void OnPanMenuSelected(bool checked);
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
	std::unordered_map<UINT, QAction*> m_actionMap;

public:
	// Qtのラッパー
	void CheckItem(UINT uIDCheckItem, UINT uCheck);
	BOOL IsItemChecked(UINT uID);

private:
	// Qtのラッパー
	void CreateActionMap();
	void CreateConnections();
};
//----------------------------------------------------------------------------

#endif
