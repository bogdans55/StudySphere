#ifndef USER_H
#define USER_H

#include<QString>

class User
{
private:
    QString m_username;

public:
    User(const QString &m_username);
    User();
    ~User();



    inline QString username() const {return m_username;}
    void setUsername(const QString &newUsername);
};

#endif // USER_H
