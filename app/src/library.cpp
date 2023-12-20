#include "lib/library.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>

Library::Library()
{
	// TODO delete hardcoded path, and make so that user can define path where the decks will be stored
	loadDecksFromFolder("../sampleData/privateDecks");
}

Library &Library::instance()
{
	static Library instance;
	return instance;
}

void Library::addDeck(const Deck &deck)
{
	m_decks.push_back(deck);
}

void Library::loadDecksFromFolder(const QString folderPath)
{
	QDir deckFolder(folderPath);

	QStringList nameFilters;
	nameFilters << "*.json";
	deckFolder.setNameFilters(nameFilters);

	QStringList deckFiles = deckFolder.entryList();

	for (const QString &deckFile : deckFiles) {
		QString filePath = deckFolder.filePath(deckFile);
		importDeck(filePath);
	}
}

void removeDeck(Deck &deck, QString &username)
{
	/*

		QTcpSocket socket;
		socket.connectToHost("127.0.0.1", 8080);

		if(socket.waitForConnected()){
			QJsonObject request;
			request["action"] = "removeDeck";
			request["username"] = username;
			request["DeckId"] = QString::number(deck.deckId());
			request["DeckName"] = deck.name();

			socket.write(QJsonDocument(request).toJson());
			socket.waitForBytesWritten();
			socket.waitForReadyRead();

			QByteArray responseData = socket.readAll();
			QTextStream stream(responseData);

			qDebug() << "Recieved Data:";

			while (!stream.atEnd()) {
				qDebug() << stream.readLine();
			}

			QString filePath = deck.getFilePath();

			QFile file(filePath);
			if(file.remove()){
				qDebug() << "File removed: " << filePath;
			}
			else{
				qDebug() << "Failed to remove file: " << filePath;
				//TODO error handling if needed...
			}
		}*/
}

void Library::importDeck(const QString &filePath)
{

	/*QFile file(filePath);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
		QJsonDocument document = QJsonDocument::fromJson(file.readAll());
		QJsonArray deckArray = document.array();

		for(const QJsonValue& deckValue : deckArray){
			Deck deck;
			deck.fromJson(deckValue.toObject());
			m_decks.push_back(deck);
		}
		file.close();
	}*/
}

void Library::exportDeck(const QVector<Deck> &decks, const QString &filePath)
{
	/*QJsonArray deckArray;
	for(const Deck& deck : decks){
		deckArray.append(deck.toJson());
	}

	QJsonDocument document(deckArray);

	QFile file(filePath);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
		file.write(document.toJson());
		file.close();
	}*/
}
