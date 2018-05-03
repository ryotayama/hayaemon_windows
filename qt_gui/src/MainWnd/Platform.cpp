#include "Platform.h"

#include <QString>
#include <QUrl>

//----------------------------------------------------------------------------
// WindowsのPathIsURL(Shlwapi)の再実装
//----------------------------------------------------------------------------
bool PathIsURL(const QString & path)
{
	return !QUrl::fromUserInput(path).isLocalFile();
}

