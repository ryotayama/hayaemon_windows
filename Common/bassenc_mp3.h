/*
	BASSenc_MP3 2.4 C/C++ header file
	Copyright (c) 2018 Un4seen Developments Ltd.

	See the BASSENC_MP3.CHM file for more detailed documentation
*/

#ifndef BASSENC_MP3_H
#define BASSENC_MP3_H

#include "bassenc.h"

#if BASSVERSION!=0x204
#error conflicting BASS and BASSenc_MP3 versions
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BASSENCMP3DEF
#define BASSENCMP3DEF(f) WINAPI f
#endif

DWORD BASSENCMP3DEF(BASS_Encode_MP3_GetVersion)();

HENCODE BASSENCMP3DEF(BASS_Encode_MP3_Start)(DWORD handle, const char *options, DWORD flags, ENCODEPROCEX *proc, void *user);
HENCODE BASSENCMP3DEF(BASS_Encode_MP3_StartFile)(DWORD handle, const char *options, DWORD flags, const char *filename);

#ifdef __cplusplus
}

#ifdef _WIN32
static inline HENCODE BASS_Encode_MP3_Start(DWORD handle, const WCHAR *options, DWORD flags, ENCODEPROCEX *proc, void *user)
{
	return BASS_Encode_MP3_Start(handle, (const char*)options, flags|BASS_UNICODE, proc, user);
}

static inline HENCODE BASS_Encode_MP3_StartFile(DWORD handle, const WCHAR *options, DWORD flags, const WCHAR *filename)
{
	return BASS_Encode_MP3_StartFile(handle, (const char*)options, flags|BASS_UNICODE, (const char*)filename);
}
#endif
#endif

#endif
