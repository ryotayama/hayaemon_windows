//----------------------------------------------------------------------------
// Platform.h : プラットフォーム依存の関数
//----------------------------------------------------------------------------
#ifndef PlatformH
#define PlatformH

class QString;

#if WIN32
#include <tchar.h>

#elif __APPLE__

#include "../Common/Define.h"

//----------------------------------------------------------------------------
// Windows固有のAPIを実装
//----------------------------------------------------------------------------
#ifndef MAX_PATH
#	define MAX_PATH 260
#endif

#ifdef UNICODE
# define lstrcmp wcscmp
# define lstrcpy wcscpy
template <size_t N, typename ... Args>
int _stprintf_s(wchar_t (&buf)[N], const wchar_t *format, Args const & ... args)
{
	swprintf(buf, N, format, args ...);
}
int _ttoi(const TCHAR *str);
double _ttof(const TCHAR *str);
double _tstof(const TCHAR *str);
#else
# define lstrcmp strcmp
# define lstrcpy strcpy
# define _stprintf_s sprintf
# define _ttoi atoi
# define _tstof atof
#endif
int _tcsicmp(const TCHAR *lhs, const TCHAR *rhs);

void OutputDebugString(const TCHAR *str);
DWORD timeGetTime(void);

UINT GetPrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nDefault,
													LPCTSTR lpFileName);
DWORD GetPrivateProfileString(LPCTSTR lpAppName, LPCTSTR lpKeyName, 
															LPCTSTR lpDefault, LPTSTR lpReturnedString,
															DWORD nSize, LPCTSTR lpFileName);
BOOL WritePrivateProfileString(LPCTSTR lpAppName, LPCTSTR lpKeyName,
															 LPCTSTR lpString, LPCTSTR lpFileName);
#endif

bool PathIsURL(const QString & path);

#endif // PlatformH
