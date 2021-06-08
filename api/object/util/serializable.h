#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

namespace api {
class Serializable {
    public:
        virtual void deserialize(QJsonObject) = 0;
        virtual QJsonObject serialize() = 0;
    };
}

#endif // SERIALIZABLE_H
