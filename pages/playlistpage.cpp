#include "playlistpage.h"
#include "ui_playlistpage.h"

PlaylistPage::PlaylistPage(api::Deezer *apiInstance, api::Playlist &playlist, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistPage)
{
    ui->setupUi(this);

    ui->titleLabel->setText(playlist.title);

    if (playlist.creator.isNull()) {

    } else {
        if (!playlist.creator->pictureSmall.isEmpty()) {
            QUrl pictureUrl(playlist.pictureSmall);
            auto coverReply = apiInstance->getAnything(pictureUrl);
            connect(coverReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
            {
                coverReply->deleteLater();
            });
            connect(coverReply, &QNetworkReply::finished, [=]
            {
                if (coverReply->error() == QNetworkReply::NetworkError::NoError)
                {
                    auto imageBytes = coverReply->readAll();
                    auto cover = QPixmap(32, 32);
                    cover.loadFromData(imageBytes);
                    ui->creatorPictureLabel->setPixmap(cover);
                    coverReply->deleteLater();
                }
            });
        }
        ui->creatorButton->setText(playlist.creator->name);
    }

    ui->descriptionLabel->setText(playlist.description);

    ui->tracksLabel->setText(ui->tracksLabel->text().append(QString::number(playlist.trackCount)));
    ui->durationLabel->setText(playlist.duration.toString("hh:mm:ss"));
    ui->fansLabel->setText(ui->fansLabel->text().append(QString::number(playlist.fanCount)));
    ui->lastUpdatedLabel->setText(ui->lastUpdatedLabel->text().append("недавно"));

    if (!playlist.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(playlist.pictureMedium);
        auto coverReply = apiInstance->getAnything(pictureUrl);
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
                ui->pictureLabel->setPixmap(cover);
                coverReply->deleteLater();
            }
        });
    }

    playlistTracksModel = new SearchTracksModel(apiInstance, ui->tracksTableView);
    ui->tracksTableView->setModel(playlistTracksModel);

    if (!playlist.tracks.isEmpty()) {
        playlistTracksModel->addData(playlist.tracks);
    } else {
        auto playlistTracksResponse = apiInstance->getPlaylistTracks(playlist.id);
        connect(playlistTracksResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
        {
            playlistTracksResponse->deleteLater();
        });
        connect(playlistTracksResponse, &QNetworkReply::finished, [=]
        {
            if (playlistTracksResponse->error() == QNetworkReply::NetworkError::NoError)
            {
                auto playlistTracksJson = api::tryReadResponse(playlistTracksResponse).object();
                auto playlistTracks = api::deserializePartialResponseTrack(playlistTracksJson);
                playlistTracksResponse->deleteLater();
                playlistTracksModel->addData(playlistTracks.getData());
            }
        });
    }
}

PlaylistPage::~PlaylistPage()
{
    delete ui;
}
