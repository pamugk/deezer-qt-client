#ifndef ARTISTFLOW_H
#define ARTISTFLOW_H

#include "artistcard.h"

#include <QLayoutItem>
#include <QScrollArea>

namespace Ui {
class ArtistFlow;
}

class ArtistFlow : public QScrollArea
{
    Q_OBJECT

public:
    explicit ArtistFlow(api::Deezer *apiInstance, QWidget *parent = nullptr);
    ~ArtistFlow();
    void addContents(QVector<api::Artist>&);
    void clearAll();

signals:
    void clickedItem(int id);

private:
    int lastContentIndex;
    Ui::ArtistFlow *ui;

    api::Deezer *apiInstance;

private slots:
    void innerClickedItem(int id);
};

#endif // ARTISTFLOW_H
