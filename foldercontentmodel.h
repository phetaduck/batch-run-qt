#ifndef FOLDERCONTENTMODEL_H
#define FOLDERCONTENTMODEL_H

#include <QAbstractListModel>

class FolderContentList;

class FolderContentModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(FolderContentList *list READ list WRITE setList)

public:
	explicit FolderContentModel(QObject *parent = nullptr);

	enum {
		SelectedRole = Qt::UserRole,
		NameRole,
		InProgressRole,
		IsFileRole,
	};

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
							 int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	virtual QHash<int, QByteArray> roleNames() const override;

	FolderContentList *list() const;
	void setList(FolderContentList *list);

public slots:
	void reloadList();

private:
	FolderContentList* mList;
};

#endif // FOLDERCONTENTMODEL_H
