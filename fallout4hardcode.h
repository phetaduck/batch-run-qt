#ifndef FALLOUT4HARDCODE_H
#define FALLOUT4HARDCODE_H

#include <string>

#include <QString>
#include <QStringList>

#include <helperutil.h>

extern const std::string& defaultWorkingDir;
extern const QStringList& defaultFileFilterConst;

class Fallout4Hardcode
{
public:
    Fallout4Hardcode(const QString& registryKey);
    const QString& installDir() const {
        return installDir_;
    }

		QString dataDir() {
        return installDir() + "Data";
    }

		QString archive2() {
			return installDir() + "/Tools/Archive2/Archive2.exe";
		}
		static QStringList workingDirFiles(const QString& path);
		static QStringList workingDirFilteredFiles(
				const QString& path,
				const QStringList filter);
private:
    QString installDir_;
		QStringList preselectedFiles_;
		QStringList dirContent_;
};

#endif // FALLOUT4HARDCODE_H
