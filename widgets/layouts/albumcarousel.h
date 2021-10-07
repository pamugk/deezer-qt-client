#ifndef ALBUMCAROUSELLAYOUT_H
#define ALBUMCAROUSELLAYOUT_H

#include "carousel.h"
#include "../albumcard.h"
#include "../../api/deezer.h"

class AlbumCarousel: public CarouselLayout<api::Album>
{
    //Q_OBJECT

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::Album &obj) override;

public:
    AlbumCarousel(api::Deezer *apiInstance,
                  QWidget *parent = nullptr, int margin = -1, int hSpacing = -1);

/*signals:
    void clickedItem(int id);*/

};

#endif // ALBUMCAROUSELLAYOUT_H
