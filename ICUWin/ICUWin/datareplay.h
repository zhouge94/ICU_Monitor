#ifndef DATAREPLAY_H
#define DATAREPLAY_H

#include <QDialog>

namespace Ui {
class DataReplay;
}

class DataReplay : public QDialog
{
    Q_OBJECT

public:
    explicit DataReplay(QWidget *parent = 0);
    ~DataReplay();

private:
    Ui::DataReplay *ui;
};

#endif // DATAREPLAY_H
