#include "albumcard.h"
#include "ui_albumcard.h"

AlbumCard::AlbumCard(api::Deezer *apiInstance, api::Album &album, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumCard)
{
    ui->setupUi(this);

    this->setToolTip(album.title);

    ui->titleLabel->setText(album.title);

    if (album.artist.isNull())
    {
        ui->artistLabel->hide();
    } else {
        ui->artistLabel->setText(ui->artistLabel->text().arg(album.artist->name));
    }

    if (!album.explicitLyrics)
    {
        ui->explicityLabel->hide();
    }

    connect(ui->coverButton, &QPushButton::clicked, [albumId{ album.id }, this]{ emit clickedAlbum(albumId); });

    if (!album.coverMedium.isEmpty())
    {
        QUrl coverUrl(album.coverMedium);
        coverReply = apiInstance->getAnything(coverUrl);
        connect(coverReply, &QNetworkReply::errorOccurred, this, &AlbumCard::errorOccurred);
        connect(coverReply, &QNetworkReply::finished, this, &AlbumCard::coverLoaded);
    } else {
        coverReply = nullptr;
    }
}

AlbumCard::~AlbumCard()
{
    if (coverReply != nullptr && !coverReply->isFinished())
    {
        qDebug() << "Aborting";
        QEventLoop loop;
        connect(coverReply, &QNetworkReply::errorOccurred, &loop, &QEventLoop::quit);
        coverReply->abort();
        loop.exec();
    }
    delete ui;
}

void AlbumCard::coverLoaded()
{
    if (coverReply->error() == QNetworkReply::NetworkError::NoError)
    {
        auto imageBytes = coverReply->readAll();
        auto cover = QPixmap(250, 250);
        cover.loadFromData(imageBytes);
        ui->coverButton->setIcon(QIcon(cover));
    }
    coverReply->deleteLater();
    coverReply = nullptr;
}

void AlbumCard::errorOccurred(QNetworkReply::NetworkError error)
{
    if (coverReply != nullptr)
    {
        coverReply->deleteLater();
        coverReply = nullptr;
    }
}
