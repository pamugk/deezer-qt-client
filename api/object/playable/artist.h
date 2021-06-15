#ifndef ARTIST_H
#define ARTIST_H

#include <QString>

namespace api {
    /*!
     * \brief An artist object
     */
    struct Artist
    {
        /*!
         * \brief The artist's Deezer id
         */
        int id;
        /*!
         * \brief The artist's name
         */
        QString name;

        /*!
         * \brief The url of the artist on Deezer
         */
        QString link;
        /*!
         * \brief The share link of the artist on Deezer
         */
        QString share;

        /*!
         * \brief The url of the artist picture
         */
        QString picture;
        /*!
         * \brief The url of the artist picture in size small
         */
        QString pictureSmall;
        /*!
         * \brief The url of the artist picture in size medium
         */
        QString pictureMedium;
        /*!
         * \brief The url of the artist picture in size big
         */
        QString pictureBig;
        /*!
         * \brief The url of the artist picture in size xl
         */
        QString pictureXl;

        /*!
         * \brief The number of artist's albums
         */
        int albumCount;
        /*!
         * \brief The number of artist's fans
         */
        int fanCount;
        /*!
         * \brief If the artist has a smartradio
         */
        bool radio;
        /*!
         * \brief API Link to the top of this artist
         */
        QString tracklist;

        Artist();
        Artist (const Artist &) = default;
    };
}

#endif // ARTIST_H
