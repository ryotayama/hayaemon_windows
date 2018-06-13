//----------------------------------------------------------------------------
// TimeLabel_MainWnd.cpp : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "TimeLabel_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTimeLabel_MainWnd::Create()
{
	CStatic::Create(SS_NOTIFY);
	if(!m_hWnd) return FALSE;
	SetParent(m_rMainWnd);

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	SetSize(GetTextWidth(_T("88:88:88 / 88:88:88")),
		GetTextHeight(_T("88:88:88 / 88:88:88")));

	POINT pt;
	pt.y = m_rMainWnd.GetDivider1().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetControlOffset(), pt.y +
		   m_rMainWnd.GetDivider1().GetHeight());

	CClientDC dc(m_hWnd);
	hMemDc = CreateCompatibleDC(dc);
	hMemBmp = CreateCompatibleBitmap(dc, GetWidth(), GetHeight());
	SelectObject(hMemDc, hMemBmp);
	SelectObject(hMemDc, GetStockObject(NULL_PEN));
	SelectObject(hMemDc, CreateSolidBrush(GetSysColor(COLOR_3DFACE)));
	Rectangle(hMemDc, 0, 0, GetWidth()+1, GetHeight()+1);
	DeleteObject(SelectObject(hMemDc, GetStockObject(WHITE_BRUSH)));
	SelectObject(hMemDc, (HFONT)m_font);
	SetBkMode(hMemDc, TRANSPARENT);

	Show(SW_SHOW);
	return TRUE;
}
//----------------------------------------------------------------------------
// 位置の再設定
//----------------------------------------------------------------------------
void CTimeLabel_MainWnd::ResetPos()
{
	// ウィンドウの右端に設定
	SetPos(m_rMainWnd.GetClientWidth() - GetWidth() -
		   m_rMainWnd.GetControlOffset(), 2 + m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
// 表示する時間を秒単位で設定
//----------------------------------------------------------------------------
void CTimeLabel_MainWnd::SetTime(double time, double totalTime, BOOL bResetPos)
{
	if(time < 0) time = 0;
	if(totalTime < 0) totalTime = 0;
	if(bRemainMode) time = totalTime - time;

	int hour = (int)(time / 3600) % 60;
	int second = (int)(time / 60) % 60;
	int minute = (int)time % 60;

	int totalHour = (int)(totalTime / 3600) % 60;
	int totalSecond = (int)(totalTime / 60) % 60;
	int totalMinute = (int)totalTime % 60;

	TCHAR text[20];
	if(totalHour > 0)
		_stprintf_s(text, _T("%02d:%02d:%02d / %02d:%02d:%02d"), hour, second,
					minute, totalHour, totalSecond, totalMinute);
	else
	{
		if(totalTime == 0.0 && time != 0.0)
			_stprintf_s(text, _T("%02d:%02d / --:--"), second, minute);
		else
			_stprintf_s(text, _T("%02d:%02d / %02d:%02d"), second, minute,
					totalSecond, totalMinute);
	}

	if(bResetPos) {
		SetSize(GetTextWidth(text), GetTextHeight(text));
		ResetPos();
	}

	if(strLast == text) return;
	strLast = text;

	SelectObject(hMemDc, GetStockObject(NULL_PEN));
	SelectObject(hMemDc, CreateSolidBrush(GetSysColor(COLOR_3DFACE)));
	Rectangle(hMemDc, 0, 0, GetWidth()+1, GetHeight()+1);
	DeleteObject(SelectObject(hMemDc, GetStockObject(WHITE_BRUSH)));
	TextOut(hMemDc, 0, 0, text, lstrlen(text));
	InvalidateRect(NULL, FALSE);
}
//----------------------------------------------------------------------------
// 描画
//----------------------------------------------------------------------------
void CTimeLabel_MainWnd::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hDc = BeginPaint(m_hWnd, &ps );
	BitBlt(hDc, 0, 0, GetWidth(), GetHeight(), hMemDc, 0, 0, SRCCOPY);
	EndPaint(m_hWnd, &ps);

	CStatic::OnPaint();
}
//----------------------------------------------------------------------------
