//----------------------------------------------------------------------------
// SliderCtrlCore.h : QSliderの拡張
//----------------------------------------------------------------------------
#ifndef SliderCtrlCoreH
#define SliderCtrlCoreH

#include <QMouseEvent>
#include <QSlider>
//----------------------------------------------------------------------------
// QSliderの拡張クラス
//----------------------------------------------------------------------------
class CSliderCtrlCore : public QSlider
{
	Q_OBJECT

public: // 関数

	explicit CSliderCtrlCore(QWidget * parent = nullptr) : QSlider(parent) { }

	void mousePressEvent(QMouseEvent * event) override {
		QSlider::mousePressEvent(event);
		auto p = event->pos();
		emit OnLButtonDown(p.x(), p.y());
	}

signals:
	void OnLButtonDown(int x, int y);
};
//----------------------------------------------------------------------------

#endif
