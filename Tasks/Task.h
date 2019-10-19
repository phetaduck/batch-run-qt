#ifndef PROGRESSMONITOR_H
#define PROGRESSMONITOR_H

#include <QProcess>
#include <memory>

#include <QTextCodec>

class MainWindow;

class Task : public QObject
{
    Q_OBJECT

public:

    Task(
            const QString& program,
            const QStringList& arguments,
            const QString& shell);
public slots:

    void chainExecute(QObject* stdOut);

signals:

    void taskStarted(QString status);
    void taskError(QString status);
    void taskFinished(QString status);

    void nextInChain(QObject*);


protected slots:

    void on_processError(QProcess::ProcessError processError);

    void on_processFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void on_processStarted();


protected:

    void createProcess(
            const QString& program,
            const QStringList& arguments,
            const QString& shell);
    void connectToProcess();
    QProcess* process = nullptr;
    QObject* stdOut = nullptr;

    void emitSuccess(QString report);

private:

    explicit Task(QObject *parent) : QObject(parent) {}
    void setParent(QObject*) {}

};

class RobocopyTask : public Task
{
    Q_OBJECT
public:

    RobocopyTask(
            const QString& program,
            const QStringList& arguments,
            const QString& shell) : Task(
                                       program,
                                       arguments,
                                       shell) {

    }
protected slots:

    void on_processFinished(int exitCode, QProcess::ExitStatus exitStatus);

};

Task* taskFactory(
        const QString& program,
        const QStringList& arguments,
        const QString& shell);

#endif // PROGRESSMONITOR_H
