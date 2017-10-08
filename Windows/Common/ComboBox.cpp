//--------------------------------------------------------------------------
// ComboBox.cpp : コンボボックス・コントロールの作成・管理を行う
//--------------------------------------------------------------------------
#include <windows.h>
#include "ComboBox.h"
//--------------------------------------------------------------------------
// 文字の追加
//--------------------------------------------------------------------------
void CComboBox::Add(LPCTSTR lpText)
{
	SendMessage(m_hWnd, CB_ADDSTRING , 0, (LPARAM)lpText);
}
//--------------------------------------------------------------------------
// 作成
//--------------------------------------------------------------------------
BOOL CComboBox::Create(int x, int y, int cx, int cy, HWND hwnd)
{
	m_hWnd = CreateWindow(_T("COMBOBOX"), NULL, WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE, x, y, cx, cy, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);

	if(!m_hWnd) return FALSE;

	// 画面のプロパティで設定されているメッセージボックスと同じシステムフォントに設定
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
// 文字の選択
//--------------------------------------------------------------------------
tstring CComboBox::GetSelectText()
{
	int n = SendMessage(m_hWnd, CB_GETCURSEL, 0, 0);
	TCHAR text[255];
	SendMessage(m_hWnd, CB_GETLBTEXT, (WPARAM)n, (LPARAM)text);
	tstring str = text;
	return str;
}
//--------------------------------------------------------------------------
// 文字の選択
//--------------------------------------------------------------------------
void CComboBox::Select(LPCTSTR lpText)
{
	SendMessage(m_hWnd, CB_SELECTSTRING, 0, (LPARAM)lpText);
}
//--------------------------------------------------------------------------
