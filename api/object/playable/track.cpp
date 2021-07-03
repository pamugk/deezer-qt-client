#include "track.h"

namespace api
{
    Track::Track():
        id(-1),
        readable(true),

        title(QString()),
        titleShort(QString()),
        titleVersion(QString()),

        unseen(false),
        isrc(QString()),

        link(QString()),
        share(QString()),

        duration(QTime()),
        trackPosition(-1),
        diskNumber(-1),
        rank(-1),
        releaseDate(QDate()),

        explicitLyrics(false),
        explicitContentLyrics(NOT_EXPLICIT),
        explicitContentCover(NOT_EXPLICIT),

        preview(QString()),
        bpm(-1),
        gain(-1),
        availableCountries(QVector<QString>()),
        alternative(nullptr),

        artist(nullptr),
        album(nullptr)
    { }
}
