#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "../api/deezer.h"

#include "../widgets/albumflow.h"
#include "../widgets/artistflow.h"
#include "../widgets/playlistflow.h"
#include "../widgets/userflow.h"


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

public slots:

    void search(QString);

private:
    bool hasUndergoingSearch;
    Ui::SearchPage *ui;

    AlbumFlow *albums;
    ArtistFlow *artists;
    PlaylistFlow *playlists;
    UserFlow *users;

    api::Deezer *deezerApiInstance;

    void clear();
};

#endif // SEARCHPAGE_H
