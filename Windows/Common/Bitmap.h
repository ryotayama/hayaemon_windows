//----------------------------------------------------------------------------
// Bitmap.h : ビットマップの管理を行う
//----------------------------------------------------------------------------
#ifndef BitmapH
#define BitmapH
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ビットマップの管理を行うクラス
//----------------------------------------------------------------------------
class CBitmap
{
public: // 関数

	CBitmap(): m_hBitmap(0) { }
	virtual ~CBitmap() { Destroy(); }

	virtual void Destroy() {
		if(m_hBitmap) DeleteObject(m_hBitmap), m_hBitmap = 0;
	}
	virtual void Load(LPCTSTR lpszName, UINT fuLoad) {
		Destroy();
		m_hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), lpszName, IMAGE_BITMAP, 0, 0, fuLoad);
	}

protected: // メンバ変数

	HBITMAP m_hBitmap;

public: // メンバ変数の取得・設定

	operator HBITMAP() const { return m_hBitmap; }
};
//----------------------------------------------------------------------------

#endif