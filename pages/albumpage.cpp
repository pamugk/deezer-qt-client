#include "albumpage.h"
#include "ui_albumpage.h"

AlbumPage::AlbumPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumPage)
{
    ui->setupUi(this);
}

AlbumPage::~AlbumPage()
{
    delete ui;
}
