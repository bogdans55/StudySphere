#ifndef STUDYSESSIONWINDOW_H
#define STUDYSESSIONWINDOW_H

#include <QWidget>

namespace Ui {
class StudySessionWindow;
}

class StudySessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudySessionWindow(QWidget *parent = nullptr);
    ~StudySessionWindow();

private slots:
    void on_flipPushButton_clicked();

    void on_skipPushButton_clicked();

    void on_badPushButton_clicked();

    void on_midPushButton_clicked();

    void on_goodPushButton_clicked();

private:
    Ui::StudySessionWindow *ui;
};

#endif // STUDYSESSIONWINDOW_H
