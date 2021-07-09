#include "playlistflow.h"

PlaylistFlow::PlaylistFlow(api::Deezer *apiInstance,
                           QWidget *parent, int margin, int hSpacing, int vSpacing) :
        Flow(parent, margin, hSpacing, vSpacing),
        apiInstance(apiInstance){}

QWidget *PlaylistFlow::instantiateItem(api::Playlist &obj)
{
    PlaylistCard *playlistCard = new PlaylistCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    connect(playlistCard, &PlaylistCard::clickedPlaylist, this, &PlaylistFlow::clickedItem);
    return playlistCard;
}
