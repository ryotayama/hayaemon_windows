//----------------------------------------------------------------------------
// Platform.cpp : macOS用プラットフォーム依存の関数
//----------------------------------------------------------------------------
#include "Platform.h"

#if __APPLE__

#include <map>
#include <QSettings>

#include "Utility.h"

namespace {

class IniFiles {
public:
	IniFiles() = default;
	explicit IniFiles(const IniFiles &) = delete;
	IniFiles &operator=(const IniFiles &) = delete;

	~IniFiles() {
		for (auto &kv : files_) {
			delete kv.second;
		}
	}

	QSettings* GetFile(const QString &filepath) {
		auto it = files_.find(filepath);
		if (it == files_.end()) {
			auto settings = new QSettings(filepath, QSettings::IniFormat);
			files_.insert({filepath, settings});
			return settings;
		} else {
			return it->second;
		}
	}

private:
	std::map<QString, QSettings *> files_;
};

IniFiles& ini_files() {
	static IniFiles instance;
	return instance;
}

}  // namespace

UINT GetPrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nDefault,
													LPCTSTR lpFileName)
{
	int value = nDefault;

	auto settings = ini_files().GetFile(ToQString(lpFileName));
	settings->beginGroup(ToQString(lpAppName));
	auto v = settings->value(ToQString(lpKeyName));
	if (v.isValid()) {
		value = v.toInt();
	}
	settings->endGroup();
	return value > 0 ? value : 0;
}

BOOL WritePrivateProfileString(LPCTSTR lpAppName, LPCTSTR lpKeyName,
															 LPCTSTR lpString, LPCTSTR lpFileName)
{
	auto settings = ini_files().GetFile(ToQString(lpFileName));
	if (!settings->isWritable()) {
		return FALSE;
	}
	settings->beginGroup(ToQString(lpAppName));
	settings->setValue(ToQString(lpKeyName), ToQString(lpString));
	settings->endGroup();

	return TRUE;
}
#endif // __APPLE__
