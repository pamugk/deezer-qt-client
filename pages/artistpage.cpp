#include "artistpage.h"
#include "ui_artistpage.h"

ArtistPage::ArtistPage(api::Deezer *apiInstance, api::Artist &artist, QWidget *parent) :
    QWidget(parent),
    apiInstance(apiInstance),
    ui(new Ui::ArtistPage)
{
    ui->setupUi(this);

    while (ui->infoTabsWidget->count() > 1) {
        ui->infoTabsWidget->removeTab(1);
    }

    top5TracksModel = new SearchTracksModel(apiInstance, ui->top5TracksTableView);
    ui->top5TracksTableView->setModel(top5TracksModel);

    popularTracksModel = new SearchTracksModel(apiInstance, ui->popularTracksTableView);
    ui->popularTracksTableView->setModel(popularTracksModel);

    if (!artist.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(artist.pictureMedium);
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

    api::AdvancedSearchQuery popularTracksQuery;
    popularTracksQuery.artist = artist.name;
    auto popularTracksReply = apiInstance->search(popularTracksQuery, 0, 100, false, api::SearchOrder::RATING_DESC);
    connect(popularTracksReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        popularTracksReply->deleteLater();
    });
    connect(popularTracksReply, &QNetworkReply::finished, [=]
    {
        if (popularTracksReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto popularTracksJson = api::tryReadResponse(popularTracksReply).object();
            auto popularTracks = api::deserializePartialResponseTrack(popularTracksJson);
            popularTracksReply->deleteLater();

            for (int i = 0; i < 5 && i < popularTracks.getData().length(); i++) {
                top5TracksModel->addData(popularTracks.getData().at(i));
            }

            popularTracksModel->addData(popularTracks.getData());

            ui->infoTabsWidget->addTab(ui->tracksTab, QString("Популярные треки"));
        }
    });

    auto albumsReply = apiInstance->getArtistAlbums(artist.id, 0, 20);
    connect(albumsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        albumsReply->deleteLater();
    });
    connect(albumsReply, &QNetworkReply::finished, [=]
    {
        if (albumsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto albumsJson = api::tryReadResponse(albumsReply).object();
            auto albums = api::deserializePartialResponseAlbum(albumsJson);
            albumsReply->deleteLater();

            albumFlow = new AlbumFlow(apiInstance, ui->discographyFlow);
            albumFlow->addContents(albums.getData());
            connect(albumFlow, &AlbumFlow::clickedItem, this, &ArtistPage::albumClicked);
            ui->discographyFlow->setLayout(albumFlow);
        }
    });

    auto relatedArtistsReply = apiInstance->getArtistRelated(artist.id, 0, 20);
    connect(relatedArtistsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        relatedArtistsReply->deleteLater();
    });
    connect(relatedArtistsReply, &QNetworkReply::finished, [=]
    {
        if (relatedArtistsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto relatedArtistsJson = api::tryReadResponse(relatedArtistsReply).object();
            auto relatedArtists = api::deserializePartialResponseArtist(relatedArtistsJson);
            relatedArtistsReply->deleteLater();

            relatedArtistsFlow = new ArtistFlow(apiInstance, ui->relatedArtistsFlow);
            relatedArtistsFlow->addContents(relatedArtists.getData());
            connect(relatedArtistsFlow, &ArtistFlow::clickedItem, this, &ArtistPage::artistClicked);
            ui->relatedArtistsFlow->setLayout(relatedArtistsFlow);

            ui->infoTabsWidget->addTab(ui->relatedTab, QString("Похожие исполнители"));
        }
    });

    auto playlistsReply = apiInstance->getArtistPlaylists(artist.id, 0, 20);
    connect(playlistsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        playlistsReply->deleteLater();
    });
    connect(playlistsReply, &QNetworkReply::finished, [=]
    {
        if (playlistsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto playlistsJson = api::tryReadResponse(playlistsReply).object();
            auto playlists = api::deserializePartialResponsePlaylist(playlistsJson);
            playlistsReply->deleteLater();

            playlistFlow = new PlaylistFlow(apiInstance, ui->playlistsFlow);
            playlistFlow->addContents(playlists.getData());
            connect(playlistFlow, &PlaylistFlow::clickedItem, this, &ArtistPage::playlistClicked);
            ui->playlistsFlow->setLayout(playlistFlow);

            ui->infoTabsWidget->addTab(ui->playlistsTab, QString("Плейлисты"));
        }
    });

    ui->nameLabel->setText(artist.name);
    ui->fansLabel->setText(ui->fansLabel->text().append(QString::number(artist.fanCount)));
}

ArtistPage::~ArtistPage()
{
    delete ui;
}

void ArtistPage::gotError(QNetworkReply *reply, QNetworkReply::NetworkError error)
{
    qDebug() << error;
    reply->deleteLater();
}

void ArtistPage::fetchedRelatedArtists(QNetworkReply *reply)
{
    auto artistsJson = api::tryReadResponse(reply).object();
    auto artistsResponse = api::deserializePartialResponseArtist(artistsJson);
    QVector<api::Artist> artistsData = artistsResponse.getData();
    relatedArtistsFlow->addContents(artistsData);
}

void ArtistPage::fetchedPlaylists(QNetworkReply *reply)
{
    auto playlistsJson = api::tryReadResponse(reply).object();
    auto playlistsResponse = api::deserializePartialResponsePlaylist(playlistsJson);
    QVector<api::Playlist> playlistsData = playlistsResponse.getData();
    playlistFlow->addContents(playlistsData);
}
