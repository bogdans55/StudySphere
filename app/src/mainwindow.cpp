#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/logindialog.h"
#include "lib/studysessionwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>
#include <QCryptographicHash>

#define LIBRARY  0
#define TODO     1
#define PLANER   2
#define CALENDAR 3
#define STATS    4
#define SETTINGS 5
#define HELP     6

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(LIBRARY);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_createDeck_clicked()
{
    CreateDeckDialog popUp(this);
    if (popUp.exec() == QDialog::Accepted) {
        QString name = popUp.getDeckName();
        Privacy privacy = popUp.getDeckPrivacy();

        CreateDeckWindow *createDeck = new CreateDeckWindow(name, privacy);
        createDeck->setAttribute(Qt::WA_DeleteOnClose);
        createDeck->show();

    }
}


void MainWindow::on_pushButton_startStudySession_clicked()
{
    StudySessionWindow *useDeck = new StudySessionWindow();
    useDeck->setAttribute(Qt::WA_DeleteOnClose);
    useDeck->show();
}


void MainWindow::on_pushButton_library_clicked()
{
    ui->stackedWidget->setCurrentIndex(LIBRARY);
}


void MainWindow::on_pushButton_todo_clicked()
{
    ui->stackedWidget->setCurrentIndex(TODO);
}


void MainWindow::on_pushButton_planer_clicked()
{
    ui->stackedWidget->setCurrentIndex(PLANER);
}


void MainWindow::on_pushButton_calendar_clicked()
{
    ui->stackedWidget->setCurrentIndex(CALENDAR);
}


void MainWindow::on_pushButton_stats_clicked()
{
    ui->stackedWidget->setCurrentIndex(STATS);

}


void MainWindow::on_pushButton_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(SETTINGS);
}


void MainWindow::on_pushButton_help_clicked()
{
    ui->stackedWidget->setCurrentIndex(HELP);
}


void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    // work in progress!

//    qDebug() << date;
    if(date.dayOfWeek() == 7)
        QMessageBox::information(this, date.toString(), "nema nista");
    else
        QMessageBox::information(this, date.toString(), "aktivnosti za taj dan npr");
}

void MainWindow::on_pushButton_login_clicked()
{
    if(!m_loggedIn) // use getter instead?
    {
        QString username;
        QString password;
        LoginDialog login(this);
        if (login.exec() != QDialog::Accepted) {
            return;
        }
        username = login.getUsername();
        password = login.getPassword();

        QTcpSocket socket;
        socket.connectToHost("127.0.0.1", 8080);

        if(socket.waitForConnected()){
            QJsonObject request;
            if(login.isRegisterSelected()){
                request["action"] = "register";

            }
            else{
                request["action"] = "login";
            }
            request["username"] = username;
            request["password"] = password;

            socket.write(QJsonDocument(request).toJson());
            socket.waitForBytesWritten();
            socket.waitForReadyRead();
            QByteArray responseData = socket.readAll();
            QTextStream stream(responseData);

            qDebug() << "Recieved Data:";

            if(request["action"] == "register" ){
                QString registerResponse = stream.readAll();
                if(registerResponse == "Username already exists, try again"){
                    qDebug() << "Username already exists, try again";
                    return;
                }
                qDebug() << registerResponse;
            }

            m_loggedIn = true; // use setter instead?

            ui->label_username->setText(request["username"].toString());
            ui->pushButton_login->setText("Odjavi se");

            while (!stream.atEnd()) {
                qDebug() << stream.readLine();
            }

            socket.disconnectFromHost();
        }else{
            qDebug() << "Failed to connect to the server";
        }
    }
    else
    {
        m_loggedIn = false; // use setter instead?

        ui->label_username->setText("Nema korisnika");
        ui->pushButton_login->setText("Prijavi se");
    }
}

