#include "lib/activity.h"

Activity::Activity()
    :m_activityText(),
    m_start(),
    m_end()
{}

Activity::Activity(QString activityText, QTime start, QTime end)
    :m_activityText(activityText),
    m_start(start),
    m_end(end)
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


