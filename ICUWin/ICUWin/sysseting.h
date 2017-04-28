#ifndef SYSSETING_H
#define SYSSETING_H

#include <QDialog>

namespace Ui {
class SysSeting;
}

class SysSeting : public QDialog
{
    Q_OBJECT

public:
    explicit SysSeting(QWidget *parent = 0);
    ~SysSeting();

private:
    Ui::SysSeting *ui;
};

#endif // SYSSETING_H
