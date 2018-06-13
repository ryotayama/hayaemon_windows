//----------------------------------------------------------------------------
// Explorer.h : エクスプローラの管理を行う
//----------------------------------------------------------------------------
#ifndef ExplorerH
#define ExplorerH

#pragma warning(disable: 4355)
	// 'this' : ベース メンバ初期化リストで使用されました。
#include <vector>
class CApp;
class CMainWnd;
#include "RMenu_Explorer.h"
#include "../Common/ListView.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// エクスプローラの管理を行うクラス
//----------------------------------------------------------------------------
class CExplorer : public CListView
{
public: // 関数

	CExplorer(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), isLastSortUp(FALSE),
		  lastSort(-1), m_nHeaderHeight(0), m_rClickMenu(*this) { }
	virtual ~CExplorer() { }

	virtual BOOL Create();
	virtual int GetWidth() const;
	virtual BOOL OpenDirectory();
	virtual void OpenFiles(BOOL bClear);
	virtual void OpenFolder();
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void SetIcon(NMLVDISPINFO * pnmlvdi);
	virtual BOOL ShowFiles();
	virtual void ShowProperties();
	virtual void Sort(NMLISTVIEW* pnmlv);

	static int CALLBACK SortProc(LPARAM lp1, LPARAM lp2, LPARAM lp3);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnBeginDrag(NM_LISTVIEW *pnmlv);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnDropFiles(HDROP hdrop);
	virtual void OnGetDispInfo(NMHDR* pnmhdr);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // メンバ変数

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	int m_nHeaderHeight;
	int lastSort; // 前回ソートしたインデックス
	BOOL isLastSortUp; // 前回のソートが昇順だったか
	std::vector<tstring> filePaths;

	CRMenu_Explorer m_rClickMenu; // 右クリックメニュー

public: // メンバ変数の取得・設定

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif