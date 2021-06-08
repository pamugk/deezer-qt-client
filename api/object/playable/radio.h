#ifndef RADIO_H
#define RADIO_H

#include <QString>

namespace api {
    /*!
     * \brief A radio object
     */
    class Radio
    {
        /*!
         * \brief The radio deezer ID
         */
        long id;
        /*!
         * \brief The radio title
         */
        QString title;
        /*!
         * \brief The radio description
         */
        QString description;
        /*!
         * \brief The share link of the radio on Deezer
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
        QString md5Image;

        /*!
         * \brief API Link to the tracklist of this radio
         */
        QString tracklist;

    public:
        Radio();
    };
}

#endif // RADIO_H
