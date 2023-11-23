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

void CreateDeckWindow::on_finishedButton_clicked()
{
    // TODO save created deck
    close();
}


void CreateDeckWindow::on_addNewButton_clicked()
{
    // TODO add card to deck
    ui->questionTextEdit->clear();
    ui->answerTextEdit->clear();
}

