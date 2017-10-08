//----------------------------------------------------------------------------
// ClientDC.h : ウィンドウのクライアント領域用デバイスコンテキストの管理を行う
//----------------------------------------------------------------------------
#ifndef ClientDCH
#define ClientDCH

#include "DC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ウィンドウのクライアント領域用デバイスコンテキストの管理を行うクラス
//----------------------------------------------------------------------------
class CClientDC : public CDC
{
public: // 関数

	CClientDC(HWND hWnd) {
		m_hWnd = hWnd;
		m_hDC = GetDC(m_hWnd);
	}
	virtual ~CClientDC() { }

	virtual void Destroy() {
		if(m_hDC) ReleaseDC(m_hWnd, m_hDC), m_hWnd = 0, m_hDC = 0;
	}

protected: // メンバ変数

	HWND m_hWnd;
};
//----------------------------------------------------------------------------

#endif