#ifndef PODCAST_H
#define PODCAST_H

#include <QString>

namespace api {
    /*!
     * \brief A podcast object
     */
    struct Podcast
    {
        /*!
         * \brief The podcast's Deezer id
         */
        int id;
        /*!
         * \brief The podcast's title
         */
        QString title;

        /*!
         * \brief The podcast's description
         */
        QString description;
        /*!
         * \brief If the podcast is available or not
         */
        bool available;
        /*!
         * \brief The playlist's rate
         */
        int rating;
        /*!
         * \brief The number of playlist's fans
         */
        int fanCount;

        /*!
         * \brief The url of the podcast on Deezer
         */
        QString link;
        /*!
         * \brief The share link of the podcast on Deezer
         */
        QString share;

        /*!
         * \brief The url of the podcast's cover
         */
        QString picture;
        /*!
         * \brief The url of the podcast's cover in size small
         */
        QString pictureSmall;
        /*!
         * \brief The url of the podcast's cover in size medium
         */
        QString pictureMedium;
        /*!
         * \brief The url of the podcast's cover in size big
         */
        QString pictureBig;
        /*!
         * \brief The url of the podcast's cover in size xl
         */
        QString pictureXl;

        /*!
         * \brief The position of the podcasts in the charts
         */
        int position;

        Podcast();
    };
}

#endif // PODCAST_H
