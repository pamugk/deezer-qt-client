#ifndef PLAYLISTCARD_H
#define PLAYLISTCARD_H

#include "../api/deezer.h"

#include <QIcon>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class PlaylistCard;
}

class PlaylistCard : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistCard(api::Deezer *apiInstance, api::Playlist &playlist, QWidget *parent = nullptr);
    ~PlaylistCard();

signals:
    void clickedPlaylist(long id);

private:
    QNetworkReply *pictureReply;
    Ui::PlaylistCard *ui;

private slots:
    void errorOccurred(QNetworkReply::NetworkError error);
    void pictureLoaded();
};

#endif // PLAYLISTCARD_H
