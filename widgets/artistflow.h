#ifndef ARTISTFLOW_H
#define ARTISTFLOW_H

#include "artistcard.h"
#include "flow.h"

class ArtistFlow : public Flow<api::Artist>
{
    Q_OBJECT

public:
    explicit ArtistFlow(api::Deezer *apiInstance,
                        QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);

signals:
    void clickedItem(int id);

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::Artist &item) override;
};

#endif // ARTISTFLOW_H
