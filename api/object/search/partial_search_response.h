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
        PartialSearchResponse(QVector<T> data, int total, QString prev, QString next);
        virtual ~PartialSearchResponse();

        bool hasPrev();
        bool hasNext();
        QVector<T> getData() const;
        int getTotal() const;
        QString getPrev() const;
        QString getNext() const;
    };
}

#endif // PARTIALSEARCHRESPONSE_H
