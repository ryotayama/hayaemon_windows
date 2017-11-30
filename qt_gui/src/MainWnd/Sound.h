//----------------------------------------------------------------------------
// Sound.h : 音の再生管理
//----------------------------------------------------------------------------
#ifndef SoundH
#define SoundH

#include "../Common/BassFx.h"
#include "../Common/Define.h"
//----------------------------------------------------------------------------
// 音の再生管理クラス
//----------------------------------------------------------------------------
class CSound : public CBassFx
{
public: // 関数

	explicit CSound(BOOL bMainStream = TRUE);

	virtual BOOL StreamCreateFile(LPCTSTR lpFilePath, BOOL bDecode = FALSE,
		int nCount = 1);
	virtual void SetLoop(BOOL bLoop);

private: // メンバ変数

	BOOL m_bLoop; // １曲ループがオンかどうか

	tstring m_strCurFile;
	int m_nCurFile;
	BOOL m_bMainStream;

public: // メンバ変数の取得・設定

	virtual BOOL IsLoop() const { return m_bLoop; }
	virtual int GetCurFileNum() const { return m_nCurFile; }
	virtual void SetCurFileNum(int n) { m_nCurFile = n; }
};
//----------------------------------------------------------------------------

#endif
