#ifndef FOLDERCONTENTLIST_H
#define FOLDERCONTENTLIST_H

#include <QObject>
#include <QVector>

#include "settings.h"

struct FolderContentItem {
	bool selected;
	QString name;
	bool inProgress;
	bool isFile;
	bool operator==(const FolderContentItem& rhs) const {
		return selected == rhs.selected &&
				name == rhs.name &&
				isFile == rhs.isFile;
	}
};

class FolderContentList : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString workingDir READ workingDir WRITE setWorkingDir NOTIFY workingDirChanged)
public:
	explicit FolderContentList(QObject *parent = nullptr);

	QVector<FolderContentItem> items() const;

	bool setItemAt(int index, const FolderContentItem& item);

	void resetList();
	QString workingDir() const;
	void setWorkingDir(QString string);

signals:
	void preItemAppended();
	void postItemAppended();

	void preItemRemoved(int index);
	void postItemRemoved();

	void listReset();

	void workingDirChanged(QString workingDir);

public slots:
	void appendItem();
	void removeCompletedItems();
	void filterChanged(QStringList filter);
	void filteringEnabled(bool enabled);
private:
	QVector<FolderContentItem> mItems;
	bool filterEnabled_ = true;
	QStringList filter_ = Settings::defaultFileFilter();
};

#endif // FOLDERCONTENTLIST_H
