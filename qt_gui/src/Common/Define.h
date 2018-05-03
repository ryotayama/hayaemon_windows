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
#  define _T(x) L ## x
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
typedef long long LRESULT;
#ifdef _WIN32
typedef unsigned long DWORD;
#elif __APPLE__
typedef uint32_t DWORD;
#endif
typedef uint64_t QWORD;

#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
typedef const char *LPCSTR;
typedef TCHAR *LPTSTR;
typedef const TCHAR *LPCTSTR, *PCTSTR;

typedef std::basic_string<TCHAR> tstring;

#ifndef SW_HIDE
# define SW_HIDE 0
#endif
#ifndef SW_SHOW
# define SW_SHOW 5
#endif

#ifndef LVIS_SELECTED
# define LVIS_SELECTED           0x0002
#endif

#ifndef MF_BYCOMMAND
# define MF_BYCOMMAND        0x00000000L
#endif
#ifndef MF_BYPOSITION
# define MF_BYPOSITION       0x00000400L
#endif

#ifndef MF_UNCHECKED
# define MF_UNCHECKED        0x00000000L
#endif
#ifndef MF_CHECKED
# define MF_CHECKED          0x00000008L
#endif
#ifndef MF_ENABLED
# define MF_ENABLED          0x00000008L
#endif
#ifndef MF_GRAYED
# define MF_GRAYED           0x00000003L
#endif
#ifndef MFS_ENABLED
# define MFS_ENABLED         MF_ENABLED
#endif
#ifndef MFS_DISABLED
# define MFS_DISABLED        MF_GRAYED
#endif

#ifndef TBSTATE_CHECKED
# define TBSTATE_CHECKED         0x01
#endif
#ifndef TBSTATE_ENABLED
# define TBSTATE_ENABLED         0x04
#endif

#endif // DefineH
