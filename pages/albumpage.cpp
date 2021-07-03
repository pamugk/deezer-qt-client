#include "../api/object/playable/album.h"

#include "albumpage.h"
#include "ui_albumpage.h"

AlbumPage::AlbumPage(api::Deezer *apiInstance, api::Album &album, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumPage)
{
    ui->setupUi(this);

    if (!album.coverMedium.isEmpty())
    {
        QUrl coverUrl(album.coverMedium);
        QNetworkReply *coverReply = apiInstance->getAnything(coverUrl);
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
                ui->coverLabel->setPixmap(cover);
                coverReply->deleteLater();
            }
        });
    }

    ui->titleLabel->setText(album.title);
    ui->tracksLabel->setText(ui->tracksLabel->text().append(QString::number(album.trackCount)));
    ui->durationLabel->setText(album.duration.hour() > 0 ?
                                   album.duration.toString("h 'ч.' m 'мин.' s 'сек.'") :
                                   album.duration.toString("m 'мин.' s 'сек.'"));
    ui->releaseDateLabel->setText(album.releaseDate.toString("dd.MM.yyyy"));
    ui->fansLabel->setText(ui->fansLabel->text().append(QString::number(album.fanCount)));

    ui->tracksTable->setModel(new AlbumTracksModel(album.tracks, ui->tracksTable));
}

AlbumPage::~AlbumPage()
{
    delete ui;
}
