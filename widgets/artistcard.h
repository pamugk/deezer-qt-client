#ifndef ARTISTCARD_H
#define ARTISTCARD_H

#include "../api/deezer.h"

#include <QWidget>

namespace Ui {
class ArtistCard;
}

class ArtistCard : public QWidget
{
    Q_OBJECT

public:
    explicit ArtistCard(api::Deezer *apiInstance, api::Artist &artist, QWidget *parent = nullptr);
    ~ArtistCard();

signals:
    void clickedArtist(int id);

private:
    Ui::ArtistCard *ui;
};

#endif // ARTISTCARD_H
