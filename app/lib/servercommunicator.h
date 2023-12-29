#ifndef SERVERCOMMUNICATOR_H
#define SERVERCOMMUNICATOR_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class ServerCommunicator : public QObject {
	Q_OBJECT

  public:
	explicit ServerCommunicator(QObject *parent = nullptr);

	QJsonObject sendRequest(const QJsonDocument &request);

  private:
	QTcpSocket *socket;
};

#endif // SERVERCOMMUNICATOR_H
