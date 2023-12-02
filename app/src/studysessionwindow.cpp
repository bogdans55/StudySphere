#include "lib/studysessionwindow.h"
#include "ui_studysessionwindow.h"

StudySessionWindow::StudySessionWindow(QWidget *parent) :
    QWidget(parent),
    m_session(),
    ui(new Ui::StudySessionWindow)
{
    ui->setupUi(this);
}

StudySessionWindow::StudySessionWindow(QWidget *parent, const StudySession& session) :
    QWidget(parent),
    m_session(session),
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
    if(!session().getCurrentCard().answerShowed())
        ui->cardTextEdit->setText(session().getCurrentCard().questionText());
    else
        ui->cardTextEdit->setText(session().getCurrentCard().questionAnswer());

    session().getCurrentCard().flipCard();
}


void StudySessionWindow::on_skipPushButton_clicked()
{
    session().getCurrentCard().evaluateAnswer(0);
    session().nextCard();
    ui->cardTextEdit->setText(session().getCurrentCard().questionText());
}


void StudySessionWindow::on_badPushButton_clicked()
{
    session().getCurrentCard().evaluateAnswer(1);
    session().nextCard();
    ui->cardTextEdit->setText(session().getCurrentCard().questionText());
}


void StudySessionWindow::on_midPushButton_clicked()
{
    session().getCurrentCard().evaluateAnswer(2);
    session().nextCard();
    ui->cardTextEdit->setText(session().getCurrentCard().questionText());
}


void StudySessionWindow::on_goodPushButton_clicked()
{
    session().getCurrentCard().evaluateAnswer(3);
    session().nextCard();
    ui->cardTextEdit->setText(session().getCurrentCard().questionText());
}

