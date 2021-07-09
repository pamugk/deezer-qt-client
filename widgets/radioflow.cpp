#include "radioflow.h"

RadioFlow::RadioFlow(api::Deezer *apiInstance,
                     QWidget *parent, int margin, int hSpacing, int vSpacing) :
  Flow(parent, margin, hSpacing, vSpacing),
  apiInstance(apiInstance){}

QWidget *RadioFlow::instantiateItem(api::Radio &obj)
{
    RadioCard *radioCard = new RadioCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    connect(radioCard, &RadioCard::clickedRadio, this, &RadioFlow::clickedItem);
    return radioCard;
}
