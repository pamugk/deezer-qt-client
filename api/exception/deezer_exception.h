#ifndef DEEZEREXCEPTION_H
#define DEEZEREXCEPTION_H

#include <QString>

namespace api
{
    class DeezerException: std::exception
    {
    public:
        DeezerException(QString message, int code);

    private:
        QString message;
        int code;

    public:
        QString getMessage();
        int getCode();
    };
}

#endif // DEEZEREXCEPTION_H
