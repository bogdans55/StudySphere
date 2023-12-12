#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QJsonObject>

class MyServer : public QObject{
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);

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

    void registerUser(QTcpSocket* socket, QJsonObject& jsonObject);
    void loginUser(QTcpSocket* socket, QJsonObject& jsonObject);
    void sendUserDecks(QTcpSocket* socket, const QString& searchQuery);
    void searchAndSendDecks(QTcpSocket* socket, const QString& searchQuery);
    void saveDeck(QTcpSocket* socket, QJsonObject& jsonObject);
    void saveDeckForUser(const QString& username, const QString& deckName, QByteArray& deckData);
    void removeDeck(QTcpSocket* socket, QJsonObject& jsonObject);
    void readData();
};

#endif // MYSERVER_H
