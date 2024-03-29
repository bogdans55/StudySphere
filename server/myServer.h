#ifndef MYSERVER_H
#define MYSERVER_H

#include "Privacy.h"
#include <QJsonObject>
#include <QObject>
#include <QTcpServer>

class MyServer : public QObject
{
	Q_OBJECT

  public:
	explicit MyServer(QObject *parent = nullptr);
	~MyServer();

  signals:

  public slots:
	void startServer();

  private slots:
	void newConnection();

  private:
	QTcpServer *server;
	QString publicDecksFolder;
	QString usersInfoFolder;
	QString userDecksFolder;
	QString uniqueIdsFile;
	QVector<QString> ids;
	QString calendarFolder;
	QString plannerFolder;
	QString todoFolder;

	void registerUser(QTcpSocket *socket, QJsonObject &jsonObject);
	void loginUser(QTcpSocket *socket, QJsonObject &jsonObject);
	void sendUserDecks(QTcpSocket *socket, const QString &searchQuery);
	void searchAndSendDecks(QTcpSocket *socket, const QString &searchQuery);
	void saveDeck(QTcpSocket *socket, QJsonObject &jsonObject);
	void saveDeckForUser(const QString &username, const QString &deckName, QByteArray &deckData);
	void removeDeck(QTcpSocket *socket, QJsonObject &jsonObject);
	void sendId(QTcpSocket *socket);
	void readData();
	uint64_t generateUniqueId();
	void loadIds();
	void writeRemainingIDsToFile();
	void writeNumbers();
	bool makePublic(QJsonObject &jsonObject);
	void sendDeckById(QTcpSocket *socket, const QString &username, const QString &deckId, Privacy &privacy);
	void savePlanner(QTcpSocket *socket, const QString &username, QJsonObject &jsonObject);
	void getPlanner(QTcpSocket *socket, const QString &username);
	void saveCalendar(QTcpSocket *socket, const QString &username, QJsonObject &jsonObject);
	void getCalendar(QTcpSocket *socket, const QString &username);
	void saveTodo(QTcpSocket *socket, const QString &username, QJsonObject &jsonObject);
	void getTodo(QTcpSocket *socket, const QString &username);
	void getStats(QTcpSocket *socket, const QString &username, const QString &deckId);
	void createUniqueIdsFile();
};

#endif // MYSERVER_H
