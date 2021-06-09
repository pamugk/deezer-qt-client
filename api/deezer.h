#ifndef DEEZER_H
#define DEEZER_H

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

namespace api
{
    class Deezer: public QObject
    {
        Q_OBJECT

        const char DEEZER_API_HOST[23] = "https://api.deezer.com";
        QNetworkAccessManager* networkManager;

    public:
        Deezer();
        virtual ~Deezer();

        Album getAlbum(long id);

        /*!
         * \brief Return a list of album's fans
         * \param Album id
         * \return
         */
        PartialSearchResponse<User> getAlbumFans(long id);

        /*!
         * \brief Return a list of album's tracks
         * \param Album id
         * \return
         */
        QVector<Track> getAlbumTracks(long id);

        Artist getArtist(long id);

        /*!
         * \brief Get the top 5 tracks of an artist
         * \param Artist id
         * \return
         */
        QVector<Track> getArtistTop(long id);

        /*!
         * \brief Return a list of artist's albums
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Album> getArtistAlbums(long id, int index, int limit);

        /*!
         * \brief Return a list of artist's fans
         * \param Artist id
         * \return
         */
        PartialSearchResponse<User> getArtistFans(long id);

        /*!
         * \brief Return a list of related artists
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Artist> getArtistRelated(long id, int index, int limit);

        /*!
         * \brief Return a list of artist's playlists
         * \param Artist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Playlist> getArtistPlaylists(long id, int index, int limit);

        Chart getChart();

        /*!
         * \brief Returns the Top albums
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Track> getChartAlbums(long id, int index, int limit);

        /*!
         * \brief Returns the Top artists
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Artist> getChartArtists(long id, int index, int limit);

        /*!
         * \brief Returns the Top playlists
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Playlist> getChartPlaylists(long id, int index, int limit);

        /*!
         * \brief Returns the Top podcasts
         * \param Chart id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Podcast> getChartPodcasts(long id, int index, int limit);

        /*!
         * \brief This method returns four lists : Top track, Top album, Top artist and Top playlist
         * \param Editorial id
         * \return
         */
        Chart getEditorialCharts(long id);

        /*!
         * \brief This method returns the new releases per genre for the current country
         * \param Genre id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Album> getEditorialReleases(long id, int index, int limit);

        Genre getGenre(long id);

        /*!
         * \brief Returns all artists for a genre
         * \param Genre id
         * \return
         */
        QVector<Artist> getGenreArtists(long id);

        /*!
         * \brief Returns all radios for a genre
         * \param Genre id
         * \return
         */
        QVector<Radio> getGenreRadios(long id);

        /*!
         * \brief Return a list of playlist's fans
         * \return
         */
        Infos getInfos();

        Playlist getPlaylist(long id);

        /*!
         * \brief Return a list of playlist's fans
         * \param Playlist id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<User> getPlaylistFans(long id, int index, int limit);

        /*!
         * \brief Return a list of playlist's recommendation tracks
         * \param Playlist id
         * \return
         */
        QVector<Track> getPlaylistRadio(long id);

        /*!
         * \brief Return a list of playlist's tracks
         * \param Playlist id
         * \return
         */
        QVector<Track> getPlaylistTracks(long id);

        Radio getRadio();

        Radio getRadio(long id);

        /*!
         * \brief Returns a list of radio splitted by genre
         * \return
         */
        QVector<Genre> getRadioGenres();

        /*!
         * \brief Return the top radios (default to 25 radios)
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Radio> getRadioTop(int index ,int limit);

        /*!
         * \brief Get first 40 tracks in the radio
         * \param Radio id
         * \return
         */
        QVector<Track> getRadioTracks(long id);

        /*!
         * \brief Returns a list of personal radio splitted by genre (as MIX in website)
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Radio> getRadioLists(int index, int limit);

        Track getTrack(long id);

        User getUser(long id);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Album> getUserChartsAlbums(long id, int index, int limit);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Playlist> getUserChartsPlaylists(long id, int index, int limit);

        /*!
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Track> getUserChartsTracks(long id, int index, int limit);

        /*!
         * \brief Return a list of user's favorite albums
         * \param User id
         * \return
         */
        PartialSearchResponse<Album> getUserFavoriteAlbums(long id);

        /*!
         * \brief Return a list of user's favorite artists
         * \param User id
         * \return
         */
        PartialSearchResponse<Artist> getUserFavoriteArtists(long id);

        /*!
         * \brief Return a list of user's favorite Radios
         * \param User id
         * \return
         */
        PartialSearchResponse<Radio> getUserFavoriteRadios(long id);

        /*!
         * \brief Return a list of user's favorite tracks
         * \param User id
         * \return
         */
        PartialSearchResponse<Track> getUserFavoriteTracks(long id);

        /*!
         * \brief Return a list of user's Folder
         * \return
         */
        QVector<Folder> getUserFolders();

        /*!
         * \brief Return a list of user's followings
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<User> getUserFollowings(long id, int index, int limit);

        /*!
         * \brief Return a list of user's followers
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<User> getUserFollowers(long id, int index, int limit);

        QVector<Track> getUserFlow(long id);

        /*!
         * \brief Returns a list of the recently played tracks
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Track> getUserHistory(long id, int index, int limit);

        /*!
         * \brief Alias of /options
         * \return
         */
        Options getUserOptions();

        /*!
         * \brief Return the user's Permissions granted to the application
         * \return
         */
        QVector<QString> getUserPermissions();

        /*!
         * \brief Return a list of user's personal song
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Track> getUserPersonalSongs(long id, int index, int limit);

        /*!
         * \brief Return a list of user's public Playlist.
         * Permission is needed to return private playlists
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Playlist> getUserPlaylists(long id, int index, int limit);

        /*!
         * \brief Return a list of albums recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Album> getUserRecommendedAlbums(long id, int index, int limit);

        /*!
         * \brief Return a list of artists recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Artist> getUserRecommendedArtists(long id, int index, int limit);

        /*!
         * \brief Return a list of playlists recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Playlist> getUserRecommendedPlaylists(long id, int index, int limit);

        /*!
         * \brief Return a list of radios recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Radio> getUserRecommendedRadios(long id, int index, int limit);

        /*!
         * \brief Return a list of released albums recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Album> getUserRecommendedReleases(long id, int index, int limit);

        /*!
         * \brief Return a list of tracks recommendations
         * \param User id
         * \param Index of results page
         * \param Max page size
         * \return
         */
        PartialSearchResponse<Track> getUserRecommendedTracks(long id, int index, int limit);

        PartialSearchResponse<Track> search(QString& query, int index, int limit, bool strict,
                                            SearchOrder order);

        PartialSearchResponse<Track> search(AdvancedSearchQuery query, int index, int limit, bool strict,
                                            SearchOrder order);

        PartialSearchResponse<Album> searchAlbums(QString& query, int index, int limit, bool strict,
                                                  SearchOrder order);

        PartialSearchResponse<Artist> searchArtists(QString& query, int index, int limit, bool strict,
                                                  SearchOrder order);

        PartialSearchResponse<Playlist> searchPlaylists(QString& query, int index, int limit, bool strict,
                                                  SearchOrder order);

        PartialSearchResponse<Radio> searchRadio(QString& query, int index, int limit, bool strict,
                                                  SearchOrder order);

        PartialSearchResponse<Track> searchTracks(QString& query, int index, int limit, bool strict,
                                                  SearchOrder order);

        PartialSearchResponse<User> searchUsers(QString& query, int index, int limit, bool strict,
                                                  SearchOrder order);

    };
}

#endif // DEEZER_H
