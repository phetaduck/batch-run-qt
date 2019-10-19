#include "Task.h"
#include <helperutil.h>

void Task::on_processError(QProcess::ProcessError processError)
{
    QString report;
    switch (processError) {
    case QProcess::FailedToStart :
        report += process->program() +
                process->nativeArguments() +
                " failed to start.";
        break;
    case QProcess::Crashed :
        report += process->program() +
                process->nativeArguments() +
                " crashed!";
        break;
    case QProcess::Timedout :
        report += process->program() +
                process->nativeArguments() +
                " timed out.";
        break;
    case QProcess::ReadError :
        report += process->program() +
                process->nativeArguments() +
                " read error.";
        break;
    case QProcess::WriteError :
        report +=
                process->program() +
                process->nativeArguments() +
                " write error.";
        break;
    case QProcess::UnknownError :
        report +=
                process->program() +
                process->nativeArguments() +
                " unknown error.";
        break;
    }
    QString p_std = process->readAllStandardError();
    if (p_std.isEmpty()) {
        p_std = process->readAllStandardOutput();
    }
    report += p_std;
    emit taskError(report);
}

void Task::emitSuccess(QString report)
{
    emit taskFinished(report);
    if (stdOut) {
        emit nextInChain(stdOut);
        stdOut = nullptr;
    }
}

void Task::on_processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString report;
    QProcess* process = qobject_cast<QProcess*>(sender());
    if (exitCode) {
        report += process->program() +
                " " +
                " error!";
        if (exitStatus == QProcess::CrashExit)
            report += process->program() + " " +
                    process->nativeArguments() +
                    " crashed!";
        QString p_std = process->readAllStandardError();
        if (p_std.isEmpty()) {
            p_std = process->readAllStandardOutput();
        }
        report += p_std;
    } else {
        report += process->program() +
                " " +
                process->nativeArguments() +
                " finished succesfully!";
    }
    emitSuccess(report);
}

void Task::on_processStarted()
{
    QString report;
    report += process->program() +
            " " +
            process->nativeArguments() +
            " started.";
    emit taskStarted(report);
}

Task::Task(const QString &program, const QStringList &arguments, const QString &shell)
{
    createProcess(program, arguments, shell);
    connectToProcess();
}

void Task::chainExecute(QObject* stdOut)
{
    this->stdOut = stdOut;
    QObject::connect(this, SIGNAL(taskStarted(QString)),
                     stdOut, SLOT(on_taskStarted(QString)));
    QObject::connect(this, SIGNAL(taskError(QString)),
                     stdOut, SLOT(on_taskError(QString)));
    QObject::connect(this, SIGNAL(taskFinished(QString)),
                     stdOut, SLOT(on_taskFinished(QString)));
    QObject::connect(this->process, SIGNAL(readyReadStandardOutput()),
                     stdOut, SLOT(processStdout()) );
    process->start();
}

void Task::createProcess(const QString &program, const QStringList &arguments, const QString &shell)
{
    process = new QProcess(this);
    QString nativeArguments {};
    if (shell.isEmpty()) {
        process->setProgram(program);
        nativeArguments = arguments.join(" ");
    }
    else {
        process->setProgram(shell);
        nativeArguments = "/C " + addQuotes(addQuotes(program) + " " + arguments.join(" "));
    }
    process->setNativeArguments(nativeArguments);
}

void Task::connectToProcess()
{
    connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(on_processError(QProcess::ProcessError)));
    connect(process,
            SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(on_processFinished(int, QProcess::ExitStatus)));
    connect(process, SIGNAL(started()),
            this, SLOT(on_processStarted()));
}

void RobocopyTask::on_processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString report;
    if (exitCode > 7) {
        report += process->program() +
                " error!";
        report += "ExitCode: " + QString::number(exitCode);
        if (exitStatus == QProcess::CrashExit)
            report += process->program() +
                    process->nativeArguments() +
                    " crashed!";
        QString p_std = process->readAllStandardError();
        if (p_std.isEmpty()) {
            p_std = process->readAllStandardOutput();
        }
        report += p_std;
    } else {
        report += process->nativeArguments() +
                " finished succesfully!";
    }
    emitSuccess(report);
}

Task *taskFactory(const QString &program, const QStringList &arguments, const QString &shell)
{
    if (program == "robocopy") {
        return new RobocopyTask(
                    program,
                    arguments,
                    shell);
    }
    return new Task(
                program,
                arguments,
                shell);
}
