//----------------------------------------------------------------------------
// AcceleratorTable.cpp : アクセラレータテーブルの管理を行う
//----------------------------------------------------------------------------
#include "AcceleratorTable.h"
#include "CommandList.h"

// Default shortcutkey
ST_ACCEL defAccel[] = {
	{FCONTROL | FVIRTKEY,          'O',      ID_OPENFILE},
	{FCONTROL | FVIRTKEY,          'E',      ID_SAVEFILE},
	{FCONTROL | FVIRTKEY,          'A',      ID_SELECTALL},
	{FCONTROL | FVIRTKEY,          'P',      ID_PAUSE},
	{FVIRTKEY,                     VK_SPACE, ID_PAUSE},
	{FCONTROL | FVIRTKEY,          'S',      ID_STOP},
	{FCONTROL | FVIRTKEY,          '0',      ID_HEAD},
	{FCONTROL | FVIRTKEY,          'B',      ID_PREV},
	{FCONTROL | FVIRTKEY,          'F',      ID_NEXT},
	{FCONTROL | FSHIFT | FVIRTKEY, 'B',      ID_REWIND},
	{FCONTROL | FSHIFT | FVIRTKEY, 'F',      ID_FORWARD},
	{FCONTROL | FVIRTKEY,          '1',      ID_SLOOP},
	{FCONTROL | FVIRTKEY,          'T',      ID_ALOOP},
	{FCONTROL | FVIRTKEY,          'H',      ID_RANDOM},
	{NULL, NULL, NULL}
};


BOOL CAcceleratorTable::Add(BYTE fVirt, WORD key, WORD cmd)
{
	// ハンドルが存在しない場合は新たに作成する
	if(!m_hAccel)
	{
		ACCEL accel[1];
		ZeroMemory(&accel, sizeof(ACCEL));
		accel[0].fVirt = fVirt;
		accel[0].key = key;
		accel[0].cmd = cmd;

		Create(accel, 1);
	}
	else
	{
		int nAccel = GetNum();

		ACCEL * pAccel = new ACCEL[nAccel + 1];
		Copy(pAccel, nAccel);
		pAccel[nAccel].fVirt = fVirt;
		pAccel[nAccel].key = key;
		pAccel[nAccel].cmd = cmd;

		Create(pAccel, nAccel + 1);

		delete [] pAccel;
	}

	return m_hAccel ? TRUE : FALSE;
}

int CAcceleratorTable::Copy(LPACCEL lpAccelDst, int cAccelEntries)
{
	if(!m_hAccel) return 0;

	return CopyAcceleratorTable(m_hAccel, lpAccelDst, cAccelEntries);
}

BOOL CAcceleratorTable::Create(LPACCEL pAccel, int nAccel)
{
	Destroy();
	m_hAccel = CreateAcceleratorTable(pAccel, nAccel);
	return m_hAccel ? TRUE : FALSE;
}

BOOL CAcceleratorTable::Delete(BYTE fVirt, WORD key, WORD cmd)
{
	if(!m_hAccel) return FALSE;

	int nAccel = GetNum();

	ACCEL * pAccel = new ACCEL[nAccel];
	Copy(pAccel, nAccel);
	BOOL bFound = FALSE; // 同じエントリが見つかったかどうか
	for(int i = 0; i < nAccel; i++)
	{
		if(pAccel[i].fVirt == fVirt && pAccel[i].key == key && pAccel[i].cmd == cmd)
			bFound = TRUE;

		if(bFound) // 見つかったら、１つずつ前に移動
		{
			pAccel[i].fVirt = pAccel[i + 1].fVirt;
			pAccel[i].key = pAccel[i + 1].key;
			pAccel[i].cmd = pAccel[i + 1].cmd;
		}
	}

	if(bFound) Create(pAccel, nAccel - 1);

	delete [] pAccel;

	return m_hAccel ? TRUE : FALSE;
}

BOOL CAcceleratorTable::Destroy()
{
	BOOL bSuccess = FALSE;
	if(m_hAccel)
	{
		bSuccess = DestroyAcceleratorTable(m_hAccel);
		m_hAccel = 0;
	}
	return bSuccess;
}

WORD CAcceleratorTable::GetCommandId(int i)
{
	if(!m_hAccel) return 0;

	int nAccel = GetNum();
	if(i > nAccel) return 0;

	ACCEL * pAccel = new ACCEL[nAccel];
	Copy(pAccel, nAccel);

	WORD cmd = pAccel[i].cmd;

	delete [] pAccel;

	return cmd;
}

tstring CAcceleratorTable::GetShortCut(int i)
{
	if(!m_hAccel) return _T("");

	int nAccel = GetNum();
	if(i > nAccel) return _T("");

	ACCEL * pAccel = new ACCEL[nAccel];
	Copy(pAccel, nAccel);

	tstring strShortCut = GetShortCut(pAccel[i].fVirt, pAccel[i].key);
	delete [] pAccel;

	return strShortCut;
}

tstring CAcceleratorTable::GetShortCut(BYTE fVirt, UINT key)
{
	tstring strShortCut = _T("");
	if(fVirt & FCONTROL) strShortCut += _T("Ctrl + ");
	if(fVirt & FALT) strShortCut += _T("Alt + ");
	if(fVirt & FSHIFT) strShortCut += _T("Shift + ");

	strShortCut += GetStringFromKey(key);
	return strShortCut;
}

tstring CAcceleratorTable::GetStringFromKey(UINT key)
{
	TCHAR text[255];
	UINT uScanCode = MapVirtualKey(key, 0);
	UINT uScanCode2 = MapVirtualKeyEx(key, 0, GetKeyboardLayout(0));
	UINT ext = 0;

	if (key == VK_CLEAR)
		return _T(""); // Numlock 無効時の "Num 5" 避け

	if (IS_EXTKEY(key))
		ext = 1 << 24;

	if(GetKeyNameText((uScanCode << 16) | ext, text, 255))
		return text;

	return _T("");
}

UINT CAcceleratorTable::GetKeyFromString(tstring str)
{
	if(str.length() == 1 &&
		((_T("A") <= str && str <= _T("Z")) || (_T("0") <= str && str <= _T("9"))))
			return (UINT)str[0];

	for(UINT u = 0; u < 0xFF; u++)
	{
		if(str == GetStringFromKey(u))
			return u;
	}

	return 0;
}

void CAcceleratorTable::SetDefault()
{
	Destroy();
	for (int i = 0; defAccel[i].key != NULL; i++)
		Add(defAccel[i].virt, defAccel[i].key, defAccel[i].cmd);
}

ST_ACCEL CAcceleratorTable::GetDefault(int idx)
{
	int cnt = sizeof(defAccel) / sizeof(ST_ACCEL);

	if (idx >= cnt || idx < 0)
		return defAccel[cnt-1];
	
	return defAccel[idx];
}
