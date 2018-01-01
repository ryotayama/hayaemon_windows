//----------------------------------------------------------------------------
// SliderCtrlCore.h : QSliderの拡張
//----------------------------------------------------------------------------
#ifndef SliderCtrlCoreH
#define SliderCtrlCoreH

#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QSlider>
#include <QStyleOption>
#include <QStylePainter>
#include "Define.h"
//----------------------------------------------------------------------------
// QSliderの拡張クラス
//----------------------------------------------------------------------------
class CSliderCtrlCore : public QSlider
{
	Q_OBJECT

public: // 関数

	explicit CSliderCtrlCore(QWidget * parent = nullptr)
		: QSlider(parent), m_selRangeEnabled(false), m_selStart(0), m_selEnd(0) { }

	void SetSelRangeEnabled(bool enabled) {
		m_selRangeEnabled = enabled;
	}
	LONG GetSelStart() const { return m_selStart; }
	void SetSelStart(LONG pos) {
		m_selStart = pos;
	}
	LONG GetSelEnd() const { return m_selEnd; }
	void SetSelEnd(LONG pos) {
		m_selEnd = pos;
	}
	void GetThumbRect(QRect * lpRc) const {
		QStyleOptionSlider opt;
		this->initStyleOption(&opt);

		QStyle * styl = style();
		*lpRc = styl->subControlRect(QStyle::CC_Slider, &opt,
																 QStyle::SC_SliderHandle, nullptr);
	}
	QRect GetSpaceAvailabel() const {
		QStyleOptionSlider opt;
		this->initStyleOption(&opt);

		QStyle * styl = this->style();
		int avl = styl->pixelMetric(QStyle::PM_SliderSpaceAvailable, &opt, this);

		auto rc = this->rect();
		int diff = rc.width() - avl;
		rc.setLeft(rc.left() + diff / 2);
		rc.setRight(rc.right() - diff / 2);
		return rc;
	}
	void mousePressEvent(QMouseEvent * event) override {
		QSlider::mousePressEvent(event);
		auto p = event->pos();
		emit OnLButtonDown(p.x(), p.y());
	}
	void mouseMoveEvent(QMouseEvent * event) override {
		QSlider::mouseMoveEvent(event);
		auto p = event->pos();
		emit OnMouseMove(p.x(), p.y());
	}
	void mouseReleaseEvent(QMouseEvent * event) override {
		QSlider::mouseReleaseEvent(event);
		auto p = event->pos();
		emit OnLButtonUp(p.x(), p.y());
	}

signals:
	void OnLButtonDown(int x, int y);
	void OnLButtonUp(int x, int y);
	void OnMouseMove(int x, int y);

protected:

	void paintEvent(QPaintEvent * e) final {
		if (!m_selRangeEnabled) {
			QSlider::paintEvent(e);
			return;
		}

		auto rc = this->rect();
		QPainter p(this);
		QBrush brush(Qt::white);
		p.setBrush(brush);
		p.drawRect(rc);
		
		int min = this->minimum();
		int max = this->maximum();
		double t = (m_selStart - min) / static_cast<double>(max - min);
		rc = GetSpaceAvailabel();
		auto rc2 = rc;
		rc2.setLeft(rc.width() * t + rc.left());
		t = (m_selEnd - min) / static_cast<double>(max - min);
		rc2.setRight(rc.width() * t + rc.left());

		QBrush brush2(QColor(51, 153, 255));
		p.setBrush(brush2);
		p.drawRect(rc2);

		QStyleOptionSlider opt;
		this->initStyleOption(&opt);
		opt.subControls = QStyle::SC_SliderHandle;

		QStylePainter painter(this);
		painter.drawComplexControl(QStyle::CC_Slider, opt);
	}

private:

	bool m_selRangeEnabled;
	LONG m_selStart;
	LONG m_selEnd;
};
//----------------------------------------------------------------------------

#endif
