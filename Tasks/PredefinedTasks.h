#ifndef PREDEFINEDTASKS_H
#define PREDEFINEDTASKS_H

#include <QObject>
#include <QDir>

#include <settings.h>
#include <Task.h>
#include <deque>

class PredefinedTasks {
public:
		PredefinedTasks(SessionSettings settings);
    void seqExec(QObject* delegate);

private:
		SessionSettings settings;
    std::deque<Task*> tasks;

    void pushToDequeue(
            const QString& program,
            const QStringList& arguments,
            const QString& shell);

    void createTasks(const QString& file);

    void unpackBA2Archve(
            const QString& file);

    QStringList unpackBA2ArchiveArguments(
            const QString& file,
            const QString& directory);

    void robocopyTextures(
            const QString& dest);

    QStringList robocopyNewArchiveArguments(
            const QString& source,
            const QString& dest);

    void createBA2Archive(const QString& source, const QString& file);

    QStringList createBA2ArchiveArguments(
            const QString& directory,
            const QString& file);
    void connectSeq();
};

#endif // PREDEFINEDTASKS_H
