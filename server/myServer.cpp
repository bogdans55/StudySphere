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

    uniqueIdsFile = "uniqueIds.txt";

    plannerFolder = "plannerFolder";
    QDir().mkpath(plannerFolder);
}

MyServer::~MyServer() {
    qDebug() << "Desc";
    //writeRemainingIDsToFile();
}

void MyServer::startServer(){
    if(!server -> listen(QHostAddress::Any, 8080)){
        qDebug() << "Server couldn't start! -- ERROR" << '\n';
    }
    else{
        //writeNumbers();
        qDebug() << "Server started on port 8080";
    }
}

void MyServer::loadIds(){
    QFile idsFile(uniqueIdsFile);

    if(idsFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray fileData = idsFile.readAll();
        QList<QByteArray> lines = fileData.split('\n');

        for(auto& line : lines){
            ids.append(line);
        }
    }
    else{
        qDebug() << "Couldn't open file: " << uniqueIdsFile;
    }
    idsFile.close();
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
            // sendDeckById(socket, username, 1);
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
        qDebug() << "Deck is saving";
        saveDeck(socket, jsonObject);
    }else if(action == "register"){
        registerUser(socket, jsonObject);
    }else if(action == "removeDeck"){
        removeDeck(socket, jsonObject);
    }else if(action == "generateId"){
        loadIds();
        sendId(socket);
        writeRemainingIDsToFile();
    }else if(action == "sendDeck"){
        sendDeckById(socket, jsonObject["username"].toString(), jsonObject["DeckId"].toString());
    }else if(action == "savePlanner"){
        QJsonObject planner = jsonObject["planner"].toObject();
        savePlanner(socket, jsonObject["username"].toString(), planner);
    }else if(action == "getPlanner"){
        sendPlanner(socket, jsonObject["username"].toString());
    }

    socket ->close();
}

void MyServer::newConnection(){
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyServer::readData);

}

void MyServer::savePlanner(QTcpSocket* socket, const QString& username, QJsonObject& jsonObject){

    QString filePath = QDir(plannerFolder).absoluteFilePath(username + ".json");
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << QJsonDocument(jsonObject).toJson();
        file.close();
        qDebug() << "Planner saved on path: " << filePath;
    }else{
        qDebug() << "Error saving deck:" << file.errorString();
    }

    QJsonObject response;
    response["status"] = "Planner saved successfully";
}

void MyServer::sendPlanner(QTcpSocket* socket, const QString& username){

    QString filePath = QDir(plannerFolder).absoluteFilePath(username + ".json");
    QFile file(filePath);
    QJsonObject response;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray plannerData = file.readAll();
        response["planner"] = QJsonDocument::fromJson(plannerData).object();
        response["status"] = "Successful!";
        file.close();
    }else{
        response["status"] = "Error getting planner!";
        qDebug() << "Error opening planner file:" << file.errorString();
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();
}


void MyServer::removeDeck(QTcpSocket* socket, QJsonObject& jsonObject){

    QString username = jsonObject["username"].toString();
    QString deckID = QString::number(jsonObject["DeckId"].toDouble());
    QString deckName = jsonObject["DeckName"].toString();
    QDir deckFolder(QDir(QDir(userDecksFolder).absoluteFilePath(username)));
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
            else{
                response["status"] = "Couldn't open deck!";
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
    QDir userFolder(QDir(userDecksFolder).absoluteFilePath(username));
    QStringList userFilters;

    QJsonObject response;

    QStringList userDeckDirectories = userFolder.entryList(userFilters, QDir::Dirs | QDir::NoDotAndDotDot);

    if(!userDeckDirectories.isEmpty()){
        response["status"] = "success";
        QStringList foundDecks;


        QStringList deckFilters;
        deckFilters << "*.json";

        for(const QString &folderName : userDeckDirectories){
            QDir deckFolder(userFolder.absoluteFilePath(folderName));
            for(const QString& deckFile : deckFolder.entryList(deckFilters)){
                foundDecks.append(deckFile);
            }
        }

        if (!foundDecks.isEmpty()) {
            response["decks"] = foundDecks.join(", ");
        } else {
            response["status"] = "no results";
        }
    }
    else{
        response["status"] = "no results";
    }

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();
}

void MyServer::sendDeckById(QTcpSocket* socket, const QString& username, const QString& deckId){
    QDir userFolder(QDir(userDecksFolder).absoluteFilePath(username));
    QStringList userFilters;
    userFilters << "*_" + deckId;
    QJsonObject response;

    QStringList userDeckDirectories = userFolder.entryList(userFilters, QDir::Dirs | QDir::NoDotAndDotDot);

    if(!userDeckDirectories.isEmpty()){
        response["status"] = "success";
        QStringList foundDecks;


        QStringList deckFilters;
        deckFilters << "*.json";

        for(const QString &folderName : userDeckDirectories){
            QDir deckFolder(userFolder.absoluteFilePath(folderName));
            for(const QString& deckName : deckFolder.entryList(deckFilters)){
                foundDecks.append(deckName);

                QFile deckFile(deckFolder.absoluteFilePath(deckName));
                if(deckFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                    QByteArray deckData = deckFile.readAll();
                    response[deckName] = QJsonDocument::fromJson(deckData).object();
                    deckFile.close();
                }else{
                    response["status"] = "Couldn't open deck!";
                    qDebug() << response["status"].toString();
                }
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
    QDir().mkdir(QDir(QDir(userDecksFolder).absoluteFilePath(username)).absoluteFilePath(deckName + "_" + deckID));
    QString filePath = QDir(QDir(QDir(userDecksFolder).absoluteFilePath(username)).absoluteFilePath(deckName + "_" + deckID)).absoluteFilePath(deckName + "_" + deckID + ".json");

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


    QDir users(usersInfoFolder);
    QJsonObject response;

    for(const QString &fileName : users.entryList()){
        if(fileName.split(".")[0] == username){
            response["status"] = "Username already exists, try again";
            QTextStream stream(socket);
            stream << QJsonDocument(response).toJson();
            return;
        }
    }

    QFile userFile(QDir(usersInfoFolder).absoluteFilePath(username + ".txt"));



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

uint64_t MyServer::generateUniqueId(){
    QString id = ids.front();
    ids.pop_front();
    return id.toULongLong();
}

void MyServer::sendId(QTcpSocket* socket){
    QJsonObject response;
    response["status"] = "Id generated";
    uint64_t id = generateUniqueId();
    response["DeckId"] = qint64(id);

    QTextStream stream(socket);
    stream << QJsonDocument(response).toJson();
}

void MyServer::writeRemainingIDsToFile() {
    QFile file(uniqueIdsFile);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (const QString& id : ids) {
            out << id << '\n';
        }

        file.close();
    }
    else{
        qDebug() << "Couldn't open file: " << uniqueIdsFile;
    }
}

// void MyServer::writeNumbers(){
//     QFile file(uniqueIdsFile);
//     qDebug() << file.filesystemFileName();
//     if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//         QTextStream out(&file);
//         qDebug() << "pisem";
//         for (int i = 1; i <= 1000000; ++i) {
//             out << QString::number(i) << '\n';
//         }

//         file.close();
//     } else {
//         qDebug() << "Couldn't open file for writing.";
//     }
// }

// void MyServer::makePublic(QTcpSocket* socket, QJsonObject& jsonObject){
//     QString username = jsonObject["username"].toString();
//     QString deckID = QString::number(jsonObject["DeckId"].toDouble());

//     QString userDeckPath = QDir(userDecksFolder).absoluteFilePath(username).absoluteFilePath(deckName + "_" + deckID + ".json");
//     QFile userDeckFile(userDeckPath);

//     if (!userDeckFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         // Handle error: Unable to open user's deck file
//         return;
//     }

//     QByteArray deckData = userDeckFile.readAll();
//     userDeckFile.close();
// }



