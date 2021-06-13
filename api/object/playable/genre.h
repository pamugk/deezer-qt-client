#ifndef GENRE_H
#define GENRE_H

#include <QString>

namespace api {
    /*!
     * \brief A genre object
     */
    struct Genre
    {
        /*!
         * \brief The genre's Deezer id
         */
        int id;
        /*!
         * \brief The genre's name
         */
        QString name;

        /*!
         * \brief The url of the genre picture
         */
        QString picture;
        /*!
         * \brief The url of the genre picture in size small
         */
        QString pictureSmall;
        /*!
         * \brief The url of the genre picture in size medium
         */
        QString pictureMedium;
        /*!
         * \brief The url of the genre picture in size big
         */
        QString pictureBig;
        /*!
         * \brief The url of the genre picture in size xl
         */
        QString pictureXl;

        Genre();
    };
}

#endif // GENRE_H
