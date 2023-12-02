#include "lib/user.h"

User::User()
    :m_username(), m_name()
{}

User::User(const QString &newUsername, const QString &newName)
    :m_username(newUsername), m_name(newName)
{}

User::~User()
{}

void User::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}

void User::setName(const QString &newName)
{
    m_name = newName;
}
