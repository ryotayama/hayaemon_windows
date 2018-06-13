//--------------------------------------------------------------------------
// M3UFile.h : M3Uファイルの管理を行う
//--------------------------------------------------------------------------
#ifndef M3UFileH
#define M3UFileH

#include <tchar.h>
#include <vector>
#include <string>

using namespace std;
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
//	M3Uファイルの管理を行うクラス
//--------------------------------------------------------------------------
class CM3UFile
{
public: // 関数

	CM3UFile(); // コンストラクタ
	~CM3UFile(); // デストラクタ

	tstring GetFilePath(int num);
	void Init();
	void Read(const PCTSTR & pFilePath, BOOL bUtf8);
	void Save(const PCTSTR & pFilePath, tstring str, BOOL bUtf8);

private: // メンバ変数

	vector<tstring> buffer;
	bool isLoaded;

public: // メンバ変数の取得・設定

	bool GetIsLoaded() { return isLoaded; }
	int GetLinesCount() { return (int)buffer.size(); }
	void PushBack(tstring str) { buffer.push_back(str); }
};
//--------------------------------------------------------------------------

#endif