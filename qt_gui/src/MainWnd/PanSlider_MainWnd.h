//----------------------------------------------------------------------------
// PanSlider_MainWnd.h : ボリューム設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef PanSlider_MainWndH
#define PanSlider_MainWndH

#include <QObject>
#include "../Common/SliderCtrl.h"
class CMainWnd;
//----------------------------------------------------------------------------
// ボリューム設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CPanSlider_MainWnd : public CSliderCtrl, public QObject
{
public: // 関数

	explicit CPanSlider_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	virtual BOOL Create();

	virtual void OnHScroll(int pos);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
