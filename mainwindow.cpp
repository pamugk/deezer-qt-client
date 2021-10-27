#include "mainwindow.h"
#include "./ui_mainwindow.h"

QSystemTrayIcon *createTrayIcon();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->clearSearchButton->setHidden(true);
    ui->notificationsButton->setHidden(true);
    ui->userButton->setHidden(true);

    trayIcon = createTrayIcon();

    deezerApiInstance = new api::Deezer();

    currentPage = initializeMainPage();
    ui->windowLayout->addWidget(currentPage, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (trayIcon != nullptr)
    {
        delete trayIcon;
    }

    delete deezerApiInstance;
}

QSystemTrayIcon *createTrayIcon()
{
    QSystemTrayIcon *trayIcon = nullptr;
    /*if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        QIcon trayIconIcon;
        trayIconIcon.addFile(QString::fromUtf8(":/assets/deezer/logotype/SVG/EQ.svg"));
        trayIcon = new QSystemTrayIcon(trayIconIcon);
        trayIcon->show();
    }*/
    return trayIcon;
}

AlbumPage *MainWindow::initializeAlbumPage(api::Album &album)
{
    currentPageKind = PageKinds::ALBUM_PAGE;
    return new AlbumPage(deezerApiInstance, album, ui->centralwidget);
}

ArtistPage *MainWindow::initializeArtistPage(api::Artist &artist)
{
    currentPageKind = PageKinds::ARTIST_PAGE;

    auto artistPage = new ArtistPage(deezerApiInstance, artist, ui->centralwidget);
    connect(artistPage, &ArtistPage::albumClicked, this, &MainWindow::onRedirectToAlbum);
    connect(artistPage, &ArtistPage::artistClicked, this, &MainWindow::onRedirectToArtist);
    connect(artistPage, &ArtistPage::playlistClicked, this, &MainWindow::onRedirectToPlaylist);

    return artistPage;
}

MainPage *MainWindow::initializeMainPage()
{
    currentPageKind = PageKinds::MAIN_PAGE;
    return new MainPage(ui->centralwidget);
}

PlaylistPage *MainWindow::initializePlaylistPage(api::Playlist &playlist)
{
    currentPageKind = PageKinds::PLAYLIST_PAGE;

    auto playlistPage = new PlaylistPage(deezerApiInstance, playlist, ui->centralwidget);
    connect(playlistPage, &PlaylistPage::albumClicked, this, &MainWindow::onRedirectToAlbum);
    connect(playlistPage, &PlaylistPage::artistClicked, this, &MainWindow::onRedirectToArtist);
    connect(playlistPage, &PlaylistPage::trackClicked, this, &MainWindow::onRedirectToTrack);
    connect(playlistPage, &PlaylistPage::userClicked, this, &MainWindow::onRedirectToUser);

    return playlistPage;
}

RadioPage *MainWindow::initializeRadioPage(api::Radio&)
{
    currentPageKind = PageKinds::RADIO_PAGE;
    return new RadioPage(ui->centralwidget);
}

SearchPage *MainWindow::initializeSearchPage()
{
    currentPageKind = PageKinds::SEARCH_PAGE;
    auto searchPage = new SearchPage(deezerApiInstance, ui->centralwidget);

    connect(this, &MainWindow::onSearchInitiated, searchPage, &SearchPage::searchRequested);
    connect(searchPage, &SearchPage::albumClicked, this, &MainWindow::onRedirectToAlbum);
    connect(searchPage, &SearchPage::artistClicked, this, &MainWindow::onRedirectToArtist);
    connect(searchPage, &SearchPage::playlistClicked, this, &MainWindow::onRedirectToPlaylist);
    connect(searchPage, &SearchPage::radioClicked, this, &MainWindow::onRedirectToRadio);
    connect(searchPage, &SearchPage::userClicked, this, &MainWindow::onRedirectToUser);

    return searchPage;
}

UserPage *MainWindow::initializeUserPage(api::User& user)
{
    currentPageKind = PageKinds::USER_PAGE;
    auto userPage = new UserPage(deezerApiInstance, user, ui->centralwidget);

    connect(userPage, &UserPage::albumClicked, this, &MainWindow::onRedirectToAlbum);
    connect(userPage, &UserPage::artistClicked, this, &MainWindow::onRedirectToArtist);
    connect(userPage, &UserPage::playlistClicked, this, &MainWindow::onRedirectToPlaylist);
    connect(userPage, &UserPage::radioClicked, this, &MainWindow::onRedirectToRadio);
    connect(userPage, &UserPage::userClicked, this, &MainWindow::onRedirectToUser);

    return userPage;
}

void MainWindow::onError(QNetworkReply *reply, QNetworkReply::NetworkError error)
{
    qDebug() << error;
    reply->deleteLater();
}

void MainWindow::MainWindow::onRedirectToAlbum(long id) {
    auto albumResponse = deezerApiInstance->getAlbum(id);
    connect(albumResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ onError(albumResponse, error); });
    connect(albumResponse, &QNetworkReply::finished, [=] { onRedirectedToAlbum(albumResponse); });
}

void MainWindow::onRedirectedToAlbum(QNetworkReply *reply)
{
    auto albumJson = api::tryReadResponse(reply).object();
    api::Album album;
    api::deserializeAlbum(albumJson, album);
    switchPage(initializeAlbumPage(album));
}

void MainWindow::onRedirectToArtist(long id) {
    auto artistResponse = deezerApiInstance->getArtist(id);
    connect(artistResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ onError(artistResponse, error); });
    connect(artistResponse, &QNetworkReply::finished, [=] { onRedirectedToArtist(artistResponse); });
}

void MainWindow::onRedirectedToArtist(QNetworkReply *reply)
{
    auto artistJson = api::tryReadResponse(reply).object();
    api::Artist artist;
    api::deserializeArtist(artistJson, artist);
    switchPage(initializeArtistPage(artist));
}

void MainWindow::onRedirectToPlaylist(long id)
{
    auto playlistResponse = deezerApiInstance->getPlaylist(id);
    connect(playlistResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ onError(playlistResponse, error); });
    connect(playlistResponse, &QNetworkReply::finished, [=] { onRedirectedToPlaylist(playlistResponse); });
}

void MainWindow::onRedirectedToPlaylist(QNetworkReply *reply)
{
    auto playlistJson = api::tryReadResponse(reply).object();
    api::Playlist playlist;
    api::deserializePlaylist(playlistJson, playlist);
    switchPage(initializePlaylistPage(playlist));
}

void MainWindow::onRedirectToRadio(long id)
{
    auto radioResponse = deezerApiInstance->getRadio(id);
    connect(radioResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ onError(radioResponse, error); });
    connect(radioResponse, &QNetworkReply::finished, [=] { onRedirectedToRadio(radioResponse); });
}

void MainWindow::onRedirectedToRadio(QNetworkReply *reply)
{
    reply->deleteLater();
}

void MainWindow::onRedirectToTrack(long id)
{
    auto trackResponse = deezerApiInstance->getTrack(id);
    connect(trackResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ onError(trackResponse, error); });
    connect(trackResponse, &QNetworkReply::finished, [=] { onRedirectedToTrack(trackResponse); });
}

void MainWindow::onRedirectedToTrack(QNetworkReply *reply)
{
    reply->deleteLater();
}

void MainWindow::onRedirectToUser(long id)
{
    auto userResponse = deezerApiInstance->getUser(id);
    connect(userResponse, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error){ onError(userResponse, error); });
    connect(userResponse, &QNetworkReply::finished, [=] { onRedirectedToUser(userResponse); });
}

void MainWindow::onRedirectedToUser(QNetworkReply *reply)
{
    reply->deleteLater();
}

void MainWindow::on_searchLineEdit_textChanged(const QString &searchText)
{
    ui->clearSearchButton->setHidden(searchText.length() == 0);
    ui->searchButton->setDisabled(searchText.length() == 0);
}

void MainWindow::on_searchLineEdit_editingFinished()
{
    if (ui->searchLineEdit->hasFocus())
    {
        startSearch();
    }
}

void MainWindow::on_clearSearchButton_clicked()
{
    ui->searchLineEdit->clear();
}

void MainWindow::on_searchButton_clicked()
{
    startSearch();
}

void MainWindow::startSearch()
{
    if (ui->searchLineEdit->text().isEmpty())
    {
        return;
    }

    if (currentPageKind != PageKinds::SEARCH_PAGE)
    {
        switchPage(initializeSearchPage());
    }

    emit onSearchInitiated(ui->searchLineEdit->text());
}

void MainWindow::switchPage(QWidget *newPage)
{
    auto replacedPageItem = ui->windowLayout->replaceWidget(currentPage, newPage);

    if (replacedPageItem != nullptr) {
        replacedPageItem->widget()->deleteLater();
    }

    currentPage = newPage;
}
