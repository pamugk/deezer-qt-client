#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(api::Deezer *apiInstance, api::User& user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);

    ui->followingLabel->setVisible(false);
    ui->followersLabel->setVisible(false);
    while (ui->infoTabsWidget->count() > 1) {
        ui->infoTabsWidget->removeTab(1);
    }

    auto playlistsReply = apiInstance->getUserPlaylists(user.id, 0, 20);
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

            playlistFlow = new PlaylistFlow(apiInstance, ui->playlistsScrollContents);
            playlistFlow->addContents(playlists.getData());
            connect(playlistFlow, &PlaylistFlow::clickedItem, this, &UserPage::playlistClicked);
            ui->playlistsScrollContents->setLayout(playlistFlow);

            ui->infoTabsWidget->addTab(ui->playlistsTab, QString("Плейлисты"));
        }
    });

    auto albumsReply = apiInstance->getUserFavoriteAlbums(user.id);
    connect(albumsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        albumsReply->deleteLater();
    });
    connect(albumsReply, &QNetworkReply::finished, [=]
    {
        if (albumsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto albumsJson = api::tryReadResponse(albumsReply).object();
            auto albums = api::deserializeResponseAlbum(albumsJson);
            albumsReply->deleteLater();

            albumFlow = new AlbumFlow(apiInstance, ui->albumsScrollContents);
            albumFlow->addContents(albums);
            connect(albumFlow, &AlbumFlow::clickedItem, this, &UserPage::albumClicked);
            ui->albumsScrollContents->setLayout(albumFlow);

            ui->infoTabsWidget->addTab(ui->albumsTab, QString("Альбомы"));
        }
    });

    auto artistsReply = apiInstance->getUserFavoriteArtists(user.id);
    connect(artistsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        artistsReply->deleteLater();
    });
    connect(artistsReply, &QNetworkReply::finished, [=]
    {
        if (artistsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto artistsJson = api::tryReadResponse(artistsReply).object();
            auto artists = api::deserializeResponseArtist(artistsJson);
            artistsReply->deleteLater();

            artistFlow = new ArtistFlow(apiInstance, ui->artitsScrollContents);
            artistFlow->addContents(artists);
            connect(artistFlow, &ArtistFlow::clickedItem, this, &UserPage::artistClicked);
            ui->artitsScrollContents->setLayout(artistFlow);

            ui->infoTabsWidget->addTab(ui->artistsTab, QString("Исполнители"));
        }
    });

    auto radiosReply = apiInstance->getUserFavoriteRadios(user.id);
    connect(radiosReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        radiosReply->deleteLater();
    });
    connect(radiosReply, &QNetworkReply::finished, [=]
    {
        if (radiosReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto radiosJson = api::tryReadResponse(radiosReply).object();
            auto radios = api::deserializeResponseRadio(radiosJson);
            radiosReply->deleteLater();

            radioFlow = new RadioFlow(apiInstance, ui->radiosScrollContents);
            radioFlow->addContents(radios);
            connect(radioFlow, &RadioFlow::clickedItem, this, &UserPage::radioClicked);
            ui->radiosScrollContents->setLayout(radioFlow);

            ui->infoTabsWidget->addTab(ui->radiosTab, QString("Миксы"));
        }
    });

    auto followingsReply = apiInstance->getUserFollowings(user.id, 0, 20);
    connect(followingsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        followingsReply->deleteLater();
    });
    connect(followingsReply, &QNetworkReply::finished, [=]
    {
        if (followingsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto followingsJson = api::tryReadResponse(followingsReply).object();
            auto followings = api::deserializePartialResponseUser(followingsJson);
            followingsReply->deleteLater();

            followingsFlow = new UserFlow(apiInstance, ui->followingScrollContents);
            followingsFlow->addContents(followings.getData());
            connect(followingsFlow, &UserFlow::clickedItem, this, &UserPage::userClicked);
            ui->followingScrollContents->setLayout(followingsFlow);

            ui->infoTabsWidget->addTab(ui->followingTab, QString("Подписки"));
            ui->followingLabel->setText(ui->followingLabel->text().append(QString::number(followings.getTotal())));
            ui->followingLabel->setVisible(true);
        }
    });

    auto followersReply = apiInstance->getUserFollowers(user.id, 0, 20);
    connect(followersReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        followersReply->deleteLater();
    });
    connect(followersReply, &QNetworkReply::finished, [=]
    {
        if (followersReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto followersJson = api::tryReadResponse(followersReply).object();
            auto followers = api::deserializePartialResponseUser(followersJson);
            followersReply->deleteLater();

            followersFlow = new UserFlow(apiInstance, ui->followersScrollContents);
            followersFlow->addContents(followers.getData());
            connect(followersFlow, &UserFlow::clickedItem, this, &UserPage::userClicked);
            ui->followersScrollContents->setLayout(followersFlow);

            ui->infoTabsWidget->addTab(ui->followersTab, QString("Подписчики"));
            ui->followersLabel->setText(ui->followersLabel->text().append(QString::number(followers.getTotal())));
            ui->followersLabel->setVisible(true);
        }
    });

    ui->nameLabel->setText(user.name);
}

UserPage::~UserPage()
{
    delete ui;
}

void UserPage::fetchedAlbums(QNetworkReply *reply)
{
    auto albumsJson = api::tryReadResponse(reply).object();
    auto albumsResponse = api::deserializePartialResponseAlbum(albumsJson);
    QVector<api::Album> albumsData = albumsResponse.getData();
    albumFlow->addContents(albumsData);
}

void UserPage::fetchedArtists(QNetworkReply *reply)
{
    auto artistsJson = api::tryReadResponse(reply).object();
    auto artistsResponse = api::deserializePartialResponseArtist(artistsJson);
    QVector<api::Artist> artistsData = artistsResponse.getData();
    artistFlow->addContents(artistsData);
}

void UserPage::fetchedPlaylists(QNetworkReply *reply)
{
    auto playlistsJson = api::tryReadResponse(reply).object();
    auto playlistsResponse = api::deserializePartialResponsePlaylist(playlistsJson);
    QVector<api::Playlist> playlistsData = playlistsResponse.getData();
    playlistFlow->addContents(playlistsData);
}

void UserPage::fetchedRadio(QNetworkReply *reply)
{
    auto radioJson = api::tryReadResponse(reply).object();
    auto radioResponse = api::deserializePartialResponseRadio(radioJson);
    QVector<api::Radio> radiosData = radioResponse.getData();
    radioFlow->addContents(radiosData);
}

void UserPage::fetchedTracks(QNetworkReply *reply)
{
    auto tracksJson = api::tryReadResponse(reply).object();
    auto tracksResponse = api::deserializePartialResponseTrack(tracksJson);

    searchTracksModel->addData(tracksResponse.getData());
}

void UserPage::fetchedFollowers(QNetworkReply *reply)
{
    auto usersJson = api::tryReadResponse(reply).object();
    auto usersResponse = api::deserializePartialResponseUser(usersJson);
    QVector<api::User> usersData = usersResponse.getData();
    followersFlow->addContents(usersData);
}

void UserPage::gotError(QNetworkReply *reply, QNetworkReply::NetworkError error)
{
    qDebug() << error;
    reply->deleteLater();
}
