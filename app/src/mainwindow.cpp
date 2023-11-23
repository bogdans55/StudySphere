#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
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
    CreateDeckDialog popUp(this);
    if (popUp.exec() == QDialog::Accepted) {
        CreateDeckWindow *createDeck = new CreateDeckWindow();
        createDeck->setAttribute(Qt::WA_DeleteOnClose);
        createDeck->show();
        QString name = popUp.getDeckName();
        int privacy = popUp.getDeckPrivacy(); // should be changed to Privacy
//        qDebug() << name << ' ' << privacy;
    }
}

