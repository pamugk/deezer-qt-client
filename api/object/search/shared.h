#ifndef SHARED_SEARCH_H
#define SHARED_SEARCH_H

namespace api {
    enum SearchOrder {
        RANKING,
        TRACK_ASC,
        TRACK_DESC,
        ARTIST_ASC,
        ARTIST_DESC,
        ALBUM_ASC,
        ALBUM_DESC,
        RATING_ASC,
        RATING_DESC,
        DURATION_ASC,
        DURATION_DESC,
        NONE
    };
}

#endif // SHARED_SEARCH_H
