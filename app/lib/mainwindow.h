#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
