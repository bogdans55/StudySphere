#include "lib/planner.h"

Planner::Planner()
    :m_activityText(),
    m_start(),
    m_end(),
    m_day()
{}

Planner::Planner(QString activityText, QString start, QString end, QString day)
    :m_activityText(activityText),
    m_start(start),
    m_end(end),
    m_day(day)
{}

Planner::~Planner()
{}

void Planner::fromJson(const QJsonObject &json){
    m_activityText.operator = (json["activity"].toString());
    m_start.operator = (json["start"].toString());
    m_end.operator = (json["end"].toString());
    m_day.operator = (json["day"].toString());
}


