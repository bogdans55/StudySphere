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
    explicit StudySessionWindow(QWidget *parent, const StudySession& session);
    ~StudySessionWindow();

    inline StudySession session() const {return m_session;}
    inline void setSession(const StudySession& session) {m_session=session;}

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
