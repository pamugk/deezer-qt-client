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
        PartialSearchResponse(QVector<T> data, int total, QString prev, QString next) :
            data(data), total(total), prev(prev), next(next)
        { }

        bool hasPrev()
        {
            return prev.isEmpty();
        }

        bool hasNext()
        {
            return next.isEmpty();
        }

        QVector<T> &getData()
        {
            return data;
        }

        int getTotal() const
        {
            return total;
        }

        QString getPrev() const
        {
            return prev;
        }

        QString getNext() const
        {
            return next;
        }
    };
}

#endif // PARTIALSEARCHRESPONSE_H
