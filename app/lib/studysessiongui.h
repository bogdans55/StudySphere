#ifndef STUDYSESSIONGUI_H
#define STUDYSESSIONGUI_H

#include <QWidget>

namespace Ui {
class StudySessionGUI;
}

class StudySessionGUI : public QWidget
{
    Q_OBJECT

public:
    explicit StudySessionGUI(QWidget *parent = nullptr);
    ~StudySessionGUI();

private slots:
    void on_flipPushButton_clicked();

    void on_skipPushButton_clicked();

    void on_badPushButton_clicked();

    void on_midPushButton_clicked();

    void on_goodPushButton_clicked();

private:
    Ui::StudySessionGUI *ui;
};

#endif // STUDYSESSIONGUI_H
