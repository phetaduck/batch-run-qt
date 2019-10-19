#include "foldercontentmodel.h"
#include "foldercontentlist.h"
#include "settings.h"

FolderContentModel::FolderContentModel(QObject *parent)
    : QAbstractListModel(parent),
      mList(nullptr)
{
}

int FolderContentModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant FolderContentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const FolderContentItem item = mList->items().at(index.row());
    switch (role) {
		case SelectedRole:
				return QVariant(item.selected);
		case NameRole:
				return QVariant(item.name);
		case InProgressRole:
			return QVariant(item.inProgress);
		case IsFileRole:
			return QVariant(item.isFile);
    }
    return QVariant();
}

bool FolderContentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList) {
        return false;
    }

    FolderContentItem item = mList->items().at(index.row());
    switch (role) {
		case SelectedRole:
				item.selected = value.toBool();
        break;
		case NameRole:
				item.name = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags FolderContentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> FolderContentModel::roleNames() const
{
    QHash<int, QByteArray> names;
		names[SelectedRole] = "selected";
		names[NameRole] = "name";
		names[InProgressRole] = "inProgress";
		names[IsFileRole] = "isFile";
    return names;
}

FolderContentList *FolderContentModel::list() const
{
    return mList;
}

void FolderContentModel::setList(FolderContentList *list)
{
    beginResetModel();

    if (mList) {
        mList->disconnect(this);
    }

    mList = list;

    if (mList) {
        connect(mList, &FolderContentList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &FolderContentList::postItemAppended, this, [=]() {
            endInsertRows();
        });
        connect(mList, &FolderContentList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &FolderContentList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
				connect(mList, &FolderContentList::listReset, this, [=]() {
					reloadList();
				});
    }

		endResetModel();
}

void FolderContentModel::reloadList()
{
	setList(mList);
}
