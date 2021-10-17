#ifndef USERFLOW_H
#define USERFLOW_H

#include "flow.h"
#include "../usercard.h"

class UserFlow : public Flow<api::User>
{
    Q_OBJECT

public:
    explicit UserFlow(api::Deezer *apiInstance,
                      QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);

signals:
    void clickedItem(long id);

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::User &item) override;
};

#endif // USERFLOW_H
