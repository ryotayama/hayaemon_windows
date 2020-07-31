//----------------------------------------------------------------------------
// Wnd.h : ウィンドウやラベルなどの基底クラス
//----------------------------------------------------------------------------
#ifndef WndH
#define WndH

#include <tchar.h>
#include <string>
#include "Define.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ウィンドウやラベルなどの基底クラス
//----------------------------------------------------------------------------
class CWnd
{
public: // 関数

	CWnd(): m_hWnd(0), m_lpfnOriginalWndProc(NULL) { }
	virtual ~CWnd() { Destroy(); }

	virtual void Close() {
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
	virtual BOOL Create(LPCTSTR lpClassName);
	virtual void Destroy() {
		if(m_hWnd) DestroyWindow(m_hWnd), m_hWnd = 0;
	}
	virtual ATOM RegisterClass(LPCTSTR lpClassName); // ウィンドウクラスの登録
	virtual tstring GetCaption() const {
		int nCaptionLength = GetWindowTextLength(m_hWnd) + 1;
		TCHAR * pszCaption = new TCHAR[nCaptionLength];
		GetWindowText(m_hWnd, pszCaption, nCaptionLength);
		tstring strCaption = pszCaption;
		delete [] pszCaption;
		return strCaption;
	}
	virtual int GetBottom() const {
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		return rc.bottom;
	}
	virtual int GetClientHeight() const {
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		return rc.bottom - rc.top;
	}
	virtual int GetClientWidth() const {
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		return rc.right - rc.left;
	}
	virtual HFONT GetFont() const {
		return (HFONT)SendMessage(m_hWnd, WM_GETFONT, 0, 0);
	}
	virtual int GetHeight() const {
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		return rc.bottom - rc.top;
	}
	virtual int GetLeft() const {
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		return rc.left;
	}
	virtual int GetRight() const {
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		return rc.right;
	}
#ifdef _WIN64
	virtual LONG_PTR GetExStyle() const {
		return GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);
	}
#else
	virtual LONG GetExStyle() const {
		return GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);
	}
#endif
#ifdef _WIN64
	virtual LONG_PTR GetStyle() const {
		return GetWindowLongPtr(m_hWnd, GWL_STYLE);
	}
#else
	virtual LONG GetStyle() const {
		return GetWindowLongPtr(m_hWnd, GWL_STYLE);
	}
#endif
	virtual int GetTop() const {
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		return rc.top;
	}
	virtual int GetWidth() const {
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		return rc.right - rc.left;
	}
	virtual BOOL InvalidateRect(const RECT *lpRect, BOOL bErase) {
		return ::InvalidateRect(m_hWnd, lpRect, bErase);
	}
	virtual void KillTimer(UINT_PTR nIDEvent) {
		::KillTimer(m_hWnd, nIDEvent);
	}
	virtual void SetCaption(LPCTSTR lpWindowName) {
		SetWindowText(m_hWnd, lpWindowName);
	}
	virtual void SetClientSize(int cx, int cy, BOOL bMenu) {
		RECT rc = {0, 0, cx, cy};
		AdjustWindowRect(&rc, (DWORD)GetStyle(), bMenu);
		SetWindowPos(m_hWnd, 0, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	}
#ifdef _WIN64
	virtual void SetExStyle(LONG_PTR lStyle) {
		SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, lStyle);
	}
#else
	virtual void SetExStyle(LONG lStyle) {
		SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, lStyle);
	}
#endif
	virtual void SetFont(HFONT hFont, BOOL fRedraw = TRUE) {
		SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)fRedraw);
	}
#ifdef _WIN64
	virtual void SetIcon(HICON hIcon, BOOL bBigIcon) {
		SetClassLongPtr(m_hWnd, bBigIcon ? GCLP_HICON : GCLP_HICONSM, (LONG_PTR)hIcon);
	}
#else
	virtual void SetIcon(HICON hIcon, BOOL bBigIcon) {
		SetClassLongPtr(m_hWnd, bBigIcon ? GCLP_HICON : GCLP_HICONSM, (LONG)hIcon);
	}
#endif
	virtual void SetParent(HWND hParentWnd);
	virtual void SetPos(int x, int y) {
		SetWindowPos(m_hWnd, NULL, x, y, NULL, NULL,
						SWP_NOSIZE | SWP_NOZORDER);
	}
	virtual void SetProc(); // プロシージャ関連の設定
	virtual void ResetProc(); // プロシージャ関連のリセット
	virtual void SetSize(int cx, int cy) {
		SetWindowPos(m_hWnd, NULL, NULL, NULL, cx, cy,
						SWP_NOMOVE | SWP_NOZORDER);
	}
#ifdef _WIN64
	virtual void SetStyle(LONG_PTR lStyle) {
		SetWindowLongPtr(m_hWnd, GWL_STYLE, lStyle);
	}
#else
	virtual void SetStyle(LONG lStyle) {
		SetWindowLongPtr(m_hWnd, GWL_STYLE, lStyle);
	}
#endif
	virtual void SetTimer(UINT_PTR nIDEvent, UINT nElapse) {
		::SetTimer(m_hWnd, nIDEvent, nElapse, NULL);
	}
	virtual void Show(int nCmdShow) { ShowWindow(m_hWnd, nCmdShow); }
	virtual void Update() { UpdateWindow(m_hWnd); }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
									LPARAM lParam);
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
		// オーバーライド可

	// メッセージ
	virtual void OnChar(TCHAR ch, int cRepeat) {
		WindowProc(WM_CHAR, (WPARAM)ch, MAKELPARAM((cRepeat),0));
	}
	virtual void OnClose() {
		WindowProc(WM_CLOSE, 0L, 0L);
	}
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos) {
		return WindowProc(WM_CONTEXTMENU, (WPARAM)hwnd, MAKELPARAM(yPos, xPos));
	}
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify) {
		WindowProc(WM_COMMAND, MAKEWPARAM((UINT)id, (UINT)codeNotify), (LPARAM)hwndCtl);
	}
	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct) {
		return WindowProc(WM_CREATE, 0, (LPARAM)lpCreateStruct);
	}
	virtual HBRUSH OnCtlColorStatic(HDC hDc, HWND hWnd) {
		return (HBRUSH)WindowProc(WM_CTLCOLORSTATIC, (WPARAM)hDc, (LPARAM)hWnd);
	}
	virtual void OnDestroy() {
		WindowProc(WM_DESTROY, 0L, 0L);
	}
	virtual void OnDropFiles(HDROP hdrop) {
		WindowProc(WM_DROPFILES, (WPARAM)hdrop, 0L);
	}
	virtual void OnEnterSizeMove() {
		WindowProc(WM_ENTERSIZEMOVE, 0L, 0L);
	}
	virtual BOOL OnEraseBkgnd(HDC hDc) {
		return WindowProc(WM_ERASEBKGND, (WPARAM)hDc, 0L);
	}
	virtual void OnExitSizeMove() {
		WindowProc(WM_EXITSIZEMOVE, 0L, 0L);
	}
	virtual void OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo) {
		WindowProc(WM_GETMINMAXINFO, 0L, (LPARAM)lpMinMaxInfo);
	}
	virtual void OnHotKey(int idHotKey, UINT fuModifiers, UINT vk) {
		WindowProc(WM_HOTKEY, (WPARAM)idHotKey, MAKELPARAM(fuModifiers, vk));
	}
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos) {
		WindowProc(WM_HSCROLL, MAKEWPARAM((UINT)(int)code, (UINT)pos), (LPARAM)hwndCtl);
	}
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags) {
		WindowProc(WM_KEYDOWN, (WPARAM)vk, MAKELPARAM(cRepeat, flags));
	}
	virtual void OnKeyUp(UINT vk, UINT lKeyData) {
		WindowProc(WM_KEYUP, (WPARAM)vk, (LPARAM)lKeyData);
	}
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags) {
		WindowProc(WM_LBUTTONDBLCLK, (WPARAM)keyFlags, MAKELPARAM(x, y));
	}
	virtual void OnLButtonDown(int x, int y, UINT keyFlags) {
		WindowProc(WM_LBUTTONDOWN, (WPARAM)keyFlags, MAKELPARAM(x, y));
	}
	virtual void OnLButtonUp(int x, int y, UINT keyFlags) {
		WindowProc(WM_LBUTTONUP, (WPARAM)keyFlags, MAKELPARAM(x, y));
	}
	virtual void OnRButtonUp(int x, int y, UINT keyFlags) {
		WindowProc(WM_RBUTTONUP, (WPARAM)keyFlags, MAKELPARAM(x, y));
	}
	virtual void OnMouseMove(int x, int y, UINT keyFlags) {
		WindowProc(WM_MOUSEMOVE, (WPARAM)keyFlags, MAKELPARAM(x, y));
	}
	virtual BOOL OnMouseWheel(UINT nFlags, int zDelta, POINTS pt) {
		return WindowProc(WM_MOUSEWHEEL, MAKEWPARAM(nFlags, zDelta),
			MAKELPARAM(pt.x, pt.y));
	}
	virtual LRESULT OnMoving(UINT nSide, LPRECT lpRect) {
		return WindowProc(WM_MOVING, (WPARAM)nSide, (LPARAM)lpRect);
	}
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr) {
		return WindowProc(WM_NOTIFY, (WPARAM)idFrom, (LPARAM)pnmhdr);
	}
	virtual void OnPaint() {
		WindowProc(WM_PAINT, 0L, 0L);
	}
	virtual BOOL OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg) {
		return WindowProc(WM_SETCURSOR, (WPARAM)hwndCursor, MAKELPARAM(codeHitTest, msg));
	}
	virtual void OnSize(UINT state, int cx, int cy) {
		WindowProc(WM_SIZE, (WPARAM)state, MAKELPARAM(cx, cy));
	}
	virtual LRESULT OnSizing(UINT nSide, LPRECT lpRect) {
		return WindowProc(WM_SIZING, (WPARAM)nSide, (LPARAM)lpRect);
	}
	virtual void OnSysCommand(UINT cmd, int x, int y) {
		WindowProc(WM_SYSCOMMAND, (WPARAM)cmd, MAKELPARAM(x, y));
	}
	virtual void OnTimer(UINT id) {
		WindowProc(WM_TIMER, (WPARAM)id, 0L);
	}
	virtual void OnTray(UINT uMsg) {
		WindowProc(WM_TRAY, 0L, (LPARAM)uMsg);
	}
	virtual void OnVScroll(HWND hwndCtl, UINT code, int pos) {
		WindowProc(WM_VSCROLL, MAKEWPARAM((UINT)(int)code, (UINT)pos), (LPARAM)hwndCtl);
	}
	virtual void OnDeviceChange(UINT nEventType, DWORD_PTR dwData) {
		WindowProc(WM_DEVICECHANGE, (WPARAM)nEventType, (LPARAM)dwData);
	}
	virtual void SetPreviousFocus() { };
	virtual void SetNextFocus() { };
	virtual void OnReturnKeyPressed() { };
	virtual void OnEscKeyPressed() { };
	virtual void OnSpaceKeyPressed() { };
	virtual void OnUpKeyPressed() { };
	virtual void OnDownKeyPressed() { };
	virtual void OnLeftKeyPressed() { };
	virtual void OnRightKeyPressed() { };

protected: // メンバ変数

	HWND m_hWnd;
	WNDPROC m_lpfnOriginalWndProc; // 元のウィンドウプロシージャのアドレス
	static const tstring st_strClassPtr;
		// プロパティリスト ( Set/GetProp ) 用文字列

public: // メンバ変数の取得・設定

	operator HWND() const { return m_hWnd; }
};
//----------------------------------------------------------------------------

#endif