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
    void on_pushButton_flip_clicked();

    void on_pushButton_skip_clicked();

    void on_pushButton_bad_clicked();

    void on_pushButton_mid_clicked();

    void on_pushButton_good_clicked();

private:
    Ui::StudySessionWindow *ui;
    StudySession m_session;
};

#endif // STUDYSESSIONWINDOW_H
