#include "deezer.h"
#include "util/serialization.h"

#include <QtGui>
#include <QtNetworkAuth>

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

    Deezer::Deezer(QString appId, QString apiSecret, QVector<Permissions> permissions, QObject *parent): QObject(parent)
    {
        oauth2Api = new QOAuth2AuthorizationCodeFlow(this);
        auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
        replyHandler->setCallbackPath("/callback");
        oauth2Api->setReplyHandler(replyHandler);
        oauth2Api->setAuthorizationUrl(QUrl("https://connect.deezer.com/oauth/auth.php"));
        oauth2Api->setAccessTokenUrl(QUrl("https://connect.deezer.com/oauth/access_token.php"));
        auto permissionsScope = buildScope(permissions);
        oauth2Api->setScope(permissionsScope);

        oauth2Api->setModifyParametersFunction(QAbstractOAuth::ModifyParametersFunction(
            [appId, apiSecret, permissionsScope](QAbstractOAuth::Stage stage, QMap<QString, QVariant> *parameters)
            {
                switch (stage)
                {
                case QAbstractOAuth::Stage::RequestingTemporaryCredentials:
                    break;
                case QAbstractOAuth::Stage::RequestingAuthorization:
                    {
                        parameters->insert("app_id", appId);
                        parameters->insert("redirect_uri", "http://localhost:8080/calback");
                        parameters->insert("perms", permissionsScope);
                        break;
                    }
                case QAbstractOAuth::Stage::RequestingAccessToken:
                case QAbstractOAuth::Stage::RefreshingAccessToken:
                    {
                        parameters->insert("app_id", appId);
                        parameters->insert("secret", apiSecret);
                        break;
                    }
                }
        }));

        connect(oauth2Api, &QOAuth2AuthorizationCodeFlow::statusChanged, this, &Deezer::authenticationStatusChanged);
        connect(oauth2Api, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    }

    void Deezer::authenticate()
    {
        oauth2Api->grant();
    }

    void Deezer::authenticationStatusChanged(QAbstractOAuth::Status status)
    {
        if (status == QAbstractOAuth::Status::Granted)
        {
            emit authenticated();
        }
    }

    QUrl Deezer::buildPartialUrl(const QString &urlStr, int index, int limit)
    {
        QUrlQuery urlParams;

        urlParams.addQueryItem("index", QString::number(index));
        urlParams.addQueryItem("limit", QString::number(limit));
        urlParams.addQueryItem("output", "xml");

        QUrl url(urlStr);
        url.setQuery(urlParams);

        return url;
    }

    QUrl Deezer::buildSearchUrl(const QString &urlStr, const QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        QUrlQuery urlParams;

        urlParams.addQueryItem("q", query);
        urlParams.addQueryItem("strict", strict ? "on" : "off");
        urlParams.addQueryItem("index", QString::number(index));
        urlParams.addQueryItem("limit", QString::number(limit));
        urlParams.addQueryItem("output", "xml");

        if (order != SearchOrder::NONE)
        {
            urlParams.addQueryItem("order", serialize(order));
        }

        QUrl url(urlStr);
        url.setQuery(urlParams);

        return url;
    }

    QString Deezer::buildScope(QVector<Permissions> permissions)
    {
        if (permissions.size() == 0)
        {
            return "";
        }

        QString scope = serialize(permissions.at(0));
        for (int i = 1; i < permissions.size(); i++)
        {
            scope.append(QString(",%1").arg(serialize(permissions.at(i))));
        }

        return scope;
    }

    QUrl buildUrl(const QString &urlStr)
    {
        QUrlQuery urlParams;
        urlParams.addQueryItem("output", "xml");

        QUrl url(urlStr);
        url.setQuery(urlParams);

        return url;
    }

    QNetworkReply *Deezer::getAnything(QUrl &url)
    {
        return oauth2Api->get(url);
    }

    QNetworkReply *Deezer::getAlbum(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id))));
    }

    QNetworkReply *Deezer::getAlbumFans(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id), Deezer::FANS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getAlbumTracks(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id), Deezer::TRACKS)));
    }

    QNetworkReply *Deezer::getArtist(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id))));
    }

    QNetworkReply *Deezer::getArtistTop(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/top").arg(Deezer::DEEZER_API_HOST, Deezer::ALBUM, QString::number(id))));
    }

    QNetworkReply *Deezer::getArtistAlbums(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::ALBUMS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getArtistFans(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::FANS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getArtistRelated(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/related").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getArtistPlaylists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::ARTIST, QString::number(id), Deezer::PLAYLISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getChartAlbums(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::ALBUMS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getChartArtists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::ARTISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getChartPlaylists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::PLAYLISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getChartPodcasts(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/podcasts").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getChartTracks(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id), Deezer::TRACKS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getEditorialCharts(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::EDITORIAL, QString::number(id), Deezer::CHARTS)));
    }

    QNetworkReply *Deezer::getEditorialReleases(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/releases").arg(Deezer::DEEZER_API_HOST, Deezer::CHART, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getEditorialSelection(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/selection").arg(Deezer::DEEZER_API_HOST, Deezer::EDITORIAL, QString::number(id))));
    }

    QNetworkReply *Deezer::getGenre(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id))));
    }

    QNetworkReply *Deezer::getGenreArtists(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id), Deezer::ARTISTS)));
    }

    QNetworkReply *Deezer::getGenreRadios(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::GENRE, QString::number(id), Deezer::RADIOS)));
    }

    QNetworkReply *Deezer::getInfos()
    {
        return oauth2Api->get(buildUrl(QString("%1/infos").arg(Deezer::DEEZER_API_HOST)));
    }

    QNetworkReply *Deezer::getPlaylist(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id))));
    }

    QNetworkReply *Deezer::getPlaylistFans(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::FANS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getPlaylistRadio(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::TRACKS)));
    }

    QNetworkReply *Deezer::getPlaylistTracks(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::PLAYLIST, QString::number(id), Deezer::RADIO)));
    }

    QNetworkReply *Deezer::getRadio()
    {
        return oauth2Api->get(buildUrl(QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO)));
    }

    QNetworkReply *Deezer::getRadio(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO, QString::number(id))));
    }

    QNetworkReply *Deezer::getRadioGenres()
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/genres").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO)));
    }

    QNetworkReply *Deezer::getRadioTop(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/top").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getRadioTracks(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO, QString::number(id), Deezer::TRACKS)));
    }

    QNetworkReply *Deezer::getRadioLists(int index = 0, int limit = 25)
    {
        const QString url = QString("%1/%2/lists").arg(Deezer::DEEZER_API_HOST, Deezer::RADIO);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getTrack(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::TRACK, QString::number(id))));
    }

    QNetworkReply *Deezer::getUser(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id))));
    }

    QNetworkReply *Deezer::getUserChartsAlbums(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::ALBUMS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserChartsPlaylists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::PLAYLISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserChartsTracks(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::CHARTS, Deezer::TRACKS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserFavoriteAlbums(long id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::ALBUMS);
        return oauth2Api->get(buildPartialUrl(url, 0, 25));
    }

    QNetworkReply *Deezer::getUserFavoriteArtists(long id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::ARTISTS);
        return oauth2Api->get(buildPartialUrl(url, 0, 25));
    }

    QNetworkReply *Deezer::getUserFavoriteRadios(long id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RADIOS);
        return oauth2Api->get(buildPartialUrl(url, 0, 25));
    }

    QNetworkReply *Deezer::getUserFavoriteTracks(long id)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::TRACKS);
        return oauth2Api->get(buildPartialUrl(url, 0, 25));
    }

    QNetworkReply *Deezer::getUserFolders()
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/me/folders").arg(Deezer::DEEZER_API_HOST, Deezer::USER)));
    }

    QNetworkReply *Deezer::getUserFollowings(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/followings").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserFollowers(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/followers").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserFlow(long id)
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/%3/flow").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id))));
    }

    QNetworkReply *Deezer::getUserHistory(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/history").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserOptions()
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/me/permissions").arg(Deezer::DEEZER_API_HOST,Deezer:: USER)));
    }

    QNetworkReply *Deezer::getUserPermissions()
    {
        return oauth2Api->get(buildUrl(QString("%1/%2/me/permissions").arg(Deezer::DEEZER_API_HOST,Deezer:: USER)));
    }

    QNetworkReply *Deezer::getUserPersonalSongs(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/personal_songs").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id));
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserPlaylists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::PLAYLISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserRecommendedAlbums(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::ALBUMS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserRecommendedArtists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::ARTISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserRecommendedPlaylists(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::PLAYLISTS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserRecommendedRadios(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::RADIOS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserRecommendedReleases(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/releases").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    QNetworkReply *Deezer::getUserRecommendedTracks(long id, int index, int limit)
    {
        const QString url = QString("%1/%2/%3/%4/%5").arg(Deezer::DEEZER_API_HOST, Deezer::USER, QString::number(id), Deezer::RECOMMENDATIONS, Deezer::TRACKS);
        return oauth2Api->get(buildPartialUrl(url, index, limit));
    }

    void Deezer::logout()
    {
        oauth2Api->setToken(nullptr);
    }

    QNetworkReply *Deezer::search(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH );
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }

    QNetworkReply *Deezer::search(AdvancedSearchQuery query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH);
        return oauth2Api->get(buildSearchUrl(url, query.toString(), index, limit, strict, order));
    }

    QNetworkReply *Deezer::searchAlbums(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::ALBUM);
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }

    QNetworkReply *Deezer::searchArtists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::ARTIST);
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }

    QNetworkReply *Deezer::searchPlaylists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::PLAYLIST);
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }

    QNetworkReply *Deezer::searchRadio(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::RADIO);
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }

    QNetworkReply *Deezer::searchTracks(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::TRACK);
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }

    QNetworkReply *Deezer::searchUsers(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        const QString url = QString("%1/%2/%3").arg(Deezer::DEEZER_API_HOST, Deezer::SEARCH, Deezer::USER);
        return oauth2Api->get(buildSearchUrl(url, query, index, limit, strict, order));
    }
}
