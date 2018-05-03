//----------------------------------------------------------------------------
// FreqLabel_MainWnd.h : 再生周波数表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef FreqLabel_MainWndH
#define FreqLabel_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 再生周波数表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CFreqLabel_MainWnd : public QObject
{
public: // 関数

	explicit CFreqLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), m_nDecimalDigit(1) { }

	virtual BOOL Create();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetFreq(double nFreq);
	virtual void SetLimit(double dMinFreq, double dMaxFreq);

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
