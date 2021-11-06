#ifndef XML_SERIALIZATION_H
#define XML_SERIALIZATION_H

#include "../object/playable/album.h"
#include "../object/playable/artist.h"
#include "../object/playable/genre.h"
#include "../object/playable/playlist.h"
#include "../object/playable/podcast.h"
#include "../object/playable/radio.h"
#include "../object/playable/track.h"
#include "../object/search/partial_search_response.h"
#include "../object/search/shared.h"
#include "../object/service/permissions.h"
#include "../object/user/user.h"

#include <QXmlStreamReader>
#include <QNetworkReply>

namespace api
{
    void deserializeAlbum(QXmlStreamReader*, Album&, QString tag = "album");
    void deserializeArtist(QXmlStreamReader*, Artist&);
    void deserializeGenre(QXmlStreamReader*, Genre&);
    void deserializePlaylist(QXmlStreamReader*, Playlist&);
    void deserializePodcast(QXmlStreamReader*, Podcast&);
    void deserializeRadio(QXmlStreamReader*, Radio&);
    void deserializeTrack(QXmlStreamReader*, Track&, QString tag = "track");
    void deserializeUser(QXmlStreamReader*, User&, QString tag = "user");

    PartialSearchResponse<Album> deserializePartialResponseAlbum(QXmlStreamReader*);
    PartialSearchResponse<Artist> deserializePartialResponseArtist(QXmlStreamReader*);
    PartialSearchResponse<Playlist> deserializePartialResponsePlaylist(QXmlStreamReader*);
    PartialSearchResponse<Podcast> deserializePartialResponsePodcast(QXmlStreamReader*);
    PartialSearchResponse<Radio> deserializePartialResponseRadio(QXmlStreamReader*);
    PartialSearchResponse<Track> deserializePartialResponseTrack(QXmlStreamReader*);
    PartialSearchResponse<User> deserializePartialResponseUser(QXmlStreamReader*);

    QVector<Album> deserializeResponseAlbum(QXmlStreamReader*);
    QVector<Artist> deserializeResponseArtist(QXmlStreamReader*);
    QVector<Genre> deserializeResponseGenre(QXmlStreamReader*);
    QVector<Radio> deserializeResponseRadio(QXmlStreamReader*);
    QVector<Track> deserializeResponseTrack(QXmlStreamReader*);

    QXmlStreamReader *tryReadXmlResponse(QNetworkReply*);
}

#endif // XML_SERIALIZATION_H
