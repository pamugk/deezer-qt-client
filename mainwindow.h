#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "api/deezer.h"

#include "pages/pages.h"

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRedirectToAlbum(long id);

    void onRedirectToArtist(long id);

    void onRedirectToPlaylist(long id);

    void onRedirectToRadio(long id);

    void onRedirectToTrack(long id);

    void onRedirectToUser(long id);

    void on_searchLineEdit_textChanged(const QString &arg1);

    void on_clearSearchButton_clicked();

    void on_searchLineEdit_editingFinished();

    void on_searchButton_clicked();

private:
    QSystemTrayIcon *trayIcon;
    Ui::MainWindow *ui;

    PageKinds currentPageKind;
    QWidget *currentPage;

    api::Deezer* deezerApiInstance;

    AlbumPage *initializeAlbumPage(api::Album&);

    ArtistPage *initializeArtistPage(api::Artist&);

    MainPage *initializeMainPage();

    PlaylistPage *initializePlaylistPage(api::Playlist&);

    RadioPage *initializeRadioPage(api::Radio&);

    SearchPage *initializeSearchPage();

    UserPage *initializeUserPage(api::User&);

    void onError(QNetworkReply *reply, QNetworkReply::NetworkError error);

    void onRedirectedToAlbum(QNetworkReply *reply);

    void onRedirectedToArtist(QNetworkReply *reply);

    void onRedirectedToPlaylist(QNetworkReply *reply);

    void onRedirectedToRadio(QNetworkReply *reply);

    void onRedirectedToTrack(QNetworkReply *reply);

    void onRedirectedToUser(QNetworkReply *reply);

    void startSearch();

    void switchPage(QWidget *newPage);

signals:
    void onSearchInitiated(QString searchString);
};
#endif // MAINWINDOW_H
