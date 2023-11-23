#include "lib/createdeckdialog.h"
#include "ui_createdeckdialog.h"

CreateDeckDialog::CreateDeckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDeckDialog)
{
    ui->setupUi(this);
}

CreateDeckDialog::~CreateDeckDialog()
{
    delete ui;
}
