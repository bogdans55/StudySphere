#ifndef USER_H
#define USER_H

#include<QString>
#include<iostream>

class User
{
private:
    QString m_username;
    QString m_name;

public:
    User(const QString &m_username, const QString &m_name);
    ~User();



    inline QString username() const {return m_username;}
    inline QString name() const {return m_name;}
    void setUsername(const QString &newUsername);
    void setName(const QString &newName);
};

#endif // USER_H
