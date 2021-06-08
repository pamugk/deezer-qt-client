#ifndef INFOS_H
#define INFOS_H

#include "offer.h"

#include <QString>
#include <QVector>

namespace api {
    /*!
     * \brief Information about the API in the current country
     */
    class Infos
    {
        /*!
         * \brief The current country ISO code
         */
        QString countryIso;
        /*!
         * \brief The current country name
         */
        QString country;
        /*!
         * \brief Indicates if Deezer is open in the current country or not
         */
        bool open;
        /*!
         * \brief An array of available offers in the current country
         */
        QVector<Offer> offers;

    public:
        Infos();
    };
}

#endif // INFOS_H
