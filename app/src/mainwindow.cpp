#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createDeckButton_clicked()
{
    CreateDeckDialog popUp;
//    this->close();
    popUp.exec();
}

