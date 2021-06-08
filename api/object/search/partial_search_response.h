#ifndef PARTIALSEARCHRESPONSE_H
#define PARTIALSEARCHRESPONSE_H

#include <QString>
#include <QVector>

template<class T>
class PartialSearchResponse<T>
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

#endif // PARTIALSEARCHRESPONSE_H
