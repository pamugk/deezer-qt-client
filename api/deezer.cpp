#include "deezer.h"

namespace api {

    const QString Deezer::DEEZER_API_HOST = "https://api.deezer.com";

    const QString Deezer::ALBUM = "album";
    const QString Deezer::ARTIST = "artist";
    const QString Deezer::CHART = "chart";
    const QString Deezer::EDITORIAL = "editorial";
    const QString Deezer::GENRE = "genre";
    const QString Deezer::PLAYLIST = "playlist";
    const QString Deezer::RADIO = "radio";
    const QString Deezer::SEARCH = "search";
    const QString Deezer::TRACK = "track";
    const QString Deezer::USER = "user";

    const QString Deezer::ALBUMS = "albums";
    const QString Deezer::ARTISTS = "artists";
    const QString Deezer::CHARTS = "charts";
    const QString Deezer::FANS = "fans";
    const QString Deezer::PLAYLISTS = "playlists";
    const QString Deezer::RADIOS = "radios";
    const QString Deezer::RECOMMENDATIONS = "recommendations";
    const QString Deezer::TRACKS = "tracks";

    Deezer::Deezer()
    {
        networkManager = new QNetworkAccessManager(this);
    }

    Deezer::~Deezer()
    {
        delete networkManager;
    }

    QNetworkRequest Deezer::buildPartialRequest(const QString &urlStr, int index, int limit)
    {
        QUrlQuery urlParams;

        urlParams.addQueryItem("index", QString::number(index));
        urlParams.addQueryItem("limit", QString::number(limit));

        QUrl url(urlStr);
        url.setQuery(urlParams);

        return QNetworkRequest(url);
    }

    QNetworkRequest Deezer::buildSearchRequest(const QString &urlStr, const QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        QUrlQuery urlParams;

        urlParams.addQueryItem("q", query);
        urlParams.addQueryItem("strict", strict ? "on" : "off");
        urlParams.addQueryItem("index", QString::number(index));
        urlParams.addQueryItem("limit", QString::number(limit));

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
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id));
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
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id), Deezer::FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    QVector<Track> Deezer::getAlbumTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    Artist Deezer::getArtist(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id));
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
        const QString url = QString("%1/%2/%3/top").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getArtistAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<User> Deezer::getArtistFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getArtistRelated(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/related").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getArtistPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getChartAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getChartArtists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::ARTISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getChartPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Podcast> Deezer::getChartPodcasts(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/podcasts").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePodcast(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getChartTracks(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    Chart Deezer::getEditorialCharts(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::EDITORIAL, QString::number(id), Deezer::CHARTS);
        return Chart();
    }

    PartialSearchResponse<Album> Deezer::getEditorialReleases(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/releases").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    QVector<Album> Deezer::getEditorialSelection(int id)
    {
        const QString url = QString("%1/%2/%3/selection").arg(Deezer::DEEZER_API_HOST, Deezer::EDITORIAL, QString::number(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseAlbum(responseJson);
    }

    Genre Deezer::getGenre(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id));
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
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id), Deezer::ARTISTS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseArtist(responseJson);
    }

    QVector<Radio> Deezer::getGenreRadios(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id), Deezer::RADIOS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseRadio(responseJson);
    }

    Infos Deezer::getInfos()
    {
        const QString url = QString("%1/infos").arg(Deezer::DEEZER_API_HOST);
        return Infos();
    }

    Playlist Deezer::getPlaylist(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        Playlist response;
        deserializePlaylist(responseJson, response);
        return response;
    }

    PartialSearchResponse<User> Deezer::getPlaylistFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    QVector<Track> Deezer::getPlaylistRadio(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    QVector<Track> Deezer::getPlaylistTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::RADIO);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    QVector<Radio> Deezer::getRadio()
    {
        const QString url = QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseRadio(responseJson);
    }

    Radio Deezer::getRadio(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO, QString::number(id));
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
        const QString url = QString("%1/%2/genres").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseGenre(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getRadioTop(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/top").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    QVector<Track> Deezer::getRadioTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getRadioLists(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/lists").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    Track Deezer::getTrack(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::TRACK, QString::number(id));
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
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        User response;
        deserializeUser(responseJson, response);
        return response;
    }

    PartialSearchResponse<Album> Deezer::getUserChartsAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getUserChartsPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserChartsTracks(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getUserFavoriteAlbums(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getUserFavoriteArtists(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::ARTISTS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getUserFavoriteRadios(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RADIOS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserFavoriteTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    QVector<Folder> Deezer::getUserFolders()
    {
        const QString url = QString("%1/%2/me/folders").arg(Deezer::DEEZER_API_HOST, Deezer::USER);
        return QVector<Folder>();
    }
    PartialSearchResponse<User> Deezer::getUserFollowings(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/followings").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    PartialSearchResponse<User> Deezer::getUserFollowers(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/followers").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }

    QVector<Track> Deezer::getUserFlow(int id)
    {
        const QString url = QString("%1/%2/%3/flow").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        QNetworkRequest request(url);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();

        return deserializeResponseTrack(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserHistory(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/history").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
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
        const QString url = QString("%1/%2/me/permissions").arg(Deezer::DEEZER_API_HOST,Deezer:: USER);
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

    PartialSearchResponse<Track> Deezer::getUserPersonalSongs(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/personal_songs").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getUserPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getUserRecommendedAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::ALBUMS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::getUserRecommendedArtists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::ARTISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::getUserRecommendedPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::getUserRecommendedRadios(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::RADIOS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    PartialSearchResponse<Album> Deezer::getUserRecommendedReleases(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/releases").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Track> Deezer::getUserRecommendedTracks(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);

        QNetworkReply *reply = networkManager->get(request);
        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Track> Deezer::search(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::TRACKS);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Track> Deezer::search(AdvancedSearchQuery query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::TRACKS);
        QNetworkRequest request = buildSearchRequest(url, query.toString(), index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<Album> Deezer::searchAlbums(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::ALBUM);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseAlbum(responseJson);
    }

    PartialSearchResponse<Artist> Deezer::searchArtists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::ARTIST);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseArtist(responseJson);
    }

    PartialSearchResponse<Playlist> Deezer::searchPlaylists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::PLAYLIST);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponsePlaylist(responseJson);
    }

    PartialSearchResponse<Radio> Deezer::searchRadio(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::RADIO);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseRadio(responseJson);
    }

    PartialSearchResponse<Track> Deezer::searchTracks(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::TRACKS);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseTrack(responseJson);
    }

    PartialSearchResponse<User> Deezer::searchUsers(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::USER);
        QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);

        QNetworkReply *reply = networkManager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QJsonParseError error;
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll(), &error).object();
        reply->deleteLater();
        return deserializePartialResponseUser(responseJson);
    }
}
