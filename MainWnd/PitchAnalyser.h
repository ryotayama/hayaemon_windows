//----------------------------------------------------------------------------
// PitchAnalyser.h : ピッチアナライザ機能の管理クラス
//----------------------------------------------------------------------------
#ifndef PitchAnalyserH
#define PitchAnalyserH

#include <string>
#include <vector>
#include "../Common/AcceleratorTable.h"
class CApp;
class CMainWnd;
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// 歌詞表示機能の管理クラス
//----------------------------------------------------------------------------
class CPitchAnalyser
{
public: // 関数

	CPitchAnalyser(CApp & app, CMainWnd & mainWnd);
	virtual ~CPitchAnalyser();
	virtual void ClearScreen();
	virtual void Update(double dCurrentTime);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	HBITMAP hBitmap;
	HDC hMemDC;
	HFONT hFont;
	void* pImage;
	int m_nLeft;

public: // メンバ変数の取得・設定

};
//----------------------------------------------------------------------------

#endif