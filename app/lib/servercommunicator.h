#ifndef SERVERCOMMUNICATOR_H
#define SERVERCOMMUNICATOR_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>

class ServerCommunicator : public QObject
{
	Q_OBJECT

  public:
	explicit ServerCommunicator(QObject *parent = nullptr);

	QJsonObject sendRequest(const QJsonDocument &request);

  private:
	QTcpSocket *socket;
};

#endif // SERVERCOMMUNICATOR_H
