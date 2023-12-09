#include "lib/logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUsername()
{
    return ui->lineEdit_username->text();
}

QString LoginDialog::getPassword()
{
    return ui->lineEdit_password->text();
}
