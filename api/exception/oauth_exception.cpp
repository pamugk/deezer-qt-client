#include "oauth_exception.h"

namespace api
{
    OAuthException::OAuthException(QString message, int code): DeezerException(message, code)
    {
    }
}
