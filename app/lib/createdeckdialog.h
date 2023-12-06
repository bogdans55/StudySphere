#ifndef CREATEDECKDIALOG_H
#define CREATEDECKDIALOG_H

#include "lib/deck.h"
#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class CreateDeckDialog;
}

class CreateDeckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDeckDialog(QWidget *parent = nullptr);
    ~CreateDeckDialog();

    QString getDeckName() const;
    Privacy getDeckPrivacy() const;

private:
    Ui::CreateDeckDialog *ui;
    QButtonGroup *deckPrivacy;
};

#endif // CREATEDECKDIALOG_H
