#include "playlist.h"

namespace api
{
    Playlist::Playlist():
        id(-1),
        title(QString()),

        description(QString()),
        duration(QTime()),
        public_(true),
        lovedTrack(false),
        collaborative(false),
        rating(-1),

        trackCount(-1),
        unseenTrackCount(-1),
        fanCount(-1),

        link(QString()),
        share(QString()),

        picture(QString()),
        pictureSmall(QString()),
        pictureMedium(QString()),
        pictureBig(QString()),
        pictureXl(QString()),

        checksum(QString()),
        creator(nullptr),
        tracks(QVector<Track>())
    {}
}
