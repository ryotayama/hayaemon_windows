//----------------------------------------------------------------------------
// DoubleSpinBox.h : QDoubleSpinBoxの拡張
//----------------------------------------------------------------------------
#ifndef DoubleSpinBoxH
#define DoubleSpinBoxH

#include <QEvent>
#include <QLineEdit>
#include <QDoubleSpinBox>
//----------------------------------------------------------------------------
// QDoubleSpinBoxの拡張クラス
//----------------------------------------------------------------------------
class CDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT

public: // 関数

	explicit CDoubleSpinBox(QWidget * parent = nullptr)
		: QDoubleSpinBox(parent), m_cannotMoveMouse(false) {
		connect(this, &CDoubleSpinBox::focused, this, &QDoubleSpinBox::selectAll,
						Qt::QueuedConnection);
		this->lineEdit()->installEventFilter(this);
	}

protected:

	void focusInEvent(QFocusEvent *event) override {
		QDoubleSpinBox::focusInEvent(event);
		m_cannotMoveMouse = true;
		emit focused();
	}

	bool eventFilter(QObject * obj, QEvent * event) override {
		if (obj == this->lineEdit()) {
			if (event->type() == QEvent::MouseMove) {
				if (m_cannotMoveMouse) {
					return true;
				}
			} else if (event->type() == QEvent::MouseButtonRelease) {
				m_cannotMoveMouse = false;
			}
		}
		return QDoubleSpinBox::eventFilter(obj, event);
	}

signals:
	void focused();

private:
	bool m_cannotMoveMouse;
};
//----------------------------------------------------------------------------

#endif
