#include "lib/studysessionwindow.h"
#include "ui_studysessionwindow.h"

StudySessionWindow::StudySessionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow),
    m_session(new StudySession())
{
    ui->setupUi(this);
    m_session->startSession();
    ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
}

StudySessionWindow::StudySessionWindow(StudySession *session, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow),
    m_session(session)
{
    ui->setupUi(this);
    m_session->startSession();
    ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
}

StudySessionWindow::~StudySessionWindow()
{
    delete ui;
}

void StudySessionWindow::on_pushButton_flip_clicked()
{
    if(m_session->answerShowed())
        ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
    else
        ui->textEdit_card->setText(m_session->getCurrentCard().questionAnswer());

    m_session->flipCard();
}


void StudySessionWindow::on_pushButton_skip_clicked()
{
    m_session->getCurrentCard().evaluateAnswer(0);
    if(m_session->hasNextCard()){
        m_session->nextCard();
        ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
    }
    else{
        close();
    }
}


void StudySessionWindow::on_pushButton_bad_clicked()
{
    m_session->getCurrentCard().evaluateAnswer(1);
    if(m_session->hasNextCard()){
        m_session->nextCard();
        ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
    }
    else{
        close();
    }
}


void StudySessionWindow::on_pushButton_mid_clicked()
{
    m_session->getCurrentCard().evaluateAnswer(2);
    if(m_session->hasNextCard()){
        m_session->nextCard();
        ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
    }
    else{
        close();
    }
}


void StudySessionWindow::on_pushButton_good_clicked()
{
    m_session->getCurrentCard().evaluateAnswer(3);
    if(m_session->hasNextCard()){
        m_session->nextCard();
        ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
    }
    else{
        close();
    }
}

