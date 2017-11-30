//----------------------------------------------------------------------------
// Utility.h : ヘルパー関数
//----------------------------------------------------------------------------
#ifndef UtilityH
#define UtilityH

#include <QString>
#include "../Common/Define.h"

class QString;

tstring ToTstring(const QString & str)
{
#ifdef UNICODE
# if _WIN32
	return str.toStdWString();
# elif __APPLE__
	return str.toStdU16String();
#endif
#else
	return str.toStdString();
#endif
}

#endif
