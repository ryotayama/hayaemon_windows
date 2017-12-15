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
	void OnResetSpeedMenuSelected();
	void OnSetSpeed50MenuSelected();
	void OnSetSpeed60MenuSelected();
	void OnSetSpeed70MenuSelected();
	void OnSetSpeed80MenuSelected();
	void OnSetSpeed90MenuSelected();
	void OnSetSpeed100MenuSelected();
	void OnSetSpeed110MenuSelected();
	void OnSetSpeed120MenuSelected();
	void OnSetSpeed130MenuSelected();
	void OnSetSpeed140MenuSelected();
	void OnSetSpeed150MenuSelected();
	void OnSetSpeed160MenuSelected();
	void OnSetSpeed170MenuSelected();
	void OnSetSpeed180MenuSelected();
	void OnSetSpeed190MenuSelected();
	void OnSetSpeed200MenuSelected();
	void OnSetSpeed250MenuSelected();
	void OnSetSpeed300MenuSelected();
	void OnSetSpeed350MenuSelected();
	void OnSetSpeed400MenuSelected();
	void OnDown0_1SpeedMenuSelected();
	void OnDown1SpeedMenuSelected();
	void OnDown2SpeedMenuSelected();
	void OnDown3SpeedMenuSelected();
	void OnDown5SpeedMenuSelected();
	void OnDown10SpeedMenuSelected();
	void OnUp0_1SpeedMenuSelected();
	void OnUp1SpeedMenuSelected();
	void OnUp2SpeedMenuSelected();
	void OnUp3SpeedMenuSelected();
	void OnUp5SpeedMenuSelected();
	void OnUp10SpeedMenuSelected();
	void OnSetSpeedDecimal0MenuSelected();
	void OnSetSpeedDecimal1MenuSelected();
	void OnSetSpeedDecimal2MenuSelected();
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
	void CreateActionGroups();
	void CreateConnections();
};
//----------------------------------------------------------------------------

#endif
