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
}

void MyServer::startServer(){
    if(!server -> listen(QHostAddress::Any, 8080)){
        qDebug() << "Server couldn't start! -- ERROR" << '\n';
    }
    else{
        qDebug() << "Server started on port 8080";
    }
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
        QString username = jsonObject["username"].toString();
        QFile userFile(QDir(usersInfoFolder).absoluteFilePath(username + ".txt"));


        qDebug() << username;
        try{
            userFile.open(QIODevice::ReadOnly);
            QByteArray storedHashedPassword = userFile.readLine().trimmed();
            QByteArray enteredPassword = jsonObject["password"].toString().toUtf8();
            QByteArray enteredHashedPassword = QCryptographicHash::hash(enteredPassword, QCryptographicHash::Sha256);


            if(QString(enteredHashedPassword.toHex()) != QString(storedHashedPassword)){
                qDebug() << "Password incorrect: " << username;
                socket -> write("Password error, try again");
                socket -> close();
            }else{
                // socket -> write("Login successful!");
                searchAndSendDecks(socket, username);
            }

        }catch(const QFile::FileError& error){
            qDebug() << "Username incorrect or file error: " << username;
            socket -> write("Username error, try again");
            socket -> close();
        }


        // searchAndSendDecks(socket, username);
    }/* else if (action == "upload") {
        // Assuming you will include the username in the upload request
        QString username = jsonObject["username"].toString();
        QString deckName = jsonObject["deckName"].toString();
        QByteArray deckData = socket->readAll();
        saveDeckForUser(username, deckName, deckData);
        socket->write("Upload successful");
        socket->close();
    }*/
}

void MyServer::newConnection(){
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyServer::readData);

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

    socket->close();
}

void MyServer::saveDeck(const QString& deckName, const QByteArray& deckData){
    QString filePath = publicDecksFolder + "/" + deckName;
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly)){
        file.write(deckData);
        file.close();
        qDebug() << "Deck saved: " << filePath;
    }
    else{
        qDebug() << "Error saving deck: " << file.errorString();
    }
}
