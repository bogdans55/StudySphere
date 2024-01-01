#ifndef STUDYSESSIONWINDOW_H
#define STUDYSESSIONWINDOW_H

#include <QWidget>

#include "lib/studysession.h"
#include "lib/whiteboardwindow.h"

namespace Ui
{
class StudySessionWindow;
}

class StudySessionWindow : public QWidget
{
	Q_OBJECT

  public:
	explicit StudySessionWindow(QWidget *parent = nullptr);
	StudySessionWindow(StudySession *session, QWidget *parent = nullptr);
	~StudySessionWindow() override;

	inline StudySession *session() const { return m_session; }

	void evaluate(int grade);

  private slots:
	void on_pushButton_flip_clicked();

	void on_pushButton_skip_clicked();

	void on_pushButton_bad_clicked();

	void on_pushButton_mid_clicked();

	void on_pushButton_good_clicked();

	void on_pushButton_whiteboard_clicked();

  public slots:
	void closeWhiteboard();

	void clearWhiteboard();

  private:
	Ui::StudySessionWindow *ui;
	StudySession *m_session;

	WhiteboardWindow *m_whiteboard = nullptr;

    void setDifficultyColor();
};

#endif // STUDYSESSIONWINDOW_H
