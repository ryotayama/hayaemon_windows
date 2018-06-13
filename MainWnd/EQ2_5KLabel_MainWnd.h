//----------------------------------------------------------------------------
// EQ2_5KLabel_MainWnd.h : イコライザ ( 2.5KHz ) 表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#ifndef EQ2_5KLabel_MainWndH
#define EQ2_5KLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_EQCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// イコライザ ( 2.5KHz ) 表示用ラベルの管理を行うクラス
//----------------------------------------------------------------------------
class CEQ2_5KLabel_MainWnd : public CStatic
{
public: // 関数

	CEQ2_5KLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd, _T('-')) { }
	virtual ~CEQ2_5KLabel_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void SetEQ2_5K(int nEQ2_5K);
	virtual void ResetPos();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnVScroll(HWND hwndCtl, UINT code, int pos);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;
	CEdit_MainWnd m_edit;
	CUpDownCtrl m_ud;
	CRMenu_EQCtrl m_rClickMenu; // 右クリックメニュー

public: // メンバ変数の取得・設定

	const CEdit_MainWnd & GetEdit() const { return m_edit; }
};
//----------------------------------------------------------------------------

#endif