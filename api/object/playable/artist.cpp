#include "artist.h"

namespace api
{
    Artist::Artist():
        id(-1),
        name(QString()),

        link(QString()),
        share(QString()),

        picture(QString()),
        pictureSmall(QString()),
        pictureMedium(QString()),
        pictureBig(QString()),
        pictureXl(QString()),

        albumCount(-1),
        fanCount(-1),
        radio(false),
        tracklist(QString())
    { }
}
