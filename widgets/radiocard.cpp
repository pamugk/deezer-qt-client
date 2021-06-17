#include "radiocard.h"
#include "ui_radiocard.h"

RadioCard::RadioCard(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::RadioCard)
{
    ui->setupUi(this);
}

RadioCard::~RadioCard()
{
    delete ui;
}
