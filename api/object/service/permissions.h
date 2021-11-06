#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <QString>

namespace api
{
    enum Permissions
    {
        BASIC_ACCESS,
        EMAIL,
        OFFLINE_ACCESS,
        MANAGE_LIBRARY,
        MANAGE_COMMUNITY,
        DELETE_LIBRARY,
        LISTENING_HISTORY
    };
}

#endif // PERMISSIONS_H
