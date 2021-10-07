#ifndef ALBUMPAGE_H
#define ALBUMPAGE_H

#include "../api/deezer.h"

#include "../widgets/layouts/albumcarousel.h"
#include "../widgets/layouts/artistcarousel.h"

#include "../widgets/models/albumtracksmodel.h"

#include <QWidget>

namespace Ui {
class AlbumPage;
}

class AlbumPage : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumPage(api::Deezer *apiInstance, api::Album &album, QWidget *parent = nullptr);
    ~AlbumPage();

private slots:
    void on_prevDiscographyButton_clicked();

    void on_nextDiscographyButton_clicked();

    void on_prevRelatedArtistsButton_clicked();

    void on_nextRelatedArtistsButton_clicked();

private:
    AlbumCarousel *discographyCarousel;
    ArtistCarousel *relatedArtistsCarousel;
    Ui::AlbumPage *ui;
};

#endif // ALBUMPAGE_H
