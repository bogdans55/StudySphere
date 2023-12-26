#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/jsonserializer.h"
#include "lib/libraryscene.h"
#include "lib/logindialog.h"
#include "lib/scheduleitem.h"
#include "lib/studysessionwindow.h"
#include "lib/user.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>

#include <QApplication>
#include <QDirIterator>
#include <QMessageBox>

enum Page
{
	LIBRARY = 0,
	TODO,
	PLANER,
	CALENDAR,
	STATS,
	SETTINGS,
	HELP
};

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui::MainWindow), m_planner(), m_user(), m_libraryScene()
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


    ui->dateTimeEdit_eventTime->setDate(QDate::currentDate());
    ui->dateTimeEdit_eventTime->setTime(QTime(12, 0));

	QVector<ScheduleItem *> scheduleItems;
	for (int i = 0; i < 7; ++i) {
		scheduleItems.append(new ScheduleItem());
		scheduleItems[i]->setWidth(ui->graphicsView_monday->width());
		m_plannerScenes[i]->addItem(scheduleItems[i]);
	}
}

MainWindow::~MainWindow()
{
	saveCalendar();
    savePlanner();
	delete ui;
}

void MainWindow::savePlanner(){

	QJsonObject requestObject;

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_planner);

	requestObject["action"] = "savePlanner";
	requestObject["username"] = m_user.username();
	requestObject["planner"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);
}

void MainWindow::on_pushButton_createDeck_clicked()
{
	CreateDeckDialog popUp(this);
	if (popUp.exec() == QDialog::Accepted) {
		QString name = popUp.getDeckName();
		Privacy privacy = popUp.getDeckPrivacy();

		CreateDeckWindow *createDeck = new CreateDeckWindow(name, privacy, m_user);
		createDeck->setAttribute(Qt::WA_DeleteOnClose);
		createDeck->show();
	}
}

void MainWindow::on_pushButton_startStudySession_clicked()
{
	QString deckName = ui->listWidget_library->currentItem()->text();
	Deck *deck = new Deck();

	QJsonObject requestObject;
	requestObject["action"] = "sendDeck";
	requestObject["username"] = m_user.username();
	requestObject["DeckId"] = deckName.split('_')[1].split('.')[0];

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

	qDebug() << jsonObj;

	QString deckNames = jsonObj.value("decks").toString();
	JSONSerializer jsonSerializer;

	QJsonObject deckObject = jsonObj[deckName].toObject();
	QJsonDocument deckDocument = QJsonDocument::fromVariant(deckObject.toVariantMap());

	jsonSerializer.loadJson(*deck, deckDocument);

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
    if(!m_plannerLoaded){

		QJsonObject requestObject;
		requestObject["action"] = "getPlanner";
		requestObject["username"] = m_user.username();

		QJsonDocument request(requestObject);
		QJsonObject jsonObj = sendRequest(request);

		JSONSerializer jsonSerializer;

		QJsonObject deckObject = jsonObj["planner"].toObject();
		QJsonDocument deckDocument = QJsonDocument::fromVariant(deckObject.toVariantMap());

		jsonSerializer.loadJson(m_planner, deckDocument);


        showActivities();
        m_plannerLoaded = true;
    }
}

void MainWindow::on_pushButton_calendar_clicked()
{
    ui->stackedWidget->setCurrentIndex(CALENDAR);
	if(!m_calendarLoaded){

		QJsonObject requestObject;
		requestObject["action"] = "getCalendar";
		requestObject["username"] = m_user.username();

		QJsonDocument request(requestObject);
		QJsonObject jsonObj = sendRequest(request);

		qDebug() << jsonObj;

		JSONSerializer jsonSerializer;

		QJsonObject deckObject = jsonObj["calendar"].toObject();
		QJsonDocument deckDocument = QJsonDocument::fromVariant(deckObject.toVariantMap());

		jsonSerializer.loadJson(m_calendar, deckDocument);

		m_calendarLoaded = true;
	}
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
    qreal textWidth = ui->graphicsView_monday->width() - 10; // hardcoded reduction for scroll bar
    activityText->setTextWidth(textWidth);
    activityText->setPos(activityItem->pos().x(), activityItem->pos().y() + activityTime->boundingRect().height());
    m_plannerScenes[day]->addItem(activityText);
}

void MainWindow::showActivities(){
    for(auto day : m_planner.activities().keys())
    {
        for(auto currentActivity : m_planner.activities().value(day)){
            QString name = currentActivity.activityText();

            QTime startTime = currentActivity.start();

            ActivityItem *activityItem = new ActivityItem(currentActivity);
            m_plannerScenes[day]->addActivity(activityItem);
            m_plannerScenes[day]->addItem(activityItem);

            QGraphicsTextItem *activityTime = new QGraphicsTextItem();
            activityTime->setPlainText(startTime.toString("hh:mm"));
            activityTime->setPos(activityItem->pos());
            m_plannerScenes[day]->addItem(activityTime);

            QGraphicsTextItem *activityText = new QGraphicsTextItem();
            activityText->setPlainText(name);
            qreal textWidth = ui->graphicsView_monday->width() - 10; // hardcoded reduction for scroll bar
            activityText->setTextWidth(textWidth);
            activityText->setPos(activityItem->pos().x(), activityItem->pos().y() + activityTime->boundingRect().height());
            m_plannerScenes[day]->addItem(activityText);
        }
    }
}


void MainWindow::setEnabled(bool value)
{
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
	//    m_libraryScene.clear(); // clear calls delete on all items on scene
	//    m_libraryScene.clearDeck();
	for (auto scene : m_plannerScenes) {
		scene->clear(); // clear calls delete on all items on scene
		scene->addItem(new ScheduleItem());
		scene->clearActivities();
	}

	if (!m_loggedIn) // use getter instead?
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
		if (login.isRegister()) {
			if (registerUser(username, password)) {
				loginSuccess = loginUser(username, password);
				setEnabled(true);
			}
			else {
				qDebug() << "Register failed.";
			}
		}
		else {
			loginSuccess = loginUser(username, password);
			qDebug(loginSuccess ? "Logged in" : "Not Logged in");
			if (!loginSuccess)
				QMessageBox::critical(
					this, "Greška pri prijavljivanju",
					"Neuspešno prijavljivanje. Proverite korisničko ime i lozinku i probajte ponovo.");
			else
				setEnabled(true);
		}

		m_loggedIn = loginSuccess;
	}
	else {
		m_loggedIn = false; // use setter instead?
		ui->listWidget_library->clear();
		ui->label_username->setText("Nema korisnika");
		ui->pushButton_login->setText("Prijavi se");
		setEnabled(false);
		ui->stackedWidget->setCurrentIndex(LIBRARY);
	}
}

QJsonObject MainWindow::sendRequest(QJsonDocument &request){
	QTcpSocket *socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1", 8080);

	if(socket ->waitForConnected()){

		socket->write(request.toJson());

		socket->waitForBytesWritten();
		socket->waitForReadyRead();
		QByteArray responseText = socket->readAll();
		QTextStream stream(responseText);

		QString response = stream.readAll();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		socket->disconnectFromHost();
		socket->deleteLater();
		return jsonObj;
	}else {
		socket->deleteLater();
		QJsonObject response;
		response["status"] = "Failed to connect to the server";
		qDebug() << response["status"];
		return response;
	}
}

bool MainWindow::loginUser(const QString &username, const QString &password)
{
	QJsonObject requestObject;

	requestObject["action"] = "login";
	requestObject["username"] = username;
	requestObject["password"] = password;

	qDebug() << "Recieved Data:";
	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

	qDebug() << jsonObj["status"];
	qDebug() << jsonObj;

	QString deckNames = jsonObj.value("decks").toString();
	if (deckNames != "") {
		QStringList deckNamesList = deckNames.split(", ");
		for (auto &deckNameID : deckNamesList) {
			ui->listWidget_library->addItem(deckNameID);
		}
	}

	if (jsonObj["status"] != QJsonValue::Undefined && jsonObj["status"] != "Password incorrect, try again") {
		ui->label_username->setText(request["username"].toString());
		ui->pushButton_login->setText("Odjavi se");
		m_user.setUsername(request["username"].toString());
	}
	else {
		return false;
	}
	return true;
}

bool MainWindow::registerUser(const QString &username, const QString &password)
{
	QJsonObject requestObject;
	requestObject["action"] = "register";
	requestObject["username"] = username;
	requestObject["password"] = password;

	qDebug() << "Recieved Data:";

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

	if (jsonObj["status"] == "Username already exists, try again") {
		qDebug() << "Username already exists, try again";
		return false;
	}

	qDebug() << jsonObj["status"];
	return true;
}

void MainWindow::saveCalendar(){

	QJsonObject requestObject;

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_calendar);

	requestObject["action"] = "saveCalendar";
	requestObject["username"] = m_user.username();
	requestObject["calendar"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);
}

