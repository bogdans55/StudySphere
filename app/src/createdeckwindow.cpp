#include "lib/createdeckwindow.h"
#include "lib/card.h"
#include "lib/jsonserializer.h"
#include "lib/serializer.h"
#include "ui_createdeckwindow.h"

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
}

CreateDeckWindow::~CreateDeckWindow()
{
	delete ui;
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
	QTcpSocket socket;
	socket.connectToHost("127.0.0.1", 8080);

	if (socket.waitForConnected()) {
		QJsonObject request;

		generateId();

		JSONSerializer serializer;
		QJsonDocument doc = serializer.createJson(m_deck);

		qDebug() << doc;

		request["action"] = "saveDeck";
		request["username"] = m_user.username();
		request["deck"] = doc.toVariant().toJsonObject();

		qDebug() << request;

		socket.write(QJsonDocument(request).toJson());
		socket.waitForBytesWritten();
		socket.waitForReadyRead();

		QByteArray responseData = socket.readAll();
		QTextStream stream(responseData);

		qDebug() << responseData;

		qDebug() << "Recieved Data:";
		while (!stream.atEnd()) {
			qDebug() << stream.readLine();
		}

		socket.disconnectFromHost();

		QMessageBox::information(this, "Uspešno kreiran špil", "Vaš špil je uspešno kreiran i sačuvan!");

		//        delete m_deck;
	}
	else {
		qDebug() << "Failed to connect to the server";
	}

	close();
}

void CreateDeckWindow::generateId()
{

	QTcpSocket socket;
	socket.connectToHost("127.0.0.1", 8080);

	if (socket.waitForConnected()) {
		QJsonObject request;

		request["action"] = "generateId";
		socket.write(QJsonDocument(request).toJson());
		socket.waitForBytesWritten();
		socket.waitForReadyRead();
		QByteArray idResponse = socket.readAll();
		QTextStream idStream(idResponse);

		QString idResponseString = idStream.readAll();
		QJsonDocument idJson = QJsonDocument::fromJson(idResponseString.toUtf8());
		QJsonObject idObject = idJson.object();
		m_deck.setId(idObject.value("DeckId").toVariant().toULongLong());

		socket.disconnectFromHost();
	}
	else {
		qDebug() << "Failed to connect to the server";
	}
}

void CreateDeckWindow::on_pushButton_add_clicked()
{
	m_questionDifficulty = new QButtonGroup(this);
	m_questionDifficulty->addButton(ui->radioButton_easy, Difficulty::EASY);
	m_questionDifficulty->addButton(ui->radioButton_medium, Difficulty::MEDIUM);
	m_questionDifficulty->addButton(ui->radioButton_hard, Difficulty::HARD);

	QString m_question = getQuestionText();
	QString m_answer = getAnswerText();
	Difficulty m_difficulty = getDifficulty();

	Card *card = new Card(m_question, m_answer, m_difficulty);

	m_deck.addCard(card);

	ui->textEdit_question->clear();
	ui->textEdit_answer->clear();

	m_questionDifficulty->setExclusive(false);
	m_questionDifficulty->checkedButton()->setChecked(false);
	m_questionDifficulty->setExclusive(true);
}
