#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <Task.h>

#include <deque>

class TaskManager : public QObject
{
	Q_OBJECT
public:

	explicit TaskManager(QObject *parent = nullptr);


signals:

public slots:

	void append(Task* task);

private:
	std::deque<Task*> tasks_;
};

#endif // TASKMANAGER_H
