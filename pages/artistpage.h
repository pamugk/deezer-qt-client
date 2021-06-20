#ifndef ARTISTPAGE_H
#define ARTISTPAGE_H

#include <QWidget>

namespace Ui {
class ArtistPage;
}

class ArtistPage : public QWidget
{
    Q_OBJECT

public:
    explicit ArtistPage(QWidget *parent = nullptr);
    ~ArtistPage();

private:
    Ui::ArtistPage *ui;
};

#endif // ARTISTPAGE_H
