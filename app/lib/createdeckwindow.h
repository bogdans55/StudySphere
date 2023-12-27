#ifndef CREATEDECKWINDOW_H
#define CREATEDECKWINDOW_H

#include "deck.h"
#include "user.h"
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QWidget>

namespace Ui
{
class CreateDeckWindow;
}

class CreateDeckWindow : public QWidget
{
	Q_OBJECT

  public:
	explicit CreateDeckWindow(User &user, QWidget *parent = nullptr);

	CreateDeckWindow(QString name, Privacy privacy, User &user, QWidget *parent = nullptr);

	~CreateDeckWindow();

	QString getQuestionText() const;
	QString getAnswerText() const;
	Difficulty getDifficulty() const;

  private slots:
	void on_pushButton_finish_clicked();

	void on_pushButton_add_clicked();

  private:
	Ui::CreateDeckWindow *ui;
	Deck m_deck;
	QButtonGroup *m_questionDifficulty;
	User &m_user;

    void generateId();
};

#endif // CREATEDECKWINDOW_H
