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

void SysSeting::on_pushButton_apply_clicked()
{
    if(ui->radioButton_showRR->isChecked())
    {
        sys.Show_RR_RI=1;
    }else
    {
        sys.Show_RR_RI=0;
    }
    this->close();
}
