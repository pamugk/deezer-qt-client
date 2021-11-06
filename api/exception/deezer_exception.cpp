#include "deezer_exception.h"

namespace api
{
    DeezerException::DeezerException(QString message, int code):
        message(message),
        code(code)
    {
    }

    QString DeezerException::getMessage()
    {
        return message;
    }

    int DeezerException::getCode()
    {
        return code;
    }
}
