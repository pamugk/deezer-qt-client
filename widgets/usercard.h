#ifndef USERCARD_H
#define USERCARD_H

#include "../api/deezer.h"

#include <QPushButton>
#include <QWidget>

namespace Ui {
class UserCard;
}

class UserCard : public QWidget
{
    Q_OBJECT

public:
    explicit UserCard(api::Deezer *apiInstance, api::User &user, QWidget *parent = nullptr);
    ~UserCard();

signals:
    void clickedUser(int id);

private:
    Ui::UserCard *ui;
};

#endif // USERCARD_H
