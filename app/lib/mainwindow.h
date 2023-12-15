#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/planner.h"
#include "lib/plannerscene.h"
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

    void on_pushButton_addActivity_clicked();

private:
    Ui::MainWindow *ui;

    PlannerScene m_plannerMondayScene;
    PlannerScene m_plannerTuesdayScene;
    PlannerScene m_plannerWednesdayScene;
    PlannerScene m_plannerThursdayScene;
    PlannerScene m_plannerFridayScene;
    PlannerScene m_plannerSaturdayScene;
    PlannerScene m_plannerSundayScene;

    Planner m_planner;
};
#endif // MAINWINDOW_H
