#include "albumflow.h"
#include "ui_albumflow.h"

AlbumFlow::AlbumFlow(api::Deezer *apiInstance, QWidget *parent) :
    QScrollArea(parent),
    lastContentIndex(0),
    apiInstance(apiInstance),
    ui(new Ui::AlbumFlow)
{
    ui->setupUi(this);
}

void AlbumFlow::addContents(QVector<api::Album> &data)
{
    for (int i = 0; i < data.size(); i++, lastContentIndex++)
    {
        AlbumCard *albumCard = new AlbumCard(apiInstance, data[i], ui->contents);
        connect(albumCard, &AlbumCard::clickedAlbum, this, &AlbumFlow::clickedItem);
        ui->contentsLayout->addWidget(albumCard, lastContentIndex / 4, lastContentIndex % 4);
    }
}

void AlbumFlow::clearAll()
{
    while (QLayoutItem * item = ui->contentsLayout->takeAt(0))
    {
        ui->contentsLayout->removeItem(item);
    }
    lastContentIndex = 0;
}

AlbumFlow::~AlbumFlow()
{
    delete ui;
}
