#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "../object/search/shared.h"
#include "../object/service/permissions.h"

#include <QString>
#include <QTime>

namespace api
{
    QTime deserializeTime(int totalSeconds);
    QString serialize(SearchOrder);
    QString serialize(Permissions permission);
}

#endif // SERIALIZATION_H
