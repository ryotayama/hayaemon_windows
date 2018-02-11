//----------------------------------------------------------------------------
// Utility.h : ヘルパー関数
//----------------------------------------------------------------------------
#ifndef UtilityH
#define UtilityH

#include <QString>
#include "../Common/Define.h"

inline tstring ToTstring(const QString & str)
{
#ifdef UNICODE
	return str.toStdWString();
#else
	return str.toStdString();
#endif
}

inline QString ToQString(const std::string & str)
{
	return QString::fromStdString(str);
}

inline QString ToQString(const std::wstring & str)
{
	return QString::fromStdWString(str);
}

inline QString ToQString(const wchar_t * str)
{
	return ToQString(std::wstring(str));
}

#endif
