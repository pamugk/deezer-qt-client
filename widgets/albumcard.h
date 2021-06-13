#ifndef ALBUMCARD_H
#define ALBUMCARD_H

#include <QWidget>

namespace Ui {
class AlbumCard;
}

class AlbumCard : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumCard(QWidget *parent = nullptr);
    ~AlbumCard();

private:
    Ui::AlbumCard *ui;
};

#endif // ALBUMCARD_H
