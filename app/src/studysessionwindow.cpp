#include "lib/studysessionwindow.h"
#include "lib/jsonserializer.h"
#include "lib/serializer.h"
#include "lib/servercommunicator.h"
#include "ui_studysessionwindow.h"

#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

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
	connect(this, &StudySessionWindow::destroyed, this, &StudySessionWindow::closeWhiteboard);
    setDifficultyColor();
}

StudySessionWindow::~StudySessionWindow()
{
	delete ui;
	delete m_session;
}

void StudySessionWindow::on_pushButton_flip_clicked()
{
	if (m_session->answerShowed()) {
		ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
		ui->label_card->setText("Pitanje");
	}
	else {
		ui->textEdit_card->setText(m_session->getCurrentCard().questionAnswer());
		ui->label_card->setText("Odgovor");
	}

	m_session->flipCard();
}

void StudySessionWindow::evaluate(int grade) // TODO should be enum grade
{
	m_session->deckStats()->addGrade(m_session->currentCardIndex(), grade);
	if (m_session->hasNextCard()) {
		m_session->nextCard();
		ui->textEdit_card->setText(m_session->getCurrentCard().questionText());
		ui->label_card->setText("Pitanje");
        setDifficultyColor();
	}
	else {
		QMessageBox::information(this, "Gotova sesija", "Uspešno ste prešli sva odabrana pitanja!");
		m_session->endSession();

		QJsonObject requestObject;

		JSONSerializer serializer;
		QJsonDocument doc = serializer.createJson(*(m_session->deckStats()));

		qDebug() << doc;

		requestObject["action"] = "saveDeck";
		requestObject["username"] = m_session->user().username();
		requestObject["deck"] = serializer.createJson(*(m_session->deck())).toVariant().toJsonObject();
		requestObject["deckStats"] = doc.toVariant().toJsonObject();

		QJsonDocument request(requestObject);
		ServerCommunicator communicator;
		QJsonObject jsonObj = communicator.sendRequest(request);

		if (jsonObj["status"].toString() != "success") {
			// TODO Juca Translation
			QMessageBox::information(this, "Greška",
									 "Došlo je do greške, statistike za poslednje učenje nisu sačuvane!");
			return;
		}
		if (m_whiteboard != nullptr) {
			m_whiteboard->close();
			delete m_whiteboard;
			m_whiteboard = nullptr;
		}
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

void StudySessionWindow::on_pushButton_whiteboard_clicked()
{
	m_whiteboard = new WhiteboardWindow();
	connect(m_whiteboard, &WhiteboardWindow::destroyed, this, &StudySessionWindow::clearWhiteboard);
	m_whiteboard->setAttribute(Qt::WA_DeleteOnClose);
	m_whiteboard->show();
}

void StudySessionWindow::closeWhiteboard()
{
	if (m_whiteboard != nullptr) {
		m_whiteboard->close();
	}
}

void StudySessionWindow::clearWhiteboard()
{
	if (m_whiteboard != nullptr) {
        m_whiteboard = nullptr;
    }
}

void StudySessionWindow::setDifficultyColor()
{
    if (m_session->getCurrentCard().questionDifficulty() == Difficulty::EASY)
        ui->toolButton_difficulty->setStyleSheet("background-color: green; border-radius: 10px;");
    else if (m_session->getCurrentCard().questionDifficulty() == Difficulty::MEDIUM)
        ui->toolButton_difficulty->setStyleSheet("background-color: yellow; border-radius: 10px;");
    else if (m_session->getCurrentCard().questionDifficulty() == Difficulty::HARD)
        ui->toolButton_difficulty->setStyleSheet("background-color: red; border-radius: 10px;");
}
