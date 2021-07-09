#include "playlistcard.h"
#include "ui_playlistcard.h"

PlaylistCard::PlaylistCard(api::Deezer *apiInstance, api::Playlist &playlist, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistCard)
{
    ui->setupUi(this);

    this->setToolTip(playlist.title);

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
        pictureReply = apiInstance->getAnything(pictureUrl);
        connect(pictureReply, &QNetworkReply::errorOccurred, this, &PlaylistCard::errorOccurred);
        connect(pictureReply, &QNetworkReply::finished, this, &PlaylistCard::pictureLoaded);
    } else {
        pictureReply = nullptr;
    }
}

PlaylistCard::~PlaylistCard()
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

void PlaylistCard::errorOccurred(QNetworkReply::NetworkError error)
{
    if (pictureReply != nullptr)
    {
        pictureReply->deleteLater();
        pictureReply = nullptr;
    }
}

void PlaylistCard::pictureLoaded()
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

