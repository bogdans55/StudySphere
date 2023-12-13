#include "myServer.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>


MyServer::MyServer(QObject* parent) : QObject(parent){
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MyServer::newConnection);

    publicDecksFolder = "publicDecks";
    QDir().mkpath(publicDecksFolder);

    usersInfoFolder = "usersInfo";
    QDir().mkpath(usersInfoFolder);

    userDecksFolder = "userDecks";
    QDir().mkpath(userDecksFolder);
}

void MyServer::startServer(){
    if(!server -> listen(QHostAddress::Any, 8080)){
        qDebug() << "Server couldn't start! -- ERROR" << '\n';
    }
    else{
        qDebug() << "Server started on port 8080";
    }
}

void MyServer::loginUser(QTcpSocket* socket, QJsonObject& jsonObject){
    QString username = jsonObject["username"].toString();
    QFile userFile(QDir(usersInfoFolder).absoluteFilePath(username + ".txt"));
    try{
        userFile.open(QIODevice::ReadOnly);
        QByteArray storedHashedPassword = userFile.readLine().trimmed();
        QByteArray enteredPassword = jsonObject["password"].toString().toUtf8();
        QByteArray enteredHashedPassword = QCryptographicHash::hash(enteredPassword, QCryptographicHash::Sha256);


        if(QString(enteredHashedPassword.toHex()) != QString(storedHashedPassword)){
            qDebug() << "Password incorrect: " << username;
            QJsonObject response;
            response["status"] = "Password incorrect, try again";

            QTextStream stream(socket);
            stream << QJsonDocument(response).toJson();
        }else{
            sendUserDecks(socket, username);
        }
    }catch(const QFile::FileError& error){
        qDebug() << "Username incorrect or file error: " << username;
        QJsonObject response;
        response["status"] = "Username error, try again";

        QTextStream stream(socket);
        stream << QJsonDocument(response).toJson();
    }
    socket -> close();
}

void MyServer::readData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = doc.object();

    QString action = jsonObject["action"].toString();

    if (action == "login") {
        loginUser(socket, jsonObject);
    }else if (action == "saveDeck") {
        saveDeck(socket, jsonObject);
    }else if(action == "register"){
        registerUser(socket, jsonObject);
    }else if(action == "removeDeck"){
        removeDeck(socket, jsonObject);
    }

    socket ->close();
}

void MyServer::newConnection(){
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyServer::readData);

}

void MyServer::removeDeck(QTcpSocket* socket, QJsonObject& jsonObject){

    QString username = jsonObject["username"].toString();
    QString deckID = QString::number(jsonObject["DeckId"].toDouble());
    QString deckName = jsonObject["DeckName"].toString();
    QDir deckFolder(QDir(userDecksFolder).absoluteFilePath(username));
    QJsonObject response;
    QString filePath = deckFolder.absoluteFilePath(deckName + "_" + deckID + ".json");

    if(QFile::remove(filePath)){
        response["status"] = "Successfuly removed deck" + deckID + ".json";
    }else{
        response["status"] = "Failed to remove deck";
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();
}

void MyServer::searchAndSendDecks(QTcpSocket* socket, const QString& searchQuery){
    QDir deckFolder(publicDecksFolder);
    QStringList filters;
    filters << "*.json";

    QStringList foundDecks;

    QJsonObject response;

    for(const QString &fileName : deckFolder.entryList(filters)){
        // if(fileName.contains(searchQuery, Qt::CaseInsensitive)){
        //     foundDecks.append(fileName);
        //     qDebug() << fileName << '\n';
        // }
        //Add search options, separate login from browser search
        foundDecks.append(fileName);
        qDebug() << fileName << '\n';
    }

    if(!foundDecks.isEmpty()){
        response["status"] = "success";
        //TODO find more elegant solution to pack found decks in response
        response["decks"] = foundDecks.join(", ");
        for(const QString& deckName : foundDecks){
            QFile deckFile(deckFolder.absoluteFilePath(deckName));
            if(deckFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                QByteArray deckData = deckFile.readAll();
                response[deckName] = QJsonDocument::fromJson(deckData).object();
                deckFile.close();
            }
        }
    }
    else{
        response["status"] = "no results";
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();

}


void MyServer::sendUserDecks(QTcpSocket* socket, const QString& username){
    QDir deckFolder(QDir(userDecksFolder).absoluteFilePath(username));
    QStringList filters;

    filters << "*.json";

    QStringList foundDecks;

    QJsonObject response;

    for(const QString &fileName : deckFolder.entryList(filters)){
        foundDecks.append(fileName);
        qDebug() << fileName << '\n';
    }

    if(!foundDecks.isEmpty()){
        response["status"] = "success";
        //TODO find more elegant solution to pack found decks in response
        response["decks"] = foundDecks.join(", ");
        for(const QString& deckName : foundDecks){
            QFile deckFile(deckFolder.absoluteFilePath(deckName));
            if(deckFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                QByteArray deckData = deckFile.readAll();
                response[deckName] = QJsonDocument::fromJson(deckData).object();
                deckFile.close();
            }
        }
    }
    else{
        response["status"] = "no results";
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();
}

void MyServer::saveDeck(QTcpSocket* socket, QJsonObject& jsonObject){
    QString username = jsonObject["username"].toString();

    QJsonObject deck = jsonObject["deck"].toObject();
    QString deckID = QString::number(deck["DeckId"].toDouble());
    QString deckName = deck["Subject"].toString();

    QString filePath = QDir(QDir(userDecksFolder).absoluteFilePath(username)).absoluteFilePath(deckName + "_" + deckID + ".json");

    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << QJsonDocument(deck).toJson();
        file.close();
        qDebug() << "Deck saved on path: " << filePath;
    }else{
        qDebug() << "Error saving deck:" << file.errorString();
    }

    QJsonObject response;
    response["status"] = "Upload Successful";
}

void MyServer::registerUser(QTcpSocket* socket, QJsonObject& jsonObject){
    QString username = jsonObject["username"].toString();
    QFile userFile(QDir(usersInfoFolder).absoluteFilePath(username + ".txt"));

    QJsonObject response;



    QDir users(usersInfoFolder);

    for(const QString &fileName : users.entryList()){
        if(fileName == username){
            socket->write("Username already exists, try again");
            return;
        }
    }

    try{
        userFile.open(QIODevice::WriteOnly);
        QByteArray enteredPassword = jsonObject["password"].toString().toUtf8();
        QByteArray enteredHashedPassword = QCryptographicHash::hash(enteredPassword, QCryptographicHash::Sha256);
        userFile.write(QByteArray(enteredHashedPassword.toHex()));
        userFile.close();

        QDir().mkdir(QDir(userDecksFolder).absoluteFilePath(username));

        response["status"] = "Register successful!";
    }catch(const QFile::FileError& error){
        qDebug() << "file error: " << username;
        response["status"] = "Registration not successful, try again";
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();
}
