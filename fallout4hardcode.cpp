#include "fallout4hardcode.h"
#include <string>
#include <QSettings>
#include <QDir>

using namespace std;

const string& defaultWorkingDir = "HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\bethesda softworks\\Fallout4";
const QStringList& defaultFileFilterConst {
	QStringLiteral("DLC* - Textures*.ba2"),
			QStringLiteral("Fallout4 - Textures*.ba2")};

Fallout4Hardcode::Fallout4Hardcode(const QString& registryKey)
{   
	QSettings falloutInstallDir(
				registryKey,
				QSettings::NativeFormat);
	auto value = falloutInstallDir.value(QStringLiteral("installed path"));
	installDir_ = value.toString();
}

QStringList Fallout4Hardcode::workingDirFiles(
		const QString& path)
{
	auto out = QDir(path).entryList(
							 QDir::Files,
							 QDir::SortFlag::Name);
	return out;

}

QStringList Fallout4Hardcode::workingDirFilteredFiles(
		const QString& path,
		const QStringList filter)
{
	return QDir(path).entryList(
				filter,
				QDir::Files,
				QDir::SortFlag::Name);
}
