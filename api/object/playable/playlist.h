#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "track.h"
#include "../user/user.h"

#include <QString>
#include <QVector>

namespace api {
    /*!
     * \brief A playlist object
     */
    struct Playlist
    {
        /*!
         * \brief The playlist's Deezer id
         */
        int id;
        /*!
         * \brief The playlist's title
         */
        QString title;

        /*!
         * \brief The playlist description
         */
        QString description;
        /*!
         * \brief The playlist's duration (seconds)
         */
        int duration;
        /*!
         * \brief If the playlist is public or not
         */
        bool public_;
        /*!
         * \brief  If the playlist is the love tracks playlist
         */
        bool lovedTrack;
        /*!
         * \brief If the playlist is collaborative or not
         */
        bool collaborative;
        /*!
         * \brief The playlist's rate
         */
        int rating;

        /*!
         * \brief Count of tracks in the playlist
         */
        int trackCount;
        /*!
         * \brief Count of tracks that are not seen
         */
        int unseenTrackCount;
        /*!
         * \brief The number of playlist's fans
         */
        int fanCount;

        /*!
         * \brief The url of the playlist on Deezer
         */
        QString link;
        /*!
         * \brief The share link of the playlist on Deezer
         */
        QString share;

        /*!
         * \brief The url of the playlist's cover
         */
        QString picture;
        /*!
         * \brief The url of the playlist's cover in size small
         */
        QString pictureSmall;
        /*!
         * \brief The url of the playlist's cover in size medium
         */
        QString pictureMedium;
        /*!
         * \brief The url of the playlist's cover in size big
         */
        QString pictureBig;
        /*!
         * \brief The url of the playlist's cover in size xl
         */
        QString pictureXl;

        /*!
         * \brief The checksum for the track list
         */
        QString checksum;
        /*!
         * \brief User object containing : id, name
         */
        User* creator;
        /*!
         * \brief List of track
         */
        QVector<Track> tracks;

        Playlist();
        ~Playlist();
    };
}

#endif // PLAYLIST_H
