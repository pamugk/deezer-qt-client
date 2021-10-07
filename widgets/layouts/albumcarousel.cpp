#include "albumcarousel.h"

AlbumCarousel::AlbumCarousel(api::Deezer *apiInstance,
                             QWidget *parent, int margin, int hSpacing):
    CarouselLayout<api::Album>(parent, margin, hSpacing),
    apiInstance(apiInstance){}

QWidget *AlbumCarousel::instantiateItem(api::Album &obj)
{
    auto albumCard = new AlbumCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    //connect(albumCard, &AlbumCard::clickedAlbum, this, &AlbumCarousel::clickedItem);
    return albumCard;
}
