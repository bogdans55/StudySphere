#ifndef CREATEDECKWINDOW_H
#define CREATEDECKWINDOW_H

#include <QWidget>

namespace Ui {
class CreateDeckWindow;
}

class CreateDeckWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDeckWindow(QWidget *parent = nullptr);
    ~CreateDeckWindow();

private slots:
    void on_finishedButton_clicked();

    void on_addNewButton_clicked();

private:
    Ui::CreateDeckWindow *ui;
};

#endif // CREATEDECKWINDOW_H
