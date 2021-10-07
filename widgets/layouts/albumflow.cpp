#include "albumflow.h"

AlbumFlow::AlbumFlow(api::Deezer *apiInstance,
                     QWidget *parent, int margin, int hSpacing, int vSpacing) :
    Flow(parent, margin, hSpacing, vSpacing),
    apiInstance(apiInstance){}

QWidget *AlbumFlow::instantiateItem(api::Album &obj)
{
    AlbumCard *albumCard = new AlbumCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    connect(albumCard, &AlbumCard::clickedAlbum, this, &AlbumFlow::clickedItem);
    return albumCard;
}
