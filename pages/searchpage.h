#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "../api/deezer.h"

#include "../widgets/models/searchtracksmodel.h"

#include "../widgets/layouts/albumflow.h"
#include "../widgets/layouts/artistflow.h"
#include "../widgets/layouts/playlistflow.h"
#include "../widgets/layouts/radioflow.h"
#include "../widgets/layouts/userflow.h"


#include <QTabWidget>

namespace Ui {
class SearchPage;
}

class SearchPage : public QTabWidget
{
    Q_OBJECT

public:
    explicit SearchPage(api::Deezer *, QWidget *parent = nullptr);
    ~SearchPage();

signals:
    void albumClicked(int id);
    void artistClicked(int id);
    void playlistClicked(int id);
    void radioClicked(int id);
    void userClicked(int id);

public slots:
    void searchRequested(QString);

private:
    QString currentRequest;

    Ui::SearchPage *ui;

    AlbumFlow *albumFlow;
    ArtistFlow *artistFlow;
    PlaylistFlow *playlistFlow;
    RadioFlow *radioFlow;
    SearchTracksModel *searchTracksModel;
    UserFlow *userFlow;

    api::Deezer *deezerApiInstance;

    void clear();

    void fetchedAlbums(QNetworkReply*);
    void fetchedArtists(QNetworkReply*);
    void fetchedPlaylists(QNetworkReply*);
    void fetchedRadio(QNetworkReply*);
    void fetchedTracks(QNetworkReply*);
    void fetchedUsers(QNetworkReply*);

    void gotError(QNetworkReply*, QNetworkReply::NetworkError);

    void prefetchedAlbums(QNetworkReply*);
    void prefetchedArtists(QNetworkReply*);
    void prefetchedPlaylists(QNetworkReply*);
    void prefetchedRadio(QNetworkReply*);
    void prefetchedTracks(QNetworkReply*);
    void prefetchedUsers(QNetworkReply*);

};

#endif // SEARCHPAGE_H
