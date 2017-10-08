//----------------------------------------------------------------------------
// PitchLabel_MainWnd.h : 音程表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef PitchLabel_MainWndH
#define PitchLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_PitchCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 音程表示用ラベル用エディットボックスの管理を行うクラス
//----------------------------------------------------------------------------
class CEdit_PitchLabel : public CEdit
{
public: // 関数

	CEdit_PitchLabel(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_PitchLabel() { }

	virtual void OnChar(TCHAR ch, int cRepeat) {
		DWORD dwSel;
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&dwSel, (LPARAM)NULL);
		tstring strText = GetText();
		if(dwSel != 0 && ch == '.' && strText.find(_T(".")) == -1)
			CEdit::OnChar(ch, cRepeat);
		else if(dwSel == 0 && ch == '-' && strText.find(_T("-")) == -1)
			CEdit::OnChar(ch, cRepeat);
		else if(IsCharAlphaNumeric(ch) && !IsCharAlpha(ch))
			CEdit::OnChar(ch, cRepeat);
		else if(ch == _T('\b'))
			CEdit::OnChar(ch, cRepeat);
		else if(ch == _T('\t'))
			return;
		else
			MessageBeep(MB_OK);
	}
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// 音程表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CPitchLabel_MainWnd : public CStatic
{
public: // 関数

	CPitchLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd), m_nDecimalDigit(1) { }
	virtual ~CPitchLabel_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetPitch(double nPitch);
	virtual void SetLimit(double dMinPitch, double dMaxPitch);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;
	CEdit_PitchLabel m_edit;
	CUpDownCtrl m_ud;
	int m_nDecimalDigit; // 小数点桁数
	CRMenu_PitchCtrl m_rClickMenu; // 右クリックメニュー

public: // メンバ変数の取得・設定

	const CEdit_PitchLabel & GetEdit() const { return m_edit; }
	const CUpDownCtrl & GetUpDownCtrl() const { return m_ud; }
	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif