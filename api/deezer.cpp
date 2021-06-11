#include "deezer.h"

namespace api {
    Deezer::Deezer()
    {
        networkManager = new QNetworkAccessManager();
    }

    Deezer::~Deezer()
    {
        delete networkManager;
    }

    Album *Deezer::getAlbum(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<User> *Deezer::getAlbumFans(long id)
    {
        return nullptr;
    }

    QVector<Track> *Deezer::getAlbumTracks(long id)
    {
        return nullptr;
    }

    QVector<Track> *Deezer::getArtistTop(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::getArtistAlbums(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<User> *Deezer::getArtistFans(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Artist> *Deezer::getArtistRelated(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Playlist> *Deezer::getArtistPlaylists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::getChartAlbums(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Artist> *Deezer::getChartArtists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Playlist> *Deezer::getChartPlaylists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Podcast> *Deezer::getChartPodcasts(long id, int index, int limit)
    {
        return nullptr;
    }

    Chart *Deezer::getEditorialCharts(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::getEditorialReleases(long id, int index, int limit)
    {
        return nullptr;
    }

    QVector<Artist> *Deezer::getGenreArtists(long id)
    {
        return nullptr;
    }

    QVector<Radio> *Deezer::getGenreRadios(long id)
    {
        return nullptr;
    }

    Playlist *Deezer::getPlaylist(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<User> *Deezer::getPlaylistFans(long id, int index, int limit)
    {
        return nullptr;
    }

    QVector<Track> *Deezer::getPlaylistRadio(long id)
    {
        return nullptr;
    }

    QVector<Track> *Deezer::getPlaylistTracks(long id)
    {
        return nullptr;
    }

    QVector<Genre> *Deezer::getRadioGenres()
    {
        return nullptr;
    }

    PartialSearchResponse<Radio> *Deezer::getRadioTop(int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Radio> *Deezer::getRadioLists(int index, int limit)
    {
        return nullptr;
    }

    Track *Deezer::getTrack(long id)
    {
        return nullptr;
    }

    User *Deezer::getUser(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::getUserChartsAlbums(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Playlist> *Deezer::getUserChartsPlaylists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::getUserChartsTracks(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::getUserFavoriteAlbums(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Artist> *Deezer::getUserFavoriteArtists(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Radio> *Deezer::getUserFavoriteRadios(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::getUserFavoriteTracks(long id)
    {
        return nullptr;
    }

    QVector<Folder> *Deezer::getUserFolders()
    {
        return nullptr;
    }

    PartialSearchResponse<User> *Deezer::getUserFollowings(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<User> *Deezer::getUserFollowers(long id, int index, int limit)
    {
        return nullptr;
    }

    QVector<Track> *Deezer::getUserFlow(long id)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::getUserHistory(long id, int index, int limit)
    {
        return nullptr;
    }

    Options *Deezer::getUserOptions()
    {
        return nullptr;
    }

    QVector<QString> *Deezer::getUserPermissions()
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::getUserPersonalSongs(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Playlist> *Deezer::getUserPlaylists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::getUserRecommendedAlbums(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Artist> *Deezer::getUserRecommendedArtists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Playlist> *Deezer::getUserRecommendedPlaylists(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Radio> *Deezer::getUserRecommendedRadios(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::getUserRecommendedReleases(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::getUserRecommendedTracks(long id, int index, int limit)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::search(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::search(AdvancedSearchQuery query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<Album> *Deezer::searchAlbums(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<Artist> *Deezer::searchArtists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<Playlist> *Deezer::searchPlaylists(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<Radio> *Deezer::searchRadio(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<Track> *Deezer::searchTracks(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }

    PartialSearchResponse<User> *Deezer::searchUsers(QString &query, int index, int limit, bool strict, SearchOrder order)
    {
        return nullptr;
    }
}
