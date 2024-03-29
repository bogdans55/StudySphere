#include "myServer.h"
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

MyServer::MyServer(QObject *parent) : QObject(parent)
{
	server = new QTcpServer(this);
	connect(server, &QTcpServer::newConnection, this, &MyServer::newConnection);

	publicDecksFolder = "publicDecks";
	QDir().mkpath(publicDecksFolder);

	usersInfoFolder = "usersInfo";
	QDir().mkpath(usersInfoFolder);

	userDecksFolder = "userDecks";
	QDir().mkpath(userDecksFolder);

	uniqueIdsFile = "uniqueIds.txt";

	calendarFolder = "calendarFolder";
	QDir().mkpath(calendarFolder);

	plannerFolder = "plannerFolder";
	QDir().mkpath(plannerFolder);

	todoFolder = "todoFolder";
	QDir().mkpath(todoFolder);

	uniqueIdsFile = "uniqueIds.txt";
}

MyServer::~MyServer()
{
	qDebug() << "Desc";
	// writeRemainingIDsToFile();
}

void MyServer::startServer()
{
	if (!server->listen(QHostAddress::Any, 8080)) {
		qDebug() << "Server couldn't start! -- ERROR" << '\n';
	}
	else {
		// writeNumbers();
		createUniqueIdsFile();
		qDebug() << "Server started on port 8080";
	}
}

void MyServer::createUniqueIdsFile(){
    QFile file(uniqueIdsFile);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            for (int i = 1; i <= 100; ++i) {
                stream << i << "\n";
            }

            file.close();
            qDebug() << "File created and numbers written successfully.";
        } else {
            qDebug() << "Error: Unable to open the file for writing.";
        }
    } else {
        qDebug() << "File 'uniqueIds.txt' already exists.";
    }
}

void MyServer::loadIds()
{
	QFile idsFile(uniqueIdsFile);

	if (idsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QByteArray fileData = idsFile.readAll();
		QList<QByteArray> lines = fileData.split('\n');

		for (auto &line : lines) {
			ids.append(line);
		}
	}
	else {
		qDebug() << "Couldn't open file: " << uniqueIdsFile;
	}
	idsFile.close();
}

void MyServer::loginUser(QTcpSocket *socket, QJsonObject &jsonObject)
{
	QString username = jsonObject["username"].toString();
	QFile userFile(QDir(usersInfoFolder).absoluteFilePath(username + ".txt"));
	try {
		userFile.open(QIODevice::ReadOnly);
		QByteArray storedHashedPassword = userFile.readLine().trimmed();
		QByteArray enteredPassword = jsonObject["password"].toString().toUtf8();
		QByteArray enteredHashedPassword = QCryptographicHash::hash(enteredPassword, QCryptographicHash::Sha256);

		if (QString(enteredHashedPassword.toHex()) != QString(storedHashedPassword)) {
			qDebug() << "Password incorrect: " << username;
			QJsonObject response;
			response["status"] = "Password incorrect, try again";

			QTextStream stream(socket);
			stream << QJsonDocument(response).toJson();
		}
		else {
			sendUserDecks(socket, username);
		}
	}
	catch (const QFile::FileError &error) {
		qDebug() << "Username incorrect or file error: " << username;
		QJsonObject response;
		response["status"] = "Username error, try again";

		QTextStream stream(socket);
		stream << QJsonDocument(response).toJson();
	}
	socket->close();
}

void MyServer::readData()
{
	QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
	if (!socket)
		return;

	QByteArray data = socket->readAll();
	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject jsonObject = doc.object();

	QString action = jsonObject["action"].toString();
	Privacy privacy;
	if (jsonObject.contains("Privacy")) {
		privacy = jsonObject["Privacy"].toString() == "PRIVATE" ? Privacy::PRIVATE : Privacy::PUBLIC;
	}
	if (action == "login") {
		loginUser(socket, jsonObject);
	}
	else if (action == "saveDeck") {
		qDebug() << "Deck is saving";
		saveDeck(socket, jsonObject);
	}
	else if (action == "register") {
		registerUser(socket, jsonObject);
	}
	else if (action == "removeDeck") {
		removeDeck(socket, jsonObject);
	}
	else if (action == "generateId") {
		loadIds();
		sendId(socket);
		writeRemainingIDsToFile();
		ids.clear();
	}
	else if (action == "sendDeck") {
		sendDeckById(socket, jsonObject["username"].toString(), jsonObject["DeckId"].toString(), privacy);
	}
	else if (action == "saveCalendar") {
		QJsonObject planner = jsonObject["calendar"].toObject();
		saveCalendar(socket, jsonObject["username"].toString(), planner);
	}
	else if (action == "getCalendar") {
		getCalendar(socket, jsonObject["username"].toString());
	}
	else if (action == "savePlanner") {
		QJsonObject planner = jsonObject["planner"].toObject();
		savePlanner(socket, jsonObject["username"].toString(), planner);
	}
	else if (action == "getPlanner") {
		getPlanner(socket, jsonObject["username"].toString());
	}
	else if (action == "getTodo") {
		getTodo(socket, jsonObject["username"].toString());
	}
	else if (action == "saveTodo") {
		QJsonObject todo = jsonObject["todo"].toObject();
		saveTodo(socket, jsonObject["username"].toString(), todo);
	}
	else if (action == "search") {
		searchAndSendDecks(socket, jsonObject["searchQuery"].toString());
	}
	else if (action == "getStats") {
		getStats(socket, jsonObject["username"].toString(), jsonObject["DeckId"].toString());
	}

	socket->close();
}

void MyServer::newConnection()
{
	QTcpSocket *socket = server->nextPendingConnection();
	connect(socket, &QTcpSocket::readyRead, this, &MyServer::readData);
}

void MyServer::savePlanner(QTcpSocket *socket, const QString &username, QJsonObject &jsonObject)
{

	QString filePath = QDir(plannerFolder).absoluteFilePath(username + ".json");
	QFile file(filePath);
	QJsonObject response;

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << QJsonDocument(jsonObject).toJson();
		file.close();
		qDebug() << "Planner saved on path: " << filePath;
		response["status"] = "success";
	}
	else {
		response["status"] = "Error saving planner";
		qDebug() << "Error saving planner:" << file.errorString();
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::getPlanner(QTcpSocket *socket, const QString &username)
{

	QString filePath = QDir(plannerFolder).absoluteFilePath(username + ".json");
	QFile file(filePath);
	QJsonObject response;

	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QByteArray plannerData = file.readAll();
		response["planner"] = QJsonDocument::fromJson(plannerData).object();
		response["status"] = "success";
		file.close();
	}
	else {
		response["status"] = "Error getting planner!";
		qDebug() << "Error opening planner file:" << file.errorString();
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::removeDeck(QTcpSocket *socket, QJsonObject &jsonObject)
{

	QString username = jsonObject["username"].toString();
	QString deckID = QString::number(jsonObject["DeckId"].toDouble());
	QString deckName = jsonObject["DeckName"].toString();
	QDir deckFolder(QDir(QDir(userDecksFolder).absoluteFilePath(username)));
	QJsonObject response;

	QString filePath = deckFolder.absoluteFilePath(deckName + "_" + deckID + "_deck.json");

	if (QFile::remove(filePath)) {
		response["status"] = "success" + deckID;
	}
	else {
		response["status"] = "Failed to remove deck";
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::searchAndSendDecks(QTcpSocket *socket, const QString &searchQuery)
{
	QDir deckFolder(publicDecksFolder);
	QStringList filters;

	QStringList foundDecks;

	QJsonObject response;
	QVector<QString> separatedSearchQuery = searchQuery.split(" ");

	for (const QString &fileName : deckFolder.entryList(filters, QDir::Dirs | QDir::NoDotAndDotDot)) {
		for (auto search : separatedSearchQuery) {
			if (fileName.contains(search, Qt::CaseInsensitive)) {
				foundDecks.append(fileName);
				qDebug() << fileName << '\n';
			}
		}
	}

	if (!foundDecks.isEmpty()) {
		response["status"] = "success";
		response["decks"] = foundDecks.join(", ");
	}
	else {
		response["status"] = "no results";
		response["decks"] = "";
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::sendUserDecks(QTcpSocket *socket, const QString &username)
{
	QDir userFolder(QDir(userDecksFolder).absoluteFilePath(username));
	QStringList userFilters;

	QJsonObject response;

	QStringList userDeckDirectories = userFolder.entryList(userFilters, QDir::Dirs | QDir::NoDotAndDotDot);

	if (!userDeckDirectories.isEmpty()) {
		response["status"] = "success";
		QStringList foundDecks;

		QStringList deckFilters;
		deckFilters << "*_deck.json";

		for (const QString &folderName : userDeckDirectories) {
			QDir deckFolder(userFolder.absoluteFilePath(folderName));
			for (const QString &deckFile : deckFolder.entryList(deckFilters)) {
				foundDecks.append(deckFile);
			}
		}

		if (!foundDecks.isEmpty()) {
			response["decks"] = foundDecks.join(", ");
		}
		else {
			response["status"] = "no results";
		}
	}
	else {
		response["status"] = "no results";
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::sendDeckById(QTcpSocket *socket, const QString &username, const QString &deckId, Privacy &privacy)
{
	QDir folder;
	if (privacy == Privacy::PRIVATE) {
		folder = (QDir(userDecksFolder).absoluteFilePath(username));
	}
	else {
		folder = (QDir(publicDecksFolder));
	}
	QStringList userFilters;
	userFilters << "*_" + deckId;
	QJsonObject response;

	QStringList userDeckDirectories = folder.entryList(userFilters, QDir::Dirs | QDir::NoDotAndDotDot);

	if (!userDeckDirectories.isEmpty()) {

		QStringList deckFilters;
		deckFilters << "*_deck.json";

		for (const QString &folderName : userDeckDirectories) {
			QDir deckFolder(folder.absoluteFilePath(folderName));
			for (const QString &deckName : deckFolder.entryList(deckFilters)) {

				QFile deckFile(deckFolder.absoluteFilePath(deckName));
				if (deckFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
					QByteArray deckData = deckFile.readAll();
					response[deckName] = QJsonDocument::fromJson(deckData).object();
					deckFile.close();
					response["status"] = "success";
				}
				else {
					response["status"] = "Couldn't open deck!";
					qDebug() << response["status"].toString();
				}
			}
		}
	}
	else {
		response["status"] = "no results";
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::saveDeck(QTcpSocket *socket, QJsonObject &jsonObject)
{

	QJsonObject response;
	QString username = jsonObject["username"].toString();

	QJsonObject deck = jsonObject["deck"].toObject();
	QString deckID = QString::number(deck["DeckId"].toDouble());
	QString deckName = deck["Subject"].toString();
	QDir().mkdir(QDir(QDir(userDecksFolder).absoluteFilePath(username)).absoluteFilePath(deckName + "_" + deckID));
	QString filePath =
		QDir(QDir(QDir(userDecksFolder).absoluteFilePath(username)).absoluteFilePath(deckName + "_" + deckID))
			.absoluteFilePath(deckName + "_" + deckID + "_deck.json");

	if (jsonObject.contains("deckStats")) {
		QString statsPath =
			QDir(QDir(QDir(userDecksFolder).absoluteFilePath(username)).absoluteFilePath(deckName + "_" + deckID))
				.absoluteFilePath(deckID + "_stats.json");

		QJsonObject stats = jsonObject["deckStats"].toObject();
		QFile statsFile(statsPath);
		if (statsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream stream(&statsFile);
			stream << QJsonDocument(stats).toJson();
			statsFile.close();
			qDebug() << "Deck stats saved on path: " << filePath;
			response["status"] = "success";
		}
		else {
			qDebug() << "Error saving deck stats:" << statsFile.errorString();
			response["status"] = "Error saving deck stats:";
		}
	}

	QFile file(filePath);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << QJsonDocument(deck).toJson();
		file.close();
		qDebug() << "Deck saved on path: " << filePath;
		response["status"] = "success";
		if (deck["Privacy"] == "Public") {
			if (!makePublic(jsonObject)) {
				response["status"] = "Failed to make deck public";
			}
		}
	}
	else {
		response["status"] = "Error saving deck";
		qDebug() << "Error saving deck:" << file.errorString();
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::registerUser(QTcpSocket *socket, QJsonObject &jsonObject)
{
	QString username = jsonObject["username"].toString();

	QDir users(usersInfoFolder);

	QJsonObject response;

	for (const QString &fileName : users.entryList()) {
		if (fileName.split(".")[0].trimmed() == username.trimmed()) {
			// status message is used on client to check if user exists
			response["status"] = "Username already exists, try again";
			QTextStream stream(socket);
			stream << QJsonDocument(response).toJson();
			return;
		}
	}

	QFile userFile(QDir(usersInfoFolder).absoluteFilePath(username + ".txt"));

	try {
		userFile.open(QIODevice::WriteOnly);
		QByteArray enteredPassword = jsonObject["password"].toString().toUtf8();
		QByteArray enteredHashedPassword = QCryptographicHash::hash(enteredPassword, QCryptographicHash::Sha256);
		userFile.write(QByteArray(enteredHashedPassword.toHex()));
		userFile.close();

		QDir().mkdir(QDir(userDecksFolder).absoluteFilePath(username));

		response["status"] = "success";
	}
	catch (const QFile::FileError &error) {
		qDebug() << "file error: " << username;
		response["status"] = "Registration not successful, try again";
	}

	try {
		QFile plannerFile(QDir(plannerFolder).absoluteFilePath(username + ".json"));
		plannerFile.open(QIODevice::WriteOnly);
		plannerFile.write("{\n}");

		QFile calendarFile(QDir(calendarFolder).absoluteFilePath(username + ".json"));
		calendarFile.open(QIODevice::WriteOnly);
		calendarFile.write("{\n}");

		QFile todoFile(QDir(todoFolder).absoluteFilePath(username + ".json"));
		todoFile.open(QIODevice::WriteOnly);
		todoFile.write("{\n}");

		todoFile.close();
		plannerFile.close();
		calendarFile.close();
	}
	catch (const QFile::FileError &error) {
		qDebug() << "file error: " << username;
		response["status"] = "Registration not successful, try again";
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

uint64_t MyServer::generateUniqueId()
{
	QString id = ids.front();
	ids.pop_front();
	return id.toULongLong();
}

void MyServer::sendId(QTcpSocket *socket)
{
	QJsonObject response;

	response["status"] = "success";
	uint64_t id = generateUniqueId();
	response["DeckId"] = qint64(id);

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::writeRemainingIDsToFile()
{
	QFile file(uniqueIdsFile);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);

		for (const QString &id : ids) {
			out << id << '\n';
		}

		file.close();
	}
	else {
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

bool MyServer::makePublic(QJsonObject &jsonObject)
{
	QString username = jsonObject["username"].toString();

	QJsonObject deck = jsonObject["deck"].toObject();
	QString deckID = QString::number(deck["DeckId"].toDouble());
	QString deckName = deck["Subject"].toString();
	QDir().mkdir(QDir(publicDecksFolder).absoluteFilePath(deckName + "_" + deckID));
	QString filePath = QDir(QDir(publicDecksFolder).absoluteFilePath(deckName + "_" + deckID))
						   .absoluteFilePath(deckName + "_" + deckID + "_deck.json");

	QFile file(filePath);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << QJsonDocument(deck).toJson();
		file.close();
		qDebug() << "Public deck saved on path: " << filePath;
		return true;
	}
	else {
		qDebug() << "Error saving public deck:" << file.errorString();
		return false;
	}
	return false;
}

void MyServer::saveCalendar(QTcpSocket *socket, const QString &username, QJsonObject &jsonObject)
{

	QJsonObject response;
	QString filePath = QDir(calendarFolder).absoluteFilePath(username + ".json");
	QFile file(filePath);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << QJsonDocument(jsonObject).toJson();
		file.close();
		qDebug() << "Calendar saved on path: " << filePath;
		response["status"] = "success";
	}
	else {
		qDebug() << "Error saving calendar:" << file.errorString();
		response["status"] = "Error saving calendar";
	}
	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::getCalendar(QTcpSocket *socket, const QString &username)
{

	QString filePath = QDir(calendarFolder).absoluteFilePath(username + ".json");
	QFile file(filePath);
	QJsonObject response;

	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QByteArray calendarData = file.readAll();
		response["calendar"] = QJsonDocument::fromJson(calendarData).object();
		response["status"] = "success";
		file.close();
	}
	else {
		response["status"] = "Error getting calendar!";
		qDebug() << "Error opening calendar file:" << file.errorString();
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::getTodo(QTcpSocket *socket, const QString &username)
{

	QString filePath = QDir(todoFolder).absoluteFilePath(username + ".json");
	QFile file(filePath);
	QJsonObject response;

	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QByteArray todoData = file.readAll();
		response["todo"] = QJsonDocument::fromJson(todoData).object();
		response["status"] = "success";
		file.close();
	}
	else {
		response["status"] = "Error getting todoList!";
		qDebug() << "Error opening todoList file:" << file.errorString();
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::saveTodo(QTcpSocket *socket, const QString &username, QJsonObject &jsonObject)
{

	QJsonObject response;
	QString filePath = QDir(todoFolder).absoluteFilePath(username + ".json");
	QFile file(filePath);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << QJsonDocument(jsonObject).toJson();
		file.close();
		qDebug() << "Todo list saved on path: " << filePath;
		response["status"] = "success";
	}
	else {
		qDebug() << "Error saving todo list:" << file.errorString();
		response["status"] = "Error saving todo list";
	}

	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}

void MyServer::getStats(QTcpSocket *socket, const QString &username, const QString &deckId)
{
	QDir folder;

	folder = (QDir(userDecksFolder).absoluteFilePath(username));

	QStringList userFilters;
	userFilters << "*_" + deckId;
	QJsonObject response;

	QStringList userDeckDirectories = folder.entryList(userFilters, QDir::Dirs | QDir::NoDotAndDotDot);

	if (!userDeckDirectories.isEmpty()) {

		QStringList deckFilters;
		deckFilters << deckId + "_stats.json";

		for (const QString &folderName : userDeckDirectories) {
			QDir statsFolder(folder.absoluteFilePath(folderName));
			for (const QString &statsFileName : statsFolder.entryList(deckFilters)) {

				QFile statsFile(statsFolder.absoluteFilePath(statsFileName));
				if (statsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
					QByteArray statsData = statsFile.readAll();
					response["status"] = "success";
					response["deckStats"] = QJsonDocument::fromJson(statsData).object();
					statsFile.close();
				}
				else {
					response["status"] = "Couldn't open deck stats file";
				}
			}
		}
		if (!response.contains("status")) {
			response["status"] = "no stats";
		}
	}
	else {
		response["status"] = "Error";
	}

	qDebug() << response;
	QTextStream stream(socket);
	stream << QJsonDocument(response).toJson();
}
