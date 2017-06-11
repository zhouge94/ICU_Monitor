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
    sys.spo2_A=ui->lineEdit_spo2_A->text().toFloat();
    sys.spo2_B=ui->lineEdit_spo2_B->text().toFloat();
    sys.xueya_A=ui->lineEdit_xueya_A->text().toFloat();
    sys.xueya_B=ui->lineEdit_xueya_B->text().toFloat();
    sys.plot_range_TRange_Hx=ui->doubleSpinBox_hxtime->value();
    sys.plot_range_TRange_EcgMb=ui->doubleSpinBox_ecgtime->value();
    this->close();
}

void SysSeting::on_pushButton_cancal_clicked()
{
    this->close();
}
