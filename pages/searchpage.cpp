#include "searchpage.h"
#include "ui_searchpage.h"

SearchPage::SearchPage(api::Deezer * deezerApiInstance, QWidget *parent) :
    QTabWidget(parent),
    deezerApiInstance(deezerApiInstance),
    ui(new Ui::SearchPage)
{
    ui->setupUi(this);

    albumFlow = new AlbumFlow(deezerApiInstance, ui->albumScrollAreaContents);
    connect(albumFlow, &AlbumFlow::clickedItem, this, &SearchPage::albumClicked);
    ui->albumScrollAreaContents->setLayout(albumFlow);

    artistFlow = new ArtistFlow(deezerApiInstance, ui->artistScrollAreaContents);
    connect(artistFlow, &ArtistFlow::clickedItem, this, &SearchPage::artistClicked);
    ui->artistScrollAreaContents->setLayout(artistFlow);

    playlistFlow = new PlaylistFlow(deezerApiInstance, ui->playlistScrollAreaContents);
    connect(playlistFlow, &PlaylistFlow::clickedItem, this, &SearchPage::playlistClicked);
    ui->playlistScrollAreaContents->setLayout(playlistFlow);

    radioFlow = new RadioFlow(deezerApiInstance, ui->mixScrollAreaContents);
    connect(radioFlow, &RadioFlow::clickedItem, this, &SearchPage::radioClicked);
    ui->mixScrollAreaContents->setLayout(radioFlow);

    searchTracksModel = new SearchTracksModel(deezerApiInstance, ui->tracksTable);
    ui->tracksTable->setModel(searchTracksModel);

    userFlow = new UserFlow(deezerApiInstance, ui->userScrollAreaContents);
    connect(userFlow, &UserFlow::clickedItem, this, &SearchPage::userClicked);
    ui->userScrollAreaContents->setLayout(userFlow);

    clear();
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::searchRequested(QString request)
{
    if (request.isNull() || request.isEmpty())
    {
        return;
    }

    clear();

    currentRequest = request;

    auto trackPrefetchResponse = deezerApiInstance->searchTracks(request, 0, 5);
    connect(trackPrefetchResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(trackPrefetchResponse, error); });
    connect(trackPrefetchResponse, &QNetworkReply::finished, [=] { prefetchedTracks(trackPrefetchResponse); });

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

    albumFlow->clearAll();
    artistFlow->clearAll();
    playlistFlow->clearAll();
    radioFlow->clearAll();
    searchTracksModel->clearAll();
    userFlow->clearAll();
}

void SearchPage::fetchedAlbums(QNetworkReply *reply)
{
    auto albumsJson = api::tryReadResponse(reply).object();
    auto albumsResponse = api::deserializePartialResponseAlbum(albumsJson);
    QVector<api::Album> albumsData = albumsResponse.getData();
    albumFlow->addContents(albumsData);
}

void SearchPage::fetchedArtists(QNetworkReply *reply)
{
    auto artistsJson = api::tryReadResponse(reply).object();
    auto artistsResponse = api::deserializePartialResponseArtist(artistsJson);
    QVector<api::Artist> artistsData = artistsResponse.getData();
    artistFlow->addContents(artistsData);
}

void SearchPage::fetchedPlaylists(QNetworkReply *reply)
{
    auto playlistsJson = api::tryReadResponse(reply).object();
    auto playlistsResponse = api::deserializePartialResponsePlaylist(playlistsJson);
    QVector<api::Playlist> playlistsData = playlistsResponse.getData();
    playlistFlow->addContents(playlistsData);
}

void SearchPage::fetchedRadio(QNetworkReply *reply)
{
    auto radioJson = api::tryReadResponse(reply).object();
    auto radioResponse = api::deserializePartialResponseRadio(radioJson);
    QVector<api::Radio> radiosData = radioResponse.getData();
    radioFlow->addContents(radiosData);
}

void SearchPage::fetchedTracks(QNetworkReply *reply)
{
    auto tracksJson = api::tryReadResponse(reply).object();
    auto tracksResponse = api::deserializePartialResponseTrack(tracksJson);

    searchTracksModel->addData(tracksResponse.getData());
}

void SearchPage::fetchedUsers(QNetworkReply *reply)
{
    auto usersJson = api::tryReadResponse(reply).object();
    auto usersResponse = api::deserializePartialResponseUser(usersJson);
    QVector<api::User> usersData = usersResponse.getData();
    userFlow->addContents(usersData);
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

        auto prefetchedAlbumList = new QWidget(ui->overviewContents);
        auto prefetchedAlbumsLayout = new AlbumFlow(deezerApiInstance, prefetchedAlbumList);
        connect(prefetchedAlbumsLayout, &AlbumFlow::clickedItem, this, &SearchPage::albumClicked);
        prefetchedAlbumsLayout->addContents(albumPrefetch.getData());
        prefetchedAlbumList->setLayout(prefetchedAlbumsLayout);
        ui->overviewContentsLayout->addWidget(prefetchedAlbumList);

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

        auto prefetchedArtistList = new QWidget(ui->overviewContents);
        auto prefetchedArtistsLayout = new ArtistFlow(deezerApiInstance, prefetchedArtistList);
        connect(prefetchedArtistsLayout, &ArtistFlow::clickedItem, this, &SearchPage::artistClicked);
        prefetchedArtistsLayout->addContents(artistPrefetch.getData());
        prefetchedArtistList->setLayout(prefetchedArtistsLayout);
        ui->overviewContentsLayout->addWidget(prefetchedArtistList);

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

        auto prefetchedPlaylistList = new QWidget(ui->overviewContents);
        auto prefetchedPlaylistsLayout = new PlaylistFlow(deezerApiInstance, prefetchedPlaylistList);
        connect(prefetchedPlaylistsLayout, &PlaylistFlow::clickedItem, this, &SearchPage::playlistClicked);
        prefetchedPlaylistsLayout->addContents(playlistPrefetch.getData());
        prefetchedPlaylistList->setLayout(prefetchedPlaylistsLayout);
        ui->overviewContentsLayout->addWidget(prefetchedPlaylistList);

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

        auto prefetchedRadioList = new QWidget(ui->overviewContents);
        auto prefetchedRadiosLayout = new RadioFlow(deezerApiInstance, prefetchedRadioList);
        connect(prefetchedRadiosLayout, &RadioFlow::clickedItem, this, &SearchPage::radioClicked);
        prefetchedRadiosLayout->addContents(radioPrefetch.getData());
        prefetchedRadioList->setLayout(prefetchedRadiosLayout);
        ui->overviewContentsLayout->addWidget(prefetchedRadioList);

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
        auto prefetchedTracksTable = new QTableView(ui->overviewContents);
        auto prefetchedTracksModel = new SearchTracksModel(deezerApiInstance, prefetchedTracksTable);
        prefetchedTracksModel->addData(trackPrefetch.getData());
        prefetchedTracksTable->setModel(prefetchedTracksModel);
        ui->overviewContentsLayout->addWidget(prefetchedTracksTable);

        ui->trackLabel->setText(QString("Треков: %1").arg(QString::number(trackPrefetch.getTotal())));

        auto tracksResponse = deezerApiInstance->searchTracks(currentRequest, 0, 20);
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

        auto prefetchedUserList = new QWidget(ui->overviewContents);
        auto prefetchedUsersLayout = new UserFlow(deezerApiInstance, prefetchedUserList);
        connect(prefetchedUsersLayout, &UserFlow::clickedItem, this, &SearchPage::userClicked);
        prefetchedUsersLayout->addContents(userPrefetch.getData());
        prefetchedUserList->setLayout(prefetchedUsersLayout);
        ui->overviewContentsLayout->addWidget(prefetchedUserList);

        ui->userLabel->setText(QString("Профилей: %1").arg(QString::number(userPrefetch.getTotal())));

        auto usersResponse = deezerApiInstance->searchUsers(currentRequest, 0, 20);
        connect(usersResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(usersResponse, error); });
        connect(usersResponse, &QNetworkReply::finished, [=] { fetchedUsers(usersResponse); });
    }
}
