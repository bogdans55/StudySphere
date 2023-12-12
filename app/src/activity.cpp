#include "lib/activity.h"

Activity::Activity()
    :m_activityText(),
    m_start(),
    m_end(),
    m_day()
{}

Activity::Activity(QString activityText, QTime start, QTime end, Day day)
    :m_activityText(activityText),
    m_start(start),
    m_end(end),
    m_day(day)
{}

Activity::~Activity()
{}

//QVariant Activity::toVariant() const
//{
//    QVariant map;
//    map.insert("activity", m_activityText);
//    map.insert("start", m_start);
//    map.insert("end", m_end);
//    map.insert("day", m_day);
//    return map;
//}

//void Activity::fromVariant(const QVariant &variant)
//{


//}


