#include "taskmanager.h"
#include <exception>

TaskManager::TaskManager(QObject *parent) : QObject(parent)
{

}

void TaskManager::append(Task* task)
{
	if (!task) {
		throw std::invalid_argument("Task is null");
	}
	tasks_.push_back(task);
}

