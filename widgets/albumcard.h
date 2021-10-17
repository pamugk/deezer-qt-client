#ifndef ALBUMCARD_H
#define ALBUMCARD_H

#include "../api/deezer.h"

#include <QWidget>

namespace Ui {
class AlbumCard;
}

class AlbumCard : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumCard(api::Deezer *apiInstance, api::Album &album, QWidget *parent = nullptr);
    ~AlbumCard();

signals:
    void clickedAlbum(long id);
    void clickedArtist(long id);

private:
    QNetworkReply *coverReply;
    Ui::AlbumCard *ui;

private slots:
    void coverLoaded();
    void errorOccurred(QNetworkReply::NetworkError error);
};

#endif // ALBUMCARD_H
