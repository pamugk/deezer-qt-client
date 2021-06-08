#ifndef ADVANCEDSEARCHQUERY_H
#define ADVANCEDSEARCHQUERY_H

#include <QString>

namespace api {
    struct AdvancedSearchQuery
    {
        QString artist;
        QString album;
        QString track;
        QString label;
        QString durMin;
        QString durMax;
        QString bpmMin;
        QString bpmMax;

        QString toString();
    };
}

#endif // ADVANCEDSEARCHQUERY_H
