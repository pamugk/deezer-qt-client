#ifndef ALBUMTRACKSMODEL_H
#define ALBUMTRACKSMODEL_H

#include "../api/object/playable/track.h"

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

class AlbumTracksModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AlbumTracksModel(QVector<api::Track> data, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QVector<QString> header;
    QVector<api::Track> items;
};

#endif // ALBUMTRACKSMODEL_H
