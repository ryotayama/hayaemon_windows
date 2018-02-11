//--------------------------------------------------------------------------
// M3UFile.h : M3Uファイルの管理を行う
//--------------------------------------------------------------------------
#ifndef M3UFileH
#define M3UFileH

#include <vector>
#include "../Common/Define.h"
//--------------------------------------------------------------------------
//	M3Uファイルの管理を行うクラス
//--------------------------------------------------------------------------
class CM3UFile
{
public: // 関数

	CM3UFile(); // コンストラクタ

	tstring GetFilePath(int num);
	void Init();
	void Read(const PCTSTR & pFilePath, BOOL bUtf8);
	void Save(const PCTSTR & pFilePath, tstring str, BOOL bUtf8);

private: // メンバ変数

	std::vector<tstring> buffer;
	bool isLoaded;

public: // メンバ変数の取得・設定

	int GetLinesCount() { return (int)buffer.size(); }
};
//--------------------------------------------------------------------------

#endif
