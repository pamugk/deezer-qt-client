#include "xml_serialization.h"
#include "serialization.h"
#include "../exception/oauth_exception.h"

namespace api
{
    void deserializeError(QXmlStreamReader *responseReader)
    {
        QString message, type;
        int code = 0;
        bool parsed = false;
        QStringRef currentElement;
        while (!responseReader->atEnd() && !parsed)
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "message")
                {
                    message = responseReader->text().toString();
                }
                else if (currentElement == "code")
                {
                    code = responseReader->text().toInt();
                }
                else if (currentElement == "type")
                {
                    type = responseReader->text().toString();
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "error")
                {
                    parsed = true;
                }
                break;
            }
            default:
                break;
            }
        }

        if (type == "OAuthException")
        {
            throw new OAuthException(message, code);
        }
    }

    void deserializeAlbum(QXmlStreamReader *responseReader, Album &albumOut, QString tag)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    albumOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "title")
                {
                    albumOut.title = responseReader->text().toString();
                }
                else if (currentElement == "upc")
                {
                    albumOut.upc = responseReader->text().toString();
                }

                else if (currentElement == "link")
                {
                    albumOut.link = responseReader->text().toString();
                }
                else if (currentElement == "share")
                {
                    albumOut.share = responseReader->text().toString();
                }

                else if (currentElement == "cover")
                {
                    albumOut.cover = responseReader->text().toString();
                }
                else if (currentElement == "cover_small")
                {
                    albumOut.coverSmall = responseReader->text().toString();
                }
                else if (currentElement == "cover_medium")
                {
                    albumOut.coverMedium = responseReader->text().toString();
                }
                else if (currentElement == "cover_big")
                {
                    albumOut.coverBig = responseReader->text().toString();
                }
                else if (currentElement == "cover_xl")
                {
                    albumOut.coverXl = responseReader->text().toString();
                }
                else if (currentElement == "md5_image")
                {
                    albumOut.md5Image = responseReader->text().toString();
                }

                else if (currentElement == "genre_id")
                {
                    albumOut.genreId = responseReader->text().toLong();
                }
                else if (currentElement == "genres")
                {
                    albumOut.genres = deserializeResponseGenre(responseReader);
                }

                else if (currentElement == "nb_tracks")
                {
                    albumOut.trackCount = responseReader->text().toInt();
                }
                else if (currentElement == "duration")
                {
                    albumOut.duration = deserializeTime(responseReader->text().toInt());
                }
                else if (currentElement == "fans")
                {
                    albumOut.fanCount = responseReader->text().toInt();
                }
                else if (currentElement == "rating")
                {
                    albumOut.rating = responseReader->text().toInt();
                }
                else if (currentElement == "release_date")
                {
                    albumOut.releaseDate = QDate::fromString(responseReader->text().toString(), "YYYY-MM-DD");
                }

                else if (currentElement == "record_type")
                {
                    albumOut.recordType = responseReader->text().toString();
                }
                else if (currentElement == "available")
                {
                    albumOut.available = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "alternative")
                {
                    albumOut.alternative = QSharedPointer<Album>(new Album());
                    deserializeAlbum(responseReader, *albumOut.alternative, "alternative");
                }

                else if (currentElement == "tracklist")
                {
                    albumOut.tracklist = responseReader->text().toString();
                }

                else if (currentElement == "explicit_lyrics")
                {
                    albumOut.explicitLyrics = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "explicit_content_lyrics")
                {
                    albumOut.explicitContentLyrics = Explicity(responseReader->text().toInt());
                }
                else if (currentElement == "explicit_content_cover")
                {
                    albumOut.explicitContentCover = Explicity(responseReader->text().toInt());
                }

                else if (currentElement == "position")
                {
                    albumOut.position = responseReader->text().toInt();
                }
                else if (currentElement == "contributors")
                {
                    albumOut.contributors = deserializeResponseArtist(responseReader);
                }
                else if (currentElement == "artist")
                {
                    albumOut.artist = QSharedPointer<Artist>(new Artist());
                    deserializeArtist(responseReader, *albumOut.artist);
                }
                else if (currentElement == "tracks")
                {
                    albumOut.tracks = deserializeResponseTrack(responseReader);
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "album")
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializeArtist(QXmlStreamReader *responseReader, Artist &artistOut)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    artistOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "name")
                {
                    artistOut.name = responseReader->text().toString();
                }

                else if (currentElement == "link")
                {
                    artistOut.link = responseReader->text().toString();
                }
                else if (currentElement == "share")
                {
                    artistOut.share = responseReader->text().toString();
                }

                else if (currentElement == "picture")
                {
                    artistOut.picture = responseReader->text().toString();
                }
                else if (currentElement == "picture_small")
                {
                    artistOut.pictureSmall = responseReader->text().toString();
                }
                else if (currentElement == "picture_medium")
                {
                    artistOut.pictureMedium = responseReader->text().toString();
                }
                else if (currentElement == "picture_big")
                {
                    artistOut.pictureBig = responseReader->text().toString();
                }
                else if (currentElement == "picture_xl")
                {
                    artistOut.pictureXl = responseReader->text().toString();
                }

                else if (currentElement == "albumCount")
                {
                    artistOut.albumCount = responseReader->text().toInt();
                }
                else if (currentElement == "nb_fan")
                {
                    artistOut.fanCount = responseReader->text().toInt();
                }
                else if (currentElement == "radio")
                {
                    artistOut.radio = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "tracklist")
                {
                    artistOut.tracklist = responseReader->text().toString();
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "artist")
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializeGenre(QXmlStreamReader *responseReader, Genre &genreOut)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    genreOut.id = responseReader->text().toLong();
                }
                if (currentElement == "name")
                {
                    genreOut.name = responseReader->text().toString();
                }

                if (currentElement == "picture")
                {
                    genreOut.picture = responseReader->text().toString();
                }
                if (currentElement == "picture_small")
                {
                    genreOut.pictureSmall = responseReader->text().toString();
                }
                if (currentElement == "picture_medium")
                {
                    genreOut.pictureMedium = responseReader->text().toString();
                }
                if (currentElement == "picture_big")
                {
                    genreOut.pictureBig = responseReader->text().toString();
                }
                if (currentElement == "picture_xl")
                {
                    genreOut.pictureXl = responseReader->text().toString();
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "genre")
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializePlaylist(QXmlStreamReader *responseReader, Playlist &playlistOut)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    playlistOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "title")
                {
                    playlistOut.title = responseReader->text().toString();
                }

                else if (currentElement == "description")
                {
                    playlistOut.description = responseReader->text().toString();
                }
                else if (currentElement == "duration")
                {
                    playlistOut.duration = deserializeTime(responseReader->text().toInt());
                }
                else if (currentElement == "public")
                {
                    playlistOut.public_ = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "is_loved_track")
                {
                    playlistOut.lovedTrack = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "collaborative")
                {
                    playlistOut.collaborative = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "rating")
                {
                    playlistOut.rating = responseReader->text().toInt();
                }

                else if (currentElement == "nb_tracks")
                {
                    playlistOut.trackCount = responseReader->text().toInt();
                }
                else if (currentElement == "unseen_track_count")
                {
                    playlistOut.unseenTrackCount = responseReader->text().toInt();
                }
                else if (currentElement == "fans")
                {
                    playlistOut.fanCount = responseReader->text().toInt();
                }

                else if (currentElement == "link")
                {
                    playlistOut.link = responseReader->text().toString();
                }
                else if (currentElement == "share")
                {
                    playlistOut.share = responseReader->text().toString();
                }

                else if (currentElement == "picture")
                {
                    playlistOut.picture = responseReader->text().toString();
                }
                else if (currentElement == "picture_small")
                {
                    playlistOut.pictureSmall = responseReader->text().toString();
                }
                else if (currentElement == "picture_medium")
                {
                    playlistOut.pictureMedium = responseReader->text().toString();
                }
                else if (currentElement == "picture_big")
                {
                    playlistOut.pictureBig = responseReader->text().toString();
                }
                else if (currentElement == "picture_xl")
                {
                    playlistOut.pictureXl = responseReader->text().toString();
                }

                else if (currentElement == "checksum")
                {
                    playlistOut.checksum = responseReader->text().toString();
                }
                else if (currentElement == "creator")
                {
                    deserializeUser(responseReader, *playlistOut.creator, "creator");
                }
                else if (currentElement == "tracks")
                {
                    playlistOut.tracks = deserializeResponseTrack(responseReader);
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "playlist")
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializePodcast(QXmlStreamReader *responseReader, Podcast &podcastOut)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    podcastOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "title")
                {
                    podcastOut.title = responseReader->text().toString();
                }

                else if (currentElement == "description")
                {
                    podcastOut.description = responseReader->text().toString();
                }
                else if (currentElement == "available")
                {
                    podcastOut.available = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "rating")
                {
                    podcastOut.rating = responseReader->text().toInt();
                }
                else if (currentElement == "fans")
                {
                    podcastOut.fanCount = responseReader->text().toInt();
                }

                else if (currentElement == "link")
                {
                    podcastOut.link = responseReader->text().toString();
                }
                else if (currentElement == "share")
                {
                    podcastOut.share = responseReader->text().toString();
                }

                else if (currentElement == "picture")
                {
                    podcastOut.picture = responseReader->text().toString();
                }
                else if (currentElement == "picture_small")
                {
                    podcastOut.pictureSmall = responseReader->text().toString();
                }
                else if (currentElement == "picture_medium")
                {
                    podcastOut.pictureMedium = responseReader->text().toString();
                }
                else if (currentElement == "picture_big")
                {
                    podcastOut.pictureBig = responseReader->text().toString();
                }
                else if (currentElement == "picture_xl")
                {
                    podcastOut.pictureXl = responseReader->text().toString();
                }

                else if (currentElement == "position")
                {
                    podcastOut.position = responseReader->text().toInt();
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "podcast")
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializeRadio(QXmlStreamReader *responseReader, Radio &radioOut)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    radioOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "title")
                {
                    radioOut.title = responseReader->text().toString();
                }
                else if (currentElement == "description")
                {
                    radioOut.description = responseReader->text().toString();
                }
                else if (currentElement == "share")
                {
                    radioOut.share = responseReader->text().toString();
                }

                else if (currentElement == "picture")
                {
                    radioOut.picture = responseReader->text().toString();
                }
                else if (currentElement == "picture_small")
                {
                    radioOut.pictureSmall = responseReader->text().toString();
                }
                else if (currentElement == "picture_medium")
                {
                    radioOut.pictureMedium = responseReader->text().toString();
                }
                else if (currentElement == "picture_big")
                {
                    radioOut.pictureBig = responseReader->text().toString();
                }
                else if (currentElement == "picture_xl")
                {
                    radioOut.pictureXl = responseReader->text().toString();
                }
                else if (currentElement == "md5_image")
                {
                    radioOut.md5Image = responseReader->text().toString();
                }

                else if (currentElement == "tracklist")
                {
                    radioOut.tracklist = responseReader->text().toString();
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == "radio")
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializeTrack(QXmlStreamReader *responseReader, Track &trackOut, QString tag)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    trackOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "readable")
                {
                    trackOut.readable = responseReader->text().toInt() == 1;
                }

                else if (currentElement == "title")
                {
                    trackOut.title = responseReader->text().toString();
                }
                else if (currentElement == "title_short")
                {
                    trackOut.titleShort = responseReader->text().toString();
                }
                else if (currentElement == "title_version")
                {
                    trackOut.titleVersion = responseReader->text().toString();
                }

                else if (currentElement == "unseen")
                {
                    trackOut.unseen = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "isrc")
                {
                    trackOut.isrc = responseReader->text().toString();
                }

                else if (currentElement == "link")
                {
                    trackOut.link = responseReader->text().toString();
                }
                else if (currentElement == "share")
                {
                    trackOut.share = responseReader->text().toString();
                }

                else if (currentElement == "duration")
                {
                    trackOut.duration = deserializeTime(responseReader->text().toInt());
                }
                else if (currentElement == "track_position")
                {
                    trackOut.trackPosition = responseReader->text().toInt();
                }
                else if (currentElement == "disk_number")
                {
                    trackOut.diskNumber = responseReader->text().toInt();
                }
                else if (currentElement == "rank")
                {
                    trackOut.rank = responseReader->text().toInt();
                }
                else if (currentElement == "release_date")
                {
                    trackOut.releaseDate = QDate::fromString(responseReader->text().toString(), "YYYY-MM-DD");
                }

                else if (currentElement == "explicit_lyrics")
                {
                    trackOut.explicitLyrics = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "explicit_content_lyrics")
                {
                    trackOut.explicitContentLyrics = Explicity(responseReader->text().toInt());
                }
                else if (currentElement == "explicit_content_cover")
                {
                    trackOut.explicitContentCover = Explicity(responseReader->text().toInt());
                }

                else if (currentElement == "preview")
                {
                    trackOut.preview = responseReader->text().toString();
                }
                else if (currentElement == "bpm")
                {
                    trackOut.bpm = responseReader->text().toDouble();
                }
                else if (currentElement == "gain")
                {
                    trackOut.gain = responseReader->text().toDouble();
                }
                else if (currentElement == "available_countries")
                {
                    trackOut.availableCountries = QVector<QString>();
                    bool parsedCountries = false;
                    while (!responseReader->atEnd() && !parsedCountries)
                    {
                        switch (responseReader->readNext())
                        {
                        case QXmlStreamReader::StartElement:
                        {
                            currentElement = responseReader->name();
                            break;
                        }
                        case QXmlStreamReader::Characters:
                        {
                            if (currentElement == "item")
                            {
                                trackOut.availableCountries.append(responseReader->text().toString());
                            }
                            break;
                        }
                        case QXmlStreamReader::EndElement:
                        {
                            if (responseReader->name() == "available_countries")
                            {
                                parsedCountries = true;
                            }
                            break;
                        }
                        default:
                            break;
                        }
                    }
                }
                else if (currentElement == "alternative")
                {
                    trackOut.alternative = QSharedPointer<Track>(new Track());
                    deserializeTrack(responseReader, *trackOut.alternative, "alternative");
                }

                else if (currentElement == "artist")
                {
                    trackOut.artist = QSharedPointer<Artist>(new Artist());
                    deserializeArtist(responseReader, *trackOut.artist);
                }
                else if (currentElement == "album")
                {
                    trackOut.album = QSharedPointer<Album>(new Album());
                    deserializeAlbum(responseReader, *trackOut.album);
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == tag)
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    void deserializeUser(QXmlStreamReader *responseReader, User &userOut, QString tag)
    {
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "id")
                {
                    userOut.id = responseReader->text().toLong();
                }
                else if (currentElement == "name")
                {
                    userOut.name = responseReader->text().toString();
                }

                else if (currentElement == "lastname")
                {
                    userOut.lastname = responseReader->text().toString();
                }
                else if (currentElement == "firstname")
                {
                    userOut.firstname = responseReader->text().toString();
                }

                else if (currentElement == "email")
                {
                    userOut.email = responseReader->text().toString();
                }
                else if (currentElement == "status")
                {
                    userOut.status = responseReader->text().toInt();
                }
                else if (currentElement == "birthday")
                {
                    userOut.birthday = QDate::fromString(responseReader->text().toString(), "YYYY-MM-DD");
                }
                else if (currentElement == "gender")
                {
                    userOut.gender = responseReader->text() == "M" ? MALE : FEMALE;
                }
                else if (currentElement == "link")
                {
                    userOut.link = responseReader->text().toString();
                }

                else if (currentElement == "picture")
                {
                    userOut.picture = responseReader->text().toString();
                }
                else if (currentElement == "picture_small")
                {
                    userOut.pictureSmall = responseReader->text().toString();
                }
                else if (currentElement == "picture_medium")
                {
                    userOut.pictureMedium = responseReader->text().toString();
                }
                else if (currentElement == "picture_big")
                {
                    userOut.pictureBig = responseReader->text().toString();
                }
                else if (currentElement == "picture_xl")
                {
                    userOut.pictureXl = responseReader->text().toString();
                }

                else if (currentElement == "country")
                {
                    userOut.country = responseReader->text().toString();
                }
                else if (currentElement == "lang")
                {
                    userOut.lang = responseReader->text().toString();
                }

                else if (currentElement == "is_kid")
                {
                    userOut.isKid = responseReader->text().toInt() == 1;
                }
                else if (currentElement == "explicit_content_level")
                {
                    userOut.explicitContentLevel = EContentExplicity(responseReader->text().toInt());
                }
                else if (currentElement == "explicit_content_levels_available")
                {
                    userOut.explicitContentLevelsAvailable = QVector<EContentExplicity>();
                    bool parsedCountries = false;
                    while (!responseReader->atEnd() && !parsedCountries)
                    {
                        switch (responseReader->readNext())
                        {
                        case QXmlStreamReader::StartElement:
                        {
                            currentElement = responseReader->name();
                            break;
                        }
                        case QXmlStreamReader::Characters:
                        {
                            if (currentElement == "item")
                            {
                                 userOut.explicitContentLevelsAvailable.append(EContentExplicity(responseReader->text().toInt()));
                            }
                            break;
                        }
                        case QXmlStreamReader::EndElement:
                        {
                            if (responseReader->name() == "available_countries")
                            {
                                parsedCountries = true;
                            }
                            break;
                        }
                        default:
                            break;
                        }
                    }
                }

                else if (currentElement == "tracklist")
                {
                    userOut.tracklist = responseReader->text().toString();
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (responseReader->name() == tag)
                {
                    return;
                }
            }
            default:
                break;
            }
        }
    }

    PartialSearchResponse<Album> deserializePartialResponseAlbum(QXmlStreamReader *responseReader)
    {
        QVector<Album> albums;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "album")
                {
                    Album album;
                    deserializeAlbum(responseReader, album);
                    albums.append(album);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<Album>(albums, total, prev, next);
    }

    PartialSearchResponse<Artist> deserializePartialResponseArtist(QXmlStreamReader *responseReader)
    {
        QVector<Artist> artists;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "artist")
                {
                    Artist artist;
                    deserializeArtist(responseReader, artist);
                    artists.append(artist);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<Artist>(artists, total, prev, next);
    }

    PartialSearchResponse<Playlist> deserializePartialResponsePlaylist(QXmlStreamReader *responseReader)
    {
        QVector<Playlist> playlists;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "playlist")
                {
                    Playlist playlist;
                    deserializePlaylist(responseReader, playlist);
                    playlists.append(playlist);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<Playlist>(playlists, total, prev, next);
    }

    PartialSearchResponse<Podcast> deserializePartialResponsePodcast(QXmlStreamReader *responseReader)
    {
        QVector<Podcast> podcasts;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "podcast")
                {
                    Podcast podcast;
                    deserializePodcast(responseReader, podcast);
                    podcasts.append(podcast);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<Podcast>(podcasts, total, prev, next);
    }

    PartialSearchResponse<Radio> deserializePartialResponseRadio(QXmlStreamReader *responseReader)
    {
        QVector<Radio> radios;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "radio")
                {
                    Radio radio;
                    deserializeRadio(responseReader, radio);
                    radios.append(radio);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<Radio>(radios, total, prev, next);
    }

    PartialSearchResponse<Track> deserializePartialResponseTrack(QXmlStreamReader *responseReader)
    {
        QVector<Track> tracks;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "track")
                {
                    Track track;
                    deserializeTrack(responseReader, track);
                    tracks.append(track);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<Track>(tracks, total, prev, next);
    }

    PartialSearchResponse<User> deserializePartialResponseUser(QXmlStreamReader *responseReader)
    {
        QVector<User> users;
        int total = 0;
        QString prev, next;
        QStringRef currentElement;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
            {
                currentElement = responseReader->name();
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "user")
                {
                    User user;
                    deserializeUser(responseReader, user);
                    users.append(user);
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (currentElement == "total")
                {
                    total = responseReader->text().toInt();
                }
                else if (currentElement == "prev")
                {
                    prev = responseReader->text().toString();
                }
                else if (currentElement == "next")
                {
                    next = responseReader->text().toString();
                }
                break;
            }
            default:
                break;
            }
        }
        return PartialSearchResponse<User>(users, total, prev, next);
    }

    QVector<Album> deserializeResponseAlbum(QXmlStreamReader *responseReader)
    {
        QVector<Album> albums;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "album")
                {
                    Album album;
                    deserializeAlbum(responseReader, album);
                    albums.append(album);
                }
                break;
            case QXmlStreamReader::EndElement:
                if (responseReader->name() == "data")
                {
                    return albums;
                }
            default:
                break;
            }
        }
        return albums;
    }

    QVector<Artist> deserializeResponseArtist(QXmlStreamReader *responseReader)
    {
        QVector<Artist> artists;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "artist")
                {
                    Artist artist;
                    deserializeArtist(responseReader, artist);
                    artists.append(artist);
                }
                break;
            case QXmlStreamReader::EndElement:
                if (responseReader->name() == "data")
                {
                    return artists;
                }
            default:
                break;
            }
        }
        return artists;
    }

    QVector<Genre> deserializeResponseGenre(QXmlStreamReader *responseReader)
    {
        QVector<Genre> genres;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "genre")
                {
                    Genre genre;
                    deserializeGenre(responseReader, genre);
                    genres.append(genre);
                }
                break;
            case QXmlStreamReader::EndElement:
                if (responseReader->name() == "data")
                {
                    return genres;
                }
            default:
                break;
            }
        }
        return genres;
    }

    QVector<Radio> deserializeResponseRadio(QXmlStreamReader *responseReader)
    {
        QVector<Radio> radios;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "radio")
                {
                    Radio radio;
                    deserializeRadio(responseReader, radio);
                    radios.append(radio);
                }
                break;
            case QXmlStreamReader::EndElement:
                if (responseReader->name() == "data")
                {
                    return radios;
                }
            default:
                break;
            }
        }
        return radios;
    }

    QVector<Track> deserializeResponseTrack(QXmlStreamReader *responseReader)
    {
        QVector<Track> tracks;
        while (!responseReader->atEnd())
        {
            switch (responseReader->readNext())
            {
            case QXmlStreamReader::StartElement:
                if (responseReader->name() == "error")
                {
                    deserializeError(responseReader);
                }
                else if (responseReader->name() == "track")
                {
                    Track track;
                    deserializeTrack(responseReader, track);
                    tracks.append(track);
                }
            case QXmlStreamReader::EndElement:
                if (responseReader->name() == "data")
                {
                    return tracks;
                }
            default:
                break;
            }
        }
        return tracks;
    }

    QXmlStreamReader *tryReadXmlResponse(QNetworkReply *reply)
    {
        auto responseReader = new QXmlStreamReader(reply->readAll());
        reply->deleteLater();
        return responseReader;
    }
};
