#include "filefilterstate.h"

FileFilterState::FileFilterState(QObject *parent)
	: QObject(parent), fileFilterEnabled(true),
		fileFilter(Settings::defaultFileFilter())

{
}

void FileFilterState::append(QString string)
{
	fileFilter.append(std::move(string));
	emit fileFilterChanged(fileFilter);
}

QString FileFilterState::back() const
{
	return fileFilter.back();
}

void FileFilterState::setLast(QString string)
{
	fileFilter.back() = std::move(string);
	emit fileFilterChanged(fileFilter);
}

void FileFilterState::removeLast()
{
	fileFilter.removeLast();
	emit fileFilterChanged(fileFilter);
}

void FileFilterState::removeAt(int index)
{
	fileFilter.removeAt(index);
	emit fileFilterChanged(fileFilter);
}

int FileFilterState::size() const
{
	return fileFilter.size();
}
