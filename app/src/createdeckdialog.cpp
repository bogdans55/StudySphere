#include "lib/createdeckdialog.h"
#include "ui_createdeckdialog.h"

CreateDeckDialog::CreateDeckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDeckDialog)
{
    ui->setupUi(this);

    deckPrivacy = new QButtonGroup(this);
    deckPrivacy->addButton(ui->PrivateRadioButton, 1);
    deckPrivacy->addButton(ui->PublicRadioButton, 2);
}

CreateDeckDialog::~CreateDeckDialog()
{
    delete ui;
}

QString CreateDeckDialog::getDeckName() const
{
    return ui->deckNameLineEdit->text();
}

int CreateDeckDialog::getDeckPrivacy() const
{
//    return deckPrivacy->checkedId() == 1 ? Privacy::PRIVATE : Privacy::PUBLIC;
    return deckPrivacy->checkedId();
}
