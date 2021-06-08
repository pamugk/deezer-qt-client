#ifndef OPTIONS_H
#define OPTIONS_H

namespace api {
/*!
 * \brief User's options
 */
class Options
{
    /*!
     * \brief If the user can stream on the platform
     */
    bool streaming;
    /*!
     * \brief The streaming duration of the user
     */
    int streamingDuration;
    /*!
     * \brief The user can listen to the music in offline mode
     */
    bool offline;
    /*!
     * \brief The HQ can be activated
     */
    bool hq;

    /*!
     * \brief Displays ads
     */
    bool adsDisplay;
    /*!
     * \brief Activates audio ads
     */
    bool adsAudio;

    /*!
     * \brief If the user reached the limit of linked devices
     */
    bool tooManyDevices;
    /*!
     * \brief If the user can subscribe to the service
     */
    bool canSubscribe;
    /*!
     * \brief The limit of radio skips. 0 = no limit
     */
    int radioSkips;
    /*!
     * \brief Lossless is available
     */
    bool lossless;

    /*!
     * \brief Allows to display the preview of the tracks
     */
    bool preview;
    /*!
     * \brief Allows to stream the radio
     */
    bool radio;

public:
    Options();
};

}

#endif // OPTIONS_H
