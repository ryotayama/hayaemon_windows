//----------------------------------------------------------------------------
// SpeedLabel_MainWnd.h : 再生速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef SpeedLabel_MainWndH
#define SpeedLabel_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生速度表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CSpeedLabel_MainWnd : public QObject
{
public: // 関数

	explicit CSpeedLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), m_nDecimalDigit(1) { }

	virtual BOOL Create();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetSpeed(double nSpeed);
	virtual void SetLimit(double dMinSpeed, double dMaxSpeed);

private: // メンバ変数

	CMainWnd & m_rMainWnd;
	int m_nDecimalDigit; // 小数点桁数

public: // メンバ変数の取得・設定

	int GetDecimalDigit() const { return m_nDecimalDigit; }
	// Qtのラッパー
	virtual void Show(int nCmdShow);
};
//----------------------------------------------------------------------------

#endif
