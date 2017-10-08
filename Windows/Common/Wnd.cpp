//----------------------------------------------------------------------------
// Wnd.cpp : ウィンドウやラベルなどの基底クラス
//----------------------------------------------------------------------------
#include <windows.h>
#include "Wnd.h"

const tstring CWnd::st_strClassPtr = _T("ClassPointer");
	// プロパティリスト ( Set/GetProp ) 用文字列
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CWnd::Create(LPCTSTR lpClassName)
{
	Destroy();

	m_hWnd = CreateWindow(lpClassName, _T(""), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ウィンドウクラスの登録
//----------------------------------------------------------------------------
ATOM CWnd::RegisterClass(LPCTSTR lpClassName)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)CWnd::WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE+1);
	wc.lpszClassName = lpClassName;

	return RegisterClassEx(&wc);
}
//----------------------------------------------------------------------------
// 親ウィンドウの設定
//----------------------------------------------------------------------------
void CWnd::SetParent(HWND hParentWnd)
{
	// 子ウィンドウにする場合のスタイルの設定
#ifdef _WIN64
	LONG_PTR lStyle = GetStyle();
#else
	LONG lStyle = GetStyle();
#endif
	if(hParentWnd) {
		lStyle &= ~WS_POPUP;
		lStyle |= WS_CHILD;
		SetStyle(lStyle);
	}

	::SetParent(m_hWnd, hParentWnd);

	// トップレベルウィンドウにする場合のスタイルの設定
	if(!hParentWnd) {
		lStyle &= ~WS_CHILD;
		lStyle |= WS_POPUP;
		SetStyle(lStyle);
	}
}
//----------------------------------------------------------------------------
// プロシージャ関連の設定
//----------------------------------------------------------------------------
void CWnd::SetProc()
{
	if(!m_hWnd) return;
	SetProp(m_hWnd, st_strClassPtr.c_str(), (HANDLE)this);
	if(GetWindowLong(m_hWnd, GWL_WNDPROC) != (LONG)WndProc)
		m_lpfnOriginalWndProc = (WNDPROC)SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)WndProc);
}
//----------------------------------------------------------------------------
// プロシージャ関連のリセット
//----------------------------------------------------------------------------
void CWnd::ResetProc()
{
	if(!m_hWnd) return;
	if(m_lpfnOriginalWndProc)
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_lpfnOriginalWndProc);
	RemoveProp(m_hWnd, st_strClassPtr.c_str());
}
//----------------------------------------------------------------------------
// ウィンドウプロシージャ
//----------------------------------------------------------------------------
LRESULT CALLBACK CWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = (CWnd*)GetProp(hWnd, st_strClassPtr.c_str());
	if(!pWnd) {
		if(uMsg == WM_CREATE || uMsg == WM_NCCREATE)
			pWnd = (CWnd*)((LPCREATESTRUCT)lParam)->lpCreateParams;

		if(pWnd) {
			pWnd->m_hWnd = hWnd;
			pWnd->SetProc();
		}
	}

	if(pWnd) {
		switch(uMsg)
		{
		case WM_CHAR:
			pWnd->OnChar((TCHAR)wParam, (int)(short)LOWORD(lParam));
			return 0;
		case WM_CLOSE:
			pWnd->OnClose();
			return 0;
		case WM_COMMAND:
			pWnd->OnCommand((int)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));
			return 0;
		case WM_CONTEXTMENU:
			return pWnd->OnContextMenu((HWND)wParam, (int)LOWORD(lParam),
				(int)HIWORD(lParam));
		case WM_CREATE:
			return pWnd->OnCreate((LPCREATESTRUCT)lParam);
		case WM_CTLCOLORSTATIC:
			return (LRESULT)pWnd->OnCtlColorStatic((HDC)wParam, (HWND)lParam);
		case WM_DESTROY:
			pWnd->OnDestroy();
			return 0;
		case WM_DROPFILES:
			pWnd->OnDropFiles((HDROP)wParam);
			return 0;
		case WM_ENTERSIZEMOVE:
			pWnd->OnEnterSizeMove();
			return 0;
		case WM_ERASEBKGND:
			return pWnd->OnEraseBkgnd((HDC)wParam);
		case WM_EXITSIZEMOVE:
			pWnd->OnExitSizeMove();
			return 0;
		case WM_GETMINMAXINFO:
			pWnd->OnGetMinMaxInfo((LPMINMAXINFO)lParam);
			return 0;
		case WM_HOTKEY:
			pWnd->OnHotKey((int)wParam, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
			return 0;
		case WM_HSCROLL:
			pWnd->OnHScroll((HWND)lParam, (UINT)LOWORD(wParam), (int)(short)HIWORD(wParam));
			return 0;
		case WM_KEYDOWN:
			pWnd->OnKeyDown((UINT)wParam, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam));
			return 0;
		case WM_KEYUP:
			pWnd->OnKeyUp((UINT)wParam, (UINT)lParam);
			return 0;
		case WM_LBUTTONDBLCLK:
			pWnd->OnLButtonDoubleClick((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)wParam);
			return 0;
		case WM_LBUTTONDOWN:
			pWnd->OnLButtonDown((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)wParam);
			return 0;
		case WM_LBUTTONUP:
			pWnd->OnLButtonUp((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)wParam);
			return 0;
		case WM_RBUTTONUP:
			pWnd->OnRButtonUp((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)wParam);
			return 0;
		case WM_MOUSEMOVE:
			pWnd->OnMouseMove((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)wParam);
			return 0;
		case WM_MOUSEWHEEL:
			return pWnd->OnMouseWheel(GET_KEYSTATE_WPARAM(wParam), GET_WHEEL_DELTA_WPARAM(wParam),
				MAKEPOINTS(lParam));
		case WM_MOVING:
			return pWnd->OnMoving((UINT)wParam, (LPRECT)lParam);
		case WM_NOTIFY:
			return pWnd->OnNotify((int)wParam, (NMHDR*)lParam);
		case WM_PAINT:
			pWnd->OnPaint();
			return 0;
		case WM_SETCURSOR:
			return pWnd->OnSetCursor((HWND)wParam, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
		case WM_SIZE:
			pWnd->OnSize((UINT)wParam, (int)LOWORD(lParam), (int)HIWORD(lParam));
			return 0;
		case WM_SIZING:
			return pWnd->OnSizing((UINT)wParam, (LPRECT)lParam);
		case WM_SYSCOMMAND:
			pWnd->OnSysCommand((UINT)wParam, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam));
			return 0;
		case WM_TIMER:
			pWnd->OnTimer((UINT)wParam);
			return 0;
		case WM_TRAY:
			pWnd->OnTray((UINT)lParam);
			return 0;
		case WM_VSCROLL:
			pWnd->OnVScroll((HWND)lParam, (UINT)LOWORD(wParam), (int)(short)HIWORD(wParam));
			return 0;
		}
		LRESULT lResult = pWnd->WindowProc(uMsg, wParam, lParam);
		if(uMsg == WM_DESTROY) pWnd->ResetProc();
		return lResult;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//----------------------------------------------------------------------------
// ウィンドウプロシージャ ( オーバーライド可 )
//----------------------------------------------------------------------------
LRESULT CWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_lpfnOriginalWndProc)
		return CallWindowProc(m_lpfnOriginalWndProc, m_hWnd, uMsg, wParam, lParam);
	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}
//----------------------------------------------------------------------------
