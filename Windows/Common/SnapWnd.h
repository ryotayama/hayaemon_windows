//----------------------------------------------------------------------------
// SnapWnd.h : スナップウィンドウクラス
//----------------------------------------------------------------------------
#ifndef SnapWndH
#define SnapWndH

#include "FrameWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// フレームウィンドウクラス
//----------------------------------------------------------------------------
class CSnapWnd : public CFrameWnd
{
public: // 関数

	CSnapWnd(): m_nSnapRange(24) { }
	virtual ~CSnapWnd() { }

	virtual void OnEnterSizeMove()
	{
		POINT pt;
		GetCursorPos(&pt);
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		m_nCsrLeftToLeft = rc.left - pt.x;
		m_nCsrLeftToRight = rc.right - pt.x;
		m_nCsrTopToTop = rc.top - pt.y;
		m_nCsrTopToBottom = rc.bottom - pt.y;

		CFrameWnd::OnEnterSizeMove();
	}

	virtual LRESULT OnMoving(UINT nSide, LPRECT lpRect)
	{
		// マウスカーソルの位置を得る
		POINT pt;
		GetCursorPos(&pt);

		// ウィンドウの位置
		int left = pt.x + m_nCsrLeftToLeft;
		int top = pt.y + m_nCsrTopToTop;
		int right = pt.x + m_nCsrLeftToRight;
		int bottom = pt.y + m_nCsrTopToBottom;

		RECT rc;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

		int width = right - left;
		int height = bottom - top;

		// 横位置
		if(top <= rc.bottom && bottom >= rc.top)
		{
			// 右位置
			if(rc.right - m_nSnapRange < right && right < rc.right + m_nSnapRange)
			{
				right = rc.right;
				left = right - width;
			}

			// 左位置
			if(rc.left - m_nSnapRange < left && left < rc.left + m_nSnapRange)
			{
				left = rc.left;
				right = left + width;
			}
		}

		// 縦位置
		if(left <= rc.right && right >= rc.left)
		{
			// 下位置
			bottom = top + height;
			if(rc.bottom - m_nSnapRange < bottom && bottom < rc.bottom + m_nSnapRange)
			{
				bottom = rc.bottom;
				top = bottom - height;
			}

			// 上位置
			if(rc.top - m_nSnapRange < top && top < rc.top + m_nSnapRange)
			{
				top = rc.top;
				bottom = top + height;
			}
		}

		// 位置の設定
		lpRect->left = left;
		lpRect->right = right;
		lpRect->top = top;
		lpRect->bottom = bottom;

		return TRUE;
	}

	virtual LRESULT OnSizing(UINT nSide, LPRECT lpRect)
	{
		// マウスカーソルの位置を得る
		POINT pt;
		GetCursorPos(&pt);

		// ウィンドウの位置
		int left = lpRect->left;
		int right = lpRect->right;
		int top = lpRect->top;
		int bottom = lpRect->bottom;

		RECT rc;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

		// 左位置
		if(nSide == WMSZ_LEFT || nSide == WMSZ_TOPLEFT || nSide == WMSZ_BOTTOMLEFT)
		{
			if(rc.left - m_nSnapRange < pt.x && pt.x < rc.left + m_nSnapRange)
				left = rc.left;
		}

		// 右位置
		if(nSide == WMSZ_RIGHT || nSide == WMSZ_TOPRIGHT || nSide == WMSZ_BOTTOMRIGHT)
		{
			if(rc.right - m_nSnapRange < pt.x && pt.x < rc.right + m_nSnapRange)
				right = rc.right;
		}

		// 上位置
		if(nSide == WMSZ_TOP || nSide == WMSZ_TOPLEFT || nSide == WMSZ_TOPRIGHT)
		{
			if(rc.top - m_nSnapRange < pt.y && pt.y < rc.top + m_nSnapRange)
				top = rc.top;
		}

		// 下位置
		if(nSide == WMSZ_BOTTOM || nSide == WMSZ_BOTTOMLEFT || nSide == WMSZ_BOTTOMRIGHT)
		{
			if(rc.bottom - m_nSnapRange < pt.y && pt.y < rc.bottom + m_nSnapRange)
				bottom = rc.bottom;
		}

		// 位置の設定
		lpRect->left = left;
		lpRect->right = right;
		lpRect->top = top;
		lpRect->bottom = bottom;

		return TRUE;
	}

protected: // メンバ変数

	int m_nCsrLeftToLeft; // カーソルからウィンドウの左端までの位置
	int m_nCsrLeftToRight; // カーソルからウィンドウの右端までの位置
	int m_nCsrTopToTop; // カーソルからウィンドウの上端までの位置
	int m_nCsrTopToBottom; // カーソルからウィンドウの下端までの位置
	int m_nSnapRange;

public: // メンバ変数の取得・設定

};
//----------------------------------------------------------------------------

#endif