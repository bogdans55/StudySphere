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

private:
    Ui::StudySessionGUI *ui;
};

#endif // STUDYSESSIONGUI_H
