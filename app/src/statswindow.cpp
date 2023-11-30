#include "lib/statswindow.h"
#include "ui_statswindow.h"

StatsWindow::StatsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
}

StatsWindow::~StatsWindow()
{
    delete ui;
}
