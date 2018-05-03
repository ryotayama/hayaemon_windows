//----------------------------------------------------------------------------
// StaticCore.h : QLabelの拡張
//----------------------------------------------------------------------------
#ifndef StaticCoreH
#define StaticCoreH

#include <QMouseEvent>
#include <QLabel>
//----------------------------------------------------------------------------
// QLabelの拡張クラス
//----------------------------------------------------------------------------
class CStaticCore : public QLabel
{
	Q_OBJECT

public: // 関数

	explicit CStaticCore(QWidget * parent = nullptr) : QLabel(parent) { }

	void mousePressEvent(QMouseEvent * event) override {
		QLabel::mousePressEvent(event);
		auto p = event->pos();
		emit OnLButtonDown(p.x(), p.y());
	}

signals:
	void OnLButtonDown(int x, int y);
};
//----------------------------------------------------------------------------

#endif
