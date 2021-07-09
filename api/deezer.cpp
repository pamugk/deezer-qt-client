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

    QNetworkReply* Deezer::getAnything(QUrl &url)
    {
        return networkManager->get(QNetworkRequest(url));
    }

   QNetworkReply *Deezer::getAlbum(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getAlbumFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id), Deezer::FANS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getAlbumTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id), Deezer::TRACKS);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getArtist(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getArtistTop(int id)
    {
        const QString url = QString("%1/%2/%3/top").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getArtistAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::ALBUMS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getArtistFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::FANS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getArtistRelated(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/related").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getArtistPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::PLAYLISTS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getChartAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::ALBUMS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getChartArtists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::ARTISTS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getChartPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::PLAYLISTS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getChartPodcasts(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/podcasts").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getChartTracks(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getEditorialCharts(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::EDITORIAL, QString::number(id), Deezer::CHARTS);
        const QNetworkRequest request(url);
        return networkManager->get(request);

    }

    QNetworkReply *Deezer::getEditorialReleases(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/releases").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getEditorialSelection(int id)
    {
        const QString url = QString("%1/%2/%3/selection").arg(Deezer::DEEZER_API_HOST, Deezer::EDITORIAL, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getGenre(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getGenreArtists(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id), Deezer::ARTISTS);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getGenreRadios(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id), Deezer::RADIOS);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getInfos()
    {
        const QString url = QString("%1/infos").arg(Deezer::DEEZER_API_HOST);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getPlaylist(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id));
        QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getPlaylistFans(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::FANS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getPlaylistRadio(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::TRACKS);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getPlaylistTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::RADIO);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getRadio()
    {
        const QString url = QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getRadio(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getRadioGenres()
    {
        const QString url = QString("%1/%2/genres").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getRadioTop(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/top").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getRadioTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO, QString::number(id), Deezer::TRACKS);
        QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getRadioLists(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/lists").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getTrack(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::TRACK, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUser(int id)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserChartsAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::ALBUMS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserChartsPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::PLAYLISTS);
        QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserChartsTracks(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::TRACKS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFavoriteAlbums(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::ALBUMS);
        const QNetworkRequest request = buildPartialRequest(url, 0, 25);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFavoriteArtists(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::ARTISTS);
        const QNetworkRequest request = buildPartialRequest(url, 0, 25);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFavoriteRadios(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RADIOS);
        QNetworkRequest request = buildPartialRequest(url, 0, 25);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFavoriteTracks(int id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::TRACKS);
        const QNetworkRequest request = buildPartialRequest(url, 0, 25);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFolders()
    {
        const QString url = QString("%1/%2/me/folders").arg(Deezer::DEEZER_API_HOST, Deezer::USER);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFollowings(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/followings").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFollowers(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/followers").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserFlow(int id)
    {
        const QString url = QString("%1/%2/%3/flow").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserHistory(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/history").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserOptions()
    {
        const QString url = QString("%1/%2/me/permissions").arg(Deezer::DEEZER_API_HOST,Deezer:: USER);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserPermissions()
    {
        const QString url = QString("%1/%2/me/permissions").arg(Deezer::DEEZER_API_HOST,Deezer:: USER);
        const QNetworkRequest request(url);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserPersonalSongs(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/personal_songs").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::PLAYLISTS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserRecommendedAlbums(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::ALBUMS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserRecommendedArtists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::ARTISTS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserRecommendedPlaylists(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::PLAYLISTS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserRecommendedRadios(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::RADIOS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserRecommendedReleases(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/releases").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::getUserRecommendedTracks(int id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::TRACKS);
        const QNetworkRequest request = buildPartialRequest(url, index, limit);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::search(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::search(AdvancedSearchQuery query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH);
        QNetworkRequest request = buildSearchRequest(url, query.toString(), index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::searchAlbums(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::ALBUM);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::searchArtists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::ARTIST);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::searchPlaylists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::PLAYLIST);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::searchRadio(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::RADIO);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::searchTracks(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::TRACK);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }

    QNetworkReply *Deezer::searchUsers(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::USER);
        const QNetworkRequest request = buildSearchRequest(url, query, index, limit, strict, order);
        return networkManager->get(request);
    }
}
