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
    void clickedArtist(long id);

private:
    QNetworkReply *pictureReply;
    Ui::ArtistCard *ui;

private slots:
    void errorOccurred(QNetworkReply::NetworkError error);
    void pictureLoaded();
};

#endif // ARTISTCARD_H
