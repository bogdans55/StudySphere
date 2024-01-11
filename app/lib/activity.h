#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "serializable.h"
#include <QString>
#include <QTime>

class Activity : Serializable
{
  public:
	Activity();
	Activity(QString m_activityText, QTime m_start, QTime m_end);
    ~Activity() override;

    inline QString activityText() const { return m_activityText; }

	inline QTime start() const { return m_start; }

	inline QTime end() const { return m_end; }

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

  private:
	QString m_activityText;
	QTime m_start;
	QTime m_end;
};

#endif // ACTIVITY_H
