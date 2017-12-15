//----------------------------------------------------------------------------
// Sound.h : 音の再生管理
//----------------------------------------------------------------------------
#ifndef SoundH
#define SoundH

#include "../Common/BassFx.h"
#include "../Common/Define.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 音の再生管理クラス
//----------------------------------------------------------------------------
class CSound : public CBassFx
{
public: // 関数

	CSound(CMainWnd & mainWnd, BOOL bMainStream = TRUE);

	virtual BOOL StreamCreateFile(LPCTSTR lpFilePath, BOOL bDecode = FALSE,
		int nCount = 1);
	virtual BOOL ChannelPlay();
	static void CALLBACK LoopSyncProc(HSYNC handle, DWORD channel, DWORD data,
									  void *user);
	virtual void SetLoop(BOOL bLoop);
	virtual BOOL SetTempo(float tempo);
	virtual BOOL ChannelSetVolume(float volume);
	virtual UINT OnLoop();

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	BOOL m_bLoop; // １曲ループがオンかどうか

	tstring m_strCurFile;
	int m_nCurFile;
	BOOL m_bMainStream;

	HFX m_hFxVolume;

public: // メンバ変数の取得・設定

	virtual BOOL IsLoop() const { return m_bLoop; }
	virtual int GetCurFileNum() const { return m_nCurFile; }
	virtual void SetCurFileNum(int n) { m_nCurFile = n; }
	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif
