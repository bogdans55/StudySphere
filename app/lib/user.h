#ifndef USER_H
#define USER_H

#include "serializable.h"
#include <QString>

class User : public Serializable
{
  private:
	QString m_username;

  public:
      User(QString m_username);
      User();
      ~User() override;

      inline QString username() const { return m_username; }

      void setUsername(const QString &newUsername);

      QVariant toVariant() const override;
      void fromVariant(const QVariant &variant) override;
};

#endif // USER_H
