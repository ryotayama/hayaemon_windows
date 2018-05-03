//----------------------------------------------------------------------------
// 3DReverbCustomizeWnd.cpp : ３Ｄリバーブのカスタマイズ用ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "3DReverbCustomizeWnd.h"
#include "../Common/CommandList.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
C3DReverbCustomizeWnd::C3DReverbCustomizeWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::Reverb3DCustomizeWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	BASS_DX8_I3DL2REVERB bdir;
	BOOL b3DReverb = m_rMainWnd.GetSound().Get3DReverb(&bdir);
	int lRoom = b3DReverb ? bdir.lRoom : -1000;
	int lRoomHF = b3DReverb ? bdir.lRoomHF : -100;
	float flRoomRolloffFactor = b3DReverb ? bdir.flRoomRolloffFactor : 0.0f;
	float flDecayTime = b3DReverb ? bdir.flDecayTime : 1.49f;
	float flDecayHFRatio = b3DReverb ? bdir.flDecayHFRatio : 0.83f;
	int lReflections = b3DReverb ? bdir.lReflections : -2602;
	float flReflectionsDelay = b3DReverb ? bdir.flReflectionsDelay : 0.007f;
	int lReverb = b3DReverb ? bdir.lReverb : 200;
	float flReverbDelay = b3DReverb ? bdir.flReverbDelay : 0.011f;
	float flDiffusion = b3DReverb ? bdir.flDiffusion : 100.0f;
	float flDensity = b3DReverb ? bdir.flDensity : 100.0f;
	float flHFReference = b3DReverb ? bdir.flHFReference : 5000.0f;

	m_room->setValue(lRoom);
	m_roomHF->setValue(lRoomHF);
	m_roomRolloffFactor->setValue(flRoomRolloffFactor);
	m_decayTime->setValue(flDecayTime);
	m_decayHFRatio->setValue(flDecayHFRatio);
	m_reflections->setValue(lReflections);
	m_reflectionsDelay->setValue(flReflectionsDelay);
	m_reverb->setValue(lReverb);
	m_reverbDelay->setValue(flReverbDelay);
	m_diffusion->setValue(flDiffusion);
	m_density->setValue(flDensity);
	m_hfReference->setValue(flHFReference);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] {
						OnOkButtonClicked();
					});
}
//----------------------------------------------------------------------------
// OK ボタンが押された
//----------------------------------------------------------------------------
void C3DReverbCustomizeWnd::OnOkButtonClicked()
{
	int lRoom = m_room->value();
	int lRoomHF = m_roomHF->value();
	float flRoomRolloffFactor = (float)m_roomRolloffFactor->value();
	float flDecayTime = (float)m_decayTime->value();
	float flDecayHFRatio = (float)m_decayHFRatio->value();
	int lReflections = m_reflections->value();
	float flReflectionsDelay = (float)m_reflectionsDelay->value();
	int lReverb = m_reverb->value();
	float flReverbDelay = (float)m_reverbDelay->value();
	float flDiffusion = (float)m_diffusion->value();
	float flDensity = (float)m_density->value();
	float flHFReference = (float)m_hfReference->value();

	m_rMainWnd.GetMenu().Set3DReverb(lRoom, lRoomHF, flRoomRolloffFactor,
		flDecayTime, flDecayHFRatio, lReflections, flReflectionsDelay, lReverb,
		flReverbDelay, flDiffusion, flDensity, flHFReference,
		ID_3DREVERB_CUSTOMIZE);

	accepted();
}
//----------------------------------------------------------------------------
