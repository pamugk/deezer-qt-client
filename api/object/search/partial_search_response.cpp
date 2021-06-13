#include "partial_search_response.h"

namespace api
{
    template<typename T>
    PartialSearchResponse<T>::PartialSearchResponse(
            QVector<T> data, int total,
            QString prev, QString next) :
        data(data), total(total), prev(prev), next(next)
    { }

    template<typename T>
    PartialSearchResponse<T>::~PartialSearchResponse()
    {
        delete[] data;
    }

    template<typename T>
    QVector<T> PartialSearchResponse<T>::getData() const
    {
        return data;
    }

    template<typename T>
    bool PartialSearchResponse<T>::hasPrev()
    {
        return prev.isEmpty();
    }

    template<typename T>
    bool PartialSearchResponse<T>::hasNext()
    {
        return next.isEmpty();
    }

    template<typename T>
    int PartialSearchResponse<T>::getTotal() const
    {
        return total;
    }

    template<typename T>
    QString PartialSearchResponse<T>::getPrev() const
    {
        return prev;
    }

    template<typename T>
    QString PartialSearchResponse<T>::getNext() const
    {
        return next;
    }
}
