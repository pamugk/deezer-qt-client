#include "radiocard.h"
#include "ui_radiocard.h"

RadioCard::RadioCard(api::Deezer *apiInstance, api::Radio &radio, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioCard)
{
    ui->setupUi(this);

    this->setToolTip(radio.title);

    connect(ui->pictureButton, &QPushButton::clicked, [radioId{ radio.id }, this]{ emit clickedRadio(radioId); });

    if (!radio.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(radio.pictureMedium);
        pictureReply = apiInstance->getAnything(pictureUrl);
        connect(pictureReply, &QNetworkReply::errorOccurred, this, &RadioCard::errorOccurred);
        connect(pictureReply, &QNetworkReply::finished, this, &RadioCard::pictureLoaded);
    } else {
        pictureReply = nullptr;
    }
}

RadioCard::~RadioCard()
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

void RadioCard::errorOccurred(QNetworkReply::NetworkError error)
{
    if (pictureReply != nullptr)
    {
        pictureReply->deleteLater();
        pictureReply = nullptr;
    }
}

void RadioCard::pictureLoaded()
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
