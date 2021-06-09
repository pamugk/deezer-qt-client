#ifndef PARTIALSEARCHRESPONSE_H
#define PARTIALSEARCHRESPONSE_H

#include <QString>
#include <QVector>

namespace api {
    template<typename T>
    class PartialSearchResponse
    {
        QVector<T> data;
        int total;
        QString prev;
        QString next;

    public:
        PartialSearchResponse();

        bool hasPrev();
        bool hasNext();
    };
}

#endif // PARTIALSEARCHRESPONSE_H
