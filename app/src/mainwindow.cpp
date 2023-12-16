#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/scheduleitem.h"
#include "lib/studysessionwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>

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
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(LIBRARY);

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

