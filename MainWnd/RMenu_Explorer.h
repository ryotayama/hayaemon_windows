//----------------------------------------------------------------------------
// RMenu_Explorer.h : エクスプローラ用右クリックメニューの管理を行う
//----------------------------------------------------------------------------
#ifndef RMenu_ExplorerH
#define RMenu_ExplorerH

class CExplorer;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// エクスプローラ用右クリックメニューの作成・管理を行うクラス
//----------------------------------------------------------------------------
class CRMenu_Explorer : public CMenu
{
public: // 関数

	CRMenu_Explorer(CExplorer & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_Explorer() { }

	virtual BOOL Create(BOOL bOnItem);
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnOpenFilesMenuSelected();
	void OnAddFilesMenuSelected();
	void OnOpenFolderMenuSelected();
	void OnPropertiesMenuSelected();
	void OnVisibleMenuSelected();

private: // メンバ変数

	CExplorer & m_rParent;

public: // 定数

	// コマンド ID
	enum {
		ID_OPEN = 11,
		ID_ADD,
		ID_OPENFOLDER,
		ID_PROPERTIES,
		ID_VISIBLE,
	};
};
//----------------------------------------------------------------------------

#endif