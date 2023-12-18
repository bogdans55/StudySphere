#include "lib/calendarevent.h"

CalendarEvent::CalendarEvent()
    :m_eventText(),
    m_dateTime()
{}

CalendarEvent::CalendarEvent(QString eventText, QDateTime dateTime)
    :m_eventText(eventText),
    m_dateTime(dateTime)
{}

CalendarEvent::~CalendarEvent()
{}

QVariant CalendarEvent::toVariant() const
{
    QVariantMap map;
    map.insert("event", m_eventText);
    map.insert("dateTime", m_dateTime);
    return map;
}

void CalendarEvent::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_eventText = map.value("event").toString();
    m_dateTime = map.value("dateTime").toDateTime();
}
