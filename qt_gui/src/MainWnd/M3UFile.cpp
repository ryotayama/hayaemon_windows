//--------------------------------------------------------------------------
// M3UFile.cpp : M3Uファイルの管理を行う
//--------------------------------------------------------------------------
#include "M3UFile.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include "Utility.h"
//--------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------
CM3UFile::CM3UFile()
	:isLoaded(false)
{
}
//--------------------------------------------------------------------------
// ファイルパスを得る
//--------------------------------------------------------------------------
tstring CM3UFile::GetFilePath(int num)
{
	if(!isLoaded || !buffer.size()) return _T("");
	return buffer[num];
}
//--------------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------------
void CM3UFile::Init()
{
	isLoaded = false;
	buffer.clear();
}
//--------------------------------------------------------------------------
// 読み込み
//--------------------------------------------------------------------------
void CM3UFile::Read(const PCTSTR & pFilePath, BOOL bUtf8)
{
	QFile file(ToQString(pFilePath));
	if(!file.open(QIODevice::ReadOnly)) return;

	Init();

	QString strPath =
			QFileInfo(ToQString(pFilePath)).dir().absolutePath() + QDir::separator();

	QTextStream in(&file);
	while(!in.atEnd()) {
		QString strName = in.readLine();

		QString strPathName = strPath + strName;
		QFileInfo info(strPathName);
		QFileInfo info_r(strName);
		if(info.exists() && info.isFile())
			// 相対パス
			buffer.push_back(ToTstring(strPathName));
		else if(info_r.exists() && info_r.isFile())
			// 絶対パス
			buffer.push_back(ToTstring(strName));
	}

	isLoaded = true;
}
//--------------------------------------------------------------------------
// 保存
//--------------------------------------------------------------------------
void CM3UFile::Save(const PCTSTR & pFilePath, tstring str, BOOL bUtf8)
{
	QFile file(ToQString(pFilePath));
	if(!file.open(QIODevice::WriteOnly)) return;

	QTextStream out(&file);
	if(bUtf8) out.setCodec("UTF-8");

	out << ToQString(str);
}
//--------------------------------------------------------------------------
