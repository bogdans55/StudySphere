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
