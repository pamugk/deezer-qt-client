#include "radiopage.h"
#include "ui_radiopage.h"

RadioPage::RadioPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioPage)
{
    ui->setupUi(this);
}

RadioPage::~RadioPage()
{
    delete ui;
}
