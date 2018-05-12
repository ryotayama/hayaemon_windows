//----------------------------------------------------------------------------
// ExplorerBar.h : エクスプローラ用ツールバーの管理を行う
//----------------------------------------------------------------------------
#ifndef ExplorerBarH
#define ExplorerBarH

#include <QLineEdit>
#include "../Common/Define.h"
class CMainWnd;
class QLineEdit;
//----------------------------------------------------------------------------
// エクスプローラ用ツールバーの管理を行うクラス
//----------------------------------------------------------------------------
class CExplorerBar : public QLineEdit
{
public: // 関数

	explicit CExplorerBar(QWidget * parent);

	virtual BOOL Create(CMainWnd * mainWnd);
	virtual void OnReturnKeyPressed();

private: // メンバ変数

	CMainWnd * m_rMainWnd;
	QLineEdit & m_edit;

public: // メンバ変数の取得・設定

	QLineEdit & GetEdit() { return m_edit; }
};
//----------------------------------------------------------------------------

#endif
