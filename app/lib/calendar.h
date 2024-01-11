#ifndef CALENDAR_H
#define CALENDAR_H

#include "serializable.h"
#include <QDate>
#include <QMap>
#include <QPair>
#include <QTime>

class Calendar : public Serializable
{
  private:
	QMap<QDate, QVector<QPair<QTime, QString>>> m_events;

  public:
	Calendar();
    ~Calendar() override;

    QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

    void addEvent(QDate date, QTime time, const QString &text);
    void deleteAll();

	inline QMap<QDate, QVector<QPair<QTime, QString>>> events() const { return m_events; }
};

#endif // CALENDAR_H
