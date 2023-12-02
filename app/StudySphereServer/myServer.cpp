#include "myServer.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QFile>


MyServer::MyServer(QObject* parent) : QObject(parent){
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MyServer::newConnection);

    publicDecksFolder = "publicDecks";
    QDir().mkpath(publicDecksFolder);
}

void MyServer::startServer(){
    if(!server -> listen(QHostAddress::Any, 8080)){
        qDebug() << "Server couldn't start! -- ERROR" << '\n';
    }
    else{
        qDebug() << "Server started on port 8080";
    }
}

void MyServer::newConnection(){
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyServer::readData);

}


void MyServer::searchAndSendDecks(QTcpSocket* socket, const QString& searchQuery){
    QDir deckFolder(".");
    QStringList filters;

    filters << "*.json";

    QStringList foundDecks;

    QJsonObject response;

    for(const QString &fileName : deckFolder.entryList(filters)){
        if(fileName.contains(searchQuery, Qt::CaseInsensitive)){
            foundDecks.append(fileName);
        }
    }

    if(!foundDecks.isEmpty()){
        response["status"] = "success";
        //TODO find more elegant solution to pack found decks in response
        response["decks"] = foundDecks.join(", ");

        for(const QString& deckName : foundDecks){
            QFile deckFile(deckName);
            if(deckFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                QByteArray deckData = deckFile.readAll();
                QTextStream stream(socket);
                stream << deckData;
                socket->flush();
                deckFile.close();
            }
        }
    }
    else{
        response["status"] = "no results";
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();

    socket->close();
}
