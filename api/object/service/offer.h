#ifndef OFFER_H
#define OFFER_H

#include <QString>

namespace api {
    class Offer
    {
        long id;
        QString name;
        float amount;
        QString currency;
        QString displayedAmount;
        QString tc;
        QString tcHtml;
        QString tcTxt;
        int tryAndBy;

    public:
        Offer();
    };
}

#endif // OFFER_H
