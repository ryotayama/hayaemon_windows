//----------------------------------------------------------------------------
// FreqLabel_MainWnd.h : 再生周波数表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef FreqLabel_MainWndH
#define FreqLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_FreqCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 再生周波数表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CFreqLabel_MainWnd : public CStatic
{
public: // 関数

	CFreqLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd, _T('.')), m_nDecimalDigit(1) { }
	virtual ~CFreqLabel_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetFreq(double nFreq);
	virtual void SetLimit(double dMinFreq, double dMaxFreq);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CStatic m_percentLabel; // 「%」表示用ラベル
	CFont m_font;
	CEdit_MainWnd m_edit;
	CUpDownCtrl m_ud;
	int m_nDecimalDigit; // 小数点桁数
	CRMenu_FreqCtrl m_rClickMenu; // 右クリックメニュー

public: // メンバ変数の取得・設定

	const CEdit_MainWnd & GetEdit() const { return m_edit; }
	const CUpDownCtrl & GetUpDownCtrl() const { return m_ud; }
	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif