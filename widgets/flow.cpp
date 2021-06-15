#include "flow.h"
#include "ui_flow.h"

Flow::Flow(api::Deezer *apiInstance, QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::Flow)
{
    ui->setupUi(this);

    lastContentIndex = 0;

    this->apiInstance = apiInstance;
}

void Flow::addContents(QVector<api::Album> &data)
{
    for (int i = 0; i < data.size(); i++, lastContentIndex++)
    {
        AlbumCard *albumCard = new AlbumCard(apiInstance, data[i], ui->contents);
        connect(albumCard, &AlbumCard::clickedAlbum, this, &Flow::innerClickedItem);
        ui->contentsLayout->addWidget(albumCard, lastContentIndex / 4, lastContentIndex % 4);
    }
}

void Flow::clearAll()
{
    while (QLayoutItem * item = ui->contentsLayout->takeAt(0))
    {
        ui->contentsLayout->removeItem(item);
    }
    lastContentIndex = 0;
}

void Flow::innerClickedItem(int id)
{
    emit clickedItem(id);
}

Flow::~Flow()
{
    delete ui;
}
