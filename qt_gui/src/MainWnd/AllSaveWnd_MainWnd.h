//----------------------------------------------------------------------------
// AllSaveWnd_MainWnd.h : 一括変換ウィンドウの管理を行う
//----------------------------------------------------------------------------
#ifndef AllSaveWnd_MainWndH
#define AllSaveWnd_MainWndH

#include <QDialog>
#include "ui_AllSaveWnd.h"
class CMainWnd;
//----------------------------------------------------------------------------
// 一括変換ウィンドウの管理を行うクラス
//----------------------------------------------------------------------------
class CAllSaveWnd_MainWnd : public QDialog, public Ui::AllSaveWnd
{
	Q_OBJECT

public: // 関数

	explicit CAllSaveWnd_MainWnd(CMainWnd & mainWnd);

public: // 定数

  int GetFormat()
	{
		// 0 : WAVE
		// 1 : MP3
		// 2 : OGG

		return m_Combo->currentIndex();
	}
};
//----------------------------------------------------------------------------

#endif
