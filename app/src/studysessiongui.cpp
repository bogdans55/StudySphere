#include "lib/studysessiongui.h"
#include "ui_studysessiongui.h"

StudySessionGUI::StudySessionGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionGUI)
{
    ui->setupUi(this);
}

StudySessionGUI::~StudySessionGUI()
{
    delete ui;
}

void StudySessionGUI::on_flipPushButton_clicked()
{
    // TODO flip card (show answer/question)
}


void StudySessionGUI::on_skipPushButton_clicked()
{
    // TODO skip question and load next card
}


void StudySessionGUI::on_badPushButton_clicked()
{
    // TODO save users grade and load next card
}


void StudySessionGUI::on_midPushButton_clicked()
{
    // TODO save users grade and load next card
}


void StudySessionGUI::on_goodPushButton_clicked()
{
    // TODO save users grade and load next card
}

