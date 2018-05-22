//----------------------------------------------------------------------------
// App.h : アプリケーションの管理を行う
//----------------------------------------------------------------------------
#ifndef AppH
#define AppH

#include <QString>
#include "Common/Define.h"
class CMainWnd;
class QString;
//----------------------------------------------------------------------------
// アプリケーションの管理を行うクラス
//----------------------------------------------------------------------------
class CApp
{
public: // 関数

	CApp();
	~CApp();

	int Run(int argc, char *argv[]); // 実行
	void ShowError(const QString & strError); // エラーを出力して終了

private: // メンバ変数

	QString m_cstrName; // アプリケーションの名前
	QString m_cstrVersionInfo; // バージョン情報
	QString m_cstrAuthorName; // 作者名
	QString m_cstrAuthorEMail; // 作者のメールアドレス
	QString m_cstrAuthorWebSiteName; // 作者のサイト名
	QString m_cstrAuthorURL; // 作者のサイトのアドレス
	QString m_strPath;

	CMainWnd * m_wnd;

public: // メンバ変数の取得・設定
	QString GetName() const { return m_cstrName; }
	QString GetFilePath() const { return m_strPath; }
	QString GetVersionInfo() const { return m_cstrVersionInfo; }
	QString GetAuthorName() const { return m_cstrAuthorName; }
	QString GetAuthorEMail() const { return m_cstrAuthorEMail; }
	QString GetAuthorWebSiteName() const { return m_cstrAuthorWebSiteName; }
	QString GetAuthorURL() const { return m_cstrAuthorURL; }
	tstring GetSettingFilePath() const;
};
//----------------------------------------------------------------------------

#endif // AppH
