//----------------------------------------------------------------------------
// TimeLabel_MainWnd.h : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef TimeLabel_MainWndH
#define TimeLabel_MainWndH

#include <string>
#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生時間表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CTimeLabel_MainWnd : public QObject
{
public: // 関数

	explicit CTimeLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), bRemainMode(FALSE) { }

	virtual BOOL Create();
	virtual void SetTime(double time, double totalTime, BOOL bResetPos = TRUE);
	virtual void OnLButtonDown(int x, int y) {
		bRemainMode = !bRemainMode;
	}

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	BOOL bRemainMode;
	std::string strLast; // 前回描画した文字列
};
//----------------------------------------------------------------------------

#endif
