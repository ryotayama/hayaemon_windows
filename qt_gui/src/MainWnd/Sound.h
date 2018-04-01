//----------------------------------------------------------------------------
// Sound.h : 音の再生管理
//----------------------------------------------------------------------------
#ifndef SoundH
#define SoundH

#include <vector>
#include "../Common/BassFx.h"
#include "../Common/Define.h"
class CApp;
class CMainWnd;
//----------------------------------------------------------------------------
// 音の再生管理クラス
//----------------------------------------------------------------------------
class CSound : public CBassFx
{
public: // 関数

	CSound(CApp & app, CMainWnd & mainWnd, BOOL bMainStream = TRUE);

	virtual void AddMarker(QWORD nPos);
	virtual int ChangeMarkerPos(int nMarker, QWORD nPos);
	virtual BOOL StreamCreateFile(LPCTSTR lpFilePath, BOOL bDecode = FALSE,
		int nCount = 1);
	virtual BOOL StreamCreateURL(LPCTSTR lpFilePath, BOOL bDecode = FALSE);
	virtual void EraseMarker(int nMarker);
	virtual BOOL ChannelPlay();
	static void CALLBACK LoopSyncProc(HSYNC handle, DWORD channel, DWORD data,
									  void *user);
	virtual void ClearMarker();
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
	virtual BOOL GetReverb(BASS_DX8_REVERB * bdr);
	virtual void SetReverb(BOOL bReverb);
	virtual void SetReverb();
	virtual void SetReverb(float fInGain, float fReverbMix, float fReverbTime,
		float fHighFreqRTRatio, BOOL bReverb);
	virtual BOOL Get3DReverb(BASS_DX8_I3DL2REVERB * bdir);
	virtual void Set3DReverb(BOOL b3DReverb);
	virtual void Set3DReverb();
	virtual void Set3DReverb(int lRoom, int lRoomHF, float flRoomRolloffFactor,
		float flDecayTime, float flDecayHFRatio, int lReflections,
		float flReflectionsDelay, int lReverb, float flReverbDelay,
		float flDiffusion, float flDensity, float flHFReference,
		BOOL b3DReverb);
	virtual BOOL GetDelay(BASS_DX8_ECHO * bde);
	virtual void SetDelay(BOOL bDelay);
	virtual void SetDelay();
	virtual void SetDelay(float fWetDryMix, float fFeedback, float fLeftDelay,
						  float fRightDelay, BOOL lPanDelay, BOOL bDelay);
	virtual BOOL GetDistortion(BASS_DX8_DISTORTION * bdd);
	virtual void SetDistortion(BOOL bDistortion);
	virtual void SetDistortion();
	virtual void SetDistortion(float fGain, float fEdge,
							   float fPostEQCenterFreq,
							   float fPostEQBandwidth, float fPreLowpassCutoff,
							   BOOL bDistortion);
	virtual BOOL GetChorus(BASS_DX8_CHORUS * bdc);
	virtual void SetChorus(BOOL bChorus);
	virtual void SetChorus();
	virtual void SetChorus(float fWetDryMix, float fDepth, float fFeedback,
						   float fFreq, DWORD lWaveform, float fDelay,
						   DWORD lPhase, BOOL bChorus);
	virtual BOOL GetCompressor(BASS_DX8_COMPRESSOR * bdcmp);
	virtual void SetCompressor(BOOL bCompressor);
	virtual void SetCompressor();
	virtual void SetCompressor(float fGain, float fAttack, float fRelease,
							   float fThreshold, float fRatio, float fPredelay,
							   BOOL bCompressor);
	virtual BOOL GetFlanger(BASS_DX8_FLANGER * bdf);
	virtual void SetFlanger(BOOL bFlanger);
	virtual void SetFlanger();
	virtual void SetFlanger(float fWetDryMix, float fDepth, float fFeedback,
							float fFreq, DWORD lWaveform, float fDelay,
							DWORD lPhase, BOOL bFlanger);
	virtual BOOL GetGargle(BASS_DX8_GARGLE * bdg);
	virtual void SetGargle(BOOL bGargle);
	virtual void SetGargle();
	virtual void SetGargle(DWORD dwRateHz, DWORD dwWaveShape, BOOL bGargle);
	virtual void SetLoop(BOOL bLoop);
	virtual void SetABLoopA(BOOL bLoop);
	virtual void SetABLoopB(BOOL bLoop);
	virtual void SetLoopPosA(QWORD nPos);
	virtual void SetLoopPosB(QWORD nPos);
	virtual float GetTempo();
	virtual BOOL SetTempo(float tempo);
	virtual float GetSampleRate();
	virtual BOOL SetSampleRate(float samplerate);
	virtual BOOL ChannelSetVolume(float volume);
	virtual UINT OnLoop();
	virtual void SaveFile(LPCTSTR lpszFilePath, int nFormat);
	virtual void SaveFile(const QString & filePath, int nFormat);
	virtual void SetMonoral(BOOL bMonoral = TRUE);
	static void CALLBACK Monoral(HDSP handle, DWORD channel, void *buffer,
								 DWORD length, void *user);
	virtual void SetVocalCancel(BOOL bVocalCancel = TRUE);
	static void CALLBACK VocalCancel(HDSP handle, DWORD channel, void *buffer,
									 DWORD length, void *user);
	virtual void SetChangeLR(BOOL bChangeLR = TRUE);
	static void CALLBACK ChangeLR(HDSP handle, DWORD channel, void *buffer,
								  DWORD length, void *user);
	virtual void SetOnlyLeft(BOOL bOnlyLeft = TRUE);
	static void CALLBACK OnlyLeft(HDSP handle, DWORD channel, void *buffer,
								  DWORD length, void *user);
	virtual void SetOnlyRight(BOOL bOnlyRight = TRUE);
	static void CALLBACK OnlyRight(HDSP handle, DWORD channel, void *buffer,
								   DWORD length, void *user);
	virtual void SetNormalize(BOOL bNormalize = TRUE);
	static void CALLBACK Normalize(HDSP handle, DWORD channel,
								   void *buffer, DWORD length, void *user);
	virtual void SetPan(int nPan);
	static void CALLBACK Pan(HDSP handle, DWORD channel,
							 void *buffer, DWORD length, void *user);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	BOOL m_bLoop; // １曲ループがオンかどうか
	QWORD m_nLoopPosA; // AB ループ A の位置
	QWORD m_nLoopPosB; // AB ループ B の位置
	BOOL m_bABLoopA; // AB ループ A がオンかどうか
	BOOL m_bABLoopB; // AB ループ B がオンかどうか

	tstring m_strCurFile;
	int m_nCurFile;
	std::vector<QWORD> m_arrayMarker;
	int m_peak;
	int m_nPan;
	BOOL m_bMainStream;

	HFX m_hFx20Hz, m_hFx25Hz, m_hFx31_5Hz, m_hFx40Hz, m_hFx50Hz, m_hFx63Hz,
		m_hFx80Hz, m_hFx100Hz, m_hFx125Hz, m_hFx160Hz, m_hFx200Hz, m_hFx250Hz,
		m_hFx315Hz, m_hFx400Hz, m_hFx500Hz, m_hFx630Hz, m_hFx800Hz,
		m_hFx1KHz, m_hFx1_25KHz, m_hFx1_6KHz, m_hFx2KHz, m_hFx2_5KHz,
		m_hFx3_15KHz, m_hFx4KHz, m_hFx5KHz, m_hFx6_3KHz, m_hFx8KHz,
		m_hFx10KHz, m_hFx12_5KHz, m_hFx16KHz, m_hFx20KHz,
		m_hFxReverb, m_hFx3DReverb, m_hFxDelay, m_hFxChorus, m_hFxCompressor,
		m_hFxFlanger, m_hFxGargle, m_hFxDistortion, m_hFxVolume;

	HFX m_hFx20Hz_2, m_hFx25Hz_2, m_hFx31_5Hz_2, m_hFx40Hz_2, m_hFx50Hz_2,
		m_hFx63Hz_2, m_hFx80Hz_2, m_hFx100Hz_2, m_hFx125Hz_2, m_hFx160Hz_2,
		m_hFx200Hz_2, m_hFx250Hz_2, m_hFx315Hz_2, m_hFx400Hz_2, m_hFx500Hz_2,
		m_hFx630Hz_2, m_hFx800Hz_2, m_hFx1KHz_2, m_hFx1_25KHz_2, m_hFx1_6KHz_2,
		m_hFx2KHz_2, m_hFx2_5KHz_2, m_hFx3_15KHz_2, m_hFx4KHz_2, m_hFx5KHz_2,
		m_hFx6_3KHz_2, m_hFx8KHz_2, m_hFx10KHz_2, m_hFx12_5KHz_2, m_hFx16KHz_2,
		m_hFx20KHz_2;

	HDSP m_hMonoralDsp, m_hVocalCancelDsp, m_hOnlyLeftDsp, m_hOnlyRightDsp,
		 m_hChangeLRDsp, m_hNormalizeDsp, m_hPanDsp;

	BASS_DX8_REVERB m_bdr;
	BASS_DX8_I3DL2REVERB m_bdir;
	BASS_DX8_ECHO m_bde;
	BASS_DX8_DISTORTION m_bdd;
	BASS_DX8_CHORUS m_bdc;
	BASS_DX8_COMPRESSOR m_bdcmp;
	BASS_DX8_FLANGER m_bdf;
	BASS_DX8_GARGLE m_bdg;

public: // メンバ変数の取得・設定

	virtual BOOL IsLoop() const { return m_bLoop; }
	virtual BOOL IsABLoopA() const { return m_bABLoopA; }
	virtual BOOL IsABLoopB() const { return m_bABLoopB; }
	virtual QWORD GetLoopPosA() const { return m_nLoopPosA; }
	virtual QWORD GetLoopPosB() const { return m_nLoopPosB; }
	virtual double GetLoopPosA_sec() const { return ChannelBytes2Seconds(m_nLoopPosA); }
	virtual double GetLoopPosB_sec() const { return ChannelBytes2Seconds(m_nLoopPosB); }
	virtual tstring GetCurFileName() const { return m_strCurFile; }
	virtual void SetCurFileName(tstring str) { m_strCurFile = str; }
	virtual int GetCurFileNum() const { return m_nCurFile; }
	virtual void SetCurFileNum(int n) { m_nCurFile = n; }
	virtual std::vector<QWORD> GetArrayMarker() const { return m_arrayMarker; }
	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif
