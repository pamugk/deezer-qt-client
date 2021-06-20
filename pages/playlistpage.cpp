#include "playlistpage.h"
#include "ui_playlistpage.h"

PlaylistPage::PlaylistPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistPage)
{
    ui->setupUi(this);
}

PlaylistPage::~PlaylistPage()
{
    delete ui;
}
