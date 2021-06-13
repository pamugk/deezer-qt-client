#include "user.h"

namespace api
{
    User::User():
        id(-1),
        name(QString()),

        lastname(QString()),
        firstname(QString()),

        email(QString()),
        status(-1),
        birthday(QDate()),
        inscriptionDate(QDate()),
        gender(MALE),
        link(QString()),

        picture(QString()),
        pictureSmall(QString()),
        pictureMedium(QString()),
        pictureBig(QString()),
        pictureXl(QString()),

        country(QString()),
        lang(QString()),

        isKid(false),
        explicitContentLevel(EXPLICIT_DISPLAY),
        explicitContentLevelsAvailable(QVector<EContentExplicity>()),

        tracklist(QString())
    { }
}
