//----------------------------------------------------------------------------
// 音程表示用ラベル用スピンボックス
//----------------------------------------------------------------------------
#ifndef PitchSpinBoxH
#define PitchSpinBoxH

#include <QDoubleSpinBox>
//----------------------------------------------------------------------------
// 音程表示用ラベル用スピンボックスクラス
//----------------------------------------------------------------------------
class CPitchSpinBox : public QDoubleSpinBox
{
public:
	CPitchSpinBox(QWidget * parent = nullptr) : QDoubleSpinBox(parent) { }

	QString textFromValue(double value) const override
	{
		if (value > 0) {
			return u8"＃" + QDoubleSpinBox::textFromValue(value);
		} else if (value < 0) {
			return u8"♭" + QDoubleSpinBox::textFromValue(-value);
		} else {
			return QDoubleSpinBox::textFromValue(value);
		}
	}
	double valueFromText(const QString &text) const override
	{
		auto t = text.trimmed();
		double sign = 1;
		if (t.startsWith(u8"♭")) {
			return -t.mid(1).toDouble();
		} else if (t.startsWith(u8"＃")) {
			return t.mid(1).toDouble();
		} else {
			return t.toDouble();
		}
	}
};
//----------------------------------------------------------------------------

#endif
