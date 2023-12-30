#include "lib/createdeckwindow.h"
#include "lib/card.h"
#include "lib/jsonserializer.h"
#include "lib/serializer.h"
#include "lib/servercommunicator.h"
#include "ui_createdeckwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

CreateDeckWindow::CreateDeckWindow(User &user, QWidget *parent)
	: QWidget(parent), ui(new Ui::CreateDeckWindow), m_user(user)
{
	ui->setupUi(this);
}

CreateDeckWindow::CreateDeckWindow(QString name, Privacy privacy, User &user, QWidget *parent)
    : QWidget(parent), ui(new Ui::CreateDeckWindow), m_deck(name, user, privacy), m_user(user)
{
	ui->setupUi(this);

	m_questionDifficulty = new QButtonGroup(this);
	m_questionDifficulty->addButton(ui->radioButton_easy, Difficulty::EASY);
	m_questionDifficulty->addButton(ui->radioButton_medium, Difficulty::MEDIUM);
	m_questionDifficulty->addButton(ui->radioButton_hard, Difficulty::HARD);

	m_questionDifficulty->setExclusive(false);
	m_questionDifficulty->checkedButton()->setChecked(false);
	m_questionDifficulty->setExclusive(true);
}

CreateDeckWindow::~CreateDeckWindow()
{
	delete ui;
    delete m_questionDifficulty;
}

QString CreateDeckWindow::getQuestionText() const
{
	return ui->textEdit_question->toPlainText();
}

QString CreateDeckWindow::getAnswerText() const
{
	return ui->textEdit_answer->toPlainText();
}

Difficulty CreateDeckWindow::getDifficulty() const
{
    return (Difficulty)m_questionDifficulty->checkedId();
}

void CreateDeckWindow::on_pushButton_finish_clicked()
{
	QJsonObject requestObject;

	generateId();

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_deck);

	qDebug() << doc;

	requestObject["action"] = "saveDeck";
	requestObject["username"] = m_user.username();
	requestObject["deck"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);
	ServerCommunicator communicator;
	QJsonObject jsonObj = communicator.sendRequest(request);

	if(jsonObj["status"].toString() != "success"){
		//TODO Juca Translation
		QMessageBox::information(this,"Kreiranje špila" ,"Došlo je do greške, špil nije sačuvan, probajte ponovo!");
		return;
	}

	QMessageBox::information(this, "Uspešno kreiran špil", "Vaš špil je uspešno kreiran i sačuvan!");

	close();
}

void CreateDeckWindow::generateId()
{
		QJsonObject requestObject;

		requestObject["action"] = "generateId";

		ServerCommunicator communicator;
		QJsonDocument request(requestObject);

		QJsonObject idObject = communicator.sendRequest(request);

		m_deck.setId(idObject.value("DeckId").toVariant().toULongLong());

        emit writeGeneratedID(m_deck.name() + "_" + QString::number(m_deck.deckId()) + "_deck.json");
        qDebug() << "send " << m_deck.name() + "_" + QString::number(m_deck.deckId());
}

void CreateDeckWindow::on_pushButton_add_clicked()
{
	QString m_question = getQuestionText();
	QString m_answer = getAnswerText();
	Difficulty m_difficulty = getDifficulty();

	if (m_question.trimmed().isEmpty() or m_answer.trimmed().isEmpty() or m_questionDifficulty->checkedId() == -1) {
		QMessageBox::warning(this, "Pogrešan unos", "Niste popunili sva neophodna polja!");
		return;
	}

	Card *card = new Card(m_question, m_answer, m_difficulty);

	m_deck.addCard(card);

	ui->textEdit_question->clear();
	ui->textEdit_answer->clear();

	m_questionDifficulty->setExclusive(false);
	m_questionDifficulty->checkedButton()->setChecked(false);
	m_questionDifficulty->setExclusive(true);
}

