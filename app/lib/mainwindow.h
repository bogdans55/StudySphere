#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/calendar.h"
#include "lib/planner.h"
#include "lib/plannerscene.h"
#include "lib/todolist.h"
#include "libraryscene.h"
#include "user.h"

#include <QListWidgetItem>
#include <QWidget>

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <QTableWidget>

#include "lib/settings.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget
{
	Q_OBJECT

  public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void setEnabled(bool value);

  private slots:
	//	void on_pushButton_createDeck_clicked();

	//	void on_pushButton_startStudySession_clicked();

	void deckButton_clicked();

	void createDeck_clicked();

    void deckPreview_clicked();

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

	void on_pushButton_addEvent_clicked();

	void on_pushButton_addTodo_clicked();

	void on_pushButton_deleteTodo_clicked();

	void on_pushButton_deleteAllTodos_clicked();

	void onTodoItemChanged(QListWidgetItem *item);

	void on_pushButton_search_clicked();

	void on_pushButton_importDecks_clicked();

	void on_pushButton_exportDecks_clicked();

	void on_pushButton_addToLibrary_clicked();

  protected:
	void resizeEvent(QResizeEvent *event) override;

  private:
	Ui::MainWindow *ui;

	QVector<PlannerScene *> m_plannerScenes;
	Planner m_planner;

	Calendar m_calendar;

	ToDoList m_toDoList;

	bool m_calendarLoaded = false;
	void saveCalendar();
	void refreshCalendar();

	bool registerUser(const QString &username, const QString &password);
	bool loginUser(const QString &username, const QString &password);
	QJsonObject sendRequest(QJsonDocument &request);

	bool m_loggedIn = false;
	bool m_plannerLoaded = false;
	bool m_todoLoaded = false;
	User m_user;
	LibraryScene m_libraryScene;

	void savePlanner();
	void showActivities();
	void saveToDoList();
	void saveOnServer();

	void setupTableView(QTableWidget *table);
};
#endif // MAINWINDOW_H
