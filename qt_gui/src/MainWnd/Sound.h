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
	virtual void SetEQ20(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ25(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ31_5(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ40(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ50(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ63(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ80(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ100(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ125(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ160(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ200(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ250(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ315(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ400(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ500(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ630(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ800(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ1K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ1_25K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ1_6K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ2K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ2_5K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ3_15K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ4K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ5K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ6_3K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ8K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ10K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ12_5K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ16K(float fCenter, float fBandwidth, float fGain);
	virtual void SetEQ20K(float fCenter, float fBandwidth, float fGain);
	virtual void SetLoop(BOOL bLoop);
	virtual BOOL SetTempo(float tempo);
	virtual BOOL SetSampleRate(float samplerate);
	virtual BOOL ChannelSetVolume(float volume);
	virtual UINT OnLoop();

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	BOOL m_bLoop; // １曲ループがオンかどうか

	tstring m_strCurFile;
	int m_nCurFile;
	BOOL m_bMainStream;

	HFX m_hFx20Hz, m_hFx25Hz, m_hFx31_5Hz, m_hFx40Hz, m_hFx50Hz, m_hFx63Hz,
		m_hFx80Hz, m_hFx100Hz, m_hFx125Hz, m_hFx160Hz, m_hFx200Hz, m_hFx250Hz,
		m_hFx315Hz, m_hFx400Hz, m_hFx500Hz, m_hFx630Hz, m_hFx800Hz,
		m_hFx1KHz, m_hFx1_25KHz, m_hFx1_6KHz, m_hFx2KHz, m_hFx2_5KHz,
		m_hFx3_15KHz, m_hFx4KHz, m_hFx5KHz, m_hFx6_3KHz, m_hFx8KHz,
		m_hFx10KHz, m_hFx12_5KHz, m_hFx16KHz, m_hFx20KHz,
		m_hFxVolume;

	HFX m_hFx20Hz_2, m_hFx25Hz_2, m_hFx31_5Hz_2, m_hFx40Hz_2, m_hFx50Hz_2,
		m_hFx63Hz_2, m_hFx80Hz_2, m_hFx100Hz_2, m_hFx125Hz_2, m_hFx160Hz_2,
		m_hFx200Hz_2, m_hFx250Hz_2, m_hFx315Hz_2, m_hFx400Hz_2, m_hFx500Hz_2,
		m_hFx630Hz_2, m_hFx800Hz_2, m_hFx1KHz_2, m_hFx1_25KHz_2, m_hFx1_6KHz_2,
		m_hFx2KHz_2, m_hFx2_5KHz_2, m_hFx3_15KHz_2, m_hFx4KHz_2, m_hFx5KHz_2,
		m_hFx6_3KHz_2, m_hFx8KHz_2, m_hFx10KHz_2, m_hFx12_5KHz_2, m_hFx16KHz_2,
		m_hFx20KHz_2;

public: // メンバ変数の取得・設定

	virtual BOOL IsLoop() const { return m_bLoop; }
	virtual int GetCurFileNum() const { return m_nCurFile; }
	virtual void SetCurFileNum(int n) { m_nCurFile = n; }
	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif
