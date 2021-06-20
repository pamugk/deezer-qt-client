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

        QNetworkReply *getAlbum(int id);

        /*!
         * \brief Return a list of album's fans
         * \param Album id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getAlbumFans(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of album's tracks
         * \param Album id
         * \return
         */
        QNetworkReply *getAlbumTracks(int id);

        QNetworkReply *getArtist(int id);

        /*!
         * \brief Get the top 5 tracks of an artist
         * \param Artist id
         * \return
         */
        QNetworkReply *getArtistTop(int id);

        /*!
         * \brief Return a list of artist's albums
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistAlbums(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of artist's fans
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistFans(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of related artists
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistRelated(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of artist's playlists
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getArtistPlaylists(int id, int index = 0, int limit = 25);

        Chart getChart();

        /*!
         * \brief Returns the Top albums
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartAlbums(int id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top artists
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartArtists(int id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top playlists
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartPlaylists(int id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top podcasts
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartPodcasts(int id, int index = 0, int limit = 25);

        /*!
         * \brief Returns the Top tracks
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getChartTracks(int id, int index = 0, int limit = 25);

        QNetworkReply *getEditorial();

        QNetworkReply *getEditorial(int id);

        /*!
         * \brief This method returns four lists : Top track, Top album, Top artist and Top playlist
         * \param Editorial id
         * \return
         */
        QNetworkReply *getEditorialCharts(int id);

        /*!
         * \brief This method returns the new releases per genre for the current country
         * \param Genre id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getEditorialReleases(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of albums selected every week by the Deezer Team
         * \param Editorial id
         * \return
         */
        QNetworkReply *getEditorialSelection(int id);

        QNetworkReply *getGenre(int id);

        /*!
         * \brief Returns all artists for a genre
         * \param Genre id
         * \return
         */
        QNetworkReply *getGenreArtists(int id);

        /*!
         * \brief Returns all radios for a genre
         * \param Genre id
         * \return
         */
        QNetworkReply *getGenreRadios(int id);

        /*!
         * \brief Get the information about the API in the current country
         * \return
         */
        QNetworkReply *getInfos();

        QNetworkReply *getPlaylist(int id);

        /*!
         * \brief Return a list of playlist's fans
         * \param Playlist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getPlaylistFans(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of playlist's recommendation tracks
         * \param Playlist id
         * \return
         */
        QNetworkReply *getPlaylistRadio(int id);

        /*!
         * \brief Return a list of playlist's tracks
         * \param Playlist id
         * \return
         */
        QNetworkReply *getPlaylistTracks(int id);

        QNetworkReply *getRadio();

        QNetworkReply *getRadio(int id);

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
        QNetworkReply *getRadioTracks(int id);

        /*!
         * \brief Returns a list of personal radio splitted by genre (as MIX in website)
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getRadioLists(int index, int limit);

        QNetworkReply *getTrack(int id);

        QNetworkReply *getUser(int id);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserChartsAlbums(int id, int index = 0, int limit = 25);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserChartsPlaylists(int id, int index = 0, int limit = 25);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserChartsTracks(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of user's favorite albums
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteAlbums(int id);

        /*!
         * \brief Return a list of user's favorite artists
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteArtists(int id);

        /*!
         * \brief Return a list of user's favorite Radios
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteRadios(int id);

        /*!
         * \brief Return a list of user's favorite tracks
         * \param User id
         * \return
         */
        QNetworkReply *getUserFavoriteTracks(int id);

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
        QNetworkReply *getUserFollowings(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of user's followers
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserFollowers(int id, int index = 0, int limit = 25);

        QNetworkReply *getUserFlow(int id);

        /*!
         * \brief Returns a list of the recently played tracks
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserHistory(int id, int index = 0, int limit = 25);

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
        QNetworkReply *getUserPersonalSongs(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of user's public Playlist.
         * Permission is needed to return private playlists
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserPlaylists(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of albums recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedAlbums(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of artists recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedArtists(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of playlists recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedPlaylists(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of radios recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedRadios(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of released albums recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedReleases(int id, int index = 0, int limit = 25);

        /*!
         * \brief Return a list of tracks recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        QNetworkReply *getUserRecommendedTracks(int id, int index = 0, int limit = 25);

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
