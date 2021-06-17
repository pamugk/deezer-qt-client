#include "userflow.h"
#include "ui_userflow.h"

UserFlow::UserFlow(api::Deezer *apiInstance, QWidget *parent) :
    QScrollArea(parent),
    apiInstance(apiInstance),
    lastContentIndex(0),
    ui(new Ui::UserFlow)
{
    ui->setupUi(this);
}

void UserFlow::addContents(QVector<api::User> &data)
{
    for (int i = 0; i < data.size(); i++, lastContentIndex++)
    {
        UserCard *artistCard = new UserCard(apiInstance, data[i], ui->contents);
        connect(artistCard, &UserCard::clickedUser, this, &UserFlow::innerClickedItem);
        ui->contentsLayout->addWidget(artistCard, lastContentIndex / 4, lastContentIndex % 4);
    }
}

void UserFlow::clearAll()
{
    while (QLayoutItem * item = ui->contentsLayout->takeAt(0))
    {
        ui->contentsLayout->removeItem(item);
    }
    lastContentIndex = 0;
}

void UserFlow::innerClickedItem(int id)
{
    emit clickedItem(id);
}


UserFlow::~UserFlow()
{
    delete ui;
}
