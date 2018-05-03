//----------------------------------------------------------------------------
// PitchLabel_MainWnd.h : 音程表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef PitchLabel_MainWndH
#define PitchLabel_MainWndH

#include <QObject>
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 音程表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CPitchLabel_MainWnd : public QObject
{
public: // 関数

	explicit CPitchLabel_MainWnd(CMainWnd & mainWnd)
		: m_rMainWnd(mainWnd), m_nDecimalDigit(1) { }

	virtual BOOL Create();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetPitch(double nPitch);
	virtual void SetLimit(double dMinPitch, double dMaxPitch);

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
