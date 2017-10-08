//―――――――――――――――――――――――――――――――――――――
// ComboBox.h : コンボボックス・コントロールの作成・管理を行う
//―――――――――――――――――――――――――――――――――――――
#ifndef ComboBoxH
#define ComboBoxH

#include "Wnd.h"
#include "Font.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
//	コンボボックス・コントロールの作成・管理を行うクラス
//--------------------------------------------------------------------------
class CComboBox : public CWnd
{
public: // 関数

	CComboBox() { }
	virtual ~CComboBox() { }

	virtual void Add(LPCTSTR);
	virtual BOOL Create(int, int, int, int, HWND);
	virtual void Select(LPCTSTR);
	virtual tstring GetSelectText();

private: // メンバ変数

	CFont m_font;
};
//--------------------------------------------------------------------------

#endif