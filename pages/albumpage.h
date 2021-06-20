#ifndef ALBUMPAGE_H
#define ALBUMPAGE_H

#include <QWidget>

namespace Ui {
class AlbumPage;
}

class AlbumPage : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumPage(QWidget *parent = nullptr);
    ~AlbumPage();

private:
    Ui::AlbumPage *ui;
};

#endif // ALBUMPAGE_H
