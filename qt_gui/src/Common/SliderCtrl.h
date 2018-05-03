//----------------------------------------------------------------------------
// SliderCtrl.h : スライダコントロールの管理を行う
//----------------------------------------------------------------------------
#ifndef SliderCtrlH
#define SliderCtrlH

#include <QRect>
#include <QStyleOption>
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
	virtual void GetSelRect(QRect * lpRc) const
	{
		*lpRc = m_slider->GetSpaceAvailabel();
	}
	virtual LONG GetSelEndLeft() const
	{
		QRect rc;
		GetSelRect(&rc);

		LONG lSelEnd = m_slider->GetSelEnd();
		LONG lRangeMax = GetRangeMax();
		double dSelEndLeft = (double)lSelEnd / (double)lRangeMax;
		dSelEndLeft *= rc.width();
		dSelEndLeft += rc.left();
		return (int)dSelEndLeft;
	}
	virtual LONG GetSelStartLeft() const
	{
		QRect rc;
		GetSelRect(&rc);

		LONG lSelStart = m_slider->GetSelStart();
		LONG lRangeMax = GetRangeMax();
		double dSelStartLeft = (double)lSelStart / (double)lRangeMax;
		dSelStartLeft *= rc.width();
		dSelStartLeft += rc.left();
		return (int)dSelStartLeft;
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

protected: // メンバ変数
	CSliderCtrlCore * m_slider = nullptr;
};
//----------------------------------------------------------------------------

#endif
