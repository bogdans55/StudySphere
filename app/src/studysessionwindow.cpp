#include "lib/studysessionwindow.h"
#include "ui_studysessionwindow.h"

StudySessionWindow::StudySessionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow),
    m_session()
{
    ui->setupUi(this);
    m_session.startSession();
    ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
}

StudySessionWindow::StudySessionWindow(const StudySession& session, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudySessionWindow),
    m_session(session)
{
    ui->setupUi(this);
    m_session.startSession();
    ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
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
    if(m_session.getCurrentCard().answerShowed())
        ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
    else
        ui->textEdit_card->setText(m_session.getCurrentCard().questionAnswer());

    m_session.getCurrentCard().flipCard();
}


void StudySessionWindow::on_pushButton_skip_clicked()
{
    m_session.getCurrentCard().evaluateAnswer(0);
    m_session.nextCard();
    ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
}


void StudySessionWindow::on_pushButton_bad_clicked()
{
    m_session.getCurrentCard().evaluateAnswer(1);
    m_session.nextCard();
    ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
}


void StudySessionWindow::on_pushButton_mid_clicked()
{
    m_session.getCurrentCard().evaluateAnswer(2);
    m_session.nextCard();
    ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
}


void StudySessionWindow::on_pushButton_good_clicked()
{
    m_session.getCurrentCard().evaluateAnswer(3);
    m_session.nextCard();
    ui->textEdit_card->setText(m_session.getCurrentCard().questionText());
}

