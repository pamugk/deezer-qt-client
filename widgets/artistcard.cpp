#include "artistcard.h"
#include "ui_artistcard.h"

ArtistCard::ArtistCard(api::Deezer *apiInstance, api::Artist &artist, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArtistCard)
{
    ui->setupUi(this);

    this->setToolTip(artist.name);

    ui->nameLabel->setText(artist.name);

    if (artist.fanCount == -1)
    {
        ui->fansLabel->hide();
    } else {
        ui->fansLabel->setText(ui->fansLabel->text().arg(QString::number(artist.fanCount)));
    }

    connect(ui->pictureButton, &QPushButton::clicked, [artistId{ artist.id }, this]{ emit clickedArtist(artistId); });

    if (!artist.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(artist.pictureMedium);
        pictureReply = apiInstance->getAnything(pictureUrl);
        connect(pictureReply, &QNetworkReply::errorOccurred, this, &ArtistCard::errorOccurred);
        connect(pictureReply, &QNetworkReply::finished, this, &ArtistCard::pictureLoaded);
    } else {
        pictureReply = nullptr;
    }
}

ArtistCard::~ArtistCard()
{
    if (pictureReply != nullptr && !pictureReply->isFinished())
    {
        qDebug() << "Aborting";
        QEventLoop loop;
        connect(pictureReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        pictureReply->abort();
        loop.exec();
    }
    delete ui;
}

void ArtistCard::errorOccurred(QNetworkReply::NetworkError error)
{
    if (pictureReply != nullptr)
    {
        pictureReply->deleteLater();
        pictureReply = nullptr;
    }
}

void ArtistCard::pictureLoaded()
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
