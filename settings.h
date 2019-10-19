#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QStringList>
#include <fstream>

#include <helperutil.h>


struct SessionSettings {
		QString inputDir;
		QString outputDir;
		QString workingDir;
		QString shell;
		QString program;
		QStringList files;
};

namespace Settings
{
		SessionSettings& sessionSettings();

		QStringList workingDirFiles();
		QStringList workingDirFilteredFiles(
				const QStringList& filter);
		QStringList workingDirSubDirs();

		SessionSettings& changeWorkingDir(const QString& dirName);
		const QStringList& defaultFileFilter();

};

#endif // SETTINGS_H
