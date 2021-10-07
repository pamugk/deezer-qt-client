#include "artistcarousel.h"

ArtistCarousel::ArtistCarousel(api::Deezer *apiInstance,
                             QWidget *parent, int margin, int hSpacing):
    CarouselLayout<api::Artist>(parent, margin, hSpacing),
    apiInstance(apiInstance){}

QWidget *ArtistCarousel::instantiateItem(api::Artist &obj)
{
   auto albumCard = new ArtistCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    //connect(albumCard, &AlbumCard::clickedAlbum, this, &AlbumCarousel::clickedItem);
    return albumCard;
}
