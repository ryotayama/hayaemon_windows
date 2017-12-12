//----------------------------------------------------------------------------
// VolumeLabel_MainWnd.h : 音量表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef VolumeLabel_MainWndH
#define VolumeLabel_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 音量表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CVolumeLabel_MainWnd : public QObject
{
public: // 関数
	explicit CVolumeLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	virtual BOOL Create();
	virtual void SetVolume(double nVolume);

private: // メンバ変数

	CMainWnd & m_rMainWnd;

public:
	// Qtのラッパー
	virtual void Show(int nCmdShow);
};
//----------------------------------------------------------------------------

#endif
