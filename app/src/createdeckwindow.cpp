#include "lib/createdeckwindow.h"
#include "ui_createdeckwindow.h"

CreateDeckWindow::CreateDeckWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDeckWindow)
{
    ui->setupUi(this);
}

CreateDeckWindow::~CreateDeckWindow()
{
    delete ui;
}
