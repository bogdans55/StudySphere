#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/planner.h"
#include "lib/plannerscene.h"
#include "user.h"
#include "libraryscene.h"

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

    void setEnabled(bool value);

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

    void on_pushButton_addActivity_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;

    QVector<PlannerScene*> m_plannerScenes;
    Planner m_planner;

    bool m_loggedIn = false;
    User m_user;
    LibraryScene m_libraryScene;

    void savePlanner();

    bool registerUser(const QString& username, const QString& password);
    bool loginUser(const QString& username, const QString& password);
    void showActivities();
};
#endif // MAINWINDOW_H
