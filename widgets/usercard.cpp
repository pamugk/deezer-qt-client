#include "usercard.h"
#include "ui_usercard.h"

UserCard::UserCard(api::Deezer *apiInstance, api::User &user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserCard)
{
    ui->setupUi(this);

    ui->nameLabel->setText(user.name);

    connect(ui->pictureButton, &QPushButton::clicked, [userId{ user.id }, this]{ emit clickedUser(userId); });

    if (!user.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(user.pictureMedium);
        QNetworkReply *coverReply = apiInstance->getAnything(pictureUrl);
        connect(coverReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
        {
            coverReply->deleteLater();
        });
        connect(coverReply, &QNetworkReply::finished, [=]
        {
            if (coverReply->error() == QNetworkReply::NetworkError::NoError)
            {
                auto imageBytes = coverReply->readAll();
                auto cover = QPixmap(250, 250);
                cover.loadFromData(imageBytes);
                ui->pictureButton->setIcon(QIcon(cover));
                coverReply->deleteLater();
            }
        });
    }
}

UserCard::~UserCard()
{
    delete ui;
}
