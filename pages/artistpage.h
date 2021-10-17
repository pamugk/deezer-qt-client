#ifndef ARTISTPAGE_H
#define ARTISTPAGE_H

#include <QWidget>

#include "../api/deezer.h"

#include "../widgets/layouts/albumflow.h"
#include "../widgets/layouts/artistflow.h"
#include "../widgets/layouts/playlistflow.h"

#include "../widgets/models/searchtracksmodel.h"

namespace Ui {
class ArtistPage;
}

class ArtistPage : public QWidget
{
    Q_OBJECT

public:
    explicit ArtistPage(api::Deezer *, api::Artist&, QWidget *parent = nullptr);
    ~ArtistPage();

signals:
    void albumClicked(long id);
    void artistClicked(long id);
    void playlistClicked(long id);

private:
    Ui::ArtistPage *ui;

    AlbumFlow *albumFlow;
    PlaylistFlow *playlistFlow;
    SearchTracksModel *popularTracksModel;
    ArtistFlow *relatedArtistsFlow;
    SearchTracksModel *top5TracksModel;

    api::Deezer *apiInstance;

    void fetchedRelatedArtists(QNetworkReply*);
    void fetchedPlaylists(QNetworkReply*);

    void gotError(QNetworkReply*, QNetworkReply::NetworkError);
};

#endif // ARTISTPAGE_H
