#include "lib/planner.h"

Planner::Planner()
    :m_map()
{}

Planner::~Planner(){}

void Planner::addActivity(Activity activity, Day day){
    m_map[day].push_back(activity);
}

QString dayToString(Day day){
    switch (day) {
    case Day::MONDAY:
        return "MONDAY";
        break;
    case Day::TUESDAY:
        return "TUESDAY";
        break;
    case Day::WEDNESDAY:
        return "WEDNESDAY";
        break;
    case Day::THURSDAY:
        return "THURSDAY";
        break;
    case Day::FRIDAY:
        return "FRIDAY";
        break;
    case Day::SATURDAY:
        return "SATURDAY";
        break;
    case Day::SUNDAY:
        return "SUNDAY";
        break;
    }
}

QVariant Planner::toVariant() const{
    QVariantMap result;
    for (const auto& day : m_map.keys()) {
        QVariantList activitiesList;
        for (const Activity& activity : m_map.value(day)) {
            activitiesList.append(activity.toVariant());
        }
        result.insert(dayToString(day), activitiesList);
    }
    return result;
}

Day dayFromString(QString dayString){
    if (dayString == "MONDAY")    return Day::MONDAY;
    else if (dayString == "TUESDAY")   return Day::TUESDAY;
    else if (dayString == "WEDNESDAY") return Day::WEDNESDAY;
    else if (dayString == "THURSDAY")  return Day::THURSDAY;
    else if (dayString == "FRIDAY")    return Day::FRIDAY;
    else if (dayString == "SATURDAY")  return Day::SATURDAY;
    else if (dayString == "SUNDAY")    return Day::SUNDAY;
    else                                  return Day::MONDAY;
}

void Planner::fromVariant(const QVariant& variant) {
    QVariantMap map = variant.toMap();
    for (const QString& dayString : map.keys()) {
        Day day = dayFromString(dayString);
        QVector<Activity> activities;
        const QVariantList activitiesList = map.value(dayString).toList();
        for (const QVariant& variant : activitiesList) {
            Activity activity;
            activity.fromVariant(variant);
            activities.append(activity);
        }
        m_map.insert(day, activities);
    }
}


