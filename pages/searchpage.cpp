#include "searchpage.h"
#include "ui_searchpage.h"

SearchPage::SearchPage(api::Deezer * deezerApiInstance, QWidget *parent) :
    QTabWidget(parent),
    deezerApiInstance(deezerApiInstance),
    ui(new Ui::SearchPage)
{
    hasUndergoingSearch = false;
    ui->setupUi(this);

    albums = new Flow(deezerApiInstance, ui->albumTab);
    ui->albumTabLayout->addWidget(albums);

    clear();
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::search(QString request)
{
    if (hasUndergoingSearch || request.isNull() || request.isEmpty())
    {
        return;
    }

    hasUndergoingSearch = true;

    clear();

    api::PartialSearchResponse<api::Track> trackPrefetch = deezerApiInstance->searchTracks(request, 0, 5);
    if (trackPrefetch.getTotal() > 0)
    {
        addTab(ui->trackTab, QString("Треки"));
        ui->overviewContentsLayout->addWidget(new QLabel("Треки", ui->overviewContents));
        ui->trackLabel->setText(QString("Треков: %1").arg(QString::number(trackPrefetch.getTotal())));
    }

    api::PartialSearchResponse<api::Album> albumPrefetch = deezerApiInstance->searchAlbums(request, 0, 5);
    if (albumPrefetch.getTotal() > 0)
    {
        addTab(ui->albumTab, QString("Альбомы"));
        ui->overviewContentsLayout->addWidget(new QLabel("Альбомы", ui->overviewContents));
        ui->albumLabel->setText(QString("Альбомов: %1").arg(QString::number(albumPrefetch.getTotal())));

        api::PartialSearchResponse<api::Album> albumsResponse = deezerApiInstance->searchAlbums(request, 0, 20);
        QVector<api::Album> albumsData = albumsResponse.getData();
        albums->addContents(albumsData);
    }

    api::PartialSearchResponse<api::Artist> artistPrefetch = deezerApiInstance->searchArtists(request, 0, 5);
    if (artistPrefetch.getTotal() > 0)
    {
        addTab(ui->artistTab, QString("Исполнители"));
        ui->overviewContentsLayout->addWidget(new QLabel("Исполнители", ui->overviewContents));
        ui->artistLabel->setText(QString("Исполнителей: %1").arg(QString::number(artistPrefetch.getTotal())));
    }

    api::PartialSearchResponse<api::Playlist> playlistPrefetch = deezerApiInstance->searchPlaylists(request, 0, 5);
    if (playlistPrefetch.getTotal() > 0)
    {
        addTab(ui->playlistTab, QString("Плейлисты"));
        ui->overviewContentsLayout->addWidget(new QLabel("Плейлисты", ui->overviewContents));
        ui->playlistLabel->setText(QString("Плейлистов: %1").arg(QString::number(playlistPrefetch.getTotal())));
    }

    api::PartialSearchResponse<api::Radio> radioPrefetch = deezerApiInstance->searchRadio(request, 0, 5);
    if (radioPrefetch.getTotal() > 0)
    {
        addTab(ui->mixTab, QString("Миксы"));
        ui->overviewContentsLayout->addWidget(new QLabel("Миксы", ui->overviewContents));
        ui->mixLabel->setText(QString("Миксов: %1").arg(QString::number(radioPrefetch.getTotal())));
    }

    api::PartialSearchResponse<api::User> userPrefetch = deezerApiInstance->searchUsers(request, 0, 5);
    if (userPrefetch.getTotal() > 0)
    {
        addTab(ui->userTab, QString("Профили"));
        ui->overviewContentsLayout->addWidget(new QLabel("Профили", ui->overviewContents));
        ui->userLabel->setText(QString("Профилей: %1").arg(QString::number(userPrefetch.getTotal())));
    }

    hasUndergoingSearch = false;
}

void SearchPage::clear()
{
    while (count() > 1)
    {
        removeTab(1);
    }

    while (QLayoutItem *item = ui->overviewContentsLayout->takeAt(0))
    {
        ui->overviewContentsLayout->removeItem(item);
    }

    albums->clearAll();
}
