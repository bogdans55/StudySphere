#include "myServer.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	MyServer server;
	server.startServer();

	return a.exec();
}
