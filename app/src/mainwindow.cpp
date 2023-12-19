#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/scheduleitem.h"
#include "lib/libraryscene.h"
#include "lib/logindialog.h"
#include "lib/studysessionwindow.h"
#include "lib/jsonserializer.h"
#include "ui_mainwindow.h"
#include "lib/user.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>
#include <QCryptographicHash>

#include <QApplication>
#include <QMessageBox>
#include <QDirIterator>

enum Page {
    LIBRARY = 0,
    TODO,
    PLANER,
    CALENDAR,
    STATS,
    SETTINGS,
    HELP
};

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , m_planner()
    , m_user()
    , m_libraryScene()
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(LIBRARY);
//    ui->graphicsView_library->setScene(&m_libraryScene);

    for (int i = 0; i < 7; ++i) {
        m_plannerScenes.push_back(new PlannerScene());
    }
    ui->graphicsView_monday->setScene(m_plannerScenes[Day::MONDAY]);
    ui->graphicsView_tuesday->setScene(m_plannerScenes[Day::TUESDAY]);
    ui->graphicsView_wednesday->setScene(m_plannerScenes[Day::WEDNESDAY]);
    ui->graphicsView_thursday->setScene(m_plannerScenes[Day::THURSDAY]);
    ui->graphicsView_friday->setScene(m_plannerScenes[Day::FRIDAY]);
    ui->graphicsView_saturday->setScene(m_plannerScenes[Day::SATURDAY]);
    ui->graphicsView_sunday->setScene(m_plannerScenes[Day::SUNDAY]);

    QVector<ScheduleItem*> scheduleItems;
    for (int i = 0; i < 7; ++i) {
        scheduleItems.append(new ScheduleItem());
        m_plannerScenes[i]->addItem(scheduleItems[i]);
    }

    ui->dateTimeEdit_eventTime->setDate(QDate::currentDate());
    ui->dateTimeEdit_eventTime->setTime(QTime(12, 0));
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
    QString deckName = ui->listWidget_library->currentItem()->text();
    Deck *deck = new Deck();

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if(socket.waitForConnected()){
        QJsonObject request;
        request["action"] = "sendDeck";
        request["username"] = m_user.username();
        request["DeckId"] = deckName.split('_')[1].split('.')[0];
        qDebug() << request;

        socket.write(QJsonDocument(request).toJson());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();

        QByteArray responseText = socket.readAll();
        QTextStream stream(responseText);

        qDebug() << "Recieved Data:";

        QString deckResponse = stream.readAll();
        QJsonDocument jsondoc = QJsonDocument::fromJson(deckResponse.toUtf8());
        QJsonObject jsonobj = jsondoc.object();

        qDebug() << jsondoc["status"];
        qDebug() << jsondoc;
        QString deckNames = jsonobj.value("decks").toString();
        JSONSerializer jsonSerializer;

        QJsonObject deckObject = jsondoc[deckName].toObject();
        QJsonDocument deckDocument = QJsonDocument::fromVariant(deckObject.toVariantMap());

        jsonSerializer.loadJson(*deck, deckDocument);

        socket.disconnectFromHost();
    }else{
        qDebug() << "Failed to connect to the server";
    }

    StudySession *session = new StudySession(m_user, deck);
    StudySessionWindow *useDeck = new StudySessionWindow(session);
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

void MainWindow::on_pushButton_addEvent_clicked()
{
    QString eventName = ui->lineEdit_event->text();
    QDate date = ui->dateTimeEdit_eventTime->dateTime().date();
    QTime time = ui->dateTimeEdit_eventTime->dateTime().time();

    m_calendar.addEvent(date, time, eventName);

    ui->lineEdit_event->clear();
    ui->dateTimeEdit_eventTime->setDate(QDate::currentDate());
    ui->dateTimeEdit_eventTime->setTime(QTime(12, 0));
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    QString message = "Na izabrani dan imate sledeće dogadjaje:\n";
    if(!m_calendar.events().contains(date))
        QMessageBox::information(this, date.toString("dd.MM.yyyy."), "Na izabrani dan nemate nijedan dogadjaj!");
    else
    {
        for(auto event : m_calendar.events()[date])
        {
            message += "\t" + event.first.toString("hh:mm") + " - " + event.second + "\n";
        }
        QMessageBox::information(this, date.toString("dd.MM.yyyy."), message);
    }
}

void MainWindow::on_pushButton_addActivity_clicked()
{
    QString name = ui->lineEdit_activityName->text();

    QTime startTime = ui->timeEdit_start->time();
    QTime endTime = ui->timeEdit_end->time();

    if (startTime >= endTime) {
        QMessageBox::warning(this, "Pogrešan unos", "Vreme početka aktivnosti mora biti pre vremena kraja!");
        return;
    }

    QString dayString = ui->comboBox_day->currentText();
    Day day = Planner::dayFromString(dayString);

    Activity activity(name, startTime, endTime);

    m_planner.addActivity(day, activity);

    ActivityItem *activityItem = new ActivityItem(activity);
    m_plannerScenes[day]->addActivity(activityItem);
    m_plannerScenes[day]->addItem(activityItem);

    QGraphicsTextItem *activityTime = new QGraphicsTextItem();
    activityTime->setPlainText(startTime.toString("hh:mm"));
    activityTime->setPos(activityItem->pos());
    m_plannerScenes[day]->addItem(activityTime);

    QGraphicsTextItem *activityText = new QGraphicsTextItem();
    activityText->setPlainText(name);
    qreal textWidth = 80;   // hardcoded
    activityText->setTextWidth(textWidth);
    activityText->setPos(activityItem->pos().x(), activityItem->pos().y() + activityTime->boundingRect().height());
    m_plannerScenes[day]->addItem(activityText);
}

void MainWindow::setEnabled(bool value)
{
    // TODO add every ui (input) element
    ui->pushButton_library->setEnabled(value);
    ui->pushButton_todo->setEnabled(value);
    ui->pushButton_planer->setEnabled(value);
    ui->pushButton_calendar->setEnabled(value);
    ui->pushButton_stats->setEnabled(value);
    ui->pushButton_settings->setEnabled(value);
    ui->pushButton_help->setEnabled(value);
    ui->pushButton_createDeck->setEnabled(value);
    ui->pushButton_startStudySession->setEnabled(value);
    ui->pushButton_addTodo->setEnabled(value);
    ui->pushButton_deleteTodo->setEnabled(value);
    ui->pushButton_deleteAllTodos->setEnabled(value);
    ui->pushButton_addActivity->setEnabled(value);
    ui->pushButton_addEvent->setEnabled(value);
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
                setEnabled(true);
            }else{
                qDebug() << "Register failed.";
            }
        }
        else{
            loginSuccess = loginUser(username, password);
            qDebug(loginSuccess ? "Logged in" : "Not Logged in");
            if(!loginSuccess)
                QMessageBox::critical(this, "Greška pri prijavljivanju", "Neuspešno prijavljivanje. Proverite korisničko ime i lozinku i probajte ponovo.");
            else
                setEnabled(true);
        }

        m_loggedIn = loginSuccess;
    }
    else
    {
        m_loggedIn = false; // use setter instead?
        ui->listWidget_library->clear();
        ui->label_username->setText("Nema korisnika");
        ui->pushButton_login->setText("Prijavi se");
        setEnabled(false);
        // load library page?
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
                // auto deckName = deckNameID.split('_')[0];
//                Deck deck(deckName, Privacy::PRIVATE); // empty deck for now
//                DeckItem *deckItem = new DeckItem(&deck);
//                m_libraryScene.addItem(deckItem);
//                m_libraryScene.addDeck(deckItem);
                // ui->listWidget_library->addItem(deckName.split('_')[0]);
                ui->listWidget_library->addItem(deckNameID);
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


