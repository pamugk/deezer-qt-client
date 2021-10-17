#ifndef PLAYLISTPAGE_H
#define PLAYLISTPAGE_H

#include <QWidget>

#include "../api/deezer.h"

#include "../widgets/models/searchtracksmodel.h"

namespace Ui {
class PlaylistPage;
}

class PlaylistPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistPage(api::Deezer *, api::Playlist &, QWidget * = nullptr);
    ~PlaylistPage();

signals:
    void albumClicked(long id);
    void artistClicked(long id);
    void trackClicked(long id);
    void userClicked(long id);

private:
    Ui::PlaylistPage *ui;

    SearchTracksModel *playlistTracksModel;
};

#endif // PLAYLISTPAGE_H
