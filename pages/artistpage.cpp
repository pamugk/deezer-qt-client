#include "artistpage.h"
#include "ui_artistpage.h"

ArtistPage::ArtistPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArtistPage)
{
    ui->setupUi(this);
}

ArtistPage::~ArtistPage()
{
    delete ui;
}
