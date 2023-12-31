#include "lib/servercommunicator.h"
#include <QTextStream>

ServerCommunicator::ServerCommunicator(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {}

QJsonObject ServerCommunicator::sendRequest(const QJsonDocument &request)
{
    socket->connectToHost("127.0.0.1", 8080);

	if (socket->waitForConnected()) {
		socket->write(request.toJson());
		socket->waitForBytesWritten();
		socket->waitForReadyRead();

		QByteArray responseText = socket->readAll();
		QTextStream stream(responseText);

		QString response = stream.readAll();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();

		socket->disconnectFromHost();
		return jsonObj;
	}
	else {
		QJsonObject response;
		response["status"] = "Failed to connect to the server";
		return response;
	}
}
