#ifndef STUDYSESSIONWINDOW_H
#define STUDYSESSIONWINDOW_H

#include <QWidget>

#include "lib/studysession.h"

namespace Ui {
class StudySessionWindow;
}

class StudySessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudySessionWindow(QWidget *parent = nullptr);
    StudySessionWindow(const StudySession& session, QWidget *parent = nullptr);
    ~StudySessionWindow();

    inline StudySession session() const {return m_session;}
    void setSession(const StudySession& session);

private slots:
    void on_flipPushButton_clicked();

    void on_skipPushButton_clicked();

    void on_badPushButton_clicked();

    void on_midPushButton_clicked();

    void on_goodPushButton_clicked();

private:
    Ui::StudySessionWindow *ui;
    StudySession m_session;
};

#endif // STUDYSESSIONWINDOW_H
