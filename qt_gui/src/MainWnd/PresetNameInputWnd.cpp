//----------------------------------------------------------------------------
// PresetNameInputWnd.cpp : プリセット名入力ウィンドウの管理を行う
//----------------------------------------------------------------------------
#include "PresetNameInputWnd.h"
#include "MainWnd.h"
#include "Utility.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CPresetNameInputWnd::CPresetNameInputWnd(CMainWnd & mainWnd)
	: m_rMainWnd(mainWnd)
{
	Ui::PresetNameInputWnd::setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	connect(this->buttonBox, &QDialogButtonBox::accepted,
					[&] { SetPreset(); });
}
//----------------------------------------------------------------------------
// プリセット名の設定
//----------------------------------------------------------------------------
void CPresetNameInputWnd::SetPreset()
{
	tstring strTime = ToTstring(m_edit->text());
	m_rMainWnd.AddPreset(strTime);
	accepted();
}
//----------------------------------------------------------------------------
