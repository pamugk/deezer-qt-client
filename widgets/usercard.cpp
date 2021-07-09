#include "usercard.h"
#include "ui_usercard.h"

UserCard::UserCard(api::Deezer *apiInstance, api::User &user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserCard)
{
    ui->setupUi(this);

    this->setToolTip(user.name);

    ui->nameLabel->setText(user.name);

    connect(ui->pictureButton, &QPushButton::clicked, [userId{ user.id }, this]{ emit clickedUser(userId); });

    if (!user.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(user.pictureMedium);
        pictureReply = apiInstance->getAnything(pictureUrl);
        connect(pictureReply, &QNetworkReply::errorOccurred, this, &UserCard::errorOccurred);
        connect(pictureReply, &QNetworkReply::finished, this, &UserCard::pictureLoaded);
    } else {
        pictureReply = nullptr;
    }
}

UserCard::~UserCard()
{
    if (pictureReply != nullptr && !pictureReply->isFinished())
    {
        QEventLoop loop;
        connect(pictureReply, &QNetworkReply::errorOccurred, &loop, &QEventLoop::quit);
        pictureReply->abort();
        loop.exec();
    }
    delete ui;
}

void UserCard::errorOccurred(QNetworkReply::NetworkError error)
{
    if (pictureReply != nullptr)
    {
        pictureReply->deleteLater();
        pictureReply = nullptr;
    }
}

void UserCard::pictureLoaded()
{
    if (pictureReply->error() == QNetworkReply::NetworkError::NoError)
    {
        auto imageBytes = pictureReply->readAll();
        auto cover = QPixmap(250, 250);
        cover.loadFromData(imageBytes);
        ui->pictureButton->setIcon(QIcon(cover));
    }
    pictureReply->deleteLater();
    pictureReply = nullptr;
}
