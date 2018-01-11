//----------------------------------------------------------------------------
// BassFx.h : bass_fx.dll の管理を行う
//----------------------------------------------------------------------------
#ifndef BassFxH
#define BassFxH

#include "bass/bass.h"
#include "bass/bass_fx.h"
#include "Bass.h"
//----------------------------------------------------------------------------
// bass_fx.dll の管理を行うクラス
//----------------------------------------------------------------------------
class CBassFx : public CBass
{
public: // 関数

	virtual ~CBassFx() { }

	virtual void TempoCreate(BOOL bDecode = FALSE) {
		if(bDecode)
			m_hStream = BASS_FX_TempoCreate(m_hStream, BASS_FX_FREESOURCE | BASS_STREAM_DECODE);
		else
			m_hStream = BASS_FX_TempoCreate(m_hStream, BASS_FX_FREESOURCE);
	}
	virtual float GetTempo() {
		float tempo;
		BASS_ChannelGetAttribute(m_hStream, BASS_ATTRIB_TEMPO, &tempo);
		return tempo;
	}
	virtual BOOL SetTempo(float tempo) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO, tempo);
	}
	virtual float GetSampleRate() {
		float samplerate;
		BASS_ChannelGetAttribute(m_hStream, BASS_ATTRIB_TEMPO_FREQ, &samplerate);
		return samplerate;
	}
	virtual BOOL SetSampleRate(float samplerate) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO_FREQ, samplerate);
	}
	virtual BOOL SetPitch(float pitch) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO_PITCH, pitch);
	}
	virtual void ReverseCreate()
	{
		m_hStream = BASS_FX_ReverseCreate(m_hStream, 2, BASS_FX_FREESOURCE | BASS_STREAM_DECODE);
	}
	virtual BOOL SetReverse(BOOL bReverse = TRUE)
	{
		DWORD chan = BASS_FX_TempoGetSource(m_hStream);
		return BASS_ChannelSetAttribute(chan, BASS_ATTRIB_REVERSE_DIR, (float)(bReverse ? BASS_FX_RVS_REVERSE : BASS_FX_RVS_FORWARD));
	}
};
//----------------------------------------------------------------------------

#endif
