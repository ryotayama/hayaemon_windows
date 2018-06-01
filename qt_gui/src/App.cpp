//----------------------------------------------------------------------------
// App.cpp : アプリケーションの管理を行う
//----------------------------------------------------------------------------
#include "App.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QLocale>
#include <QMessageBox>
#include <QStandardPaths>
#include <QString>
#include <QTranslator>
#include "./MainWnd/MainWnd.h"
#include "./MainWnd/Platform.h"
#include "./MainWnd/Utility.h"
//----------------------------------------------------------------------------
// main 関数
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	CApp app;
	return app.Run(argc, argv);
}
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CApp::CApp()
	: m_wnd(nullptr)
{
}
//----------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
CApp::~CApp()
{
}
//----------------------------------------------------------------------------
// 実行
//----------------------------------------------------------------------------
int CApp::Run(int argc, char *argv[])
{
	QApplication app(argc, argv);

	qRegisterMetaType<QVector<int>>();

	QString filePath = QCoreApplication::applicationFilePath();
	QString fileName = QFileInfo(filePath).fileName();
	m_strPath = filePath.left(filePath.length() - fileName.length());
	m_strPath = QDir::toNativeSeparators(m_strPath);

	// 翻訳のインストール
	TCHAR lang[255];
	GetPrivateProfileString(_T("Options"), _T("Language"), _T(""), lang, 255,
													ToTstring(m_strPath + "Setting.ini").c_str());
	if (lstrcmp(lang, _T("")) == 0) {
		QString loc = QLocale::system().name();
		loc.truncate(loc.lastIndexOf('_'));
		if (loc == "ja") {
			lstrcpy(lang, _T("ja"));
		}
	}
	QTranslator ts;
	if (lstrcmp(lang, _T("ja")) == 0) { 
		if(ts.load(":/translation/Hayaemon_ja.qm")) {
			app.installTranslator(&ts);
		}
	}
	
	m_cstrName = QObject::tr("Hayaemon");
	m_cstrVersionInfo = u8"0.01β3";
	m_cstrAuthorName = QObject::tr("Ryota");
	m_cstrAuthorEMail = "ryota.yamauch@gmail.com";
	m_cstrAuthorWebSiteName = QObject::tr("Free Software Development Station");
	m_cstrAuthorURL = "http://soft.edolfzoku.com/";

	CMainWnd mainWnd(*this);
	m_wnd = &mainWnd;
	if(!m_wnd->Create()) return 0;

	m_wnd->show();

	return app.exec();
}
//----------------------------------------------------------------------------
// エラーを出力して終了
//----------------------------------------------------------------------------
void CApp::ShowError(const QString & strError)
{
	QString str = QString(QObject::tr("%1\nApplication exit.")).arg(strError);
	QMessageBox::critical(m_wnd, QObject::tr("Error"), str);
	m_wnd->close();
}
//----------------------------------------------------------------------------
// 設定ファイルのパスを取得する
//----------------------------------------------------------------------------
tstring CApp::GetSettingFilePath() const
{
#if __APPLE__
	auto dir =
			QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
	auto path = dir + "/Hayaemon/Setting.ini";
	path = QDir::cleanPath(path);
	return ToTstring(path);
#else
	return ToTstring(m_strPath + "Setting.ini");
#endif
}
//----------------------------------------------------------------------------
