#ifndef USERFLOW_H
#define USERFLOW_H

#include "usercard.h"

#include <QLayoutItem>
#include <QScrollArea>

namespace Ui {
class UserFlow;
}

class UserFlow : public QScrollArea
{
    Q_OBJECT

public:
    explicit UserFlow(api::Deezer *apiInstance, QWidget *parent = nullptr);
    ~UserFlow();
    void addContents(QVector<api::User>&);
    void clearAll();

signals:
    void clickedItem(int id);

private:
    int lastContentIndex;
    Ui::UserFlow *ui;

    api::Deezer *apiInstance;

private slots:
    void innerClickedItem(int id);
};

#endif // USERFLOW_H
