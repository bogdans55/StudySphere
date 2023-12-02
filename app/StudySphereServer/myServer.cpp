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

