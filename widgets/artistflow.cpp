#include "artistflow.h"

ArtistFlow::ArtistFlow(api::Deezer *apiInstance,
                       QWidget *parent, int margin, int hSpacing, int vSpacing) :
    Flow(parent, margin, hSpacing, vSpacing),
    apiInstance(apiInstance){}

QWidget *ArtistFlow::instantiateItem(api::Artist &obj)
{
    ArtistCard *artistCard = new ArtistCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    connect(artistCard, &ArtistCard::clickedArtist, this, &ArtistFlow::clickedItem);
    return artistCard;
}
