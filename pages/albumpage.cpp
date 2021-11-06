#include "../api/object/playable/album.h"
#include "../api/util/xml_serialization.h"

#include "albumpage.h"
#include "ui_albumpage.h"

AlbumPage::AlbumPage(api::Deezer *apiInstance, api::Album &album, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumPage)
{
    ui->setupUi(this);

    discographyCarousel = nullptr;
    relatedArtistsCarousel = nullptr;

    if (!album.coverMedium.isEmpty())
    {
        QUrl coverUrl(album.coverMedium);
        auto coverReply = apiInstance->getAnything(coverUrl);
        connect(coverReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
        {
            coverReply->deleteLater();
        });
        connect(coverReply, &QNetworkReply::finished, [=]
        {
            if (coverReply->error() == QNetworkReply::NetworkError::NoError)
            {
                auto imageBytes = coverReply->readAll();
                auto cover = QPixmap(250, 250);
                cover.loadFromData(imageBytes);
                ui->coverLabel->setPixmap(cover);
                coverReply->deleteLater();
            }
        });
    }

    auto discographyReply = apiInstance->getArtistAlbums(album.artist->id, 0, 10);
    connect(discographyReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        discographyReply->deleteLater();
    });
    connect(discographyReply, &QNetworkReply::finished, [=]
    {
        if (discographyReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto discographyResponse = api::tryReadXmlResponse(discographyReply);
            auto discography = api::deserializePartialResponseAlbum(discographyResponse);
            delete discographyResponse;

            discographyCarousel = new AlbumCarousel(apiInstance, ui->discographyCarouselContents);
            discographyCarousel->addData(discography.getData());
            ui->discographyCarouselContents->setLayout(discographyCarousel);
        }
    });

    auto relatedArtistsReply = apiInstance->getArtistRelated(album.artist->id, 0, 10);
    connect(relatedArtistsReply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error)
    {
        relatedArtistsReply->deleteLater();
    });
    connect(relatedArtistsReply, &QNetworkReply::finished, [=]
    {
        if (relatedArtistsReply->error() == QNetworkReply::NetworkError::NoError)
        {
            auto relatedArtistsResponse = api::tryReadXmlResponse(relatedArtistsReply);
            auto relatedArtists = api::deserializePartialResponseArtist(relatedArtistsResponse);
            delete relatedArtistsResponse;

            relatedArtistsCarousel = new ArtistCarousel(apiInstance, ui->relatedArtistsCarouselContents);
            relatedArtistsCarousel->addData(relatedArtists.getData());
            ui->relatedArtistsCarouselContents->setLayout(relatedArtistsCarousel);
        }
    });

    ui->titleLabel->setText(album.title);
    ui->tracksLabel->setText(ui->tracksLabel->text().append(QString::number(album.trackCount)));
    ui->durationLabel->setText(album.duration.hour() > 0 ?
                                   album.duration.toString("h 'ч.' m 'мин.' s 'сек.'") :
                                   album.duration.toString("m 'мин.' s 'сек.'"));
    ui->releaseDateLabel->setText(album.releaseDate.toString("dd.MM.yyyy"));
    ui->fansLabel->setText(ui->fansLabel->text().append(QString::number(album.fanCount)));

    ui->tracksTable->setModel(new AlbumTracksModel(album.tracks, ui->tracksTable));
}

AlbumPage::~AlbumPage()
{
    delete ui;
}

void AlbumPage::on_prevDiscographyButton_clicked()
{
    if (discographyCarousel != nullptr)
    {
        discographyCarousel->prev();
    }
}


void AlbumPage::on_nextDiscographyButton_clicked()
{
    if (discographyCarousel != nullptr)
    {
        discographyCarousel->next();
    }
}


void AlbumPage::on_prevRelatedArtistsButton_clicked()
{

}


void AlbumPage::on_nextRelatedArtistsButton_clicked()
{

}

