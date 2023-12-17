#include "lib/mainwindow.h"
#include "lib/createdeckdialog.h"
#include "lib/createdeckwindow.h"
#include "lib/studysessionwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFile>

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
    , m_settings()
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(LIBRARY);

    m_settings.setTheme(static_cast<Theme>(0));

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/todoFile.txt");
    //    QString path = QDir(QCoreApplication::applicationDirPath()).filePath("/info/todoFile.txt");
    //    QFile file(path);



    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget_todos);
        ui->listWidget_todos->addItem(item);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/todoFile.txt");
//    QString path = QDir(QCoreApplication::applicationDirPath()).filePath("/info/todoFile.txt");
//    QFile file(path);

    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);

    for(int i = 0; i < ui->listWidget_todos->count(); ++i) {
        out << ui->listWidget_todos->item(i)->text() << '\n';
    }

    file.close();
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


void MainWindow::on_pushButton_addTodo_clicked()
{
    QListWidgetItem* item = new QListWidgetItem(ui->textEdit_todo->toPlainText(), ui->listWidget_todos);
    ui->listWidget_todos->addItem(item);
    ui->textEdit_todo->clear();
    ui->textEdit_todo->setFocus();
}


void MainWindow::on_pushButton_deleteTodo_clicked()
{
    int currentRow = ui->listWidget_todos->currentRow();

    if (currentRow >= 0) {
        QListWidgetItem* item = ui->listWidget_todos->takeItem(currentRow);
        delete item;

        MainWindow::updateTodoFile();
    }
}


void MainWindow::on_pushButton_deleteAllTodos_clicked()
{
    ui->listWidget_todos->clear();

    MainWindow::updateTodoFile();
}

void MainWindow::updateTodoFile()
{
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/todoFile.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(0, "Error", file.errorString());
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < ui->listWidget_todos->count(); ++i) {
        out << ui->listWidget_todos->item(i)->text() << '\n';
    }

    file.close();
}


void MainWindow::on_comboBox_theme_currentIndexChanged(int index)
{
    m_settings.setTheme(static_cast<Theme>(index));
}
