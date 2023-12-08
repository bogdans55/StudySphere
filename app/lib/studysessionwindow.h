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
    void on_pushButton_flip_clicked();

    void on_pushButton_skip_clicked();

    void on_pushButton_bad_clicked();

    void on_pushButton_mid_clicked();

    void on_pushButton_good_clicked();

private:
    Ui::StudySessionWindow *ui;
};

#endif // STUDYSESSIONWINDOW_H
