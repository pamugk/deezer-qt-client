#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>

#include "../api/deezer.h"

#include "../widgets/layouts/albumflow.h"
#include "../widgets/layouts/artistflow.h"
#include "../widgets/layouts/playlistflow.h"
#include "../widgets/layouts/radioflow.h"
#include "../widgets/layouts/userflow.h"
#include "../widgets/models/searchtracksmodel.h"

namespace Ui {
class UserPage;
}

class UserPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserPage(api::Deezer *, api::User&, QWidget *parent = nullptr);
    ~UserPage();

signals:
    void albumClicked(long id);
    void artistClicked(long id);
    void playlistClicked(long id);
    void radioClicked(long id);
    void userClicked(long id);

private:
    Ui::UserPage *ui;

    AlbumFlow *albumFlow;
    ArtistFlow *artistFlow;
    PlaylistFlow *playlistFlow;
    RadioFlow *radioFlow;
    SearchTracksModel *searchTracksModel;
    UserFlow *followersFlow;
    UserFlow *followingsFlow;

    api::Deezer *deezerApiInstance;

    void clear();

    void fetchedAlbums(QNetworkReply*);
    void fetchedArtists(QNetworkReply*);
    void fetchedPlaylists(QNetworkReply*);
    void fetchedRadio(QNetworkReply*);
    void fetchedTracks(QNetworkReply*);
    void fetchedFollowers(QNetworkReply*);
    void fetchedFollowings(QNetworkReply*);

    void gotError(QNetworkReply*, QNetworkReply::NetworkError);
};

#endif // USERPAGE_H
