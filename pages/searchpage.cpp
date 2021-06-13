#include "searchpage.h"
#include "ui_searchpage.h"

SearchPage::SearchPage(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SearchPage)
{
    ui->setupUi(this);
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::setDeezerApiInstance(api::Deezer * deezerApiInstance)
{
    this->deezerApiInstance = deezerApiInstance;
}
