//--------------------------------------------------------------------------
// Define.h : 共通定義
//--------------------------------------------------------------------------
#ifndef DefineH
#define DefineH

#include <stdint.h>
#include <string>

//--------------------------------------------------------------------------
// DEFINITION
//--------------------------------------------------------------------------
#ifndef _T
# ifdef UNICODE
#  if _WIN32
#   define _T(x) L ## x
#  elif __APPLE__
#   define _T(x) u ## x
#  endif
# else
#  define _T(x) x
# endif
#endif

#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif
#ifndef LVCFMT_LEFT
# define LVCFMT_LEFT 0
#endif
#ifndef LVCFMT_RIGHT
# define LVCFMT_RIGHT 1
#endif

//--------------------------------------------------------------------------
// TYPES
//--------------------------------------------------------------------------
typedef int BOOL;
typedef long LONG;
typedef unsigned int UINT;
typedef unsigned long long UINT_PTR;
typedef uint64_t QWORD;
typedef long long LRESULT;

#ifdef UNICODE
# if _WIN32
typedef wchar_t TCHAR;
# elif __APPLE__
typedef char16_t TCHAR;
# endif
#else
typedef char TCHAR;
#endif
typedef const TCHAR *LPCTSTR;

typedef std::basic_string<TCHAR> tstring;

#endif // DefineH
