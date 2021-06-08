#ifndef CHART_H
#define CHART_H

#include "../playable/album.h"
#include "../playable/artist.h"
#include "../playable/playlist.h"
#include "../playable/podcast.h"
#include "../playable/track.h"

#include <QVector>

namespace api {
    /*!
     * \brief Charts of a specified genre
     */
    class Chart
    {
        /*!
         * \brief List of track
         */
        QVector<Track> tracks;
        /*!
         * \brief List of album
         */
        QVector<Album> albums;
        /*!
         * \brief List of artist
         */
        QVector<Artist> artists;
        /*!
         * \brief List of playlist
         */
        QVector<Playlist> playlists;
        /*!
         * \brief List of podcast
         */
        QVector<Podcast> podcasts;

    public:
        Chart();
    };
}

#endif // CHART_H
