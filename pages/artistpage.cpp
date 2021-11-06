#include "artistpage.h"
#include "ui_artistpage.h"
#include "../api/util/xml_serialization.h"

ArtistPage::ArtistPage(api::Deezer *apiInstance, api::Artist &artist, QWidget *parent) :
    QWidget(parent),
    apiInstance(apiInstance),
    ui(new Ui::ArtistPage)
{
    ui->setupUi(this);

    ui->top5TracksLabel->setVisible(false);
    ui->top5TracksTableView->setVisible(false);

    while (ui->infoTabsWidget->count() > 1) {
        ui->infoTabsWidget->removeTab(1);
    }

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
            popularTracksModel = new SearchTracksModel(apiInstance, ui->popularTracksTableView);
            ui->popularTracksTableView->setModel(popularTracksModel);
            auto popularTracksResponse = api::tryReadXmlResponse(popularTracksReply);
            auto popularTracks = api::deserializePartialResponseTrack(popularTracksResponse);
            delete popularTracksResponse;

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
            auto albumsResponse = api::tryReadXmlResponse(albumsReply);
            auto albums = api::deserializePartialResponseAlbum(albumsResponse);
            delete albumsResponse;

            albumFlow = new AlbumFlow(apiInstance, ui->discographyFlow);
            albumFlow->addContents(albums.getData());
            connect(albumFlow, &AlbumFlow::clickedItem, this, &ArtistPage::albumClicked);
            ui->discographyFlow->setLayout(albumFlow);

            ui->infoTabsWidget->addTab(ui->discographyTab, QString("Дискография"));
        }
    });

    auto top5TracksReply = apiInstance->getArtistTop(artist.id);
    connect(top5TracksReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        top5TracksReply->deleteLater();
    });
    connect(top5TracksReply, &QNetworkReply::finished, [=]
    {
        if (top5TracksReply->error() == QNetworkReply::NetworkError::NoError)
        {
            top5TracksModel = new SearchTracksModel(apiInstance, ui->top5TracksTableView);
            ui->top5TracksTableView->setModel(top5TracksModel);
            auto top5TracksResponse = api::tryReadXmlResponse(top5TracksReply);
            auto top5Tracks = api::deserializeResponseTrack(top5TracksResponse);
            delete top5TracksResponse;
            top5TracksModel->addData(top5Tracks);
            ui->top5TracksLabel->setVisible(true);
            ui->top5TracksTableView->setVisible(true);
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
            auto relatedArtistsResponse = api::tryReadXmlResponse(relatedArtistsReply);
            auto relatedArtists = api::deserializePartialResponseArtist(relatedArtistsResponse);
            delete relatedArtistsResponse;

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
            auto playlistsResponse = api::tryReadXmlResponse(playlistsReply);
            auto playlists = api::deserializePartialResponsePlaylist(playlistsResponse);
            delete playlistsResponse;

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
    auto artistsResponse = api::tryReadXmlResponse(reply);
    auto artists = api::deserializePartialResponseArtist(artistsResponse);
    QVector<api::Artist> artistsData = artists.getData();
    relatedArtistsFlow->addContents(artistsData);
}

void ArtistPage::fetchedPlaylists(QNetworkReply *reply)
{
    auto playlistsResponse = api::tryReadXmlResponse(reply);
    auto playlists = api::deserializePartialResponsePlaylist(playlistsResponse);
    QVector<api::Playlist> playlistsData = playlists.getData();
    playlistFlow->addContents(playlistsData);
}
