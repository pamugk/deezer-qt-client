#ifndef ALBUMFLOW_H
#define ALBUMFLOW_H

#include "albumcard.h"
#include "flow.h"

class AlbumFlow : public Flow<api::Album>
{
    Q_OBJECT

public:
    explicit AlbumFlow(api::Deezer *apiInstance,
                       QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);

signals:
    void clickedItem(int id);

private:
    api::Deezer *apiInstance;
    QWidget *instantiateItem(api::Album &item) override;
};

#endif // ALBUMFLOW_H
