#include "albumcard.h"
#include "ui_albumcard.h"

AlbumCard::AlbumCard(api::Deezer apiInstance, api::Album &album, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumCard)
{
    ui->setupUi(this);

    ui->titleLabel->setText(album.title);

    if (album.artist != nullptr)
    {
        ui->artistLabel->setText(ui->artistLabel->text().arg(album.artist->name));
    } else {
        ui->artistLabel->hide();
    }

    if (!album.explicitLyrics)
    {
        ui->explicityLabel->hide();
    }

    connect(ui->coverButton, &QPushButton::clicked, [albumId{ album.id }, this]{ emit clickedAlbum(albumId); });

    if (!album.coverMedium.isEmpty())
    {
        QUrl coverUrl(album.coverMedium);
        QNetworkReply *coverReply = apiInstance.getAnything(coverUrl);
        connect(coverReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error) { coverReply->deleteLater(); });
        connect(coverReply, &QNetworkReply::finished, [=]
        {
            if (coverReply->error() == QNetworkReply::NetworkError::NoError)
            {
                ui->coverButton->setIcon(QIcon(QPixmap::fromImage(QImage(coverReply->readAll()))));
                coverReply->deleteLater();
            }
        });
    }
}

AlbumCard::~AlbumCard()
{
    delete ui;
}
