#ifndef FOLDER_H
#define FOLDER_H

#include <QString>

namespace api {
    /*!
     * \brief User's Folder
     */
    class Folder
    {
        /*!
         * \brief The folder's Deezer id
         */
        long id;
        /*!
         * \brief The folder's title
         */
        QString title;

    public:
        Folder();
    };
}

#endif // FOLDER_H
