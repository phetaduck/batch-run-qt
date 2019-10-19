#include "PredefinedTasks.h"
#include <algorithm>
#include <helperutil.h>

PredefinedTasks::PredefinedTasks(SessionSettings settings) {
    this->settings = std::move(settings);
    for (const auto& file : this->settings.files) {
        createTasks(file);
    }
}

void PredefinedTasks::pushToDequeue(
        const QString &program,
        const QStringList &arguments,
        const QString &shell)
{
    auto task = taskFactory(
                program,
                arguments,
                shell);
    tasks.push_back(task);
}

void PredefinedTasks::createTasks(const QString &file)
{
    unpackBA2Archve(file);
}

void PredefinedTasks::unpackBA2Archve(const QString &file)
{
    QFileInfo inputFile(QString{file});
    QString stem = inputFile.baseName();
    QDir dir (settings.outputDir);
    if (!dir.exists(stem)) {
        dir.mkdir(stem);
    }
    QDir newDir (dir.absolutePath() + '/' + stem);
    QString newDirPath = newDir.absolutePath();
    auto arguments = unpackBA2ArchiveArguments(
                file, newDirPath);
    pushToDequeue(
                settings.program,
                arguments,
                settings.shell);
    robocopyTextures(newDirPath);
}

void PredefinedTasks::robocopyTextures(const QString &dest)
{
    auto arguments = robocopyNewArchiveArguments(settings.inputDir, dest);
    pushToDequeue(
                "robocopy",
                arguments,
                settings.shell);
    createBA2Archive(
                dest,
                dest + ".ba2");
}

void PredefinedTasks::createBA2Archive(const QString &source, const QString &file)
{
    auto arguments = createBA2ArchiveArguments(
                source, file);
    pushToDequeue(
                settings.program,
                arguments,
                settings.shell);
}

QStringList PredefinedTasks::unpackBA2ArchiveArguments(const QString &file, const QString &directory)
{
    QStringList out;
    out << addQuotes( file );
    out << "-extract=" + addQuotes( directory );
    return out;
}

QStringList PredefinedTasks::robocopyNewArchiveArguments(const QString &source, const QString &dest)
{
    QStringList out;
    out << addQuotes( source );
    out << addQuotes( dest );
    out << "/S /XL";
    return out;
}

QStringList PredefinedTasks::createBA2ArchiveArguments(const QString &directory, const QString &file)
{
    QStringList out;
    out << addQuotes(directory);
    auto filePath = file;
#ifdef _WIN32
    filePath.replace('/', '\\');
#endif
    out << addQuotes("-create=" + filePath);
    out << addQuotes("-root=" + directory);
    out << addQuotes(QString{"-format=DDS"} );
    return out;
}

void PredefinedTasks::connectSeq()
{
    auto task = tasks.front();
    tasks.pop_front();
    while(!tasks.empty()) {
        auto nextTask = tasks.front();
        tasks.pop_front();
        QObject::connect(task, SIGNAL(nextInChain(QObject*)),
                         nextTask, SLOT(chainExecute(QObject*)));
        task = nextTask;
    }
}

void PredefinedTasks::seqExec(QObject *delegate)
{
    auto firstTask = tasks.front();
    connectSeq();
    firstTask->chainExecute(delegate);
}
