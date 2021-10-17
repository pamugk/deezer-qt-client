#ifndef PLAYLISTFLOW_H
#define PLAYLISTFLOW_H

#include "flow.h"
#include "../playlistcard.h"

class PlaylistFlow : public Flow<api::Playlist>
{
    Q_OBJECT

public:
    explicit PlaylistFlow(api::Deezer *apiInstance,
                          QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);

signals:
    void clickedItem(long id);

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::Playlist &item) override;
};

#endif // PLAYLISTFLOW_H
