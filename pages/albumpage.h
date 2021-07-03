#ifndef ALBUMPAGE_H
#define ALBUMPAGE_H

#include "../api/deezer.h"

#include "../model/albumtracksmodel.h"

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

private:
    Ui::AlbumPage *ui;
};

#endif // ALBUMPAGE_H
