#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/studysessionwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_createDeckButton_clicked()
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


void MainWindow::on_startStudySessionButton_clicked()
{
    StudySessionWindow *useDeck = new StudySessionWindow();
    useDeck->setAttribute(Qt::WA_DeleteOnClose);
    useDeck->show();
}


void MainWindow::on_libraryButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(LIBRARY);
}


void MainWindow::on_todoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(TODO);
}


void MainWindow::on_planerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(PLANER);
}


void MainWindow::on_calendarButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(CALENDAR);
}


void MainWindow::on_statsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(STATS);

}


void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(SETTINGS);
}


void MainWindow::on_helpButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(HELP);
}

