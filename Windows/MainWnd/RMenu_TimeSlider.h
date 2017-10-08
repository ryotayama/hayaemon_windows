//----------------------------------------------------------------------------
// RMenu_TimeSlider.h : 再生時間設定用スライダ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_TimeSliderH
#define RMenu_TimeSliderH

class CTimeSlider_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// メインウィンドウ用メニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_TimeSlider : public CMenu
{
public: // 関数

	CRMenu_TimeSlider(CTimeSlider_MainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_TimeSlider() { }

	virtual BOOL Create(BOOL bOnMarker);
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnDeleteMenuSelected();
	void OnVisibleMenuSelected();

private: // メンバ変数

	CTimeSlider_MainWnd & m_rParent;

public: // 定数

	// コマンド ID
	enum {
		// 削除メニュー
		ID_DELETE = 11,
		ID_VISIBLE,
	};
};
//----------------------------------------------------------------------------

#endif