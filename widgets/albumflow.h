#ifndef ALBUMFLOW_H
#define ALBUMFLOW_H

#include "../api/deezer.h"

#include "albumcard.h"

#include <QScrollArea>
#include <QGridLayout>

namespace Ui {
class AlbumFlow;
}

class AlbumFlow : public QScrollArea
{
    Q_OBJECT

public:
    explicit AlbumFlow(api::Deezer *apiInstance, QWidget *parent = nullptr);
    ~AlbumFlow();
    void addContents(QVector<api::Album>&);
    void clearAll();

signals:
    void clickedItem(int id);

private:
    int lastContentIndex;
    Ui::AlbumFlow *ui;

    api::Deezer *apiInstance;
};

#endif // ALBUMFLOW_H
