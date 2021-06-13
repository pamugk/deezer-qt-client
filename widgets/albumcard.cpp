#include "albumcard.h"
#include "ui_albumcard.h"

AlbumCard::AlbumCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumCard)
{
    ui->setupUi(this);
}

AlbumCard::~AlbumCard()
{
    delete ui;
}
