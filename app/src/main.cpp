#include "../lib/mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if(socket.waitForConnected()){
        QJsonObject request;
        request["action"] = "login";
        request["username"] = "marko1684";

        socket.write(QJsonDocument(request).toJson());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();

        QByteArray responseData = socket.readAll();
        QTextStream stream(responseData);

        qDebug() << "Recieved Data:";
        while (!stream.atEnd()) {
            qDebug() << stream.readLine();
        }
        socket.disconnectFromHost();
    }else{
        qDebug() << "Failed to connect to the server";
    }
    return a.exec();
}
