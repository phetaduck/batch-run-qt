#include "settings.h"
#include <sstream>
#include <exception>
#include <string>
#include <algorithm>

#include <QSettings>
#include <QDebug>
#include <QDir>

#include "JSON/json.hpp"
#include "fallout4hardcode.h"

using namespace std;

static const string& workingDirKey = "working_dir";


SessionSettings& Settings::sessionSettings()
{
	static SessionSettings sessionSettings_ {};
	if (sessionSettings_.workingDir.isEmpty()) {
		fstream settingsFile("settings.ini", ios_base::in | ios_base::out);
		stringstream ss;
		ss << settingsFile.rdbuf();
		using namespace nlohmann;
		json settingsJSON;
		try {
			ss >> settingsJSON;
		} catch (exception& e) {
			QString what = QString::fromStdString(e.what());
			qDebug() << what;
		}
		if (!settingsJSON.contains(workingDirKey)) {
			settingsJSON[workingDirKey] = defaultWorkingDir;
		}
#ifdef FALLOUT4_HARDCODE
		string tmp = settingsJSON.at(workingDirKey);
		QString tmpQt = QString::fromStdString(tmp);
		Fallout4Hardcode f4hardcode {tmpQt};
		sessionSettings_.workingDir = f4hardcode.dataDir();

#else
		sessionSettings_.workingDir = settingsJSON[workingDirKey];
#endif
	}
	return sessionSettings_;
}

QStringList Settings::workingDirFiles()
{
	auto out = QDir(sessionSettings().workingDir).entryList(
							 QDir::Files,
							 QDir::SortFlag::Name);
	return out;
}

QStringList Settings::workingDirSubDirs()
{
	auto out = QDir(sessionSettings().workingDir).entryList(
							 QDir::AllDirs,
							 QDir::SortFlag::Name);
	out.removeAll(".");
	return out;
}

#ifdef FALLOUT4_HARDCODE

QStringList Settings::workingDirFilteredFiles(
		const QStringList& filter)
{
	return QDir(sessionSettings().workingDir).entryList(
				filter,
				QDir::Files,
				QDir::SortFlag::Name);
}

#endif

SessionSettings& Settings::changeWorkingDir(QString directory)
{
	QString dirName = std::move(directory);
	SessionSettings& sSettings = sessionSettings();
	if (QDir(dirName).isAbsolute()) {
		sSettings.workingDir = dirName;
	} else {
		auto currentDir = sSettings.workingDir;
		currentDir += "/" + dirName;
		QDir dir(currentDir);
		sSettings.workingDir = dir.absolutePath();
	}
	return sessionSettings() = sSettings;
}

const QStringList& Settings::defaultFileFilter()
{
	return defaultFileFilterConst;
}
