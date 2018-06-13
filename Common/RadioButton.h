//--------------------------------------------------------------------------
// RadioButton.h : ラジオボタンの作成・管理を行う
//--------------------------------------------------------------------------
#ifndef RadioButtonH
#define RadioButtonH

#include "Button.h"
#include "Font.h"
#include "ClientDC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
// ラジオボタンの作成・管理を行うクラス
//--------------------------------------------------------------------------
class CRadioButton : public CButton
{
public: // 関数

	CRadioButton() { }
	virtual ~CRadioButton() { }

	virtual BOOL Create(LPCTSTR, int, int, int, int, HWND);
	virtual BOOL Create(LPCTSTR, HWND);

private: // メンバ変数

};
//--------------------------------------------------------------------------

#endif
