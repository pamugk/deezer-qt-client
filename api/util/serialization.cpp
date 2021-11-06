#include "serialization.h"

namespace api
{
    QTime deserializeTime(int totalSeconds) {
        int hours = totalSeconds / 3600;
        const int hourPart = totalSeconds % 3600;
        int minutes = hourPart / 60;
        int seconds = hourPart % 60;
        return QTime(hours, minutes, seconds);
    }

    QString serialize(Permissions permission)
    {
        switch (permission)
        {
        case api::BASIC_ACCESS:
            return "basic_access";
        case api::EMAIL:
            return "email";
        case api::OFFLINE_ACCESS:
            return "offline_access";
        case api::MANAGE_LIBRARY:
            return "manage_library";
        case api::MANAGE_COMMUNITY:
            return "manage_community";
        case api::DELETE_LIBRARY:
            return "delete_library";
        case api::LISTENING_HISTORY:
            return "listening_history";
        }
        return "";
    }

    QString serialize(SearchOrder order)
    {
        switch (order) {
        case NONE:
            break;
        case RANKING:
            return "RANKING";
        case TRACK_ASC:
            return "TRACK_ASC";
        case TRACK_DESC:
            return "TRACK_DESC";
        case ARTIST_ASC:
            return "ARTIST_ASC";
        case ARTIST_DESC:
            return "ARTIST_DESC";
        case ALBUM_ASC:
            return "ALBUM_ASC";
        case ALBUM_DESC:
            return "ALBUM_DESC";
        case RATING_ASC:
            return "RATING_ASC";
        case RATING_DESC:
            return "RATING_DESC";
        case DURATION_ASC:
            return "DURATION_ASC";
        case DURATION_DESC:
            return "DURATION_DESC";
        }
        return QString();
    }
}
