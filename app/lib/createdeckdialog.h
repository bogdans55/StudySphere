#ifndef CREATEDECKDIALOG_H
#define CREATEDECKDIALOG_H

#include <QDialog>

namespace Ui {
class CreateDeckDialog;
}

class CreateDeckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDeckDialog(QWidget *parent = nullptr);
    ~CreateDeckDialog();

private:
    Ui::CreateDeckDialog *ui;
};

#endif // CREATEDECKDIALOG_H
