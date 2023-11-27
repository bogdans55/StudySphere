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
    void on_createDeckButton_clicked();

    void on_startStudySessionButton_clicked();

    void on_libraryButton_clicked();

    void on_todoButton_clicked();

    void on_planerButton_clicked();

    void on_calendarButton_clicked();

    void on_statsButton_clicked();

    void on_settingsButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
