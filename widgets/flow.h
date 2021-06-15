#ifndef ALBUMFLOW_H
#define ALBUMFLOW_H

#include "../api/deezer.h"

#include "albumcard.h"

#include <QScrollArea>
#include <QGridLayout>

namespace Ui {
class Flow;
}

class Flow : public QScrollArea
{
    Q_OBJECT

public:
    explicit Flow(api::Deezer *apiInstance, QWidget *parent = nullptr);
    ~Flow();
    void addContents(QVector<api::Album>&);
    void clearAll();

signals:
    void clickedItem(int id);

private:
    int lastContentIndex;
    Ui::Flow *ui;

    api::Deezer *apiInstance;

private slots:
    void innerClickedItem(int id);
};

#endif // ALBUMFLOW_H
