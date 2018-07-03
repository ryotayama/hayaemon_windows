//----------------------------------------------------------------------------
// TimeSlider_MainWnd.cpp : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../Common/CommandList.h"
#include "Explorer.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
#include "TimeSlider_MainWnd.h"
#include "RMenu_TimeSlider.h"
#include "Sound.h"
#include "VideoScreen_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTimeSlider_MainWnd::Create()
{
	CSliderCtrl::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;

	SetStyle(GetStyle() | WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ | TBS_NOTICKS);
	ResetPos();
	ResetSize();

	SetLineSize(1);
	SetPageSize(1);

	return TRUE;
}
//----------------------------------------------------------------------------
// マーカーの削除
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::DeleteMarker()
{
	m_rMainWnd.GetSound().EraseMarker(nDeleteMarker);
	m_rMainWnd.SetTime(m_rMainWnd.GetSound().ChannelGetPosition());
}
//----------------------------------------------------------------------------
// 高さを得る
//----------------------------------------------------------------------------
int CTimeSlider_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_TIMESLIDER))
		return CSliderCtrl::GetHeight();
	else return m_rMainWnd.GetVideoScreen().GetHeight();
}
//----------------------------------------------------------------------------
// 縦位置を得る
//----------------------------------------------------------------------------
int CTimeSlider_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_TIMESLIDER))
		return CSliderCtrl::GetTop();
	else return m_rMainWnd.GetVideoScreen().GetTop();
}
//----------------------------------------------------------------------------
// 位置を再設定
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetVideoScreen().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = 0;
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		nLeft += m_rMainWnd.GetExplorer().GetWidth()
			+ m_rMainWnd.GetControlOffset() / 2;
	SetPos(nLeft, pt.y + m_rMainWnd.GetVideoScreen().GetHeight()
			+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
// サイズの再設定
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::ResetSize()
{
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	int nWidth = m_rMainWnd.GetClientWidth() - pt.x;
	SetSize(nWidth, (int)(GetSystemMetrics(SM_CYHSCROLL) * 1.5));
}
//----------------------------------------------------------------------------
// スライダをバイト単位で設定
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::SetTime(QWORD bytes, QWORD totalBytes)
{
	SetRangeMin(0);
	SetRangeMax((LONG)(totalBytes / 100000));
	SetThumbPos((LONG)(bytes / 100000));
	SetPageSize((LONG)m_rMainWnd.GetSound().ChannelGetFreq() * 4 / 100000);
}
//----------------------------------------------------------------------------
// コマンド
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CSliderCtrl::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// スクロールされた
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnHScroll(HWND hwndCtl, UINT code, int pos)
{
	QWORD trackpos = (QWORD)GetThumbPos();
	m_rMainWnd.SetTime(trackpos * 100000);
}
//----------------------------------------------------------------------------
// キーボードが押された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_CONTROL) < 0)
			m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
		break;
	case VK_CONTROL:
		bControl = TRUE;
		break;
	}
	CSliderCtrl::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// キーボードが離された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnKeyUp(UINT vk, UINT lKeyData)
{
	switch(vk)
	{
	case VK_CONTROL:
		bControl = FALSE;
		break;
	}
	CSliderCtrl::OnKeyUp(vk, lKeyData);
}
//----------------------------------------------------------------------------
// カーソル設定のタイミングが来た
//----------------------------------------------------------------------------
BOOL CTimeSlider_MainWnd::OnSetCursor(HWND hwndCursor,
									  UINT codeHitTest,
									  UINT msg)
{
	if(m_rMainWnd.GetSound().IsABLoopA()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		LONG nSelStartLeft = GetSelStartLeft();

		// カーソルの設定
		if(rc.top <= ptCsr.y && ptCsr.y <= rc.bottom) {
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nSelStartLeft - nDrag < ptCsr.x
			   && ptCsr.x < nSelStartLeft + nDrag) {
				SetCursor(LoadCursor(NULL, IDC_SIZEWE));
				return FALSE;
			}
		}
	}

	if(m_rMainWnd.GetSound().IsABLoopB()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		LONG nSelEndLeft = GetSelEndLeft();

		// カーソルの設定
		if(rc.top <= ptCsr.y && ptCsr.y <= rc.bottom) {
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nSelEndLeft - nDrag < ptCsr.x
			   && ptCsr.x < nSelEndLeft + nDrag) {
				SetCursor(LoadCursor(NULL, IDC_SIZEWE));
				return FALSE;
			}
		}
	}

	if(m_rMainWnd.IsMarkerPlay()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		QWORD length = m_rMainWnd.GetSound().ChannelGetLength();
		std::vector<QWORD> arrayMarker =
			m_rMainWnd.GetSound().GetArrayMarker();
		for(int i = 0; i < (int)arrayMarker.size(); i++) {
			double rate = (double)(int)(arrayMarker[i] / 100000)
						  / (double)(int)(length / 100000);
			int nLeft = LONG(rc.left + width * rate + 0.5);
			int nTop = rc.top + 3;
			int nRight = nLeft + 1;
			int nBottom = rc.bottom - 3;
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nTop <= ptCsr.y && ptCsr.y <= nBottom
			   && nLeft - nDrag < ptCsr.x && ptCsr.x < nRight + nDrag) {
				SetCursor(LoadCursor(NULL, IDC_SIZEWE));
				return FALSE;
			}
		}
	}

	return CSliderCtrl::OnSetCursor(hwndCursor, codeHitTest, msg);
}
//----------------------------------------------------------------------------
// クリックされた
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	if(m_rMainWnd.GetSound().IsABLoopA()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		LONG nSelStartLeft = GetSelStartLeft();

		// ドラッグの開始
		if(rc.top <= ptCsr.y && ptCsr.y <= rc.bottom) {
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nSelStartLeft - nDrag < ptCsr.x
			   && ptCsr.x < nSelStartLeft + nDrag) {
				bABLoopADrag = TRUE;
				SetCapture(m_hWnd);
				return;
			}
		}
	}

	if(m_rMainWnd.GetSound().IsABLoopB()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		LONG nSelEndLeft = GetSelEndLeft();

		// ドラッグの開始
		if(rc.top <= ptCsr.y && ptCsr.y <= rc.bottom) {
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nSelEndLeft - nDrag < ptCsr.x
			   && ptCsr.x < nSelEndLeft + nDrag) {
				bABLoopBDrag = TRUE;
				SetCapture(m_hWnd);
				return;
			}
		}
	}

	if(m_rMainWnd.IsMarkerPlay()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		QWORD length = m_rMainWnd.GetSound().ChannelGetLength();
		std::vector<QWORD> arrayMarker
			= m_rMainWnd.GetSound().GetArrayMarker();
		for(int i = 0; i < (int)arrayMarker.size(); i++) {
			double rate = (double)(int)(arrayMarker[i] / 100000)
						  / (double)(int)(length / 100000);
			int nLeft = LONG(rc.left + width * rate + 0.5);
			int nTop = rc.top + 3;
			int nRight = nLeft + 1;
			int nBottom = rc.bottom - 3;
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nTop <= ptCsr.y && ptCsr.y <= nBottom
			   && nLeft - nDrag < ptCsr.x && ptCsr.x < nRight + nDrag) {
				bDrag = TRUE;
				nDraggingMarker = i;
				qwFirstPos = arrayMarker[nDraggingMarker];
				SetCapture(m_hWnd);
				return;
			}
		}
	}

	// 選択範囲の位置を得る
	RECT rc;
	GetSelRect(&rc);

	// カーソルの位置を得る
	POINT ptCsr;
	GetCursorPos(&ptCsr);
	ScreenToClient(m_hWnd, &ptCsr);

	double dPos = ptCsr.x;
	dPos -= rc.left;
	dPos /= rc.right - rc.left;
	QWORD qwRangeMax = (QWORD)SendMessage(m_hWnd, TBM_GETRANGEMAX, 0, 0);
	QWORD qwPos = (QWORD)(dPos * qwRangeMax);
	if(qwPos < 0)
		qwPos = 0;
	else if(qwPos > qwRangeMax - m_rMainWnd.GetSound().ChannelGetFreq()
			/ 100000)
		qwPos = (QWORD)(qwRangeMax - m_rMainWnd.GetSound().ChannelGetFreq()
				/ 100000);

	m_rMainWnd.SetTime(qwPos * 100000);

	CSliderCtrl::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// クリックが離された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnLButtonUp(int x, int y, UINT keyFlags)
{
	bABLoopADrag = bABLoopBDrag = bDrag = FALSE;
	if(GetCapture() == m_hWnd) ReleaseCapture();
	CSliderCtrl::OnLButtonUp(x, y, keyFlags);
	CSliderCtrl::OnLButtonUp(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// 右クリックが離された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnRButtonUp(int x, int y, UINT keyFlags)
{
	if(m_rMainWnd.IsMarkerPlay()) {
		// 選択範囲の位置を得る
		RECT rc;
		GetSelRect(&rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		// カーソルの位置を得る
		POINT ptCsr;
		GetCursorPos(&ptCsr);
		ScreenToClient(m_hWnd, &ptCsr);

		QWORD length = m_rMainWnd.GetSound().ChannelGetLength();
		std::vector<QWORD> arrayMarker
			= m_rMainWnd.GetSound().GetArrayMarker();
		for(int i = 0; i < (int)arrayMarker.size(); i++) {
			double rate = (double)(int)(arrayMarker[i] / 100000)
						  / (double)(int)(length / 100000);
			int nLeft = LONG(rc.left + width * rate + 0.5);
			int nTop = rc.top + 3;
			int nRight = nLeft + 1;
			int nBottom = rc.bottom - 3;
			int nDrag = GetSystemMetrics(SM_CXDRAG);
			if(nTop <= ptCsr.y && ptCsr.y <= nBottom
			   && nLeft - nDrag < ptCsr.x && ptCsr.x < nRight + nDrag) {
				nDeleteMarker = i;
				m_rClickMenu.Create(TRUE);
				POINT pt;
				GetCursorPos(&pt);
				SetForegroundWindow(m_hWnd);
				TrackPopupMenu((HMENU)m_rClickMenu,
							   TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0,
							   m_hWnd, NULL);
				CSliderCtrl::OnRButtonUp(x, y, keyFlags);
				return;
			}
		}
	}
	m_rClickMenu.Create(FALSE);
	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(m_hWnd);
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x,
		pt.y, 0, m_hWnd, NULL);

	CSliderCtrl::OnRButtonUp(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// マウスが移動された
//----------------------------------------------------------------------------
void CTimeSlider_MainWnd::OnMouseMove(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		if(m_rMainWnd.GetSound().IsABLoopA() && bABLoopADrag) {
			// 選択範囲の位置を得る
			RECT rc;
			GetSelRect(&rc);

			// カーソルの位置を得る
			POINT ptCsr;
			GetCursorPos(&ptCsr);
			ScreenToClient(m_hWnd, &ptCsr);

			// AB ループの A にあたる位置を設定
			double dSelStartLeft = ptCsr.x;
			dSelStartLeft -= rc.left;
			dSelStartLeft /= rc.right - rc.left;
			QWORD qwRangeMax = (QWORD)SendMessage(m_hWnd, TBM_GETRANGEMAX, 0,
												  0);
			QWORD qwSelStart = (QWORD)(dSelStartLeft * qwRangeMax);
			QWORD qwSelEnd = (QWORD)SendMessage(m_hWnd, TBM_GETSELEND, 0L, 0L);
			if(qwSelStart < 0)
				qwSelStart = 0;
			else if(qwSelStart >=
					qwSelEnd - m_rMainWnd.GetSound().ChannelGetFreq()
					/ 100000)
				qwSelStart = qwSelEnd
							- (QWORD)m_rMainWnd.GetSound().ChannelGetFreq()
							/ 100000;

			m_rMainWnd.GetSound().SetLoopPosA(qwSelStart * 100000);

			// 現在の再生位置がループの範囲外にある場合は、修正
			QWORD trackpos = GetThumbPos();
			if(trackpos < qwSelStart)
				m_rMainWnd.SetTime(qwSelStart * 100000);
			else if(trackpos > qwSelEnd)
				m_rMainWnd.SetTime((QWORD)(qwSelEnd * 100000
								   - m_rMainWnd.GetSound().ChannelGetFreq()
								   / 2));

			SendMessage(m_hWnd, TBM_SETSELSTART, TRUE, (LPARAM)qwSelStart);
		}

		if(m_rMainWnd.GetSound().IsABLoopB() && bABLoopBDrag) {
			// 選択範囲の位置を得る
			RECT rc;
			GetSelRect(&rc);

			// カーソルの位置を得る
			POINT ptCsr;
			GetCursorPos(&ptCsr);
			ScreenToClient(m_hWnd, &ptCsr);

			// AB ループの B にあたる位置を設定
			double dSelEndLeft = ptCsr.x;
			dSelEndLeft -= rc.left;
			dSelEndLeft /= rc.right - rc.left;
			QWORD qwRangeMax = (QWORD)SendMessage(m_hWnd, TBM_GETRANGEMAX, 0,
												  0);
			QWORD qwSelStart = (QWORD)SendMessage(m_hWnd, TBM_GETSELSTART, 0L,
												  0L);
			QWORD qwSelEnd = (QWORD)(dSelEndLeft * qwRangeMax);
			if(qwSelEnd <= qwSelStart + m_rMainWnd.GetSound().ChannelGetFreq()
						  / 100000)
				qwSelEnd = qwSelStart
						   + (QWORD)m_rMainWnd.GetSound().ChannelGetFreq()
						   / 100000;
			else if(qwSelEnd > qwRangeMax) qwSelEnd = qwRangeMax;

			m_rMainWnd.GetSound().SetLoopPosB(qwSelEnd * 100000);

			// 現在の再生位置がループの範囲外にある場合は、修正
			QWORD trackpos = GetThumbPos();
			if(trackpos < qwSelStart)
				m_rMainWnd.SetTime(qwSelStart * 100000);
			else if(trackpos > qwSelEnd)
				m_rMainWnd.SetTime((QWORD)(qwSelEnd * 100000
								   - m_rMainWnd.GetSound().ChannelGetFreq()));

			SendMessage(m_hWnd, TBM_SETSELEND, TRUE, (LONG)qwSelEnd);
		}

		if(m_rMainWnd.IsMarkerPlay() && bDrag) {
			// 変更後の位置を算出

			// スライダの可動領域の位置を得る
			RECT rc;
			GetSelRect(&rc);
			int width = rc.right - rc.left; // 可動領域の幅
			int height = rc.bottom - rc.top; // 可動領域の高さ

			// カーソルの位置を得る
			POINT ptCsr;
			GetCursorPos(&ptCsr);
			ScreenToClient(m_hWnd, &ptCsr);

			QWORD length = m_rMainWnd.GetSound().ChannelGetLength();
			int csrLeft = ptCsr.x - rc.left;
			if(!bControl && csrLeft < 0) csrLeft = 0;
			else if(!bControl && csrLeft > width) csrLeft = width;
			double rate = (double)csrLeft / (double)width;
			QWORD qwDstPos = (QWORD)(length * rate);

			// 変更前の値を保存しておく
			std::vector<QWORD> arrayMarker
				= m_rMainWnd.GetSound().GetArrayMarker();
			QWORD qwSrcPos = arrayMarker[nDraggingMarker];

			if(bControl) {
				QWORD difference = qwDstPos > qwFirstPos ?
								   qwDstPos - qwFirstPos
								   : qwFirstPos - qwDstPos;
				difference /= 10;
				qwDstPos = qwDstPos > qwFirstPos ?
						   qwFirstPos + difference
						   : qwFirstPos - difference;
				if(qwDstPos < 0) qwDstPos = 0;
				else if(qwDstPos > length) qwDstPos = length;
			}

			// 変更
			nDraggingMarker
				= m_rMainWnd.GetSound().ChangeMarkerPos(nDraggingMarker,
													   qwDstPos);

			// 変更後の位置に現在の再生位置を設定
			if(m_rMainWnd.IsSetPositionAuto()) m_rMainWnd.SetTime(qwDstPos);
			else m_rMainWnd.SetTime(m_rMainWnd.GetSound().ChannelGetPosition(),
									FALSE);
		}
	}
	CSliderCtrl::OnMouseMove(x, y, keyFlags);
}
//----------------------------------------------------------------------------
