#include "radioflow.h"
#include "ui_radioflow.h"

RadioFlow::RadioFlow(api::Deezer *apiInstance, QWidget *parent) :
    QScrollArea(parent),
    apiInstance(apiInstance),
    lastContentIndex(0),
    ui(new Ui::RadioFlow)
{
    ui->setupUi(this);
}

void RadioFlow::addContents(QVector<api::Radio> &data)
{
    for (int i = 0; i < data.size(); i++, lastContentIndex++)
    {
        auto radioCard = new RadioCard(apiInstance, data[i], ui->contents);
        connect(radioCard, &RadioCard::clickedRadio, this, &RadioFlow::clickedItem);
        ui->contentsLayout->addWidget(radioCard, lastContentIndex / 4, lastContentIndex % 4);
    }
}

void RadioFlow::clearAll()
{
    while (QLayoutItem * item = ui->contentsLayout->takeAt(0))
    {
        ui->contentsLayout->removeItem(item);
    }
    lastContentIndex = 0;
}

RadioFlow::~RadioFlow()
{
    delete ui;
}
