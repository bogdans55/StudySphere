#include "lib/user.h"

User::User(const QString &newUsername) : m_username(newUsername) {}

User::User() {}

User::~User() {}

void User::setUsername(const QString &newUsername)
{
	m_username = newUsername;
}

QVariant User::toVariant() const
{
	QVariantMap map;
	map.insert("Username", m_username);
	return map;
}

void User::fromVariant(const QVariant &variant)
{
	QVariantMap map = variant.toMap();
	m_username = map.value("Username").toString();
}
