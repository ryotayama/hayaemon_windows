//----------------------------------------------------------------------------
// LyricsManager.h : 歌詞表示機能の管理クラス
//----------------------------------------------------------------------------
#ifndef LyricsManagerH
#define LyricsManagerH

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
class CLyricsManager
{
public: // 関数

	CLyricsManager(CApp & app, CMainWnd & mainWnd);
	virtual ~CLyricsManager();
	virtual void AddLyrics(double dStartTime, double dEndTime, tstring str,
						   BOOL bReline);
	virtual void ClearScreen();
	virtual void DrawTitle(CWnd* pWnd);
	virtual void DrawLine(tstring str, int nLine, CWnd* pWnd);
	virtual double GetCharacterLength(tstring str);
	virtual double GetExtendedTimeTag(LPTSTR p);
	virtual double GetTimeTag(LPTSTR p);
	virtual tstring GetTagValue(LPTSTR p);
	virtual BOOL IsExtendedTimeTag(LPTSTR p);
	virtual BOOL IsNumeric(LPTSTR p, BOOL bBeforeFive = FALSE);
	virtual BOOL IsTag(LPTSTR p);
	virtual BOOL IsTimeTag(LPTSTR p);
	virtual BOOL IsArtistTag(LPTSTR p);
	virtual BOOL IsOffsetTag(LPTSTR p);
	virtual BOOL IsTitleTag(LPTSTR p);
	virtual BOOL IsBgFolderTag(LPTSTR p);
	virtual void LoadBackImage(tstring strPath, double dLevel);
	virtual BOOL Read(tstring strOriginalFilePath);
	virtual void Update(double dCurrentTime);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	HBITMAP hBitmap;
	HDC hMemDC;
	HBITMAP hBackBitmap;
	HDC hBackDC;
	tstring strBackPath;
	std::vector<tstring> m_arStrBackPath;
	int nBackWidth;
	int nBackHeight;
	HFONT hFont;
	void* pImage;
	std::vector<ST_LYRICS> arrayLyrics; // 歌詞を保持する配列
	double dMaxCharacters; // 最大文字数
	int nLine; // 現在の行数
	ST_LYRICS stlLast; // 前回表示した歌詞
	tstring strTitle; // タイトル
	tstring strArtist; // アーティスト名

public: // メンバ変数の取得・設定
	BOOL IsLyricsRead() {
		return (arrayLyrics.size() > 0);
	}
};
//----------------------------------------------------------------------------

#endif