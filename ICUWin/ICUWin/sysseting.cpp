#include "sysseting.h"
#include "ui_sysseting.h"

SysSeting::SysSeting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysSeting)
{
    ui->setupUi(this);
}

SysSeting::~SysSeting()
{
    delete ui;
}
