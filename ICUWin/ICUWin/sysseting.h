#ifndef SYSSETING_H
#define SYSSETING_H

#include <QDialog>
#include "sys.h"
namespace Ui {
class SysSeting;
}

class SysSeting : public QDialog
{
    Q_OBJECT

public:
    explicit SysSeting(QWidget *parent = 0);
    ~SysSeting();

private slots:
    void on_pushButton_apply_clicked();

private:
    Ui::SysSeting *ui;
};

#endif // SYSSETING_H
