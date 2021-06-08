#ifndef USER_H
#define USER_H

#include <QDate>
#include <QString>
#include <QVector>

namespace api {
    enum EContentExplicity {
        EXPLICIT_DISPLAY,
        EXPLICIT_NO_RECCOMMENDATION,
        EXPLICIT_HIDE
    };

    enum EGender {
        MALE,
        FEMALE
    };

    /*!
     * \brief A user object
     */
    class User
    {
        /*!
         * \brief The user's Deezer ID
         */
        long id;
        /*!
         * \brief The user's Deezer nickname
         */
        QString name;

        /*!
         * \brief The user's last name
         */
        QString lastname;
        /*!
         * \brief The user's first name
         */
        QString firstname;

        /*!
         * \brief The user's email
         */
        QString email;
        /*!
         * \brief The user's status
         */
        int status;
        /*!
         * \brief The user's birthday
         */
        QDate birthday;
        /*!
         * \brief The user's inscription date
         */
        QDate inscriptionDate;
        /*!
         * \brief The user's gender
         */
        EGender gender;
        /*!
         * \brief The url of the profile for the user on Deezer
         */
        QString link;

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
         * \brief The user's country
         */
        QString country;
        /*!
         * \brief The user's language
         */
        QString lang;

        /*!
         * \brief If the user is a kid or not
         */
        bool isKid;
        /*!
         * \brief The user's explicit content level according to his country
         */
        EContentExplicity explicitContentLevel;
        /*!
         * \brief The user's available explicit content levels according to his country
         */
        QVector<EContentExplicity> explicitContentLevelsAvailable;

        /*!
         * \brief API Link to the flow of this user
         */
        QString tracklist;

    public:
        User();
    };
}

#endif // USER_H
