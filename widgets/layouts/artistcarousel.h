#ifndef ARTISTCAROUSEL_H
#define ARTISTCAROUSEL_H

#include "carousel.h"

#include "../artistcard.h"
#include "../../api/deezer.h"

#include <QObject>

class ArtistCarousel: public CarouselLayout<api::Artist>
{
    //Q_OBJECT

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::Artist &obj) override;

public:
    ArtistCarousel(api::Deezer *apiInstance,
                   QWidget *parent = nullptr, int margin = -1, int hSpacing = -1);
};

#endif // ARTISTCAROUSEL_H
