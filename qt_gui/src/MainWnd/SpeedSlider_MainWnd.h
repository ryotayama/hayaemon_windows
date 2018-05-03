//----------------------------------------------------------------------------
// SpeedSlider_MainWnd.h : 再生速度設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef SpeedSlider_MainWndH
#define SpeedSlider_MainWndH

#include <QObject>
#include "../Common/Define.h"
#include "../Common/SliderCtrl.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生速度設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CSpeedSlider_MainWnd : public CSliderCtrl, public QObject
{
public: // 関数

	explicit CSpeedSlider_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), m_nDecimalDigit(1) { }

	virtual BOOL Create();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetLimit(double dMinSpeed, double dMaxSpeed);

	virtual void OnHScroll(int pos);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	int m_nDecimalDigit; // 小数点桁数

public: // メンバ変数の取得・設定

	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif
