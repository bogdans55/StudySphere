#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/deckpreviewwindow.h"
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
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

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
	: QWidget(parent), ui(new Ui::MainWindow), m_planner(), m_toDoList(), m_user(), m_libraryScene()
{
	ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(LIBRARY);
	setEnabled(false);

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

	connect(ui->listWidget_todos, &QListWidget::itemChanged, this, &MainWindow::onTodoItemChanged);
}

MainWindow::~MainWindow()
{
	if (m_loggedIn) {
		saveOnServer();
	}
	delete ui;
}

void MainWindow::saveOnServer()
{
	if (m_calendarLoaded) {
		saveCalendar();
	}
	if (m_plannerLoaded) {
		savePlanner();
	}
	if (m_todoLoaded) {
		saveToDoList();
	}
}

void MainWindow::savePlanner()
{

	QJsonObject requestObject;

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_planner);

	requestObject["action"] = "savePlanner";
	requestObject["username"] = m_user.username();
	requestObject["planner"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);
}

void MainWindow::createDeck_clicked()
{
	CreateDeckDialog popUp(this);
	if (popUp.exec() == QDialog::Accepted) {
		QString name = popUp.getDeckName();
		Privacy privacy = popUp.getDeckPrivacy();

		CreateDeckWindow *createDeck = new CreateDeckWindow(name, privacy, m_user);
        connect(createDeck, &CreateDeckWindow::writeGeneratedID, this, &MainWindow::readGeneratedID);
		createDeck->setAttribute(Qt::WA_DeleteOnClose);
        createDeck->show();
    }
}

void MainWindow::deckPreview_clicked()
{
    // TODO load deck

    // DeckPreviewWindow *preview = new DeckPreviewWindow(deck);
    DeckPreviewWindow *preview = new DeckPreviewWindow();
    preview->setAttribute(Qt::WA_DeleteOnClose);
    preview->show();
}

void MainWindow::deckButton_clicked()
{
	QPushButton *chosenDeck = qobject_cast<QPushButton *>(sender());

    QString deckName = chosenDeck->text();
	Deck *deck = new Deck();

    qDebug() << deckName;

	QJsonObject requestObject;
	requestObject["action"] = "sendDeck";
	requestObject["username"] = m_user.username();
	requestObject["DeckId"] = deckName.split('_')[1].split('.')[0];
	requestObject["Privacy"] = "PRIVATE";

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

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
	if (!m_todoLoaded) {

		QJsonObject requestObject;
		requestObject["action"] = "getTodo";
		requestObject["username"] = m_user.username();

		QJsonDocument request(requestObject);
		QJsonObject jsonObj = sendRequest(request);

		JSONSerializer jsonSerializer;

		QJsonObject deckObject = jsonObj["todo"].toObject();
		QJsonDocument deckDocument = QJsonDocument::fromVariant(deckObject.toVariantMap());

		jsonSerializer.loadJson(m_toDoList, deckDocument);

		showActivities();
		m_todoLoaded = true;

        for (auto &todo : m_toDoList.toDos()) {
			QListWidgetItem *item = new QListWidgetItem();
			item->setCheckState(todo.second ? Qt::Checked : Qt::Unchecked);
			item->setText(todo.first);
            onTodoItemChanged(item);
			ui->listWidget_todos->addItem(item);
		}
	}
}

void MainWindow::on_pushButton_planer_clicked()
{
	ui->stackedWidget->setCurrentIndex(PLANER);
	if (!m_plannerLoaded) {

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
	if (!m_calendarLoaded) {

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

	if (eventName.trimmed().isEmpty()) {
		QMessageBox::warning(this, "Pogrešan unos", "Niste popunili polje za naziv dogadjaja!");
		return;
	}

	m_calendar.addEvent(date, time, eventName);

	ui->lineEdit_event->clear();
	ui->dateTimeEdit_eventTime->setDate(QDate::currentDate());
	ui->dateTimeEdit_eventTime->setTime(QTime(12, 0));

	QMessageBox::information(this, "Uspešan unos", "Uspešno ste dodali novi dogadjaj!");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	setupTableView(ui->tableWidget_library);
	setupTableView(ui->tableWidget_browser);

	for (auto scene : m_plannerScenes) {
		for (auto item : scene->items()) {
			if (dynamic_cast<QGraphicsTextItem *>(item)) {
				QGraphicsTextItem *textItem = static_cast<QGraphicsTextItem *>(item);
				textItem->setTextWidth(ui->graphicsView_monday->width() - 10);
			}
		}
	}
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{
	QString message = "Na izabrani dan imate sledeće dogadjaje:\n";
	if (!m_calendar.events().contains(date))
		QMessageBox::information(this, date.toString("dd.MM.yyyy."), "Na izabrani dan nemate nijedan dogadjaj!");
	else {
		for (auto event : m_calendar.events()[date]) {
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

	if (name.trimmed().isEmpty()) {
		QMessageBox::warning(this, "Pogrešan unos", "Niste popunili polje za naziv aktivnosti!");
		return;
	}

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

void MainWindow::showActivities()
{
	for (auto day : m_planner.activities().keys()) {
		for (auto currentActivity : m_planner.activities().value(day)) {
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
			activityText->setPos(activityItem->pos().x(),
								 activityItem->pos().y() + activityTime->boundingRect().height());
			m_plannerScenes[day]->addItem(activityText);
		}
	}
}

void MainWindow::setupTableView(QTableWidget *table)
{
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowHeight(0, table->height() * 0.43);
	table->setRowHeight(1, table->height() * 0.05);
    table->setRowHeight(2, table->height() * 0.43);
    table->setRowHeight(3, table->height() * 0.05);
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
	ui->pushButton_importDecks->setEnabled(value);
	ui->pushButton_exportDecks->setEnabled(value);
	ui->pushButton_addTodo->setEnabled(value);
	ui->pushButton_deleteTodo->setEnabled(value);
	ui->pushButton_deleteAllTodos->setEnabled(value);
	ui->pushButton_addActivity->setEnabled(value);
	ui->pushButton_addEvent->setEnabled(value);
	ui->tab_browser->setEnabled(value);
	ui->tabWidget_library->setTabEnabled(1, value);
}

void MainWindow::on_pushButton_login_clicked()
{
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
			if (!loginSuccess) {
				QMessageBox::critical(
					this, "Greška pri prijavljivanju",
					"Neuspešno prijavljivanje. Proverite korisničko ime i lozinku i probajte ponovo.");
				return;
			}
			else
				setEnabled(true);
		}

		m_loggedIn = loginSuccess;
	}
	else {
		// logout
		saveOnServer();
		m_loggedIn = false; // use setter instead?
		ui->label_username->setText("Nema korisnika");
		ui->pushButton_login->setText("Prijavi se");
		setEnabled(false);
		ui->tableWidget_library->clear();
		ui->tableWidget_browser->clear();
		m_planner.deleteAll();
		m_calendar.deleteAll();
		m_toDoList.deleteAllToDos();
		ui->listWidget_todos->clear();
		m_todoLoaded = false;
		m_plannerLoaded = false;
		m_calendarLoaded = false;
		ui->stackedWidget->setCurrentIndex(LIBRARY);

		ui->tableWidget_library->setColumnCount(0);
		ui->tableWidget_browser->setColumnCount(0);
		setupTableView(ui->tableWidget_library);
		setupTableView(ui->tableWidget_browser);
	}
}

QJsonObject MainWindow::sendRequest(QJsonDocument &request)
{
	QTcpSocket *socket = new QTcpSocket(this);
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
		socket->deleteLater();
		return jsonObj;
	}
	else {
		socket->deleteLater();
		QJsonObject response;
		response["status"] = "Failed to connect to the server";
		qDebug() << response["status"];
		return response;
	}
}

bool MainWindow::loginUser(const QString &username, const QString &password)
{
    setupTableView(ui->tableWidget_library);
    setupTableView(ui->tableWidget_browser);
	QJsonObject requestObject;

	requestObject["action"] = "login";
	requestObject["username"] = username;
	requestObject["password"] = password;

	qDebug() << "Recieved Data:";
	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

	qDebug() << jsonObj["status"];
	qDebug() << jsonObj;

	if (jsonObj["status"] != QJsonValue::Undefined && jsonObj["status"] != "Password incorrect, try again") {
		ui->label_username->setText(request["username"].toString());
		ui->pushButton_login->setText("Odjavi se");
		m_user.setUsername(request["username"].toString());
	}
	else {
		return false;
	}

	QString deckNames = jsonObj.value("decks").toString();
    m_deckCounter = 0;
	if (deckNames != "") {
		QStringList deckNamesList = deckNames.split(", ");
		for (auto &deckNameID : deckNamesList) {
            addDeckToTable(deckNameID, ui->tableWidget_library);
            auto deckNameSplit = deckNameID.split("_");
            ui->comboBox_deck->addItem(deckNameSplit[0] + "_" + deckNameSplit[1]);
		}
    }
    addCreateDeckButton();

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

void MainWindow::saveCalendar()
{

	QJsonObject requestObject;

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_calendar);

	requestObject["action"] = "saveCalendar";
	requestObject["username"] = m_user.username();
	requestObject["calendar"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);
}

void MainWindow::on_pushButton_addTodo_clicked()
{
	if (ui->lineEdit_todo->text().trimmed().isEmpty()) {
		QMessageBox::warning(this, "Pogrešan unos", "Niste popunili polje za naziv aktivnosti!");
		return;
	}

	QListWidgetItem *item = new QListWidgetItem();
	item->setCheckState(Qt::Unchecked);
	item->setText(ui->lineEdit_todo->text());

	m_toDoList.addToDo(item->text(), item->checkState());

	ui->listWidget_todos->addItem(item);
	ui->lineEdit_todo->clear();
	ui->lineEdit_todo->setFocus();
}

void MainWindow::on_pushButton_deleteTodo_clicked()
{
	int currentRow = ui->listWidget_todos->currentRow();

	if (currentRow >= 0) {
		QListWidgetItem *item = ui->listWidget_todos->takeItem(currentRow);

		m_toDoList.deleteToDo(item->text());
		delete item;
	}
}

void MainWindow::on_pushButton_deleteAllTodos_clicked()
{
	m_toDoList.deleteAllToDos();
	ui->listWidget_todos->clear();
}

void MainWindow::onTodoItemChanged(QListWidgetItem *item)
{
	if (item) {
		m_toDoList.checkToDo(item->text(), item->checkState());

		if (item->checkState() == Qt::Checked) {
			item->setBackground(QBrush(QColor(140, 255, 140)));
		}
		else {
			item->setBackground(QBrush(Qt::white));
		}
	}
}

void MainWindow::saveToDoList()
{
	QJsonObject requestObject;

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_toDoList);

	qDebug() << doc;

	requestObject["action"] = "saveTodo";
	requestObject["username"] = m_user.username();
	requestObject["todo"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

	qDebug() << jsonObj;
}

void MainWindow::on_pushButton_search_clicked()
{
	ui->tableWidget_browser->clear();
    setupTableView(ui->tableWidget_browser);

    QString query = ui->lineEdit_browser->text().trimmed();

    if (query.isEmpty()) {
        QMessageBox::warning(this, "Pogrešan unos", "Niste popunili polje za naziv špila!");
        return;
    }

	QJsonObject requestObject;
	requestObject["action"] = "search";
    requestObject["searchQuery"] = query;
	qDebug() << "Recieved Data:";

	QJsonDocument request(requestObject);
	QJsonObject jsonObj = sendRequest(request);

	if (jsonObj["status"] == "No result") {
		return;
	}

	qDebug() << jsonObj["status"];

	QString deckNames = jsonObj.value("decks").toString();
	if (deckNames != "") {
		QStringList deckNamesList = deckNames.split(", ");
        m_deckCounter = 0;
        for (auto &deckNameID : deckNamesList) {
            addDeckToTable(deckNameID, ui->tableWidget_browser);
        }
    }
    else {
        QMessageBox::warning(this, "Nema rezultata", "Nije pronadjen nijedan špil!");
    }
}

void MainWindow::on_pushButton_importDecks_clicked()
{
	QStringList filePaths =
		QFileDialog::getOpenFileNames(nullptr, "Choose JSON Files", "", "JSON Files (*.json);;All Files (*)");

    qDebug() << filePaths;

    // TODO iterate thru list and save each deck on server
}

void MainWindow::on_pushButton_exportDecks_clicked()
{
    QString selectedDirectory = QFileDialog::getExistingDirectory(
        nullptr,
        "Select Directory",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    qDebug() << selectedDirectory;

    auto rows = ui->tableWidget_library->rowCount();
    auto cols = ui->tableWidget_library->columnCount();

    for (auto i = 0; i < rows; i += 2) {
        for(auto j = 0; j < cols; j++) {
            auto cell = ui->tableWidget_library->cellWidget(i, j);
            if (QPushButton *button = dynamic_cast<QPushButton*>(cell)) {
                if(!button->children().isEmpty()) {
                    QCheckBox *checkbox = dynamic_cast<QCheckBox*>(ui->tableWidget_library->cellWidget(i, j)->children().front());
                    if (checkbox->isChecked()) {
                        // TODO save deck
                        qDebug() << button->text();
                    }
                }
            }
        }
    }

}

void MainWindow::readGeneratedID(QString deckNameID)
{
    addDeckToTable(deckNameID, ui->tableWidget_library);
    addCreateDeckButton();
    ui->comboBox_deck->addItem(deckNameID.split("_")[0]);
}

void MainWindow::addDeckToTable(QString deckNameID, QTableWidget *table)
{
    qDebug() << deckNameID;
    QPushButton *button = new QPushButton((deckNameID));
    button->setStyleSheet("color: transparent; margin-left: 25%;");
    qDebug() << button->text();

    if (table == ui->tableWidget_library) {
        connect(button, &QPushButton::clicked, this, &MainWindow::deckButton_clicked);
        QCheckBox *checkbox = new QCheckBox(button);
        checkbox->setStyleSheet("padding: 5%");
    }
    else
        connect(button, &QPushButton::clicked, this, &MainWindow::deckPreview_clicked);


    QLabel *label = new QLabel(deckNameID.split("_")[0], table);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("text-align: center; margin-left: 25%");

    if (m_deckCounter % 2 == 0) {
        table->setColumnCount(table->columnCount() + 1);
        table->setColumnWidth(m_deckCounter / 2, 220); // hardcoded
    }

    table->setCellWidget(m_deckCounter % 2 * 2, m_deckCounter / 2, button);
    table->setCellWidget(m_deckCounter % 2 * 2 + 1, m_deckCounter / 2, label);
    m_deckCounter++;
}

void MainWindow::addCreateDeckButton()
{
    QPushButton *button = new QPushButton("+ (kreiraj novi spil)", ui->tableWidget_library);
    connect(button, &QPushButton::clicked, this, &MainWindow::createDeck_clicked);
    button->setStyleSheet("margin-left: 25%;");
    if (m_deckCounter % 2 == 0) {
        ui->tableWidget_library->setColumnCount(ui->tableWidget_library->columnCount() + 1);
        ui->tableWidget_library->setColumnWidth(m_deckCounter / 2, 220); // hardcoded
    }
    ui->tableWidget_library->setCellWidget(m_deckCounter % 2 * 2, m_deckCounter / 2, button);
}

void MainWindow::on_comboBox_deck_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    qDebug() << ui->comboBox_deck->currentText();

    // TODO read stats from current deck and add them to ui elements
}

