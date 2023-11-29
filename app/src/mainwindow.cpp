#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/studysessionwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createDeckButton_clicked()
{
    CreateDeckDialog popUp(this);
    if (popUp.exec() == QDialog::Accepted) {
        CreateDeckWindow *createDeck = new CreateDeckWindow();
        createDeck->setAttribute(Qt::WA_DeleteOnClose);
        createDeck->show();
        QString name = popUp.getDeckName();
        int privacy = popUp.getDeckPrivacy(); // should be changed to Privacy
//        qDebug() << name << ' ' << privacy;
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
    // TODO clear form?
}


void MainWindow::on_todoButton_clicked()
{
    // TODO create and load TODO list form
}


void MainWindow::on_planerButton_clicked()
{
    // TODO create and load weekly planer form
}


void MainWindow::on_calendarButton_clicked()
{
    // TODO create and load activity calendar form
}


void MainWindow::on_statsButton_clicked()
{
    // TODO create and load stats form
}


void MainWindow::on_settingsButton_clicked()
{
    // TODO create and load settings form
}


void MainWindow::on_helpButton_clicked()
{
    // TODO create and load help form
}

