//----------------------------------------------------------------------------
// EQSlider_MainWnd.h : イコライザ ( 100Hz ) 設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef EQSlider_MainWndH
#define EQSlider_MainWndH

#include <functional>
#include <QObject>
#include "../Common/Define.h"
#include "../Common/SliderCtrl.h"
class CEQLabel_MainWnd;
class CMainWnd;
class CSliderCtrlCore;
//----------------------------------------------------------------------------
// イコライザ設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CEQSlider_MainWnd : public CSliderCtrl, public QObject
{
public: // 関数

	explicit CEQSlider_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	void Init(CSliderCtrlCore * slider, CEQLabel_MainWnd * label,
						std::function<void(LONG)> setEQ);
	virtual BOOL Create();

	virtual void OnHScroll(int pos);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	CEQLabel_MainWnd * m_label;
	std::function<void(LONG)> m_setEQ;
};
//----------------------------------------------------------------------------

#endif
