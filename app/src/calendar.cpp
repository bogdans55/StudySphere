#include "lib/calendar.h"

Calendar::Calendar()
    :m_eventText(),
    m_dateTime()
{}

Calendar::Calendar(QString eventText, QDateTime dateTime)
    :m_eventText(eventText),
    m_dateTime(dateTime)
{}

Calendar::~Calendar()
{}

