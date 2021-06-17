#include "artistcard.h"
#include "ui_artistcard.h"

ArtistCard::ArtistCard(api::Deezer *apiInstance, api::Artist &artist, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArtistCard)
{
    ui->setupUi(this);

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

ArtistCard::~ArtistCard()
{
    delete ui;
}
