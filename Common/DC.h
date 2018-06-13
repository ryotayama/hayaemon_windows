//----------------------------------------------------------------------------
// DC.h : デバイスコンテキストの管理を行う
//----------------------------------------------------------------------------
#ifndef DCH
#define DCH
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// デバイスコンテキストの管理を行うクラス
//----------------------------------------------------------------------------
class CDC
{
public: // 関数

	CDC(): m_hDC(0) { }
	virtual ~CDC() { Destroy(); }
	virtual void Destroy() { if(m_hDC) DeleteDC(m_hDC), m_hDC = 0; }

	virtual int GetTextHeight(const tstring & str) const {
		SIZE size;
		GetTextExtentPoint32(m_hDC, str.c_str(), static_cast<int>(str.length()), &size);
		return size.cy;
	}
	virtual int GetTextWidth(const tstring & str) const {
		SIZE size;
		GetTextExtentPoint32(m_hDC, str.c_str(), static_cast<int>(str.length()), &size);
		return size.cx;
	}
	virtual HFONT SelectFont(HFONT hFont) {
		return (HFONT)SelectObject(m_hDC, hFont);
	}

protected: // メンバ変数

	HDC m_hDC;

public: // メンバ変数の取得・設定

	operator HDC() const { return m_hDC; }
};
//----------------------------------------------------------------------------

#endif