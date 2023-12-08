#include "lib/studysessionwindow.h"
#include "ui_studysessionwindow.h"

StudySessionWindow::StudySessionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow)
{
    ui->setupUi(this);
}

StudySessionWindow::~StudySessionWindow()
{
    delete ui;
}

void StudySessionWindow::on_pushButton_flip_clicked()
{
    // TODO flip card (show answer/question)
}


void StudySessionWindow::on_pushButton_skip_clicked()
{
    // TODO skip question and load next card
}


void StudySessionWindow::on_pushButton_bad_clicked()
{
    // TODO save users grade and load next card
}


void StudySessionWindow::on_pushButton_mid_clicked()
{
    // TODO save users grade and load next card
}


void StudySessionWindow::on_pushButton_good_clicked()
{
    // TODO save users grade and load next card
}

