#include "lib/activity.h"
#include <QVariantMap>

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

QVariant Activity::toVariant() const
{
    QVariantMap map;
    map.insert("activity", m_activityText);
    map.insert("start", m_start);
    map.insert("end", m_end);
    return map;
}

void Activity::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_activityText = map.value("activity").toString();
    m_start = map.value("start").toTime();
    m_end = map.value("end").toTime();
}


