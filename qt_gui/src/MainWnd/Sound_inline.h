//----------------------------------------------------------------------------
// Sound_inline.h : CSoundクラスのインラインメンバーの実装
//----------------------------------------------------------------------------
#pragma once

#include "Sound.h"

#include <QString>
#include "Utility.h"

void CSound::SaveFile(const QString & filePath, int nFormat)
{
	SaveFile(ToTstring(filePath).c_str(), nFormat);
}

