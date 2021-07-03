#ifndef TRACK_H
#define TRACK_H

#include "artist.h"
#include "shared.h"

#include <QDate>
#include <QSharedPointer>
#include <QString>
#include <QTime>
#include <QVector>

namespace api {
    class Album;

    /*!
     * \brief A track object
     */
    struct Track
    {
        /*!
         * \brief The track's Deezer id
         */
        int id;
        /*!
         * \brief If the track is readable in the player for the current user
         */
        bool readable;

        /*!
         * \brief The track's fulltitle
         */
        QString title;
        /*!
         * \brief The track's short title
         */
        QString titleShort;
        /*!
         * \brief The track version
         */
        QString titleVersion;

        /*!
         * \brief The track unseen status
         */
        bool unseen;
        /*!
         * \brief The track isrc
         */
        QString isrc;

        /*!
         * \brief The url of the track on Deezer
         */
        QString link;
        /*!
         * \brief The share link of the track on Deezer
         */
        QString share;

        /*!
         * \brief The track's duration in seconds
         */
        QTime duration;
        /*!
         * \brief The position of the track in its album
         */
        int trackPosition;
        /*!
         * \brief The track's album's disk number
         */
        int diskNumber;
        /*!
         * \brief The track's Deezer rank
         */
        int rank;
        /*!
         * \brief The track's release date
         */
        QDate releaseDate;

        /*!
         * \brief Whether the track contains explicit lyrics
         */
        bool explicitLyrics;
        /*!
         * \brief The explicit content lyrics
         */
        Explicity explicitContentLyrics;
        /*!
         * \brief The explicit cover value
         */
        Explicity explicitContentCover;

        /*!
         * \brief The url of track's preview file.
         * This file contains the first 30 seconds of the track
         */
        QString preview;
        /*!
         * \brief Beats per minute
         */
        float bpm;
        /*!
         * \brief Signal strength
         */
        float gain;
        /*!
         * \brief List of countries where the track is available
         */
        QVector<QString> availableCountries;
        /*!
         * \brief Return an alternative readable track if the current track is not readable
         */
        QSharedPointer<Track> alternative;

        /*!
         * \brief Artist object
         */
        QSharedPointer<Artist> artist;
        /*!
         * \brief Album object
         */
        QSharedPointer<Album> album;

        Track();
        Track (const Track &) = default;
    };
}

#endif // TRACK_H
