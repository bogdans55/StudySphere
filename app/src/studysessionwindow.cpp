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

void StudySessionWindow::on_flipPushButton_clicked()
{
    // TODO flip card (show answer/question)
}


void StudySessionWindow::on_skipPushButton_clicked()
{
    // TODO skip question and load next card
}


void StudySessionWindow::on_badPushButton_clicked()
{
    // TODO save users grade and load next card
}


void StudySessionWindow::on_midPushButton_clicked()
{
    // TODO save users grade and load next card
}


void StudySessionWindow::on_goodPushButton_clicked()
{
    // TODO save users grade and load next card
}

