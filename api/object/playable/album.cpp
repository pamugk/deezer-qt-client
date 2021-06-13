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

    void Album::setId(int newId)
    {
        id = newId;
    }

    const QString &Album::getTitle() const
    {
        return title;
    }

    void Album::setTitle(const QString &newTitle)
    {
        title = newTitle;
    }

    const QString &Album::getUpc() const
    {
        return upc;
    }

    void Album::setUpc(const QString &newUpc)
    {
        upc = newUpc;
    }

    const QString &Album::getLink() const
    {
        return link;
    }

    void Album::setLink(const QString &newLink)
    {
        link = newLink;
    }

    const QString &Album::getShare() const
    {
        return share;
    }

    void Album::setShare(const QString &newShare)
    {
        share = newShare;
    }

    const QString &Album::getCover() const
    {
        return cover;
    }

    void Album::setCover(const QString &newCover)
    {
        cover = newCover;
    }

    const QString &Album::getCoverSmall() const
    {
        return coverSmall;
    }

    void Album::setCoverSmall(const QString &newCoverSmall)
    {
        coverSmall = newCoverSmall;
    }

    const QString &Album::getCoverMedium() const
    {
        return coverMedium;
    }

    void Album::setCoverMedium(const QString &newCoverMedium)
    {
        coverMedium = newCoverMedium;
    }

    const QString &Album::getCoverBig() const
    {
        return coverBig;
    }

    void Album::setCoverBig(const QString &newCoverBig)
    {
        coverBig = newCoverBig;
    }

    const QString &Album::getCoverXl() const
    {
        return coverXl;
    }

    void Album::setCoverXl(const QString &newCoverXl)
    {
        coverXl = newCoverXl;
    }

    const QString &Album::getMd5Image() const
    {
        return md5Image;
    }

    void Album::setMd5Image(const QString &newMd5Image)
    {
        md5Image = newMd5Image;
    }

    int Album::getGenreId() const
    {
        return genreId;
    }

    void Album::setGenreId(int newGenreId)
    {
        genreId = newGenreId;
    }

    const QVector<Genre> &Album::getGenres() const
    {
        return genres;
    }

    void Album::setGenres(const QVector<Genre> &newGenres)
    {
        genres = newGenres;
    }

    int Album::getTrackCount() const
    {
        return trackCount;
    }

    void Album::setTrackCount(int newTrackCount)
    {
        trackCount = newTrackCount;
    }

    int Album::getDuration() const
    {
        return duration;
    }

    void Album::setDuration(int newDuration)
    {
        duration = newDuration;
    }

    int Album::getFanCount() const
    {
        return fanCount;
    }

    void Album::setFanCount(int newFanCount)
    {
        fanCount = newFanCount;
    }

    int Album::getRating() const
    {
        return rating;
    }

    void Album::setRating(int newRating)
    {
        rating = newRating;
    }

    const QDate &Album::getReleaseDate() const
    {
        return releaseDate;
    }

    void Album::setReleaseDate(const QDate &newReleaseDate)
    {
        releaseDate = newReleaseDate;
    }

    const QString &Album::getRecordType() const
    {
        return recordType;
    }

    void Album::setRecordType(const QString &newRecordType)
    {
        recordType = newRecordType;
    }

    bool Album::getAvailable() const
    {
        return available;
    }

    void Album::setAvailable(bool newAvailable)
    {
        available = newAvailable;
    }

    Album *Album::getAlternative() const
    {
        return alternative;
    }

    void Album::setAlternative(Album *newAlternative)
    {
        alternative = newAlternative;
    }

    const QString &Album::getTracklist() const
    {
        return tracklist;
    }

    void Album::setTracklist(const QString &newTracklist)
    {
        tracklist = newTracklist;
    }

    bool Album::getExplicitLyrics() const
    {
        return explicitLyrics;
    }

    void Album::setExplicitLyrics(bool newExplicitLyrics)
    {
        explicitLyrics = newExplicitLyrics;
    }

    Explicity Album::getExplicitContentLyrics() const
    {
        return explicitContentLyrics;
    }

    void Album::setExplicitContentLyrics(Explicity newExplicitContentLyrics)
    {
        explicitContentLyrics = newExplicitContentLyrics;
    }

    Explicity Album::getExplicitContentCover() const
    {
        return explicitContentCover;
    }

    void Album::setExplicitContentCover(Explicity newExplicitContentCover)
    {
        explicitContentCover = newExplicitContentCover;
    }

    int Album::getPosition() const
    {
        return position;
    }

    void Album::setPosition(int newPosition)
    {
        position = newPosition;
    }

    const QVector<Artist> &Album::getContributors() const
    {
        return contributors;
    }

    void Album::setContributors(const QVector<Artist> &newContributors)
    {
        contributors = newContributors;
    }

    Artist *Album::getArtist() const
    {
        return artist;
    }

    void Album::setArtist(Artist *newArtist)
    {
        artist = newArtist;
    }

    const QVector<Track> &Album::getTracks() const
    {
        return tracks;
    }

    void Album::setTracks(const QVector<Track> &newTracks)
    {
        tracks = newTracks;
    }

}
