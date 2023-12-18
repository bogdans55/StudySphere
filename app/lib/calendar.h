#ifndef CALENDAR_H
#define CALENDAR_H

#include "lib/calendarevent.h"
#include <QMap>
#include "lib/serializable.h"

class Calendar : public Serializable
{
private:
    QMap<QDateTime, QString> m_events;
public:
    Calendar();
    ~Calendar();


    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

    void addEvent(CalendarEvent event);

    inline QMap<QDateTime, QString> events() const {return m_events;}
};


#endif // CALENDAR_H
