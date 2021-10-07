#ifndef RADIOFLOW_H
#define RADIOFLOW_H

#include "flow.h"
#include "../radiocard.h"

class RadioFlow : public Flow<api::Radio>
{
    Q_OBJECT

public:
    explicit RadioFlow(api::Deezer *apiInstance,
                       QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);

signals:
    void clickedItem(int id);

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::Radio &item) override;
};

#endif // RADIOFLOW_H
