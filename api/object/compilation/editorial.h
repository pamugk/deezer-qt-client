#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <QString>

namespace api {
    /*!
     * \brief An editorial object
     */
    class Editorial
    {
        /*!
         * \brief The editorial's Deezer id
         */
        long id;
        /*!
         * \brief The editorial's name
         */
        QString name;

        /*!
         * \brief The url of the editorial picture
         */
        QString picture;
        /*!
         * \brief The url of the editorial picture in size small
         */
        QString pictureSmall;
        /*!
         * \brief The url of the editorial picture in size medium
         */
        QString pictureMedium;
        /*!
         * \brief The url of the editorial picture in size big
         */
        QString pictureBig;
        /*!
         * \brief The url of the editorial picture in size xl
         */
        QString pictureXl;

    public:
        Editorial();
    };
}

#endif // EDITORIAL_H
