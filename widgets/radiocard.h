#ifndef RADIOCARD_H
#define RADIOCARD_H

#include <QStackedWidget>

namespace Ui {
class RadioCard;
}

class RadioCard : public QStackedWidget
{
    Q_OBJECT

public:
    explicit RadioCard(QWidget *parent = nullptr);
    ~RadioCard();

private:
    Ui::RadioCard *ui;
};

#endif // RADIOCARD_H
