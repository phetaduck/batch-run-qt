#include "foldercontentlist.h"
#include "settings.h"


FolderContentList::FolderContentList(QObject *parent) : QObject(parent)
{
	resetList();
}

void FolderContentList::resetList()
{
	mItems.clear();
	if (filterEnabled_) {
		for (const auto& d : Settings::workingDirFilteredFiles(filter_)) {
			mItems.append({true, d, false, true});
		}
	} else {
		for (const auto& d : Settings::workingDirFiles()) {
			mItems.append({false, d, false, true});
		}
	}
	for (const auto& d : Settings::workingDirSubDirs()) {
		mItems.append({false, d, false, false});
	}
}

QVector<FolderContentItem> FolderContentList::items() const
{
	return mItems;
}

bool FolderContentList::setItemAt(int index, const FolderContentItem &item)
{
	if (index < 0 || index >= mItems.size())
		return false;

	const FolderContentItem& oldItem = mItems.at(index);
	if (item == oldItem)
		return false;

	mItems[index] = item;
	return true;
}

void FolderContentList::appendItem()
{
	emit preItemAppended();

	FolderContentItem item;
	item.selected = false;
	mItems.append(item);

	emit postItemAppended();
}

void FolderContentList::removeCompletedItems()
{
	for (int i = 0; i < mItems.size(); ) {
		if (mItems.at(i).selected) {
			emit preItemRemoved(i);

			mItems.removeAt(i);

			emit postItemRemoved();
		} else {
			++i;
		}
	}
}

void FolderContentList::setWorkingDir(const QString& string)
{
	Settings::changeWorkingDir(string);
	resetList();
	emit listReset();
}

void FolderContentList::filterChanged(QStringList filter)
{
	if (filter_ != filter) {
		filter_ = std::move(filter);
		resetList();
		emit listReset();
	}
}

void FolderContentList::filteringEnabled(bool enabled)
{
	if (filterEnabled_ != enabled) {
		this->filterEnabled_ = enabled;
		resetList();
		emit listReset();
	}
}
