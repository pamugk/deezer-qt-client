#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->clearSearchButton->setHidden(true);
    ui->notificationsButton->setHidden(true);
    ui->userButton->setHidden(true);

    deezerApiInstance = new api::Deezer();

    searchPage = new SearchPage(ui->centralwidget);
    searchPage->setDeezerApiInstance(deezerApiInstance);
    static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(searchPage, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete deezerApiInstance;
}

void MainWindow::on_searchLineEdit_textChanged(const QString &searchText)
{
    ui->clearSearchButton->setHidden(searchText.length() == 0);
    ui->searchButton->setDisabled(searchText.length() == 0);
}

void MainWindow::on_searchLineEdit_editingFinished()
{
    /*deezerApiInstance->searchAlbums(ui->searchLineEdit->text(), 0, 5);
    deezerApiInstance->searchArtists(ui->searchLineEdit->text(), 0, 5);
    deezerApiInstance->searchPlaylists(ui->searchLineEdit->text(), 0, 5);
    deezerApiInstance->searchRadio(ui->searchLineEdit->text(), 0, 5);
    deezerApiInstance->searchTracks(ui->searchLineEdit->text(), 0, 5);
    deezerApiInstance->searchUsers(ui->searchLineEdit->text(), 0, 5);*/
}

void MainWindow::on_clearSearchButton_clicked()
{
    ui->searchLineEdit->clear();
}
