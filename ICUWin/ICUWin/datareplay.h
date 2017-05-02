#ifndef DATAREPLAY_H
#define DATAREPLAY_H

#include <QDialog>
#include "qcustomplot.h"
#include "my_cvs.h"
#include "iostream"
#include "filter.h"
#include "sys.h"
namespace Ui {
class DataReplay;
}

class DataReplay : public QDialog
{
    Q_OBJECT

public:
    explicit DataReplay(QWidget *parent = 0);
    ~DataReplay();
    Ui::DataReplay *ui;

private slots:
    void on_Bt_Play_clicked();

private:
    void setupRealtimeData(QCustomPlot *customPlot);
    void Play();
};

#endif // DATAREPLAY_H
