#include "searchtracksmodel.h"

SearchTracksModel::SearchTracksModel(api::Deezer *apiInstance, QObject *parent)
    : QAbstractTableModel(parent),
      apiInstance(apiInstance)
{
    header.append("Трек");
    header.append("Исполнитель");
    header.append("Альбом");
    header.append("Длительность");
    header.append("Популярность");
}

QVariant SearchTracksModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int SearchTracksModel::rowCount(const QModelIndex &parent) const
{
    return items.size();
}

int SearchTracksModel::columnCount(const QModelIndex &parent) const
{
    return header.size();
}

bool SearchTracksModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}

bool SearchTracksModel::canFetchMore(const QModelIndex &parent) const
{
    return false;
}

void SearchTracksModel::fetchMore(const QModelIndex &parent)
{
}

QVariant getTrackColumnValue(api::Track &track, int column) {
    switch (column) {
        case 0: {
            return track.title;
        }
        case 1: {
            return track.artist.isNull() ? "" : track.artist->name;
        }
        case 2: {
            return track.album.isNull() ? "" : track.album->title;
        }
        case 3: {
            return track.duration.hour() > 0 ? track.duration.toString(Qt::TextDate) : track.duration.toString("mm:ss");
        }
        case 4: {
            return track.rank;
        }
    }
    return QVariant();
}

QVariant SearchTracksModel::data(const QModelIndex &index, int role) const
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

void SearchTracksModel::addData(api::Track data) {
    items.append(data);

    emit layoutChanged();
}

void SearchTracksModel::addData(QVector<api::Track> &data)
{
    for (api::Track item: qAsConst(data))
    {
        items.append(item);
    }

    emit layoutChanged();
}

void SearchTracksModel::clearAll()
{
    items.clear();
}
