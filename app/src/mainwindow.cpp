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

    ui->graphicsView_monday->setScene(&m_plannerMondayScene);
    ui->graphicsView_tuesday->setScene(&m_plannerTuesdayScene);
    ui->graphicsView_wednesday->setScene(&m_plannerWednesdayScene);
    ui->graphicsView_thursday->setScene(&m_plannerThursdayScene);
    ui->graphicsView_friday->setScene(&m_plannerFridayScene);
    ui->graphicsView_saturday->setScene(&m_plannerSaturdayScene);
    ui->graphicsView_sunday->setScene(&m_plannerSundayScene);

    QVector<ScheduleItem*> scheduleItems;
    for (int i = 0; i < 7; ++i) {
        scheduleItems.append(new ScheduleItem());
    }
    m_plannerMondayScene.addItem(scheduleItems[0]);
    m_plannerTuesdayScene.addItem(scheduleItems[1]);
    m_plannerWednesdayScene.addItem(scheduleItems[2]);
    m_plannerThursdayScene.addItem(scheduleItems[3]);
    m_plannerFridayScene.addItem(scheduleItems[4]);
    m_plannerSaturdayScene.addItem(scheduleItems[5]);
    m_plannerSundayScene.addItem(scheduleItems[6]);
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
}

