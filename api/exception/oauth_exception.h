#ifndef OAUTHEXCEPTION_H
#define OAUTHEXCEPTION_H

#include "deezer_exception.h"

namespace api
{
    class OAuthException: public DeezerException
    {
    public:
        OAuthException(QString message, int code);
    };
}

#endif // OAUTHEXCEPTION_H
