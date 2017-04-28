#include "datareplay.h"
#include "ui_datareplay.h"

DataReplay::DataReplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataReplay)
{
    ui->setupUi(this);
}

DataReplay::~DataReplay()
{
    delete ui;
}
