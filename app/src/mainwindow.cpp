#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/libraryscene.h"
#include "lib/logindialog.h"
#include "lib/studysessionwindow.h"
#include "ui_mainwindow.h"
#include "lib/user.h"

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
    , m_user()
    , m_libraryScene()
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(LIBRARY);
//    ui->graphicsView_library->setScene(&m_libraryScene);

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

        CreateDeckWindow *createDeck = new CreateDeckWindow(name,privacy,m_user);
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
//    for (auto item : m_libraryScene.items())
//        delete item;
//    m_libraryScene.clear();
//    m_libraryScene.clearDeck();

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

        bool loginSuccess = false;
        if(login.isRegister()){
            if(registerUser(username, password)){
                loginSuccess = loginUser(username, password);
            }else{
                qDebug() << "Register failed.";
            }
        }
        else{
            loginSuccess = loginUser(username, password);
            qDebug(loginSuccess ? "Logged in" : "Not Logged in");
            if(!loginSuccess)
                QMessageBox::critical(this, "Greška pri prijavljivanju", "Neuspešno prijavljivanje. Proverite korisničko ime i lozinku i probajte ponovo.");
        }

        m_loggedIn = loginSuccess;
    }
    else
    {
        m_loggedIn = false; // use setter instead?
        ui->listWidget_library->clear();
        ui->label_username->setText("Nema korisnika");
        ui->pushButton_login->setText("Prijavi se");
    }
}

bool MainWindow::loginUser(const QString& username, const QString& password){
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if(socket.waitForConnected()){
        QJsonObject request;
        request["action"] = "login";
        request["username"] = username;
        request["password"] = password;

        socket.write(QJsonDocument(request).toJson());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        QByteArray responseText = socket.readAll();
        QTextStream stream(responseText);

        qDebug() << "Recieved Data:";

        QString loginResponse = stream.readAll();
        QJsonDocument jsondoc = QJsonDocument::fromJson(loginResponse.toUtf8());
        QJsonObject jsonobj = jsondoc.object();

        qDebug() << jsondoc["status"];
        qDebug() << jsondoc;

        QString deckNames = jsonobj.value("decks").toString();
        if(deckNames != "")
        {
            // split deckNames with ", "
            QStringList deckNamesList = deckNames.split(", ");
            for (auto &deckNameID : deckNamesList)
            {
                auto deckName = deckNameID.split('_')[0];
//                Deck deck(deckName, Privacy::PRIVATE); // empty deck for now
//                DeckItem *deckItem = new DeckItem(&deck);
//                m_libraryScene.addItem(deckItem);
//                m_libraryScene.addDeck(deckItem);
                ui->listWidget_library->addItem(deckName.split('_')[0]);
            }
        }

        if(jsondoc["status"] != QJsonValue::Undefined && jsondoc["status"] != "Password incorrect, try again")
        {
            ui->label_username->setText(request["username"].toString());
            ui->pushButton_login->setText("Odjavi se");
            m_user.setUsername(request["username"].toString());
        }
        else{
            return false;
        }
        socket.disconnectFromHost();
        return true;
    }else{
        return false;
        qDebug() << "Failed to connect to the server";
    }
}

bool MainWindow::registerUser(const QString& username, const QString& password){
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if(socket.waitForConnected()){
        QJsonObject request;
        request["action"] = "register";
        request["username"] = username;
        request["password"] = password;

        socket.write(QJsonDocument(request).toJson());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        QByteArray responseText = socket.readAll();
        QTextStream stream(responseText);

        qDebug() << "Recieved Data:";

        QString registerResponse = stream.readAll();

        QJsonDocument jsondoc = QJsonDocument::fromJson(registerResponse.toUtf8());
        QJsonObject jsonobj = jsondoc.object();

        if(jsondoc["status"] == "Username already exists, try again"){
            qDebug() << "Username already exists, try again";
            return false;
        }
        qDebug() << registerResponse;

        qDebug() << jsondoc["status"];
        qDebug() << jsondoc;

        socket.disconnectFromHost();
        return true;
    }else{
        qDebug() << "Failed to connect to the server";
        return false;
    }
}
