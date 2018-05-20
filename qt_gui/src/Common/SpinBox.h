//----------------------------------------------------------------------------
// SpinBox.h : QSpinBoxの拡張
//----------------------------------------------------------------------------
#ifndef SpinBoxH
#define SpinBoxH

#include <QEvent>
#include <QLineEdit>
#include <QSpinBox>
//----------------------------------------------------------------------------
// QSpinBoxの拡張クラス
//----------------------------------------------------------------------------
class CSpinBox : public QSpinBox
{
	Q_OBJECT

public: // 関数

	explicit CSpinBox(QWidget * parent = nullptr)
		: QSpinBox(parent), m_cannotMoveMouse(false) {
		connect(this, &CSpinBox::focused, this, &QSpinBox::selectAll,
						Qt::QueuedConnection);
		this->lineEdit()->installEventFilter(this);
	}

protected:

	void focusInEvent(QFocusEvent *event) override {
		QSpinBox::focusInEvent(event);
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
		return QSpinBox::eventFilter(obj, event);
	}

signals:
	void focused();

private:
	bool m_cannotMoveMouse;
};
//----------------------------------------------------------------------------

#endif
