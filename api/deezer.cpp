#include "deezer.h"

namespace api {
    Deezer::Deezer()
    {
        networkManager = new QNetworkAccessManager(this);
    }

    Deezer::~Deezer()
    {
        delete networkManager;
    }

    QNetworkRequest buildPartialRequest(const QString &urlStr, int index, int limit)
    {
        QUrlQuery urlParams;

        urlParams.addQueryItem("index", QString(index));
        urlParams.addQueryItem("limit", QString(limit));

        QUrl url(urlStr);
        url.setQuery(urlParams);

        return QNetworkRequest(url);
    }

    QNetworkRequest Deezer::buildSearchRequest(const QString &urlStr, const QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        QUrlQuery urlParams;

        urlParams.addQueryItem("q", query);
        urlParams.addQueryItem("strict", strict ? "on" : "off");
        urlParams.addQueryItem("index", QString(index));
        urlParams.addQueryItem("limit", QString(limit));

        if (order != SearchOrder::NONE)
        {
            urlParams.addQueryItem("order", serialize(order));
        }

        QUrl url(urlStr);
        url.setQuery(urlParams);

        return QNetworkRequest(url);
    }

    Album Deezer::getAlbum(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, ALBUM, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Album response;
        deserializeAlbum(responseJson, response);
        return response;
    }

    PartialSearchResponse<User> Deezer::getAlbumFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, ALBUM, QString(id), FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    QVector<Track> Deezer::getAlbumTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, ALBUM, QString(id), TRACKS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    Artist Deezer::getArtist(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, ARTIST, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Artist response;
        deserializeArtist(responseJson, response);
        return response;
    }

    QVector<Track> Deezer::getArtistTop(int id)
    {
        const QString url = QString("%1/%2/%3/top").arg(DEEZER_API_HOST, ALBUM, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getArtistAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, ARTIST, QString(id), ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<User> Deezer::getArtistFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, ARTIST, QString(id), FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getArtistRelated(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/related").arg(DEEZER_API_HOST, ARTIST, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getArtistPlaylists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, ARTIST, QString(id), PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getChartAlbums(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, CHART, QString(id), ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getChartArtists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, CHART, QString(id), ARTISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getChartPlaylists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, CHART, QString(id), PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Podcast> Deezer::getChartPodcasts(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/podcasts").arg(DEEZER_API_HOST, CHART, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePodcast(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getChartTracks(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, CHART, QString(id), TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    Chart Deezer::getEditorialCharts(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, EDITORIAL, QString(id), CHARTS);
        return Chart();
    }

    PartialSearchResponse<Album> Deezer::getEditorialReleases(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/releases").arg(DEEZER_API_HOST, CHART, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    QVector<Album> Deezer::getEditorialSelection(int id)
    {
        const QString url = QString("%1/%2/%3/selection").arg(DEEZER_API_HOST, EDITORIAL, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseAlbum(responseJson);
    }

    Genre Deezer::getGenre(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, GENRE, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Genre response;
        deserializeGenre(responseJson, response);
        return response;
    }

    QVector<Artist> Deezer::getGenreArtists(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, GENRE, QString(id), ARTISTS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseArtist(responseJson);
    }

    QVector<Radio> Deezer::getGenreRadios(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, GENRE, QString(id), RADIOS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseRadio(responseJson);
    }

    Infos Deezer::getInfos()
    {
        const QString url = QString("%1/infos").arg(DEEZER_API_HOST);
        return Infos();
    }

    Playlist Deezer::getPlaylist(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, PLAYLIST, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Playlist response;
        deserializePlaylist(responseJson, response);
        return response;
    }

    PartialSearchResponse<User> Deezer::getPlaylistFans(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, PLAYLIST, QString(id), FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    QVector<Track> Deezer::getPlaylistRadio(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, PLAYLIST, QString(id), TRACKS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    QVector<Track> Deezer::getPlaylistTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, PLAYLIST, QString(id), RADIO);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    QVector<Radio> Deezer::getRadio()
    {
        const QString url = QString("%1/%2").arg(DEEZER_API_HOST, RADIO);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseRadio(responseJson);
    }

    Radio Deezer::getRadio(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, RADIO, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Radio response;
        deserializeRadio(responseJson, response);
        return response;
    }

    QVector<Genre> Deezer::getRadioGenres()
    {
        const QString url = QString("%1/%2/genres").arg(DEEZER_API_HOST, RADIO);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseGenre(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getRadioTop(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/top").arg(DEEZER_API_HOST, RADIO);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    QVector<Track> Deezer::getRadioTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, RADIO, QString(id), TRACKS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getRadioLists(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/lists").arg(DEEZER_API_HOST, RADIO);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    Track Deezer::getTrack(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, TRACK, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Track response;
        deserializeTrack(responseJson, response);
        return response;
    }

    User Deezer::getUser(int id)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, USER, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        User response;
        deserializeUser(responseJson, response);
        return response;
    }

    PartialSearchResponse<Album> Deezer::getUserChartsAlbums(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), CHARTS, ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getUserChartsPlaylists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), CHARTS, PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserChartsTracks(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), CHARTS, TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getUserFavoriteAlbums(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, USER, QString(id), ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getUserFavoriteArtists(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, USER, QString(id), ARTISTS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getUserFavoriteRadios(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, USER, QString(id), RADIOS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserFavoriteTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, USER, QString(id), TRACKS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    QVector<Folder> Deezer::getUserFolders()
    {
        const QString url = QString("%1/%2/me/folders").arg(DEEZER_API_HOST, USER);
        return QVector<Folder>();
    }
    PartialSearchResponse<User> Deezer::getUserFollowings(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/followings").arg(DEEZER_API_HOST, USER, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    PartialSearchResponse<User> Deezer::getUserFollowers(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/followers").arg(DEEZER_API_HOST, USER, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    QVector<Track> Deezer::getUserFlow(int id)
    {
        const QString url = QString("%1/%2/%3/flow").arg(DEEZER_API_HOST, USER, QString(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserHistory(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/history").arg(DEEZER_API_HOST, USER, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    Options Deezer::getUserOptions()
    {
        return Options();
    }

    QVector<QString> Deezer::getUserPermissions()
    {
        const QString url = QString("%1/%2/me/permissions").arg(DEEZER_API_HOST, USER);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        if (!(responseJson.contains("data") && responseJson["data"].isArray()))
        {
            return QVector<QString>();
        }

        QJsonArray permissionsJsonArray = responseJson["data"].toArray();
        QVector<QString> permissions(permissionsJsonArray.size());
        for (int i = 0; i < permissionsJsonArray.size(); i++)
        {
            permissions[i] = permissionsJsonArray[i].toString();
        }
        return permissions;
    }

    PartialSearchResponse<Track> Deezer::getUserPersonalSongs(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/personal_songs").arg(DEEZER_API_HOST, USER, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getUserPlaylists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4").arg(DEEZER_API_HOST, USER, QString(id), PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getUserRecommendedAlbums(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), RECOMMENDATIONS, ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getUserRecommendedArtists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), RECOMMENDATIONS, ARTISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getUserRecommendedPlaylists(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), RECOMMENDATIONS, PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getUserRecommendedRadios(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), RECOMMENDATIONS, RADIOS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getUserRecommendedReleases(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/releases").arg(DEEZER_API_HOST, USER, QString(id), RECOMMENDATIONS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserRecommendedTracks(int id, int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(DEEZER_API_HOST, USER, QString(id), RECOMMENDATIONS, TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Track> Deezer::search(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, TRACKS);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Track> Deezer::search(AdvancedSearchQuery query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, TRACKS);
        QNetworkRequest request = buildSearchRequest(url, query.toString(), index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Album> Deezer::searchAlbums(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, ALBUM);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::searchArtists(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, ARTIST);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::searchPlaylists(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, PLAYLIST);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::searchRadio(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, RADIO);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    PartialSearchResponse<Track> Deezer::searchTracks(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, TRACKS);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<User> Deezer::searchUsers(QString &query, int index = 0, int limit = 25, bool strict = false, SearchOrder order = SearchOrder::NONE)
    {
        const QString url = QString("%1/%2/%3").arg(DEEZER_API_HOST, SEARCH, USER);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }
}
