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
	virtual BOOL SetTempo(float tempo) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO, tempo);
	}
	virtual BOOL SetSampleRate(float samplerate) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO_FREQ, samplerate);
	}
};
//----------------------------------------------------------------------------

#endif
