#include "lib/calendar.h"

Calendar::Calendar()
    :m_events()
{}

Calendar::~Calendar()
{}

void Calendar::addEvent(CalendarEvent event){
    m_events[event.dateTime()].push_back(event.eventText());
}

QVariant Calendar::toVariant() const{

}

void Calendar::fromVariant(const QVariant& variant){

}
