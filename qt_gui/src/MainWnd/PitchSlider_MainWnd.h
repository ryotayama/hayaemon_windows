//----------------------------------------------------------------------------
// PitchSlider_MainWnd.h : 音程設定用スライダの管理を行う
//----------------------------------------------------------------------------
#ifndef PitchSlider_MainWndH
#define PitchSlider_MainWndH

#include <QObject>
#include "../Common/SliderCtrl.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 音程設定用スライダの管理を行うクラス
//----------------------------------------------------------------------------
class CPitchSlider_MainWnd : public CSliderCtrl, public QObject
{
public: // 関数

	CPitchSlider_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), m_nDecimalDigit(1) { }

	virtual BOOL Create();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetLimit(double dMinPitch, double dMaxPitch);

	virtual void OnHScroll(int pos);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	int m_nDecimalDigit; // 小数点桁数

public: // メンバ変数の取得・設定

	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif
