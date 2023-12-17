#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QDir>
#include <QCoreApplication>
#include <QStandardPaths>

#include "lib/settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_createDeck_clicked();

    void on_pushButton_startStudySession_clicked();

    void on_pushButton_library_clicked();

    void on_pushButton_todo_clicked();

    void on_pushButton_planer_clicked();

    void on_pushButton_calendar_clicked();

    void on_pushButton_stats_clicked();

    void on_pushButton_settings_clicked();

    void on_pushButton_help_clicked();

    void on_calendarWidget_activated(const QDate &date);

    void on_pushButton_addTodo_clicked();

    void on_pushButton_deleteTodo_clicked();

    void on_pushButton_deleteAllTodos_clicked();

    void on_comboBox_theme_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Settings m_settings;

    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/todoFile.txt";

//    QString path = QDir(QCoreApplication::applicationDirPath()).filePath("/info/todoFile.txt");


    void updateTodoFile();
};
#endif // MAINWINDOW_H
