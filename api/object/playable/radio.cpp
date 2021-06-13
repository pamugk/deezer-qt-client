#include "radio.h"

namespace api
{
    Radio::Radio():
        id(-1),
        title(QString()),
        description(QString()),
        share(QString()),

        picture(QString()),
        pictureSmall(QString()),
        pictureMedium(QString()),
        pictureBig(QString()),
        pictureXl(QString()),
        md5Image(QString()),

        tracklist(QString())
    {}
}
