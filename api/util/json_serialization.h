#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "../object/playable/album.h"
#include "../object/playable/artist.h"
#include "../object/playable/genre.h"
#include "../object/playable/playlist.h"
#include "../object/playable/podcast.h"
#include "../object/playable/radio.h"
#include "../object/playable/track.h"
#include "../object/search/partial_search_response.h"
#include "../object/search/shared.h"
#include "../object/user/user.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValueRef>
#include <QString>

namespace api
{
    void deserializeAlbum(QJsonObject&, Album&);
    void deserializeArtist(QJsonObject&, Artist&);
    void deserializeGenre(QJsonObject&, Genre&);
    void deserializePlaylist(QJsonObject&, Playlist&);
    void deserializePodcast(QJsonObject&, Podcast&);
    void deserializeRadio(QJsonObject&, Radio&);
    void deserializeTrack(QJsonObject&, Track&);
    void deserializeUser(QJsonObject&, User&);

    template<typename T>
    PartialSearchResponse<T> deserializePartialResponse(QJsonObject&, QJsonArray&);
    PartialSearchResponse<Album> deserializePartialResponseAlbum(QJsonObject&);
    PartialSearchResponse<Artist> deserializePartialResponseArtist(QJsonObject&);
    PartialSearchResponse<Playlist> deserializePartialResponsePlaylist(QJsonObject&);
    PartialSearchResponse<Podcast> deserializePartialResponsePodcast(QJsonObject&);
    PartialSearchResponse<Radio> deserializePartialResponseRadio(QJsonObject&);
    PartialSearchResponse<Track> deserializePartialResponseTrack(QJsonObject&);
    PartialSearchResponse<User> deserializePartialResponseUser(QJsonObject&);

    QVector<Album> deserializeResponseAlbum(QJsonObject&);
    QVector<Artist> deserializeResponseArtist(QJsonObject&);
    QVector<Genre> deserializeResponseGenre(QJsonObject&);
    QVector<Radio> deserializeResponseRadio(QJsonObject&);
    QVector<Track> deserializeResponseTrack(QJsonObject&);

    QString serialize(SearchOrder);

    template<typename T>
    PartialSearchResponse<T> deserializePartialResponse(QJsonObject &jsonObj, QJsonArray &jsonData)
    {
        return PartialSearchResponse<T>(
                    QVector<T>(jsonData.size()),
                    jsonObj.keys().contains("total") ? jsonObj["total"].toInt() : 0,
                    jsonObj.keys().contains("prev") ? QString(jsonObj["prev"].toString()) : QString(),
                    jsonObj.keys().contains("next") ? QString(jsonObj["next"].toString()) : QString());
    }
}
#endif // SERIALIZATION_H
