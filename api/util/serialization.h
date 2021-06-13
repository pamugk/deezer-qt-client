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
    namespace
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

        void deserializeAlbum(QJsonObject &jsonObj, Album& albumOut)
        {
            if (jsonObj.contains("id"))
            {
                albumOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("title"))
            {
                albumOut.title = jsonObj["title"].toString();
            }
            if (jsonObj.contains("upc"))
            {
                albumOut.upc = jsonObj["upc"].toString();
            }

            if (jsonObj.contains("link"))
            {
                albumOut.link = jsonObj["link"].toString();
            }
            if (jsonObj.contains("share"))
            {
                albumOut.share = jsonObj["share"].toString();
            }

            if (jsonObj.contains("cover"))
            {
                albumOut.cover = jsonObj["cover"].toString();
            }
            if (jsonObj.contains("cover_small"))
            {
                albumOut.coverSmall = jsonObj["cover_small"].toString();
            }
            if (jsonObj.contains("cover_medium"))
            {
                albumOut.coverMedium = jsonObj["cover_medium"].toString();
            }
            if (jsonObj.contains("cover_big"))
            {
                albumOut.coverBig = jsonObj["cover_big"].toString();
            }
            if (jsonObj.contains("cover_xl"))
            {
                albumOut.coverXl = jsonObj["cover_xl"].toString();
            }
            if (jsonObj.contains("md5_image"))
            {
                albumOut.md5Image = jsonObj["md5_image"].toString();
            }

            if (jsonObj.contains("genre_id"))
            {
                albumOut.genreId = jsonObj["genre_id"].toInt();
            }
            if (jsonObj.contains("genres"))
            {
                QJsonObject genresJson = jsonObj["genres"].toObject();
                albumOut.genres = deserializeResponseGenre(genresJson);
            }

            if (jsonObj.contains("nb_tracks"))
            {
                albumOut.trackCount = jsonObj["nb_tracks"].toInt();
            }
            if (jsonObj.contains("duration"))
            {
                albumOut.duration = jsonObj["duration"].toInt();
            }
            if (jsonObj.contains("fans"))
            {
                albumOut.fanCount = jsonObj["fans"].toInt();
            }
            if (jsonObj.contains("rating"))
            {
                albumOut.rating = jsonObj["rating"].toInt();
            }
            if (jsonObj.contains("release_date"))
            {
                albumOut.releaseDate = QDate::fromString(jsonObj["release_date"].toString(), "YYYY-MM-DD");
            }

            if (jsonObj.contains("record_type"))
            {
                albumOut.recordType = jsonObj["record_type"].toString();
            }
            if (jsonObj.contains("available"))
            {
                albumOut.available = jsonObj["available"].toBool();
            }
            if (jsonObj.contains("alternative"))
            {
                QJsonObject alternativeJson = jsonObj["alternative"].toObject();
                albumOut.alternative = new Album();
                deserializeAlbum(alternativeJson, *albumOut.alternative);
            }

            if (jsonObj.contains("tracklist"))
            {
                albumOut.tracklist = jsonObj["tracklist"].toString();
            }

            if (jsonObj.contains("explicit_lyrics"))
            {
                albumOut.explicitLyrics = jsonObj["explicit_lyrics"].toBool();
            }
            if (jsonObj.contains("explicit_content_lyrics"))
            {
                albumOut.explicitContentLyrics = Explicity(jsonObj["explicit_content_lyrics"].toInt());
            }
            if (jsonObj.contains("explicit_content_cover"))
            {
                albumOut.explicitContentCover = Explicity(jsonObj["explicit_content_cover"].toInt());
            }

            if (jsonObj.contains("position"))
            {
                albumOut.position = jsonObj["position"].toInt();
            }
            if (jsonObj.contains("contributors"))
            {
                QJsonObject contributorsJson = jsonObj["contributors"].toObject();
                albumOut.contributors = deserializeResponseArtist(contributorsJson);
            }
            if (jsonObj.contains("artist"))
            {
                QJsonObject artistJson = jsonObj["artist"].toObject();
                albumOut.artist = new Artist();
                deserializeArtist(artistJson, *albumOut.artist);
            }
            if (jsonObj.contains("tracks"))
            {
                QJsonObject tracksJson = jsonObj["tracks"].toObject();
                albumOut.tracks = deserializeResponseTrack(tracksJson);
            }
        }

        void deserializeArtist(QJsonObject &jsonObj, Artist& artistOut)
        {
            if (jsonObj.contains("id"))
            {
                artistOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("name"))
            {
                artistOut.name = jsonObj["name"].toString();
            }

            if (jsonObj.contains("link"))
            {
                artistOut.link = jsonObj["link"].toString();
            }
            if (jsonObj.contains("share"))
            {
                artistOut.share = jsonObj["share"].toString();
            }

            if (jsonObj.contains("picture"))
            {
                artistOut.picture = jsonObj["picture"].toString();
            }
            if (jsonObj.contains("picture_small"))
            {
                artistOut.pictureSmall = jsonObj["picture_small"].toString();
            }
            if (jsonObj.contains("picture_medium"))
            {
                artistOut.pictureMedium = jsonObj["picture_medium"].toString();
            }
            if (jsonObj.contains("picture_big"))
            {
                artistOut.pictureBig = jsonObj["picture_big"].toString();
            }
            if (jsonObj.contains("picture_xl"))
            {
                artistOut.pictureXl = jsonObj["picture_xl"].toString();
            }

            if (jsonObj.contains("artistOut"))
            {
                artistOut.albumCount = jsonObj["artistOut"].toInt();
            }
            if (jsonObj.contains("nb_fan"))
            {
                artistOut.fanCount = jsonObj["nb_fan"].toInt();
            }
            if (jsonObj.contains("radio"))
            {
                artistOut.radio = jsonObj["radio"].toBool();
            }
            if (jsonObj.contains("tracklist"))
            {
                artistOut.tracklist = jsonObj["tracklist"].toString();
            }
        }

        void deserializeGenre(QJsonObject &jsonObj, Genre &genreOut)
        {
            if (jsonObj.contains("id"))
            {
                genreOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("name"))
            {
                genreOut.name = jsonObj["name"].toString();
            }

            if (jsonObj.contains("picture"))
            {
                genreOut.picture = jsonObj["picture"].toString();
            }
            if (jsonObj.contains("picture_small"))
            {
                genreOut.pictureSmall = jsonObj["picture_small"].toString();
            }
            if (jsonObj.contains("picture_medium"))
            {
                genreOut.pictureMedium = jsonObj["picture_medium"].toString();
            }
            if (jsonObj.contains("picture_big"))
            {
                genreOut.pictureBig = jsonObj["picture_big"].toString();
            }
            if (jsonObj.contains("picture_xl"))
            {
                genreOut.pictureXl = jsonObj["picture_xl"].toString();
            }
        }

        void deserializePlaylist(QJsonObject &jsonObj, Playlist &playlistOut)
        {
            if (jsonObj.contains("id"))
            {
                playlistOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("title"))
            {
                playlistOut.title = jsonObj["title"].toString();
            }

            if (jsonObj.contains("description"))
            {
                playlistOut.description = jsonObj["description"].toString();
            }
            if (jsonObj.contains("duration"))
            {
                playlistOut.duration = jsonObj["duration"].toInt();
            }
            if (jsonObj.contains("public"))
            {
                playlistOut.public_ = jsonObj["public"].toBool();
            }
            if (jsonObj.contains("is_loved_track"))
            {
                playlistOut.lovedTrack = jsonObj["is_loved_track"].toBool();
            }
            if (jsonObj.contains("collaborative"))
            {
                playlistOut.collaborative = jsonObj["collaborative"].toBool();
            }
            if (jsonObj.contains("rating"))
            {
                playlistOut.rating = jsonObj["rating"].toInt();
            }

            if (jsonObj.contains("nb_tracks"))
            {
                playlistOut.trackCount = jsonObj["nb_tracks"].toInt();
            }
            if (jsonObj.contains("unseen_track_count"))
            {
                playlistOut.unseenTrackCount = jsonObj["unseen_track_count"].toInt();
            }
            if (jsonObj.contains("fans"))
            {
                playlistOut.fanCount = jsonObj["fans"].toInt();
            }

            if (jsonObj.contains("link"))
            {
                playlistOut.link = jsonObj["link"].toString();
            }
            if (jsonObj.contains("share"))
            {
                playlistOut.share = jsonObj["share"].toString();
            }

            if (jsonObj.contains("picture"))
            {
                playlistOut.picture = jsonObj["picture"].toString();
            }
            if (jsonObj.contains("picture_small"))
            {
                playlistOut.pictureSmall = jsonObj["picture_small"].toString();
            }
            if (jsonObj.contains("picture_medium"))
            {
                playlistOut.pictureMedium = jsonObj["picture_medium"].toString();
            }
            if (jsonObj.contains("picture_big"))
            {
                playlistOut.pictureBig = jsonObj["picture_big"].toString();
            }
            if (jsonObj.contains("picture_xl"))
            {
                playlistOut.pictureXl = jsonObj["picture_xl"].toString();
            }

            if (jsonObj.contains("checksum"))
            {
                playlistOut.checksum = jsonObj["checksum"].toString();
            }
            if (jsonObj.contains("creator"))
            {
                QJsonObject userJson = jsonObj["creator"].toObject();
                playlistOut.creator = new User();
                deserializeUser(userJson, *playlistOut.creator);
            }
            if (jsonObj.contains("tracks"))
            {
                QJsonObject tracksJson = jsonObj["tracks"].toObject();
                playlistOut.tracks = deserializeResponseTrack(tracksJson);
            }
        }

        void deserializePodcast(QJsonObject &jsonObj, Podcast &podcastOut)
        {
            if (jsonObj.contains("id"))
            {
                podcastOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("title"))
            {
                podcastOut.title = jsonObj["title"].toString();
            }

            if (jsonObj.contains("description"))
            {
                podcastOut.description = jsonObj["description"].toString();
            }
            if (jsonObj.contains("available"))
            {
                podcastOut.available = jsonObj["available"].toBool();
            }
            if (jsonObj.contains("rating"))
            {
                podcastOut.rating = jsonObj["rating"].toInt();
            }
            if (jsonObj.contains("fans"))
            {
                podcastOut.fanCount = jsonObj["fans"].toInt();
            }

            if (jsonObj.contains("link"))
            {
                podcastOut.link = jsonObj["link"].toString();
            }
            if (jsonObj.contains("share"))
            {
                podcastOut.share = jsonObj["share"].toString();
            }

            if (jsonObj.contains("picture"))
            {
                podcastOut.picture = jsonObj["picture"].toString();
            }
            if (jsonObj.contains("picture_small"))
            {
                podcastOut.pictureSmall = jsonObj["picture_small"].toString();
            }
            if (jsonObj.contains("picture_medium"))
            {
                podcastOut.pictureMedium = jsonObj["picture_medium"].toString();
            }
            if (jsonObj.contains("picture_big"))
            {
                podcastOut.pictureBig = jsonObj["picture_big"].toString();
            }
            if (jsonObj.contains("picture_xl"))
            {
                podcastOut.pictureXl = jsonObj["picture_xl"].toString();
            }

            if (jsonObj.contains("position"))
            {
                podcastOut.position = jsonObj["position"].toInt();
            }
        }

        void deserializeRadio(QJsonObject &jsonObj, Radio &radioOut)
        {
            if (jsonObj.contains("id"))
            {
                radioOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("title"))
            {
                radioOut.title = jsonObj["title"].toString();
            }
            if (jsonObj.contains("description"))
            {
                radioOut.description = jsonObj["description"].toString();
            }
            if (jsonObj.contains("share"))
            {
                radioOut.share = jsonObj["share"].toString();
            }

            if (jsonObj.contains("picture"))
            {
                radioOut.picture = jsonObj["picture"].toString();
            }
            if (jsonObj.contains("picture_small"))
            {
                radioOut.pictureSmall = jsonObj["picture_small"].toString();
            }
            if (jsonObj.contains("picture_medium"))
            {
                radioOut.pictureMedium = jsonObj["picture_medium"].toString();
            }
            if (jsonObj.contains("picture_big"))
            {
                radioOut.pictureBig = jsonObj["picture_big"].toString();
            }
            if (jsonObj.contains("picture_xl"))
            {
                radioOut.pictureXl = jsonObj["picture_xl"].toString();
            }
            if (jsonObj.contains("md5_image"))
            {
                radioOut.md5Image = jsonObj["md5_image"].toString();
            }

            if (jsonObj.contains("tracklist"))
            {
                radioOut.tracklist = jsonObj["tracklist"].toString();
            }
        }

        void deserializeTrack(QJsonObject &jsonObj, Track &trackOut)
        {
            if (jsonObj.contains("id"))
            {
                trackOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("readable"))
            {
                trackOut.readable = jsonObj["readable"].toBool();
            }

            if (jsonObj.contains("title"))
            {
                trackOut.title = jsonObj["title"].toString();
            }
            if (jsonObj.contains("title_short"))
            {
                trackOut.titleShort = jsonObj["title_short"].toString();
            }
            if (jsonObj.contains("title_version"))
            {
                trackOut.titleVersion = jsonObj["title_version"].toString();
            }

            if (jsonObj.contains("unseen"))
            {
                trackOut.unseen = jsonObj["unseen"].toBool();
            }
            if (jsonObj.contains("isrc"))
            {
                trackOut.isrc = jsonObj["isrc"].toString();
            }

            if (jsonObj.contains("link"))
            {
                trackOut.link = jsonObj["link"].toString();
            }
            if (jsonObj.contains("share"))
            {
                trackOut.share = jsonObj["share"].toString();
            }

            if (jsonObj.contains("duration"))
            {
                trackOut.duration = jsonObj["duration"].toInt();
            }
            if (jsonObj.contains("track_position"))
            {
                trackOut.trackPosition = jsonObj["track_position"].toInt();
            }
            if (jsonObj.contains("disk_number"))
            {
                trackOut.diskNumber = jsonObj["disk_number"].toInt();
            }
            if (jsonObj.contains("rank"))
            {
                trackOut.rank = jsonObj["rank"].toInt();
            }
            if (jsonObj.contains("release_date"))
            {
                trackOut.releaseDate = QDate::fromString(jsonObj["release_date"].toString(), "YYYY-MM-DD");
            }

            if (jsonObj.contains("explicit_lyrics"))
            {
                trackOut.explicitLyrics = jsonObj["explicit_lyrics"].toBool();
            }
            if (jsonObj.contains("explicit_content_lyrics"))
            {
                trackOut.explicitContentLyrics = Explicity(jsonObj["explicit_content_lyrics"].toInt());
            }
            if (jsonObj.contains("explicit_content_cover"))
            {
                trackOut.explicitContentCover = Explicity(jsonObj["explicit_content_cover"].toInt());
            }

            if (jsonObj.contains("preview"))
            {
                trackOut.preview = jsonObj["preview"].toString();
            }
            if (jsonObj.contains("bpm"))
            {
                trackOut.bpm = jsonObj["bpm"].toDouble();
            }
            if (jsonObj.contains("gain"))
            {
                trackOut.gain = jsonObj["gain"].toDouble();
            }
            if (jsonObj.contains("available_countries"))
            {
                QJsonArray countriesJson = jsonObj["available_countries"].toArray();
                trackOut.availableCountries = QVector<QString>();
                for (int i = 0; i < countriesJson.size(); i++)
                {
                    trackOut.availableCountries[i] = countriesJson[i].toString();
                }

            }
            if (jsonObj.contains("alternative"))
            {
                QJsonObject alternativeJson = jsonObj["alternative"].toObject();
                trackOut.alternative = new Track();
                deserializeTrack(alternativeJson, *trackOut.alternative);
            }

            if (jsonObj.contains("artist"))
            {
                QJsonObject artistJson = jsonObj["artist"].toObject();
                trackOut.artist = new Artist();
                deserializeArtist(artistJson, *trackOut.artist);
            }
            if (jsonObj.contains("album"))
            {
                QJsonObject albumJson = jsonObj["album"].toObject();
                trackOut.album = new Album();
                deserializeAlbum(albumJson, *trackOut.album);
            }
        }

        void deserializeUser(QJsonObject &jsonObj, User &userOut)
        {
            if (jsonObj.contains("id"))
            {
                userOut.id = jsonObj["id"].toInt();
            }
            if (jsonObj.contains("name"))
            {
                userOut.name = jsonObj["name"].toString();
            }

            if (jsonObj.contains("lastname"))
            {
                userOut.lastname = jsonObj["lastname"].toString();
            }
            if (jsonObj.contains("firstname"))
            {
                userOut.firstname = jsonObj["firstname"].toString();
            }

            if (jsonObj.contains("email"))
            {
                userOut.email = jsonObj["email"].toString();
            }
            if (jsonObj.contains("status"))
            {
                userOut.status = jsonObj["status"].toInt();
            }
            if (jsonObj.contains("birthday"))
            {
                userOut.birthday = QDate::fromString(jsonObj["birthday"].toString(), "YYYY-MM-DD");
            }
            if (jsonObj.contains("gender"))
            {
                QString genderStr = jsonObj["gender"].toString();
                userOut.gender = genderStr == "M" ? MALE : FEMALE;
            }
            if (jsonObj.contains("link"))
            {
                userOut.link = jsonObj["link"].toString();
            }

            if (jsonObj.contains("picture"))
            {
                userOut.picture = jsonObj["picture"].toString();
            }
            if (jsonObj.contains("picture_small"))
            {
                userOut.pictureSmall = jsonObj["picture_small"].toString();
            }
            if (jsonObj.contains("picture_medium"))
            {
                userOut.pictureMedium = jsonObj["picture_medium"].toString();
            }
            if (jsonObj.contains("picture_big"))
            {
                userOut.pictureBig = jsonObj["picture_big"].toString();
            }
            if (jsonObj.contains("picture_xl"))
            {
                userOut.pictureXl = jsonObj["picture_xl"].toString();
            }

            if (jsonObj.contains("country"))
            {
                userOut.country = jsonObj["country"].toString();
            }
            if (jsonObj.contains("lang"))
            {
                userOut.lang = jsonObj["lang"].toString();
            }

            if (jsonObj.contains("is_kid"))
            {
                userOut.isKid = jsonObj["is_kid"].toBool();
            }
            if (jsonObj.contains("explicit_content_level"))
            {
                userOut.explicitContentLevel = EContentExplicity(jsonObj["explicit_content_level"].toInt());
            }
            if (jsonObj.contains("explicit_content_levels_available"))
            {
                QJsonArray explicitContentLevelsJson = jsonObj["explicit_content_level"].toArray();
                userOut.explicitContentLevelsAvailable = QVector<EContentExplicity>(explicitContentLevelsJson.size());
                for (int i = 0; i < explicitContentLevelsJson.size(); i++)
                {
                    userOut.explicitContentLevelsAvailable[i] = EContentExplicity(explicitContentLevelsJson[i].toInt());
                }
            }

            if (jsonObj.contains("tracklist"))
            {
                userOut.tracklist = jsonObj["tracklist"].toString();
            }
        }

        template<typename T>
        PartialSearchResponse<T> deserializePartialResponse(QJsonObject &jsonObj, QJsonArray &jsonData)
        {
            return PartialSearchResponse<T>(
                        QVector<T>(jsonData.size()),
                        jsonObj.keys().contains("total") ? jsonObj["total"].toInt() : 0,
                        jsonObj.keys().contains("prev") ? QString(jsonObj["prev"].toString()) : QString(),
                        jsonObj.keys().contains("next") ? QString(jsonObj["next"].toString()) : QString());
        }

        PartialSearchResponse<Album> deserializePartialResponseAlbum(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<Album> response = deserializePartialResponse<Album>(jsonObj, jsonData);
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject albumObj = jsonData[i].toObject();
                deserializeAlbum(albumObj, response.getData()[i]);

            }
            return response;
        }

        PartialSearchResponse<Artist> deserializePartialResponseArtist(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<Artist> response = deserializePartialResponse<Artist>(jsonObj, jsonData);
            QVector<Artist> data = response.getData();
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject artistObj = jsonData[i].toObject();
                deserializeArtist(artistObj, data[i]);
            }
            return response;
        }

        PartialSearchResponse<Playlist> deserializePartialResponsePlaylist(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<Playlist> response = deserializePartialResponse<Playlist>(jsonObj, jsonData);
            QVector<Playlist> data = response.getData();
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject playlistObj = jsonData[i].toObject();
                deserializePlaylist(playlistObj, data[i]);

            }
            return response;
        }

        PartialSearchResponse<Podcast> deserializePartialResponsePodcast(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<Podcast> response = deserializePartialResponse<Podcast>(jsonObj, jsonData);
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject podcastObj = jsonData[i].toObject();
                deserializePodcast(podcastObj, response.getData()[i]);

            }
            return response;
        }

        PartialSearchResponse<Radio> deserializePartialResponseRadio(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<Radio> response = deserializePartialResponse<Radio>(jsonObj, jsonData);
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject radioObj = jsonData[i].toObject();
                deserializeRadio(radioObj, response.getData()[i]);
            }
            return response;
        }

        PartialSearchResponse<Track> deserializePartialResponseTrack(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<Track> response = deserializePartialResponse<Track>(jsonObj, jsonData);
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject trackObj = jsonData[i].toObject();
                deserializeTrack(trackObj, response.getData()[i]);
            }
            return response;
        }

        PartialSearchResponse<User> deserializePartialResponseUser(QJsonObject &jsonObj)
        {
            QJsonArray jsonData = jsonObj["data"].toArray();
            PartialSearchResponse<User> response = deserializePartialResponse<User>(jsonObj, jsonData);
            for (int i = 0; i < jsonData.size(); i++)
            {
                QJsonObject trackObj = jsonData[i].toObject();
                deserializeUser(trackObj, response.getData()[i]);
            }
            return response;
        }

        QVector<Album> deserializeResponseAlbum(QJsonObject &jsonObj)
        {
            if (!(jsonObj.contains("data") && jsonObj["data"].isArray()))
            {
                return QVector<Album>();
            }

            QJsonArray albumsJson = jsonObj["data"].toArray();
            QVector<Album> albums(albumsJson.size());
            for (int i = 0; i < albumsJson.size(); i++)
            {
                QJsonObject albumJson = albumsJson[i].toObject();
                deserializeAlbum(albumJson, albums[i]);
            }
            return albums;
        }

        QVector<Artist> deserializeResponseArtist(QJsonObject &jsonObj)
        {
            if (!(jsonObj.contains("data") && jsonObj["data"].isArray()))
            {
                return QVector<Artist>();
            }

            QJsonArray artistsJson = jsonObj["data"].toArray();
            QVector<Artist> artists(artistsJson.size());
            for (int i = 0; i < artistsJson.size(); i++)
            {
                QJsonObject albumJson = artistsJson[i].toObject();
                deserializeArtist(albumJson, artists[i]);
            }
            return artists;
        }

        QVector<Genre> deserializeResponseGenre(QJsonObject &jsonObj)
        {
            if (!(jsonObj.contains("data") && jsonObj["data"].isArray()))
            {
                return QVector<Genre>();
            }

            QJsonArray genresJson = jsonObj["data"].toArray();
            QVector<Genre> genres(genresJson.size());
            for (int i = 0; i < genresJson.size(); i++)
            {
                QJsonObject genreJson = genresJson[i].toObject();
                deserializeGenre(genreJson, genres[i]);
            }
            return genres;
        }

        QVector<Radio> deserializeResponseRadio(QJsonObject& jsonObj)
        {
            if (!(jsonObj.contains("data") && jsonObj["data"].isArray()))
            {
                return QVector<Radio>();
            }

            QJsonArray radiosJson = jsonObj["data"].toArray();
            QVector<Radio> radios(radiosJson.size());
            for (int i = 0; i < radiosJson.size(); i++)
            {
                QJsonObject radioJson = radiosJson[i].toObject();
                deserializeRadio(radioJson, radios[i]);
            }
            return radios;
        }

        QVector<Track> deserializeResponseTrack(QJsonObject &jsonObj)
        {
            if (!(jsonObj.contains("data") && jsonObj["data"].isArray()))
            {
                return QVector<Track>();
            }

            QJsonArray tracksJson = jsonObj["data"].toArray();
            QVector<Track> tracks(tracksJson.size());
            for (int i = 0; i < tracksJson.size(); i++)
            {
                QJsonObject trackJson = tracksJson[i].toObject();
                deserializeTrack(trackJson, tracks[i]);
            }
            return tracks;
        }

        QString serialize(SearchOrder order)
        {
            switch (order) {
            case NONE:
                break;
            case RANKING:
                return "RANKING";
            case TRACK_ASC:
                return "TRACK_ASC";
            case TRACK_DESC:
                return "TRACK_DESC";
            case ARTIST_ASC:
                return "ARTIST_ASC";
            case ARTIST_DESC:
                return "ARTIST_DESC";
            case ALBUM_ASC:
                return "ALBUM_ASC";
            case ALBUM_DESC:
                return "ALBUM_DESC";
            case RATING_ASC:
                return "RATING_ASC";
            case RATING_DESC:
                return "RATING_DESC";
            case DURATION_ASC:
                return "DURATION_ASC";
            case DURATION_DESC:
                return "DURATION_DESC";
            }
            return QString();
        }
    }
}
#endif // SERIALIZATION_H
