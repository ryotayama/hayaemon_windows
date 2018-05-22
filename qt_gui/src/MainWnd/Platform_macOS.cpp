//----------------------------------------------------------------------------
// Platform.cpp : macOS用プラットフォーム依存の関数
//----------------------------------------------------------------------------
#include "Platform.h"

#if __APPLE__

#include <time.h>

#include <map>
#include <QDebug>
#include <QSettings>
#include <QString>

#include "Utility.h"

#ifdef UNICODE
int _ttoi(const TCHAR *str) {
	return ToQString(str).toInt();
}

double _ttof(const TCHAR *str) {
	return ToQString(str).toDouble();
}

double _tstof(const TCHAR *str) {
	return _ttof(str);
}
#endif

int _tcsicmp(const TCHAR *lhs, const TCHAR *rhs) {
	auto l = ToQString(lhs);
	auto r = ToQString(rhs);
	return l.compare(r, Qt::CaseInsensitive);
}

void OutputDebugString(const TCHAR *str) {
	qDebug() << str;
}

DWORD timeGetTime(void) {
	return clock();
}

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

DWORD GetPrivateProfileString(LPCTSTR lpAppName, LPCTSTR lpKeyName, 
                              LPCTSTR lpDefault, LPTSTR lpReturnedString,
                              DWORD nSize, LPCTSTR lpFileName)
{
	std::wstring value = ToQString(lpDefault).toStdWString();

	auto settings = ini_files().GetFile(ToQString(lpFileName));
	settings->beginGroup(ToQString(lpAppName));
	auto v = settings->value(ToQString(lpKeyName));
	if (v.isValid()) {
		value = v.toString().toStdWString();
	}
	std::copy(value.begin(), value.end(), lpReturnedString);
	size_t l = value.size();
	lpReturnedString[value.size()] = 0;
	settings->endGroup();
	return value.length();
}

BOOL WritePrivateProfileString(LPCTSTR lpAppName, LPCTSTR lpKeyName,
															 LPCTSTR lpString, LPCTSTR lpFileName)
{
	auto settings = ini_files().GetFile(ToQString(lpFileName));
	if (!settings->isWritable()) {
		return FALSE;
	}
	settings->beginGroup(ToQString(lpAppName));
	if (lpKeyName != nullptr && lpString != nullptr) {
		settings->setValue(ToQString(lpKeyName), ToQString(lpString));
	} else {
		settings->remove("");
	}
	settings->endGroup();

	return TRUE;
}
#endif // __APPLE__
