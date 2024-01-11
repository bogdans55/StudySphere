#include <utility>

#include "../lib/user.h"

User::User(QString newUsername)
    : m_username(std::move(newUsername))
{}

User::User() = default;

User::~User() = default;

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
