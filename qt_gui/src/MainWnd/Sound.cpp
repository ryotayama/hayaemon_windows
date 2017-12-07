//----------------------------------------------------------------------------
// Sound.cpp : 音の再生管理
//----------------------------------------------------------------------------
#include "Sound.h"
#include <algorithm>
#include <cctype>
#include "../Common/Define.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CSound::CSound(CMainWnd & mainWnd, BOOL bMainStream)
	: m_rMainWnd(mainWnd), m_bLoop(FALSE), m_nCurFile(0),
	  m_bMainStream(bMainStream)
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
// 再生
//----------------------------------------------------------------------------
BOOL CSound::ChannelPlay()
{
	ChannelRemoveSync();
	ChannelSetSync(BASS_SYNC_END, 0, LoopSyncProc, (DWORD *)this);
	return CBass::ChannelPlay();
}
//----------------------------------------------------------------------------
// ループ用コールバック関数
//----------------------------------------------------------------------------
void CALLBACK CSound::LoopSyncProc(HSYNC handle, DWORD channel,
	DWORD data, void *user)
{
	CSound* pthis = (CSound*)user;
	CMainWnd* mainWnd = &pthis->GetMainWnd();
 	if(!pthis->OnLoop()) mainWnd->SetFinish(TRUE);
}
//----------------------------------------------------------------------------
// ループの設定
//----------------------------------------------------------------------------
void CSound::SetLoop(BOOL bLoop)
{
	m_bLoop = bLoop;
}
//----------------------------------------------------------------------------
// ループ
//----------------------------------------------------------------------------
UINT CSound::OnLoop()
{
	return 0;
}
//----------------------------------------------------------------------------
