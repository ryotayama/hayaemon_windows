//--------------------------------------------------------------------------
// Define.h : 共通定義
//--------------------------------------------------------------------------
#ifndef DefineH
#define DefineH

#include <tchar.h>
#include <string>
#include "bassinc.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
// DEFINITION
//--------------------------------------------------------------------------
#ifdef UNICODE
#define BASS_IF_UNICODE		BASS_UNICODE
#define CLIPBOARD_TXT_FMT	CF_UNICODETEXT
#else // UNICODE
#define BASS_IF_UNICODE		0
#define CLIPBOARD_TXT_FMT	CF_TEXT
#endif // UNICODE

#define WM_TRAY WM_APP+1 // タスクトレイメッセージ

//--------------------------------------------------------------------------
// TYPES
//--------------------------------------------------------------------------
typedef std::basic_string<TCHAR> tstring;

#endif // DefineH