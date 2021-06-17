#include "playlistcard.h"
#include "ui_playlistcard.h"

PlaylistCard::PlaylistCard(api::Deezer *apiInstance, api::Playlist &playlist, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistCard)
{
    ui->setupUi(this);
    ui->titleLabel->setText(playlist.title);

    if (playlist.trackCount == -1)
    {
        ui->tracksLabel->hide();
    } else {
        ui->tracksLabel->setText(ui->tracksLabel->text().arg(QString::number(playlist.trackCount)));
    }

    connect(ui->pictureButton, &QPushButton::clicked, [playlistId{ playlist.id }, this]{ emit clickedPlaylist(playlistId); });

    if (!playlist.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(playlist.pictureMedium);
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

PlaylistCard::~PlaylistCard()
{
    delete ui;
}
