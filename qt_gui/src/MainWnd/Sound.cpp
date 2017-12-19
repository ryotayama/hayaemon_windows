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
		m_bMainStream(bMainStream), m_hFx20Hz(0), m_hFx25Hz(0), m_hFx31_5Hz(0),
		m_hFx40Hz(0), m_hFx50Hz(0), m_hFx63Hz(0), m_hFx80Hz(0), m_hFx100Hz(0),
		m_hFx125Hz(0), m_hFx160Hz(0), m_hFx200Hz(0), m_hFx250Hz(0), m_hFx315Hz(0),
		m_hFx400Hz(0), m_hFx500Hz(0), m_hFx630Hz(0), m_hFx800Hz(0), m_hFx1KHz(0),
		m_hFx1_25KHz(0), m_hFx1_6KHz(0), m_hFx2KHz(0), m_hFx2_5KHz(0),
		m_hFx3_15KHz(0), m_hFx4KHz(0), m_hFx5KHz(0), m_hFx6_3KHz(0), m_hFx8KHz(0),
		m_hFx10KHz(0), m_hFx12_5KHz(0), m_hFx16KHz(0), m_hFx20KHz(0),
		m_hFxVolume(0), m_hFx20Hz_2(0), m_hFx25Hz_2(0), m_hFx31_5Hz_2(0),
		m_hFx40Hz_2(0), m_hFx50Hz_2(0), m_hFx63Hz_2(0), m_hFx80Hz_2(0),
		m_hFx100Hz_2(0), m_hFx125Hz_2(0), m_hFx160Hz_2(0), m_hFx200Hz_2(0),
		m_hFx250Hz_2(0), m_hFx315Hz_2(0), m_hFx400Hz_2(0), m_hFx500Hz_2(0),
		m_hFx630Hz_2(0), m_hFx800Hz_2(0), m_hFx1KHz_2(0), m_hFx1_25KHz_2(0),
		m_hFx1_6KHz_2(0), m_hFx2KHz_2(0), m_hFx2_5KHz_2(0), m_hFx3_15KHz_2(0),
		m_hFx4KHz_2(0), m_hFx5KHz_2(0), m_hFx6_3KHz_2(0), m_hFx8KHz_2(0),
		m_hFx10KHz_2(0), m_hFx12_5KHz_2(0), m_hFx16KHz_2(0), m_hFx20KHz_2(0)
{
	// BASS_FXSetParametersでボリュームを変更しようとするだけでは、bass_fxが
	// ロードされないので、明示的にbass_fxの関数を実行する。
	auto v = BASS_FX_GetVersion();
}
//----------------------------------------------------------------------------
// ファイルの読み込み
//----------------------------------------------------------------------------
BOOL CSound::StreamCreateFile(LPCTSTR lpFilePath, BOOL bDecode, int nCount)
{
	BOOL bRet = FALSE;
	if(!m_bMainStream) {
		bRet = CBassFx::StreamCreateFile(lpFilePath);
		TempoCreate(bDecode);
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
		TempoCreate(bDecode);
		m_strCurFile = lpFilePath;
		m_hFx20Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFxVolume = ChannelSetFX(BASS_FX_BFX_VOLUME, 1);
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
// イコライザ ( 20Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ20(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 25Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ25(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx25Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx25Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 31.5Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ31_5(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx31_5Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx31_5Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 40Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ40(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx40Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx40Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 50Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ50(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx50Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx50Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 63Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ63(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx63Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx63Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 80Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ80(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx80Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx80Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 100Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ100(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx100Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx100Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 125Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ125(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx125Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx125Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 160Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ160(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx160Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx160Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 200Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ200(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx200Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx200Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 250Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ250(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx250Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx250Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 315Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ315(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx315Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx315Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 400Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ400(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx400Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx400Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 500Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ500(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx500Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx500Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 630Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ630(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx630Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx630Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 800Hz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ800(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx800Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx800Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 1KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ1K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 1.25KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ1_25K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_25KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_25KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 1.6KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ1_6K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_6KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_6KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 2KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ2K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 2.5KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ2_5K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2_5KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2_5KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 3.15KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ3_15K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx3_15KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx3_15KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 4KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ4K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx4KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx4KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 5KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ5K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx5KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx5KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 6.3KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ6_3K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx6_3KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx6_3KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 8KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ8K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx8KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx8KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 10KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ10K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx10KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx10KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 12.5KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ12_5K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx12_5KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx12_5KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 16KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ16K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx16KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx16KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// イコライザ ( 20KHz ) の設定
//----------------------------------------------------------------------------
void CSound::SetEQ20K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz_2, &p2);
		}
	}
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
// テンポの設定
//----------------------------------------------------------------------------
BOOL CSound::SetTempo(float tempo)
{
	return CBassFx::SetTempo(tempo - 100.0f);
}
//----------------------------------------------------------------------------
// サンプルレートの設定
//----------------------------------------------------------------------------
BOOL CSound::SetSampleRate(float samplerate)
{
	return CBassFx::SetSampleRate(ChannelGetFreq() * samplerate / 100.0f);
}
//----------------------------------------------------------------------------
// 音量の設定
//----------------------------------------------------------------------------
BOOL CSound::ChannelSetVolume(float volume)
{
	BASS_BFX_VOLUME p = {0, volume / 100.0f};
	return BASS_FXSetParameters(m_hFxVolume, &p);
}
//----------------------------------------------------------------------------
// ループ
//----------------------------------------------------------------------------
UINT CSound::OnLoop()
{
	return 0;
}
//----------------------------------------------------------------------------
