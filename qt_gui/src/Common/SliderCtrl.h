//----------------------------------------------------------------------------
// SliderCtrl.h : スライダコントロールの管理を行う
//----------------------------------------------------------------------------
#ifndef SliderCtrlH
#define SliderCtrlH

#include "Define.h"
#include "SliderCtrlCore.h"
//----------------------------------------------------------------------------
// スライダコントロールの管理を行うクラス
//----------------------------------------------------------------------------
class CSliderCtrl
{
public: // 関数

	virtual ~CSliderCtrl() { }

	virtual void Init(CSliderCtrlCore * slider) { m_slider = slider; }
	virtual LONG GetRangeMin() const {
		return m_slider->minimum();
	}
	virtual LONG GetRangeMax() const {
		return m_slider->maximum();
	}
	virtual LONG GetThumbPos() const {
		return (LONG)m_slider->value();
	}
	virtual LRESULT SetLineSize(LONG lLineSize)
	{
		int old = m_slider->singleStep();
		m_slider->setSingleStep(lLineSize);
		return old;
	}
	virtual int SetPageSize(LONG lPageSize)
	{
		int old = m_slider->pageStep();
		m_slider->setPageStep(lPageSize);
		return old;
	}
	virtual void SetRangeMax(LONG lMax, BOOL bRedraw = FALSE)
	{
		m_slider->setMaximum(lMax);
	}
	virtual void SetRangeMin(LONG lMin, BOOL bRedraw = FALSE)
	{
		m_slider->setMinimum(lMin);
	}
	virtual void SetThumbPos(LONG lPos, BOOL bRedraw = TRUE)
	{
		m_slider->setValue(lPos);
	}
	virtual void Show(int nCmdShow)
	{
		m_slider->setVisible(nCmdShow != SW_HIDE);
	}

private: // メンバ変数
	CSliderCtrlCore * m_slider = nullptr;
};
//----------------------------------------------------------------------------

#endif
