#include "lib/studysessionwindow.h"
#include "ui_studysessionwindow.h"

StudySessionWindow::StudySessionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow),
    m_session()
{
    ui->setupUi(this);
}

StudySessionWindow::StudySessionWindow(const StudySession& session, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow),
    m_session(session)
{
    ui->setupUi(this);
}

StudySessionWindow::~StudySessionWindow()
{
    delete ui;
}

void StudySessionWindow::setSession(const StudySession &session)
{
    m_session = session;
}

void StudySessionWindow::on_pushButton_flip_clicked()
{
    if(!session().getCurrentCard().answerShowed())
        ui->textEdit_card->setText(session().getCurrentCard().questionText());
    else
        ui->textEdit_card->setText(session().getCurrentCard().questionAnswer());

    session().getCurrentCard().flipCard();
}


void StudySessionWindow::on_pushButton_skip_clicked()
{
    session().getCurrentCard().evaluateAnswer(0);
    session().nextCard();
    ui->textEdit_card->setText(session().getCurrentCard().questionText());
}


void StudySessionWindow::on_pushButton_bad_clicked()
{
    session().getCurrentCard().evaluateAnswer(1);
    session().nextCard();
    ui->textEdit_card->setText(session().getCurrentCard().questionText());
}


void StudySessionWindow::on_pushButton_mid_clicked()
{
    session().getCurrentCard().evaluateAnswer(2);
    session().nextCard();
    ui->textEdit_card->setText(session().getCurrentCard().questionText());
}


void StudySessionWindow::on_pushButton_good_clicked()
{
    session().getCurrentCard().evaluateAnswer(3);
    session().nextCard();
    ui->textEdit_card->setText(session().getCurrentCard().questionText());
}

