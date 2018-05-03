//----------------------------------------------------------------------------
// PanLabel_MainWnd.h : パン表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef PanLabel_MainWndH
#define PanLabel_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// パン表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CPanLabel_MainWnd : public QObject
{
public: // 関数

	explicit CPanLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd) { }

	virtual BOOL Create();
	virtual void SetPan(int nPan);

private: // メンバ変数

	CMainWnd & m_rMainWnd;

public:
	// Qtのラッパー
	virtual void Show(int nCmdShow);
};
//----------------------------------------------------------------------------

#endif
