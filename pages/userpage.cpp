#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(api::Deezer *apiInstance, api::User& user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);

    ui->followingLabel->setVisible(false);
    ui->followersLabel->setVisible(false);
    while (ui->infoTabsWidget->count() > 1)
    {
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
            auto playlistsData = playlists.getData();
            playlistsReply->deleteLater();

            if (playlists.getTotal() == 0)
            {
                return;
            }

            ui->overviewContentsLayout->addWidget(new QLabel("Плейлисты", ui->overviewScrollContents));
            auto top5PlaylistList = new QWidget(ui->overviewScrollContents);
            auto top5PlaylistsLayout = new PlaylistFlow(deezerApiInstance, top5PlaylistList);
            connect(top5PlaylistsLayout, &PlaylistFlow::clickedItem, this, &UserPage::playlistClicked);
            for (int i = 0; i < 5 && i < playlistsData.size(); i ++) {
                auto playlist = playlistsData.at(0);
                top5PlaylistsLayout->addElement(playlist);
            }
            top5PlaylistList->setLayout(top5PlaylistsLayout);
            ui->overviewContentsLayout->addWidget(top5PlaylistList);

            playlistFlow = new PlaylistFlow(apiInstance, ui->playlistsScrollContents);
            playlistFlow->addContents(playlistsData);
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

            if (albums.size() == 0)
            {
                return;
            }

            ui->overviewContentsLayout->addWidget(new QLabel("Альбомы", ui->overviewScrollContents));
            auto top5AlbumList = new QWidget(ui->overviewScrollContents);
            auto top5AlbumsLayout = new AlbumFlow(deezerApiInstance, top5AlbumList);
            connect(top5AlbumsLayout, &AlbumFlow::clickedItem, this, &UserPage::albumClicked);
            for (int i = 0; i < 5 && i < albums.size(); i ++) {
                auto album = albums.at(0);
                top5AlbumsLayout->addElement(album);
            }
            top5AlbumList->setLayout(top5AlbumsLayout);
            ui->overviewContentsLayout->addWidget(top5AlbumList);

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

            if (artists.size() == 0)
            {
                return;
            }

            ui->overviewContentsLayout->addWidget(new QLabel("Исполнители", ui->overviewScrollContents));
            auto top5ArtistList = new QWidget(ui->overviewScrollContents);
            auto top5ArtistsLayout = new ArtistFlow(deezerApiInstance, top5ArtistList);
            connect(top5ArtistsLayout, &ArtistFlow::clickedItem, this, &UserPage::artistClicked);
            for (int i = 0; i < 5 && i < artists.size(); i ++) {
                auto artist = artists.at(0);
                top5ArtistsLayout->addElement(artist);
            }
            top5ArtistList->setLayout(top5ArtistsLayout);
            ui->overviewContentsLayout->addWidget(top5ArtistList);

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

            if (radios.size() == 0)
            {
                return;
            }

            ui->overviewContentsLayout->addWidget(new QLabel("Миксы", ui->overviewScrollContents));
            auto top5RadioList = new QWidget(ui->overviewScrollContents);
            auto top5RadiosLayout = new RadioFlow(deezerApiInstance, top5RadioList);
            connect(top5RadiosLayout, &RadioFlow::clickedItem, this, &UserPage::radioClicked);
            for (int i = 0; i < 5 && i < radios.size(); i ++) {
                auto radio = radios.at(0);
                top5RadiosLayout->addElement(radio);
            }
            top5RadioList->setLayout(top5RadiosLayout);
            ui->overviewContentsLayout->addWidget(top5RadioList);

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
            auto followingsData = followings.getData();
            followingsReply->deleteLater();

            if (followings.getTotal() == 0)
            {
                return;
            }

            ui->overviewContentsLayout->addWidget(new QLabel("Подписки", ui->overviewScrollContents));
            auto top5FollowingsList = new QWidget(ui->overviewScrollContents);
            auto top5FollowingsLayout = new UserFlow(deezerApiInstance, top5FollowingsList);
            connect(top5FollowingsLayout, &UserFlow::clickedItem, this, &UserPage::userClicked);
            for (int i = 0; i < 5 && i < followingsData.size(); i ++) {
                auto user = followingsData.at(0);
                top5FollowingsLayout->addElement(user);
            }
            top5FollowingsList->setLayout(top5FollowingsLayout);
            ui->overviewContentsLayout->addWidget(top5FollowingsList);

            followingsFlow = new UserFlow(apiInstance, ui->followingScrollContents);
            followingsFlow->addContents(followingsData);
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
            auto followersData = followers.getData();
            followersReply->deleteLater();

            if (followers.getTotal() == 0)
            {
                return;
            }

            ui->overviewContentsLayout->addWidget(new QLabel("Подписчики", ui->overviewScrollContents));
            auto top5FollowingsList = new QWidget(ui->overviewScrollContents);
            auto top5FollowingsLayout = new UserFlow(deezerApiInstance, top5FollowingsList);
            connect(top5FollowingsLayout, &UserFlow::clickedItem, this, &UserPage::userClicked);
            for (int i = 0; i < 5 && i < followersData.size(); i ++) {
                auto user = followersData.at(0);
                top5FollowingsLayout->addElement(user);
            }
            top5FollowingsList->setLayout(top5FollowingsLayout);
            ui->overviewContentsLayout->addWidget(top5FollowingsList);

            followersFlow = new UserFlow(apiInstance, ui->followersScrollContents);
            followersFlow->addContents(followersData);
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
