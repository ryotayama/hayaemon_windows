//----------------------------------------------------------------------------
// VolumeSlider_MainWnd.h : 音量設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef VolumeSlider_MainWndH
#define VolumeSlider_MainWndH

#include <QObject>
#include "../Common/Define.h"
#include "../Common/SliderCtrl.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 音量設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CVolumeSlider_MainWnd : public CSliderCtrl, public QObject
{
public: // 関数

	explicit CVolumeSlider_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	virtual BOOL Create();

	virtual void OnHScroll(int pos);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
