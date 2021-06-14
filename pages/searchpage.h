#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "../api/deezer.h"

#include <QDebug>
#include <QTabWidget>

namespace Ui {
class SearchPage;
}

class SearchPage : public QTabWidget
{
    Q_OBJECT

public:
    explicit SearchPage(api::Deezer *, QWidget *parent = nullptr);
    ~SearchPage();

public slots:

    void search(QString);

private:
    bool hasUndergoingSearch;
    Ui::SearchPage *ui;
    api::Deezer *deezerApiInstance;

    void clear();
};

#endif // SEARCHPAGE_H
