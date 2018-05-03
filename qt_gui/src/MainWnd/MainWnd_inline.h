//----------------------------------------------------------------------------
// MainWnd_inline.h : CMainWndクラスのインラインメンバーの実装
//----------------------------------------------------------------------------
#pragma once

#include "MainWnd.h"

#include <QString>
#include "Utility.h"

void CMainWnd::SaveSettings(const QString & filePath)
{
	SaveSettings(ToTstring(filePath).c_str());
}

