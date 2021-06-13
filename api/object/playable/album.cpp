#include "album.h"

namespace api {
    Album::Album():
            id(-1),
            title(QString()),
            upc(QString()),

            link(QString()),
            share(QString()),

            cover(QString()),
            coverSmall(QString()),
            coverMedium(QString()),
            coverBig(QString()),
            coverXl(QString()),
            md5Image(QString()),

            genreId(-1),
            genres(QVector<Genre>()),

            trackCount(-1),
            duration(-1),
            fanCount(-1),
            rating(-1),
            releaseDate(QDate()),

            recordType(QString()),
            available(true),
            alternative(nullptr),

            tracklist(QString()),

            explicitLyrics(false),
            explicitContentLyrics(Explicity::NOT_EXPLICIT),
            explicitContentCover(Explicity::NOT_EXPLICIT),

            position(-1),
            contributors(QVector<Artist>()),
            artist(nullptr),
            tracks(QVector<Track>())
    {}

    Album::~Album()
    {
        if (alternative != nullptr)
        {
            delete alternative;
        }
        if (artist != nullptr)
        {
            delete artist;
        }
    }
}
