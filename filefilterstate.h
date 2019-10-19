#ifndef UISTATE_H
#define UISTATE_H

#include <QObject>
#include <QStringListModel>

#include "settings.h"

class FileFilterState : public QObject
{
	Q_OBJECT
	Q_PROPERTY( bool fileFilterEnabled MEMBER fileFilterEnabled NOTIFY fileFilterEnabledChanged)
	Q_PROPERTY(QStringList fileFilter MEMBER fileFilter NOTIFY fileFilterChanged)


public:
	explicit FileFilterState(QObject *parent = nullptr);
	bool fileFilterEnabled = true;
	QStringList fileFilter;

signals:

	void fileFilterEnabledChanged(bool fileFilterEnabled);

	void fileFilterChanged(QStringList fileFilter);

public slots:
	void append(QString string);
	QString back() const;
	void setLast(QString string);
	void removeLast();
	void removeAt(int index);
	int size() const;
};

#endif // UISTATE_H
