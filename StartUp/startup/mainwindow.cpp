#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdlib.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_Start_clicked()
{
    this->hide();
    system("~/run.sh");
    this->showMaximized();
}

