#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "../api/deezer.h"

#include <QTabWidget>

namespace Ui {
class SearchPage;
}

class SearchPage : public QTabWidget
{
    Q_OBJECT

public:
    explicit SearchPage(QWidget *parent = nullptr);
    ~SearchPage();

    void setDeezerApiInstance(api::Deezer *);

private:
    Ui::SearchPage *ui;
    api::Deezer *deezerApiInstance;
};

#endif // SEARCHPAGE_H
