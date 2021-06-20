#ifndef RADIOCARD_H
#define RADIOCARD_H

#include "../api/deezer.h"

#include <QStackedWidget>

namespace Ui {
class RadioCard;
}

class RadioCard : public QWidget
{
    Q_OBJECT

public:
    explicit RadioCard(api::Deezer *apiInsance, api::Radio &radio, QWidget *parent = nullptr);
    ~RadioCard();

signals:
    void clickedRadio(int id);

private:
    Ui::RadioCard *ui;
};

#endif // RADIOCARD_H
