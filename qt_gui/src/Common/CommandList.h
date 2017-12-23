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
		ID_SPEED,
		ID_FREQ,
		ID_PITCH,
		ID_VOLUME,
		ID_PAN,
		ID_EQ,
		ID_EQ20,
		ID_EQ25,
		ID_EQ31_5,
		ID_EQ40,
		ID_EQ50,
		ID_EQ63,
		ID_EQ80,
		ID_EQ100,
		ID_EQ125,
		ID_EQ160,
		ID_EQ200,
		ID_EQ250,
		ID_EQ315,
		ID_EQ400,
		ID_EQ500,
		ID_EQ630,
		ID_EQ800,
		ID_EQ1K,
		ID_EQ1_25K,
		ID_EQ1_6K,
		ID_EQ2K,
		ID_EQ2_5K,
		ID_EQ3_15K,
		ID_EQ4K,
		ID_EQ5K,
		ID_EQ6_3K,
		ID_EQ8K,
		ID_EQ10K,
		ID_EQ12_5K,
		ID_EQ16K,
		ID_EQ20K,
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
	// システムメニュー
		// 復元メニュー
			// 表示状態メニュー
				ID_RECOVERSPEEDVISIBLE,
				ID_RECOVERFREQVISIBLE,
				ID_RECOVERPITCHVISIBLE,
				ID_RECOVERVOLUMEVISIBLE,
				ID_RECOVERPANVISIBLE,
				ID_RECOVEREQVISIBLE,
};

#endif // CommandListH
