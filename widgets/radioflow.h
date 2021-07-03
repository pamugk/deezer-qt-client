#ifndef RADIOFLOW_H
#define RADIOFLOW_H

#include "radiocard.h"

#include <QLayoutItem>
#include <QScrollArea>

namespace Ui {
class RadioFlow;
}

class RadioFlow : public QScrollArea
{
    Q_OBJECT

public:
    explicit RadioFlow(api::Deezer *apiInstance, QWidget *parent = nullptr);
    ~RadioFlow();
    void addContents(QVector<api::Radio>&);
    void clearAll();

signals:
    void clickedItem(int id);

private:
    int lastContentIndex;
    Ui::RadioFlow *ui;

    api::Deezer *apiInstance;
};

#endif // RADIOFLOW_H
