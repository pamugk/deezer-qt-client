#include "searchpage.h"
#include "ui_searchpage.h"
#include "../api/util/xml_serialization.h"

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

    auto trackResponse = deezerApiInstance->searchTracks(request, 0, 20);
    connect(trackResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(trackResponse, error); });
    connect(trackResponse, &QNetworkReply::finished, [=] { fetchedTracks(trackResponse); });

    auto albumResponse = deezerApiInstance->searchAlbums(request, 0, 20);
    connect(albumResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(albumResponse, error); });
    connect(albumResponse, &QNetworkReply::finished, [=] { fetchedAlbums(albumResponse); });

    auto artistResponse = deezerApiInstance->searchArtists(request, 0, 20);
    connect(artistResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(artistResponse, error); });
    connect(artistResponse, &QNetworkReply::finished, [=] { fetchedArtists(artistResponse); });

    auto playlistResponse = deezerApiInstance->searchPlaylists(request, 0, 20);
    connect(playlistResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(playlistResponse, error); });
    connect(playlistResponse, &QNetworkReply::finished, [=] { fetchedPlaylists(playlistResponse); });

    auto radioResponse = deezerApiInstance->searchRadio(request, 0, 20);
    connect(radioResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(radioResponse, error); });
    connect(radioResponse, &QNetworkReply::finished, [=] { fetchedRadio(radioResponse); });

    auto userResponse = deezerApiInstance->searchUsers(request, 0, 20);
    connect(userResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ gotError(userResponse, error); });
    connect(userResponse, &QNetworkReply::finished, [=] { fetchedUsers(userResponse); });
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
    auto albumsResponse = api::tryReadXmlResponse(reply);
    auto albums = api::deserializePartialResponseAlbum(albumsResponse);
    delete albumsResponse;
    if (albums.getTotal() > 0)
    {
        QVector<api::Album> albumsData = albums.getData();
        addTab(ui->albumTab, QString("Альбомы"));
        ui->overviewContentsLayout->addWidget(new QLabel("Альбомы", ui->overviewContents));

        auto top5AlbumList = new QWidget(ui->overviewContents);
        auto top5AlbumsLayout = new AlbumFlow(deezerApiInstance, top5AlbumList);
        connect(top5AlbumsLayout, &AlbumFlow::clickedItem, this, &SearchPage::albumClicked);
        for (int i = 0; i < 5 && i < albumsData.size(); i++) {
            auto album = albumsData.at(i);
            top5AlbumsLayout->addElement(album);
        }
        top5AlbumList->setLayout(top5AlbumsLayout);
        ui->overviewContentsLayout->addWidget(top5AlbumList);

        ui->albumLabel->setText(QString("Альбомов: %1").arg(QString::number(albums.getTotal())));
        albumFlow->addContents(albumsData);
    }
}

void SearchPage::fetchedArtists(QNetworkReply *reply)
{
    auto artistsResponse = api::tryReadXmlResponse(reply);
    auto artists = api::deserializePartialResponseArtist(artistsResponse);
    delete artistsResponse;
    if (artists.getTotal() > 0)
    {
        QVector<api::Artist> artistsData = artists.getData();
        addTab(ui->artistTab, QString("Исполнители"));
        ui->overviewContentsLayout->addWidget(new QLabel("Исполнители", ui->overviewContents));

        auto top5ArtistList = new QWidget(ui->overviewContents);
        auto top5ArtistsLayout = new ArtistFlow(deezerApiInstance, top5ArtistList);
        connect(top5ArtistsLayout, &ArtistFlow::clickedItem, this, &SearchPage::artistClicked);
        for (int i = 0; i < 5 && i < artistsData.size(); i++) {
            auto artist = artistsData.at(i);
            top5ArtistsLayout->addElement(artist);
        }
        top5ArtistList->setLayout(top5ArtistsLayout);
        ui->overviewContentsLayout->addWidget(top5ArtistList);

        ui->artistLabel->setText(QString("Исполнителей: %1").arg(QString::number(artists.getTotal())));
        artistFlow->addContents(artistsData);
    }
}

void SearchPage::fetchedPlaylists(QNetworkReply *reply)
{
    auto playlistsResponse = api::tryReadXmlResponse(reply);
    auto playlists = api::deserializePartialResponsePlaylist(playlistsResponse);
    delete playlistsResponse;
    if (playlists.getTotal() > 0)
    {
        QVector<api::Playlist> playlistsData = playlists.getData();
        addTab(ui->playlistTab, QString("Плейлисты"));
        ui->overviewContentsLayout->addWidget(new QLabel("Плейлисты", ui->overviewContents));

        auto top5PlaylistList = new QWidget(ui->overviewContents);
        auto top5PlaylistsLayout = new PlaylistFlow(deezerApiInstance, top5PlaylistList);
        connect(top5PlaylistsLayout, &PlaylistFlow::clickedItem, this, &SearchPage::playlistClicked);
        for (int i = 0; i < 5 && i < playlistsData.size(); i++) {
            auto playlist = playlistsData.at(i);
            top5PlaylistsLayout->addElement(playlist);
        }
        top5PlaylistList->setLayout(top5PlaylistsLayout);
        ui->overviewContentsLayout->addWidget(top5PlaylistList);

        ui->playlistLabel->setText(QString("Плейлистов: %1").arg(QString::number(playlists.getTotal())));
        playlistFlow->addContents(playlistsData);
    }
}

void SearchPage::fetchedRadio(QNetworkReply *reply)
{
    auto radioResponse = api::tryReadXmlResponse(reply);
    auto radios = api::deserializePartialResponseRadio(radioResponse);
    delete radioResponse;
    if (radios.getTotal() > 0)
    {
        QVector<api::Radio> radiosData = radios.getData();
        addTab(ui->mixTab, QString("Миксы"));
        ui->overviewContentsLayout->addWidget(new QLabel("Миксы", ui->overviewContents));

        auto top5RadioList = new QWidget(ui->overviewContents);
        auto top5RadiosLayout = new RadioFlow(deezerApiInstance, top5RadioList);
        connect(top5RadiosLayout, &RadioFlow::clickedItem, this, &SearchPage::radioClicked);
        for (int i = 0; i < 5 && i < radiosData.size(); i++) {
            auto radio = radiosData.at(i);
            top5RadiosLayout->addElement(radio);
        }
        top5RadioList->setLayout(top5RadiosLayout);
        ui->overviewContentsLayout->addWidget(top5RadioList);

        ui->mixLabel->setText(QString("Миксов: %1").arg(QString::number(radios.getTotal())));
        radioFlow->addContents(radiosData);
    }
}

void SearchPage::fetchedTracks(QNetworkReply *reply)
{
    auto tracksResponse = api::tryReadXmlResponse(reply);
    auto tracks = api::deserializePartialResponseTrack(tracksResponse);
    delete tracksResponse;
    if (tracks.getTotal() > 0)
    {
        QVector<api::Track> tracksData = tracks.getData();
        addTab(ui->trackTab, QString("Треки"));

        ui->overviewContentsLayout->addWidget(new QLabel("Треки", ui->overviewContents));
        auto top5TracksTable = new QTableView(ui->overviewContents);
        auto top5TracksModel = new SearchTracksModel(deezerApiInstance, top5TracksTable);
        for (int i = 0; i < 5 && i < tracksData.size(); i++) {
            auto track = tracksData.at(i);
            top5TracksModel->addData(track);
        }
        top5TracksTable->setModel(top5TracksModel);
        ui->overviewContentsLayout->addWidget(top5TracksTable);

        ui->trackLabel->setText(QString("Треков: %1").arg(QString::number(tracks.getTotal())));
        searchTracksModel->addData(tracksData);
    }
}

void SearchPage::fetchedUsers(QNetworkReply *reply)
{
    auto usersResponse = api::tryReadXmlResponse(reply);
    auto users = api::deserializePartialResponseUser(usersResponse);
    delete usersResponse;
    if (users.getTotal() > 0)
    {
        QVector<api::User> usersData = users.getData();
        addTab(ui->userTab, QString("Профили"));
        ui->overviewContentsLayout->addWidget(new QLabel("Профили", ui->overviewContents));

        auto top5UserList = new QWidget(ui->overviewContents);
        auto top5UsersLayout = new UserFlow(deezerApiInstance, top5UserList);
        connect(top5UsersLayout, &UserFlow::clickedItem, this, &SearchPage::userClicked);
        for (int i = 0; i < 5 && i < usersData.size(); i++) {
            auto user = usersData.at(i);
            top5UsersLayout->addElement(user);
        }
        top5UserList->setLayout(top5UsersLayout);
        ui->overviewContentsLayout->addWidget(top5UserList);

        ui->userLabel->setText(QString("Профилей: %1").arg(QString::number(users.getTotal())));

        userFlow->addContents(usersData);
    }
}

void SearchPage::gotError(QNetworkReply *reply, QNetworkReply::NetworkError error)
{
    qDebug() << error;
    reply->deleteLater();
}
