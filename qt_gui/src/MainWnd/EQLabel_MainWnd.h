//----------------------------------------------------------------------------
// EQLabel_MainWnd.h : イコライザ ( 200Hz ) 表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef EQLabel_MainWndH
#define EQLabel_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CEQSlider_MainWnd;
class CMainWnd;
class QLabel;
class QSpinBox;
//----------------------------------------------------------------------------
// イコライザ表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CEQLabel_MainWnd : public QObject
{
public: // 関数

	explicit CEQLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), m_label(nullptr), m_spinBox(nullptr),
			m_slider(nullptr) { }
	
	void Init(QLabel * label, QSpinBox * spinBox,
						CEQSlider_MainWnd * slider);
	virtual BOOL Create();
	virtual void SetEQ(int nEQ);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	QLabel * m_label;
	QSpinBox * m_spinBox;
	CEQSlider_MainWnd * m_slider;

public:

	// Qtのラッパー
	virtual void Show(int nCmdShow);
};
//----------------------------------------------------------------------------

#endif
