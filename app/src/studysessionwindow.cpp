#include "lib/studysessionwindow.h"
#include "ui_studysessionwindow.h"

#include <QMessageBox>

StudySessionWindow::StudySessionWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui::StudySessionWindow), m_session(new StudySession())
{
	ui->setupUi(this);
	m_session->startSession();
	ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
}

StudySessionWindow::StudySessionWindow(StudySession *session, QWidget *parent)
	: QWidget(parent), ui(new Ui::StudySessionWindow), m_session(session)
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
	if (m_session->answerShowed())
		ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
	else
		ui->textEdit_card->setText(m_session->getCurrentCard().questionAnswer());

	m_session->flipCard();
}

void StudySessionWindow::evaluate(int grade) // TODO should be enum grade
{
	m_session->getCurrentCard().evaluateAnswer(grade);
	if (m_session->hasNextCard()) {
		m_session->nextCard();
		ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
	}
	else {
		QMessageBox::information(this, "Gotova sesija", "Uspešno ste prešli sva odabrana pitanja!");
		close();
	}
}

void StudySessionWindow::on_pushButton_skip_clicked()
{
	evaluate(0);
}

void StudySessionWindow::on_pushButton_bad_clicked()
{
	evaluate(1);
}

void StudySessionWindow::on_pushButton_mid_clicked()
{
	evaluate(2);
}

void StudySessionWindow::on_pushButton_good_clicked()
{
	evaluate(3);
}
