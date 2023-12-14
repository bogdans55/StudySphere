#include "lib/logindialog.h"
#include "ui_logindialog.h"

#define LOGIN       (0)
#define REGISTER    (1)

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(LOGIN);
    ui->label_error->setVisible(false);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    m_username = ui->lineEdit_username->text();
    m_password = ui->lineEdit_password->text();
    accept();
}


void LoginDialog::on_pushButton_openRegister_clicked()
{
    m_isRegister = true;
    m_username = ui->lineEdit_username_reg->text();
    m_password = ui->lineEdit_password_reg->text();
    QString confirmPassword = ui->lineEdit_confirmPassword->text();

    if (m_password != confirmPassword)
    {
        ui->lineEdit_password_reg->clear();
        ui->lineEdit_confirmPassword->clear();

        ui->label_error->setVisible(true);
    }
    else
        accept();
}

