//--------------------------------------------------------------------------
// Utils.cpp : ユーティリティ関数
//--------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H>
#include "Utils.h"
//--------------------------------------------------------------------------
tstring CUtils::GetFilePath(const tstring & filePath)
{
	TCHAR drive[_MAX_DRIVE + _MAX_DIR];
	TCHAR dir[_MAX_DIR];
	_tsplitpath_s(filePath.c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, NULL,
		0, NULL, 0);
	lstrcat(drive, dir);
	return drive;
}
//--------------------------------------------------------------------------
tstring CUtils::GetFileName(const tstring & filePath)
{
	TCHAR fname[_MAX_FNAME + _MAX_EXT];
	TCHAR ext[_MAX_EXT];
	_tsplitpath_s(filePath.c_str(), NULL, 0, NULL, 0, fname, _MAX_FNAME,
		ext, _MAX_EXT);
	lstrcat(fname, ext);
	return fname;
}
//--------------------------------------------------------------------------
tstring CUtils::GetFileNameWithoutExt(const tstring & filePath)
{
	TCHAR fname[_MAX_FNAME];
	_tsplitpath_s(filePath.c_str(), NULL, 0, NULL, 0, fname, _MAX_FNAME,
		NULL, 0);
	return fname;
}
//--------------------------------------------------------------------------
tstring CUtils::GetFileSize_KB(const tstring & filePath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(filePath.c_str(), &wfd);
	if(hFind == INVALID_HANDLE_VALUE) return _T("");
	if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		FindClose(hFind);
		return TEXT("");
	}
	TCHAR strSize[MAX_PATH];
	int size = (int)((wfd.nFileSizeHigh * ((int)MAXDWORD+1) + wfd.nFileSizeLow
		+ 1023) >> 10);
	int j = 0;
	TCHAR * pstr = strSize;
	do {
		*pstr = "0123456789"[size % 10];
		pstr = CharNext(pstr);
		size /= 10;
		j++;
		if(size != 0 && j % 3 == 0) {
			*pstr = ',';
			pstr = CharNext(pstr);
		}
	}
	while(size != 0);
	*pstr = '\0';
	_tcsrev(strSize);
	_tcscat_s(strSize, _T(" KB"));
	return strSize;
}
//--------------------------------------------------------------------------
tstring CUtils::Replace(tstring str, tstring srcStr, tstring dstStr)
{
	tstring::size_type n, offset = 0;
	while((n = str.find(srcStr, offset)) != tstring::npos)
	{
		str.replace(n, srcStr.size(), dstStr);
		offset = n + dstStr.size();
	}
	return str;
}
//--------------------------------------------------------------------------
int CUtils::GetRandom(int nMin, int nMax)
{
	srand(timeGetTime());
	return nMin + (int)(rand() * (nMax - nMin + 1.0) / (1.0 + RAND_MAX));
}
//--------------------------------------------------------------------------
