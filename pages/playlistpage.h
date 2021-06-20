#ifndef PLAYLISTPAGE_H
#define PLAYLISTPAGE_H

#include <QWidget>

namespace Ui {
class PlaylistPage;
}

class PlaylistPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistPage(QWidget *parent = nullptr);
    ~PlaylistPage();

private:
    Ui::PlaylistPage *ui;
};

#endif // PLAYLISTPAGE_H
