#ifndef PROGRESSMONITOR_H
#define PROGRESSMONITOR_H

#include <QProcess>
#include <memory>

#include <QTextCodec>

class MainWindow;

class Task : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString program READ program WRITE setProgram NOTIFY programChanged)
	Q_PROPERTY(QStringList arguments READ arguments WRITE setArguments NOTIFY argumentsChanged)
	Q_PROPERTY(QString shell READ shell WRITE setShell NOTIFY shellChanged)

public:

	explicit Task(QObject *parent = nullptr) : QObject(parent) {}
	Task(
			const QString& program,
			const QStringList& arguments,
			const QString& shell);
	QString program() const
	{
		return m_program;
	}

	QStringList arguments() const
	{
		return m_arguments;
	}

	QString shell() const
	{
		return m_shell;
	}

public slots:

	void chainExecute(QObject* stdOut);

	void setProgram(QString program)
	{
		if (m_program == program)
			return;

		m_program = program;
		emit programChanged(m_program);
	}

	void setArguments(QStringList arguments)
	{
		if (m_arguments == arguments)
			return;

		m_arguments = arguments;
		emit argumentsChanged(m_arguments);
	}

	void setShell(QString shell)
	{
		if (m_shell == shell)
			return;

		m_shell = shell;
		emit shellChanged(m_shell);
	}

signals:

	void taskStarted(QString status);
	void taskError(QString status);
	void taskFinished(QString status);

	void nextInChain(QObject*);


	void programChanged(QString program);

	void argumentsChanged(QStringList arguments);

	void shellChanged(QString shell);

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

	void setParent(QObject*) {}

	QString m_program;
	QStringList m_arguments;
	QString m_shell;
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
