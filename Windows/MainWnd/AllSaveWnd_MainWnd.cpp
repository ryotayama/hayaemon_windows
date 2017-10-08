//----------------------------------------------------------------------------
// AllSaveWnd_MainWnd.cpp : 一括変換ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "AllSaveWnd_MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CAllSaveWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("AllSaveWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("AllSaveWndCls"), _T(""),
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// コマンドが送られた
//----------------------------------------------------------------------------
void CAllSaveWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
		bOk = TRUE;
		break;
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// 作成された
//----------------------------------------------------------------------------
LRESULT CAllSaveWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(320, 90, FALSE);
	SetPos(m_rMainWnd.GetLeft() + m_rMainWnd.GetWidth() / 2 - GetWidth() / 2,
		   m_rMainWnd.GetTop() + m_rMainWnd.GetHeight() / 2 - GetHeight() / 2);

	// 不要なシステムメニューを削除
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // セパレータ

	EnableWindow(m_rMainWnd, FALSE);

	if(!m_Combo.Create(10, 10, 300, 480, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("コンボボックスの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create combobox."));
#endif // JP
		return FALSE;
	}

#if JP
	m_Combo.Add(_T("WAVEファイル(*.wav)"));
	m_Combo.Add(_T("MP3ファイル(*.mp3)"));
	m_Combo.Add(_T("Ogg Vorbisファイル(*.ogg)"));
#else // JP
	m_Combo.Add(_T("WAVE file(*.wav)"));
	m_Combo.Add(_T("MP3 file(*.mp3)"));
	m_Combo.Add(_T("Ogg Vorbis file(*.ogg)"));
#endif // JP
	tstring strSaveFormat = m_rMainWnd.GetStrSaveFormat();
	if(strSaveFormat == _T("MP3"))
#if JP
		m_Combo.Select(_T("MP3ファイル(*.mp3)"));
#else // JP
		m_Combo.Select(_T("MP3 file(*.mp3)"));
#endif // JP
	else if(strSaveFormat == _T("OGG"))
#if JP
		m_Combo.Select(_T("Ogg Vorbisファイル(*.ogg)"));
#else // JP
		m_Combo.Select(_T("Ogg Vorbis file(*.ogg)"));
#endif // JP
	else
#if JP
		m_Combo.Select(_T("WAVEファイル(*.wav)"));
#else // JP
		m_Combo.Select(_T("WAVE file(*.wav)"));
#endif // JP

	if(!m_OkButton.Create(_T("OK"), 124, 63, 90, 22, m_hWnd, ID_OK)) {
#if JP
		m_rApp.ShowError(_T("OK ボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}

	if(!m_CancelButton.Create(
#if JP
							  _T("キャンセル"),
#else // JP
							  _T("Cancel"),
#endif // JP
							  222, 63, 90, 22, m_hWnd, ID_CANCEL)) {
#if JP
		m_rApp.ShowError(_T("キャンセルボタンの作成に失敗しました。"));
#else // JP
		m_rApp.ShowError(_T("failed to create cancel button."));
#endif // JP
		return FALSE;
	}

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
