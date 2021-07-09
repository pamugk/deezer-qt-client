#include "userflow.h"

UserFlow::UserFlow(api::Deezer *apiInstance,
                   QWidget *parent, int margin, int hSpacing, int vSpacing) :
    Flow(parent, margin, hSpacing, vSpacing),
    apiInstance(apiInstance){}

QWidget *UserFlow::instantiateItem(api::User &obj)
{
    UserCard *userCard = new UserCard(apiInstance, obj, static_cast<QWidget *>(this->parent()));
    connect(userCard, &UserCard::clickedUser, this, &UserFlow::clickedItem);
    return userCard;
}
