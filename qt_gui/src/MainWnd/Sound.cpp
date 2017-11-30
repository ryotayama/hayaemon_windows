//----------------------------------------------------------------------------
// Sound.cpp : 音の再生管理
//----------------------------------------------------------------------------
#include "Sound.h"
#include <algorithm>
#include <cctype>
#include "../Common/Define.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CSound::CSound(BOOL bMainStream)
	: m_nCurFile(0), m_bMainStream(bMainStream), m_bLoop(FALSE)
{
}
//----------------------------------------------------------------------------
// ファイルの読み込み
//----------------------------------------------------------------------------
BOOL CSound::StreamCreateFile(LPCTSTR lpFilePath, BOOL bDecode, int nCount)
{
	BOOL bRet = FALSE;
	if(!m_bMainStream) {
		bRet = CBassFx::StreamCreateFile(lpFilePath);
		m_strCurFile = lpFilePath;
		return bRet;
	}

	tstring ext;
	tstring filePath(lpFilePath);
	auto pos = filePath.rfind('.');
	if(pos != tstring::npos) {
		ext = filePath.substr(pos);
		std::transform(ext.begin(), ext.end(), ext.begin(), std::tolower);
	}

	if(ext == _T(".nsf"))
		return FALSE;

	if(ext == _T(".avi") || ext == _T(".wmv") ||
		 ext == _T(".mp4") || ext == _T(".mkv") ||
		 ext == _T(".flv")) {
		StreamFree();
		return FALSE;
	}

	if(!bRet) {
		bRet = CBassFx::StreamCreateFile(lpFilePath);
		m_strCurFile = lpFilePath;
	}
	return bRet;
}
//----------------------------------------------------------------------------
// ループの設定
//----------------------------------------------------------------------------
void CSound::SetLoop(BOOL bLoop)
{
	m_bLoop = bLoop;
}
//----------------------------------------------------------------------------
