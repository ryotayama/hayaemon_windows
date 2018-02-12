//----------------------------------------------------------------------------
// App.cpp : アプリケーションの管理を行う
//----------------------------------------------------------------------------
#include "App.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <QTranslator>
#include "./MainWnd/MainWnd.h"
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

	// 翻訳のインストール
	QTranslator ts;
	if(ts.load(":/translation/Hayaemon_ja.qm")) {
		app.installTranslator(&ts);
	}
	
	m_cstrName = QObject::tr("Hayaemon");

	QString filePath = QCoreApplication::applicationFilePath();
	QString fileName = QFileInfo(filePath).fileName();
	m_strPath = filePath.left(filePath.length() - fileName.length());
	m_strPath = QDir::toNativeSeparators(m_strPath);

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
