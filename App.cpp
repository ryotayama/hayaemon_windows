//----------------------------------------------------------------------------
// App.cpp : アプリケーションの管理を行う
//----------------------------------------------------------------------------
#include <windows.h>
#include "App.h"
//----------------------------------------------------------------------------
// WinMain 関数
//----------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CApp app(nCmdShow);
	return app.Run();
}
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CApp::CApp(const int & nCmdShow)
#if JP
	: m_nCmdShow(nCmdShow), 
#ifdef NDEBUG
	  m_cstrName(_T("聞々ハヤえもん")),
#endif // NDEBUG

#ifdef _DEBUG
	  m_cstrName(_T("聞々ハヤえもん Debug")),
#endif

	  m_cstrAuthorName(_T("りょーた")),
	  m_cstrAuthorEMail(_T("ryota.yamauch@gmail.com")),
	  m_cstrAuthorWebSiteName(_T("聞々ハヤえもん公式サイト")),
#else // JP
	: m_nCmdShow(nCmdShow),
#ifdef NDEBUG
	  m_cstrName(_T("Hayaemon")),
#endif // NDEBUG

#ifdef _DEBUG
	  m_cstrName(_T("Hayaemon Debug")),
#endif // DEBUG

	  m_cstrAuthorName(_T("Ryota")),
	  m_cstrAuthorEMail(_T("ryota.yamauch@gmail.com")),
	  m_cstrAuthorWebSiteName(_T("Hayaemon Official Website")),
#endif // JP
	  m_cstrVersionInfo(_T("2.77β12")),
	  m_cstrAuthorURL(_T("http://hayaemon.jp/")),
	  m_wnd(*this)
{
	TCHAR pathName[MAX_PATH] = _T("");
	if(GetModuleFileName(NULL, pathName, MAX_PATH)) {
		TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR];
		_tsplitpath_s(pathName, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0,
					  NULL, 0);
		TCHAR path[_MAX_DRIVE + _MAX_DIR];
		lstrcpy(path, drive);
		lstrcat(path, dir);
		m_strPath = path;
	}

	char chPathName[MAX_PATH] = "";
	if(GetModuleFileNameA(NULL, chPathName, MAX_PATH)) {
		char chDrive[_MAX_DRIVE], chDir[_MAX_DIR];
		_splitpath_s(chPathName, chDrive, _MAX_DRIVE, chDir, _MAX_DIR, NULL,
			0, NULL, 0);
		char chPath[_MAX_DRIVE + _MAX_DIR];
		strcpy_s(chPath, chDrive);
		strcat_s(chPath, chDir);
		m_strPathA = chPath;
	}
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CApp::~CApp()
{
}
//----------------------------------------------------------------------------
// 多重起動のチェック
//----------------------------------------------------------------------------
BOOL CApp::CheckDoubleRun()
{
	HANDLE hMutex = CreateMutex(NULL, false, m_cstrName.c_str());
	if(!hMutex) {
#if JP
		ShowError(_T("ミューテックスオブジェクトの作成に失敗しました。"));
#else // JP
		ShowError(_T("failed to create mutex object."));
#endif // JP
		return TRUE;
	}

	if(GetLastError() == ERROR_ALREADY_EXISTS) {
		HWND hWnd = FindWindow(_T("Hayaemon_MainWndClass"), NULL);
		if(hWnd && !IsWindowVisible(hWnd)) {
			while(IsWindow(hWnd)) {
				// 前回終了待ち
			}
		}

		TCHAR buf[255];
		GetPrivateProfileString(_T("Options"), _T("DoubleRun"), _T("1"), buf,
								255, (GetFilePath() +
								_T("Setting.ini")).c_str());
		if(_ttoi(buf)) return FALSE;

		if(hWnd) {
			if(IsIconic(hWnd)) ShowWindowAsync(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);

			// アイコンにドロップされたファイルを渡す
			if(__argc > 1) {
				COPYDATASTRUCT cd;
				cd.dwData = __argc;
				cd.cbData = 0;
				for (int i = 0; i < __argc; i++)
					cd.cbData += (_tcslen(__targv[i]) + 1) * sizeof(TCHAR);
				cd.lpData = *__targv;
				SendMessage(hWnd, WM_COPYDATA, 0L, (LPARAM)&cd);
			}
		}
		return TRUE;
	}
	return FALSE;
}
//----------------------------------------------------------------------------
// 実行
//----------------------------------------------------------------------------
int CApp::Run()
{
	_tsetlocale(LC_ALL, _T(""));

	if(CheckDoubleRun()) return 0;
	if(!m_wnd.Create()) return 0;

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		if(!TranslateAccelerator(m_wnd, m_accelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
//----------------------------------------------------------------------------
// エラーを出力して終了
//----------------------------------------------------------------------------
void CApp::ShowError(tstring strError)
{
#if JP
	tstring _strError = strError + _T("\nアプリケーションを終了します。");
	MessageBox(m_wnd, _strError.c_str(), _T("エラー"), MB_ICONERROR);
#else // JP
	tstring _strError = strError + _T("\nApplication exit.");
	MessageBox(m_wnd, _strError.c_str(), _T("Error"), MB_ICONERROR);
#endif // JP
	m_wnd.Destroy();
}
//----------------------------------------------------------------------------
