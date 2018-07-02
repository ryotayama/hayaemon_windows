//----------------------------------------------------------------------------
// Edit_MainWnd.cpp : メインウィンドウ用エディットボックスの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "../App.h"
#include "MainWnd.h"
#include "Edit_MainWnd.h"
#include "EQ125Label_MainWnd.h"
#include "EQ16KLabel_MainWnd.h"
#include "EQ1KLabel_MainWnd.h"
#include "EQ250Label_MainWnd.h"
#include "EQ2KLabel_MainWnd.h"
#include "EQ4KLabel_MainWnd.h"
#include "EQ500Label_MainWnd.h"
#include "EQ8KLabel_MainWnd.h"
#include "FreqLabel_MainWnd.h"
#include "PanLabel_MainWnd.h"
#include "SpeedLabel_MainWnd.h"
#include "VolumeLabel_MainWnd.h"
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CEdit_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	HWND hSrcFocus = GetFocus();
	tstring strDefault = _T("");
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_HOME) {
		if(hSrcFocus == m_rMainWnd.GetEQ125Label().GetEdit() ||
		   hSrcFocus == m_rMainWnd.GetEQ250Label().GetEdit() ||
		   hSrcFocus == m_rMainWnd.GetEQ500Label().GetEdit() ||
		   hSrcFocus == m_rMainWnd.GetEQ1KLabel().GetEdit()  ||
		   hSrcFocus == m_rMainWnd.GetEQ2KLabel().GetEdit()  ||
		   hSrcFocus == m_rMainWnd.GetEQ4KLabel().GetEdit()  ||
		   hSrcFocus == m_rMainWnd.GetEQ8KLabel().GetEdit()  ||
		   hSrcFocus == m_rMainWnd.GetEQ16KLabel().GetEdit() ||
		   hSrcFocus == m_rMainWnd.GetPanLabel().GetEdit())
			strDefault = _T("0");
		else if(hSrcFocus == m_rMainWnd.GetFreqLabel().GetEdit() ||
				hSrcFocus == m_rMainWnd.GetSpeedLabel().GetEdit() ||
				hSrcFocus == m_rMainWnd.GetVolumeLabel().GetEdit()) {
			strDefault = _T("100");
			if(m_nDecimalDigit > 0) {
				strDefault += _T(".");
				for(int i = 0; i < m_nDecimalDigit; i++) strDefault += _T("0");
			}
		}
	}
	if(strDefault != _T("")) {
		this->SetText(strDefault.c_str());
		PostMessage(m_hWnd, WM_LBUTTONUP, 0, 0);
		PostMessage(m_hWnd, EM_SETSEL, 0, -1);
	}
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
