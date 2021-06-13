#include "podcast.h"

namespace api
{
    Podcast::Podcast():
        id(-1),
        title(QString()),

        description(QString()),
        available(true),
        rating(-1),
        fanCount(-1),

        link(QString()),
        share(QString()),

        picture(QString()),
        pictureSmall(QString()),
        pictureMedium(QString()),
        pictureBig(QString()),
        pictureXl(QString()),

        position(-1)
    { }
}
