#include "artistflow.h"
#include "ui_artistflow.h"

ArtistFlow::ArtistFlow(api::Deezer *apiInstance, QWidget *parent) :
    QScrollArea(parent),
    apiInstance(apiInstance),
    lastContentIndex(0),
    ui(new Ui::ArtistFlow)
{
    ui->setupUi(this);
}

void ArtistFlow::addContents(QVector<api::Artist> &data)
{
    for (int i = 0; i < data.size(); i++, lastContentIndex++)
    {
        ArtistCard *artistCard = new ArtistCard(apiInstance, data[i], ui->contents);
        connect(artistCard, &ArtistCard::clickedArtist, this, &ArtistFlow::clickedItem);
        ui->contentsLayout->addWidget(artistCard, lastContentIndex / 4, lastContentIndex % 4);
    }
}

void ArtistFlow::clearAll()
{
    while (QLayoutItem * item = ui->contentsLayout->takeAt(0))
    {
        ui->contentsLayout->removeItem(item);
    }
    lastContentIndex = 0;
}

ArtistFlow::~ArtistFlow()
{
    delete ui;
}
