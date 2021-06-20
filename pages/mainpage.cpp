#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}
