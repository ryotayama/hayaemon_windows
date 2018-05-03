//----------------------------------------------------------------------------
// PresetNameInputWnd.h : プリセット名入力ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef PresetNameInputWndH
#define PresetNameInputWndH

#include <QDialog>
#include "ui_PresetNameInputWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// プリセット名入力ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CPresetNameInputWnd : public QDialog, public Ui::PresetNameInputWnd
{
public: // 関数

	explicit CPresetNameInputWnd(CMainWnd & mainWnd);

	virtual void SetPreset();

private: // メンバ変数

	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------

#endif
