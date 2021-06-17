#include "playlistflow.h"
#include "ui_playlistflow.h"

PlaylistFlow::PlaylistFlow(api::Deezer *apiInstance, QWidget *parent) :
    QScrollArea(parent),
    apiInstance(apiInstance),
    lastContentIndex(0),
    ui(new Ui::PlaylistFlow)
{
    ui->setupUi(this);
}

void PlaylistFlow::addContents(QVector<api::Playlist> &data)
{
    for (int i = 0; i < data.size(); i++, lastContentIndex++)
    {
        PlaylistCard *playlistCard = new PlaylistCard(apiInstance, data[i], ui->contents);
        connect(playlistCard, &PlaylistCard::clickedPlaylist, this, &PlaylistFlow::innerClickedItem);
        ui->contentsLayout->addWidget(playlistCard, lastContentIndex / 4, lastContentIndex % 4);
    }
}

void PlaylistFlow::clearAll()
{
    while (QLayoutItem * item = ui->contentsLayout->takeAt(0))
    {
        ui->contentsLayout->removeItem(item);
    }
    lastContentIndex = 0;
}

void PlaylistFlow::innerClickedItem(int id)
{
    emit clickedItem(id);
}


PlaylistFlow::~PlaylistFlow()
{
    delete ui;
}
