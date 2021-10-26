#ifndef DEEZER_H
#define DEEZER_H

#include "util/json_serialization.h"

#include "object/compilation/chart.h"
#include "object/compilation/editorial.h"

#include "object/playable/album.h"
#include "object/playable/artist.h"
#include "object/playable/genre.h"
#include "object/playable/playlist.h"
#include "object/playable/podcast.h"
#include "object/playable/radio.h"
#include "object/playable/track.h"

#include "object/search/advanced_search_query.h"
#include "object/search/partial_search_response.h"
#include "object/search/shared.h"

#include "object/service/infos.h"
#include "object/service/options.h"

#include "object/user/folder.h"
#include "object/user/user.h"

#include <QObject>
#include <QString>
#include <QVector>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork>

namespace api
{
    class Deezer: public QObject
    {
        Q_OBJECT

    public:
        Deezer();
        virtual ~Deezer();

        QNetworkReply *getAnything(QUrl&);

        QNetworkReply *getAlbum(long id);

        /*!
         * \brief Return a list of album's fans
         * \param Album id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getAlbumFans(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of album's tracks
         * \param Album id
         * \return
         */
        QNetworkReply *getAlbumTracks(long id);

        QNetworkReply *getArtist(long id);

        /*!
         * \brief Get the top 5 tracks of an artist
         * \param Artist id
         * \return
         */
        QNetworkReply *getArtistTop(long id);

        /*!
         * \brief Return a list of artist's albums
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistAlbums(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of artist's fans
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistFans(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of related artists
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistRelated(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of artist's playlists
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistPlaylists(long id, int index = 0, int limit = 25);

        Chart getChart();

        /*!
         * \brief Returns the Top albums
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartAlbums(long id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top artists
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartArtists(long id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top playlists
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartPlaylists(long id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top podcasts
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartPodcasts(long id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top tracks
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartTracks(long id, int index = 0, int limit = 25);

        QNetworkReply *getEditorial();

        QNetworkReply *getEditorial(long id);

        /*!
         * \brief This method returns four lists : Top track, Top album, Top artist and Top playlist
         * \param Editorial id
         * \return
         */
        QNetworkReply *getEditorialCharts(long id);

        /*!
         * \brief This method returns the new releases per genre for the current country
         * \param Genre id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getEditorialReleases(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of albums selected every week by the Deezer Team
         * \param Editorial id
         * \return
         */
        QNetworkReply *getEditorialSelection(long id);

        QNetworkReply *getGenre(long id);

        /*!
         * \brief Returns all artists for a genre
         * \param Genre id
         * \return
         */
        QNetworkReply *getGenreArtists(long id);

        /*!
         * \brief Returns all radios for a genre
         * \param Genre id
         * \return
         */
        QNetworkReply *getGenreRadios(long id);

        /*!
         * \brief Get the information about the API in the current country
         * \return
         */
        QNetworkReply *getInfos();

        QNetworkReply *getPlaylist(long id);

        /*!
         * \brief Return a list of playlist's fans
         * \param Playlist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getPlaylistFans(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of playlist's recommendation tracks
         * \param Playlist id
         * \return
         */
        QNetworkReply *getPlaylistRadio(long id);

        /*!
         * \brief Return a list of playlist's tracks
         * \param Playlist id
         * \return
         */
        QNetworkReply *getPlaylistTracks(long id);

        QNetworkReply *getRadio();

        QNetworkReply *getRadio(long id);

        /*!
         * \brief Returns a list of radio splitted by genre
         * \return
         */
        QNetworkReply *getRadioGenres();

        /*!
         * \brief Return the top radios (default to 25 radios)
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getRadioTop(int index ,int limit);

        /*!
         * \brief Get first 40 tracks in the radio
         * \param Radio id
         * \return
         */
        QNetworkReply *getRadioTracks(long id);

        /*!
         * \brief Returns a list of personal radio splitted by genre (as MIX in website)
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getRadioLists(int index, int limit);

        QNetworkReply *getTrack(long id);

        QNetworkReply *getUser(long id);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserChartsAlbums(long id, int index = 0, int limit = 25);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserChartsPlaylists(long id, int index = 0, int limit = 25);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserChartsTracks(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of user's favorite albums
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteAlbums(long id);

        /*!
         * \brief Return a list of user's favorite artists
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteArtists(long id);

        /*!
         * \brief Return a list of user's favorite Radios
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteRadios(long id);

        /*!
         * \brief Return a list of user's favorite tracks
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteTracks(long id);

        /*!
         * \brief Return a list of user's Folder
         * \return
         */
        QNetworkReply *getUserFolders();

        /*!
         * \brief Return a list of user's followings
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserFollowings(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of user's followers
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserFollowers(long id, int index = 0, int limit = 25);

        QNetworkReply *getUserFlow(long id);

        /*!
         * \brief Returns a list of the recently played tracks
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserHistory(long id, int index = 0, int limit = 25);

        /*!
         * \brief Alias of /options
         * \return
         */
        QNetworkReply *getUserOptions();

        /*!
         * \brief Return the user's Permissions granted to the application
         * \return
         */
        QNetworkReply *getUserPermissions();

        /*!
         * \brief Return a list of user's personal song
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserPersonalSongs(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of user's public Playlist.
         * Permission is needed to return private playlists
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserPlaylists(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of albums recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedAlbums(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of artists recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedArtists(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of playlists recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedPlaylists(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of radios recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedRadios(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of released albums recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedReleases(long id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of tracks recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedTracks(long id, int index = 0, int limit = 25);

        QNetworkReply *search(QString& query, int index = 0, int limit = 25, bool strict = false,
                                            SearchOrder order = SearchOrder::NONE);

        QNetworkReply *search(AdvancedSearchQuery query, int index = 0, int limit = 25, bool strict = false,
                                            SearchOrder order = SearchOrder::NONE);

        QNetworkReply *searchAlbums(QString& query, int index = 0, int limit = 25, bool strict = false,
                                                  SearchOrder order = SearchOrder::NONE);

        QNetworkReply *searchArtists(QString& query, int index = 0, int limit = 25, bool strict = false,
                                                    SearchOrder order = SearchOrder::NONE);

        QNetworkReply *searchPlaylists(QString& query, int index = 0, int limit = 25, bool strict = false,
                                                        SearchOrder order = SearchOrder::NONE);

        QNetworkReply *searchRadio(QString& query, int index = 0, int limit = 25, bool strict = false,
                                                 SearchOrder order = SearchOrder::NONE);

        QNetworkReply *searchTracks(QString& query, int index = 0, int limit = 25, bool strict = false,
                                                  SearchOrder order = SearchOrder::NONE);

        QNetworkReply *searchUsers(QString& query, int index = 0, int limit = 25, bool strict = false,
                                                SearchOrder order = SearchOrder::NONE);
    private:
        static const QString DEEZER_API_HOST;

        static const QString ALBUM;
        static const QString ARTIST;
        static const QString CHART;
        static const QString EDITORIAL;
        static const QString GENRE;
        static const QString PLAYLIST;
        static const QString RADIO;
        static const QString SEARCH;
        static const QString TRACK;
        static const QString USER;

        static const QString ALBUMS;
        static const QString ARTISTS;
        static const QString CHARTS;
        static const QString FANS;
        static const QString PLAYLISTS;
        static const QString RADIOS;
        static const QString RECOMMENDATIONS;
        static const QString TRACKS;

        QNetworkAccessManager* networkManager;

        QNetworkRequest buildPartialRequest(const QString &urlStr, int index, int limit);
        QNetworkRequest buildSearchRequest(const QString &urlStr, const QString &query, int index, int limit, bool strict, api::SearchOrder order);
    };
}

#endif // DEEZER_H
