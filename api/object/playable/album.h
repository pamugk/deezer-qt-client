#ifndef ALBUM_H
#define ALBUM_H

#include "artist.h"
#include "genre.h"
#include "shared.h"
#include "track.h"

#include <QDate>
#include <QSharedPointer>
#include <QString>
#include <QTime>
#include <QVector>

namespace api {
    /*!
     * An album object
     */
    struct Album
    {
        /*!
         * \brief The Deezer album id
         */
        long id;
        /*!
         * \brief The album title
         */
        QString title;
        /*!
         * \brief The album UPC
         */
        QString upc;

        /*!
          * \brief The url of the album on Deezer
          */
        QString link;
        /*!
         * \brief The share link of the album on Deezer
         */
        QString share;

        /*!
         * \brief The url of the album's cover
         */
        QString cover;
        /*!
         * \brief The url of the album's cover in size small
         */
        QString coverSmall;
        /*!
         * \brief The url of the album's cover in size medium
         */
        QString coverMedium;
        /*!
         * \brief The url of the album's cover in size big
         */
        QString coverBig;
        /*!
         * \brief The url of the album's cover in size xl
         */
        QString coverXl;
        QString md5Image;

        /*!
         * \brief The album's first genre id (You should use the genre list instead).
         * NB : -1 for not found
         */
        int genreId;
        /*!
         * \brief List of genre object
         */
        QVector<Genre> genres;

        /*!
         * \brief The album's label name
         */
        int trackCount;
        /*!
         * \brief The album's duration (seconds)
         */
        QTime duration;
        /*!
         * \brief The number of album's Fans
         */
        int fanCount;
        /*!
          * \brief The album's rate
          */
        int rating;
        /*!
          * \brief The album's release date
          */
        QDate releaseDate;

        /*!
          * The record type of the album (EP / ALBUM / etc..)
          */
        QString recordType;
        /*!
         * \brief available
         */
        bool available;
        /*!
          * \brief Return an alternative album object if the current album is not available
          */
        QSharedPointer<Album> alternative;

        /*!
         * \brief API Link to the tracklist of this album
         */
        QString tracklist;

        /*!
         * \brief explicitLyrics
         */
        bool explicitLyrics;
        /*!
         * \brief The explicit content lyrics values
         */
        Explicity explicitContentLyrics;
        /*!
         * \brief The explicit cover values
         */
        Explicity explicitContentCover;

        /*!
         * \brief The position of the album in the charts
         */
        int position;
        /*!
         * \brief Return a list of contributors on the album
         */
        QVector<Artist> contributors;
        /*!
         * \brief Artist object
         */
        QSharedPointer<Artist> artist;
        /*!
         * \brief List of track
         */
        QVector<Track> tracks;

        Album();
        Album (const Album &) = default;
    };
}

#endif // ALBUM_H
