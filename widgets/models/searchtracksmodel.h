#ifndef SEARCHTRACKSMODEL_H
#define SEARCHTRACKSMODEL_H

#include "../../api/deezer.h"

#include <QAbstractTableModel>

class SearchTracksModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SearchTracksModel(api::Deezer *apiInstance, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addData(api::Track data);
    void addData(QVector<api::Track> &data);
    void clearAll();

private:
    api::Deezer *apiInstance;
    QVector<QString> header;
    QVector<api::Track> items;
};

#endif // SEARCHTRACKSMODEL_H
