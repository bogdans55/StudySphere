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

