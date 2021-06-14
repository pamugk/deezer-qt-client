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
    explicit AlbumCard(api::Deezer apiInstance, api::Album &album, QWidget *parent = nullptr);
    ~AlbumCard();

signals:
    void clickedAlbum(int id);
    void clickedArtist(int id);

private:
    Ui::AlbumCard *ui;
};

#endif // ALBUMCARD_H
