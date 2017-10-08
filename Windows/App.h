//----------------------------------------------------------------------------
// App.h : アプリケーションの管理を行う
//----------------------------------------------------------------------------
#ifndef AppH
#define AppH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
#include <TCHAR.H>
#include "./MainWnd/MainWnd.h"
#include "./Common/AcceleratorTable.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// アプリケーションの管理を行うクラス
//----------------------------------------------------------------------------
class CApp
{
public: // 関数

	CApp(const int & nCmdShow);
	~CApp();

	BOOL CheckDoubleRun(); // 多重起動のチェック
	int Run(); // 実行
	void ShowError(tstring strError); // エラーを出力して終了

private: // メンバ変数

	const int m_nCmdShow; // 初期表示状態
	const tstring m_cstrName; // アプリケーションの名前
	const tstring m_cstrVersionInfo; // バージョン情報
	const tstring m_cstrAuthorName; // 作者名
	const tstring m_cstrAuthorEMail; // 作者のメールアドレス
	const tstring m_cstrAuthorWebSiteName; // 作者のサイト名
	const tstring m_cstrAuthorURL; // 作者のサイトのアドレス
	tstring m_strPath;
	std::string m_strPathA;

	CMainWnd m_wnd;
	CAcceleratorTable m_accelTable;

public: // メンバ変数の取得・設定

	int GetNCmdShow() const { return m_nCmdShow; }
	tstring GetName() const { return m_cstrName; }
	tstring GetVersionInfo() const { return m_cstrVersionInfo; }
	tstring GetAuthorName() const { return m_cstrAuthorName; }
	tstring GetAuthorEMail() const { return m_cstrAuthorEMail; }
	tstring GetAuthorWebSiteName() const { return m_cstrAuthorWebSiteName; }
	tstring GetAuthorURL() const { return m_cstrAuthorURL; }
	tstring GetFilePath() const { return m_strPath; }
	std::string GetFilePathA() const { return m_strPathA; }
	CAcceleratorTable & GetAccelTable() { return m_accelTable; }
};
//----------------------------------------------------------------------------

#endif // AppH