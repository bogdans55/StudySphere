#include "lib/user.h"

User::User(const QString &newUsername)
    :m_username(newUsername)
{}

User::User()
{}

User::~User()
{}

void User::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}
