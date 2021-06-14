#include "mainwindow.h"
#include "./ui_mainwindow.h"

QSystemTrayIcon *createTrayIcon();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->clearSearchButton->setHidden(true);
    ui->notificationsButton->setHidden(true);
    ui->userButton->setHidden(true);

    trayIcon = createTrayIcon();

    deezerApiInstance = new api::Deezer();

    searchPage = new SearchPage(deezerApiInstance, ui->centralwidget);
    static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(searchPage, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (trayIcon != nullptr)
    {
        delete trayIcon;
    }

    delete deezerApiInstance;
}

void MainWindow::on_searchLineEdit_textChanged(const QString &searchText)
{
    ui->clearSearchButton->setHidden(searchText.length() == 0);
    ui->searchButton->setDisabled(searchText.length() == 0);
}

void MainWindow::on_searchLineEdit_editingFinished()
{
    if (ui->searchLineEdit->hasFocus())
    {
        searchPage->search(ui->searchLineEdit->text());
    }
}

void MainWindow::on_clearSearchButton_clicked()
{
    ui->searchLineEdit->clear();
}

void MainWindow::on_searchButton_clicked()
{
    searchPage->search(ui->searchLineEdit->text());
}

QSystemTrayIcon *createTrayIcon()
{
    QSystemTrayIcon *trayIcon = nullptr;
    /*if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        QIcon trayIconIcon;
        trayIconIcon.addFile(QString::fromUtf8(":/assets/deezer/logotype/SVG/EQ.svg"));
        trayIcon = new QSystemTrayIcon(trayIconIcon);
        trayIcon->show();
    }*/
    return trayIcon;
}
