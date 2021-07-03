#include "albumtracksmodel.h"

AlbumTracksModel::AlbumTracksModel(QVector<api::Track> data, QObject *parent)
    : QAbstractTableModel(parent),
    items(data)
{
    header.append("#");
    header.append("Трек");
    header.append("Длительность");
    header.append("Популярность");
}

QVariant AlbumTracksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Orientation::Horizontal) {
        switch (role) {
            case Qt::DisplayRole: {
                return header.at(section);
            }
        }
    }
    return QVariant();
}

int AlbumTracksModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? items.size(): 0;
}

int AlbumTracksModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? header.size(): 0;
}

QVariant getTrackColumnValue(api::Track &track, int column) {
    switch (column) {
        case 0: {
            return track.trackPosition;
        }
        case 1: {
            return track.title;
        }
        case 2: {
            return track.duration.hour() > 0 ? track.duration.toString(Qt::TextDate) : track.duration.toString("mm:ss");
        }
        case 3: {
            return track.rank;
        }
    }
    return QVariant();
}

QVariant AlbumTracksModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = items.at(index.row());
    switch (role) {
        case Qt::DisplayRole: {
            return getTrackColumnValue(item, index.column());
        }
    }

    return QVariant();
}
