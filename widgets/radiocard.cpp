#include "radiocard.h"
#include "ui_radiocard.h"

RadioCard::RadioCard(api::Deezer *apiInstance, api::Radio &radio, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioCard)
{
    ui->setupUi(this);

    connect(ui->pictureButton, &QPushButton::clicked, [radioId{ radio.id }, this]{ emit clickedRadio(radioId); });

    if (!radio.pictureMedium.isEmpty())
    {
        QUrl pictureUrl(radio.pictureMedium);
        QNetworkReply *coverReply = apiInstance->getAnything(pictureUrl);
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
                ui->pictureButton->setIcon(QIcon(cover));
                coverReply->deleteLater();
            }
        });
    }
}

RadioCard::~RadioCard()
{
    delete ui;
}
