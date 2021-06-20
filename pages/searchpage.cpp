#include "searchpage.h"
#include "ui_searchpage.h"

SearchPage::SearchPage(api::Deezer * deezerApiInstance, QWidget *parent) :
    QTabWidget(parent),
    deezerApiInstance(deezerApiInstance),
    ui(new Ui::SearchPage)
{
    ui->setupUi(this);

    albums = new AlbumFlow(deezerApiInstance, ui->albumTab);
    ui->albumTabLayout->addWidget(albums);

    artists = new ArtistFlow(deezerApiInstance, ui->artistTab);
    ui->artistTabLayout->addWidget(artists);

    playlists = new PlaylistFlow(deezerApiInstance, ui->playlistTab);
    ui->playlistTabLayout->addWidget(playlists);

    users = new UserFlow(deezerApiInstance, ui->userTab);
    ui->userTabLayout->addWidget(users);

    clear();
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::search(QString request)
{
    if (request.isNull() || request.isEmpty())
    {
        return;
    }

    clear();

    currentRequest = request;

    auto trackPrefetchResponse = deezerApiInstance->searchTracks(request, 0, 5);
    connect(trackPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(trackPrefetchResponse, error); });
    connect(trackPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedAlbums(trackPrefetchResponse); });


    auto albumPrefetchResponse = deezerApiInstance->searchAlbums(request, 0, 5);
    connect(albumPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(albumPrefetchResponse, error); });
    connect(albumPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedAlbums(albumPrefetchResponse); });

    auto artistPrefetchResponse = deezerApiInstance->searchArtists(request, 0, 5);
    connect(artistPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(artistPrefetchResponse, error); });
    connect(artistPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedArtists(artistPrefetchResponse); });

    auto playlistPrefetchResponse = deezerApiInstance->searchPlaylists(request, 0, 5);
    connect(albumPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(playlistPrefetchResponse, error); });
    connect(playlistPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedPlaylists(playlistPrefetchResponse); });

    auto radioPrefetchResponse = deezerApiInstance->searchRadio(request, 0, 5);
    connect(radioPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(radioPrefetchResponse, error); });
    connect(radioPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedRadio(radioPrefetchResponse); });

    auto userPrefetchResponse = deezerApiInstance->searchUsers(request, 0, 5);
    connect(userPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(userPrefetchResponse, error); });
    connect(userPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedUsers(userPrefetchResponse); });
}

void SearchPage::clear()
{
    while (count() > 1)
    {
        removeTab(1);
    }

    while (QLayoutItem *item = ui->overviewContentsLayout->takeAt(0))
    {
        ui->overviewContentsLayout->removeItem(item);
    }

    albums->clearAll();
    artists->clearAll();
    playlists->clearAll();
    users->clearAll();
}

void SearchPage::fetchedAlbums(QNetworkReply *reply)
{
    auto albumsJson = api::tryReadResponse(reply).object();
    auto albumsResponse = api::deserializePartialResponseAlbum(albumsJson);
    QVector<api::Album> albumsData = albumsResponse.getData();
    albums->addContents(albumsData);
}

void SearchPage::fetchedArtists(QNetworkReply *reply)
{
    auto artistsJson = api::tryReadResponse(reply).object();
    auto artistsResponse = api::deserializePartialResponseArtist(artistsJson);
    QVector<api::Artist> artistsData = artistsResponse.getData();
    artists->addContents(artistsData);
}

void SearchPage::fetchedPlaylists(QNetworkReply *reply)
{
    auto playlistsJson = api::tryReadResponse(reply).object();
    auto playlistsResponse = api::deserializePartialResponsePlaylist(playlistsJson);
    QVector<api::Playlist> playlistsData = playlistsResponse.getData();
    playlists->addContents(playlistsData);
}

void SearchPage::fetchedRadio(QNetworkReply *reply)
{
    auto radioJson = api::tryReadResponse(reply).object();
    auto radioResponse = api::deserializePartialResponseRadio(radioJson);
}

void SearchPage::fetchedTracks(QNetworkReply *reply)
{
    auto tracksJson = api::tryReadResponse(reply).object();
    auto tracksResponse = api::deserializePartialResponseUser(tracksJson);
}

void SearchPage::fetchedUsers(QNetworkReply *reply)
{
    auto usersJson = api::tryReadResponse(reply).object();
    auto usersResponse = api::deserializePartialResponseUser(usersJson);
    QVector<api::User> usersData = usersResponse.getData();
    users->addContents(usersData);
}

void SearchPage::gotError(QNetworkReply *reply, QNetworkReply::NetworkError error)
{
    qDebug() << error;
    reply->deleteLater();
}

void SearchPage::prefetchedAlbums(QNetworkReply *reply)
{
    auto albumPrefetchJson = api::tryReadResponse(reply).object();
    auto albumPrefetch = api::deserializePartialResponseAlbum(albumPrefetchJson);
    if (albumPrefetch.getTotal() > 0)
    {
        addTab(ui->albumTab, QString("Альбомы"));
        ui->overviewContentsLayout->addWidget(new QLabel("Альбомы", ui->overviewContents));
        ui->albumLabel->setText(QString("Альбомов: %1").arg(QString::number(albumPrefetch.getTotal())));

        auto albumsResponse = deezerApiInstance->searchAlbums(currentRequest, 0, 20);
        connect(albumsResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(albumsResponse, error); });
        connect(albumsResponse, &QNetworkReply::finished, [=] { fetchedAlbums(albumsResponse); });
    }
}

void SearchPage::prefetchedArtists(QNetworkReply *reply)
{
    auto artistPrefetchJson = api::tryReadResponse(reply).object();
    auto artistPrefetch = api::deserializePartialResponseArtist(artistPrefetchJson);
    if (artistPrefetch.getTotal() > 0)
    {
        addTab(ui->artistTab, QString("Исполнители"));
        ui->overviewContentsLayout->addWidget(new QLabel("Исполнители", ui->overviewContents));
        ui->artistLabel->setText(QString("Исполнителей: %1").arg(QString::number(artistPrefetch.getTotal())));

        auto artistsResponse = deezerApiInstance->searchArtists(currentRequest, 0, 20);
        connect(artistsResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(artistsResponse, error); });
        connect(artistsResponse, &QNetworkReply::finished, [=] { fetchedArtists(artistsResponse); });
    }
}

void SearchPage::prefetchedPlaylists(QNetworkReply *reply)
{
    auto playlistPrefetchJson = api::tryReadResponse(reply).object();
    auto playlistPrefetch = api::deserializePartialResponsePlaylist(playlistPrefetchJson);
    if (playlistPrefetch.getTotal() > 0)
    {
        addTab(ui->playlistTab, QString("Плейлисты"));
        ui->overviewContentsLayout->addWidget(new QLabel("Плейлисты", ui->overviewContents));
        ui->playlistLabel->setText(QString("Плейлистов: %1").arg(QString::number(playlistPrefetch.getTotal())));

        auto playlistsResponse = deezerApiInstance->searchPlaylists(currentRequest, 0, 20);
        connect(playlistsResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(playlistsResponse, error); });
        connect(playlistsResponse, &QNetworkReply::finished, [=] { fetchedPlaylists(playlistsResponse); });
    }
}

void SearchPage::prefetchedRadio(QNetworkReply *reply)
{
    auto radioPrefetchJson = api::tryReadResponse(reply).object();
    auto radioPrefetch = api::deserializePartialResponseRadio(radioPrefetchJson);
    if (radioPrefetch.getTotal() > 0)
    {
        addTab(ui->mixTab, QString("Миксы"));
        ui->overviewContentsLayout->addWidget(new QLabel("Миксы", ui->overviewContents));
        ui->mixLabel->setText(QString("Миксов: %1").arg(QString::number(radioPrefetch.getTotal())));

        auto radioResponse = deezerApiInstance->searchRadio(currentRequest, 0, 20);
        connect(radioResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(radioResponse, error); });
        connect(radioResponse, &QNetworkReply::finished, [=] { fetchedRadio(radioResponse); });
    }
}

void SearchPage::prefetchedTracks(QNetworkReply *reply)
{
    auto trackPrefetchJson = api::tryReadResponse(reply).object();
    auto trackPrefetch = api::deserializePartialResponseTrack(trackPrefetchJson);
    if (trackPrefetch.getTotal() > 0)
    {
        addTab(ui->trackTab, QString("Треки"));
        ui->overviewContentsLayout->addWidget(new QLabel("Треки", ui->overviewContents));
        ui->trackLabel->setText(QString("Треков: %1").arg(QString::number(trackPrefetch.getTotal())));

        auto tracksResponse = deezerApiInstance->searchRadio(currentRequest, 0, 20);
        connect(tracksResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(tracksResponse, error); });
        connect(tracksResponse, &QNetworkReply::finished, [=] { fetchedTracks(tracksResponse); });
    }
}

void SearchPage::prefetchedUsers(QNetworkReply *reply)
{
    auto userPrefetchJson = api::tryReadResponse(reply).object();
    auto userPrefetch = api::deserializePartialResponseUser(userPrefetchJson);
    if (userPrefetch.getTotal() > 0)
    {
        addTab(ui->userTab, QString("Профили"));
        ui->overviewContentsLayout->addWidget(new QLabel("Профили", ui->overviewContents));
        ui->userLabel->setText(QString("Профилей: %1").arg(QString::number(userPrefetch.getTotal())));

        auto usersResponse = deezerApiInstance->searchUsers(currentRequest, 0, 20);
        connect(usersResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(usersResponse, error); });
        connect(usersResponse, &QNetworkReply::finished, [=] { fetchedUsers(usersResponse); });
    }
}

