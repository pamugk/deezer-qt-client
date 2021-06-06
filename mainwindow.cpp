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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_searchLineEdit_textChanged(const QString &searchText)
{
    ui->clearSearchButton->setHidden(searchText.length() == 0);
    ui->searchButton->setDisabled(searchText.length() == 0);
}

void MainWindow::on_searchLineEdit_editingFinished()
{

}

void MainWindow::on_clearSearchButton_clicked()
{
    ui->searchLineEdit->clear();
}
