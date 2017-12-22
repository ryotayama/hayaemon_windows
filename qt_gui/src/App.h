//----------------------------------------------------------------------------
// App.h : アプリケーションの管理を行う
//----------------------------------------------------------------------------
#ifndef AppH
#define AppH

#include <QString>
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
	QString m_strPath;

	CMainWnd * m_wnd;

public: // メンバ変数の取得・設定
	QString GetName() const { return m_cstrName; }
	QString GetFilePath() const { return m_strPath; }
};
//----------------------------------------------------------------------------

#endif // AppH
