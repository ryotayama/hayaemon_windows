//--------------------------------------------------------------------------
// CommandList.h : Command IDs
//--------------------------------------------------------------------------
#ifndef CommandListH
#define CommandListH

//--------------------------------------------------------------------------
// COMMAND ID
//--------------------------------------------------------------------------
typedef enum CMDID {
	// 表示メニュー
		ID_VOLUME,
		ID_PAN,
	// エフェクトメニュー
		ID_SPEEDDEC_0,
		ID_SPEEDDEC_1,
		ID_SPEEDDEC_2,
		ID_FREQDEC_0,
		ID_FREQDEC_1,
		ID_FREQDEC_2,
		ID_PITCHDEC_0,
		ID_PITCHDEC_1,
		ID_PITCHDEC_2,
};

#endif // CommandListH
