#include "deezer.h"

namespace api {
    Deezer::Deezer()
    {
        networkManager = new QNetworkAccessManager();
    }

    Deezer::~Deezer()
    {
        delete networkManager;
    }
}
