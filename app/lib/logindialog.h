#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    inline QString getUsername() const { return m_username; }
    inline QString getPassword() const { return m_password; }
    inline bool isRegister() const { return m_isRegister; }

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_openRegister_clicked();

private:
    Ui::LoginDialog *ui;
    QString m_username;
    QString m_password;
    bool m_isRegister = false;
};

#endif // LOGINDIALOG_H
